# kupyna-c

[![Build and Test](https://github.com/sjinks/kupyna-c/actions/workflows/test.yml/badge.svg)](https://github.com/sjinks/kupyna-c/actions/workflows/test.yml)
[![codecov](https://codecov.io/gh/sjinks/kupyna-c/branch/master/graph/badge.svg)](https://codecov.io/gh/sjinks/kupyna-c)
[![Coverity Scan Build Status](https://scan.coverity.com/projects/11055/badge.svg)](https://scan.coverity.com/projects/sjinks-kupyna-c)

Implementation of the Kupyna hash function (DSTU 7564:2014) inspired by [this project](https://github.com/Roman-Oliynykov/Kupyna-reference).

Unlike the original implementation, this project uses a different and more traditional API: instead of hashing the entire block at once,
it allows the developer to feed buffers of arbitrary size to the hash function (i.e., it follows the traditional init/update/final approach).

SSE and SSE2 are used if available.
