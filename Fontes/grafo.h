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
*  Nome alternativo:		  Primeiro trabalho de Inteligencia Artificial
*
*  Projeto: Disciplinas INF1777 e INF 1628 / 1301
*  Gestor:  DI/PUC-Rio
*  Autores: avs - Luiz Carlos R Viana
*
*  $HA Historico de evolucao:
*     Versao  Autor    Data     Observacoes
*       1.00   avs   7/09/2018 Inicio do desenvolvimento
*
*  $ED Descricao do modulo
*     Este modulo implementa um conjunto simples de funcoes para criar e
*     explorar grafos.
*     O Grafo possui uma cabeca que contem uma referencia para uma lista de
*	vertices do grafo e outra para o vertice corrente.
*     O grafo podera estar vazio. Neste caso o vertice corrente sera nulo.
*     O vertice corrente sera nulo se e somente se o grafo estiver vazio.
*	A implementacao deste grafo e' generica e serve para diversas aplicacoes,
*	tanto as que usam pesos quanto rotulos nas arestas. Fizemos isto para
*	que pudessemos utilizar o mesmo codigo em trabalhos de duas materias diferentes.
*	Desse modo, se quisermos posteriormente utilizar este grafo como representacao de
*	um automato, vamos ter que implementar um modulo adicional para isto.
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
*	$P grafo - grafo no qual inserir o vertice.
*     $P vertice - vertice a ser inserido.
*
*  $ED Descricao da funcao
*	Insere um vertice no grafo.
*	Caso a chave do vertice ja exista no grafo, faz um update dos outros valores do mesmo.
*	Caso o vertice tenha arestas, todos os nos vizinhos serao inseridos tambem.
*
*  $FV Valor retornado
*     GRP_CondRetOK
*	GRP_CondRetGrafoNaoExiste
*     GRP_CondRetFaltouMemoria
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
*	Caso a aresta ja exista no grafo enquanto par ordenado de chaves, faz um update dos seus outros valores.

*  $FV Valor retornado
*     GRP_CondRetOK
*	GRP_CondRetGrafoNaoExiste
*	GRP_CondRetGrafoVazio
*	GRP_CondRetErroEstrutura - caso os vertices da aresta nao existam no grafo
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

/************************Funcoes adicionais que nao serao testadas*****************************/
//Estas sao funcoes puramente adicionais que nao sao imediatamente importantes para o trabalho atual,
//ou entao funcoes de implementacao tao trivial que e' redundante testa-las.

/***********************************************************************
*
*  $FC Funcao: GRP vertice de chave
*
*  $EP Parametros
*	$P grafo - grafo do qual se quer acessar um vertice
*	$P chave - chave do vertice que se quer
*
*  $FV Valor retornado
*	O unico vertice do grafo para o valor da chave dado.
*
***********************************************************************/
Vertice VerticedeChave(Grafo grafo, int chave);


/***********************************************************************
*
*  $FC Funcao: GRP grafo e' completo?
*
*  $EP Parametros
*	$P grafo - grafo a testar se e' completo ou nao.
*
*  $FV Valor retornado
*	1 caso completo, senao 0
*
***********************************************************************/
int GRP_EhCompleto(Grafo grafo);

/***********************************************************************
*
*  $FC Funcao: GRP Circuito Hamiltoniano
*
*  $EP Parametros
*	$P grafo	 - grafo completo a partir do qual calcular o circuito.
*	$P inicial	 - vertice inicial que deve ser o inicio e o fim do circuito.
*	$P minimizar - valor booleano que determina se a busca procurara minizar ou maximizar os pesos
*
*  $ED Descricao da funcao
*	Essa funcao procura um circuito Hamiltoniano em um grafo completo que seja razoavelmente otimizado com respeito
*	a maximizacao ou minimizacao dos pesos das arestas. Ele utiliza uma composicao de algoritmos de busca gulosa e Hill Climbing
*	baseado em swap para concretizar esta tarefa. Este algoritmo pode portanto ser utilizado para obter uma solucao aproximada de
*	problemas como TSP e MLP (Travelling Salesman Problem e Minimum Latency Problem, respectivamente).

*  $FV Valor retornado
*     Um vetor de chaves de vertices de tamanho igual ao numero de vertices do grafo,
*	onde o primeiro valor e' a chave do no inicial e as demais sao as chaves dos outros nos
*	que formam um ciclo Hamiltoniano. Retorna NULL caso o grafo nao seja completo.
*
***********************************************************************/

int* GRP_Hamilton(Grafo grafo, Vertice inicial, int minimizar);

/***********************************************************************
*
*  $FC Funcao: GRP Circuito Hamiltoniano Alternativo
*
*  $EP Parametros
*	$P grafo	 - grafo completo a partir do qual calcular o circuito.
*	$P inicial	 - vertice inicial que deve ser o inicio e o fim do circuito.
*	$P minimizar - valor booleano que determina se a busca procurara minizar ou maximizar os pesos
*
*  $ED Descricao da funcao
*	Essa funcao procura um circuito Hamiltoniano em um grafo completo que seja razoavelmente otimizado com respeito
*	a maximizacao ou minimizacao dos pesos das arestas. Ele utiliza UM ALGORITMO ALTERNATIVO para concretizar esta tarefa.
*	Este algoritmo pode portanto ser utilizado para obter uma solucao aproximada de
*	problemas como TSP e MLP (Travelling Salesman Problem e Minimum Latency Problem, respectivamente).

*  $FV Valor retornado
*     Um vetor de chaves de vertices de tamanho igual ao numero de vertices do grafo,
*	onde o primeiro valor e' a chave do no inicial e as demais sao as chaves dos outros nos
*	que formam um ciclo Hamiltoniano. Retorna NULL caso o grafo nao seja completo.
*
***********************************************************************/

int* GRP_HamiltonAlternativo(Grafo grafo, Vertice inicial, int minimizar);

/************************Fim de Funcoes adicionais que nao serao testadas*****************************/


/************************Fim da definicao do modulo Grafo*****************************/