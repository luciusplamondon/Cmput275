#include <stdio.h>

void printFractionalBinary(float num, float e) {
    float approx = 0.0;
    float place = 0.5;   // 2^-1
    float diff;
    printf("0.");

    while (1) {
        if (approx > num) diff = approx - num;
        else diff = num - approx;
        if (diff < e)
            break;
        if (approx + place <= num) {
            printf("1");
            approx += place;
        } else {
            printf("0");
        }

        place *= 0.5;   // next bit (2^-2, 2^-3, ...)
    }

    printf("\n");
}

int main(int argc, char const *argv[])
{
    printFractionalBinary(0.43,0.001);
}
