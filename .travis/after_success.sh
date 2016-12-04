#!/bin/bash

/bin/bash <(curl -s https://codecov.io/bash) -s coverage-default/ -s coverage-nosse/ -s coverage-nosse2/ -X gcov
