#pragma once
#include "vertice.h"
/***************************************************************************
*
*  $MCD Modulo de definicao: Modulo grafo
*
*  Arquivo gerado:              GRAFO.H
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
*	  1.1	  lcrv   18/9/2018 Correcao das interfaces
*       1.0   lcrv   7/09/2018 Inicio do desenvolvimento
*  Para maiores detalhes do historico ver controle de versao no GitHub, referenciado no LeiaMe do projeto.
*  $ED Descricao do modulo
*     Este modulo implementa um conjunto simples de funcoes para criar e
*     explorar grafos.
*     O Grafo possui uma cabeca que contem uma referencia para a lista de
*	vertices do grafo e outra para o vertice corrente. Possui tambem
*	uma lista de origens, que sao vertices a partir dos quais se pode
*	facilmente construir a lista de componentes conectados do grafo.
*     O grafo podera estar vazio. Neste caso o vertice corrente sera nulo.
*     O vertice corrente sera nulo se e somente se o grafo estiver vazio.
*	A implementacao deste grafo e' generica e serve para diversas aplicacoes.
*
***************************************************************************/

typedef struct grafo* Grafo;

/***********************************************************************
*
*  $TC Tipo de dados: GRP Condicoes de retorno
*
*
***********************************************************************/

typedef enum {

      GRP_CondRetOK = 0,
            /* Executou correto */

      GRP_CondRetErroEstrutura = 1,
            /* Estrutura do grafo esta errada */

      GRP_CondRetGrafoNaoExiste = 2,
            /* Grafo nao existe */

      GRP_CondRetGrafoVazio = 3,
            /* grafo esta vazio */

      GRP_CondRetFaltouMemoria = 4,
            /* Faltou memoria ao alocar dados */

} GRP_tpCondRet;

/***********************************************************************
*
*  $FC Funcao: GRP Criar grafo
*
*	$EP Parametros
*     $P endereco - endereco do grafo a ser inicializado.
*
*  $ED Descricao da funcao
*     Cria um novo grafo vazio.
*     Caso ja exista um grafo, este sera destruido.
*	Caso o endereco seja nulo nada sera feito e sera retornado
*	OK.
*
*  $FV Valor retornado
*     GRP_CondRetOK
*     GRP_CondRetFaltouMemoria
*
***********************************************************************/

GRP_tpCondRet GRP_CriarGrafo(Grafo* endereco);


/***********************************************************************
*
*  $FC funcao: GRP Destruir grafo
*
*	$EP Parametros
*     $P endereco - endereco do grafo a ser destruido.
*
*  $ED Descricao da funcao
*     Destroi o grafo, anulando o grafo presente no local especificado.
*     Faz nada caso o grafo nao exista.
*
***********************************************************************/

void GRP_DestruirGrafo(Grafo* endereco);

/***********************************************************************
*
*  $FC Funcao: GRP Inserir vertice
*
*  $EP Parametros
*	$P grafo     - grafo no qual inserir o vertice.
*     $P vertice   - vertice a ser inserido.
*
*  $ED Descricao da funcao
*	Insere um vertice no grafo.
*	Caso a chave do vertice ja exista no grafo, nada e' feito e um erro de estrutura e' retornado.
*	Caso o vertice tenha arestas, e' verificado se todos os seus vizinhos fazem parte do grafo,
*	nesse caso as arestas sao adicionadas, do contrario um erro de estrutura e' retornado.
*	Caso o vertice nao exista nada e' feito e OK e' retornado.
*	
*
*  $FV Valor retornado
*     GRP_CondRetOK
*	GRP_CondRetGrafoNaoExiste
*     GRP_CondRetFaltouMemoria
*	GRP_CondRetErroEstrutura - caso a chave do vertice ja' exista no grafo ou a chave de algum de seus vizinhos nao exista
*
***********************************************************************/

GRP_tpCondRet GRP_InserirVertice(Grafo grafo, Vertice vertice);

/***********************************************************************
*
*  $FC Funcao: GRP Inserir aresta
*
*  $EP Parametros
*	$P grafo - grafo no qual inserir a aresta.
*     $P aresta - aresta a ser inserida.
*
*  $ED Descricao da funcao
*	Insere uma aresta no grafo.
*	Caso a aresta ja exista no grafo enquanto par ordenado de chaves, nada e' feito e um erro de estrutura 'e retornado.

*  $FV Valor retornado
*     GRP_CondRetOK
*	GRP_CondRetGrafoNaoExiste
*	GRP_CondRetGrafoVazio
*	GRP_CondRetErroEstrutura - caso os vertices da aresta nao existam no grafo ou a aresta ja exista.
*     GRP_CondRetFaltouMemoria
*
***********************************************************************/

GRP_tpCondRet GRP_InserirAresta(Grafo grafo, Aresta aresta);

/***********************************************************************
*
*  $FC Funcao: GRP Remover vertice
*
*  $EP Parametros
*	$P grafo - grafo do qual remover o vertice.
*     $P vertice - chave do vertice a ser removido.
*
*  $FV Valor retornado
*     GRP_CondRetOK
*	GRP_CondRetGrafoNaoExiste
*	GRP_CondRetGrafoVazio
*	GRP_CondRetErroEstrutura - caso a chave nao referencie um vertice
*     GRP_CondRetFaltouMemoria
*
***********************************************************************/

GRP_tpCondRet GRP_RemoverVertice(Grafo grafo, int vertice);

/***********************************************************************
*
*  $FC Funcao: GRP Remover aresta
*
*  $EP Parametros
*	$P grafo - grafo do qual remover a aresta.
*     $P aresta - array de duas posicoes com as chaves dos vertices da aresta a ser removida.
*
*  $FV Valor retornado
*     GRP_CondRetOK
*	GRP_CondRetGrafoNaoExiste
*	GRP_CondRetGrafoVazio
*	GRP_CondRetErroEstrutura - caso a aresta nao exista no grafo
*     GRP_CondRetFaltouMemoria
*
***********************************************************************/

GRP_tpCondRet GRP_RemoverAresta(Grafo grafo, int (*aresta)[2]);

/***********************************************************************
*
*  $FC Funcao: GRP vertice de chave
*
*  $EP Parametros
*	$P grafo	- grafo do qual se quer acessar um vertice
*	$P chave	- chave do vertice que se quer
*	$P endereco - endereco no qual colocar o Vertice
*
*  $ED Descricao da funcao
*	Deposita o unico vertice do grafo que possui a chave especificada
*	no endereco especificado.
*
*  $FV Valor retornado
*     GRP_CondRetOK
*	GRP_CondRetGrafoNaoExiste
*	GRP_CondRetGrafoVazio
*	GRP_CondRetErroEstrutura - caso o vertice nao exista no grafo
*	
*
***********************************************************************/
GRP_tpCondRet VerticedeChave(Grafo grafo, int chave, Vertice* endereco);


/************************Fim da definicao do modulo Grafo*****************************/