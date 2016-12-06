#!/bin/sh

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
mkdir -p coverage-default
mv *.gcov coverage-default/
rm -f *.gcno *.gcda

make clean
make -B CFLAGS="-Wall -O0 --coverage -mno-sse -mno-sse2" LDFLAGS="--coverage" test
$GCOV $ARGS *.c
mkdir -p coverage-nosse
mv *.gcov coverage-nosse/
rm -f *.gcno *.gcda

make clean
make -B CFLAGS="-Wall -O0 --coverage -mno-sse2" LDFLAGS="--coverage" test
$GCOV $ARGS *.c
mkdir -p coverage-nosse2
mv *.gcov coverage-nosse2/
rm -f *.gcno *.gcda

make clean

echo "SSE2 (64 bit)"
make -s -B CFLAGS="-Wall -O2 -msse2" benchmark
echo "SSE (64 bit)"
make -s -B CFLAGS="-Wall -O2 -mno-sse2 -msse" benchmark
echo "SSE2 (32 bit)"
make -s -B CFLAGS="-Wall -O2 -msse2 -m32" LDFLAGS="-m32" benchmark
echo "SSE (32 bit)"
make -s -B CFLAGS="-Wall -O2 -mno-sse2 -msse -m32" LDFLAGS="-m32" benchmark
echo "Raw (32 bit)"
make -s -B CFLAGS="-Wall -O2 -mno-sse2 -mno-sse -m32" LDFLAGS="-m32" benchmark
