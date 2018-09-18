#include <stdlib.h>
#include "grafo.h"
#include "LISTA.H"

struct grafo{
	LIS_tppLista vertices;
	LIS_tppLista origens;
	//chaves ja utilizadas
	LIS_tppLista chaves;
	Vertice corrente;
};

/***** Prototipos das funcoes encapsuladas no modulo *****/

static char chaveNoGrafo(Grafo g, int chave);


/************************Codigo das funcoes exportadas pelo modulo******************************/

GRP_tpCondRet GRP_CriarGrafo(Grafo* endereco){
	if(!endereco) return GRP_CondRetOK;
	if(*endereco) GRP_DestruirGrafo(endereco);

	*endereco = (Grafo) malloc(sizeof(struct grafo));
	if(!(*endereco)) return GRP_CondRetFaltouMemoria;
	(*endereco)->vertices = (*endereco)->origens = NULL;
	(*endereco)->corrente = NULL;

	return GRP_CondRetOK;
}

void GRP_DestruirGrafo(Grafo* endereco){
	Grafo g;
	if(!endereco || !(*endereco)) return;
	g = *endereco;
	VER_DestruirVertice(&g->corrente);
	LIS_DestruirLista(g->origens);
	LIS_DestruirLista(g->vertices);
	free(g);
	*endereco = NULL;
}

GRP_tpCondRet GRP_InserirVertice(Grafo grafo, Vertice vertice){
	int chave = 0;
	if(!grafo) return GRP_CondRetGrafoNaoExiste;
	if(!vertice) return GRP_CondRetOK;

	//listas de ENDERECOS de vertices
	if(!grafo->vertices) grafo->vertices = LIS_CriarLista((void(*)(void *pDado))VER_DestruirVertice);
	if(!grafo->origens) grafo->origens = LIS_CriarLista((void(*)(void *pDado))VER_DestruirVertice);
	//lista de enderecos de chaves, que referenciam as chaves dos vertices. Nao e' necessario apagar as chaves junto com a lista.
	if(!grafo->chaves) grafo->chaves = LIS_CriarLista(NULL);
	//verificando a criacao correta de todos os dados
	if(!grafo->vertices || !grafo->origens || !grafo->chaves) return GRP_CondRetFaltouMemoria;

	//verifica se a chave do vertice ja' existe no grafo. Nesse caso retorna uma condicao de erro.
	VER_getChave(vertice, &chave);
	if(chaveNoGrafo(grafo, chave)) return GRP_CondRetErroEstrutura;

	//adiciona o vertice e seus vizinhos na lista de vertices, e sua chave na lista de chaves.

	//verifica se o vertice e' uma origem nova percorrendo a lista atual de origens e determinando se o vertice a ser inserido
	//pode ser alcancado a partir de alguma origem. Se ele nao puder, sera uma nova origem.


	return GRP_CondRetOK;
}

/*****  Codigo das funcoes encapsuladas no modulo  *****/
//assertiva de entrada: o elemento corrente da lista de chaves do grafo esta na sua posicao inicial
//nota: nao e' possivel aqui utilizar a funcao de procura da lista, pois ele nao compara valores mas apenas ponteiros.
static char chaveNoGrafo(Grafo g, int chave){
	int corr = 0;
	LIS_tpCondRet cond = LIS_CondRetOK;
	if(!g || !g->chaves) return 0;
	while(cond != LIS_CondRetFimLista){
		//obter valor atual
		corr = *((int*) LIS_ObterValor(g->chaves));
		if(corr == chave) return 1;
		//pular para o proximo elemento da lista
		cond = LIS_AvancarElementoCorrente(g->chaves, 1);
	}
	return 0;
}
