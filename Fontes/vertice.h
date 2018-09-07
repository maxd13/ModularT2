#pragma once
//#include "Lista.h"

/***************************************************************************
*
*  $MCD Modulo de definicao: Modulo vertice
*
*  Arquivo gerado:              VERTICE.H
*  Letras identificadoras:      VER
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
*     Este modulo implementa um conjunto simples de funcoes para criar vertices e arestas de um grafo.
*     Cada vertice possui um tipo, uma chave identificadora, um valor, 
*	conhece seus sucessores e antecessores e pode ser marcado como visitado.
*	Os tipos de vertice podem ser: inicial, intermediario ou final.
*     O vertice nunca estara vazio, mas pode ocorrer de nao ter antecessores ou sucessores, sendo desconectado.
*	Tambem e' possivel que o seu valor seja nulo.
*	Uma aresta tem origem, destino, peso e rotulo. 
*	A implementacao deste modulo e' generica e serve para diversas aplicacoes,
*	tanto as que usam pesos quanto rotulos nas arestas. Fizemos isto para
*	que pudessemos utilizar o mesmo codigo em trabalhos de duas materias diferentes.
*
***************************************************************************/

typedef struct vertice* Vertice;
typedef struct aresta* Aresta;
//temporario
typedef void** Lista;

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
*     $P endereco   - endereco do vertice a ser criado.
*	$P valor	  - valor do vertice.
*	$P chave	  - chave do vertice.
*
*  $ED Descricao da funcao
*     Cria um novo vertice.
*     Caso ja exista um vertice, este sera destruido.
*
*  $FV Valor retornado
*     VER_CondRetOK
*     VER_CondRetFaltouMemoria
*
***********************************************************************/

VER_tpCondRet VER_CriarVertice(Vertice* endereco, void* valor, int chave);

/***********************************************************************
*
*  $FC Funcao: VER Inserir Aresta
*
*	$EP Parametros
*     $P vertice    - vertice no qual inserir as arestas.
*	$P aresta	  - aresta para outros vertices a ser inserida.
*
*  $FV Valor retornado
*     VER_CondRetOK
*	VER_CondRetVerticeNaoExiste
*	VER_CondRetArestaNaoExiste - caso o vetor seja nulo.
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
*	VER_CondRetErroInsercao - caso o tipo seja nulo.
*
***********************************************************************/

VER_tpCondRet VER_ModificarTipo(Vertice vertice, VER_TipoVer tipo);


/***********************************************************************
*
*  $FC funcao: VER Destruir vertice
*
*	$EP Parametros
*     $P endereco - endereco do vertice a ser destruido.
*
*  $ED Descricao da funcao
*     Destroi o vertice, anulando o vertice presente no local especificado.
*     Faz nada caso o vertice nao exista.
*
***********************************************************************/

void VER_DestruirVertice(Vertice* endereco);

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

/************************Funcoes adicionais de VERTICE que nao serao testadas*****************************/
//Essas funcoes sao implementadas basicamente com um return e assim dispensam testes.

/***********************************************************************
*
*  $FC Funcao: VER Visitado
*
*	$EP Parametros
*     $P vertice  - o vertice a testar.
*	
*  $ED Descricao da funcao
*	Verifica se o vertice ja foi visitado ou nao.
*	Se nao houver vertice retorna -1.
*
*
*  $FV Valor retornado
*     1 caso o vertice ja tenha sido visitado, do contrario 0.
*
***********************************************************************/

int VER_Visitado(Vertice vertice);

/***********************************************************************
*
*  $FC Funcao: VER Get Chave
*
*	$EP Parametros
*     $P vertice  - o vertice.
*	
*  $ED Descricao da funcao
*	Retorna a chave do vertice.
*	Se nao houver vertice retorna -1.
*
*  $FV Valor retornado
*     A chave do vertice
*
***********************************************************************/

int VER_getChave(Vertice vertice);

/***********************************************************************
*
*  $FC Funcao: VER Get Tipo
*
*	$EP Parametros
*     $P vertice  - o vertice.
*	
*  $ED Descricao da funcao
*	Retorna o tipo do vertice.
*	Se nao houver vertice retorna -1.
*
*  $FV Valor retornado
*     O tipo do vertice
*
***********************************************************************/

VER_TipoVer VER_getTipo(Vertice vertice);

/************************Fim de funcoes adicionais de VERTICE que nao serao testadas*****************************/


/************************Funcoes de acesso a estrutura Aresta*****************************/

/***********************************************************************
*
*  $FC Funcao: VER Criar aresta
*
*	$EP Parametros
*     $P endereco - endereco da aresta a ser inicializada.
*	$P origem	- chave do vertice origem da aresta.
*	$P destino	- chave do vertice destino da aresta
*	$P peso	- peso da aresta (e.g. distancia entre os vertices)
*	$P rotulo	- rotulo da aresta
*	
*  $ED Descricao da funcao
*     Cria uma nova aresta.
*	Esta aresta e' independente de qualquer vertice especifico.
*
*
*  $FV Valor retornado
*     VER_CondRetOK
*     VER_CondRetFaltouMemoria
*
***********************************************************************/

VER_tpCondRet VER_CriarAresta(Aresta* endereco, int origem, int destino, float peso, char* rotulo);

/***********************************************************************
*
*  $FC funcao: VER Destruir aresta
*
*	$EP Parametros
*     $P endereco - endereco da aresta a ser destruida.
*
*  $ED Descricao da funcao
*     Destroi a aresta, anulando a aresta presente no local especificado.
*     Faz nada caso a aresta nao exista.
*
***********************************************************************/

void VER_DestruirAresta(Aresta* endereco);

/***********************************************************************
*
*  $FC Funcao: VER Get chaves da aresta
*
*	$EP Parametros
*     $P aresta   - aresta cujos valores se quer receber.
*	$P chaves	- endereco do array de inteiros onde serao colocaos as chaves da aresta
*	
*  $ED Descricao da funcao
*	Retorna os valores origem e destino das chaves dos vertices da aresta nas respectivas posicoes 0 e 1 do parametro chaves
*
*
*  $FV Valor retornado
*     VER_CondRetOK
*	VER_CondRetArestaNaoExiste
*     VER_CondRetFaltouMemoria
*
***********************************************************************/

VER_tpCondRet VER_GetChaves(Aresta aresta, int** chaves);

/************************Funcoes adicionais de ARESTA que nao serao testadas*****************************/
//Essas funcoes sao implementadas basicamente com um return e assim dispensam testes

/***********************************************************************
*
*  $FC Funcao: VER Get Peso
*
*	$EP Parametros
*     $P aresta  - a aresta.
*	
*  $ED Descricao da funcao
*	Retorna o peso da aresta.
*	Se nao houver aresta retorna -1.
*
*  $FV Valor retornado
*     O peso da aresta
*
***********************************************************************/

float VER_getPeso(Aresta aresta);

/***********************************************************************
*
*  $FC Funcao: VER Get Rotulo
*
*	$EP Parametros
*     $P aresta  - a aresta.
*	
*  $ED Descricao da funcao
*	Retorna o rotulo da aresta.
*	Se nao houver aresta retorna -1.
*
*  $FV Valor retornado
*     O rotulo da aresta
*
***********************************************************************/

char* VER_getRotulo(Aresta aresta);

/************************Fim de funcoes adicionais de ARESTA que nao serao testadas*****************************/

/************************Fim das funcoes de acesso a estrutura Aresta*****************************/

/************************Fim da definicao do modulo Vertice*****************************/