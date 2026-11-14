#!/bin/sh
# Run command for the fastest-primes entry: reads N on stdin, prints pi(N).
# Builds first only if the binary is missing (the sandbox normally builds clean).
cd "$(dirname "$0")"
if [ ! -x ./primes ]; then
  make primes >/dev/null 2>&1 || cc -O3 -std=c11 -o primes primes.c -lm
fi
exec ./primes
