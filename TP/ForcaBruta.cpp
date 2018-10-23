#include <stdio.h>
#include <stdlib.h>
#include <float.h>
#include <math.h>
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
Função que utiliza a técnica de arranjo para achar a menor distância que será percorrida pelo carteiro
Parâmetros:
  - n -> numero total de cidades
  - r -> numero de cidades que pertencerá ao arranjo
  - x -> vetor que armazena o arranjo
  - flag -> vetor flag que identifica quais elementos estão presentes no arranjo
  - k -> numero de elementos presentes no arranjo
  - min_dist -> distância mínima encontrada
  - caminho -> vetor que armazena o caminho encontrado na distância minima
  - coord_x -> vetor que armazena as coordenadas x das cidades
  - coord_y -> vetor que armazena as coordenadas y das cidades
*/
float arranjo(int n, int r, int x[], int flag[], int k, float min_dist, int *caminho, int coord_x[], int coord_y[]){
  int i;

  if(k == r){
    float soma_dist = 0;
    int cidade1, cidade2;
    for(i = 0; i < r - 1; i++){
      cidade1 = x[i];
      cidade2 = x[i + 1];
      soma_dist += distancia(coord_x[cidade1], coord_x[cidade2], coord_y[cidade1], coord_y[cidade2]);   // Calculo da distancia entre as cidades
    }

    cidade1 = x[0];
    soma_dist += distancia(coord_x[cidade1], coord_x[cidade2], coord_y[cidade1], coord_y[cidade2]);     // Calculo da distancia entre a cidade de origem e a cidade final

    if(soma_dist < min_dist){
      min_dist = soma_dist;

      // Setando caminho encontrado
      for(int i = 0; i < r; i++){
        caminho[i] = x[i] + 1;
      }
    }
  }else{
    for(i = 1; i < n; i++){
      if(flag[i] != 1){
        x[k] = i;                                                                                         // Armazenando elemento no arranjo
        flag[i] = 1;                                                                                      // Identificando que elemento está agora presente no arranjo
        min_dist = arranjo(n, r, x, flag, k+1, min_dist, caminho, coord_x, coord_y);
        flag[i] = 0;                                                                                      // Identificando que elemento foi retirado do arranjo
      }
    }
  }

  return min_dist;
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

  float resultado, min_dist = MAX;
  int x[numCidades], flag[numCidades];
  int *caminho = new int[4];

  for(int i = 0; i < numCidades; i++){
    flag[i] = 0;
  }
  x[0] = 0;

  resultado = arranjo(numCidades, numCidades, x, flag, 1, min_dist, caminho, coord_x, coord_y);
  printf("%.2f\n", resultado);

  for(int i = 0; i < numCidades; i++){
    printf("%d ", caminho[i]);
  }

  printf("\n");
}
