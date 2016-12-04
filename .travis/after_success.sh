#!/bin/bash

if [ "$CC" = "clang" ]; then
	GCOVEXE=gcov
	GCOVARGS=""
else
	GCOVEXE=llvm-cov
	GCOVARGS="gcov"
fi

/bin/bash <(curl -s https://codecov.io/bash) -x "$GCOVEXE" -a "$GCOVARGS"
