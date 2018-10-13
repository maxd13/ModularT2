#if ! defined( LISTA_ )
#define LISTA_
/***************************************************************************
*
*  $MCD Módulo de definição: LIS  Lista duplamente encadeada
*
*  Arquivo gerado:              LISTA.h
*  Letras identificadoras:      LIS
*
*  Nome da base de software:    Arcabouço para a automação de testes de programas redigidos em C
*  Arquivo da base de software: D:\AUTOTEST\PROJETOS\LISTA.BSW
*
*  Projeto: INF 1301 / 1628 Automatização dos testes de módulos C
*  Gestor:  LES/DI/PUC-Rio
*  Autores: avs, bpf - Breno Perricone Fischer
*
*  $HA Histórico de evolução:
*     Versão  Autor    Data     Observações
*     5       bpf   03/out/2018 criacao de assertivas de entrada e saida
*     4       avs   01/fev/2006 criar linguagem script simbólica
*     3       avs   08/dez/2004 uniformização dos exemplos
*     2       avs   07/jul/2003 unificação de todos os módulos em um só projeto
*     1       avs   16/abr/2003 início desenvolvimento
*
*  $ED Descrição do módulo
*     Implementa listas genéricas duplamente encadeadas.
*     Podem existir n listas em operação simultaneamente.
*     As listas possuem uma cabeça encapsulando o seu estado.
*
*     Cada lista é homogênea quanto ao tipo dos dados que armazena.
*     Cada elemento da lista referencia o valor que contém.
*
*     Os ponteiros para os dados são copiados para elementos da lista.
*        Não é copiado o valor apontado por estes ponteiros.
*
*     O controle da destruição do valor de um elemento a ser excluído
*        é realizado por uma função fornecida pelo usuário.
*
*     Cada lista referencia uma função que determina como devem ser
*        desalocados os dados nela contidos.
*
*     A função de liberação dos valores contidos nos elementos deve
*        assegurar a liberação de todos os espaços referênciados pelo
*        valor contido em um elemento.
*        Esta função é chamada antes de se desalocar um elemento
*        de uma lista.
*        Caso não seja necessário desalocar o valor referenciado pelo
*        elemento, o ponteiro para a função de liberação poderá ser NULL .
*        Caso o elemento da lista seja a única âncora do valor referenciado,
*        esta função deve promover a destruição (free) desse valor e
*        de todos os dados nele ancorados.
*
***************************************************************************/
 
#if defined( LISTA_OWN )
   #define LISTA_EXT
#else
   #define LISTA_EXT extern
#endif

/***** Declarações exportadas pelo módulo *****/

/* Tipo referência para uma lista */

typedef struct LIS_tagLista * LIS_tppLista ;


/***********************************************************************
*
*  $TC Tipo de dados: LIS Condições de retorno
*
*
*  $ED Descrição do tipo
*     Condições de retorno das funções da lista
*
***********************************************************************/

   typedef enum {

         LIS_CondRetOK ,
               /* Concluiu corretamente */

         LIS_CondRetListaVazia ,
               /* A lista não contém elementos */

         LIS_CondRetFimLista ,
               /* Foi atingido o fim de lista */

         LIS_CondRetNaoAchou ,
               /* Não encontrou o valor procurado */

         LIS_CondRetFaltouMemoria
               /* Faltou memória ao tentar criar um elemento de lista */

   } LIS_tpCondRet ;


/***********************************************************************
*
*  $FC Função: LIS  &Criar lista
*
*  $ED Descrição da função
*     Cria uma lista genérica duplamente encadeada.
*     Os possíveis tipos são desconhecidos a priori.
*     A tipagem é implicita.
*     Não existe identificador de tipo associado à lista.
*
*  $EP Parâmetros
*     ExcluirValor  - ponteiro para a função que processa a
*                     exclusão do valor referenciado pelo elemento
*                     a ser excluído.
*                     Ver descrição do módulo.
*
*  $FV Valor retornado
*     Se executou corretamente retorna o ponteiro para a lista.
*     Este ponteiro será utilizado pelas funções que manipulem esta lista.
*
*     Se ocorreu algum erro, por exemplo falta de memória ou dados errados,
*     a função retornara NULL.
*     Não será dada mais informação quanto ao problema ocorrido.
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
*		  que referencia a funçao de destruiçao do valor.
*
***********************************************************************/


/***********************************************************************
*
*  $FC Função: LIS  &Destruir lista
*
*  $ED Descrição da função
*     Destrói a lista fornecida.
*     O parâmetro ponteiro para a lista não é modificado.
*     Se ocorrer algum erro durante a destruição, a lista resultará
*     estruturalmente incorreta.
*     OBS. não existe previsão para possíveis falhas de execução.
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
*		- Ponteiro corrente referencia a lista, na qual não pode ser NULL, a ser excluída.
*
*	Assertivas de saida:
*		- Lista referenciada inicialmente foi excluída, os elementos contidos nela 
*		  inicialmente foram liberados e a cabeça da lista foi limpa.
*		- O parâmetro ponteiro para lista não foi modificado.
*
*
***********************************************************************/

/***********************************************************************
*
*  $FC Função: LIS  &Esvaziar lista
*
*  $ED Descrição da função
*     Elimina todos os elementos, sem contudo eliminar a lista
*
*  $EP Parâmetros
*     pLista - ponteiro para a lista a ser esvaziada
*
***********************************************************************/

   void LIS_EsvaziarLista( LIS_tppLista pLista ) ;


/***********************************************************************
*   LIS Esvaziar lista:
*
*	Assertivas de entrada:
*		- Ponteiro corrente referencia a lista, na qual não pode ser NULL, a ser esvaziada.
*
*	Assertivas de saida:
*		- Lista referenciada inicialmente teve seus elementos liberados e a 
*		  cabeça da lista foi limpa.
*
*
***********************************************************************/

/***********************************************************************
*
*  $FC Função: LIS  &Inserir elemento antes
*
*  $ED Descrição da função
*     Insere novo elemento antes do elemento corrente.
*     Caso a lista esteja vazia, insere o primeiro elemento da lista.
*
*  $EP Parâmetros
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
*		- Ponteiro corrente referencia endereço da lista, após ao qual será inserido o elemento.
*		- Ponteiro para o valor, que pode ser NULL, do novo elemento a ser criado para
*		  ser inserido na lista.
*		- Caso a lista esteja vazia, o elemento a ser inserido será o primeiro da lista.
*
*	Assertivas de saida:
*		- Lista referenciada inicialmente teve o elemento criado, com o valor passado como 
*		  parâmetro, inserido no pAnt (ponteiro para o anterior do corrente).
*		- Se o elemento corrente era NULL, o elemento foi inserido como ponteiro para origem
*		  e como fim da lista (primeiro elemento da lista).
*		- Se o elemento anterior ao corrente era NULL, o elemento foi inserido como ponteiro 
*		  para origem da lista.
*
***********************************************************************/

/***********************************************************************
*
*  $FC Função: LIS  &Inserir elemento após
*
*  $ED Descrição da função
*     Insere novo elemento apás o elemento corrente.
*     Caso a lista esteja vazia, insere o primeiro elemento da lista.
*
*  $EP Parâmetros
*     Parâmetros
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
*		- Ponteiro corrente referencia endereço da lista, anterior ao qual será inserido o elemento.
*		- Ponteiro para o valor, que pode ser NULL, do novo elemento a ser criado para
*		  ser inserido na lista.
*		- Caso a lista esteja vazia, o elemento a ser inserido será o primeiro da lista.
*
*	Assertivas de saida:
*		- Lista referenciada inicialmente teve o elemento criado, com o valor passado como parâmetro,
*		  inserido no pProx (ponteiro para o próximo do corrente). 
*		- Se o elemento corrente era NULL, o elemento foi inserido como ponteiro para origem e como fim
*		  da lista (primeiro elemento da lista).
*		- Se o elemento próximo ao corrente era NULL, o elemento foi inserido como ponteiro para fim da lista.
*
***********************************************************************/


/***********************************************************************
*
*  $FC Função: LIS  &Excluir elemento
*
*  $ED Descrição da função
*     Exclui o elemento corrente da lista dada.
*     Se existir o elemento aa esquerda do corrente será o novo corrente.
*     Se não existir e existir o elemento à direita, este se tornará corrente.
*     Se este também não existir a lista tornou-se vazia.
*
*  $EP Parâmetros
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
*		- Ponteiro corrente referencia lista ao qual elemento corrente será excluído.
*
*	Assertivas de saida:
*		- Elemento anterior ao corrente, passado inicialmente, (pAnt) é o novo elemento 
*	      corrente, caso esse elemento anterior existia no ponteiro para lista passado inicialmente.
*		- Elemento após ao corrente, passado inicialmente, (pProx) é o novo elemento corrente, caso
*         esse elemento após existia e não existia um elemento anterior ao corrente, no ponteiro para
*		  lista passado inicialmente.
*		- A lista era vazia, caso nem o elemento anterior ao corrente, nem o elemento após ao corrente,
*	      passado inicialmente, existia no ponteiro para lista.
*
*
***********************************************************************/

/***********************************************************************
*
*  $FC Função: LIS  &Obter referência para o valor contido no elemento
*
*  $ED Descrição da função
*     Obtem a referência para o valor contido no elemento corrente da lista
*
*  $EP Parâmetros
*     pLista - ponteiro para a lista de onde se quer o valor
*
*  $FV Valor retornado
*     não NULL - se o elemento corrente existe
*     NULL     - se a lista estiver vazia
*                Pode retornar NULL se o valor inserido no elemento for NULL.
*
***********************************************************************/

   void * LIS_ObterValor( LIS_tppLista pLista ) ;


/***********************************************************************
*   LIS Obter valor:
*  
*	Assertivas de entrada:
*		- Ponteiro corrente referencia endereço da lista na qual será obtido o valor
*		  contido no elemento corrente da lista.
*
*	Assertivas de saida:
*		- Ponteiro para o valor referenciado pelo elemento corrente da lista passada
*		  inicialmente, foi retornado, caso a lista não era NULL, nem o elemento corrente.
*		- Foi retornado NULL, caso o elemento corrente era NULL ou a lista.
*
***********************************************************************/

/***********************************************************************
*
*  $FC Função: LIS  &Ir para o elemento inicial
*
*  $ED Descrição da função
*     Torna corrente o primeiro elemento da lista.
*     Faz nada se a lista está vazia.
*
*  $EP Parâmetros
*     pLista - ponteiro para a lista a manipular
*
***********************************************************************/

   void IrInicioLista( LIS_tppLista pLista ) ;


/***********************************************************************
*   LIS Ir para elemento inicial da lista:
*  
*	Assertivas de entrada:
*		- Ponteiro corrente referencia endereço da lista na qual será manipulada.
*
*	Assertivas de saida:
*		- Estado inicial foi preservado (nada foi feito), caso a lista passada
*		  inicialmente era NULL.
*		- Caso contrário, o ponteiro para o elemento corrente tornou-se o ponteiro
*		  para a origem da lista (o primeiro elemento da lista inicial).
*
***********************************************************************/

/***********************************************************************
*
*  $FC Função: LIS  &Ir para o elemento final
*
*  $ED Descrição da função
*     Torna corrente o elemento final da lista.
*     Faz nada se a lista está vazia.
*
*  $EP Parâmetros
*     pLista - ponteiro para a lista a manipular
*
***********************************************************************/

   void IrFinalLista( LIS_tppLista pLista ) ;


/***********************************************************************
*   LIS Ir para elemento final da lista:
*  
*	Assertivas de entrada:
*		- Ponteiro corrente referencia endereço da lista na qual será manipulada.
*
*	Assertivas de saida:
*		- Estado inicial foi preservado (nada foi feito), caso a lista passada
*		  inicialmente era NULL.
*		- Caso contrário, o ponteiro para o elemento corrente tornou-se o ponteiro
*		  para o fim da lista (o último elemento da lista inicial).
*
***********************************************************************/

/***********************************************************************
*
*  $FC Função: LIS  &Avançar elemento
*
*  $ED Descrição da função
*     Avança o elemento corrente numElem elementos na lista
*     Se numElem for positivo avança em direção ao final
*     Se numElem for negativo avança em direção ao início
*     numElem pode ser maior do que o númro de elementos existentes na
*               direção desejada
*     Se numElem for zero somente verifica se a lista está vazia
*
*  $EP Parâmetros
*     pLista  - ponteiro para a lista a ser manipulada
*     numElem - o número de elementos a andar
*
*  $FV Valor retornado
*     CondRetOK         - se numElem elementos tiverem sido andados
*     CondRetFimLista   - se encontrou o fim da lista antes de andar numElem
*                         elementos
*     CondRetListaVazia - se a lista está vazia
*
***********************************************************************/

   LIS_tpCondRet LIS_AvancarElementoCorrente( LIS_tppLista pLista ,
                                              int numElem ) ;

/***********************************************************************
*   LIS Avancar elemento corrente:
*  
*	Assertivas de entrada:
*		- Ponteiro corrente referencia endereço da lista na qual será manipulada.
*		- Número inteiro correspondente ao número de elementos a andar na lista, a partir
*		do elemento corrente. O número inteiro passado pode ser positivo, negativo ou zero
*
*	Assertivas de saida:
*		- A lista passada inicialmente é vazia, caso o elemento corrente inicial era NULL.
*		- O ponteiro para o elemento corrente referencia o número de elementos retrocedidos, 
*		 caso o número inteiro passado como parâmetro era negativo e a lista não chegou ao fim.
*		- O ponteiro para o elemento corrente referencia o número de elementos, caso o número 
*		 inteiro passado como parâmetro era positivo e a lista não chegou ao fim.
*		- O ponteiro para o elemento corrente referencia o fim da lista, caso o número inteiro 
*		 passado como parâmetro era positivo e a lista chegou ao fim.
*		- O ponteiro para o elemento corrente referencia a origem da lista, caso o número inteiro 
*		 passado como parâmetro era negativo e a lista chegou ao início.
*		- A lista foi verificada como vazia ou não, caso o número inteiro passado como parâmetro 
*		 era igual a zero.
*
***********************************************************************/

/***********************************************************************
*
*  $FC Função: LIS  &Procurar elemento contendo valor
*
*  $ED Descrição da função
*     Procura o elemento que referencia o valor dado.
*     A função compara ponteiro e não conteúdo apontado.
*
*  $EP Parâmetros
*     pLista  - ponteiro para a lista onde procura
*     pValor  - ponteiro para o valor procurado
*               Pode ser NULL
*
*  $FV Valor retornado
*     LIS_CondRetOK  - se encontrou.
*                      O elemento corrente é o primeiro elemento do
*                      elemento corrente inclusive para o fim da lista
*                      e que contém o ponteiro procurado
*
*     LIS_CondRetNaoEncontrou - se o ponteiro não foi encontrado
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
*		- Ponteiro corrente referencia endereço da lista na qual será procurado o valor dado.
*		- Ponteiro para o valor que será procurado, podendo ser NULL.
*
*	Assertivas de saida:
*		- A lista passada inicialmente e' vazia, caso o elemento corrente era NULL.
*		- Ponteiro para elemento corrente faz referência ao valor encontrado, 
*		  sendo o primeiro elemento corrente.
*		- Ponteiro para elemento corrente continua o mesmo referenciado inicialmente, 
*		  indicando que não foi encontrado o valor procurado.
*
***********************************************************************/

#undef LISTA_EXT

/********** Fim do módulo de definição: LIS  Lista duplamente encadeada **********/

#else
#endif
