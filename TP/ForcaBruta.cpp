#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <math.h>
#define max INT_MAX

float distancia(int x1, int x2, int y1, int y2){
  float dist = sqrt(pow((x1 - x2),2) + pow((y1 - y2),2));

  return dist;
}

float arranjo(int n, int r, int x[], int flag[], int k, float min_dist, int coord_x[], int coord_y[]){
  int i;

  if(k == r){
    float soma_dist = 0;
    int cidade1, cidade2;
    for(i = 0; i < r - 1; i++){
      cidade1 = x[i];
      cidade2 = x[i + 1];
      soma_dist += distancia(coord_x[cidade1], coord_x[cidade2], coord_y[cidade1], coord_y[cidade2]);
    }

    cidade1 = x[0];
    cidade2 = x[i];
    soma_dist += distancia(coord_x[cidade1], coord_x[cidade2], coord_y[cidade1], coord_y[cidade2]);

    if(soma_dist < min_dist){
      min_dist = soma_dist;
    }
  }else{
    for(i = 1; i < n; i++){
      if(flag[i] != 1){
        x[k] = i;
        flag[i] = 1;
        min_dist = arranjo(n, r, x, flag, k+1, min_dist, coord_x, coord_y);
        flag[i] = 0;
      }
    }
  }

  return min_dist;
}

int main(){
  int numCidades;
  scanf("%d\n", &numCidades);
  int coord_x[numCidades];
  int coord_y[numCidades];


  for(int i = 0; i < numCidades; i++){
    scanf("%d %d", &coord_x[i], &coord_y[i]);
  }

  float resultado, min_dist = 99999.0;
  int x[numCidades], flag[numCidades];

  for(int i = 0; i < numCidades; i++){
    flag[i] = 0;
  }
  x[0] = 0;
  resultado = arranjo(numCidades, numCidades, x, flag, 1, min_dist, coord_x, coord_y);

  printf("%.2f\n", resultado);
}
