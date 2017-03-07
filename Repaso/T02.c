//Tarea 2
#include<stdio.h>

void Enter_data(float *data, unsigned int *number_data);
void Show_vector(float *data, unsigned int *number_data);
float Average_vector(float *data, unsigned int *number_data);

int main(void)
{
  float data[100];
  unsigned int number_data;
  float average;

  printf("Ingrese numero de datos del arreglo: ");
  scanf("%u", &number_data);

  Enter_data(data, &number_data);
  Show_vector(data, &number_data);

  average = Average_vector(data, &number_data);
  printf("\nEl promedio del vector es: %.3f\n", average);

  return 0;
}

void Enter_data(float *data, unsigned int *number_data)
{
  unsigned int i;

  for(i = 0; i < *number_data; i++)
  {
    printf("Dato[%i]: ", i+1);
    scanf("%f", data+i); //data+i == &data[i]
  }
  return 0;
}

void Show_vector(float *data, unsigned int *number_data)
{
  unsigned int i;

  printf("El vector ingresado es:\n");
  for(i = 0; i < *number_data; i++)
    printf("%2.2f  ", data[i]); //*(data+i)

  return 0;
}

float Average_vector(float *data, unsigned int *number_data)
{
  unsigned int i;
  float sum = 0;

  for(i = 0; i < *number_data; i++)
    sum += data[i];

  return sum / (*number_data);
}
