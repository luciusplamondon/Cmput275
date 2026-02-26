#include <stdio.h>
#include <stdlib.h>

struct pixel{
    int r, g, b;
};

void print(struct pixel **pic, int width, int height){
    printf("P3\n%d %d\n255\n", width, height);
    for (int i = 0; i < height; i++){
        for (int j = 0; j < width; j++){
            printf("%d %d %d ", pic[i][j].r, pic[i][j].g, pic[i][j].b);
        }
        printf("\n");
    }
}
void flip(struct pixel **pic, int width, int height) {
    struct pixel **copy = malloc(height * sizeof *copy);
    for (int i = 0; i < height; i++) {
        copy[i] = malloc(width * sizeof *copy[i]);
        for (int j = 0; j < width; j++) {
            copy[i][j] = pic[i][j];
        }
    }
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            pic[i][j] = copy[i][width - 1 - j];
        }
    }
    for (int i = 0; i < height; i++) {
        free(copy[i]);
    }
    free(copy);
}
void sepia(struct pixel **pic, int width, int height) {
    struct pixel **copy = malloc(height * sizeof *copy);
    for (int i = 0; i < height; i++) {
        copy[i] = malloc(width * sizeof *copy[i]);
        for (int j = 0; j < width; j++) {
            copy[i][j] = pic[i][j];
        }
    }
    int newR = 0;
    int newG = 0;
    int newB = 0;
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            newR = (copy[i][j].r*0.393 + copy[i][j].g*0.769 + copy[i][j].b*0.189);
            newG = (copy[i][j].r*0.349 + copy[i][j].g*0.686 + copy[i][j].b*0.168);
            newB = (copy[i][j].r*0.272 + copy[i][j].g*0.534 + copy[i][j].b*0.131);
            if (newR > 255) newR = 255;
            if (newG > 255) newG = 255;
            if (newB > 255) newB = 255;
            pic[i][j].r = newR;
            pic[i][j].g = newG;
            pic[i][j].b = newB;
        }
    }
    for (int i = 0; i < height; i++) {
        free(copy[i]);
    }
    free(copy);
}

int main(int argc, char const *argv[]){
    struct pixel **pic;
    int f = 0;
    int s = 0;
    for (int i = 1; i < argc; i++) {
        if (argv[i][0] == '-' && argv[i][1] == 'f' && argv[i][2] == '\0') {
            f = 1;
        }
        else if (argv[i][0] == '-' && argv[i][1] == 's' && argv[i][2] == '\0') {
            s = 1;
        }
    }
    int width = 0;
    int height = 0;
    char garbage;
    int garbageint;
    scanf("%c%c", &garbage,&garbage);
    scanf("%d %d",&width, &height);
    scanf("%d", &garbageint);
    pic = malloc(height*sizeof(*pic));
    for (int i = 0; i < height; i++){
        pic[i] = malloc(width *sizeof(*pic[i]));
        for (int j = 0;j < width; j++){
            scanf("%d %d %d", &pic[i][j].r,&pic[i][j].g, &pic[i][j].b);
        }
    }

    if (f) flip(pic, width, height);

    if (s) sepia(pic, width, height);

    print(pic, width, height);
    for (int i = 0; i < height; i++) {
        free(pic[i]);
    free(pic);
}
}
