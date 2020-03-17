TARGETS = InsertionSortle, InsertionSortge, MergeSortle, MergeSortge, QuickSortle, QuickSortge

all: $(TARGETS)

clean:
	rm -f *.o $(TARGETS)

InsertionSortle: InsertionSortle.o pcg_basic.o
InsertionSortge: InsertionSortge.o pcg_basic.o
MergeSortle: MergeSortle.o pcg_basic.o
MergeSortge: MergeSortge.o pcg_basic.o
QuickSortle: QuickSortle.o pcg_basic.o
QuickSortge: QuickSortge.o pcg_basic.o

pcg_basic.o: pcg_basic.c pcg_basic.h
InsertionSortle.o: InsertionSortle.c pcg_basic.h
InsertionSortge.o: InsertionSortge.c pcg_basic.h
MergeSortle.o: MergeSortle.c pcg_basic.h
MergeSortge.o: MergeSortge.c pcg_basic.h
QuickSortle.o: QuickSortle.c pcg_basic.h
QuickSortge.o: QuickSortge.c pcg_basic.h