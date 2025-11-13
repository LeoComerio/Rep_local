#include "posto.h"
#include <string.h>
#include "fila.h"

/*Tipo que define um Posto de Saúde (tipo opaco)
 *Um posto deve ter os seguintes atributos:
 * * Nome do Posto
 * * Uma FILA de amostras para exame não processadas
 * * Uma FILA de amostras processadas com resultado POSITIVO
 * * Uma FILA de amostras processadas com resultado NEGATIVO
 * */
 
 struct posto{
    Fila* Nao_Processou;
    Fila* Positivo;
    Fila* Negativo;
    char nome[100];
};

/* Cria um posto de saúde, ainda vazio, com as 3 filas, vazias
* inputs: nome do posto de saúde.
* output: posto alocado e vazio, com filas de amostras ainda vazias
* pre-condicao: nao tem
* pos-condicao: posto alocado e vazio, com filas de amostras alocadas e vazias
 */
Posto* inicPosto(char* nome){
    Posto* p=malloc(sizeof(Posto));
    p->Nao_Processou = criaFila();
    p->Positivo = criaFila();
    p->Negativo = criaFila();
    strcpy(p->nome,nome);
    return p;
}

/* Imprime os dados do Posto no seguinte formato:
 
 Dados do Posto: <nome do posto>
 Amostras não processadas
 <fila de amostras não processadas - do início ao fim>
 
 Amostras com resultados positivos
 <fila de amostras positivas - do início ao fim>
 
 Amostra com resultados negativos
 <fila de amostras negativas - do início ao fim>
 
* inputs: referencia para o posto
* output: nenhum
* pre-condicao: posto alocado
* pos-condicao: dados do posto não são alterados
 */
void imprimePosto(Posto* posto) {
    if (posto == NULL) {
        printf("Posto inexistente!\n");
        return;
    }

    printf("Dados do Posto: %s\n", posto->nome);

    printf("\nAmostras não processadas:\n");
    for (int i = 0; i < getqtd(posto->Nao_Processou); i++) {
        int idx = (getInicio(posto->Nao_Processou) + i) % getCapacidade(posto->Nao_Processou);
        imprimeAmostra(RetornaItem(posto->Nao_Processou, idx));
    }
    printf("\nAmostras com resultados positivos:\n");
    for (int i = 0; i < getqtd(posto->Positivo); i++) {
        int idx = (getInicio(posto->Positivo) + i) % getCapacidade(posto->Positivo);
        imprimeAmostra(RetornaItem(posto->Positivo, idx));
    }
    printf("\nAmostras com resultados negativos:\n");
    for (int i = 0; i < getqtd(posto->Negativo); i++) {
        int idx = (getInicio(posto->Negativo) + i) % getCapacidade(posto->Negativo);
        imprimeAmostra(RetornaItem(posto->Negativo, idx));
    }

    printf("\n");
}


/* Simula a realização de uma coleta de material para teste
 * A função deve criar uma amostra e fazer as devidas atribuições à amostra
 * Deve-se inserir a amostra na fila de "não processados"
 * ATENÇÃO: se a pessoa for idosa (idade>=60), ela deve ir para o início da fila de não processados
* inputs: referência para o posto de saúde, o nome do dono da coleta e a idade da pessa
* output: nenhum
* pre-condicao: posto válido, nome da pessoa válido
* pos-condicao: Amostra alocada e inserida na fila de amostras não processadas
 */
void realizaColeta(Posto* posto, char* pessoa, int idade){
    if(!posto || !pessoa){
        printf("Nome da pessoa invalido ou posto invalido!\n");
        return;
    }
    Amostra* coleta= inicAmostra(pessoa, idade);
    registraResultado(coleta,0);
    AdicionaFilaNoFinal(posto->Nao_Processou, coleta);
}


/* Essa função simula o processamento (testagem) das amostras e atualiza os resultados nas amostras. Deve-se usar a constante LIMITE_CARGA_VIRAL para definir positivo e negativo.
* inputs: referência do posto de saúde.
* output: nenhum
* pre-condicao: posto válido
* pos-condicao: amostras foram devidamente processadas; fila de amostras não processadas deve ficar vazia; fila de amostras positivas deve conter as amostras que testaram positivo (idosos na frente); fila de amostras negativas deve conter as amostras que testaram negativo (idosos na frente).
 */

void processaLoteAmostras(Posto* posto){
    int i=0;
    while(getqtd(posto->Nao_Processou)>0){
        Amostra* atual = RetornaItem(posto->Nao_Processou, getInicio(posto->Nao_Processou));
        if(retornaCargaViral(atual)>=LIMITE_CARGA_VIRAL){
        AdicionaFilaNoFinal(posto->Positivo, atual);
        registraResultado(atual, 1);
        RemoveFilaNoComeco(posto->Nao_Processou);
        continue;
        }
        if(retornaCargaViral(atual)<LIMITE_CARGA_VIRAL){
        AdicionaFilaNoFinal(posto->Negativo, atual);
        registraResultado(atual, 0);
        RemoveFilaNoComeco(posto->Nao_Processou);
        continue;
        }
    }
}

/* Libera toda a memória alocada para o posto de saúde
* inputs: referência do posto de saúde.
* output: nenhum
* pre-condicao: posto válido
* pos-condicao: Memória para a string nome liberada; memória para as 3 filas liberada, memoria do posto liberada
 */
void liberaPosto(Posto* posto){
    if(posto==NULL){
        return;
    }
    liberaFila(posto->Nao_Processou);
    liberaFila(posto->Positivo);
    liberaFila(posto->Negativo);
    free(posto);
}
