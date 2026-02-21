#include <stdio.h>

int main(int argc, char **argv) {
  int x = 10;
  int arr[5] = {0,1,2,3,4};
  for (int i; i < 5; ++i){
  printf("%d\n",arr[i]);
  }
  for (int i; i<5; ++i){
   arr[i] = arr[i]*2;
  }
  for (int i; i < 5; ++i){
  printf("%d\n",arr[i]);
}
}