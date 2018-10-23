#include <stdio.h>

int arranjo(int n, int r, int x[], int flag[], int k){
  int i;

  if(k == r){
    for(i = 0; i < r; i++){
      printf("%d ", x[i] + 1);
    }
    printf("\n");
  }else{
    for(i = 1; i < n; i++){
      if(flag[i] != 1){
        x[k] = i;
        flag[i] = 1;
        arranjo(n, r, x, flag, k+1);
        flag[i] = 0;
      }
    }
  }
}

int main(){
  int n, r, x[100];
  x[0] = 0;

  printf("Entre com o valor de n: \n");
  scanf("%d", &n);

  printf("Entre com o valor de r: \n");
  scanf("%d", &r);

  int flag[n];
  for(int i = 0; i < n; i++){
    flag[i] = 0;
  }

  arranjo(n, r, x, flag, 1);
}
