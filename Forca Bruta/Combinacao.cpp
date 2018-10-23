#include <stdio.h>

int combinacao(int n, int r, int x[], int next, int k){
  int i;

  if(k == r){
    for(i = 0; i < r; i++){
      printf("%d ", x[i] + 1);
    }
    printf("\n");
  }else{
    for(i = next; i < n; i++){
      x[k] = i;
      combinacao(n, r, x, i+1, k+1);
    }
  }
}

int main(){
  int n, r, x[100];

  printf("Entre com o valor de n: \n");
  scanf("%d", &n);

  printf("Entre com o valor de r: \n");
  scanf("%d", &r);

  combinacao(n, r, x, 0, 0);
}
