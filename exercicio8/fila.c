#include "fila.h"
#include "amostra.h"
#define TAM_inicial 1

struct fila{
    int inicio;
    int fim;
    Amostra** item_da_fila;
    int qtd;
    int capacidade;
};

Fila* criaFila(){
    Fila* f =malloc(sizeof(Fila));
    if(f==NULL){
        printf("Fila não alocada!\n");
        exit(1);
    }
    f->item_da_fila = malloc(sizeof(Amostra*) * TAM_inicial);
    f->capacidade=TAM_inicial;
    f->qtd=0;
    f->inicio=0;
    f->fim=-1;
    return f;
}
int getInicio (Fila* f){
    return f->inicio;
}
int getFim (Fila* f){
    return f->fim;
}
int getqtd (Fila* f){
    return f->qtd;
}
int getCapacidade (Fila* f){
    return f->capacidade;
}
void RemoveFilaNoComeco(Fila* f) {
    if (f == NULL) {
        printf("Erro: fila inexistente!\n");
        return;
    }

    if (f->qtd == 0) {
        printf("Fila vazia, nada para remover.\n");
        return;
    }

    //liberaAmostra(f->item_da_fila[f->inicio]);
    f->inicio = (f->inicio + 1) % f->capacidade;
    f->qtd--;
    if (f->qtd == 0) {
        f->inicio = 0;
        f->fim = -1;
    }
}
void AdicionaFilaNoFinal(Fila* f, Amostra* item){
    if((f->qtd)<f->capacidade){
        f->qtd++;
        f->fim = (f->fim + 1) % f->capacidade; 
        f->item_da_fila[f->fim]=item;
    }
    else{
        int antiga_capacidade=f->capacidade;
        f->capacidade=f->capacidade*2;
        Amostra** fila_temporaria=malloc(f->capacidade* sizeof(Amostra*));
        for(int i=0; i<f->qtd; i++){
            fila_temporaria[i]=f->item_da_fila[(f->inicio + i) % antiga_capacidade];
        }

        free(f->item_da_fila);
        f->item_da_fila = fila_temporaria;
        f->inicio = 0;
        f->fim = f->qtd - 1;
        if(retornaIdade(item)<60){
            f->fim = (f->fim + 1) % f->capacidade;
            f->item_da_fila[f->fim] = item;
            f->qtd++;
        }
        if(retornaIdade(item)>=60){
            f->inicio = (f->inicio - 1 + f->capacidade) % f->capacidade;
            f->item_da_fila[f->inicio] = item;
            f->qtd++;
        }
    }
}
Amostra* RetornaItem(Fila* f, int idx){
    return f->item_da_fila[idx];
}
void liberaFila(Fila* f){
    if(f==NULL){
        return;
    }
    for (int i = 0; i < f->qtd; i++) {
        int indice = (f->inicio + i) % f->capacidade;
        liberaAmostra(f->item_da_fila[indice]);
    }
    free(f->item_da_fila);
    free(f);
}
