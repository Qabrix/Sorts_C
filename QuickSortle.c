#include <stdio.h>
#include <stdlib.h>

int comp = 0;
int trans = 0;

void QuickSort(int lenght, int *elements) {
    if (lenght <= 1) {
        return;
    }

    int div_p = *(elements+lenght-1); // biore div_p jako ostatni element tablicy, zawsze
    int index_left = 0;
    int index_right = lenght-2;

    while (index_left < index_right) { // to nasz warunek, robie na dwa "pointery"
        comp++;
        if (*(elements+index_left) > div_p) {
            while (index_left < index_right) {
                comp++;
                if (*(elements+index_right) <= div_p) {
                    int swap = *(elements+index_right);
                    *(elements+index_right) = *(elements+index_left);
                    *(elements+index_left) = swap;
                    index_right--;
                    index_left++;
                    goto END; // jesli udal sie swap to robimy "break"
                } else {
                    index_right--;
                }
            }
            goto SWAP; // jesli nie bylo goto END to wtedy while() skonczyl sie na index_left == index_right i wiemy ze *(elements+index_right) <= div_p wiec mozemy swap
END:        trans++;
        } else {
            index_left++;
        }
    }

    comp++;
    if (*(elements+index_left) > div_p) {
SWAP:   *(elements+lenght-1) = *(elements+index_left);
        *(elements+index_left) = div_p;
        index_left--;
        trans++;
    } else { // w tym wypadku skonczylismy na ostatniej mniejszej lub rownej od div_p wiec swapujemy kolejna z div_p
        *(elements+lenght-1) = *(elements+index_left+1); // czasami swapniemy div_p z samym soba, probowalem jakos to zrobic ale jednak zostalo :(
        *(elements+index_left+1) = div_p;
        trans++;
    }

    QuickSort(index_left+1, elements);
    QuickSort(lenght-index_left-2, elements+index_left+2);
}

int main() {
    int lenght = 0;
    printf("Welcome to Quick Sort <=, enter lenght: ");
    scanf("%d", &lenght);
    int *elements = malloc(sizeof(int)*lenght);
    printf("Insert %d elements: ", lenght);
    for (int i=0; i<lenght; i++) {
        scanf("%d", elements+i);
    }

    QuickSort(lenght, elements);

    for (int i=1; i<lenght; i++) {
        if (*(elements+i) < *(elements+i-1)) {
            fprintf(stderr, "Array not sorted.\n");
            exit(1);
        }
    }

    for (int i=0; i<lenght; i++) {
        printf("%d, ", *(elements+i));
    }
    printf("\n");

    fprintf(stderr, "Comparisions = %d\n", comp);
    fprintf(stderr, "Transpositions = %d\n", trans);

    return 0;
}