#include <stdio.h>
#include <stdlib.h>

typedef struct _NO_ARVORE{
    int chave;
    struct _NO_ARVORE *esq, *dir;
} NO_ARVORE;

typedef struct _NO{
    NO_ARVORE *no_arv;
    struct _NO *prox;
} NO;

typedef struct _FILA{
    NO *pInicio, *pFinal;
    int vazia;
} FILA;

void initFila(FILA **f);
void enqueue(FILA **f, NO_ARVORE *ptNo);
NO_ARVORE *dequeue(FILA **f);
void printaEmNivel(NO_ARVORE *ptRaiz);
void printaEmOrdem(NO_ARVORE *ptRaiz);
void insereElemento(NO_ARVORE **ptRaiz, int chave);
NO_ARVORE *buscaElemento(NO_ARVORE *ptRaiz, NO_ARVORE **pai, int chave);
void removeElemento(NO_ARVORE **ptRaiz, int chave);

int main(){
    int sair=0, opc, num;
    NO_ARVORE *ptRaiz = NULL;   /*Iniciando com a árvore vazia*/

    do{
        printf("1 - Inserir na arvore\n2 - Remover da arvore\n3 - Printar arvore\n4 - Sair\n");
        scanf("%d", &opc);
        switch(opc){
            case 1:
                printf("Digite o elemento a ser inserido: ");
                scanf("%d", &num);
                insereElemento(&ptRaiz, num);
                break;
            case 2:
                printf("Digite o elemento a ser removido: ");
                scanf("%d", &num);
                removeElemento(&ptRaiz, num);
                break;
            case 3:
                printaEmNivel(ptRaiz);
                /*printaEmOrdem(ptRaiz);*/
                printf("\n");
                break;
            case 4:
                sair = 1;
                break;
        }
    } while(!sair);

    return 0;
}

void initFila(FILA **f){
    (*f) = (FILA *)malloc(sizeof(FILA));
    (*f)->pFinal = (NO *)malloc(sizeof(NO));
    (*f)->pInicio = (NO *)malloc(sizeof(NO));
    if((*f) && (*f)->pFinal && (*f)->pInicio){
        (*f)->pInicio->no_arv = NULL;
        (*f)->pInicio->prox = NULL;
        (*f)->pFinal->no_arv = NULL;
        (*f)->pFinal->prox = NULL;
        (*f)->vazia = 1;
    }
    else
        return;
}

void enqueue(FILA **f, NO_ARVORE *ptNo){
    NO_ARVORE *copiaNo = ptNo;
    if((*f)->pInicio->no_arv == NULL && (*f)->pFinal->no_arv == NULL){    /*Fila vazia*/
        (*f)->pInicio->no_arv = (NO_ARVORE *)malloc(sizeof(NO_ARVORE));
        (*f)->pFinal->no_arv = (NO_ARVORE *)malloc(sizeof(NO_ARVORE));

        if((*f)->pInicio->no_arv && (*f)->pFinal->no_arv){
            (*f)->pInicio = (*f)->pFinal;
            (*f)->pInicio->no_arv = copiaNo;
            (*f)->pFinal->no_arv = copiaNo;
        }
        else
            return;
    }
    else{
        NO *novo = (NO *)malloc(sizeof(NO));
        if(novo){
            NO_ARVORE *no_arv = (NO_ARVORE *)malloc(sizeof(NO_ARVORE));
            no_arv = copiaNo;
            if(no_arv){
                novo->no_arv = no_arv;
                novo->prox = NULL;
                (*f)->pFinal->prox = novo;
                (*f)->pFinal = (*f)->pFinal->prox;
            }
        }
    }
    (*f)->vazia = 0;
}

NO_ARVORE *dequeue(FILA **f){
    NO_ARVORE *no_arv;
    if((*f)->pInicio->no_arv == NULL && (*f)->pFinal->no_arv == NULL){    /*Fila vazia*/
        printf("Fila vazia!\n");
        return NULL;
    }
    else if((*f)->pInicio == (*f)->pFinal){   /*Fila com 1 elemento*/
        NO *copia = (*f)->pInicio;
        no_arv = (*f)->pInicio->no_arv;
        (*f)->pInicio->no_arv = NULL;
        (*f)->pFinal->no_arv = NULL;
        (*f)->vazia = 1;
        free(copia);
    }
    else{     /*Fila com mais de um elemento*/
        NO *copia = (*f)->pInicio;
        no_arv = (*f)->pInicio->no_arv;
        (*f)->pInicio = (*f)->pInicio->prox;
        free(copia);
    }
    return no_arv;
}

void insereElemento(NO_ARVORE **ptRaiz, int chave){
    if((*ptRaiz) == NULL){
        (*ptRaiz) = (NO_ARVORE *)malloc(sizeof(NO_ARVORE));
        if(!ptRaiz)
            return;
        (*ptRaiz)->chave = chave;
        (*ptRaiz)->dir = NULL;
        (*ptRaiz)->esq = NULL;
    }
    else{
        NO_ARVORE *novo = (NO_ARVORE *)malloc(sizeof(NO_ARVORE));
        if(novo == NULL){
            printf("Erro.\n");
            return;
        }
        else{
            NO_ARVORE *pt = (*ptRaiz);
            NO_ARVORE *ant = NULL;
            novo->chave = chave;
            novo->esq = NULL;
            novo->dir = NULL;
            while(pt != NULL){
                ant = pt;
                if(chave < pt->chave)
                    pt = pt->esq;
                else
                    pt = pt->dir;
            }
            if(chave < ant->chave)
                ant->esq = novo;
            else
                ant->dir = novo;
        }
    }
    printf("Elemendo inserido!\n");
}

NO_ARVORE *buscaElemento(NO_ARVORE *ptRaiz, NO_ARVORE **pai, int chave){
    NO_ARVORE *pt = ptRaiz;
    (*pai) = NULL;
    while(pt != NULL && pt->chave != chave){
        (*pai) = pt;
        if(chave < pt->chave)
            pt = pt->esq;
        else
            pt = pt->dir;
    }
    return pt;
}


void removeElemento(NO_ARVORE **ptRaiz, int chave){
    NO_ARVORE *pt, *pai;
    int numFilhos=0;
    NO_ARVORE *filho = NULL;

    pt = buscaElemento((*ptRaiz), &pai, chave);
    if(pt == NULL){
        printf("Elemento nao encontrado!\n");
        return;
    }

    if(pt->esq != NULL){
        numFilhos++;
        filho = pt->esq;
    }
    if(pt->dir != NULL){
        numFilhos++;
        filho = pt->dir;
    }
    if(numFilhos != 2){    /*Se o nó que está sendo removido tem 1 ou 0 filhos*/
        if(pai == NULL)    /*Se estivermos tentando remover a raíz da árvore, o filho será a nova raíz*/
            (*ptRaiz) = filho;
        else{
            if(pt == pai->esq)
                pai->esq = filho;
            else if(pt == pai->dir)
                pai->dir = filho;
        }
        free(pt);
    }
    else{
        NO_ARVORE *elemRemove = pt;
        pai = pt;
        pt = pt->dir;
        while(pt->esq != NULL){
            pai = pt;
            pt = pt->esq;
        }
        elemRemove->chave = pt->chave;
        if(pt == pai->dir)
            pai->dir = pt->dir;
        else
            pai->esq = pt->dir;
        free(pt);
    }

    printf("Elemento removido!\n");
}

void printaEmOrdem(NO_ARVORE *ptRaiz){
    if(ptRaiz == NULL)
        return;
    printaEmOrdem(ptRaiz->esq);
    printf("%d ", ptRaiz->chave);
    printaEmOrdem(ptRaiz->dir);
}

void printaEmNivel(NO_ARVORE *ptRaiz){
    FILA *f1;
    initFila(&f1);
    if(ptRaiz != NULL){
        enqueue(&f1, ptRaiz);
        while(!(f1->vazia)){
            NO_ARVORE *pt = dequeue(&f1);
            printf("%d ", pt->chave);
            if(pt->esq != NULL)
                enqueue(&f1, pt->esq);
            if(pt->dir != NULL)
                enqueue(&f1, pt->dir);
        }
        printf("\n");
    }
    free(f1);
}