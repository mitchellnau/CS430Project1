/* Project 1 *
 * Mitchell Hewitt*/

#include <stdio.h>
#include <stdlib.h>


FILE* inputfp;
FILE* outputfp;

void read_p3(){
  printf("Args: %d\n", inputfp);
  char* str;
  char* data;
  int i, line, endOfHeader, x;
  char a, b;


  a = fgetc(inputfp);
  b = fgetc(inputfp);
  data[0] = a;
  data[1] = b;
  if(a != 'P' || b !='3'){
    fprintf(stderr, "Error: Improper header filetype.\n", 005);
  }
  a = fgetc(inputfp);
  data[2] = a;
  i = 3;
  line = 2;
  a = fgetc(inputfp);

  while(line < 5){
    data[i] = a;
    a = fgetc(inputfp);
    //printf("%c", a);
    i++;
    if (a == '\n')
      line++;
  }
  data[i] = a;

  endOfHeader = i;



  printf("\nBuffer:\n%s-------------\n", data);
  for(i=0; !feof(inputfp) ; i++){
    a = fgetc(inputfp);
    printf("%c", a);
//    x = atoi(str);
//    if(x > 255){
//      fprintf(stderr, "Error: Color value exceeds maximum specified in header.\n", 006);
//      break;
//    }
//    printf("%5dth nmbr: %d\n", i, x);
  }

}


void write_p3();

void read_p6();
void write_p6();





int main(int argc, char* argv[]){
  printf("Args: %s\n", argv[0]);
  printf("Args: %s\n", argv[1]);
  printf("Args: %s\n", argv[2]);
  printf("Args: %s\n\n\n", argv[3]);

  if(argc < 4)
    fprintf(stderr, "Error: Insufficient parameter amount.\nProper input: input_filename output_filename\n\n", 001);

  if(argc > 4)
    fprintf(stderr, "Error: Too many parameters.\nProper input: input_filename output_filename\n\n", 002);

  if(argc == 4){
    inputfp = fopen(argv[2], "r");
    outputfp = fopen(argv[3], "w");
    if (inputfp == 0)
      fprintf(stderr, "Error: Input file \"%s\" could not be opened.\n", argv[2], 003);
    if (outputfp == 0)
      fprintf(stderr, "Error: Output file \"%s\" could not be opened.\n", 004, argv[3]);

    read_p3();


    fclose(inputfp);
    fclose(outputfp);
  }
  printf("closing...");
  return(0);
};
