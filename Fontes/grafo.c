#include <stdlib.h>
#include "grafo.h"

struct grafo{
	LIS_tppLista vertices;
	LIS_tppLista origens;
	Vertice corrente;
};

/***** Prototipos das funcoes encapsuladas no modulo *****/


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
	VER_DestruirVertice(g->corrente);
	LIS_DestruirLista(g->origens);
	LIS_DestruirLista(g->vertices);
	free(g);
	*endereco = NULL;
}

GRP_tpCondRet GRP_InserirVertice(Grafo grafo, Vertice vertice){
	int chave = 0;
	GRP_tpCondRet cond;
	Vertice v = NULL;
	if(!grafo) return GRP_CondRetGrafoNaoExiste;
	if(!vertice) return GRP_CondRetOK;

	//listas de vertices
	if(!grafo->vertices) grafo->vertices = LIS_CriarLista((void(*)(void *pDado))VER_DestruirVertice);
	if(!grafo->origens) grafo->origens = LIS_CriarLista((void(*)(void *pDado))VER_DestruirVertice);
	//verificando a criacao correta de todos os dados
	if(!grafo->vertices || !grafo->origens) return GRP_CondRetFaltouMemoria;

	//verifica se a chave do vertice ja' existe no grafo. Nesse caso retorna uma condicao de erro.
	VER_getChave(vertice, &chave);
	cond = VerticedeChave(grafo, chave, &v);
	if(cond == GRP_CondRetOK) return GRP_CondRetErroEstrutura;

	//adiciona o vertice e seus vizinhos na lista de vertices.


	//verifica se o vertice e' uma origem nova percorrendo a lista atual de origens e determinando se o vertice a ser inserido
	//pode ser alcancado a partir de alguma origem. Se ele nao puder, sera uma nova origem.


	return GRP_CondRetOK;
}

//assertiva de entrada: o elemento corrente da lista de chaves do grafo esta na sua posicao inicial
//nota: nao e' possivel aqui utilizar a funcao de procura da lista, pois ele nao compara valores mas apenas ponteiros.
GRP_tpCondRet VerticedeChave(Grafo grafo, int chave, Vertice* endereco){
	Vertice corr = NULL;
	int chaveCorr = 0;
	LIS_tpCondRet cond = LIS_CondRetOK;
	if(!grafo) return GRP_CondRetGrafoNaoExiste;
	if(!grafo->vertices) return GRP_CondRetGrafoVazio;

	while(cond != LIS_CondRetFimLista){
		//obter valor atual
		corr = (Vertice) LIS_ObterValor(grafo->vertices);
		//se nao houver a lista estara vazia. Neste caso, o grafo tambem.
		if(!corr) return GRP_CondRetGrafoVazio;
		//comparar as chaves para ver se achou
		VER_getChave(corr, &chaveCorr);
		if(chaveCorr == chave){
			*endereco = corr;
			return GRP_CondRetOK;
		}
		//pular para o proximo elemento da lista
		cond = LIS_AvancarElementoCorrente(grafo->vertices, 1);
		if(cond == LIS_CondRetListaVazia) return GRP_CondRetGrafoVazio;
	}
	//caso o vertice nao seja encontrado, um erro de estrutura e' retornado.
	return GRP_CondRetErroEstrutura;
}

/*****  Codigo das funcoes encapsuladas no modulo  *****/

