/***************************************************************************
*
*  $MCD Modulo de implementacao: Modulo vertice
*
*  Arquivo gerado:              VERTICE.C
*  Letras identificadoras:      VER
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
#include <string.h>
#include "vertice.h"

/***********************************************************************
*
*  $TC Tipo de dados: VER Vertice
*
*  $ED Descricao do tipo
*     A implementacao do Vertice.
*	Sua implementacao faz uso de Listas duplamenente
*	encadeadas, implementadas no modulo Lista desse
*	projeto. Utilizamos uma unica aresta reflexiva para
*	tratar o caso da unica aresta que pode ir do vertice para si
*	mesmo. Para mais informacoes veja a descricao do tipo no seu modulo
*	de definicao.
*
***********************************************************************/

struct vertice{
	// listas de ARESTAS
	LIS_tppLista sucessores;
	LIS_tppLista antecessores;
	// a unica aresta do vertice para ele mesmo, se houver.
	Aresta reflexiva;
	void* valor;
	// identificador unico do vertice em um grafo
	int chave;
	// vertice foi visitado?
	int visitado;
	VER_TipoVer tipo;
	//funcao de exclusao
	void (*ExcluirValor)(void*valor);
};

/***********************************************************************
*
*  $TC Tipo de dados: VER Aresta
*
*  $ED Descricao do tipo
*     A implementacao da Aresta.
*	A implementacao deste tipo abstrato
*	e' tao simples que estamos justificados em inclui-lo
*	no mesmo modulo que o tipo Vertice, mesmo porque isto auxilia
*	grandemente a implementacao do mesmo tipo Vertice, considerando
*	que muitas outras funcoes de acesso ao tipo Aresta 
*	teriam de ser adicionadas para que fosse possivel separar este modulo
*	em dois. Utilizamos uma constante preprocessada para especificar o
*	tamanho maximo dos rotulos das arestas.
*
***********************************************************************/

#define MAX_LABEL_SIZE 20
struct aresta{
	int origem;
	int destino;
	char rotulo[MAX_LABEL_SIZE];
};

/************************Codigo das funcoes exportadas pelo modulo******************************/

/***************************************************************************
*
*  Funcao: VER Criar Vertice
*  ****/

VER_tpCondRet VER_CriarVertice(Vertice* endereco, void* valor, int chave, void(*ExcluirValor)(void * valor)){
	if(!endereco) return VER_CondRetOK;
	if(*endereco) VER_DestruirVertice(*endereco);

	*endereco = (Vertice) malloc(sizeof(struct vertice));
	if(!(*endereco)) return VER_CondRetFaltouMemoria;

	(*endereco)->valor = valor;
	(*endereco)->chave = chave;
	(*endereco)->ExcluirValor = ExcluirValor;
	(*endereco)->reflexiva = NULL;
	(*endereco)->antecessores = (*endereco)->sucessores = NULL;
	(*endereco)->visitado = 0;
	(*endereco)->tipo = VER_Intermediario;

	return VER_CondRetOK;
}

/***************************************************************************
*
*  Funcao: VER Inserir Aresta
*  ****/

VER_tpCondRet VER_InserirAresta(Vertice vertice, Aresta aresta){
	char orig;
	char dest;
	
	if(!vertice) return VER_CondRetVerticeNaoExiste;
	if(!aresta) return VER_CondRetArestaNaoExiste;
	orig = aresta->origem == vertice->chave;
	dest = aresta->destino == vertice->chave;
	if(!orig && !dest) return VER_CondRetErroInsercao;

	if(orig && dest) vertice->reflexiva = aresta;
	else if(!orig){
		if(!vertice->antecessores) vertice->antecessores = LIS_CriarLista((void(*)(void *pDado))VER_DestruirAresta);
		if(!vertice->antecessores) return VER_CondRetFaltouMemoria;
		//verifica se aresta ja existe no vertice, nesse caso nada precisa ser feito.
		if(LIS_ProcurarValor(vertice->antecessores, aresta) == LIS_CondRetOK) return VER_CondRetOK;
		LIS_InserirElementoApos(vertice->antecessores, aresta);
	}
	else{
		if(!vertice->sucessores) vertice->sucessores = LIS_CriarLista((void(*)(void *pDado))VER_DestruirAresta);
		if(!vertice->sucessores) return VER_CondRetFaltouMemoria;
		//verifica se aresta ja existe no vertice, nesse caso nada precisa ser feito.
		if(LIS_ProcurarValor(vertice->sucessores, aresta) == LIS_CondRetOK) return VER_CondRetOK;
		LIS_InserirElementoApos(vertice->sucessores, aresta);
	}

	return VER_CondRetOK;
}

/***************************************************************************
*
*  Funcao: VER Remover Aresta
*  ****/

VER_tpCondRet VER_RemoverAresta(Vertice vertice, Aresta aresta){
	char orig;
	char dest;
	
	if(!vertice) return VER_CondRetVerticeNaoExiste;
	if(!aresta) return VER_CondRetArestaNaoExiste;
	orig = aresta->origem == vertice->chave;
	dest = aresta->destino == vertice->chave;
	if(!orig && !dest) return VER_CondRetErroInsercao;

	if(orig && dest) {
		VER_DestruirAresta(vertice->reflexiva);
		vertice->reflexiva = NULL;
	}
	else if(!orig){
		if(!vertice->antecessores) return VER_CondRetOK;
		//verifica se aresta ja existe no vertice, do contrario nada precisa ser feito.
		if(LIS_ProcurarValor(vertice->antecessores, aresta) != LIS_CondRetOK) return VER_CondRetOK;
		LIS_ExcluirElemento(vertice->antecessores);
	}
	else{
		if(!vertice->sucessores) return VER_CondRetOK;
		//verifica se aresta ja existe no vertice, do contrario nada precisa ser feito.
		if(LIS_ProcurarValor(vertice->sucessores, aresta) != LIS_CondRetOK) return VER_CondRetOK;
		LIS_ExcluirElemento(vertice->sucessores);
	}

	return VER_CondRetOK;
}


/***************************************************************************
*
*  Funcao: VER Modificar Tipo
*  ****/

VER_tpCondRet VER_ModificarTipo(Vertice vertice, VER_TipoVer tipo){
	if(!vertice) return VER_CondRetVerticeNaoExiste;
	if(tipo < 0 || tipo > 2) return VER_CondRetErroInsercao;
	vertice->tipo = tipo;
	return VER_CondRetOK;
}

/***************************************************************************
*
*  Funcao: VER Destruir Vertice
*  ****/

void VER_DestruirVertice(Vertice vertice){
	if(!vertice) return;
	VER_DestruirAresta(vertice->reflexiva);
	if(vertice->antecessores) LIS_DestruirLista(vertice->antecessores);
	if(vertice->sucessores) LIS_DestruirLista(vertice->sucessores);
	vertice->ExcluirValor(vertice->valor);
	free(vertice);
}

/***************************************************************************
*
*  Funcao: VER Marcar Visitado
*  ****/

VER_tpCondRet VER_MarcarVisitado(Vertice vertice){
	if(!vertice) return VER_CondRetVerticeNaoExiste;
	vertice->visitado = vertice->visitado? 0 : 1;
	return VER_CondRetOK;
}

/***************************************************************************
*
*  Funcao: VER Get Valor
*  ****/

VER_tpCondRet VER_getValor(Vertice vertice, void** enderecoValor){
	if(!vertice) return VER_CondRetVerticeNaoExiste;
	if(!enderecoValor) return VER_CondRetOK;
	*enderecoValor = vertice->valor;
	return VER_CondRetOK;
}

/***************************************************************************
*
*  Funcao: VER Get Sucessores
*  ****/

VER_tpCondRet VER_getSucessores(Vertice vertice, LIS_tppLista* enderecoSucessores){
	if(!vertice) return VER_CondRetVerticeNaoExiste;
	if(!enderecoSucessores) return VER_CondRetOK;
	*enderecoSucessores = vertice->sucessores;
	return VER_CondRetOK;
}

/***************************************************************************
*
*  Funcao: VER Get Antecessores
*  ****/

VER_tpCondRet VER_getAntecessores(Vertice vertice, LIS_tppLista* enderecoAntecessores){
	if(!vertice) return VER_CondRetVerticeNaoExiste;
	if(!enderecoAntecessores) return VER_CondRetOK;
	*enderecoAntecessores = vertice->antecessores;
	return VER_CondRetOK;
}

/***************************************************************************
*
*  Funcao: VER Get Reflexiva
*  ****/

VER_tpCondRet VER_getReflexiva(Vertice vertice, Aresta* enderecoReflexiva){
	if(!vertice) return VER_CondRetVerticeNaoExiste;
	if(!enderecoReflexiva) return VER_CondRetOK;
	*enderecoReflexiva = vertice->reflexiva;
	return VER_CondRetOK;
}

/************************Funcoes adicionais de VERTICE*****************************/

/***************************************************************************
*
*  Funcao: VER Visitado?
*  ****/

VER_tpCondRet VER_Visitado(Vertice vertice, int* endereco){
	if(!vertice) return VER_CondRetVerticeNaoExiste;
	if(!endereco) return VER_CondRetOK;
	*endereco = vertice->visitado;
	return VER_CondRetOK;
}

/***************************************************************************
*
*  Funcao: VER Get Chave
*  ****/

VER_tpCondRet VER_getChave(Vertice vertice, int* endereco){
	if(!vertice) return VER_CondRetVerticeNaoExiste;
	if(!endereco) return VER_CondRetOK;
	*endereco = vertice->chave;
	return VER_CondRetOK;
}

/***************************************************************************
*
*  Funcao: VER Get Tipo
*  ****/

VER_tpCondRet VER_getTipo(Vertice vertice, VER_TipoVer* endereco){
	if(!vertice) return VER_CondRetVerticeNaoExiste;
	if(!endereco) return VER_CondRetOK;
	*endereco = vertice->tipo;
	return VER_CondRetOK;
}

/************************Funcoes de acesso a estrutura Aresta*****************************/

/***************************************************************************
*
*  Funcao: VER Criar Aresta
*  ****/

VER_tpCondRet VER_CriarAresta(Aresta* endereco, int origem, int destino, char* rotulo){
	if(!endereco) return VER_CondRetOK;
	if(*endereco) VER_DestruirAresta(*endereco);

	*endereco = (Aresta) malloc(sizeof(struct aresta));
	if(!(*endereco)) return VER_CondRetFaltouMemoria;

	(*endereco)->origem = origem;
	(*endereco)->destino = destino;
	strcpy((*endereco)->rotulo, rotulo);

	return VER_CondRetOK;
}

/***************************************************************************
*
*  Funcao: VER Destruir Aresta
*  ****/

void VER_DestruirAresta(Aresta aresta){
	if(!aresta) return;
	free(aresta);
}

/***************************************************************************
*
*  Funcao: VER Get Chaves
*  ****/

VER_tpCondRet VER_GetChaves(Aresta aresta, int (*chaves)[2]){
	if(!aresta) return VER_CondRetArestaNaoExiste;
	if(!chaves) return VER_CondRetOK;
	(*chaves)[0] = aresta->origem;
	(*chaves)[1] = aresta->destino;
	return VER_CondRetOK;
}

/***************************************************************************
*
*  Funcao: VER Get Rotulo
*  ****/

VER_tpCondRet VER_getRotulo(Aresta aresta, char** endereco){
	if(!aresta) return VER_CondRetArestaNaoExiste;
	if(!endereco) return VER_CondRetOK;
	*endereco = aresta->rotulo;
	return VER_CondRetOK;
}

/********** Fim do modulo de implementacao: Modulo Vertice**********/