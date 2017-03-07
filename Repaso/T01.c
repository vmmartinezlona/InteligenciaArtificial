//Tarea 1
#include<stdio.h>

int main(void)
{
  char caracter, *pchar;
  int entero, *pint;
  short int short_entero;
  long int logn_entero;
  float flotante, *pfloat;
  double doble, *pdouble;
  long double long_doble;

  printf("El tamaño en bytes del tipo char es : %i \n", sizeof(caracter));
  printf("El tamaño en bytes del tipo int es : %i \n", sizeof(entero));
  printf("El tamaño en bytes del tipo short int es : %i \n", sizeof(short_entero));
  printf("El tamaño en bytes del tipo long int es : %i \n", sizeof(logn_entero));
  printf("El tamaño en bytes del tipo float es : %i \n", sizeof(flotante));
  printf("El tamaño en bytes del tipo double es : %i \n", sizeof(doble));
  printf("El tamaño en bytes del tipo long double es : %i \n", sizeof(long_doble));

  printf("El tamaño en bytes del tipo *char es : %i \n", sizeof(pchar));
  printf("El tamaño en bytes del tipo *int es : %i \n", sizeof(pint));
  printf("El tamaño en bytes del tipo *float es : %i \n", sizeof(pfloat));
  printf("El tamaño en bytes del tipo *double es : %i \n", sizeof(pdouble));

  return 0;
}
