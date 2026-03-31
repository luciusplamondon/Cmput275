#include <stdio.h>
#include <stdlib.h>

struct stuff{
    int x, y, z;
};

void mutate(struct stuff *p){
    p->x +=2;
    p->y +=3;
}

void mutatebad(struct stuff p){
    p.x +=2;
    p.y +=3;
}
int main(int argc, char const *argv[])
{
    struct stuff r;
    r.x = 1;
    r.y = 3;
    printf("x %d, y %d\n", r.x, r.y);
    mutate(&r);
    printf("x %d, y %d\n", r.x, r.y);
    mutatebad(r);
    printf("x %d, y %d\n", r.x, r.y);
}
