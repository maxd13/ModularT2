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
*  Autores: lcrv - Luiz Carlos R Viana, bpf - Breno Perricone Fischer
*
*  $HA Historico de evolucao:
*     Versao  Autor    Data     Observacoes
*      2     bpf    3/out/2018 criacao de assertivas de entrada e saida
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
*	GRP Criar grafo:
*
*	Assertivas de entrada:
*		- Ponteiro para endereço do grafo a ser criado, podendo ser inexistente, com tipo struct grafo.
*
*	Assertivas de saída:
*		- Nada foi feito e condição de OK retornada, caso o endereço passado
*		  inicialmente era NULL.
*		- Grafo alocado dinamicamente, com tamanho de uma struct do tamanho de grafo,
*		  referenciado pelo ponteiro do endereço passado inicialmente, com os respectivos valores, 
*		  iniciados como NULL e condição de retorno OK retornada.
*		- Grafo destruido, anteriormente referenciado pelo ponteiro de endereço passado 
*		  como parametro, caso já existia um grafo nesse endereço e novo grafo vazio criado, com condicao de
*		  retorno OK retornado.
*
***********************************************************************/

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
*	GRP Destruir Grafo:
*
*	Assertivas de entrada:
*		- Ponteiro para grafo a ser destruido, podendo ser inexistente.
*
*	Assertivas de saída:
*		- Nada foi modificado, caso grafo inexistente.
*		- O conteudo do grafo foi destruido (a lista de origens e de vertices do grafo)
*		  e o grafo foi anulado no ponteiro, passado como parametro.
*
***********************************************************************/

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
*	GRP Inserir Vertice:
*
*	Assertivas de entrada:
*		- Ponteiro para o grafo, podendo ser inexistente, no qual sera inserido o vertice.
*		- Ponteiro para o vertice, podendo ser inexistente, o qual sera inserido.
*
*	Assertivas de saída:
*		- Nada foi modificado e condição de retorno OK retornada, caso vertice inexistente.
*		- Nada foi modificado e condição de retorno Grafo Nao Existe retornada, caso grafo inexistente.
*		- Ponteiro do grafo para vertices referenciando a lista de vertices criada, caso o grafo nao possuia uma
*		  lista de vertices, assim como para a lista de origens criada. Caso as listas nao tenham sido criadas corretamente,
*		  condicao de retorno faltou memoria foi retornada.
*		- Condicao de erro de estrutura retornada, caso a chave do vertice ja existia no grafo passado como parametro.
*		- Condicao OK de retorno e, vertice e origem, inseridos como elemento de lista apos o elemento corrente, caso o
*		  vertice, passado como parametro, nao possuia vizinhos.
*		- Condicao OK de retorno e, vertice, origem e aresta, inseridos como elemento de lista no elemento corrente.
*
***********************************************************************/

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
*	Caso a aresta ja exista no grafo enquanto par ordenado de chaves, nada e' feito e OK e' retornado.

*  $FV Valor retornado
*     GRP_CondRetOK
*	GRP_CondRetGrafoNaoExiste
*	GRP_CondRetGrafoVazio
*	GRP_CondRetErroEstrutura - caso os vertices da aresta nao existam no grafo.
*     GRP_CondRetFaltouMemoria
*
***********************************************************************/

GRP_tpCondRet GRP_InserirAresta(Grafo grafo, Aresta aresta);


/***********************************************************************
*	GRP Inserir Aresta:
*
*	Assertivas de entrada:
*		- Ponteiro para o grafo, podendo ser inexistente, no qual sera inserida a aresta.
*		- Ponteiro para a aresta, podendo ser inexistente, a qual sera inserida.
*
*	Assertivas de saída:
*		- Nada foi modificado e condição de retorno OK retornada, caso aresta inexistente.
*		- Nada foi modificado e condição de retorno Grafo Nao Existe retornada, caso grafo inexistente.
*		- Nada foi modificado e condição de retorno OK retornada, caso par ordenado de chaves da aresta, passada como parametro,
*		  ja existia no grafo.
*		- Nada foi modificado e condicao de retorno Grafo Vazio retornada, caso nenhum vertice estava contido no grafo.
*		- Condicao de erro de estrutura retornado, caso o valor contido nas chaves da aresta, passada como parametro,
*		  nao corresponderam aos vertices contidos no grafo.
*		- Chaves da aresta foram inseridas na origem e no destino do vertice corrente do grafo.
*
***********************************************************************/

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
*
***********************************************************************/

GRP_tpCondRet GRP_RemoverVertice(Grafo grafo, int vertice);


/***********************************************************************
*	GRP Remover Vertice:
*
*	Assertivas de entrada:
*		- Ponteiro para o grafo, podendo ser inexistente, no qual sera removido o vertice.
*		- Valor inteiro representando a chave do vertice, o qual sera removido do grafo.
*
*	Assertivas de saída:
*		- Nada foi modificado e condição de retorno Grafo Nao Existe retornada, caso grafo inexistente.
*		- Nada foi modificado e condicao de retorno Grafo Vazio retornada, caso nenhum vertice estava contido no grafo.
*		- Nada foi modificado e condicao de retorno Erro de estrutura retornada, caso a chave passada como parametro
*		  nao referenciava nenhum vertice existente no grafo.
*		- As arestas, com o par de chaves respectivas, da chave do vertice, passado como parametro, foram removidas,
*		 elemento corrente da lista de vertices do grafo aponta para o anterior ou proximo, chave passada como parametro,
*		 referenciando um vertice valido. Condicao de retorno OK retornada.
*
***********************************************************************/

/***********************************************************************
*
*  $FC Funcao: GRP Remover aresta
*
*  $EP Parametros
*	$P grafo - grafo do qual remover a aresta.
*     $P aresta - aresta a ser removida.
*
*  $FV Valor retornado
*     GRP_CondRetOK
*	GRP_CondRetGrafoNaoExiste
*	GRP_CondRetGrafoVazio
*	GRP_CondRetErroEstrutura - caso os vertices da aresta nao existam no grafo
*     GRP_CondRetFaltouMemoria
*
***********************************************************************/

GRP_tpCondRet GRP_RemoverAresta(Grafo grafo, Aresta aresta);


/***********************************************************************
*	GRP Remover Aresta:
*
*	Assertivas de entrada:
*		- Ponteiro para o grafo, podendo ser inexistente, na qual sera removida a aresta.
*		- Ponteiro para a aresta, podendo ser inexistente, a qual sera removida.
*
*	Assertivas de saída:
*		- Nada foi modificado e condição de retorno Grafo Nao Existe retornada, caso grafo inexistente.
*		- Nada foi modificado e condicao de retorno Grafo Vazio retornada, caso nenhum vertice estava contido no grafo.
*		- Nada foi modificado e condição de retorno OK retornada, caso aresta inexistente.
*		- Nada foi modificado e condicao de retorno Erro de estrutura retornada, caso o par de chaves, passada como parametro,
*		  da aresta, nao referenciava nenhum vertice existente no grafo.
*		- A aresta foram removidas do vertice de origem e destinos respectivos e condicao de retorno OK retornada.
*
***********************************************************************/

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

/***********************************************************************
*	GRP Vertice de Chave:
*
*	Assertivas de entrada:
*		- Ponteiro para o grafo, podendo ser inexistente, no qual sera acessado o vertice.
*		- Valor inteiro representando a chave do vertice, o qual sera acessado no grafo.
*		- Ponteiro para endereco de vertice no qual sera colocado o vertice.
*
*	Assertivas de saída:
*		- Nada foi modificado e condição de retorno Grafo Nao Existe retornada, caso grafo inexistente.
*		- Nada foi modificado e condicao de retorno Grafo Vazio retornada, caso nenhum vertice estava contido no grafo.
*		- Condicao de retorno erro de estrutura retornado e elemento corrente da lista de vertices contidos no grafo
*		  apontando para o final da lista, caso a chave do vertice, passada como parametro, nao correspondeu
*		  a nenhuma chave de vertice contida no grafo.
*		- Condicao de retorno OK retornada e endereco de vertice com valor atribuido ao endereco do vertice corrente da
*		  lista de vertices do grafo, caso a chave, passada como parametro, foi encontrada na lista de vertices do grafo.
*
***********************************************************************/

/************************Fim da definicao do modulo Grafo*****************************/