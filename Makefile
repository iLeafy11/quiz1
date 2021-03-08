CC=gcc -Wall
obj1=list.o

recursive: $(obj1) qsort.c
	$(CC) $(obj1) qsort.c -o qsort

iterative: $(obj1) qsort_iterative.c
	$(CC) $(obj1) qsort_iterative.c -o qsort

clean:
	rm -f *.o qsort
