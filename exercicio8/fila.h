#ifndef fila_h
#define fila_h

#include <stdlib.h>
#include <stdio.h>
#include "amostra.h"

typedef struct fila Fila;

Fila* criaFila();
void RemoveFilaNoComeco(Fila* f);
void AdicionaFilaNoFinal(Fila* f, Amostra* item);
int getInicio (Fila* f);
int getFim (Fila* f);
int getqtd (Fila* f);
Amostra* RetornaItem(Fila* f, int idx);
int getCapacidade (Fila* f);
void liberaFila(Fila* f);

#endif