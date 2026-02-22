#include <stdio.h>
#include <stdlib.h>
char* increaseCap(char *s, unsigned int *capacity) {  //function that doubles the array storage
    unsigned int newCap = (*capacity) * 2;  //the size of the new array
    char *newArr = malloc(newCap); //the creation of the new array
    for (unsigned int i = 0; i < *capacity; i++) { //copying the element of the old array to the new one
        newArr[i] = s[i];
    }
    free(s); //free array to avoid mem leak
    *capacity = newCap; //update the capacity indicator from caps[]
    return newArr;
}
void read(char **s, unsigned int *size, unsigned int *capacity){
    *size = 0; //inputing completly new string so reset the size
    char x; //garbage variable, to grab input
    while ((x = getchar()) != EOF && (x == ' ' || x == '\n' || x == '\t'));  //make sure we get ride of space char between var and the string
    int quote = 0;
    if (x == '"'){
        quote = 1;  //signaling quote mode
        x = getchar();
    }
    while (x != EOF){      //loop until eof
        if (quote){ 
            if (x == '"') {   //this will prevent checking for space char
                break;
            }}
        else{
            if (x == ' ' || x == '\n' || x == '\t' ) { //if space char, stop loop
                break;
            }
        }
        if (*size == *capacity-1) {    // if arrat full, double capacity
            *s = increaseCap(*s, capacity);
            }
        (*s)[(*size)++] = x;  //put nth char in nth location in array
        x = getchar();   //get next char
        }
        (*s)[*size] = '\0'; //end of string
}
void append(char **s, unsigned int *size, unsigned int *capacity){ // code is the same except we arent resetting the size
    // notice we did not reset the size, simply increment size by one will be we appending values into *s
    char x; //garbage variable, to grab input
    while ((x = getchar()) != EOF && (x == ' ' || x == '\n' || x == '\t'));  //make sure we get ride of space char between var and the string
    int quote = 0;
    if (x == '"'){
        quote = 1;  //signaling quote mode
        x = getchar();
    }
    while (x != EOF){      //loop until eof
        if (quote){ 
            if (x == '"') {   //this will prevent checking for space char
                break;
            }}
        else{
            if (x == ' ' || x == '\n' || x == '\t' ) { //if space char, stop loop
                break;
            }
        }
        if (*size == *capacity-1) {    // if arrat full, double capacity
            *s = increaseCap(*s, capacity);
            }
        (*s)[(*size)++] = x;  //put nth char in nth location in array
        x = getchar();   //get next char
        }
        (*s)[*size] = '\0'; //end of string
}
void concadenate(char **t1, unsigned int *size1, unsigned int *cap1, char *t2, unsigned int size2, char *t3, unsigned int size3){
    *size1 = 0; // resetting var
    (*t1)[0] = '\0'; //this time we put null teminator because we are going to simply add using for loops
    while (*cap1 <= size2 + size3 + 1) { //making sure our array size of t1 is big enough for the process
        *t1 = increaseCap(*t1, cap1);
    }
    for (unsigned int i = 0; i < size2; i++) { //adding *t2 into *t1
        (*t1)[(*size1)++] = t2[i];
    }
    for (unsigned int i = 0; i < size3; i++) {//adding *t3 into *t1
        (*t1)[(*size1)++] = t3[i];
    }
    (*t1)[*size1] = '\0';//end of string
}
int main(int argc, char const *argv[]){
    char *a = malloc(4); //setting up array for the variables
    char *b = malloc(4);
    char *c = malloc(4);
    char *d = malloc(4);
    char *var[4] = {a,b,c,d}; // putting the variable in array (will make things cleaner seen below)
    unsigned int sizes[4] = {0,0,0,0}; //since the array size will be updating, we need to keep note on its size and max capacity
    unsigned int caps[4] = {4,4,4,4};
    char x; //garbage variable to put input in
    char y; // x and y are only used for the concadenate step
    char z;
    while (scanf(" %c", &x) != EOF) { //the space before %c in scanf indicate skiping whitespace before it, this function will loop until EOF
        if (x == 'q'){ // if the char is q, end the loop
            break;
        }
        else if (x == 'r'){ // if r is receive, trigger the read step
            scanf(" %c",&x); //the space before %c in scanf indicate skiping whitespace before it, check what variable it will use
            if ( x >= 'a' && x <= 'd' ) read(&var[x-'a'],&sizes[x-'a'], &caps[x-'a']); // check if variable is a-d, since we have those variable in the array var, we can use x-'a' for the variable we need along with is recorded size stored in sizes and caps array
            else printf("Invalid SString target %c\n", x);// if not a-d, tell the use its invalid
        }
        else if (x == 'p'){ // if p is receive, trigger the print step
            scanf(" %c",&x);//like in read, check what variable we will print
            if ( x >= 'a' && x <= 'd' ) printf("%s\n", var[x-'a']);// like in read, we check if variable is valid and simply print its contents
            else printf("Invalid SString target %c\n", x);//if not a-d signal the user that its invalid
        }
        else if (x == 'a') {// if a is receive, trigger the append step
           scanf(" %c",&x);
            if ( x >= 'a' && x <= 'd' ) append(&var[x-'a'],&sizes[x-'a'], &caps[x-'a']);
           else printf("Invalid SString target %c\n", x);//if not a-d signal the user that its invalid
        }
        else if (x == 'c') { // concadenate step
            scanf(" %c", &x); // we need to check three variables now
            scanf(" %c", &y);
            scanf(" %c", &z);
            if ( x < 'a' && x > 'd' ) printf("Invalid SString target %c\n", x); // checking if var in x, y, z are valid
            else if ( y < 'a' && y > 'd' ) printf("Invalid SString target %c\n", y);
            else if ( z < 'a' && z > 'd' ) printf("Invalid SString target %c\n", z);
            else concadenate(&var[x-'a'], &sizes[x-'a'], &caps[x-'a'], var[y-'a'], sizes[y-'a'], var[z-'a'], sizes[z-'a']);//little to many variable imo lmao
        }
    
}
free(var[0]);// since we use malloc, we must free the memory of variable to prevent memory leak
free(var[1]);//to note, we did not do for example free(a) because it will be invalid since "a" is
free(var[2]);//the inital array which is no longer in use when we increase its size
free(var[3]);
}