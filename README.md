Calculating option greeks using Bianomial Tree
==============================

This project is part of the [C++ Nanodegree](https://www.udacity.com/course/c-plus-plus-nanodegree--nd213)
 program from Udacity. I develop a program to approximate and consolidate the
 greeks of an options portfolio using the binomial tree model. The greeks are
 defined as derivatives of the option value with respect to the underlying
 parameters on which it is dependent. They help decide how to hedge the
 positions against some of its risk drivers, as stock price direction,
 volatility, and interest rate.


### Install
To set up your python environment to run the code in this repository, start by
 creating a new environment with Anaconda and install de dependencies. You also
 need to install Docker and Make in your machine (in Windows, you may want to try
 [chocolatery](https://chocolatey.org/packages/make)).

```shell
$ conda create --name greeks python=3.6
$ source activate greeks
$ pip install -r requirements.txt
$ make docker-build
$ make environment-test
```


### Run
In a terminal or command window, navigate to the top-level project directory
 `cpp-copula-greeks/` (that contains this README) and run the following
 command, which will ....

```shell
$ make greeks-computation
```

### Reference
1. P. Wilmott.  *Paul Wilmott on Quantitative Finance 3 Volume Set
 (2nd Edition)*. Wiley, 2006. pg 287-289 [*link*](https://bit.ly/3w8YGPQ)
2. CL. Costa.  *Opções - Operando Volatilidade*. BMF, 1999. pg 97-99
 [*link*](https://bit.ly/3db063z)


### License
The contents of this repository are covered under the [MIT License](LICENSE).
