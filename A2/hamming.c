#include <stdio.h>
#include <stdlib.h>
int hammingbase(int num1, int num2, int base){
    int hamming = 0;
    while (num1 != 0 || num2 != 0){
    if ((num1%base) != (num2%base)){
        ++hamming;
    }
    num1 = num1/base;
    num2 = num2/base;
    }
    return hamming;
}
int main(int argc, char **argv) {
    if (argc != 4){
        printf("Usage: ./hamming n1 n2 base\n");
    }
    else{
    int num1 = atoi(argv[1]);
    int num2 = atoi(argv[2]);
    int base = atoi(argv[3]);
    printf("%d\n",hammingbase(num1,num2,base));
}
}