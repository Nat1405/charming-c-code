/* A program utlizing command line io in c. */
/* based of an example found at http://crasseux.com/books/ctutorial/argc-and-argv.html*/
#define EXIT_SUCCESS 0
#include<stdio.h>


int print_args(int argc, char *argv[]){
  printf("Printing command line arguments.\nargc = %d.\n", argc);
  int count;
  if (argc > 1){
    for (count = 0; count < argc; count++){
      printf("argv[%d] = %s\n", count, argv[count]);
    }
  }
  else {
    printf("No further arguments.\n");
  }
  return 0;
}



int main(int argc, char *argv[]){
  printf("Hi there! I have recieved %d command line args.\n", argc);
  print_args(argc, argv);
  return EXIT_SUCCESS;
}
