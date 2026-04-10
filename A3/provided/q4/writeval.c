#include <stdio.h>
#include "writeval.h"
#include <string.h>
void *nextAlignedAddress(void *faddr, size_t size) {
  unsigned long long d = (unsigned long long)faddr; //convert hex to decimal
  while (1){
    if (d%size == 0) break; //check if divible by size, if not increment d until it does
    d = d+1;
  }
  return (void*)d;
}



void *writeValue(void *writeLoc, const char *type, void *payload){
    int tag;
    if (strcmp(type, "int") == 0) tag = 0;
    else if (strcmp(type, "char") == 0) tag = 1;
    else if (strcmp(type, "ptr") == 0) tag = 2;
    else if (strcmp(type, "str") == 0) tag = 3;
    else tag = 4;
    *(char *)writeLoc = (char)tag; //place tag at set memory location
    
    char *current = (char*)writeLoc + 1;
    if (tag == 0){
      current = (char *)nextAlignedAddress(current, sizeof(int)); //cast new location to char for arithmetic
      *(int *)current = *(int *)payload;// add the payload in
      return (void *)(current + sizeof(int));//add the new location
    } 
    if (tag == 1){
        current = (char *)nextAlignedAddress(current, sizeof(char)); //char size is 1 to basically nothing happends, I put it for symmetric purpose for me to understand more clearly
        *(char *)current = *(char *)payload;
        return (void *)(current + sizeof(char));
    }
    if (tag == 2){
        current = (char *)nextAlignedAddress(current, sizeof(void *)); 
        *(void **)current = *(void **)payload;
        return (void *)(current + sizeof(void *));
    }
    if (tag == 3){
      current = (char *)nextAlignedAddress(current, sizeof(char)); //char size is 1 to basically nothing happends
      char *sourceString = (char *)payload;
      strcpy(current, sourceString);//simply copy the string in
      return (void *)(current + strlen(sourceString) + 1);//add string lenth to current, +1 because of null terminator
    }
    if (tag == 4) printf("error");// if there is an error tell the user
    return NULL;
}
void printValues(void *dataStart){
    unsigned char *current = (unsigned char *)dataStart;
    int count = 0;
    while (*current != 0xFF){
        char tag = *current;
        if (tag == 0){
            unsigned char *load = current + 1;
            load = (unsigned char *)nextAlignedAddress(load, sizeof(int));
            printf("Value %d at %p: %d\n", count, current,*(int *)load);
            current = load + sizeof(int);
        }
        else if (tag == 1){
            unsigned char *load = current + 1;
            load = (unsigned char *)nextAlignedAddress(load, sizeof(char));
            printf("Value %d at %p: \'%c\'\n", count, current,*(char *)load);
            current = load + sizeof(char);
        }
        else if (tag == 2){
            unsigned char *load = current + 1;
            load = (unsigned char *)nextAlignedAddress(load, sizeof(void *));
            printf("Value %d at %p: %p\n", count, current,*(void **)load);
            current = load + sizeof(void *);
        }
        else if (tag == 3){
            unsigned char *load = current + 1;
            load = (unsigned char *)nextAlignedAddress(load, sizeof(char));
            printf("Value %d at %p: \"%s\"\n", count, current,(char *)load);//%s print from the pointer
            current = load + strlen((char *)load) + 1; //plus 1 because of null terminator
        }
        ++count;
    }
}