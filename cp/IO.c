#include <stdio.h>

int main(int argc, char const *argv[])
{
char x;
x = getchar();
while (x == ' '  || x == '\n'){
    x = getchar();
}
int str = 0;
if (x == '"') {
    str = 1;
    x = getchar();
}
while (x != EOF) {
    if (str && x == '"') break;
    else if (str) printf("%c",x);
    else if (x == ' ' || x == '\n') break;
    else printf("%c",x);
    x = getchar();
}
printf("\n");
}