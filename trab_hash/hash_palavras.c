#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define TAM_TABELA 300    /*Tamanho da tabela hash*/

/*A hash implementada para este trabalho utiliza encadeamento externo*/
typedef struct _Palavra_Hash {
    char palavra[100];
    int qntOcorrencias;
    struct _Palavra_Hash *prox;
} Palavra_Hash;

int h(char *palavra){    /*Esta é a função de hash utilizada (somatório dos códigos ASCII da palavra módulo o tamanho da tabela)*/
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
            strcpy(novo->palavra, palavra);
            novo->qntOcorrencias = 1;    /*Quando um novo elemento é inserido, seu número de ocorrências começa com 1*/

            if(ptAnt != NULL)    /*Se eu não estiver inserindo o primeiro elemento da lista*/
                ptAnt->prox = novo;
            else
                tabela[indiceValor] = novo;

            /*printf("Palavra '%s' inserida!\n", palavra);*/
        }
    }
}

/*Esta função foi feita para verificar se caracteres isolados do texto são palavras válidas (se for um algarismo ou uma letra)*/
int isCaractereValido(char caractere){
    if((caractere >= 48 && caractere <= 57) || (caractere >= 65 && caractere <= 90) || (caractere >= 97 && caractere <= 122))
        return 1;
    return 0;
}


/*As seguintes funções de remoção e de printar a tabela hash foram feitas apenas como treinamento e para realizar testes*/
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
        /*printf("Nao foi possivel remover o elemento '%s'. Elemento nao esta na hash!\n", palavra);*/
        return 0;
    }

    if(ptAnt == NULL)
        tabela[indiceValor] = pt->prox;
    else
        ptAnt->prox = pt->prox;

    free(pt);

    /*printf("Elemento '%s' removido!\n", palavra);*/
    return 1;
}

void printarTabelaHash(Palavra_Hash **tabela){
    int i;
    float fatorCarga=0;
    printf("\n==========TABELA HASH==========\n");
    for(i=0; i<TAM_TABELA; i++){
        Palavra_Hash *pt = tabela[i];
        int contElementosPosicao=0;
        printf("%d: ", i+1);
        while(pt != NULL){
            fatorCarga++;

            contElementosPosicao++;
            pt = pt->prox;
        }
        if(contElementosPosicao == 0)
            printf("---------- ");

        printf("     Quantidade de elementos: %d\n", contElementosPosicao);
    }
    fatorCarga = fatorCarga / (float) TAM_TABELA;
    printf("Fator de carga: %.2f", fatorCarga);
    printf("\n");
}


int main(){
    char palavra[100], *palavraProcurada = "the";
    Palavra_Hash *tabela[TAM_TABELA];    /*Este vetor representa a tabela hash*/
    Palavra_Hash *elementoProcurado;
    Init_Hash(tabela);     /*Inicializando a tabela hash (todas as posições receberão NULL)*/

    while(scanf("%s", palavra) != EOF){     /*Realizando a leitura do input de texto palavra por palavra*/
        int tamPalavra = strlen(palavra), palavraValida=0;
        /*Fazendo algumas verificações antes de adicionar a palavra lida na tabela hash*/
        if(tamPalavra > 0){
            if(palavra[tamPalavra-1] == ','){
                palavra[tamPalavra-1] = '\0';
                tamPalavra--;
            }
        }
        if(tamPalavra == 1){
            if(isCaractereValido(palavra[0]))
                palavraValida = 1;
        }
        else if(tamPalavra > 1)
            palavraValida = 1;

        if(palavraValida)
            inserirNaHash(tabela, palavra);
    }

    /*printarTabelaHash(tabela);*/

    elementoProcurado = recuperarElementoNaHash(tabela, palavraProcurada);     /*Recuperando o elemento correspondente à palavra procurada na tabela hash*/
    if(elementoProcurado == NULL)
        printf("O termo procurado nao foi encontrado!");
    else
        printf(" %d %s ", elementoProcurado->qntOcorrencias, palavraProcurada);

    return 0;
}