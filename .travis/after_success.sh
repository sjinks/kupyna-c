#!/bin/bash

/bin/bash <(curl -s https://codecov.io/bash) -s coverage-raw/ -s coverage-mmx/ -s coverage-sse/ -s coverage-sse2/ -X gcov
