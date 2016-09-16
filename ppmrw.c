/* Project 1 *
 * Mitchell Hewitt*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Pixel {
  unsigned char r, g, b;
} Pixel;


FILE* inputfp;
FILE* outputfp;
char header[64];
Pixel* image;
int width, height, maxcv;

int write_p3();
int write_p6();
int read_p6();

int read_p3(){
  //printf("Fd: %d\n", inputfp);
  int i, line, endOfHeader, x;
  char a, b;
  char number[4];
  char widthB[32], heightB[32], maxcvB[32];
  char comment[64];

  a = fgetc(inputfp);
  b = fgetc(inputfp);
  header[0] = a;
  header[1] = b;
  if(a != 'P' || b !='3'){
    fprintf(stderr, "Error: Improper header filetype.\n", 006);
    return 0;
  }

  a = fgetc(inputfp);
  header[2] = a;

  a = fgetc(inputfp);
  if(a == '#'){
    while(a != '\n'){
        a = fgetc(inputfp);
    }
  }

  a = fgetc(inputfp);
  i = 0;
  while(a != ' '){
    widthB[i] = a;
    a = fgetc(inputfp);
    i++;
  }
  width = atoi(widthB);
  widthB[i] = a;
  widthB[i+1] = '\0';
  //printf("width: %d\n", width);


  a = fgetc(inputfp);
  i = 0;
  while(a != '\n'){
    heightB[i] = a;
    a = fgetc(inputfp);
    i++;
  }
  height = atoi(heightB);
  heightB[i] = a;
  heightB[i+1] = '\0';
  //printf("height: %d\n", height);

  a = fgetc(inputfp);
  i = 0;
  while(a != '\n'){
    maxcvB[i] = a;
    a = fgetc(inputfp);
    i++;
  }
  maxcv = atoi(maxcvB);
  maxcvB[i] = a;
  maxcvB[i+1] = '\0';
  //printf("maxcv: %d\n", maxcv);

  strcat(header, widthB);
  strcat(header, heightB);
  strcat(header, maxcvB);

  //printf("%s\n", header);

  image = malloc(sizeof(Pixel)*width*height);
  for(i=0; i < width*height ; i++){
    //a = fgetc(inputfp);
    Pixel temp;

    fgets(number, 5, inputfp);
    temp.r = atoi(number);
    fgets(number, 5, inputfp);
    temp.g = atoi(number);
    fgets(number, 5, inputfp);
    temp.b = atoi(number);
    //printf("%3d: %d %d %d\n", i, temp.r, temp.g, temp.b);

    image[i*sizeof(Pixel)] = temp;
  }
  return 1;
}


int write_p3(){
  header[1] = '3';
  fprintf(outputfp, "%s", header);
  int i;
  //char number[4];
  for(i = 0; i < width*height; i++){
    printf("%3d: %d %d %d\n", i, image[i*sizeof(Pixel)].r,
                                              image[i*sizeof(Pixel)].g,
                                              image[i*sizeof(Pixel)].b);
    /*sprintf(number, "%d\n", image[i*sizeof(Pixel)].r);
    fputs(number, outputfp);
    sprintf(number, "%d\n", image[i*sizeof(Pixel)].g);
    fputs(number, outputfp);
    sprintf(number, "%d\n", image[i*sizeof(Pixel)].b);
    fputs(number, outputfp);*/
  }
  return 1;
};

int read_p6(){
  //printf("Fd: %d\n", inputfp);
  int i, line, endOfHeader, x;
  char a, b;
  char number[8];
  char widthB[32], heightB[32], maxcvB[32];
  char comment[64];

  a = fgetc(inputfp);
  b = fgetc(inputfp);
  header[0] = a;
  header[1] = b;
  if(a != 'P' || b !='6'){
    fprintf(stderr, "Error: Improper header filetype.\n", 006);
    return 0;
  }

  a = fgetc(inputfp);
  header[2] = a;

  a = fgetc(inputfp);
  if(a == '#'){
    while(a != '\n'){
        a = fgetc(inputfp);
    }
  }

  a = fgetc(inputfp);
  i = 0;
  while(a != ' '){
    widthB[i] = a;
    a = fgetc(inputfp);
    i++;
  }
  width = atoi(widthB);
  widthB[i] = a;
  widthB[i+1] = '\0';
  //printf("width: %d\n", width);


  a = fgetc(inputfp);
  i = 0;
  while(a != '\n'){
    heightB[i] = a;
    a = fgetc(inputfp);
    i++;
  }
  height = atoi(heightB);
  heightB[i] = a;
  heightB[i+1] = '\0';
  //printf("height: %d\n", height);

  a = fgetc(inputfp);
  i = 0;
  while(a != '\n'){
    maxcvB[i] = a;
    a = fgetc(inputfp);
    i++;
  }
  maxcv = atoi(maxcvB);
  maxcvB[i] = a;
  maxcvB[i+1] = '\0';
  //printf("maxcv: %d\n", maxcv);

  strcat(header, widthB);
  strcat(header, heightB);
  strcat(header, maxcvB);

  int c;
  image = malloc(sizeof(Pixel)*width*height);
  for(i=0; i < width*height ; i++){
    Pixel temp;
    c = fgetc(inputfp);
    temp.r = c;
    c = fgetc(inputfp);
    temp.g = c;
    c = fgetc(inputfp);
    temp.b = c;
    //printf("%3d: %d %d %d\n", i, temp.r, temp.g, temp.b);

    image[i*sizeof(Pixel)] = temp;
  }

  return 1;
};

int write_p6(){
  return 1;

};





int main(int argc, char* argv[]){
  printf("Args: %s\n", argv[0]);
  printf("Args: %s\n", argv[1]);
  printf("Args: %s\n", argv[2]);
  printf("Args: %s\n", argv[3]);

  if(argc < 4)
    fprintf(stderr, "Error: Insufficient parameter amount.\nProper input: input_filename output_filename\n\n", 001);

  if(argc > 4)
    fprintf(stderr, "Error: Too many parameters.\nProper input: input_filename output_filename\n\n", 002);

  if(argc == 4){
    if (argv[1][0] == '3' || argv[1][0] == '6'){
      if(argv[1][0] == '3'){
        inputfp = fopen(argv[2], "r");
        if (inputfp == 0){
          fprintf(stderr, "Error: Input file \"%s\" could not be opened.\n", argv[2], 003);
          exit(1);
        }
        outputfp = fopen(argv[3], "w+");
        if (outputfp == 0){
          fprintf(stderr, "Error: Output file \"%s\" could not be opened.\n", argv[3], 004);
          exit(1);
        }
        read_p3();
        write_p6();
      }
      else{
        inputfp = fopen(argv[2], "rb");
        if (inputfp == 0){
          fprintf(stderr, "Error: Input file \"%s\" could not be opened.\n", argv[2], 003);
          exit(1);
        }
        outputfp = fopen(argv[3], "w");
        if (outputfp == 0){
          fprintf(stderr, "Error: Output file \"%s\" could not be opened.\n", argv[3], 004);
          exit(1);
        }
        read_p6();
        write_p3();
      }
    }
    else {
      fprintf(stderr, "Error: Input number \"%s\" is not 3 or 6.\n", argv[1], 005);
      exit(1);
    }

    fclose(outputfp);
    fclose(inputfp);
    }
  printf("closing...");
  return(0);
};
