#include <stdio.h>
#include <stdlib.h>
unsigned int hammingbase(unsigned int num1, unsigned int num2, unsigned int base){
    unsigned int hamming = 0;
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
    unsigned int num1 = atoi(argv[1]);
    unsigned int num2 = atoi(argv[2]);
    unsigned int base = atoi(argv[3]);
    printf("%d\n",hammingbase(num1,num2,base));
}
}