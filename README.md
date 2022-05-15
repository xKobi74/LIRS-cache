# LIRS-cache
---
## How to build the project: 

* mkdir build
* cd build
* cmake ..
* make 

## Compiler settings:
```
-Wall -Wextra -Wpedantic -O2
```
In a folder 'build' a file 'lirs' will appear executing a program

---
## Input data:
* cache size
* number of files
* name of uploaded files
## Output data:
* number of times when input file has already been cached
---
## How to build the tester:

* mkdir build_tester
* cd build_tester
* cmake ../tester
* make 

## Compiler settings:
```
-Wall -Wextra -Wpedantic -O2
```
In a folder 'build_tester' a file 'lirs_tester' will appear executing a program

## How to run tester:

To start it with random tests: 
```
./lirs_tester 0 ../tester/tests
```
Returns number of files that should not be overwritten

To start it with unit tests: 
```
./lirs_tester 1 ../tester/tests.txt
``` 
Returns number of files that should not be overwritten if correct, else return wrong answer and correct answer

## How to generated tests:

* cd ../tester/
* gcc main_generator.c generator.c
* ./a.out tests [number_of_tests] [max_cache] [max_files] [max_name]

[number_of_tests] - Number of tests

[max_cache] - Maximum possible cache size

[max_files] - The maximum number of files that can come in

[max_name] - The maximum number of the incoming file by module     

An example to generated tests:
```
./a.out tests 100 1000 10000 100000
```

If enter ```./a.out tests``` starts with default parameters:

[number_of_tests] = 5

[max_cache] = 20

[max_files] = 100

[max_name] = 40  

---
## Documentation:

The documentation generated with doxygen can be found here:
[LIRS-cache](https://xkobi74.github.io/LIRS-cache/html/index.html)

---
## A little about the algorithm:
LIRS is Low Inter-reference Recency Set. This algorithm is based on such parameters of each incoming file as 
Inter-Reference Recency (IRR) and Recency. We use recent Inter-Reference Recency (IRR) as the recorded
history information of each block, where IRR of a block refers to the number of other blocks accessed between 
two consecutive references to the block. Cache memory is divided into two parts: Lir, where the most frequently 
called files are located, and Resident HIR, where to store recent called files. Files not written to memory are called Non-Resident HIR.

In the implementation, we used two objects such as stack and list. List holds files from Resident HIR, 
and there are the most recently called ones at the top. The stack stores all the files that come to the input
with their status (Lir, Resident HIR or Non-Resident HIR), and the last called ones are located at the top. 
During the process of the algorithm, some files from the stack can be removed. Therefore, not necessarily all 
files stored in the list (Resident_HIR) will be on the stack.

---
## Some examples of how the algorithm works:

**Calling a file stored in the LIR:**
![Calling a file stored in the LIR](https://github.com/xKobi74/LIRS-cache/blob/main/pictures/1.jpg)

**Calling a file not written to the cache but presented in the stack:**
![Calling a file not written to the cache but presented in the stack](https://github.com/xKobi74/LIRS-cache/blob/main/pictures/2.jpg)

**Calling a file not written to the cache or stack:**
![Calling a file not written to the cache or stack](https://github.com/xKobi74/LIRS-cache/blob/main/pictures/3.jpg)

**Calling a file written to the stack and to list:**
![Calling a file written to the stack and to list](https://github.com/xKobi74/LIRS-cache/blob/main/pictures/4.jpg)

---

## Useful materials:
+ http://web.cse.ohio-state.edu/hpcs/WWW/HTML/publications/papers/TR-02-6.pdf
+ https://russianblogs.com/article/59551446435/
