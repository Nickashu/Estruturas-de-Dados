#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void insereNumero(int **vetor, int *tam, int *n_elementos, int num);
void overflow(int **vetor, int *tam);
void quickSort(int *vetor, int inicio, int fim);
int particiona(int *vetor, int inicio, int fim);
void printaVetor(int *vetor, int n_elementos);

int main(){
    int *vetorDinamico, num, tam=10, n_elementos=0;

    vetorDinamico = (int *)malloc(tam * sizeof(int));   /*Iniciando com um vetor de 10 posições*/

    while (scanf("%d", &num) != EOF) {    /*Inserindo elementos até o fim de arquivo*/
        insereNumero(&vetorDinamico, &tam, &n_elementos, num);   /*Tenho que passar o endereço do vetor pois estou modificando ele em outra função*/
    }

    /*printaVetor(vetorDinamico, n_elementos);*/    /*Printando antes da ordenação*/
    quickSort(vetorDinamico, 0, n_elementos-1);    /*Ordenando o vetor com o quick sort*/
    /*printf("Ordenando...\n");*/
    printaVetor(vetorDinamico, n_elementos);    /*Printando depois da ordenação*/

    return 0;
}

void insereNumero(int **vetor, int *tam, int *n_elementos, int num){     /*Função para inserir um número no array*/
    if(*n_elementos == *tam)   /*Vetor cheio*/
        overflow(&(*vetor), &(*tam));

    if(*n_elementos < *tam) {
        (*vetor)[*n_elementos] = num;
        (*n_elementos)++;
    }
}

void overflow(int **vetor, int *tam){
    int i, novoTamanho = (*tam) * 2;   /*Dobrando o tamanho anterior*/
    int *vetorTemp = (int *)malloc(novoTamanho * sizeof(int));
    if(vetorTemp == NULL){
        printf("Erro ao criar novo vetor.\n");
        return;
    }

    for(i=0; i<(*tam); i++){
        vetorTemp[i] = (*vetor)[i];    /*Copiando os elementos de um vetor para o outro*/
    }

    free(*vetor);
    *vetor = vetorTemp;
    *tam = novoTamanho;
}

/*
void bubbleSort(int *vetor, int n_elementos){
    int i, j, temp;
    for(i=0; i<n_elementos; i++){
        for(j=i+1; j<n_elementos; j++){
            if(vetor[i] > vetor[j]){
                temp = vetor[i];
                vetor[i] = vetor[j];
                vetor[j] = temp;
            }
        }
    }
}
*/

void quickSort(int *vetor, int inicio, int fim){
    int p;
    if(inicio < fim){
        p = particiona(vetor, inicio, fim);
        quickSort(vetor, inicio, p-1);
        quickSort(vetor, p+1, fim);
    }
}

int particiona(int *vetor, int inicio, int fim){
    int idAleatorio = inicio + (rand() % (fim - inicio));    /*Fazendo com o pivot sendo aleatório*/
    int i=inicio, j, temp, pivot;
    srand(time(NULL));
    temp = vetor[idAleatorio];
    vetor[idAleatorio] = vetor[fim];
    vetor[fim] = temp;
    pivot = vetor[fim];

    for(j=inicio; j<fim; j++){
        if(vetor[j] <= pivot){
            temp = vetor[j];
            vetor[j] = vetor[i];
            vetor[i] = temp;
            i++;
        }
    }
    temp = vetor[i];
    vetor[i] = vetor[fim];
    vetor[fim] = temp;
    return i;
}

void printaVetor(int *vetor, int n_elementos){
    int i;
    //printf("Vetor:\n");
    for(i=0; i<n_elementos; i++){
        printf("%d\n", vetor[i]);
    }
    printf("\n");
}