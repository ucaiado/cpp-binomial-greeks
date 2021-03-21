Calculating option greeks using Copulas
==============================

This project is part of the [C++ Nanodegree](https://www.udacity.com/course/c-plus-plus-nanodegree--nd213)
 program from Udacity. I develop a ....


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


### License
The contents of this repository are covered under the [MIT License](LICENSE).
