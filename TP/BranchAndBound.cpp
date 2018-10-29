#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <float.h>
#define MAX FLT_MAX

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
  - coord_x -> vetor que armazena as coordenadas x das cidades
  - coord_y -> vetor que armazena as coordenadas y das cidades
  - n -> numero de cidades
  - i -> ultima cidade inserida no caminho
  - j -> número de cidades inseridas no caminho
  - x -> vetor que armazena as cidades presentes no caminho
  - flag -> vetor flag que identifica se uma cidade está ou não presente no caminho
  - dist -> distancia atual do caminho
  - min_dist -> menor distancia encontrada (limite inferior)
  - caminho -> caminho final encontrado
*/
void branchbound(int coord_x[], int coord_y[], int n, int i, int j, int x[], int flag[], float dist, float &min_dist, int *caminho){
  for(int k = 1; k < n; k++){
    if(flag[k] != 1){
      flag[k] = 1;                                                                          // Identifcando que a cidade entrou no caminho
      float new_dist = dist + distancia(coord_x[i], coord_x[k], coord_y[i], coord_y[k]);    // Calcula distancia entre a ultima cidade que entrou no caminho e a nova que está entrando

      if(new_dist < min_dist){                                                              // Verifica se distancia continua menor que a menor distancia encontrada
        x[j] = k;                                                                           // Inserindo cidade no caminho
        if(j == n - 1){                                                                     // Verifica se e a ultima cidade do problema
          new_dist += distancia(coord_x[k], coord_x[0], coord_y[k], coord_y[0]);            // Calcula a distancia de retorno para a cidade de origem

          if(new_dist < min_dist){                                                          // Verfica se distancia continua menor que a menor distancia encontrada
            min_dist = new_dist;

            for(int l = 0; l < n; l++){                                                      // Setando caminho
              caminho[l] = x[l] + 1;
            }
          }
        }else{                                                                               // Se não for a ultima cidade do problema
          branchbound(coord_x, coord_y, n, k, j+1, x, flag, new_dist, min_dist, caminho);    // Chama a recursividade para inserir a proxima cidade
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
  int coord_x[numCidades];
  int coord_y[numCidades];


  for(int i = 0; i < numCidades; i++){
    scanf("%d %d", &coord_x[i], &coord_y[i]);
  }

  float resultado = MAX;
  int x[numCidades], flag[numCidades];
  int caminho[numCidades];

  for(int i = 0; i < numCidades; i++){
    flag[i] = 0;
  }
  flag[0] = 1;
  x[0] = 0;

  branchbound(coord_x, coord_y, numCidades, 0, 1, x, flag, 0, resultado, caminho);
  printf("%.2f\n", resultado);

  for(int i = 0; i < numCidades; i++){
    printf("%d ", caminho[i]);
  }

  printf("\n");
}
