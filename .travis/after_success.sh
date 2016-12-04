#!/bin/bash

if [ "$CC" = "gcc" ]; then
	gcov *.c
else
	llvm-cov gcov *.c
fi

/bin/bash <(curl -s https://codecov.io/bash) -X gcov
