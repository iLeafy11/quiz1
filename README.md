# 2021q1 Homework1 (quiz1)
contributed by < `iLeafy11` >
###### tags: `linux2021`

## 作業描述

Implementing quick sort using singly linked list.

[作業要求](https://hackmd.io/@sysprog/SJlXFVMzMu)

## Makefile

### Make recursive quicksort
```
$ make recursive
gcc -Wall    -c -o list.o list.c
gcc -Wall list.o qsort.c -o qsort
```
### Make iterative quicksort
```
$ make iterative
gcc -Wall    -c -o vector.o vector.c
gcc -Wall list.o vector.o qsort_iterative.c -o qsort
```
### clean
```
$ make clean
rm -f *.o qsort
```
## execution
```
$ ./qsort
```

## HackMD

[2021q1 Homework1 (quiz1)](https://hackmd.io/g1_AyhXXRRmwtRh965SKLw?view)
