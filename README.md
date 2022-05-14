# LIRS-cache
---
## How to build the project 

* mkdir build
* cd build
* cmake ..
* make 

## Compiler settings:
```
-Wall -Wextra -Wpedantic -O2
```
#### In a folder 'build' a file 'lirs' will appear executing a program
---
## Input data:
* cache size
* number of files
* name of uploaded files
## Output data:
* how many times an input file has already been cached
---
## A little about the algorithm:
LIRS is Low Inter-reference Recency Set. This algorithm is based on such parameters of each incoming file as 
Inter-Reference Recency (IRR) and Recency. We use recent Inter-Reference Recency (IRR) as the recorded
history information of each block, where IRR of a block refers to the number of other blocks accessed between 
two consecutive references to the block. Cache memory is divided into two parts: Lir, where the most frequently 
called files are located, and Resident HIR. Files not written to memory are called Non-Resident HIR.

In the implementation, we used two objects such as stack and list. List holds files from Resident HIR, 
and at the top are the most recently called ones. The stack stores all the files that come to the input
with their status (Lir, Resident HIR or Non-Resident HIR), and the last called ones are located at the top.

---
## Some examples of how the algorithm works:

**Calling a file stored in the LIR:**
![Calling a file stored in the LIR](https://github.com/xKobi74/LIRS-cache/blob/main/cmake/1.jpg)

**Calling a file not written to the cache but present in the stack:**
![Calling a file not written to the cache but present in the stack](https://github.com/xKobi74/LIRS-cache/blob/main/cmake/2.jpg)

**Calling a file not written to the cache or stack:**
![Calling a file not written to the cache or stack](https://github.com/xKobi74/LIRS-cache/blob/main/cmake/3.jpg)

**Calling a non-resident file written to stack:**
![Calling a non-resident file written to stack](https://github.com/xKobi74/LIRS-cache/blob/main/cmake/4.jpg)

---

## Useful materials:
+ http://web.cse.ohio-state.edu/hpcs/WWW/HTML/publications/papers/TR-02-6.pdf
+ https://russianblogs.com/article/59551446435/
