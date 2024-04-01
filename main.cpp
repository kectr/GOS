#include "stdio.h"
// #include "lib/Window/window.h"

int main(){
   int x = 5,y=10;
   x +=y;
   y = x-y;
   x -=y;
   printf("%d%d",x,y);

}