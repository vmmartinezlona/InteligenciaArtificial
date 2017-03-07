#include<stdio.h>

#include<stdlib.h>

typedef struct {
  float *data;
  unsigned int rows;
  unsigned int columns;
} MATRIX;

void Create_matrix(MATRIX *p_matrix, unsigned int rows, unsigned int columns);
void Fill_matrix(MATRIX *p_matrix);
void Show_matrix(MATRIX *p_matrix);
void Transposed_matrix(MATRIX *p_matrix, MATRIX *trasposed_matrix);

int main(void)
{
  MATRIX *p_matrix, *trasposed_matrix;
  unsigned int rows, columns;

  p_matrix = (MATRIX*)malloc(sizeof(MATRIX));
  trasposed_matrix = (MATRIX*)malloc(sizeof(MATRIX));

  printf("Number of rows: ");
  scanf("%u", &rows);
  printf("Number of columns: ");
  scanf("%u", &columns);

  Create_matrix(p_matrix, rows, columns);
  Fill_matrix(p_matrix);
  printf("\n\nMatrix:\n");
  Show_matrix(p_matrix);

  Create_matrix(trasposed_matrix, p_matrix->columns, p_matrix->rows);
  Transposed_matrix(p_matrix, trasposed_matrix);
  printf("\n\nTrasposed matrix: \n");
  Show_matrix(trasposed_matrix);

  return 0;
}

void Create_matrix(MATRIX *p_matrix, unsigned int rows, unsigned int columns)
{
  unsigned int num_elements;

  p_matrix->rows = rows; p_matrix->columns = columns;
  num_elements = p_matrix->rows * p_matrix->columns;
  p_matrix->data = (float*)malloc(num_elements*sizeof(float));

  return 0;
}

void Fill_matrix(MATRIX *p_matrix)
{
  unsigned int i, j;

  for(i = 0; i < p_matrix->rows; i++)
  {
    for(j = 0; j < p_matrix->columns; j++)
    {
      printf("Ingrese el dato[%d][%d] = ", i, j);
      scanf("%f", &p_matrix->data[p_matrix->columns * i + j]); //data+(p_matrix->colums * i + j)
    }
  }

  return 0;
}

void Show_matrix(MATRIX *p_matrix)
{
  unsigned int i, j;

  for(i = 0; i < p_matrix->rows; i++)
  {
    for(j = 0; j < p_matrix->columns; j++)
    {
      printf("%.2f\t", p_matrix->data[p_matrix->columns * i + j]);
    }
    printf("\n");
  }

  return 0;
}

void Transposed_matrix(MATRIX *p_matrix, MATRIX *trasposed_matrix)
{
  unsigned int i, j;

  for(i = 0; i < p_matrix->rows; i++)
  {
    for(j = 0; j < p_matrix->columns; j++)
    {
      trasposed_matrix->data[trasposed_matrix->columns * j + i]
        = p_matrix->data[p_matrix->columns * i + j];
    }
  }

  return 0;
}
