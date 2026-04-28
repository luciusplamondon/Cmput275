#include <iostream>
#include <iomanip>

using namespace std;


int adder(int *arr, int size){
    int num =0;
    for (int i = 0; i < size; ++i){
        num = num + arr[i];
    }
    return num;
}
int max(int *arr, int size){
    int max = arr[0];
    for (int i = 0; i < size; ++i){
        if (max < arr[i]) max = arr[i];
    }
    return max;
}
float max(float *arr, int size){
    float max = arr[0];
    for (int i = 0; i < size; ++i){
        if (max < arr[i]) max = arr[i];
    }
    return max;
}

int main() {
    int size = 5;
    int arr[] = {1, 2, 3, 4, 5};
    float arr2[] = {1.1, 2.2, 3.3, 4.4, 5.5};
    cout << adder(arr, size) << endl;
    cout << max(arr, size) << endl;
    cout << max(arr2, size) << endl;
}