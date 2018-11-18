#include <stdio.h>
#include <math.h>
#include <float.h>
#include <vector>
#include <time.h>

using namespace std;

/*
Estrutura para armazenamento das coordenadas das cidades
*/
struct Cidade{
  int coord_x;
  int coord_y;
};
typedef Cidade Cidade;

struct Celula{
  float custo;
  int cidadeOrigem;
  vector <int> conjunto;
};
typedef Celula Celula;

Celula *vetorCusto;
float **distancias;
vector <vector <int> > matrizCombinacoes;
int numCombinacoes, numCidades, controle = 0;
int *index;

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

vector <int> retiraElemento(vector <int> vetor, int elemento){
  vector <int> novoVetor;
  novoVetor.resize(vetor.size() - 1);

  for(int i = 0, j = 0; i < vetor.size(); i++, j++){
    if(vetor[i] == elemento){
      i++;
    }

    if(i < vetor.size()){
      novoVetor[j] = vetor[i];
    }
  }

  return novoVetor;
}

int calcularNumCombinacoes (int numEle, int tamConj) {
  int dividendo = 1;

  for(int i = numEle; i >= 1; i--){
    dividendo *= i;
  }

  int aux1 = 1;
  for(int i = tamConj; i >= 1; i--){
    aux1 *= i;
  }

  int aux2 = 1;
  for(int i = numEle - tamConj; i >= 1; i--){
    aux2 *= i;
  }

  int divisor = aux1 * aux2;

  return (dividendo / divisor);
}

void combinacoes(int n, int r, vector <int> x, int next, int k, int origem){
  int i;
  if(k == r){
    matrizCombinacoes[numCombinacoes - 1] = x;
    numCombinacoes++;
  }else{
    for(i = next; i < n; i++){
      if(i != origem){
        x[k] = i;
        combinacoes(n, r, x, i+1, k+1, origem);
      }
    }
  }
}

void calculoVetorCusto(){
  int tamConjunto = 1;
  matrizCombinacoes.resize(numCidades - 2);
  numCombinacoes = 1;

  for(int i = 1; i < numCidades; i++){
    vector <int> x;
    x.resize(tamConjunto);
    combinacoes(numCidades, 1, x, 1, 0, i);

    for(int j = 0; j < matrizCombinacoes.size(); j++){
      vetorCusto[controle].custo = distancias[i][matrizCombinacoes[j][0]] + distancias[matrizCombinacoes[j][0]][0];
      vetorCusto[controle].cidadeOrigem = i;
      vetorCusto[controle].conjunto = matrizCombinacoes[j];

      index[i] = controle;

      controle++;
    }

    numCombinacoes = 1;
  }

  tamConjunto++;

  vector <int> x;
  int aux;
  while(tamConjunto < numCidades - 1){
    aux = controle;
    x.resize(tamConjunto);
    matrizCombinacoes.resize(calcularNumCombinacoes(numCidades - 2, tamConjunto));
    for(int i = 1; i < numCidades; i++){
      combinacoes(numCidades, tamConjunto, x, 1, 0, i);
      for(int j = 0; j < matrizCombinacoes.size(); j++){
        float minCusto = FLT_MAX;
        for(int k = 0; k < tamConjunto; k++){
          int cidadeOrigem = matrizCombinacoes[j][k];
          vector <int> auxVetor = retiraElemento(matrizCombinacoes[j], matrizCombinacoes[j][k]);

          bool achou = false;
          for(int l = index[cidadeOrigem]; l >= 0 && achou == false; l--){
            if(cidadeOrigem == vetorCusto[l].cidadeOrigem && vetorCusto[l].conjunto == auxVetor){
              achou = true;
              float custo = distancias[i][cidadeOrigem] + vetorCusto[l].custo;

              if(custo < minCusto){
                minCusto = custo;
              }
            }
          }
        }

        index[i] = controle;

        vetorCusto[controle].custo = minCusto;
        vetorCusto[controle].cidadeOrigem = i;
        vetorCusto[controle].conjunto = matrizCombinacoes[j];

        controle++;
      }

      numCombinacoes = 1;
    }

    tamConjunto++;
  }

  x.resize(tamConjunto);
  matrizCombinacoes.resize(1);
  combinacoes(numCidades, tamConjunto, x, 1, 0, 0);

  for(int j = 0; j < matrizCombinacoes.size(); j++){
    float minCusto = FLT_MAX;
    for(int k = 0; k < tamConjunto; k++){
      int cidadeOrigem = matrizCombinacoes[j][k];
      vector <int> auxVetor = retiraElemento(matrizCombinacoes[j], matrizCombinacoes[j][k]);

      bool achou = false;
      for(int i = index[cidadeOrigem]; i >=0 && achou == false; i--){
        if(cidadeOrigem == vetorCusto[i].cidadeOrigem && vetorCusto[i].conjunto == auxVetor){
          achou = true;
          float custo = distancias[0][cidadeOrigem] + vetorCusto[i].custo;

          if(custo < minCusto){
            minCusto = custo;
          }
        }
      }
    }

    vetorCusto[controle].custo = minCusto;
    vetorCusto[controle].cidadeOrigem = 0;
    vetorCusto[controle].conjunto = matrizCombinacoes[j];
  }

  printf("%.2f\n", vetorCusto[controle].custo);
}

// Função principal
int main(){
  scanf("%d\n", &numCidades);

  Cidade cidades[numCidades];
  vetorCusto = new Celula[numCidades-1];

  // Leitura das coordenadas das cidades
  for(int i = 0; i < numCidades; i++){
    scanf("%d %d", &cidades[i].coord_x, &cidades[i].coord_y);
  }

  distancias = new float*[numCidades];                                        // Matriz para armazenamento das distâncias

  // Reserva de espaço de memória para a matriz
  for(int i = 0; i < numCidades; i++){
    distancias[i] = new float[numCidades];
  }

  // Calculo da matriz de distancias
  for(int i = 0; i < numCidades; i++){
    for(int j = 0; j < numCidades; j++){
      distancias[i][j] = distancia(cidades[i].coord_x, cidades[j].coord_x, cidades[i].coord_y, cidades[j].coord_y);
    }
  }

  int tamanho = 0;
  for(int i = 1; i < numCidades - 1; i++){
    tamanho += (numCidades - 1) * calcularNumCombinacoes(numCidades - 2, i);
  }
  tamanho = tamanho + 1;

  index = new int[numCidades];
  vetorCusto = new Celula[tamanho];

  clock_t Ticks[2];
  Ticks[0] = clock();
  calculoVetorCusto();
  Ticks[1] = clock();
  double tempo = (Ticks[1] - Ticks[0]) * 1000.0 / CLOCKS_PER_SEC;

  printf("Tempo gasto: %.2f\n", tempo);
}
