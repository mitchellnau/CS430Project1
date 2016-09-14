/* Project 1 *
 * Mitchell Hewitt*/

#include <stdio.h>
#include <stdlib.h>

void read_p3();
void write_p3();

void read_p6();
void write_p6();

int main(int argc, char* argv[]){
  printf("Args: %d\n", argc);
  printf("Args: %s\n", argv[0]);
  printf("Args: %s\n", argv[1]);
  printf("Args: %s\n", argv[2]);
  printf("Args: %s\n", argv[3]);

  if(argc < 4)
    fprintf(stderr, "Insufficient parameter amount.\nProper input: input_filename output_filename\n\n", 001);
  if(argc > 4)
    fprintf(stderr, "Too many parameters.\nProper input: input_filename output_filename\n\n", 002);
  if(argc == 4){
    printf("Good job.");
  }
  return(0);
};
