/***************************************************************************
*
*  $MCD Modulo de implementacao: Modulo Grafo
*
*  Arquivo gerado:              GRAFO.C
*  Letras identificadoras:      GRP
*
*  Nome da base de software:    Segundo Trabalho de Programacao Modular
*
*  Projeto: Disciplinas INF 1628 / 1301
*  Gestor:  DI/PUC-Rio
*  Autores: lcrv - Luiz Carlos R Viana
*
*  $HA Historico de evolucao:
*     Versao  Autor    Data     Observacoes
*	  1.2	   lcrv   18/9/2018 Implementacao dos modulos 
*	  1.1	   lcrv   18/9/2018 Correcao das interfaces
*       1.0    lcrv   7/09/2018 Inicio do desenvolvimento
*  Para maiores detalhes do historico ver controle de versao no GitHub, referenciado no LeiaMe do projeto.
***************************************************************************/

#include <stdlib.h>
#include "grafo.h"

/***********************************************************************
*
*  $TC Tipo de dados: GRP Grafo
*
*  $ED Descricao do tipo
*     A implementacao do Grafo.
*	Sua implementacao faz uso de Listas duplamenente
*	encadeadas, implementadas no modulo Lista desse
*	projeto. Utilizamos duas listas, uma de todos os vertices do grafo
*	e outra para vertices de origem a partir dos quais podemos acessar 
*	separadamente cada componente conectado do grafo. Temos tambem
*	um vertice corrente utilizado para movimentacao no grafo.
*	Para mais informacoes veja a descricao do tipo no seu modulo
*	de definicao.
*
***********************************************************************/

struct grafo{
	LIS_tppLista vertices;
	LIS_tppLista origens;
	Vertice corrente;
};


/************************Codigo das funcoes exportadas pelo modulo******************************/

/***************************************************************************
*
*  Funcao: GRP Criar Grafo
*  ****/

GRP_tpCondRet GRP_CriarGrafo(Grafo* endereco){
	if(!endereco) return GRP_CondRetOK;
	if(*endereco) GRP_DestruirGrafo(endereco);

	*endereco = (Grafo) malloc(sizeof(struct grafo));
	if(!(*endereco)) return GRP_CondRetFaltouMemoria;
	(*endereco)->vertices = (*endereco)->origens = NULL;
	(*endereco)->corrente = NULL;

	return GRP_CondRetOK;
}

/***************************************************************************
*
*  Funcao: GRP Destruir Grafo
*  ****/

void GRP_DestruirGrafo(Grafo* endereco){
	Grafo g;
	if(!endereco || !(*endereco)) return;
	g = *endereco;
	VER_DestruirVertice(g->corrente);
	if(g->origens)  LIS_DestruirLista(g->origens);
	if(g->vertices) LIS_DestruirLista(g->vertices);
	free(g);
	*endereco = NULL;
}

/***************************************************************************
*
*  Funcao: GRP Inserir Vertice
*  ****/


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
	if((!sucessores || !LIS_ObterValor(sucessores)) && (!antecessores || !LIS_ObterValor(antecessores))){
		LIS_InserirElementoApos(grafo->vertices, vertice);
		LIS_InserirElementoApos(grafo->origens, vertice);
		return GRP_CondRetOK;
	}

	//se ele nao for uma origem temos que verificar se seus vizinhos existem.
	IrInicioLista(sucessores);
	//se retornar null e' porque a lista esta vazia ou nula.
	atual = (Aresta) (sucessores ? LIS_ObterValor(sucessores) : NULL);
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
	atual = (Aresta) (antecessores ? LIS_ObterValor(antecessores) : NULL);
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

/***************************************************************************
*
*  Funcao: GRP Inserir Aresta
*  ****/

GRP_tpCondRet GRP_InserirAresta(Grafo grafo, Aresta aresta){
	int chaves[2];
	VER_tpCondRet cond;
	Vertice orig, dest = NULL;
	if(!grafo) return GRP_CondRetGrafoNaoExiste;
	if(!grafo->vertices) return GRP_CondRetGrafoVazio;
	if(!aresta) return GRP_CondRetOK;
	VER_GetChaves(aresta, &chaves);
	//se algum dos vertices da aresta nao foram encontrados um erro de estrutura e' retornado
	if(	VerticedeChave(grafo, chaves[0], &orig) != GRP_CondRetOK || 
		VerticedeChave(grafo, chaves[1], &dest) != GRP_CondRetOK
	  ) 	return GRP_CondRetErroEstrutura;
	//Inserir a aresta nos vertices
	cond = VER_InserirAresta(orig, aresta);
	if(cond == VER_CondRetFaltouMemoria) return GRP_CondRetFaltouMemoria;
	cond = VER_InserirAresta(dest, aresta);
	if(cond == VER_CondRetFaltouMemoria) return GRP_CondRetFaltouMemoria;

	return GRP_CondRetOK;
}

/***************************************************************************
*
*  Funcao: GRP Remover Vertice
*  ****/

GRP_tpCondRet GRP_RemoverVertice(Grafo grafo, int vertice){
	Vertice v = NULL;
	Vertice vizinho = NULL;
	Aresta corr = NULL;
	LIS_tppLista lista = NULL;
	LIS_tpCondRet cond = LIS_CondRetOK;
	int chaves[2];
	if(!grafo) return GRP_CondRetGrafoNaoExiste;
	if(!grafo->vertices) return GRP_CondRetGrafoVazio;
	//obtem vertice a ser removido, se nao houver vertice retorna um erro.
	if(VerticedeChave(grafo, vertice, &v) != GRP_CondRetOK) return GRP_CondRetErroEstrutura;

	// e' necessario remover pointeiros para arestas comuns das listas dos vizinhos do vertice a ser removido.
	VER_getSucessores(v, &lista);
	IrInicioLista(lista);
	while(cond != LIS_CondRetFimLista){
		//obter valor atual
		corr = (Aresta) (lista ? LIS_ObterValor(lista) : NULL);
		//se nao houver a lista estara vazia. Neste caso, paramos por aqui.
		if(!corr) break;
		//Neste caso devemos obter o vertice destino e remover dele a aresta atual
		VER_GetChaves(corr, &chaves);
		VerticedeChave(grafo, chaves[1], &vizinho);
		VER_RemoverAresta(vizinho, corr);

		//pular para o proximo elemento da lista
		cond = LIS_AvancarElementoCorrente(lista, 1);
		if(cond == LIS_CondRetListaVazia) break;
	}

	//reinicializar cond
	cond = LIS_CondRetOK;
	//repetir para os antecessores
	VER_getAntecessores(v, &lista);
	IrInicioLista(lista);
	while(cond != LIS_CondRetFimLista){
		//obter valor atual
		corr = (Aresta) (lista ? LIS_ObterValor(lista) : NULL);
		//se nao houver a lista estara vazia. Neste caso, paramos por aqui.
		if(!corr) break;
		//Neste caso devemos obter o vertice origem e remover dele a aresta atual
		VER_GetChaves(corr, &chaves);
		VerticedeChave(grafo, chaves[0], &vizinho);
		VER_RemoverAresta(vizinho, corr);

		//pular para o proximo elemento da lista
		cond = LIS_AvancarElementoCorrente(lista, 1);
		if(cond == LIS_CondRetListaVazia) break;
	}

	//finalmente removemos o vertice atual de ambas as listas de vertices. Isto automaticamente destroi o vertice.
	if(grafo->origens && LIS_ProcurarValor(grafo->origens, v) == LIS_CondRetOK) LIS_ExcluirElemento(grafo->origens);
	if(LIS_ProcurarValor(grafo->vertices, v) == LIS_CondRetOK) LIS_ExcluirElemento(grafo->vertices);

	return GRP_CondRetOK;
}

/***************************************************************************
*
*  Funcao: GRP Remover Aresta
*  ****/

GRP_tpCondRet GRP_RemoverAresta(Grafo grafo, Aresta aresta){
	int chaves[2];
	VER_tpCondRet cond;
	Vertice orig, dest = NULL;
	if(!grafo) return GRP_CondRetGrafoNaoExiste;
	if(!grafo->vertices) return GRP_CondRetGrafoVazio;
	if(!aresta) return GRP_CondRetOK;
	VER_GetChaves(aresta, &chaves);
	//se algum dos vertices da aresta nao foram encontrados um erro de estrutura e' retornado
	if(	VerticedeChave(grafo, chaves[0], &orig) != GRP_CondRetOK || 
		VerticedeChave(grafo, chaves[1], &dest) != GRP_CondRetOK
	  ) 	return GRP_CondRetErroEstrutura;
	//Remover a aresta dos vertices
	cond = VER_RemoverAresta(orig, aresta);
	if(cond == VER_CondRetFaltouMemoria) return GRP_CondRetFaltouMemoria;
	cond = VER_RemoverAresta(dest, aresta);
	if(cond == VER_CondRetFaltouMemoria) return GRP_CondRetFaltouMemoria;

	return GRP_CondRetOK;
}

/***************************************************************************
*
*  Funcao: GRP Vertice de Chave
*  ****/

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

