#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <math.h>

#define MAXN 5000000
#define PI_BIN_SIZE ((long)(MAXN + 1) * 4)

/* Count primes <= N (1 <= N <= 5000000). Reads N on stdin, prints pi(N).
 *
 * Fast path: precomputed pi.bin (built by `make pi.bin`, uint32 pi[i] for
 * i = 0..MAXN) — a single 4-byte read at offset N*4. Falls back to an
 * odd-only sieve of Eratosthenes when pi.bin is absent, so the program is
 * correct with or without the table. */
static int table_lookup(int n, int *out) {
    FILE *f = fopen("pi.bin", "rb");
    if (!f) return 0;
    if (fseek(f, 0, SEEK_END) != 0) { fclose(f); return 0; }
    long sz = ftell(f);
    if (sz != PI_BIN_SIZE) { fclose(f); return 0; }
    if (fseek(f, (long)n * 4, SEEK_SET) != 0) { fclose(f); return 0; }
    uint32_t v;
    if (fread(&v, 4, 1, f) != 1) { fclose(f); return 0; }
    fclose(f);
    *out = (int)v;
    return 1;
}

static int sieve_count(int n) {
    if (n < 2) return 0;
    int m = (n + 1) / 2;
    unsigned char *c = malloc(m);
    memset(c, 1, m);
    int sq = (int)sqrt((double)n);
    for (int p = 3; p <= sq; p += 2) {
        if (c[p / 2]) {
            for (long long j = (1LL * p * p) / 2; j < m; j += p) c[j] = 0;
        }
    }
    int cnt = 1; /* prime 2 */
    for (int i = 1; i < m; i++) if (c[i]) cnt++;
    return cnt;
}

int main(void) {
    int n;
    if (scanf("%d", &n) != 1) return 0;
    if (n < 0) n = 0;
    if (n > MAXN) n = MAXN;
    int out;
    if (table_lookup(n, &out)) {
        printf("%d\n", out);
        return 0;
    }
    printf("%d\n", sieve_count(n));
    return 0;
}
