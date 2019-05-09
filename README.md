# HaarIntegral
Code that EXACTLY computes Haar integral on SU(2) (or SO(3)) using iRRAM library in C++
# Requirements
* gen-modulus branch of fbrausse's iRRAM (https://github.com/fbrausse/iRRAM/tree/gen-modulus)
* On Ubuntu 18.04 LTS, the iRRAM we require needs the followings: autoconf, libgmp-dev, libmpfr-dev, gcc, g++, make, libtool
# Notes
* Integral on the real interval [0,1] can be computed with `IntegralOnR`. It can compute about down to two decimal points in a minute.
* Integral on SU(2) (or SO(3)) can be computed with `IntegralOnSU2`. Currently, it does not give any meaningful results in reasonable time.
* All codes are very slow, because they are all basically exponential time.
