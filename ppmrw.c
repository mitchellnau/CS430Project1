/* Project 1 *
 * Mitchell Hewitt*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//data type to store pixel rgb values
typedef struct Pixel {
  unsigned char r, g, b;
} Pixel;


FILE* inputfp;
FILE* outputfp;
int width, height, maxcv; //global variables to store header information

//This function reads the header data of the input file and stores the crucial parts into global variables for future use
int read_header(char input){ //take in the p type (3 or 6) as a char
  int i, line, endOfHeader, x;
  char a, b;
  char widthB[32], heightB[32], maxcvB[32]; //buffers to temporarily store the width, height, and max color value
  char comment[64];                         //buffer to store the comment

  a = fgetc(inputfp); //get the first two chars of the file (P#)
  b = fgetc(inputfp);
  if(a != 'P' || b != input){  //check to see if the input number matches the function input and if the P is there
    fprintf(stderr, "Error: Improper header filetype.\n", 005);
    exit(1);                   //exit if the header is incorrect
  }
  a = fgetc(inputfp); //move past newline

  a = fgetc(inputfp); //get the comment # OR the first digit of the width
  if(a == '#'){       //if there is a comment, move past it
    while(a != '\n'){ //move past comment with this loop
        a = fgetc(inputfp);
    }
    a = fgetc(inputfp); //get the first digit of the width if there was a comment
  }


  i = 0;
  while(a != ' '){ //get the rest of the width
    widthB[i] = a; //store it in a buffer
    a = fgetc(inputfp);
    i++;
  }
  width = atoi(widthB); //convert the buffer to an integer and store it


  a = fgetc(inputfp);  //get the first char of the height
  i = 0;
  while(a != '\n'){    //get the rest of the height
    heightB[i] = a;    //store it in a buffer
    a = fgetc(inputfp);
    i++;
  }
  height = atoi(heightB); //convert the buffer to an integer and store it

  a = fgetc(inputfp);  //get the first char of the max color value
  i = 0;
  while(a != '\n'){    //get the rest of the max color value
    maxcvB[i] = a;     //store it in a buffer
    a = fgetc(inputfp);
    i++;
  }
  maxcv = atoi(maxcvB); //convert the buffer to an integer and store it

  return 1;
}

//This function reads p3 data from an input file and stores it in dynamically allocated memory, a pointer to which is passed into the function.
int read_p3(Pixel* image){
  int i;
  unsigned char check;
  char number[5];
  for(i=0; i < width*height ; i++){ //for as many pixels in the image
    Pixel temp;         //create a temporary pixel struct

    fgets(number, 10, inputfp); //get the red value
    check = atoi(number);       //store it in an intermediate variable
    if(check > maxcv){          //check to see if the color value is compliant with the max color value
      fprintf(stderr, "Error: Color value exceeds limit.\n", 006);
      exit(1);                  //exit the program if the image's pixels don't comply with the max color value
    }
    temp.r = check;             //store it in the temporary pixel

    fgets(number, 10, inputfp); //get the green value
    check = atoi(number);       //store it in an intermediate variable
    if(check > maxcv){          //check to see if the color value is compliant with the max color value
      fprintf(stderr, "Error: Color value exceeds limit.\n", 006);
      exit(1);                  //exit the program if the image's pixels don't comply with the max color value
    }
    temp.g = check;             //store it in the temporary pixel

    fgets(number, 10, inputfp); //get the blue value
    check = atoi(number);       //store it in an intermediate variable
    if(check > maxcv){          //check to see if the color value is compliant with the max color value
      fprintf(stderr, "Error: Color value exceeds limit.\n", 006);
      exit(1);                  //exit the program if the image's pixels don't comply with the max color value
    }
    temp.b = check;             //store it in the temporary pixel
    *(image+i*sizeof(Pixel)) = temp; //store the temporary pixel in the dynamically allocated memory
  }
  return 1;
}

//This function writes data from the pixel buffer passed into the function to the output file in ascii.
int write_p3(Pixel* image){
  fprintf(outputfp, "%c%c\n", 'P', '3'); //write out the file header P type
  fprintf(outputfp, "%d %d\n", width, height); //write the width and the height
  fprintf(outputfp, "%d\n", maxcv); //write the max color value
  int i;
  for(i = 0; i < width*height; i++){ //write each pixel in the image to the output file
    fprintf(outputfp, "%d\n%d\n%d\n", image[i*sizeof(Pixel)].r, //in ascii
                                      image[i*sizeof(Pixel)].g,
                                      image[i*sizeof(Pixel)].b);
  }
  return 1;
};

int read_p6(Pixel* image){
  int i, c;
  char number[8];
  for(i=0; i < width*height ; i++){
    Pixel temp;

    c = fgetc(inputfp);     //get the red value
    if(c > maxcv){          //check to see if the color value is compliant with the max color value
      fprintf(stderr, "Error: Color value exceeds limit.\n", 006);
      exit(1);              //exit the program if the image's pixels don't comply with the max color value
    }
    temp.r = c;             //store it in the temporary pixel

    c = fgetc(inputfp);     //get the green value
    if(c > maxcv){          //check to see if the color value is compliant with the max color value
      fprintf(stderr, "Error: Color value exceeds limit.\n", 006);
      exit(1);              //exit the program if the image's pixels don't comply with the max color value
    }
    temp.g = c;             //store it in the temporary pixel

    c = fgetc(inputfp);     //get the blue value
    if(c > maxcv){          //check to see if the color value is compliant with the max color value
      fprintf(stderr, "Error: Color value exceeds limit.\n", 006);
      exit(1);              //exit the program if the image's pixels don't comply with the max color value
    }
    temp.b = c;             //store it in the temporary pixel

    *(image+i*sizeof(Pixel)) = temp; //store the temporary pixel in the dynamically allocated memory
  }

  return 1;
};

int write_p6(Pixel* image){
  fprintf(outputfp, "%c%c\n", 'P', '6'); //write out the file header P type
  fprintf(outputfp, "%d %d\n", width, height); //write the width and the height
  fprintf(outputfp, "%d\n", maxcv); //write the max color value
  int i;
  char number[4];
  for(i = 0; i < width*height; i++){ //write each pixel in the image to the output file
    fputc((*(image+i*sizeof(Pixel))).r, outputfp); //in binary using putc to place bytes
    fputc((*(image+i*sizeof(Pixel))).g, outputfp);
    fputc((*(image+i*sizeof(Pixel))).b, outputfp);
  }
  return 1;
};





int main(int argc, char* argv[]){
  if(argc < 4){
    fprintf(stderr, "Error: Insufficient parameter amount.\nProper input: number input_filename output_filename\n\n", 001);
    exit(1); //exit the program if there are insufficient arguments
  }

                                 //echo the command line arguments
  printf("Args: %s\n", argv[0]);
  printf("Args: %s\n", argv[1]);
  printf("Args: %s\n", argv[2]);
  printf("Args: %s\n", argv[3]);

  if(argc > 4){
    fprintf(stderr, "Error: Too many parameters.\nProper input: input_filename output_filename\n\n", 002);
    exit(1); //exit the program if there are too many parameters
  }

  if(argc == 4){
    if (argv[1][0] == '3' || argv[1][0] == '6'){ //check to see if the input number was one of the required numbers
      if(argv[1][0] == '3'){
        inputfp = fopen(argv[2], "r"); //open input to read
        if (inputfp == 0){
          fprintf(stderr, "Error: Input file \"%s\" could not be opened.\n", argv[2], 003);
          exit(1); //if the file cannot be opened, exit the program
        }
        outputfp = fopen(argv[3], "wb"); //open output to write to binary
        if (outputfp == 0){
          fprintf(stderr, "Error: Output file \"%s\" could not be opened.\n", argv[3], 004);
          exit(1); //if the file cannot be opened, exit the program
        }
        read_header('3'); //read the header of a P3 file
        Pixel* data = malloc(sizeof(Pixel)*width*height*3); //allocate memory to hold all of the pixel data
        read_p3(&data[0]);
        write_p6(&data[0]);
      }
      else{
        inputfp = fopen(argv[2], "rb"); //open the input to read from binary
        if (inputfp == 0){
          fprintf(stderr, "Error: Input file \"%s\" could not be opened.\n", argv[2], 003);
          exit(1); //if the file cannot be opened, exit the program
        }
        outputfp = fopen(argv[3], "w"); //open the output to write
        if (outputfp == 0){
          fprintf(stderr, "Error: Output file \"%s\" could not be opened.\n", argv[3], 004);
          exit(1); //if the file cannot be opened, exit the program
        }
        read_header('6'); //read the header of a P6 file
        Pixel* data = malloc(sizeof(Pixel)*width*height*3); //allocate memory to hold all of the pixel data
        read_p6(&data[0]);
        write_p3(&data[0]);
      }
    }
    else {
      fprintf(stderr, "Error: Input number \"%s\" is not 3 or 6.\n", argv[1], 005);
      exit(1); //exit the program if the specified P type is incorrect
    }

    fclose(outputfp); //close the output file
    fclose(inputfp);  //close the input file
    }

  printf("closing...");
  return(0);
}
