#include <stdio.h>
int main() {
int x;
int y;
int z;
int sum;
sum = 0;
scanf("%d",&x);
y = x%10;
x = x/10;
z = y;
while (x > 0) {
    y = x%10;
    x = x/10;
    if (y*2 >= 10) {
        sum = sum + (2*y - 9);
    } else {
        sum = sum + 2*y;
    }
    y = x%10;
    x = x/10;
    sum = sum + y;
    }
if ((sum*9)%10 == z) {
    printf("Valid\n");
} 
else {
    printf("Invalid\n");
}
}
