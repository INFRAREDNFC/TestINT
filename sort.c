#include <stdio.h>
#include <stddef.h>

static void bubble_sort(int *array, size_t n)
{
    size_t i;
    size_t j;
    int temp;

    if (array == NULL) {
        return;
    }

    for (i = 0U; i < n; i++) {
        for (j = 0U; j + 1U < n - i; j++) {
            if (array[j] > array[j + 1U]) {
                temp = array[j];
                array[j] = array[j + 1U];
                array[j + 1U] = temp;
            }
        }
    }
}

static void print_array(const char *label, const int *array, size_t n)
{
    size_t i;

    if ((label == NULL) || (array == NULL)) {
        return;
    }

    printf("%s", label);

    for (i = 0U; i < n; i++) {
        printf("%d", array[i]);

        if (i + 1U < n) {
            printf(" ");
        }
    }

    printf("\n");
}

int main(void)
{
    int numbers[] = {9, 4, 1, 7, 3, 8, 2, 6, 5};
    size_t n = sizeof(numbers) / sizeof(numbers[0]);

    print_array("Przed sortowaniem: ", numbers, n);
    bubble_sort(numbers, n);
    print_array("Po sortowaniu: ", numbers, n);

    return 0;
}
