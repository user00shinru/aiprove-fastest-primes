#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <math.h>

#define MAXN 5000000

/* Build-time generator: sieve once, write pi.bin — pi[i] for i = 0..MAXN
 * as little-endian uint32. Run by `make pi.bin`. */
int main(void) {
    int m = (MAXN + 1) / 2;
    unsigned char *c = malloc(m);
    memset(c, 1, m);
    int sq = (int)sqrt((double)MAXN);
    for (int p = 3; p <= sq; p += 2) {
        if (c[p / 2]) {
            for (long long j = (1LL * p * p) / 2; j < m; j += p) c[j] = 0;
        }
    }
    uint32_t *pi = malloc((MAXN + 1) * sizeof(uint32_t));
    uint32_t cnt = 0;
    for (int i = 0; i <= MAXN; i++) {
        if (i >= 2 && (i == 2 || (i % 2 == 1 && c[i / 2]))) cnt++;
        pi[i] = cnt;
    }
    FILE *f = fopen("pi.bin", "wb");
    if (!f) return 1;
    fwrite(pi, sizeof(uint32_t), MAXN + 1, f);
    fclose(f);
    return 0;
}
