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
*  Autores: lcrv - Luiz Carlos R Viana, bpf - Breno Perricone Fischer
*
*  $HA Historico de evolucao:
*     Versao  Autor    Data     Observacoes
*      2      bpf   3/out/2018 criacao de assertivas de entrada e saida
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
*	Criar vertice:
*
*	Assertivas de entrada:
*		- Ponteiro para endere�o do v�rtice a ser criado, podendo ser inexistente.
*		- Ponteiro para o valor que ser� inserido no v�rtice a ser criado.
*		- Ponteiro para chave que ser� inserida no v�rtice a ser criado.
*		- Argumento da fun��o referencia a fun��o de destrui��o do valor 
*		  referenciado pelo v�rtice a serem exclu�dos.
*
*	Assertivas de sa�da:
*		- Nada foi feito e condi��o de OK retornada, caso o endere�o passado
*		  inicialmente era inexistente.
*		- V�rtice alocado dinamicamente, com tamanho de uma struct do tamanho de vertice,
*		  referenciado pelo ponteiro do endere�o passado inicialmente, os respectivos valores, 
*		  passados como par�metros, atribu�dos ao v�rtice e condi��o de retorno OK.
*		- V�rtice destru�do, anteriormente referenciado pelo ponteiro de endere�o passado 
*		  inicialmente, caso j� existia um v�rtice nesse endere�o e novo v�rtice criado.
*
***********************************************************************/

/***********************************************************************
*
*  $FC Funcao: VER Inserir Aresta
*
*	$EP Parametros
*     $P vertice    - vertice no qual inserir a aresta.
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
*	Inserir aresta:
*
*	Assertivas de entrada:
*		- Ponteiro para o v�rtice, podendo ser inexistente, no qual ser� inserido a aresta.
*		- Ponteiro para a aresta, podendo ser inexistente, a qual ser� inserida.
*
*	Assertivas de sa�da:
*		- Condi��es de retorno respectivas foram retornadas, caso o endere�o da aresta
*		  ou o endere�o do v�rtice passados como par�metro, n�o existiam.
*		- Aresta reflexiva inserida, no ponteiro para reflexiva do v�rtice inicial, caso
*		  a origem e destino da aresta eram iguais.
*		- Nada foi feito e condi��o de retorno OK, caso a aresta j� existia no v�rtice.
*		- Aresta inserida, com ponteiro para antecessor do v�rtice referenciando o endere�o
*		  da aresta passado inicialmente, caso a origem da aresta era diferente da chave do v�rtice.
*		- Aresta inserida, com ponteiro para sucessor do v�rtice referenciando o endere�o da aresta
*		  passado inicialmente, caso o destino da aresta era diferente da chave do v�rtice.
*
***********************************************************************/

/***********************************************************************
*
*  $FC Funcao: VER Remover Aresta
*
*	$EP Parametros
*     $P vertice    - vertice do qual remover a aresta.
*	$P aresta	  - aresta para outros vertices a ser removida.
*
*  $ED Descricao da funcao
*	Remove uma aresta.
*	Caso a aresta nao exista no vertice, nada e' feito e OK e' retornado.
*
*  $FV Valor retornado
*     VER_CondRetOK
*	VER_CondRetVerticeNaoExiste
*	VER_CondRetArestaNaoExiste - caso a aresta seja nula.
*	VER_CondRetErroInsercao	   - caso nem origem nem destino da aresta sejam iguais a chave do vertice.
*
*
***********************************************************************/

VER_tpCondRet VER_RemoverAresta(Vertice vertice, Aresta aresta);

/***********************************************************************
*	Remover Aresta:
*
*	Assertivas de entrada:
*		- Ponteiro para o v�rtice, podendo ser inexistente, no qual a aresta a ser removida est� contida.
*		- Ponteiro para a aresta, podendo ser inexistente, a qual ser� removida.
*
*	Assertivas de sa�da:
*		- Condi��es de retorno respectivas foram retornadas, caso o endere�o da aresta
*		  ou o endere�o do v�rtice passados como par�metro, n�o existiam.
*		- Nada foi modificado e condi��o de retorno Erro de Inser��o retornada, caso a
*		  origem e destino da aresta eram diferentes da chave contida no v�rtice.
*		- Aresta reflexiva destru�da, com ponteiro para reflexiva do v�rtice inicial igualado
*		  a NULL, caso a origem e destino da aresta eram iguais.
*		- Aresta removida e destru�da, com ponteiro para antecessor do v�rtice tendo seu elemento
*		  exclu�do, caso a origem da aresta era diferente da chave do v�rtice.
*		- Aresta removida e destru�da, com ponteiro para sucessor do v�rtice tendo seu elemento
*		  exclu�do, caso o destino da aresta era diferente da chave do v�rtice.
*
***********************************************************************/

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
*	Modificar tipo do vertice:
*
*	Assertivas de entrada:
*		- Ponteiro para v�rtice corrente a ter seu tipo modificado, podendo ser inexistente.
*		- Valor dado a ser modificado do tipo VER_TipoVer (podendo ser inicial = 0, intermedi�rio = 1 e final = 2).
*
*	Assertivas de sa�da:
*		- Nada foi modificado e condi��o de retorno Vertice N�o existe retornada, caso v�rtice inexistente.
*		- Nada foi modificado e condi��o de retorno Erro Inser��o retornada, caso tipo inical passado como par�metro diferente de 0, 1 ou 2.
*		- Ponteiro para tipo do v�rtice passado inicialmente modificado com o novo valor de tipo.
*
***********************************************************************/


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
*	Destruir Vertice:
*
*	Assertivas de entrada:
*		- Ponteiro para v�rtice corrente a ser destru�do, podendo ser inexistente.
*
*	Assertivas de sa�da:
*		- Nada foi modificado, caso v�rtice inexistente.
*		- Ponteiro para aresta reflexiva liberado, ponteiro para excluir valor
*		  referenciado pelo valor do v�rtice, respectivos antecessores e sucessores
*		  existentes do v�rtice destru�dos e v�rtice liberado.
*		- Depois de destru�do o v�rtice nao foi anulado isto deve ser feito pelo caller da fun��o.
*
***********************************************************************/

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
*	Marcar visitado:
*
*	Assertivas de entrada:
*		- Ponteiro para v�rtice corrente a ser marcado, podendo ser inexistente.
*
*	Assertivas de sa�da:
*		- Nada foi modificado e condi��o de retorno Vertice N�o existe retornada,
*		  caso v�rtice inexistente.
*		- Ponteiro para visitado do v�rtice corrente foi marcado como visitado,
*		  caso inicialmente estivesse marcado como n�o visitado ou foi marcado como n�o visitado,
*		  caso inicialmente estivesse marcado como visitado.
*
***********************************************************************/

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
*	Get Valor:
*
*	Assertivas de entrada:
*		- Ponteiro para v�rtice corrente, podendo ser inexistente, do qual o valor ser� obtido.
*		- Ponteiro para endere�o aonde o valor do v�rtice ser� colocado, podendo ser inv�lido.
*
*	Assertivas de sa�da:
*		- Nada foi obtido e condi��o de retorno OK retornada, caso o endere�o
*		  passado como par�metro era inv�lido.
*		- Nada foi obtido e condi��o de retorno Vertice N�o existe retornada,
*		  caso v�rtice inexistente.
*		- Ponteiro do endere�o passado como par�metro teve o valor atribu�do com
*		  o ponteiro para o valor do v�rtice, passado inicialmente.
*
***********************************************************************/

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
*
***********************************************************************/

VER_tpCondRet VER_getSucessores(Vertice vertice, LIS_tppLista* enderecoSucessores);

/***********************************************************************
*	Get sucessores:
*
*	Assertivas de entrada:
*		- Ponteiro para v�rtice corrente, podendo ser inexistente, do qual o sucessor ser� obtido.
*		- Ponteiro para endereco do tipo LIS_tppLista aonde o sucessor do v�rtice ser� colocado, podendo ser inv�lido.
*
*	Assertivas de saida:
*		- Nada foi obtido e condi��o de retorno OK retornada, caso o endere�o
*		  passado como par�metro era inv�lido.
*		- Nada foi obtido e condi��o de retorno Vertice N�o existe retornada,
*		  caso v�rtice inexistente.
*		- Ponteiro do endere�o passado como par�metro teve o valor NULL atribu�do,
*		  caso o sucessor era inexistente.
*		- Ponteiro do endere�o passado como par�metro teve o valor atribu�do com
*		  o ponteiro para a lista de arestar de sucessoras do v�rtice, passado inicialmente. 
*
***********************************************************************/

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
*	Get antecessores:
*
*	Assertivas de entrada:
*		- Ponteiro para v�rtice corrente, podendo ser inexistente, do qual o antecessor ser� obtido.
*		- Ponteiro para endereco do tipo LIS_tppLista aonde o antecessor do v�rtice ser� colocado, podendo ser inv�lido.
*
*	Assertivas de saida:
*		- Nada foi obtido e condi��o de retorno OK retornada, caso o endere�o
*		  passado como par�metro era inv�lido.
*		- Nada foi obtido e condi��o de retorno Vertice N�o existe retornada,
*		  caso v�rtice inexistente.
*		- Ponteiro do endere�o passado como par�metro teve o valor NULL atribu�do,
*		  caso o antecessor era inexistente.
*		- Ponteiro do endere�o passado como par�metro teve o valor atribu�do com
*		  o ponteiro para a lista de arestas de antecessores do v�rtice, passado inicialmente. 
*
***********************************************************************/

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

/***********************************************************************
*	Get reflexiva:
*
*	Assertivas de entrada:
*		- Ponteiro para v�rtice corrente, podendo ser inexistente, do qual a aresta reflexiva ser� obtida.
*		- Ponteiro para endereco do tipo Aresta aonde a aresta reflexiva do v�rtice ser� colocado, podendo ser inv�lido.
*
*	Assertivas de saida:
*		- Nada foi obtido e condi��o de retorno OK retornada, caso o endere�o
*		  passado como par�metro era inv�lido.
*		- Nada foi obtido e condi��o de retorno Vertice N�o existe retornada,
*		  caso v�rtice inexistente.
*		- Ponteiro do endere�o passado como par�metro teve o valor NULL atribu�do,
*		  caso n�o existia aresta sendo apontada pelo v�rtice.
*		- Ponteiro do endere�o passado como par�metro teve o valor atribu�do com
*		  o ponteiro para a aresta reflexiva do v�rtice, passado inicialmente.
*
***********************************************************************/


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
***********************************************************************/

VER_tpCondRet VER_Visitado(Vertice vertice, int* endereco);

/***********************************************************************
*	Ver visitado:
*
*	Assertivas de entrada:
*		- Ponteiro para vertice corrente, podendo ser inexistente, que sera vertificado se ja foi visitado ou nao.
*		- Ponteiro para endereco do tipo inteiro, aonde sera colocado o valor de verificacao, podendo ser inv�lido.
*
*	Assertivas de saida:
*		- Nada foi obtido e condi��o de retorno OK retornada, caso o endere�o
*		  passado como par�metro era inv�lido.
*		- Nada foi obtido e condi��o de retorno Vertice N�o existe retornada,
*		  caso v�rtice inexistente.
*		- Ponteiro do endere�o passado como par�metro teve o valor atribu�do com
*		  o ponteiro para visitado do v�rtice (tipo inteiro), passado inicialmente, sendo este valor
*		  igual a 1, caso ja tenha sido visitado ou 0, caso contr�rio.
*
***********************************************************************/

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
*	Get chave:
*
*	Assertivas de entrada:
*		- Ponteiro para vertice corrente, podendo ser inexistente, do qual ser� obtida a chave.
*		- Ponteiro para endereco do tipo inteiro, aonde sera colocado o valor da chave do vertice, podendo ser invalido.
*
*	Assertivas de saida:
*		- Nada foi obtido e condi��o de retorno OK retornada, caso o endere�o
*		  passado como par�metro era inv�lido.
*		- Nada foi obtido e condi��o de retorno Vertice N�o existe retornada,
*		  caso v�rtice inexistente.
*		- Ponteiro do endere�o passado como par�metro teve o valor atribu�do com
*		  o ponteiro para a chave do v�rtice (tipo inteiro), passado inicialmente.
*
***********************************************************************/

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

/***********************************************************************
*	Get tipo do vertice:
*
*	Assertivas de entrada:
*		- Ponteiro para vertice corrente, podendo ser inexistente, do qual ser� obtido o tipo do vertice.
*		- Ponteiro para endereco do tipo VER_TipoVer, aonde sera colocado o valor do tipo do vertice, podendo ser invalido.
*
*	Assertivas de saida:
*		- Nada foi obtido e condi��o de retorno OK retornada, caso o endere�o
*		  passado como par�metro era inv�lido.
*		- Nada foi obtido e condi��o de retorno Vertice N�o existe retornada,
*		  caso v�rtice inexistente.
*		- Ponteiro do endere�o passado como par�metro teve o valor atribu�do com
*		  o ponteiro para o tipo do v�rtice (tipo VER_TipoVer), passado inicialmente.
*
***********************************************************************/

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
*	Criar aresta:
*
*	Assertivas de entrada:
*		- Ponteiro para endere�o da aresta a ser criada, podendo ser inexistente.
*		- Inteiro referente a chave do vertice de origem da aresta.
*		- Inteiro referente a chave do vertice de destino da aresta.
*		- Ponteiro para char, fazendo referencia a uma string, correspondente
*		  ao rotulo da aresta.
*
*	Assertivas de sa�da:
*		- Nada foi feito e condi��o de OK retornada, caso o endere�o passado
*		  inicialmente era inexistente.
*		- Aresta alocada dinamicamente, com tamanho de uma struct do tamanho de aresta,
*		  referenciado pelo ponteiro do endere�o passado inicialmente, com os respectivos valores, 
*		  passados como par�metros, atribu�dos a aresta e condi��o de retorno OK.
*		- Aresta destru�da, anteriormente referenciado pelo ponteiro de endere�o passado 
*		  inicialmente, caso j� existia uma aresta nesse endere�o e nova aresta criada, com condicao de
*		  retorno OK retornada.
*
***********************************************************************/

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
*	Destruir Aresta:
*	Assertivas de entrada:
*		- Ponteiro para aresta a ser destru�da, podendo ser inexistente.
*
*	Assertivas de sa�da:
*		- Nada foi modificado, caso aresta inexistente.
*		- Aresta, passada como par�metro, liberada.
*		- Depois de destru�da a aresta, nao foi anulada. Isto deve ser feito pelo caller da fun��o.
*
*
***********************************************************************/

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
*	Get chaves:
*	Assertivas de entrada:
*		- Ponteiro para aresta, podendo ser inexistente, da qual serao obtidas as chaves.
*		- Endereco do array estatico, de tamanho 2, de inteiros onde serao colocaos as chaves da aresta.
*
*	Assertivas de sa�da:
*		- Nada foi feito e condi��o de OK retornada, caso o parametro chaves passado
*		  inicialmente era NULL.
*		- Nada foi obtido e condi��o de retorno Aresta N�o existe retornada,
*		  caso aresta inexistente.
*		- Primeira posicao do array, passado como par�metro, teve o valor atribu�do com
*		  o ponteiro para o valor de origem da aresta e, na segunda posicao, com o ponteiro para
*		  o valor de destino da aresta.
*
*
***********************************************************************/

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

/***********************************************************************
*	Get rotulo:
*	Assertivas de entrada:
*		- Ponteiro para aresta, podendo ser inexistente, da qual sera obtido o rotulo.
*		- Endereco do ponteiro para array de caracteres no qual colocar o valor do rotulo.
*
*	Assertivas de sa�da:
*		- Nada foi feito e condi��o de OK retornada, caso o endere�o passado
*		  inicialmente era inexistente.
*		- Nada foi obtido e condi��o de retorno Aresta N�o existe retornada,
*		  caso aresta inexistente.
*		- Ponteiro para array, passado como parametro, teve valor atribuido com o ponteiro para o 
*		  rotulo da aresta, enviada inicialmente como parametro.
*
*
***********************************************************************/

/************************Fim das funcoes de acesso a estrutura Aresta*****************************/

/************************Fim da definicao do modulo Vertice*****************************/