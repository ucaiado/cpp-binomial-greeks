Calculating option greeks using Bianomial Tree
==============================

This project is part of the [C++ Nanodegree](https://www.udacity.com/course/c-plus-plus-nanodegree--nd213)
 program from Udacity. I develop a program to approximate and consolidate an
 options portfolio's Greeks using the binomial tree model. The Greeks are
 defined as derivatives of the option value with respect to the underlying
 parameters on which it is dependent. They help decide how to hedge the
 positions against some of its risk drivers, as stock price direction,
 volatility, and interest rate. After calculating the greeks and current PnL
 for a portfolio read from `data/portfolio.csv`, the program output the results
 in the same folder in two different files. One with the data computed to all
 options and another with the data consolidated by the underlying stock.


### Install
To set up your environment to run the code in this repository, start by
 installing Docker and Make in your machine (in Windows, you may want to try
 [chocolatery](https://chocolatey.org/packages/make)). Then, run the following
 commands

```shell
$ make docker-build
$ make environment-test
```


### Run
In a terminal or command window, navigate to the top-level project directory
 `cpp-binomial-greeks/` (that contains this README) and run the following
 command.

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
