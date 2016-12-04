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
