/* A program utlizing command line io in c. */
#define EXIT_SUCCESS 0
#include<stdio.h>

int main(int argc, char *argv[]){
  printf("Hi there! I have recieved %d command line args.\n", argc);
  return EXIT_SUCCESS;
}
