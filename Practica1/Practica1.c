//Desarrollo de PSO
/*
Problema de ejemplo:
  Maximizar la función:
    f(x, y) = 50 - (x-5) ^ 2 + (y - 5) ^ 2
*/
#include<stdio.h>
#include<stdlib.h>

//Particle definition
typedef struct {
  float *Xi; //Actual Position
  float *Vi; //Actual Speed
  float *Pi; //Best Position
  float XFit; //Fitness value
  float PFit; //Best position fitness value
} PARTICLE;

//Swarm definition
typedef struct {
  unsigned int numParticles; //Number of particles of the swarm
  unsigned int numParameters; //Number of parameters of the equation
  unsigned int idGbest; //id of the best particle
  float Vmin;
  float Vmax;
  float c1; //Random constant
  float c2; //Random constant
  PARTICLE *particle; //swarm
} SWARM;

const unsigned int NUMBER_PARTICLES = 200;
const unsigned int NUMBER_PARAMETERS = 2;
const unsigned int NUMBER_ITERATIONS = 100;
const float LimiteInf = 0;
const float LimiteSup = 10;
const float C1 = 2; //por teoria toman este valor
const float C2 = 2;
const float Vmin = -1.0;
const float Vmax = 1.0;

PARTICLE *CreateParticle(void);
SWARM *CreateSwarm(const unsigned int numParticles, const unsigned int numParameters);
void InitSwarm(SWARM *pSwarm, const float infL, const float supL,  const float Vmin, const float Vmax, const float c1, const float c2);
void InitBest(SWARM *pSwarm);
void UpdateSpeed(SWARM *pSwarm);
void UpdatePosition(SWARM *pSwarm);
void UpdateBest(SWARM *pSwarm);
void EvaluateSwarm(SWARM *pSwarm);
void DeleteSwarm(SWARM *pSwarm);
void ShowParticle(SWARM *pSwarm, const unsigned int i);
void ShowSwarm(SWARM *pSwarm);

int main(void)
{
  SWARM *expSwarm;
  unsigned int it = 0;
  unsigned int maxIt = NUMBER_ITERATIONS;
  //Crear memoria para el enjambre
  expSwarm = CreateSwarm(NUMBER_PARTICLES, NUMBER_PARAMETERS);
  //Inicializar posicones de las partículas ente los límite del espacio de búsqueda del problema
  InitSwarm(expSwarm, LimiteInf, LimiteSup, Vmin, Vmax, C1, C2);
  //Iniciar el fitness de cada partícula e identificar el fitness de la mejor global
  InitBest(expSwarm);

  while((it < maxIt) && (50 - expSwarm -> particle[expSwarm -> idGbest].PFit) > 0.0000001)
  {
    //Evaluar las partículas del enjambre en la ecuacion
    EvaluateSwarm(expSwarm);
    UpdateSpeed(expSwarm);
    UpdatePosition(expSwarm);
    UpdateBest(expSwarm);
    //Mostrar todas las partículas del enjambre
    ShowSwarm(expSwarm);
    printf("idGbest: %d \n", expSwarm -> idGbest);
    printf("it = %d ------------------------------------------------\n", it);
    it++;
  }

  //Liberar la memoria del enjambre
  DeleteSwarm(expSwarm);

  return 0;
}

SWARM *CreateSwarm(const unsigned int numParticles, const unsigned int numParameters)
{
  SWARM *pSwarm;

  //_________________________________Asignar memoria para la estructura enjambre
  pSwarm = (SWARM*)malloc(sizeof(SWARM));
  if (pSwarm == NULL)
  {
    printf("Error al asignar memoria a la estructura enjambre.\n");
    return -1;
  }
  //_________________________________Inicializar la estructura
  //Asignar número de partículas
  pSwarm -> numParticles = numParticles;
  //Asignar memoria para las partículas
  pSwarm -> particle = (PARTICLE*)malloc(numParticles*sizeof(PARTICLE));
  if(pSwarm -> particle == NULL)
  {
    printf("Error al asignar memoria a las particulas.\n");
    return -1;
  }
  pSwarm -> numParameters = numParameters;
  //Asignar la memoria a cada partícula
  for (unsigned int i = 0; i < numParticles; i++)
  {
    pSwarm -> particle[i].Xi = (float*)malloc(numParameters*sizeof(float));
    pSwarm -> particle[i].Vi = (float*)malloc(numParameters*sizeof(float));
    pSwarm -> particle[i].Pi = (float*)malloc(numParameters*sizeof(float));
  }

  return pSwarm;
}

void InitSwarm(SWARM *pSwarm, const float infL, const float supL,  const float Vmin, const float Vmax, const float c1, const float c2)
{
  unsigned int i, j;
  double r;

  pSwarm -> c1 = c1;
  pSwarm -> c2 = c2;

  pSwarm -> Vmin = Vmin;
  pSwarm -> Vmax = Vmax;

  //Para todas las particulas
  for(i = 0; i < pSwarm -> numParticles; i++)
  {
    //Para todos los parametros
    for(j = 0; j < pSwarm -> numParameters; j++)
    {
      r = ((double) rand() / RAND_MAX) * (supL - infL) + infL; //Valor random entre InfL-SupL
      //Posicion aleatoria
      pSwarm -> particle[i].Xi[j] = r;
      //Asignamos velocidad 0, pues aun no se empiezan a mover
      pSwarm -> particle[i].Vi[j] = 0;
      //Peso aleatorio
      pSwarm -> particle[i].Pi[j] = r;
    }
      pSwarm -> particle[i].XFit = 0;
      pSwarm -> particle[i].PFit = 0;
  }


  return;
}

void InitBest(SWARM *pSwarm)
{
  unsigned int i;
  float best;
  best = 0;

  for(i = 0; i < pSwarm -> numParticles; i++)
  {
    //En la inicalización el mejor peso es directamente el peso de la particula, pues no hay mas en el historico
    pSwarm -> particle[i].PFit = pSwarm -> particle[i].XFit;
    if(pSwarm -> particle[i].XFit > best)
    {
        //Comparar los pesos de las particulas del ejambre poara saber cual de ellas es la mejor
        pSwarm -> idGbest = i;
        best = pSwarm -> particle[i].PFit;
    }
  }

  return;
}

void EvaluateSwarm(SWARM *pSwarm)
{
  //Evaluamos las particulas en la ecuacion
  unsigned int i;
  for(i = 0; i < pSwarm -> numParticles; i++)
  {
    //f(x,y) = (x-5)º2 + (y-5)ª2
    pSwarm -> particle[i].XFit = 50 - ((pSwarm -> particle[i].Xi[0] - 5) * (pSwarm -> particle[i].Xi[0] - 5) +
                                    (pSwarm -> particle[i].Xi[1]  -5 ) * (pSwarm -> particle[i].Xi[1] - 5));
  }
  return;
}

void UpdateSpeed(SWARM *pSwarm)
{
  unsigned int i, j;
  float y1, y2, aux;

srand(time(NULL));

  //Para todas las partículas
  for(i = 0; i < pSwarm -> numParticles; i++)
  {
    //para todos los parámetros
    for(j = 0; j < pSwarm -> numParameters; j++)
    {
      //Variables aleatorias
      y1 = ((double)rand()/RAND_MAX);
      y2 = ((double)rand()/RAND_MAX);
      //Càlculo de la formula que marca el algoritmo
      aux = pSwarm -> particle[i].Vi[j] + pSwarm -> c1 * y1 * (pSwarm -> particle[i].Pi[j] - pSwarm -> particle[i].Xi[j]) +
                                     pSwarm -> c2 * y2 * (pSwarm -> particle[pSwarm -> idGbest].Pi[j] - pSwarm -> particle[i].Xi[j]);
      if(aux > pSwarm -> Vmax)
      {
        pSwarm -> particle[i].Vi[j] = pSwarm -> Vmax;
        continue;
      }
      if(aux < pSwarm -> Vmin)
      {
        pSwarm -> particle[i].Vi[j] = pSwarm -> Vmin;
        continue;
      }

      pSwarm -> particle[i].Vi[j] = aux;
    }
  }

  return;
}

void UpdatePosition(SWARM *pSwarm)
{
  unsigned int i, j;

  //para todas las particulas
  for(i = 0; i < pSwarm -> numParticles; i++)
  {
    //para todos los parametros
    for(j = 0; j < pSwarm -> numParameters; j++)
    {
      //posicion actual mas la velocidad
      pSwarm -> particle[i].Xi[j] += pSwarm -> particle[i].Vi[j];
    }
  }

  return;
}

void UpdateBest(SWARM *pSwarm)
{
  unsigned int i, j;
  //Peso de la mejor partícula del enjambre
  float best = pSwarm -> particle[pSwarm -> idGbest].PFit;

  //Para todas las particulas
  for(i = 0; i < pSwarm -> numParticles; i++)
  {
    //Si el peso de actual es mayor que el del historico de esa particula
    if(pSwarm -> particle[i].XFit > pSwarm -> particle[i].PFit)
    {
      //Para todos los parametros
      for(j = 0; j < pSwarm -> numParameters; j++)
      {
        //Se actualizan los pesos optimos
        pSwarm -> particle[i].Pi[j] = pSwarm -> particle[i].Xi[j];
        pSwarm -> particle[i].PFit = pSwarm -> particle[i].XFit;
      }
    }
    //Si el mejor peso actual de la particula es mejor que el de la mejor del ejambre
    if(pSwarm -> particle[i].PFit > best)
    {
      //Se actualiza el id y peso del mejor
      pSwarm -> idGbest = i;
      best = pSwarm -> particle[i].PFit;
    }
  }

  return;
}

void ShowParticle(SWARM *pSwarm, const unsigned int i)
{
  unsigned int j;

  printf("\nX%d : ", i);
  for(j = 0; j < pSwarm -> numParameters; j++)
  {
    printf("%2.4f   ", pSwarm -> particle[i].Xi[j]);
  }
  printf("\nV%d : ", i);
  for(j = 0; j < pSwarm -> numParameters; j++)
  {
    printf("%2.4f   ", pSwarm -> particle[i].Vi[j]);
  }
  printf("\nP%d : ", i);
  for(j = 0; j < pSwarm -> numParameters; j++)
  {
    printf("%2.4f   ", pSwarm -> particle[i].Pi[j]);
  }
  printf("\nXFit%d : ", i);
  printf("%2.4f   ", pSwarm -> particle[i].XFit);

  printf("PFit%d : ", i);
  printf("%2.4f\n", pSwarm -> particle[i].PFit);

  return;
}

void ShowSwarm(SWARM *pSwarm)
{
  unsigned int i;
  //Para todas las partículas
  for(i = 0; i < pSwarm -> numParticles; i++)
  {
    ShowParticle(pSwarm, i);
  }

  return;
}

void DeleteSwarm(SWARM *pSwarm)
{
  unsigned int i;

  for (i = 0; i < pSwarm -> numParticles; i++)
  {
    free(pSwarm -> particle[i].Xi);
    free(pSwarm -> particle[i].Vi);
    free(pSwarm -> particle[i].Pi);
  }

  free(pSwarm);

  return;
}
