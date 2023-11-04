#include <stdio.h>
#include <stdlib.h>

/*Utilizando conjuntos disjuntos para resolver este problema sobre grafos*/
typedef struct _Conjunto{
    struct _Conjunto* pai;    /*Ponteiro para o próximo elemento do conjunto*/
    int relacoes;             /*Número de relações que este elemento possui*/
} Conjunto;

/*Função para inicializar um conjunto*/
Conjunto* Init() {
    Conjunto* ptr = malloc(sizeof(Conjunto));
    ptr->pai = ptr;
    ptr->relacoes = 0;
    return ptr;
}

/*Função para encontrar o representante do conjunto*/
Conjunto* Find(Conjunto* ptr){
    if(ptr->pai == ptr)
        return ptr;
    ptr->pai = Find(ptr->pai);
    return ptr->pai;
}

/*Função para unir dois conjuntos*/
void Union(Conjunto* a, Conjunto* b){
    /*Achando os representantes dos elementos A e B*/
    Conjunto* RepA = Find(a);
    Conjunto* RepB = Find(b);

    if(RepA->relacoes > RepB->relacoes) {
        RepB->pai = RepA;
        RepA->relacoes++;
    }
    else{
        RepA->pai = RepB;
        RepB->relacoes++;
    }
}

/*Função para verificar se dois elementos estão no mesmo conjunto*/
int isRelacionado(Conjunto *elem1, Conjunto *elem2){
    if(Find(elem1) == Find(elem2))
        return 1;
    return 0;
}

int main() {
    int i, numVertices, v1, v2, pesoAresta, somaPesos=0;
    Conjunto **conjunto;

    scanf("%d", &numVertices);
    conjunto = (Conjunto **) malloc(sizeof(Conjunto *) * numVertices);
    for (i = 0; i < numVertices; i++){
        conjunto[i] = Init();
    }

    /*while (scanf("%d", &v1) != EOF) {*/      /*Loop para os inputs do usuário*/
    while (1) {
        scanf("%d %d %d", &v1, &v2, &pesoAresta);
        if(v1 == 99)
            break;
        if(!isRelacionado(conjunto[v1-1], conjunto[v2-1])) {   /*Se os elementos já estiverem no mesmo conjunto, não vou uni-los (eu só preciso desta verificação. Como os pesos das arestas são fornecidos de forma crescente, eu tenho certeza de que, se já existe relação entre dois elementos, esta relação já tem caminho mínimo)*/
            Union(conjunto[v1-1], conjunto[v2-1]);
            somaPesos += pesoAresta;
        }
    }

    printf("%d\n", somaPesos);

    return 0;
}