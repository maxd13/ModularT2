#if ! defined( LISTA_ )
#define LISTA_
/***************************************************************************
*
*  $MCD M?dulo de defini??o: LIS  Lista duplamente encadeada
*
*  Arquivo gerado:              LISTA.h
*  Letras identificadoras:      LIS
*
*  Nome da base de software:    Arcabou?o para a automa??o de testes de programas redigidos em C
*  Arquivo da base de software: D:\AUTOTEST\PROJETOS\LISTA.BSW
*
*  Projeto: INF 1301 / 1628 Automatiza??o dos testes de m?dulos C
*  Gestor:  LES/DI/PUC-Rio
*  Autores: avs, bpf - Breno Perricone Fischer
*
*  $HA Hist?rico de evolu??o:
*     Vers?o  Autor    Data     Observa??es
*     5       bpf   03/out/2018 criacao de assertivas de entrada e saida
*     4       avs   01/fev/2006 criar linguagem script simb?lica
*     3       avs   08/dez/2004 uniformiza??o dos exemplos
*     2       avs   07/jul/2003 unifica??o de todos os m?dulos em um s? projeto
*     1       avs   16/abr/2003 in?cio desenvolvimento
*
*  $ED Descri??o do m?dulo
*     Implementa listas gen?ricas duplamente encadeadas.
*     Podem existir n listas em opera??o simultaneamente.
*     As listas possuem uma cabe?a encapsulando o seu estado.
*
*     Cada lista ? homog?nea quanto ao tipo dos dados que armazena.
*     Cada elemento da lista referencia o valor que cont?m.
*
*     Os ponteiros para os dados s?o copiados para elementos da lista.
*        N?o ? copiado o valor apontado por estes ponteiros.
*
*     O controle da destrui??o do valor de um elemento a ser exclu?do
*        ? realizado por uma fun??o fornecida pelo usu?rio.
*
*     Cada lista referencia uma fun??o que determina como devem ser
*        desalocados os dados nela contidos.
*
*     A fun??o de libera??o dos valores contidos nos elementos deve
*        assegurar a libera??o de todos os espa?os refer?nciados pelo
*        valor contido em um elemento.
*        Esta fun??o ? chamada antes de se desalocar um elemento
*        de uma lista.
*        Caso n?o seja necess?rio desalocar o valor referenciado pelo
*        elemento, o ponteiro para a fun??o de libera??o poder? ser NULL .
*        Caso o elemento da lista seja a ?nica ?ncora do valor referenciado,
*        esta fun??o deve promover a destrui??o (free) desse valor e
*        de todos os dados nele ancorados.
*
***************************************************************************/
 
#if defined( LISTA_OWN )
   #define LISTA_EXT
#else
   #define LISTA_EXT extern
#endif

/***** Declara??es exportadas pelo m?dulo *****/

/* Tipo refer?ncia para uma lista */

typedef struct LIS_tagLista * LIS_tppLista ;


/***********************************************************************
*
*  $TC Tipo de dados: LIS Condi??es de retorno
*
*
*  $ED Descri??o do tipo
*     Condi??es de retorno das fun??es da lista
*
***********************************************************************/

   typedef enum {

         LIS_CondRetOK ,
               /* Concluiu corretamente */

         LIS_CondRetListaVazia ,
               /* A lista n?o cont?m elementos */

         LIS_CondRetFimLista ,
               /* Foi atingido o fim de lista */

         LIS_CondRetNaoAchou ,
               /* N?o encontrou o valor procurado */

         LIS_CondRetFaltouMemoria
               /* Faltou mem?ria ao tentar criar um elemento de lista */

   } LIS_tpCondRet ;


/***********************************************************************
*
*  $FC Fun??o: LIS  &Criar lista
*
*  $ED Descri??o da fun??o
*     Cria uma lista gen?rica duplamente encadeada.
*     Os poss?veis tipos s?o desconhecidos a priori.
*     A tipagem ? implicita.
*     N?o existe identificador de tipo associado ? lista.
*
*  $EP Par?metros
*     ExcluirValor  - ponteiro para a fun??o que processa a
*                     exclus?o do valor referenciado pelo elemento
*                     a ser exclu?do.
*                     Ver descri??o do m?dulo.
*
*  $FV Valor retornado
*     Se executou corretamente retorna o ponteiro para a lista.
*     Este ponteiro ser? utilizado pelas fun??es que manipulem esta lista.
*
*     Se ocorreu algum erro, por exemplo falta de mem?ria ou dados errados,
*     a fun??o retornara NULL.
*     N?o ser? dada mais informa??o quanto ao problema ocorrido.
*
***********************************************************************/

   LIS_tppLista LIS_CriarLista(
             void   ( * ExcluirValor ) ( void * pDado ) ) ;

/***********************************************************************
*   LIS Criar lista:
*  
*	Assertivas de entrada: 
*		- Argumento da funcao referencia a funcao de destruicao do valor contido
*		  nos elementos a serem excluidos.
*		- Argumento da funcao e' diferente de NULL.
*
*	Assertivas de saida:
*		- Ponteiro corrente referencia lista alocada dinamicamente, com tamanho 
*		  da struct de Lista.
*		- Conteudo da lista com ponteiro corrente igualado a NULL e valor de 
*		  pLista->ExcluirValor e' igualado ao ponteiro passado como parametro 
*		  que referencia a fun?ao de destrui?ao do valor.
*
***********************************************************************/


/***********************************************************************
*
*  $FC Fun??o: LIS  &Destruir lista
*
*  $ED Descri??o da fun??o
*     Destr?i a lista fornecida.
*     O par?metro ponteiro para a lista n?o ? modificado.
*     Se ocorrer algum erro durante a destrui??o, a lista resultar?
*     estruturalmente incorreta.
*     OBS. n?o existe previs?o para poss?veis falhas de execu??o.
*
*  $FV Valor retornado
*     LIS_CondRetOK    - destruiu sem problemas
*
*
***********************************************************************/

   void LIS_DestruirLista( LIS_tppLista pLista ) ;


/***********************************************************************
*   LIS Destruir lista:
*  
*	Assertivas de entrada:
*		- Ponteiro corrente referencia a lista, na qual n?o pode ser NULL, a ser exclu?da.
*
*	Assertivas de saida:
*		- Lista referenciada inicialmente foi exclu?da, os elementos contidos nela 
*		  inicialmente foram liberados e a cabe?a da lista foi limpa.
*		- O par?metro ponteiro para lista n?o foi modificado.
*
*
***********************************************************************/

/***********************************************************************
*
*  $FC Fun??o: LIS  &Esvaziar lista
*
*  $ED Descri??o da fun??o
*     Elimina todos os elementos, sem contudo eliminar a lista
*
*  $EP Par?metros
*     pLista - ponteiro para a lista a ser esvaziada
*
***********************************************************************/

   void LIS_EsvaziarLista( LIS_tppLista pLista ) ;


/***********************************************************************
*   LIS Esvaziar lista:
*
*	Assertivas de entrada:
*		- Ponteiro corrente referencia a lista, na qual n?o pode ser NULL, a ser esvaziada.
*
*	Assertivas de saida:
*		- Lista referenciada inicialmente teve seus elementos liberados e a 
*		  cabe?a da lista foi limpa.
*
*
***********************************************************************/

/***********************************************************************
*
*  $FC Fun??o: LIS  &Inserir elemento antes
*
*  $ED Descri??o da fun??o
*     Insere novo elemento antes do elemento corrente.
*     Caso a lista esteja vazia, insere o primeiro elemento da lista.
*
*  $EP Par?metros
*     pLista - ponteiro para a lista onde deve ser inserido o elemento
*     pValor - ponteiro para o valor do novo elemento
*              Pode ser NULL
*
*  $FV Valor retornado
*     LIS_CondRetOK
*     LIS_CondRetFaltouMemoria
*
***********************************************************************/

   LIS_tpCondRet LIS_InserirElementoAntes( LIS_tppLista pLista ,
                                           void * pValor        ) ;


/***********************************************************************
*   LIS Inserir elemento antes:
*
*	Assertivas de entrada:
*		- Ponteiro corrente referencia endere?o da lista, ap?s ao qual ser? inserido o elemento.
*		- Ponteiro para o valor, que pode ser NULL, do novo elemento a ser criado para
*		  ser inserido na lista.
*		- Caso a lista esteja vazia, o elemento a ser inserido ser? o primeiro da lista.
*
*	Assertivas de saida:
*		- Lista referenciada inicialmente teve o elemento criado, com o valor passado como 
*		  par?metro, inserido no pAnt (ponteiro para o anterior do corrente).
*		- Se o elemento corrente era NULL, o elemento foi inserido como ponteiro para origem
*		  e como fim da lista (primeiro elemento da lista).
*		- Se o elemento anterior ao corrente era NULL, o elemento foi inserido como ponteiro 
*		  para origem da lista.
*
***********************************************************************/

/***********************************************************************
*
*  $FC Fun??o: LIS  &Inserir elemento ap?s
*
*  $ED Descri??o da fun??o
*     Insere novo elemento ap?s o elemento corrente.
*     Caso a lista esteja vazia, insere o primeiro elemento da lista.
*
*  $EP Par?metros
*     Par?metros
*        pLista - ponteiro para a lista onde deve ser inserido o elemento
*        pValor - ponteiro para o valor do novo elemento
*                 Pode ser NULL
*           
*
*  $FV Valor retornado
*     Valor retornado
*        LIS_CondRetOK
*        LIS_CondRetFaltouMemoria
*
***********************************************************************/

   LIS_tpCondRet LIS_InserirElementoApos( LIS_tppLista pLista ,
                                          void * pValor        )
       ;

/***********************************************************************
*   LIS Inserir elemento apos:
*
*	Assertivas de entrada:
*		- Ponteiro corrente referencia endere?o da lista, anterior ao qual ser? inserido o elemento.
*		- Ponteiro para o valor, que pode ser NULL, do novo elemento a ser criado para
*		  ser inserido na lista.
*		- Caso a lista esteja vazia, o elemento a ser inserido ser? o primeiro da lista.
*
*	Assertivas de saida:
*		- Lista referenciada inicialmente teve o elemento criado, com o valor passado como par?metro,
*		  inserido no pProx (ponteiro para o pr?ximo do corrente). 
*		- Se o elemento corrente era NULL, o elemento foi inserido como ponteiro para origem e como fim
*		  da lista (primeiro elemento da lista).
*		- Se o elemento pr?ximo ao corrente era NULL, o elemento foi inserido como ponteiro para fim da lista.
*
***********************************************************************/


/***********************************************************************
*
*  $FC Fun??o: LIS  &Excluir elemento
*
*  $ED Descri??o da fun??o
*     Exclui o elemento corrente da lista dada.
*     Se existir o elemento aa esquerda do corrente ser? o novo corrente.
*     Se n?o existir e existir o elemento ? direita, este se tornar? corrente.
*     Se este tamb?m n?o existir a lista tornou-se vazia.
*
*  $EP Par?metros
*     pLista    - ponteiro para a lista na qual deve excluir.
*
*  $FV Valor retornado
*     LIS_CondRetOK
*     LIS_CondRetListaVazia
*
***********************************************************************/

   LIS_tpCondRet LIS_ExcluirElemento( LIS_tppLista pLista ) ;


/***********************************************************************
*   LIS Excluir elemento:
*
*	Assertivas de entrada:
*		- Ponteiro corrente referencia lista ao qual elemento corrente ser? exclu?do.
*
*	Assertivas de saida:
*		- Elemento anterior ao corrente, passado inicialmente, (pAnt) ? o novo elemento 
*	      corrente, caso esse elemento anterior existia no ponteiro para lista passado inicialmente.
*		- Elemento ap?s ao corrente, passado inicialmente, (pProx) ? o novo elemento corrente, caso
*         esse elemento ap?s existia e n?o existia um elemento anterior ao corrente, no ponteiro para
*		  lista passado inicialmente.
*		- A lista era vazia, caso nem o elemento anterior ao corrente, nem o elemento ap?s ao corrente,
*	      passado inicialmente, existia no ponteiro para lista.
*
*
***********************************************************************/

/***********************************************************************
*
*  $FC Fun??o: LIS  &Obter refer?ncia para o valor contido no elemento
*
*  $ED Descri??o da fun??o
*     Obtem a refer?ncia para o valor contido no elemento corrente da lista
*
*  $EP Par?metros
*     pLista - ponteiro para a lista de onde se quer o valor
*
*  $FV Valor retornado
*     n?o NULL - se o elemento corrente existe
*     NULL     - se a lista estiver vazia
*                Pode retornar NULL se o valor inserido no elemento for NULL.
*
***********************************************************************/

   void * LIS_ObterValor( LIS_tppLista pLista ) ;


/***********************************************************************
*   LIS Obter valor:
*  
*	Assertivas de entrada:
*		- Ponteiro corrente referencia endere?o da lista na qual ser? obtido o valor
*		  contido no elemento corrente da lista.
*
*	Assertivas de saida:
*		- Ponteiro para o valor referenciado pelo elemento corrente da lista passada
*		  inicialmente, foi retornado, caso a lista n?o era NULL, nem o elemento corrente.
*		- Foi retornado NULL, caso o elemento corrente era NULL ou a lista.
*
***********************************************************************/

/***********************************************************************
*
*  $FC Fun??o: LIS  &Ir para o elemento inicial
*
*  $ED Descri??o da fun??o
*     Torna corrente o primeiro elemento da lista.
*     Faz nada se a lista est? vazia.
*
*  $EP Par?metros
*     pLista - ponteiro para a lista a manipular
*
***********************************************************************/

   void IrInicioLista( LIS_tppLista pLista ) ;


/***********************************************************************
*   LIS Ir para elemento inicial da lista:
*  
*	Assertivas de entrada:
*		- Ponteiro corrente referencia endere?o da lista na qual ser? manipulada.
*
*	Assertivas de saida:
*		- Estado inicial foi preservado (nada foi feito), caso a lista passada
*		  inicialmente era NULL.
*		- Caso contr?rio, o ponteiro para o elemento corrente tornou-se o ponteiro
*		  para a origem da lista (o primeiro elemento da lista inicial).
*
***********************************************************************/

/***********************************************************************
*
*  $FC Fun??o: LIS  &Ir para o elemento final
*
*  $ED Descri??o da fun??o
*     Torna corrente o elemento final da lista.
*     Faz nada se a lista est? vazia.
*
*  $EP Par?metros
*     pLista - ponteiro para a lista a manipular
*
***********************************************************************/

   void IrFinalLista( LIS_tppLista pLista ) ;


/***********************************************************************
*   LIS Ir para elemento final da lista:
*  
*	Assertivas de entrada:
*		- Ponteiro corrente referencia endere?o da lista na qual ser? manipulada.
*
*	Assertivas de saida:
*		- Estado inicial foi preservado (nada foi feito), caso a lista passada
*		  inicialmente era NULL.
*		- Caso contr?rio, o ponteiro para o elemento corrente tornou-se o ponteiro
*		  para o fim da lista (o ?ltimo elemento da lista inicial).
*
***********************************************************************/

/***********************************************************************
*
*  $FC Fun??o: LIS  &Avan?ar elemento
*
*  $ED Descri??o da fun??o
*     Avan?a o elemento corrente numElem elementos na lista
*     Se numElem for positivo avan?a em dire??o ao final
*     Se numElem for negativo avan?a em dire??o ao in?cio
*     numElem pode ser maior do que o n?mro de elementos existentes na
*               dire??o desejada
*     Se numElem for zero somente verifica se a lista est? vazia
*
*  $EP Par?metros
*     pLista  - ponteiro para a lista a ser manipulada
*     numElem - o n?mero de elementos a andar
*
*  $FV Valor retornado
*     CondRetOK         - se numElem elementos tiverem sido andados
*     CondRetFimLista   - se encontrou o fim da lista antes de andar numElem
*                         elementos
*     CondRetListaVazia - se a lista est? vazia
*
***********************************************************************/

   LIS_tpCondRet LIS_AvancarElementoCorrente( LIS_tppLista pLista ,
                                              int numElem ) ;

/***********************************************************************
*   LIS Avancar elemento corrente:
*  
*	Assertivas de entrada:
*		- Ponteiro corrente referencia endere?o da lista na qual ser? manipulada.
*		- N?mero inteiro correspondente ao n?mero de elementos a andar na lista, a partir
*		do elemento corrente. O n?mero inteiro passado pode ser positivo, negativo ou zero
*
*	Assertivas de saida:
*		- A lista passada inicialmente ? vazia, caso o elemento corrente inicial era NULL.
*		- O ponteiro para o elemento corrente referencia o n?mero de elementos retrocedidos, 
*		 caso o n?mero inteiro passado como par?metro era negativo e a lista n?o chegou ao fim.
*		- O ponteiro para o elemento corrente referencia o n?mero de elementos, caso o n?mero 
*		 inteiro passado como par?metro era positivo e a lista n?o chegou ao fim.
*		- O ponteiro para o elemento corrente referencia o fim da lista, caso o n?mero inteiro 
*		 passado como par?metro era positivo e a lista chegou ao fim.
*		- O ponteiro para o elemento corrente referencia a origem da lista, caso o n?mero inteiro 
*		 passado como par?metro era negativo e a lista chegou ao in?cio.
*		- A lista foi verificada como vazia ou n?o, caso o n?mero inteiro passado como par?metro 
*		 era igual a zero.
*
***********************************************************************/

/***********************************************************************
*
*  $FC Fun??o: LIS  &Procurar elemento contendo valor
*
*  $ED Descri??o da fun??o
*     Procura o elemento que referencia o valor dado.
*     A fun??o compara ponteiro e n?o conte?do apontado.
*
*  $EP Par?metros
*     pLista  - ponteiro para a lista onde procura
*     pValor  - ponteiro para o valor procurado
*               Pode ser NULL
*
*  $FV Valor retornado
*     LIS_CondRetOK  - se encontrou.
*                      O elemento corrente ? o primeiro elemento do
*                      elemento corrente inclusive para o fim da lista
*                      e que cont?m o ponteiro procurado
*
*     LIS_CondRetNaoEncontrou - se o ponteiro n?o foi encontrado
*                      O elemento corrente continua o mesmo
*     LIS_CondRetListaVazia   - se a lista estiver vazia
*
***********************************************************************/

   LIS_tpCondRet LIS_ProcurarValor( LIS_tppLista pLista ,
                                    void * pValor        ) ;

/***********************************************************************
*   LIS Procurar valor:
*  
*	Assertivas de entrada:
*		- Ponteiro corrente referencia endere?o da lista na qual ser? procurado o valor dado.
*		- Ponteiro para o valor que ser? procurado, podendo ser NULL.
*
*	Assertivas de saida:
*		- A lista passada inicialmente e' vazia, caso o elemento corrente era NULL.
*		- Ponteiro para elemento corrente faz refer?ncia ao valor encontrado, 
*		  sendo o primeiro elemento corrente.
*		- Ponteiro para elemento corrente continua o mesmo referenciado inicialmente, 
*		  indicando que n?o foi encontrado o valor procurado.
*
***********************************************************************/

#undef LISTA_EXT

/********** Fim do m?dulo de defini??o: LIS  Lista duplamente encadeada **********/

#else
#endif
