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
	LIS_tpCondRet lcond = LIS_CondRetOK;
	VER_tpCondRet vcond;
	Vertice v = NULL;
	LIS_tppLista sucessores = NULL;
	LIS_tppLista antecessores = NULL;
	Aresta atual = NULL;
	int chaves[2];
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

	//verifica vizinhos do vertice.
	//verifica tambem se o vertice e' uma origem nova.
	//para fazer isto basta verificar que ele nao tem vizinhos, pois se os tiver nao sera uma nova origem.
	
	VER_getSucessores(vertice, &sucessores);
	VER_getAntecessores(vertice, &antecessores);
	if(!LIS_ObterValor(sucessores) && !LIS_ObterValor(antecessores)){
		LIS_InserirElementoApos(grafo->vertices, vertice);
		LIS_InserirElementoApos(grafo->origens, vertice);
		return GRP_CondRetOK;
	}

	//se ele nao for uma origem temos que verificar se seus vizinhos existem.
	IrInicioLista(sucessores);
	//se retornar null e' porque a lista esta vazia ou nula.
	atual = (Aresta) LIS_ObterValor(sucessores);
	while(atual && lcond != LIS_CondRetFimLista){
		VER_GetChaves(atual, &chaves);
		cond = VerticedeChave(grafo, chaves[1], &v);
		//se o vizinho atual nao for encontrado, devemos retornar um erro de estrutura.
		if(cond == GRP_CondRetErroEstrutura) return GRP_CondRetErroEstrutura;
		//se o encontrar-mos, devemos tambem inserir a aresta atual no grafo inserindo-a no vizinho atual. 
		//como indicado na documentacao da funcao de insercao, ela nao permite redundancias.
		vcond = VER_InserirAresta(v, atual);
		//devemos tratar a condicao de falta de memoria
		if(vcond == VER_CondRetFaltouMemoria) return GRP_CondRetFaltouMemoria;
		//passar para o proximo vizinho.
		lcond = LIS_AvancarElementoCorrente(sucessores, 1);
		atual = (Aresta) LIS_ObterValor(sucessores);
	}

	//reinicializa lcond
	lcond = LIS_CondRetOK;
	//faz o mesmo para os antecessores
	IrInicioLista(antecessores);
	atual = (Aresta) LIS_ObterValor(antecessores);
	while(atual && lcond != LIS_CondRetFimLista){
		VER_GetChaves(atual, &chaves);
		cond = VerticedeChave(grafo, chaves[0], &v);
		//se o vizinho atual nao for encontrado, devemos retornar um erro de estrutura.
		if(cond == GRP_CondRetErroEstrutura) return GRP_CondRetErroEstrutura;
		//se o encontrar-mos, devemos tambem inserir a aresta atual no grafo inserindo-a no vizinho atual. 
		vcond = VER_InserirAresta(v, atual);
		//devemos tratar a condicao de falta de memoria
		if(vcond == VER_CondRetFaltouMemoria) return GRP_CondRetFaltouMemoria;
		//passar para o proximo vizinho.
		lcond = LIS_AvancarElementoCorrente(antecessores, 1);
		atual = (Aresta) LIS_ObterValor(antecessores);
	}

	//finalmente a insercao.
	LIS_InserirElementoApos(grafo->vertices, vertice);
	//atualizar corrente
	grafo->corrente = vertice;
	return GRP_CondRetOK;
}

GRP_tpCondRet GRP_InserirAresta(Grafo grafo, Aresta aresta){
	int chaves[2];
	if(!grafo) return GRP_CondRetGrafoNaoExiste;
	if(!aresta) return GRP_CondRetOK;
	VER_GetChaves(aresta, &chaves);

}

//assertiva de entrada: o elemento corrente da lista de chaves do grafo esta na sua posicao inicial
//nota: nao e' possivel aqui utilizar a funcao de procura da lista, pois ele nao compara valores mas apenas ponteiros.
GRP_tpCondRet VerticedeChave(Grafo grafo, int chave, Vertice* endereco){
	Vertice corr = NULL;
	int chaveCorr = 0;
	LIS_tpCondRet cond = LIS_CondRetOK;
	if(!grafo) return GRP_CondRetGrafoNaoExiste;
	if(!grafo->vertices) return GRP_CondRetGrafoVazio;

	//asseguramo-nos de testar todos os vertices
	IrInicioLista(grafo->vertices);

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

	//por padrao esperamos que o vertice corrente seja o ultimo para insercao rapida, entao corrigimos as movimentacoes
	//feitas na lista.
	IrFinalLista(grafo->vertices);

	//caso o vertice nao seja encontrado, um erro de estrutura e' retornado.
	return GRP_CondRetErroEstrutura;
}

/*****  Codigo das funcoes encapsuladas no modulo  *****/

