#include <stdio.h>
#include <string.h>
void *nextAlignedAddress(void *faddr, size_t size) {
  unsigned long long d = (unsigned long long)faddr; //convert hex to decimal
  printf("%llu\n",d);
  while (1){
    if (d%size == 0) break; //check if divible by size, if not increment d until it does
    d = d+1;
  }
  printf("%llu\n",d);
  return (void*)d;
}


int main() {
  void *p;
  if (1 != scanf("%llx", (long long unsigned int *) &p)) {
    printf("Failed to read a hexadecimal number for the pointer!");
    return 1;
  }
  size_t size;
  if (1 != scanf("%lu", &size)) {
    printf("Failed to read an unsigned number for the size!");
    return 1;
  }
  printf("Start of free memory address is: %p\n", p);
  printf("So next %lu size aligned address is: %p\n", size, nextAlignedAddress(p, size));
}
