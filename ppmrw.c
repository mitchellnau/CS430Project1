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
int width, height, maxcv;

int write_p3();
int write_p6();
int read_p6();

int read_header(char input){
  //printf("Fd: %d\n", inputfp);
  int i, line, endOfHeader, x;
  char a, b;
  char widthB[32], heightB[32], maxcvB[32];
  char comment[64];

  a = fgetc(inputfp);
  b = fgetc(inputfp);
  if(a != 'P' || b != input){
    fprintf(stderr, "Error: Improper header filetype.\n", 005);
    exit(1);
  }
  a = fgetc(inputfp); //move past whitespace

  a = fgetc(inputfp);
  if(a == '#'){       //move past comment
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

  a = fgetc(inputfp);
  i = 0;
  while(a != '\n'){
    maxcvB[i] = a;
    a = fgetc(inputfp);
    i++;
  }
  maxcv = atoi(maxcvB);

  return 1;
}

int read_p3(Pixel* image){
  int i;
  unsigned char check;
  char number[5];
  for(i=0; i < width*height ; i++){
    Pixel temp;

    fgets(number, 10, inputfp);
    check = atoi(number);
    if(check > maxcv){
      fprintf(stderr, "Error: Color value exceeds limit.\n", 006);
      exit(1);
    }
    temp.r = check;

    fgets(number, 10, inputfp);
    check = atoi(number);
    if(check > maxcv){
      fprintf(stderr, "Error: Color value exceeds limit.\n", 006);
      exit(1);
    }
    temp.g = check;

    fgets(number, 10, inputfp);
    check = atoi(number);
    if(check > maxcv){
      fprintf(stderr, "Error: Color value exceeds limit.\n", 006);
      exit(1);
    }
    temp.b = check;
    *(image+i*sizeof(Pixel)) = temp;
  }
  return 1;
}


int write_p3(){
  header[1] = '3';
  fprintf(outputfp, "%s", header);
  int i;
  //char number[4];
  for(i = 0; i < width*height; i++){
    //printf("%3d: %d %d %d\n", i, image[i*sizeof(Pixel)].r,
    //                                          image[i*sizeof(Pixel)].g,
    //                                          image[i*sizeof(Pixel)].b);

    fprintf(outputfp, "%3d: %d %d %d\n", i, image[i*sizeof(Pixel)].r,
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
  int i, c;
  char number[8];
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
  //header[1] = '6';
  //fprintf(outputfp, "%s", header);
  fprintf(outputfp, "%c%c\n", 'P', '6');
  fprintf(outputfp, "%d %d\n", width, height);
  fprintf(outputfp, "%d\n", maxcv);
  int i;
  char number[4];
  for(i = 0; i < width*height; i++){
    sprintf(number, "%c\0", image[i*sizeof(Pixel)].r);
    fwrite(number , 1 , 1 , outputfp );
    sprintf(number, "%c\0", image[i*sizeof(Pixel)].g);
    fwrite(number , 1 , 1 , outputfp );
    sprintf(number, "%c\0", image[i*sizeof(Pixel)].b);
    fwrite(number , 1 , 1 , outputfp );
  }
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
        outputfp = fopen(argv[3], "wb");
        if (outputfp == 0){
          fprintf(stderr, "Error: Output file \"%s\" could not be opened.\n", argv[3], 004);
          exit(1);
        }
        read_header('3');
        Pixel* data = malloc(sizeof(Pixel)*width*height*3);

        read_p3(&data[0]);
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
        read_header('6');
        Pixel* data = malloc(sizeof(Pixel)*width*height*3);

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
