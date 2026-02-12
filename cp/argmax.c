#include <stdio.h>

int argmax(int arr[], unsigned int size) {
    int x = *arr;
    while (size > 0) {
        if (x < *arr) {
            x = *arr;
        }
        size = size - 1;
        ++arr;
    };
    return x;
    }

int main() {
    int arr1[5] = {1,7,3,4,5};
    int arr2[] = {-10,-8,-2,-3,-5,-2};
    printf("%d\n",argmax(arr1,5));
    printf("%d\n",argmax(arr2,6));
}
