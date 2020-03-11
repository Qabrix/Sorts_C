#include <stdio.h>
#include <stdlib.h>

int main() {
    int lenght = 0;
    printf("Welcome to Insertion Sort >=, enter lenght: ");
    scanf("%d", &lenght);
    int *elements = malloc(sizeof(int)*lenght);
    printf("Insert %d elements: ", lenght);
    for (int i=0; i<lenght; i++) {
        scanf("%d", elements+i);
    }

    int temp;
    for (int i=lenght-1; i>0; i--) {
        for (int k=0; k<i; k++) {
            if (*(elements+k) < *(elements+k+1)) {
                temp = *(elements+k+1);
                *(elements+k+1) = *(elements+k);
                *(elements+k) = temp;
            }
        }
    }

    for (int i=1; i<lenght; i++) {
        if (*(elements+i) > *(elements+i-1)) {
            fprintf(stderr, "Tablica nie jest posortowana.\n");
        }
    }

    for (int i=0; i<lenght; i++) {
        printf("%d, ", *(elements+i));
    }
    printf("\n");

    return 0;
}