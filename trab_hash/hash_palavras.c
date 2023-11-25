#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define TAM_TABELA 100    /*Tamanho da tabela hash*/

/*A hash implementada para este trabalho utiliza encadeamento externo*/
typedef struct _Palavra_Hash {
    char *palavra;
    int qntOcorrencias;
    struct _Palavra_Hash *prox;
} Palavra_Hash;


int h(char *palavra){    /*Esta é a função de hash*/
    int tam_string = strlen(palavra), i, somatorio_ASCII=0;
    for(i=0; i<tam_string; i++){
        somatorio_ASCII += palavra[i];
    }
    return (somatorio_ASCII % TAM_TABELA);
}

void Init_Hash(Palavra_Hash *tabela[]){
    int i;
    for(i=0; i<TAM_TABELA; i++){
        tabela[i] = NULL;     /*Inicialmente, todas as posições da tabela estão vazias*/
    }
}

Palavra_Hash* recuperarElementoNaHash(Palavra_Hash **tabela, char *palavra){    /*Função para recuperar determinado elemento da hash*/
    int indiceValor = h(palavra);
    Palavra_Hash *pt = tabela[indiceValor];
    while(pt != NULL){
        if(strcmp(pt->palavra, palavra) == 0)    /*Se as strings forem iguais*/
            break;
        pt = pt->prox;
    }

    return pt;
}

void inserirNaHash(Palavra_Hash **tabela, char *palavra){
    int indiceValor = h(palavra);
    Palavra_Hash *pt = tabela[indiceValor], *ptAnt;
    ptAnt = NULL;
    while(pt != NULL){
        if(strcmp(pt->palavra, palavra) == 0)
            break;
        ptAnt = pt;
        pt = pt->prox;
    }

    if(pt != NULL){
        pt->qntOcorrencias++;    /*Se foi tentado inserir um elemento que já estava na tabela, sua quantidade de ocorrências será incrementada*/
        /*printf("O elemento '%s' ja esta na hash! Sua ocorrencia foi incrementada.\n", palavra);*/
    }
    else{
        /*Aqui, vou inserir o novo elemento ao final da lista*/
        Palavra_Hash *novo = (Palavra_Hash *)malloc(sizeof(Palavra_Hash));
        if(novo){
            novo->prox = NULL;

            novo->palavra = (char *)malloc(sizeof(char) * (strlen(palavra) + 1));
            if(!(novo->palavra))
                return;
            strcpy(novo->palavra, palavra);

            novo->qntOcorrencias = 1;

            if(ptAnt != NULL){    /*Se eu não estiver inserindo o primeiro elemento da lista*/
                ptAnt->prox = novo;
            }
            else{     /*Se for o primeiro elemento da lista*/
                tabela[indiceValor] = novo;
            }

            /*printf("Palavra '%s' inserida!\n", palavra);*/
        }
    }
}


int removerDaHash(Palavra_Hash **tabela, char *palavra){
    int indiceValor = h(palavra);
    Palavra_Hash *pt = tabela[indiceValor], *ptAnt;
    ptAnt = NULL;
    while(pt != NULL){
        if(strcmp(pt->palavra, palavra) == 0)
            break;
        ptAnt = pt;
        pt = pt->prox;
    }

    if(pt == NULL){
        printf("Nao foi possivel remover o elemento '%s'. Elemento nao esta na hash!\n", palavra);
        return 0;
    }

    if(ptAnt == NULL){
        tabela[indiceValor] = pt->prox;
    }
    else{
        ptAnt->prox = pt->prox;
    }

    free(pt);

    printf("Elemento '%s' removido!\n", palavra);
    return 1;
}


void printarTabelaHash(Palavra_Hash **tabela){
    int i;
    printf("\n==========TABELA HASH==========\n");
    for(i=0; i<TAM_TABELA; i++){
        Palavra_Hash *pt = tabela[i];
        int contElementos=0;
        printf("%d: ", i+1);
        while(pt != NULL){
            /*
            if(pt->prox != NULL)
                printf("%s - ", pt->palavra);
            else
                printf("%s ", pt->palavra);
            */
            contElementos++;
            pt = pt->prox;
        }
        if(contElementos == 0)
            printf("---------- ");

        printf("     Quantidade de elementos: %d\n", contElementos);
    }
    printf("\n");
}

/*Esta função foi feita para verificar se caracteres isolados do texto são palavras válidas (se for um algarismo ou uma letra)*/
int isCaractereValido(char caractere){
    if((caractere >= 48 && caractere <= 57) || (caractere >= 65 && caractere <= 90) || (caractere >= 97 && caractere <= 122))
        return 1;
    return 0;
}


int main(){
    char palavra[100];
    Palavra_Hash *tabela[TAM_TABELA];    /*Este vetor representa nossa tabela hash*/
    Init_Hash(tabela);     /*Inicializando minha tabela hash*/

    /*
    printf("Paul -> %d\n", h("Paul"));
    printf("John -> %d\n", h("John"));
    printf("George -> %d\n", h("George"));
    printf("Ringo -> %d\n", h("Ringo"));
    printf("Hugo -> %d\n", h("Hugo"));
    */

    /*
    inserirNaHash(tabela, "Paul");
    inserirNaHash(tabela, "John");
    inserirNaHash(tabela, "George");
    inserirNaHash(tabela, "Ringo");
    printarTabelaHash(tabela);

    inserirNaHash(tabela, "Hugo");
    inserirNaHash(tabela, "Paul");
    removerDaHash(tabela, "John");
    removerDaHash(tabela, "George");
    removerDaHash(tabela, "John");
    inserirNaHash(tabela, "George");
    inserirNaHash(tabela, "Nicolas");
    printarTabelaHash(tabela);

    Palavra_Hash *teste2 = recuperarElementoNaHash(tabela, "Paul");
    Palavra_Hash *teste3 = recuperarElementoNaHash(tabela, "George");

    printf("Elemento: %s  qnt ocorrencias: %d\n", teste2->palavra, teste2->qntOcorrencias);
    printf("Elemento: %s  qnt ocorrencias: %d\n", teste3->palavra, teste3->qntOcorrencias);
    */


    while(scanf("%s", palavra) != EOF){
        int tamPalavra = strlen(palavra), palavraValida=0;
        if(tamPalavra == 1){
            if(isCaractereValido(palavra[0])){
                palavraValida = 1;
            }
        }
        else{
            if(palavra[tamPalavra-1] == ',')
                palavra[tamPalavra-1] = '\0';
            palavraValida = 1;
        }

        if(palavraValida){
            inserirNaHash(tabela, palavra);
        }
    }

    printarTabelaHash(tabela);

    Palavra_Hash *teste = recuperarElementoNaHash(tabela, "the");
    if(teste == NULL)
        printf("Nao foi achado o termo procurado!");
    else
        printf("\nQuantidade de 'the': %d", teste->qntOcorrencias);
    printf("\n\nFIM\n");
    return 0;
}