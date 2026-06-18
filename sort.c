#include <stdio.h>
#include <stddef.h>

void bubble_sort(int *array, size_t n) {
    for (size_t i = 0; i < n; i++) {
        for (size_t j = 0; j + 1 < n - i; j++) {
            if (array[j] > array[j + 1]) {
                int temp = array[j];
                array[j] = array[j + 1];
                array[j + 1] = temp;
            }
        }
    }
}

void print_array(const char *label, const int *array, size_t n) {
    printf("%s", label);
    for (size_t i = 0; i < n; i++) {
        printf("%d", array[i]);
        if (i + 1 < n) {
            printf(" ");
        }
    }
    printf("\n");
}

int main(void) {
    int numbers[] = {9, 4, 1, 7, 3, 8, 2, 6, 5};
    size_t n = sizeof(numbers) / sizeof(numbers[0]);

    print_array("Przed sortowaniem: ", numbers, n);
    bubble_sort(numbers, n);
    print_array("Po sortowaniu:    ", numbers, n);

    return 0;
}
