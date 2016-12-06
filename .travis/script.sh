#!/bin/sh

set -e

if [ "$CC" = "gcc" ]; then
	GCOV=gcov
	ARGS=""
else
	GCOV=llvm-cov
	ARGS=gcov
fi

make -B CFLAGS="-Wall -O2" test

make clean
make -B CFLAGS="-Wall -O0 --coverage" LDFLAGS="--coverage" test
$GCOV $ARGS *.c
mkdir -p coverage-sse2
mv *.gcov coverage-sse2/
rm -f *.gcno *.gcda

make clean
make -B CFLAGS="-Wall -O0 --coverage -mno-sse2" LDFLAGS="--coverage" test
$GCOV $ARGS *.c
mkdir -p coverage-sse
mv *.gcov coverage-sse/
rm -f *.gcno *.gcda

make clean
make -B CFLAGS="-Wall -O0 --coverage -mmmx -mno-sse -mno-sse2" LDFLAGS="--coverage" test
$GCOV $ARGS *.c
mkdir -p coverage-mmx
mv *.gcov coverage-mmx/
rm -f *.gcno *.gcda

make clean
make -B CFLAGS="-Wall -O0 --coverage -mno-mmx -mno-sse -mno-sse2" LDFLAGS="--coverage" test
$GCOV $ARGS *.c
mkdir -p coverage-raw
mv *.gcov coverage-raw/
rm -f *.gcno *.gcda

make clean

echo "SSE2 (64 bit)"
make -s -B CFLAGS="-std=c11 -Wall -O2 -msse2" benchmark
echo "SSE (64 bit)"
make -s -B CFLAGS="-std=c11 -Wall -O2 -mno-sse2 -msse" benchmark
echo "SSE2 (32 bit)"
make -s -B CFLAGS="-std=c11 -Wall -O2 -msse2 -m32" LDFLAGS="-m32" benchmark
echo "SSE (32 bit)"
make -s -B CFLAGS="-std=c11 -Wall -O2 -mno-sse2 -msse -m32" LDFLAGS="-m32" benchmark
echo "MMX (32 bit)"
make -s -B CFLAGS="-std=c11 -Wall -O2 -mno-sse2 -mno-sse -mmmx -m32" LDFLAGS="-m32" benchmark
echo "Raw (32 bit)"
make -s -B CFLAGS="-std=c11 -Wall -O2 -mno-sse2 -mno-sse -mno-mmx -m32" LDFLAGS="-m32" benchmark
