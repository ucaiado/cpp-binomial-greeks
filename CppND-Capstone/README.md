# CPPND: Capstone  - Calculating option greeks using Bianomial Tree

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


## Dependencies for Running Locally
* cmake >= 3.7
  * All OSes: [click here for installation instructions](https://cmake.org/install/)
* make >= 4.1 (Linux, Mac), 3.81 (Windows)
  * Linux: make is installed by default on most Linux distros
  * Mac: [install Xcode command line tools to get make](https://developer.apple.com/xcode/features/)
  * Windows: [Click here for installation instructions](http://gnuwin32.sourceforge.net/packages/make.htm)
* gcc/g++ >= 5.4
  * Linux: gcc / g++ is installed by default on most Linux distros
  * Mac: same deal as make - [install Xcode command line tools](https://developer.apple.com/xcode/features/)
  * Windows: recommend using [MinGW](http://www.mingw.org/)


## Basic Build Instructions

1. Clone this repo.
2. Make a build directory in the top level directory: `mkdir build && cd build`
3. Compile: `cmake .. && make`
4. Run it: `./OptionsData`.


### Reference
1. P. Wilmott.  *Paul Wilmott on Quantitative Finance 3 Volume Set
 (2nd Edition)*. Wiley, 2006. pg 287-289 [*link*](https://bit.ly/3w8YGPQ)
2. CL. Costa.  *Opções - Operando Volatilidade*. BMF, 1999. pg 97-99
 [*link*](https://bit.ly/3db063z)


## Rubric Points Addressed

This project addressed many of the points suggested in the rubric. For example,
 in file/header `file_parser` **, the program reads data from a file, processes
 it, and then writes the output to another file**.  The project also **uses
 Object Oriented Programming techniques** and **uses appropriate access
 specifiers for class members**. The class Portfolio is in the file/header
 `option_portfolio`. The project also ** uses references in function
 declarations**, as can be seen in the function `binomialtree`,  also in
 `option_portfolio`. **Smart pointers instead of raw pointers** are used in
 `compute_udly_greeks`, in `pricing` files. Finally, **the project uses
 multithreading** in `main` to calculate the greeks to all options of each
 underlying stock.
