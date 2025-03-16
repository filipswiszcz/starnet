#include <stdlib.h>

typedef struct farray farray;

struct farray {
    float *numbers;
    size_t k;
    size_t capacity;
};

void addnum(farray *arr, float *num) {
    do {
        if (arr -> k >= arr -> capacity) {
            if (arr -> capacity == 0) arr -> capacity = 64;
            else arr -> capacity *= 2;
            arr -> numbers = (float*) realloc(arr -> numbers, arr -> capacity * sizeof(*arr -> numbers));
        }
        arr -> numbers[arr -> k++] = *num;
    } while (0);
}