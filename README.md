# matrixDescriber [![Build Status](https://travis-ci.org/cbkmephisto/matrixDescriber.svg?branch=master)](https://travis-ci.org/cbkmephisto/matrixDescriber)
Trivial tool to summarize column-wised data file, printing min/mean/max/std for each column and (co-)variance, correlation and linear regression coefficient matrices for all columns.

## Dependency
`matrixDescriber` depends on [eigen3][c41c0ee0].

  [c41c0ee0]: http://eigen.tuxfamily.org/index.php

- For Ubuntu Linux, install `libeigen3-dev` before `make`

    ```
    sudo apt-get update && sudo apt-get install libeigen3-dev
    ```
- For Mac OS X, I used port:

    ```
    sudo port install eigen3
    ```
- Other operating system may need to install the package with a different name, or download directly from the [eigen3][c41c0ee0] website. Makefile may need to be modified to correct for the full path to your [eigen3][c41c0ee0] header files.


## Compile
```
make
```
or
```
g++ matrixDescriber.cpp -o matrixDescriber
```

## Install
Copy/move the executable to somewhere in your PATH environment variable.

## Usage example
```
Wed Dec 14 14:53:52 cbkmephisto@cervine $ cat test
1 2 3 4 5
3 5 2 3 1
6 7 8 9 6
1 5 4 5 6
6 7 4 5 4
3 4 5 4 3
2 6 2 7 4

Wed Dec 14 14:55:43 cbkmephisto@cervine $ matrixDescriber test
v20150112-1644
MatrixDescriber::load() finished successfully, returning matrix (7, 5)

======== DESCRIPTION
     min           1           2           2           3           1
    mean     3.14286     5.14286           4     5.28571     4.14286
     max           6           7           8           9           6

======== VARIANCE / COVARIANCE MATRIX
   4.47619    2.80952    2.66667    1.95238 -0.0238095
   2.80952    3.14286    1.33333    2.28571   0.309524
   2.66667    1.33333    4.33333    2.66667          2
   1.95238    2.28571    2.66667     4.2381    2.28571
-0.0238095   0.309524          2    2.28571    3.14286

======== CORRELATION COEFFICIENT MATRIX
          1    0.749059    0.605485    0.448255 -0.00634796
   0.749059           1    0.361298    0.626288   0.0984849
   0.605485    0.361298           1    0.622261    0.541947
   0.448255    0.626288    0.622261           1    0.626288
-0.00634796   0.0984849    0.541947    0.626288           1

======== REGRESSION COEFFICIENT MATRIX: mB(r, c)=b(r/c)
          1    0.893939    0.615385    0.460674 -0.00757575
    0.62766           1    0.307692    0.539326   0.0984848
   0.595745    0.424243           1    0.629214    0.636364
    0.43617    0.727273    0.615385           1    0.727273
-0.00531915   0.0984849    0.461539    0.539326           1
```
