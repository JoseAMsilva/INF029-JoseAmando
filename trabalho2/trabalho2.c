#include <stdio.h>
#include <stdlib.h>
#define TAM 10

#include "trabalho2.h"

typedef struct estrutra {
    int *listaAux;
    int tam;
    int qtde;
}estrutra;

estrutra vetorPrincipal[TAM];

int posValida(int posicao)
{
    return (posicao >= 0 && posicao < TAM) ? 1 : 0;
}

int verificaEspaco(int posicao)
{
    return vetorPrincipal[posicao].qtde < vetorPrincipal[posicao].tam ? 1 : 0;
}

int existeEstrutura(int posicao)
{
    if (!posValida(posicao))
        return 0;
    return (vetorPrincipal[posicao].listaAux != NULL) ? 1 : 0;
}

void sort(int arr[], int n)
{
    int i, j, min_idx;
    for (i = 0; i < n - 1; i++)
    {
        min_idx = i;
        for (j = i + 1; j < n; j++)
            if (arr[j] < arr[min_idx])
                min_idx = j;
        int temp = arr[min_idx];
        arr[min_idx] = arr[i];
        arr[i] = temp;
    }
}

int getNumeroDeElementos(){
    int total = 0;
    for (int i = 0; i < TAM; i++){
        if (existeEstrutura(i)){
            total += vetorPrincipal[i].qtde;
        }
    } 
    return total;
}

void inserirListaEncadeadaComCabecote(No *cabecote, int valor){
    No *novoNo = (No *)malloc(sizeof(No));
    novoNo->conteudo = valor;
    novoNo->prox = NULL;

    No *atual = cabecote;

    if (atual->prox == NULL){
        atual->prox = novoNo;
        return;
    }

    while (atual->prox != NULL){
        atual = atual->prox;
    }
    atual->prox = novoNo;
}

/*
Objetivo: criar estrutura auxiliar na posição 'posicao'.
com tamanho 'tamanho'

Rertono (int)
    SUCESSO - criado com sucesso
    JA_TEM_ESTRUTURA_AUXILIAR - já tem estrutura na posição
    POSICAO_INVALIDA - Posição inválida para estrutura auxiliar
    SEM_ESPACO_DE_MEMORIA - Sem espaço de memória
    TAMANHO_INVALIDO - o tamanho deve ser maior ou igual a 1
*/
int criarEstruturaAuxiliar(int posicao, int tamanho)
{
    posicao--;
    
    // a posicao pode já existir estrutura auxiliar
    if (existeEstrutura(posicao))
        return JA_TEM_ESTRUTURA_AUXILIAR;

    // se posição é um valor válido {entre 1 e 10}
    if (!posValida(posicao))
        return POSICAO_INVALIDA;

    // o tamanho nao pode ser menor que 1
    if (tamanho < 1)
        return TAMANHO_INVALIDO;

    // o tamanho ser muito grande
    int *p = (int *)malloc(tamanho * sizeof(int));
    if (p == NULL)
        return SEM_ESPACO_DE_MEMORIA;

    // deu tudo certo, crie
    else
    {
        free(p); // libera o ponteiro temporario
        vetorPrincipal[posicao].listaAux = (int *)malloc(tamanho * sizeof(int));
        vetorPrincipal[posicao].tam = tamanho;
        vetorPrincipal[posicao].qtde = 0;
        return SUCESSO;
    }
}


/*
Objetivo: inserir número 'valor' em estrutura auxiliar da posição 'posicao'
Rertono (int)
    SUCESSO - inserido com sucesso
    SEM_ESPACO - não tem espaço
    SEM_ESTRUTURA_AUXILIAR - Não tem estrutura auxiliar
    POSICAO_INVALIDA - Posição inválida para estrutura auxiliar
CONSTANTES
*/
int inserirNumeroEmEstrutura(int posicao, int valor)
{
    posicao--;

    if (!posValida(posicao))
        return POSICAO_INVALIDA;
    else
    {
        if (existeEstrutura(posicao))
        {
            if (verificaEspaco(posicao))
            {
                vetorPrincipal[posicao].listaAux[vetorPrincipal[posicao].qtde] = valor;
                vetorPrincipal[posicao].qtde++;
                return SUCESSO;
            }
            else
            {
                return SEM_ESPACO;
            }
        }
        else
        {
            return SEM_ESTRUTURA_AUXILIAR;
        }
    }
}

/*
Objetivo: excluir o numero 'valor' da estrutura auxiliar no final da estrutura.
ex: suponha os valores [3, 8, 7, 9,  ,  ]. Após excluir, a estrutura deve ficar da seguinte forma [3, 8, 7,  ,  ,  ].
Obs. Esta é uma exclusão lógica

Rertono (int)
    SUCESSO - excluido com sucesso
    ESTRUTURA_AUXILIAR_VAZIA - estrutura vazia
    SEM_ESTRUTURA_AUXILIAR - Não tem estrutura auxiliar
    POSICAO_INVALIDA - Posição inválida para estrutura auxiliar
*/
int excluirNumeroDoFinaldaEstrutura(int posicao)
{
    posicao--;
    if (!posValida(posicao))
        return POSICAO_INVALIDA;
    if (!existeEstrutura(posicao))
        return SEM_ESTRUTURA_AUXILIAR;
    if (vetorPrincipal[posicao].qtde == 0)
        return ESTRUTURA_AUXILIAR_VAZIA;

    vetorPrincipal[posicao].qtde--;
    return SUCESSO;
}

/*
Objetivo: excluir o numero 'valor' da estrutura auxiliar da posição 'posicao'.
Caso seja excluido, os números posteriores devem ser movidos para as posições anteriores
ex: suponha os valores [3, 8, 7, 9,  ,  ] onde deve ser excluido o valor 8. A estrutura deve ficar da seguinte forma [3, 7, 9,  ,  ,  ]
Obs. Esta é uma exclusão lógica
Rertono (int)
    SUCESSO - excluido com sucesso 'valor' da estrutura na posição 'posicao'
    ESTRUTURA_AUXILIAR_VAZIA - estrutura vazia
    SEM_ESTRUTURA_AUXILIAR - Não tem estrutura auxiliar
    NUMERO_INEXISTENTE - Número não existe
    POSICAO_INVALIDA - Posição inválida para estrutura auxiliar

*/
int excluirNumeroEspecificoDeEstrutura(int posicao, int valor)
{
    posicao--;
    if (!posValida(posicao))
        return POSICAO_INVALIDA;
    if (!existeEstrutura(posicao))
        return SEM_ESTRUTURA_AUXILIAR;
    if (vetorPrincipal[posicao].qtde == 0)
        return ESTRUTURA_AUXILIAR_VAZIA;
    for (int i = 0; i < vetorPrincipal[posicao].qtde; i++)
    {
        if (vetorPrincipal[posicao].listaAux[i] == valor)
        {
            for (int j = i; j < vetorPrincipal[posicao].qtde - 1; j++)
            {
                vetorPrincipal[posicao].listaAux[j] = vetorPrincipal[posicao].listaAux[j + 1];
            }
            vetorPrincipal[posicao].qtde--;
            return SUCESSO;
        }
    }
    return NUMERO_INEXISTENTE;
}

/*
Objetivo: retorna os números da estrutura auxiliar da posição 'posicao (1..10)'.
os números devem ser armazenados em vetorAux

Retorno (int)
    SUCESSO - recuperado com sucesso os valores da estrutura na posição 'posicao'
    SEM_ESTRUTURA_AUXILIAR - Não tem estrutura auxiliar
    POSICAO_INVALIDA - Posição inválida para estrutura auxiliar
*/
int getDadosEstruturaAuxiliar(int posicao, int vetorAux[])
{
    posicao--;
    if (!posValida(posicao))
        return POSICAO_INVALIDA;

    if (!existeEstrutura(posicao))
        return SEM_ESTRUTURA_AUXILIAR;
    
    for (int i = 0; i < vetorPrincipal[posicao].qtde; i++)
    {
        vetorAux[i] = vetorPrincipal[posicao].listaAux[i];
    }

    return SUCESSO;
}

/*
Objetivo: retorna os números ordenados da estrutura auxiliar da posição 'posicao (1..10)'.
os números devem ser armazenados em vetorAux

Rertono (int)
    SUCESSO - recuperado com sucesso os valores da estrutura na posição 'posicao (1..10)'
    SEM_ESTRUTURA_AUXILIAR - Não tem estrutura auxiliar
    POSICAO_INVALIDA - Posição inválida para estrutura auxiliar
*/
int getDadosOrdenadosEstruturaAuxiliar(int posicao, int vetorAux[])
{

    posicao--;
    if (!posValida(posicao))
        return POSICAO_INVALIDA;
    if (!existeEstrutura(posicao))
        return SEM_ESTRUTURA_AUXILIAR;

    for (int i = 0; i < vetorPrincipal[posicao].qtde; i++)
    {
        vetorAux[i] = vetorPrincipal[posicao].listaAux[i];
    }

    sort(vetorAux, vetorPrincipal[posicao].qtde);
    
    return SUCESSO;
}

/*
Objetivo: retorna os números de todas as estruturas auxiliares.
os números devem ser armazenados em vetorAux

Rertono (int)
    SUCESSO - recuperado com sucesso os valores da estrutura na posição 'posicao'
    TODAS_ESTRUTURAS_AUXILIARES_VAZIAS - todas as estruturas auxiliares estão vazias
*/
int getDadosDeTodasEstruturasAuxiliares(int vetorAux[])
{
    int vazia = 1;
    for (int i = 0; i < TAM; i++)
    {
        if (existeEstrutura(i) && vetorPrincipal[i].qtde > 0)
        {
            vazia = 0;
            break;
        }
    }

    if (vazia)
        return TODAS_ESTRUTURAS_AUXILIARES_VAZIAS;

    for (int i = 0, k = 0; i < TAM; i++)
    {
        if (existeEstrutura(i))
        {
            for (int j = 0; j < vetorPrincipal[i].qtde; j++)
            {
                vetorAux[k] = vetorPrincipal[i].listaAux[j];
                k++;
            }
        }
    }

    return SUCESSO;
}

/*
Objetivo: retorna os números ordenados de todas as estruturas auxiliares.
os números devem ser armazenados em vetorAux

Rertono (int)
    SUCESSO - recuperado com sucesso os valores da estrutura na posição 'posicao'
    TODAS_ESTRUTURAS_AUXILIARES_VAZIAS - todas as estruturas auxiliares estão vazias
*/
int getDadosOrdenadosDeTodasEstruturasAuxiliares(int vetorAux[])
{
    int vazia = 1;
    for (int i = 0; i < TAM; i++)
    {
        if (existeEstrutura(i) && vetorPrincipal[i].qtde > 0)
        {
            vazia = 0;
            break;
        }
    }

    if (vazia)
        return TODAS_ESTRUTURAS_AUXILIARES_VAZIAS;

    int k = 0;

    for (int i = 0; i < TAM; i++)
    {
        if (existeEstrutura(i))
        {
            for (int j = 0; j < vetorPrincipal[i].qtde; j++)
            {
                vetorAux[k] = vetorPrincipal[i].listaAux[j];
                k++;
            }
        }
    }

    sort(vetorAux, k);

    return SUCESSO;
}

/*
Objetivo: modificar o tamanho da estrutura auxiliar da posição 'posicao' para o novo tamanho 'novoTamanho' + tamanho atual
Suponha o tamanho inicial = x, e novo tamanho = n. O tamanho resultante deve ser x + n. Sendo que x + n deve ser sempre >= 1

Rertono (int)
    SUCESSO - foi modificado corretamente o tamanho da estrutura auxiliar
    SEM_ESTRUTURA_AUXILIAR - Não tem estrutura auxiliar
    POSICAO_INVALIDA - Posição inválida para estrutura auxiliar
    NOVO_TAMANHO_INVALIDO - novo tamanho não pode ser negativo
    SEM_ESPACO_DE_MEMORIA - erro na alocação do novo valor
*/
int modificarTamanhoEstruturaAuxiliar(int posicao, int novoTamanho)
{
    posicao--;
    int tamanhoResultante = vetorPrincipal[posicao].tam + novoTamanho;

    if (!posValida(posicao))
        return POSICAO_INVALIDA;

    if (!existeEstrutura(posicao))
        return SEM_ESTRUTURA_AUXILIAR;

    if (tamanhoResultante < 1)
        return NOVO_TAMANHO_INVALIDO;

    if (tamanhoResultante < 1)
        return NOVO_TAMANHO_INVALIDO;

    if (novoTamanho < 0){
        for (int ndx = 0; ndx <= tamanhoResultante; ndx++){
            excluirNumeroDoFinaldaEstrutura(posicao + 1);
        }
    }

    if (novoTamanho < vetorPrincipal[posicao].tam && novoTamanho > 0){
        vetorPrincipal[posicao].listaAux = realloc(vetorPrincipal[posicao].listaAux, novoTamanho);
        vetorPrincipal[posicao].tam = novoTamanho;
    }

    vetorPrincipal[posicao].listaAux = realloc(vetorPrincipal[posicao].listaAux, tamanhoResultante);
    vetorPrincipal[posicao].tam = tamanhoResultante;

    if (vetorPrincipal[posicao].listaAux == NULL)
        return SEM_ESPACO_DE_MEMORIA;

    return SUCESSO;
}

/*
Objetivo: retorna a quantidade de elementos preenchidos da estrutura auxiliar da posição 'posicao'.

Retorno (int)
    POSICAO_INVALIDA - posição inválida
    SEM_ESTRUTURA_AUXILIAR - sem estrutura auxiliar
    ESTRUTURA_AUXILIAR_VAZIA - estrutura auxiliar vazia
    Um número int > 0 correpondente a quantidade de elementos preenchidos da estrutura
*/
int getQuantidadeElementosEstruturaAuxiliar(int posicao)
{
    posicao--;
    if (!posValida(posicao))
        return POSICAO_INVALIDA;

    if (!existeEstrutura(posicao))
        return SEM_ESTRUTURA_AUXILIAR;

    if (vetorPrincipal[posicao].qtde == 0)
        return ESTRUTURA_AUXILIAR_VAZIA;

    return vetorPrincipal[posicao].qtde;
}

/*
Objetivo: montar a lista encadeada com cabeçote com todos os números presentes em todas as estruturas.

Retorno (No*)
    NULL, caso não tenha nenhum número nas listas
    No*, ponteiro para o início da lista com cabeçote
*/
No *montarListaEncadeadaComCabecote()
{
    int total = getNumeroDeElementos();
    
    int aux[total];

    No *cabecote = (No *)malloc(sizeof(No));
    cabecote->prox = NULL;

    if (getDadosDeTodasEstruturasAuxiliares(aux) != SUCESSO)
        return NULL;

    for (int i = 0; i < total; i++)
    {
        inserirListaEncadeadaComCabecote(cabecote, aux[i]);
    }

    return cabecote;
}

/*
Objetivo: retorna os números da lista enceada com cabeçote armazenando em vetorAux.
Retorno void
*/
void getDadosListaEncadeadaComCabecote(No *inicio, int vetorAux[])
{
    No *atual = inicio->prox;
    int i = 0;
    while (atual != NULL)
    {
        vetorAux[i] = atual->conteudo;
        atual = atual->prox;
        i++;
    }
}

/*
Objetivo: Destruir a lista encadeada com cabeçote a partir de início.
O ponteiro inicio deve ficar com NULL.

Retorno 
    void.
*/
void destruirListaEncadeadaComCabecote(No **inicio)
{
    No *atual = (*inicio);
    No *proxNo;

    while (atual != NULL)
    {
        proxNo = atual->prox;
        free(atual);
        atual = proxNo;
    }

    *inicio = NULL;
}

/*
Objetivo: inicializa o programa. deve ser chamado ao inicio do programa 

*/

void inicializar()
{
    for (int i = 0; i < TAM; i++)
    {
        vetorPrincipal[i].listaAux = NULL;
        vetorPrincipal[i].qtde = 0;
        vetorPrincipal[i].tam = 0;
    }
}

/*
Objetivo: finaliza o programa. deve ser chamado ao final do programa 
para poder liberar todos os espaços de memória das estruturas auxiliares.

*/

void finalizar()
{
    for (int i = 0; i < TAM; i++)
    {
        if (vetorPrincipal[i].listaAux != NULL)
        {
            free(vetorPrincipal[i].listaAux);
            vetorPrincipal[i].listaAux = NULL;
            vetorPrincipal[i].qtde = 0;
            vetorPrincipal[i].tam = 0;
        }
    }
}
