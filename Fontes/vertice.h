#pragma once

/***************************************************************************
*
*  $MCD Modulo de definicao: Modulo vertice
*
*  Arquivo gerado:              VERTICE.H
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
*	  1.1	  lcrv   18/9/2018 Correcao das interfaces
*       1.0   lcrv   7/09/2018 Inicio do desenvolvimento
*  Para maiores detalhes do historico ver controle de versao no GitHub, referenciado no LeiaMe do projeto.
*
*  $ED Descricao do modulo
*     Este modulo implementa um conjunto simples de funcoes para criar vertices e arestas de um grafo.
*     Cada vertice possui um tipo, uma chave identificadora, um valor, 
*	conhece seus sucessores e antecessores e pode ser marcado como visitado.
*	Os tipos de vertice podem ser: inicial, intermediario ou final.
*     O vertice nunca estara vazio, mas pode ocorrer de nao ter antecessores ou sucessores, sendo desconectado.
*	Tambem e' possivel que o seu valor seja nulo.
*	Uma aresta tem origem, destino e rotulo.
*	Atualmente o peso de arestas nao sera implementado mas
*	esta modificacao podera ser implementada no futuro.
*	
*	O controle da destruicao do valor de um vertice a ser excluido
*     e' realizado por uma funcao fornecida pelo usuario.
*
*     Cada vertice referencia uma funcao que determina como devem ser
*     desalocados o dado nele contido pelo campo "valor".
*
*     A funcao de liberacao do valor contido nos vertices deve
*        assegurar a liberacao de todos os espacos referenciados pelo
*        mesmo valor.
*        Esta funcao e' chamada antes de se desalocar um vertice.
*        Caso nao seja necessario desalocar o valor referenciado pelo
*        vertice, o ponteiro para a funcao de liberacao podera ser NULL.
*        Caso o vertice seja a unica ancora do valor referenciado,
*        esta funcao deve promover a destruicao (free) desse valor e
*        de todos os dados nele ancorados.
*
***************************************************************************/

#include "LISTA.H"

typedef struct vertice* Vertice;
typedef struct aresta* Aresta;


/***********************************************************************
*
*  $TC Tipo de dados: VER Condicoes de retorno
*
*
***********************************************************************/

typedef enum {

      VER_CondRetOK = 0,
            /* Executou correto */

      VER_CondRetVerticeNaoExiste = 1,
            /* Vertice nao existe */

	VER_CondRetArestaNaoExiste = 2,
            /* Aresta nao existe */

	VER_CondRetErroInsercao = 3,
		/* Tentativa de inserir num vertice um valor inconsistente (e.g. arestas que nao tem ele como origem ou destino) */

      VER_CondRetFaltouMemoria = 4,
            /* Faltou memoria ao alocar dados */

} VER_tpCondRet;

/***********************************************************************
*
*  $TC Tipo de dados: VER Tipo de vertice
*
*
***********************************************************************/

typedef enum {

      VER_Inicial = 0,
            /* Vertice Inicial */

      VER_Intermediario = 1,
            /* Vertice Intermediario */

	VER_Final = 2,
            /* Vertice Final */

} VER_TipoVer;


/***********************************************************************
*
*  $FC Funcao: VER Criar vertice
*
*	$EP Parametros
*     $P endereco     - endereco do vertice a ser criado.
*	$P valor	    - valor do vertice.
*	$P chave	    - chave do vertice.
*	$P ExcluirValor - ponteiro para a funcao que processa a
*				exclusao do valor referenciado pelo vertice.
*				Ver descricao do modulo.
*
*  $ED Descricao da funcao
*     Cria um novo vertice.
*     Caso ja exista um vertice, este sera destruido.
*	Caso seja passado um endereco inexistente nada sera feito,
*	e sera retornada uma condicao de retorno OK.
*
*  $FV Valor retornado
*     VER_CondRetOK
*     VER_CondRetFaltouMemoria
*
***********************************************************************/

VER_tpCondRet VER_CriarVertice(Vertice* endereco, void* valor, int chave, void(*ExcluirValor)(void * valor));

/***********************************************************************
*
*  $FC Funcao: VER Inserir Aresta
*
*	$EP Parametros
*     $P vertice    - vertice no qual inserir as arestas.
*	$P aresta	  - aresta para outros vertices a ser inserida.
*
*  $ED Descricao da funcao
*	Insere uma nova aresta.
*	Verifica antes se a aresta a ser inserida ja existe no vertice, 
*	nesse caso nada e' feito e OK e' retornado.
*
*  $FV Valor retornado
*     VER_CondRetOK
*	VER_CondRetVerticeNaoExiste
*	VER_CondRetArestaNaoExiste - caso a aresta seja nula.
*	VER_CondRetErroInsercao	   - caso nem origem nem destino da aresta sejam iguais a chave do vertice.
*     VER_CondRetFaltouMemoria
*
***********************************************************************/

VER_tpCondRet VER_InserirAresta(Vertice vertice, Aresta aresta);

/***********************************************************************
*
*  $FC Funcao: VER Modificar Tipo
*
*	$EP Parametros
*     $P vertice    - vertice a modificar.
*	$P tipo	  - tipo novo.
*
*  $FV Valor retornado
*     VER_CondRetOK
*	VER_CondRetVerticeNaoExiste
*	VER_CondRetErroInsercao - caso o tipo nao exista.
*
***********************************************************************/

VER_tpCondRet VER_ModificarTipo(Vertice vertice, VER_TipoVer tipo);


/***********************************************************************
*
*  $FC funcao: VER Destruir vertice
*
*	$EP Parametros
*     $P vertice - vertice a ser destruido.
*
*  $ED Descricao da funcao
*     Destroi o vertice.
*     Faz nada caso o vertice nao exista.
*	Depois de destruido o vertice nao e' anulado,
*	isto deve ser feito pelo caller da funcao.
*
***********************************************************************/

void VER_DestruirVertice(Vertice vertice);

/***********************************************************************
*
*  $FC Funcao: VER Marcar Visitado
*
*	$EP Parametros
*     $P vertice  - vertice a ser marcado.
*
*	
*  $ED Descricao da funcao
*	Caso o vertice esteja marcado como visitado, ele e' desmarcado, do contrario e' marcado.
*
*
*  $FV Valor retornado
*     VER_CondRetOK
*	VER_CondRetVerticeNaoExiste
*
***********************************************************************/

VER_tpCondRet VER_MarcarVisitado(Vertice vertice);

/***********************************************************************
*
*  $FC Funcao: VER Get Valor
*
*	$EP Parametros
*     $P vertice	     - vertice.
*	$P enderecoValor - endereco aonde o valor do vertice deve ser colocado.
*	
*  $ED Descricao da funcao
*	Coloca o valor do vertice no endereco especificado. 
*	Se o endereco e' nulo, nao faz nada e retorna OK.
*
*
*  $FV Valor retornado
*     VER_CondRetOK
*	VER_CondRetVerticeNaoExiste
*
***********************************************************************/

VER_tpCondRet VER_getValor(Vertice vertice, void** enderecoValor);

/***********************************************************************
*
*  $FC Funcao: VER Get Sucessores
*
*	$EP Parametros
*     $P vertice		    - vertice.
*	$P enderecoSucessores - endereco da lista onde serao postos os sucessores do vertice.
*	
*  $ED Descricao da funcao
*	Coloca a lista de arestas de sucessores do vertice no endereco especificado. 
*	Se o endereco e' nulo, nao faz nada e retorna OK.
*	Se nao existirem sucessores, o valor NULL sera colocado no endereco.
*
*
*  $FV Valor retornado
*     VER_CondRetOK
*	VER_CondRetVerticeNaoExiste
*
***********************************************************************/

VER_tpCondRet VER_getSucessores(Vertice vertice, LIS_tppLista* enderecoSucessores);

/***********************************************************************
*
*  $FC Funcao: VER Get Antecessores
*
*	$EP Parametros
*     $P vertice		    - vertice.
*	$P enderecoAntecessores - endereco da lista onde serao postos os sucessores do vertice.
*	
*  $ED Descricao da funcao
*	Coloca a lista de arestas de antecessores do vertice no endereco especificado. 
*	Se o endereco e' nulo, nao faz nada e retorna OK.
*	Se nao existirem antecessores, o valor NULL sera colocado no endereco.
*
*
*  $FV Valor retornado
*     VER_CondRetOK
*	VER_CondRetVerticeNaoExiste
*
***********************************************************************/

VER_tpCondRet VER_getAntecessores(Vertice vertice, LIS_tppLista* enderecoAntecessores);

/***********************************************************************
*
*  $FC Funcao: VER Get Reflexiva
*
*	$EP Parametros
*     $P vertice		    - vertice.
*	$P enderecoReflexiva  - endereco aonde a Aresta deve ser colocada.
*	
*  $ED Descricao da funcao
*	Coloca a unica aresta do vertice para ele mesmo no endereco especificado. 
*	Se o endereco e' nulo, nao faz nada e retorna OK.
*	Se nao existir aresta, o valor NULL sera colocado no endereco.
*
*
*  $FV Valor retornado
*     VER_CondRetOK
*	VER_CondRetVerticeNaoExiste
*
***********************************************************************/

VER_tpCondRet VER_getReflexiva(Vertice vertice, Aresta* enderecoReflexiva);


/************************Funcoes adicionais de VERTICE*****************************/


/***********************************************************************
*
*  $FC Funcao: VER Visitado?
*
*	$EP Parametros
*     $P vertice  - o vertice a testar.
*	$P endereco - o endereco do inteiro no qual colocar o valor.
*	
*  $ED Descricao da funcao
*	Verifica se o vertice ja foi visitado ou nao.
*	Se nao houver vertice gera uma condicao de erro.
*	Se o endereco e' nulo, nao faz nada e retorna OK.
*	Deposita 1 no endereco especificado caso 
*	o vertice ja tenha sido visitado, do contrario 0.
*
*  $FV Valor retornado
*     VER_CondRetOK
*	VER_CondRetVerticeNaoExiste
*     
*
***********************************************************************/

VER_tpCondRet VER_Visitado(Vertice vertice, int* endereco);

/***********************************************************************
*
*  $FC Funcao: VER Get Chave
*
*	$EP Parametros
*     $P vertice  - o vertice.
*	$P endereco - o endereco do inteiro no qual colocar o valor.
*
*  $ED Descricao da funcao
*	Deposita a chave do vertice no endereco especificado.
*	Se nao houver vertice gera uma condicao de erro.
*	Se o endereco e' nulo, nao faz nada e retorna OK.
*
*  $FV Valor retornado
*     VER_CondRetOK
*	VER_CondRetVerticeNaoExiste
*
***********************************************************************/

VER_tpCondRet VER_getChave(Vertice vertice, int* endereco);

/***********************************************************************
*
*  $FC Funcao: VER Get Tipo
*
*	$EP Parametros
*     $P vertice  - o vertice.
*	$P endereco - o endereco do VER_TipoVer no qual colocar o valor.
*	
*  $ED Descricao da funcao
*	Deposita o tipo do vertice no endereco especificado.
*	Se nao houver vertice gera uma condicao de erro.
*	Se o endereco e' nulo, nao faz nada e retorna OK.
*
*  $FV Valor retornado
*     VER_CondRetOK
*	VER_CondRetVerticeNaoExiste
*
***********************************************************************/

VER_tpCondRet VER_getTipo(Vertice vertice, VER_TipoVer* endereco);

/************************Fim de funcoes adicionais de VERTICE*****************************/

/************************Funcoes de acesso a estrutura Aresta*****************************/

/***********************************************************************
*
*  $FC Funcao: VER Criar aresta
*
*	$EP Parametros
*     $P endereco - endereco da aresta a ser inicializada.
*	$P origem	- chave do vertice origem da aresta.
*	$P destino	- chave do vertice destino da aresta
*	$P rotulo	- rotulo da aresta
*	
*  $ED Descricao da funcao
*     Cria uma nova aresta.
*	Esta aresta e' independente de qualquer vertice especifico.
*	Caso ja exista uma aresta, esta sera destruida.
*	Caso seja passado um endereco inexistente nada sera feito,
*	e sera retornada uma condicao de retorno OK.
*
*
*  $FV Valor retornado
*     VER_CondRetOK
*     VER_CondRetFaltouMemoria
*
***********************************************************************/

VER_tpCondRet VER_CriarAresta(Aresta* endereco, int origem, int destino, char* rotulo);

/***********************************************************************
*
*  $FC funcao: VER Destruir aresta
*
*	$EP Parametros
*     $P aresta - aresta a ser destruida.
*
*  $ED Descricao da funcao
*     Destroi a aresta.
*     Faz nada caso a aresta nao exista.
*	Depois de destruido a aresta nao e' anulada,
*	isto deve ser feito pelo caller da funcao.
*
***********************************************************************/

void VER_DestruirAresta(Aresta aresta);

/***********************************************************************
*
*  $FC Funcao: VER Get chaves da aresta
*
*	$EP Parametros
*     $P aresta   - aresta cujos valores se quer receber.
*	$P chaves	- endereco do array estatico de inteiros onde serao colocaos as chaves da aresta
*	
*  $ED Descricao da funcao
*	Retorna os valores origem e destino das chaves dos vertices da aresta nas respectivas posicoes 0 e 1 do parametro chaves.
*	Faz nada caso o parametro chaves seja nulo, e retorna OK.
*
*
*  $FV Valor retornado
*     VER_CondRetOK
*	VER_CondRetArestaNaoExiste
*
***********************************************************************/

VER_tpCondRet VER_GetChaves(Aresta aresta, int (*chaves)[2]);

/***********************************************************************
*
*  $FC Funcao: VER Get Rotulo
*
*	$EP Parametros
*     $P aresta   - a aresta.
*	$P endereco - o endereco do ponteiro para array de caracteres no qual colocar o valor.
*
*  $ED Descricao da funcao
*	Deposita o rotulo da aresta no endereco especificado.
*	Se nao houver aresta gera uma condicao de erro.
*	Caso seja passado um endereco inexistente nada sera feito,
*	e sera retornada uma condicao de retorno OK.
*
*  $FV Valor retornado
*     VER_CondRetOK
*	VER_CondRetArestaNaoExiste
*
***********************************************************************/

VER_tpCondRet VER_getRotulo(Aresta aresta, char** endereco);

/************************Fim das funcoes de acesso a estrutura Aresta*****************************/

/************************Fim da definicao do modulo Vertice*****************************/