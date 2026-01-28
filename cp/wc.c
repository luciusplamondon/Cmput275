#include <stdio.h>

int isws(char c) {
    return (c == '\n' || c == ' ' || c == '\t' || c == '\r');
}


int main() {
    int cc = 0; //char count
    int wc = 0; // word count
    int lc = 0; // line count
    char c = 0;
    char prevChar = ' ';
    while ((c = getchar()) != EOF) {
        ++cc;
        if (c == '\n') ++lc;
        if (isws(prevChar) && !isws(c)) ++wc;
        prevChar = c;
}
printf("\t%d\t%d\t%d\n", lc, wc, cc );
}
