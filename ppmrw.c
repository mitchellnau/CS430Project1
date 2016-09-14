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
  printf("Args: %s\n\n\n", argv[3]);

  if(argc < 4)
    fprintf(stderr, "Error: Insufficient parameter amount.\nProper input: input_filename output_filename\n\n", 001);

  if(argc > 4)
    fprintf(stderr, "Error: Too many parameters.\nProper input: input_filename output_filename\n\n", 002);

  if(argc == 4){
    FILE * inputfp;
    FILE * outputfp;
    inputfp = fopen(argv[2], "r");
    outputfp = fopen(argv[3], "w");
    if (inputfp == 0)
      fprintf(stderr, "Error: Input file \"%s\" could not be opened.\n", argv[2], 003);
    if (outputfp == 0)
      fprintf(stderr, "Error: Output file \"%s\" could not be opened.\n", 004, argv[3]);




    fclose(inputfp);
    fclose(outputfp);
  }
  printf("closing...");
  return(0);
};
