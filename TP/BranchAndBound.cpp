#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <float.h>
#include <time.h>
#define MAX FLT_MAX

/*
Estrutura para armazenamento das coordenadas das cidades
*/

struct Cidade{
  int coord_x;
  int coord_y;
};

typedef Cidade Cidade;

/*
Função para cálculo da distância entre duas cidades.
Parâmetros:
  - x1 -> coordenada x da cidade1
  - x2 -> coordenada x da cidade2
  - y1 -> coordenada y da cidade1
  - x2 -> coordenada y da cidade2
*/
float distancia(int x1, int x2, int y1, int y2){
  float dist = sqrt(pow((x1 - x2),2) + pow((y1 - y2),2));
  return dist;
}

/*
Função que utiliza a técnica de branch and bound para achar a menor distância que será percorrida pelo carteiro
Parâmetros:
  - distancias -> matriz que armazena as distancias entre as cidades
  - n -> numero de cidades
  - i -> ultima cidade inserida no caminho
  - j -> número de cidades inseridas no caminho
  - x -> vetor que armazena as cidades presentes no caminho
  - flag -> vetor flag que identifica se uma cidade está ou não presente no caminho
  - dist -> distancia atual do caminho
  - min_dist -> menor distancia encontrada (limite inferior)
  - caminho -> caminho final encontrado
*/
void branchbound(double **distancias, int n, int i, int j, int x[], int flag[], float dist, float &min_dist, int *caminho){
  for(int k = 1; k < n; k++){
    if(flag[k] != 1){
      flag[k] = 1;                                                                          // Identifcando que a cidade entrou no caminho
      float new_dist = dist + distancias[i][k];                                             // Calcula distancia entre a ultima cidade que entrou no caminho e a nova que está entrando

      if(new_dist < min_dist){                                                              // Verifica se distancia continua menor que a menor distancia encontrada
        x[j] = k;                                                                           // Inserindo cidade no caminho
        if(j == n - 1){                                                                     // Verifica se e a ultima cidade do problema
          new_dist += distancias[k][0];                                                     // Calcula a distancia de retorno para a cidade de origem

          if(new_dist < min_dist){                                                          // Verfica se distancia continua menor que a menor distancia encontrada
            min_dist = new_dist;

            for(int l = 0; l < n; l++){                                                      // Setando caminho
              caminho[l] = x[l] + 1;
            }
          }
        }else{                                                                               // Se não for a ultima cidade do problema
          branchbound(distancias, n, k, j+1, x, flag, new_dist, min_dist, caminho);          // Chama a recursividade para inserir a proxima cidade
        }
      }

      flag[k] = 0;                                                                            // Identifica que a cidade está saindo do caminho
    }
  }
}

// Função principal
int main(){
  int numCidades;
  scanf("%d\n", &numCidades);

  Cidade cidades[numCidades];

  // Leitura das coordenadas das cidades
  for(int i = 0; i < numCidades; i++){
    scanf("%d %d", &cidades[i].coord_x, &cidades[i].coord_y);
  }

  double **distancias = new double*[numCidades];                                                // Matriz para armazenamento das distâncias

  // Reserva de espaço de memória para a matriz
  for(int i = 0; i < numCidades; i++){
    distancias[i] = new double[numCidades];
  }

  // Calculo da matriz de distancias
  for(int i = 0; i < numCidades; i++){
    for(int j = 0; j < numCidades; j++){
      distancias[i][j] = distancia(cidades[i].coord_x, cidades[j].coord_x, cidades[i].coord_y, cidades[j].coord_y);
    }
  }

  float resultado = MAX;
  int x[numCidades], flag[numCidades];
  int caminho[numCidades];

  for(int i = 0; i < numCidades; i++){
    flag[i] = 0;
  }
  flag[0] = 1;
  x[0] = 0;

  clock_t Ticks[2];
  Ticks[0] = clock();
  branchbound(distancias, numCidades, 0, 1, x, flag, 0, resultado, caminho);
  Ticks[1] = clock();
  double tempo = (Ticks[1] - Ticks[0]) * 1000.0 / CLOCKS_PER_SEC;

  printf("%.2f\n", resultado);

  for(int i = 0; i < numCidades; i++){
    printf("%d ", caminho[i]);
  }
  printf("\n");

  printf("Tempo gasto: %.2f\n", tempo);
}
