#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

struct dataset {
  double x;
  double y;
};

void inputData(struct dataset data[], int dataNumber, char filename[256])
{
  FILE *fp;
  int i;

  fp = fopen(filename, "r");
  if(fp==NULL) {
    printf("Error.\n");
    printf("Can't open file.\n");
    exit(1);
  }
  
  for(i=0; i<dataNumber; i++) {
    fscanf(fp, "%lf", &data[i].x);
    fscanf(fp, "%lf", &data[i].y);
  }
  
  fclose(fp);
}

void dispData(struct dataset data[], int dataNumber)
{
  int i;
  
  for(i=0; i<dataNumber; i++) {
    printf("%lf %lf\n", data[i].x, data[i].y);
  }

}

void lsm(struct dataset data[], int dataNumber)
{
  dispData(data, dataNumber);

  double sum_1 = 0;
  double sum_x = 0;
  double sum_xx = 0;
  double sum_xy = 0;
  double sum_y = 0;

  int i;
  double a,b;
  double denom;

  for(i=0; i<dataNumber; i++){
    sum_1 ++;
    sum_x += data[i].x;
    sum_xx += data[i].x * data[i].x;
    sum_xy += data[i].x * data[i].y;
    sum_y += data[i].y;
  }

  denom = (sum_xx * sum_1) - (sum_x * sum_x);

  a = ((sum_1 * sum_xy) - (sum_x * sum_y)) / denom;
  b = ((sum_xx * sum_y) - (sum_x * sum_xy)) / denom;

  printf("a = %f\n",a);
  printf("b = %f\n",b);
}


int main(int argc, char *argv[])
{
  struct dataset *data;
  int dataNumber;
  char filename[256];

  if(argc-1 != 2) {
    printf("Error.\n");
    printf("Usage: ./a.out [Data Number] [Filename]\n");
    exit(1);
  }
  
  dataNumber = atoi(argv[1]);
  strcpy(filename, argv[2]);

  data = (struct dataset *)malloc(sizeof(struct dataset)*dataNumber);

  inputData(data, dataNumber, filename);

  lsm(data, dataNumber);

  return 0;
}
