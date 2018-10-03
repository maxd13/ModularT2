/***************************************************************************
*  $MCI Modulo de implementacao: Modulo de teste especifico
*
*  Arquivo gerado:              TESGRP.C
*  Letras identificadoras:      TGRP
*
*  Nome da base de software:    Segundo Trabalho de Programacao Modular
*
*  Projeto: Disciplinas INF 1628 / 1301
*  Gestor:  DI/PUC-Rio
*  Autores: bpf - Breno Perricone Fischer e lab - Larissa Alves Binatti
*
*  $HA Historico de evolucaoo:
*     Versao  Autor    Data     Observacoes
*	1.10   bpf   26/09/2018 Melhoria da documentacao e implementacao do modulo
*	1.00   bpf   21/09/2018 Inicio do desenvolvimento
*  $ED Descricao do modulo
*     Este modulo contem as funcoes especificas para o teste do
*     modulo Vertice.
*
*  $EIU Interface com o usuario pessoa
*     Comandos de teste especificos para testar o modulo vertice utilizados como auxiliares no teste de grafos:
*
*     "=VERiniciar"     - inicia o contexto de teste
*     "=VERresetar"     - reinicia o contexto de teste, destruindo primeiro.
*     "=VERcriarver"    - chama a funcao VER_CriarVertice( )
*     "=VERcriarare"    - chama a funcao VER_CriarAresta( )
*     "=VERdestver"     - chama a funcao VER_DestruirVertice( )
*     "=VERdestare"     - chama a funcao VER_DestruirAresta( )
*	"=VERremovare"    - chama a funcao VER_RemoverAresta ( )
*     "=VERinsare"      - chama a funcao VER_InserirAresta( )               
*     "=VERmodif"       - chama a funcao VER_ModificarTipo( )
*     "=VERmarcar"      - chama a funcao VER_MarcVERisitado( )
*     "=VERvisitado"    - chama a funcao VER_Visitado( )
*     "=VERgetvalor"    - chama a funcao VER_getValor( )
*	"=VERgetsucessor" - chama a funcao VER_getSucessores( )
*	"=VERgetante"	- chama a funcao VER_getAntecessores ( )
*	"=VERgetrefle"    - chama a funcao VER_getReflexiva ( )
*     "=VERgetchave"    - chama a funcao VER_getChave( )
*     "=VERgettipo"     - chama a funcao VER_getTipo( )
*     "=VERgetrotulo"   - chama a funcao VER_getRotulo( )
*     "=VERgetchaves"   - chama a funcao VER_GetChaves( )
*
*     Comandos de teste especificos para testar o modulo grafo:
*
*	"=GRPcria"		   - chama a funcao GRP_CriarGrafo( )
*	"=GRPdestroi"	   - chama a funcao GRP_DestruirGrafo( )
*	"=GRPinserevertice"  - chama a funcao GRP_InserirVertice( )
*	"=GRPinserearesta"   - chama a funcao GRP_InserirAresta( )
*	"=GRPremovevertice"  - chama a funcao GRP_RemoverVertice( ) 
*	"=GRPremovearesta"   - chama a funcao GRP_RemoverAresta( )
*	"=GRPverticedechave" - chama a funcao VerticedeChave( )
*
*
***************************************************************************/

#include <string.h>
#include <stdio.h>
#include <malloc.h>
#include "TST_Espc.h"
#include "generico.h"
#include "lerparm.h"
#include "grafo.h"


/* Tabela dos nomes dos comandos de teste de vertices especificos */

#define VER_CRIAR_VER_CMD	  "=VERcriarver"
#define VER_CRIAR_ARE_CMD       "=VERcriarare"
#define VER_DEST_VER_CMD	  "=VERdestver"
#define VER_DEST_ARE_CMD        "=VERdestare" 
#define VER_REMOV_ARE_CMD	  "=VERremovare" 
#define VER_INS_ARE_CMD	        "=VERinsare"
#define VER_MODIF_CMD	 	  "=VERmodif" 
#define VER_MARCAR_CMD          "=VERmarcar" 
#define VER_VISITADO_CMD        "=VERvisitado" 
#define VER_GET_VALOR_CMD       "=VERgetvalor" 
#define VER_GET_SUC_CMD		  "=VERgetsucessor" 
#define VER_GET_ANT_CMD		  "=VERgetante" 
#define VER_GET_REF_CMD		  "=VERgetrefle" 
#define VER_GET_CHAVE_CMD       "=VERgetchave" 
#define VER_GET_TIPO_CMD        "=VERgettipo" 
#define VER_GET_CHAVES_CMD      "=VERgetchaves" 
#define VER_GET_ROTULO_CMD      "=VERgetrotulo" 

/* Tabela dos nomes dos comandos de teste de grafo especificos */
#define GRP_START_CMD		    "=iniciar"
#define GRP_RESET_CMD		    "=resetar" 
#define GRP_CRIAR_CMD		    "=GRPcria" 
#define GRP_DESTRUIR_CMD	    "=GRPdestroi" 
#define GRP_INSERIR_VERT_CMD	    "=GRPinserevertice" 
#define GRP_INSERIR_ARESTA_CMD    "=GRPinserearesta" 
#define GRP_REMOVER_VERT_CMD	    "=GRPremovevertice" 
#define GRP_REMOVER_ARESTA_CMD    "=GRPremovearesta" 
#define GRP_VERT_CHAVE_CMD	    "=GRPverticedechave"

#define MAX_NUM 100
#define DIM_VT 10
#define MAX_LABEL_SIZE 20

Vertice vtVertice[ DIM_VT ] ;
Aresta vtAresta[ DIM_VT ] ;
Grafo vtGrafo[ DIM_VT ];
char* StrBuffer[MAX_NUM];
int pos = 0;

/***** Prototipos das funcoes encapuladas no modulo *****/

	static int VerificarInx( int inx ) ;

/*****  Codigo das funcoes exportadas pelo modulo  *****/


/***********************************************************************
*
*  $FC Funcao: TGRP Efetuar operacoes de teste especificas para vertice e grafo
*
*  $ED Descricao da funcao
*     Efetua os diversos comandos de teste especificos para os modulos
*     vertice e grafo sendo testado.
*     Podem ser criados ate 10 vertices, identificados pelos indices 0 a 10
*
*  $EP Parametros
*     $P ComandoTeste - String contendo o comando
*
*  $FV Valor retornado
*     Ver TST_tpCondRet definido em TST_ESPC.H
*
***********************************************************************/
	TST_tpCondRet TST_EfetuarComando(char * ComandoTeste)
	{
		GRP_tpCondRet CondRetObtido = GRP_CondRetOK;
		GRP_tpCondRet CondRetEsperada = GRP_CondRetFaltouMemoria;

		int inxVertice = -1;
		int inxAresta = -1;
		int inxGrafo = -1;

		int ValorObtido = -1;
		int ValorEsperado = -1;

		TST_tpCondRet Ret;

		int  NumLidos = -1;
		int i;

		char cabecalho[4];

		VER_tpCondRet VERCondRetObtido   = VER_CondRetOK ;
		VER_tpCondRet VERCondRetEsperada = VER_CondRetFaltouMemoria ;
                                      /* inicializa para qualquer coisa */
		int chave = 0 ;
		int chaves[2];
		int chavesObtidas[2];

		char* rotulo = (char*) malloc(sizeof(char)*MAX_NUM);

		LIS_tppLista sucessores = NULL;
		LIS_tppLista antecessores = NULL;

		Aresta reflexiva = NULL;

		int origem, destino = -1 ;
		VER_TipoVer tipo = VER_Intermediario;
		VER_TipoVer tipoObtido = VER_Intermediario;

		Vertice verticeObtido = NULL;

		for(i = 0; i < 3; i++)
		{
			cabecalho[i] = ComandoTeste[i+1];
		}
		cabecalho[i] = '\0';

		/* Efetuar Iniciar contexto de grafo */
			if (strcmp(ComandoTeste, GRP_START_CMD) == 0) {
				for (i = 0; i < DIM_VT; i++)
				{
					vtAresta[i] = NULL;
					vtVertice[i] = NULL;
					StrBuffer[i] = NULL;
					vtGrafo[i] = NULL;
				} /* for */
				for (; i < MAX_NUM; i++) StrBuffer[i] = NULL;
				return TST_CondRetOK;
			}
			/* fim ativa: Efetuar iniciar contexto de grafo */

			/* Efetuar Reset de teste de grafo */
			else if (strcmp(ComandoTeste, GRP_RESET_CMD) == 0) {
				for (i = 0; i < DIM_VT; i++)
				{	//para evitar dangling pointers, as arestas e vertices serao destruidas apenas com a destruicao do grafo.
					//if (vtAresta[i]) VER_DestruirAresta(vtAresta[i]);
					//if (vtVertice[i]) VER_DestruirVertice(vtVertice[i]);
					if (vtGrafo[i]) GRP_DestruirGrafo(&vtGrafo[i]);
					if (StrBuffer[i]) free(StrBuffer[i]);
					vtAresta[i] = NULL;
					vtVertice[i] = NULL;
					vtGrafo[i] = NULL;
				} /* for */
				for (; i < MAX_NUM; i++) {
					if (StrBuffer[i]) free(StrBuffer[i]);
					StrBuffer[i] = NULL;
				}

				return TST_CondRetOK;
			}
			/* fim ativa: Efetuar Reset de teste de grafo */


		/*verifica se o comando e' de grafo*/
		else if (strcmp(cabecalho, "GRP") == 0) 
		{		
			/* testar criar grafo */
			if (strcmp(ComandoTeste, GRP_CRIAR_CMD) == 0)
			{
				NumLidos = LER_LerParametros("ii", &inxGrafo, &CondRetEsperada);

				if ((NumLidos != 2) || (!VerificarInx(inxGrafo)))
				{
					return TST_CondRetParm;
				} /* if */

				CondRetObtido = GRP_CriarGrafo(&(vtGrafo[inxGrafo]));
				return TST_CompararInt(CondRetEsperada, CondRetObtido,
					"Retorno errado ao criar grafo.");

			} /* fim testar criar grafo*/

			/* Testar Destruir grafo */
			else if (strcmp(ComandoTeste, GRP_DESTRUIR_CMD) == 0)
			{
				NumLidos = LER_LerParametros("i", &inxGrafo);
				if ((NumLidos != 1) || (!VerificarInx(inxGrafo)))
				{
					return TST_CondRetParm;
				} /* if */
				GRP_DestruirGrafo(&(vtGrafo[inxGrafo]));
				return TST_CondRetOK;
			}/* fim ativa: Testar Destruir grafo */
		
			/* Testar inserir vertice*/
			else if (strcmp(ComandoTeste, GRP_INSERIR_VERT_CMD) == 0)
			{
				NumLidos = LER_LerParametros("iii", &inxGrafo, &inxVertice, &CondRetEsperada);
				if ((NumLidos != 3) || (!VerificarInx(inxVertice) || !VerificarInx(inxGrafo))) {
					return TST_CondRetParm;
				}/* if */
				
				CondRetObtido = GRP_InserirVertice(vtGrafo[inxGrafo], vtVertice[inxVertice]);
				return TST_CompararInt(CondRetEsperada, CondRetObtido,
					"Retorno errado ao inserir vertice.");
				
			}/* Fim Testar inserir vertice  */

			 /* Testar inserir aresta */
			else if (strcmp(ComandoTeste, GRP_INSERIR_ARESTA_CMD) == 0)
			{ 
				NumLidos = LER_LerParametros("iii", &inxGrafo, &inxAresta, &CondRetEsperada);
				if ((NumLidos != 3) || (!VerificarInx(inxAresta) || !VerificarInx(inxGrafo))) {
					return TST_CondRetParm;
				}/* if */

				CondRetObtido = GRP_InserirAresta(vtGrafo[inxGrafo], vtAresta[inxAresta]);
				return TST_CompararInt(CondRetEsperada, CondRetObtido,
						"Retorno errado ao inserir aresta.");
			}/* Fim Testar inserir aresta  */

			/* Testar remover vertice */
			else if (strcmp(ComandoTeste, GRP_REMOVER_VERT_CMD) == 0)
			{
				NumLidos = LER_LerParametros("iii", &inxGrafo, &inxVertice, &CondRetEsperada);
				if ((NumLidos != 3) || (!VerificarInx(inxGrafo) || !VerificarInx(inxVertice))) {
					return TST_CondRetParm;
				}/* if */
				VER_getChave(vtVertice[inxVertice], &chave);
				CondRetObtido = GRP_RemoverVertice(vtGrafo[inxGrafo], chave);
				if (CondRetObtido == GRP_CondRetOK)
					vtVertice[inxVertice] = NULL;
				return TST_CompararInt(CondRetEsperada, CondRetObtido,
					"Retorno errado ao remover vertice.");
			}/*Fim Testar remover vertice */

			 /* Testar remover aresta */
			else if (strcmp(ComandoTeste, GRP_REMOVER_ARESTA_CMD) == 0)
			{
				NumLidos = LER_LerParametros("iii", &inxGrafo, &inxAresta, &CondRetEsperada);
				if ((NumLidos != 3) || (!VerificarInx(inxAresta) || !VerificarInx(inxGrafo))) {
					return TST_CondRetParm;
				}/* if */

				CondRetObtido = GRP_RemoverAresta(vtGrafo[inxGrafo], vtAresta[inxAresta]);
				if (CondRetObtido == GRP_CondRetOK)
					vtAresta[inxAresta] = NULL;
				return TST_CompararInt(CondRetEsperada, CondRetObtido,
					"Retorno errado ao remover aresta.");
			}/*Fim Testar remover aresta */

			/* teste vertice de chave */
			else if (strcmp(ComandoTeste, GRP_VERT_CHAVE_CMD) == 0)
			{
				NumLidos = LER_LerParametros("iiii", &inxGrafo, &chave, &inxVertice, &CondRetEsperada);
				if ((NumLidos != 4) || (!VerificarInx(inxGrafo) || !VerificarInx(inxVertice))) {
					return TST_CondRetParm;
				}/* if */

				CondRetObtido = VerticedeChave(vtGrafo[inxGrafo], chave, &verticeObtido);
				Ret =  TST_CompararInt(CondRetEsperada, CondRetObtido,
					"Retorno errado ao buscar vertice de chave.");

				if ( Ret != TST_CondRetOK || CondRetObtido != GRP_CondRetOK) return Ret;

				return TST_CompararInt( 1, (vtVertice[inxVertice] == verticeObtido ? 1 : 0),
                                     "Vertice errado no grafo para a chave dada." ) ;

			}/* fim teste vertice de chave */

			return TST_CondRetNaoConhec;
		} /******************fim das funcoes de grafo ***************/



		/*********** funcoes de vertice e aresta *****************/
		else if (strcmp(cabecalho, "VER") == 0)
		{
			/* Testar VER Criar vertice */
	         if ( strcmp( ComandoTeste , VER_CRIAR_VER_CMD ) == 0 ){

				 StrBuffer[pos] = (char*) malloc(sizeof(char)*MAX_NUM);

				 NumLidos = LER_LerParametros( "isii" , &inxVertice, StrBuffer[pos], &chave, &VERCondRetEsperada );

				 if ( (NumLidos != 4) || ( ! VerificarInx( inxVertice )) ){
					return TST_CondRetParm;
				 }/* if */

				VERCondRetObtido = VER_CriarVertice ( &(vtVertice[inxVertice]), StrBuffer[pos++], chave, free) ;

				return TST_CompararInt( VERCondRetEsperada , VERCondRetObtido ,
                                    "Retorno errado ao criar vertice." );
			 } /* fim ativa: Testar VER Criar Vertice */

			  /* Testar VER Criar aresta */
			 else if ( strcmp( ComandoTeste , VER_CRIAR_ARE_CMD ) == 0 ){

				NumLidos = LER_LerParametros( "iiisi" , &inxAresta, &origem, &destino, rotulo , &VERCondRetEsperada);

				if ( NumLidos != 5 || !VerificarInx(inxAresta)) return TST_CondRetParm;

				VERCondRetObtido = VER_CriarAresta(&(vtAresta[inxAresta]), origem, destino, rotulo);

				return TST_CompararInt( VERCondRetEsperada , VERCondRetObtido ,
                                    "Retorno errado ao criar aresta." );
			 } /* fim ativa: Testar VER Criar aresta */

			 /* Testar VER Destruir vertice */
			 else if ( strcmp( ComandoTeste , VER_DEST_VER_CMD ) == 0 ){

				NumLidos = LER_LerParametros( "i" , &inxVertice);

				if ( NumLidos != 1 || !VerificarInx(inxVertice)) return TST_CondRetParm;

				VER_DestruirVertice(vtVertice[inxVertice]);
				vtVertice[ inxVertice ] = NULL ;

				return TST_CondRetOK ;

			 } /* fim ativa: Testar VER Destruir vertice */

			 /* Testar VER Destruir aresta */
			else if ( strcmp( ComandoTeste , VER_DEST_ARE_CMD ) == 0 ){

				NumLidos = LER_LerParametros( "i" , &inxAresta);

				if ( NumLidos != 1 || !VerificarInx(inxAresta)) return TST_CondRetParm;

				VER_DestruirAresta(vtAresta[inxAresta]);
				vtAresta[ inxAresta ] = NULL ;

				return TST_CondRetOK ;

			} /* fim ativa: Testar VER Destruir aresta */

			/* Testar VER Inserir aresta */
			else if ( strcmp( ComandoTeste , VER_INS_ARE_CMD ) == 0 ){

				NumLidos = LER_LerParametros( "iii", &inxVertice, &inxAresta, &VERCondRetEsperada);

				if ( NumLidos != 3 || !VerificarInx(inxVertice) || !VerificarInx(inxAresta) ) return TST_CondRetParm;

				VERCondRetObtido = VER_InserirAresta(vtVertice[inxVertice], vtAresta[inxAresta]);

				return TST_CompararInt( VERCondRetEsperada , VERCondRetObtido ,
                                    "Retorno errado ao inserir aresta." );

			} /* fim ativa: Testar VER Inserir aresta */

			 /* Testar VER Remover aresta */
			else if ( strcmp( ComandoTeste , VER_REMOV_ARE_CMD ) == 0 ){

				NumLidos = LER_LerParametros( "iii", &inxVertice, &inxAresta, &VERCondRetEsperada);

				if ( NumLidos != 3 || !VerificarInx(inxVertice) || !VerificarInx(inxAresta) ) return TST_CondRetParm;

				VERCondRetObtido = VER_RemoverAresta(vtVertice[inxVertice], vtAresta[inxAresta]);

				vtAresta[inxAresta] = NULL;

				return TST_CompararInt( VERCondRetEsperada , VERCondRetObtido ,
                                    "Retorno errado ao remover aresta." );
			}/* fim ativa: Testar VER Remover aresta */

			/* Testar VER Modificar tipo do vertice */
			else if ( strcmp( ComandoTeste , VER_MODIF_CMD ) == 0 ){

				NumLidos = LER_LerParametros( "iii", &inxVertice, &tipo, &VERCondRetEsperada);

				if ( NumLidos != 3 || !VerificarInx(inxVertice)) return TST_CondRetParm;

				VERCondRetObtido = VER_ModificarTipo(vtVertice[inxVertice], tipo);

				return TST_CompararInt( VERCondRetEsperada , VERCondRetObtido ,
                                    "Retorno errado ao modificar tipo do vertice." );
			} /* fim ativa: Testar VER Modificar tipo do vertice */

			/* Testar VER Marcar visitado */
			else if ( strcmp( ComandoTeste , VER_MARCAR_CMD ) == 0 ){

				NumLidos = LER_LerParametros( "ii", &inxVertice, &VERCondRetEsperada);

				if ( NumLidos != 2 || !VerificarInx(inxVertice)) return TST_CondRetParm;

				VERCondRetObtido = VER_MarcarVisitado(vtVertice[inxVertice]);

				return TST_CompararInt( VERCondRetEsperada , VERCondRetObtido ,
                                   "Retorno errado ao marcar visitado." );
			} /* fim ativa: Testar VER Marcar visitado */

			/* Testar VER Ver visitado */
			else if ( strcmp( ComandoTeste , VER_VISITADO_CMD ) == 0 ){

				NumLidos = LER_LerParametros( "iii", &inxVertice, &ValorEsperado, &VERCondRetEsperada);

				if ( NumLidos != 3 || !VerificarInx(inxVertice)) return TST_CondRetParm;

				VERCondRetObtido = VER_Visitado(vtVertice[inxVertice], &ValorObtido);

				Ret = TST_CompararInt( VERCondRetEsperada , VERCondRetObtido ,
                                   "Retorno errado ao ver visitado." );

				if ( Ret != TST_CondRetOK || VERCondRetObtido == VER_CondRetVerticeNaoExiste) return Ret;

				return TST_CompararInt( ValorEsperado , ValorObtido ,
                                     "Visitacao do vertice esta errada." ) ;
			}/* fim ativa: Testar VER Ver visitado */

			
			/* Testar VER Get valor do vertice */
			else if ( strcmp( ComandoTeste , VER_GET_VALOR_CMD ) == 0 ){
			 
				StrBuffer[pos] = (char*) malloc(sizeof(char)*MAX_NUM);

				NumLidos = LER_LerParametros( "isi", &inxVertice, StrBuffer[pos], &VERCondRetEsperada);

				if ( NumLidos != 3 || !VerificarInx(inxVertice)) return TST_CondRetParm;

				VERCondRetObtido = VER_getValor(vtVertice[inxVertice], (void**) &StrBuffer[pos+1]);

				Ret = TST_CompararInt( VERCondRetEsperada , VERCondRetObtido ,
                                   "Retorno errado ao obter valor do vertice." );

				if ( Ret != TST_CondRetOK  || VERCondRetObtido == VER_CondRetVerticeNaoExiste) return Ret;

				pos += 2;
				return TST_CompararString( StrBuffer[pos-2] , StrBuffer[pos-1],
                                     "Valor do vertice esta errado" ) ;
			} /* fim ativa: Testar VER Get valor do vertice */

			/* Testar VER Get sucessores */
			else if ( strcmp( ComandoTeste , VER_GET_SUC_CMD ) == 0 ){

				NumLidos = LER_LerParametros( "iii", &inxVertice, &ValorEsperado, &VERCondRetEsperada);

				if ( NumLidos != 3 || !VerificarInx(inxVertice)) return TST_CondRetParm;

				VERCondRetObtido = VER_getSucessores(vtVertice[inxVertice], &sucessores);

				Ret = TST_CompararInt( VERCondRetEsperada , VERCondRetObtido ,
                                   "Retorno errado ao obter sucessores." );

				if ( Ret != TST_CondRetOK  || VERCondRetObtido == VER_CondRetVerticeNaoExiste) return Ret;

				return TST_CompararInt( ValorEsperado, (sucessores && LIS_ObterValor(sucessores) ? 1 : 0), "Existencia de sucessores nao bate com o esperado." );
			}/* fim ativa: Testar VER Get sucessores */

			/* Testar VER Get antecessores */
			else if ( strcmp( ComandoTeste , VER_GET_ANT_CMD ) == 0 ){

				NumLidos = LER_LerParametros( "iii", &inxVertice, &ValorEsperado, &VERCondRetEsperada);

				if ( NumLidos != 3 || !VerificarInx(inxVertice)) return TST_CondRetParm;

				VERCondRetObtido = VER_getAntecessores(vtVertice[inxVertice], &antecessores);

				Ret = TST_CompararInt( VERCondRetEsperada , VERCondRetObtido ,
                                   "Retorno errado ao obter antecessores." );

				if ( Ret != TST_CondRetOK || VERCondRetObtido == VER_CondRetVerticeNaoExiste ) return Ret;

				return TST_CompararInt( ValorEsperado, (antecessores && LIS_ObterValor(antecessores) ? 1 : 0), "Existencia de antecessores nao bate com o esperado." );
			}/* fim ativa: Testar VER Get antecessores */

			/* Testar VER Get reflexiva */
			else if ( strcmp( ComandoTeste , VER_GET_REF_CMD ) == 0 ){

				NumLidos = LER_LerParametros( "iii", &inxVertice, &inxAresta, &VERCondRetEsperada);

				if ( NumLidos != 3 || !VerificarInx(inxVertice) || !VerificarInx(inxAresta)) return TST_CondRetParm;

				VERCondRetObtido = VER_getReflexiva(vtVertice[inxVertice], &reflexiva);

				Ret = TST_CompararInt( VERCondRetEsperada , VERCondRetObtido ,
                                   "Retorno errado ao obter reflexiva." );

				if ( Ret != TST_CondRetOK || VERCondRetObtido == VER_CondRetVerticeNaoExiste ) return Ret;

				return TST_CompararInt( 1, (reflexiva == vtAresta[inxAresta] ? 1 : 0), "Aresta reflexiva esta errada." );
			}/* fim ativa: Testar VER Get reflexiva */

			/* Testar VER Get chave do vertice */
			else if ( strcmp( ComandoTeste , VER_GET_CHAVE_CMD) == 0 ){

				NumLidos = LER_LerParametros( "iii", &inxVertice, &ValorEsperado, &VERCondRetEsperada);

				if ( NumLidos != 3 || !VerificarInx(inxVertice)) return TST_CondRetParm;

				VERCondRetObtido = VER_getChave(vtVertice[inxVertice], &ValorObtido);

				Ret = TST_CompararInt( VERCondRetEsperada , VERCondRetObtido ,
                                   "Retorno errado ao obter chave do vertice." );

				if ( Ret != TST_CondRetOK || VERCondRetObtido == VER_CondRetVerticeNaoExiste) return Ret;

				return TST_CompararInt( ValorEsperado, ValorObtido, "Chave do vertice esta errada." );
			}/* fim ativa: Testar VER Get chave do vertice  */

			/* Testar VER Get tipo do vertice */
			else if ( strcmp( ComandoTeste , VER_GET_TIPO_CMD) == 0 ){

				NumLidos = LER_LerParametros( "iii" , &inxVertice, &tipo, &VERCondRetEsperada);

				if ( NumLidos != 3 || !VerificarInx(inxVertice)) return TST_CondRetParm;

				VERCondRetObtido = VER_getTipo(vtVertice[inxVertice], &tipoObtido);

				Ret = TST_CompararInt( VERCondRetEsperada , VERCondRetObtido ,
                                   "Retorno errado ao obter tipo do vertice." );

				if ( Ret != TST_CondRetOK || VERCondRetObtido == VER_CondRetVerticeNaoExiste) return Ret;

				return TST_CompararInt( tipo, tipoObtido, "Tipo do vertice esta errado." );
			} /* fim ativa: Testar VER GET tipo do vertice */

			/* Testar VER Get rotulo da aresta */
			else if ( strcmp( ComandoTeste , VER_GET_ROTULO_CMD) == 0 ){

				NumLidos = LER_LerParametros( "isi", &inxAresta, rotulo, &VERCondRetEsperada );
		   
				if ( NumLidos != 3 || !VerificarInx(inxAresta)) return TST_CondRetParm;

				VERCondRetObtido = VER_getRotulo(vtAresta[inxAresta], &StrBuffer[pos]);

				Ret = TST_CompararInt( VERCondRetEsperada , VERCondRetObtido ,
                                   "Retorno errado ao obter rotulo da aresta." );

				if ( Ret != TST_CondRetOK || VERCondRetObtido == VER_CondRetArestaNaoExiste) return Ret;

				return TST_CompararString(rotulo, StrBuffer[pos++], "Rotulo da aresta esta errado." );
			}/* fim ativa: Testar VER GET rotulo da aresta */

			/* Testar VER Get chaves da aresta */
			else if ( strcmp( ComandoTeste , VER_GET_CHAVES_CMD) == 0 ){

				NumLidos = LER_LerParametros( "iiii", &inxAresta, &chaves[0], &chaves[1], &VERCondRetEsperada );
		   
				if ( NumLidos != 4 || !VerificarInx(inxAresta)) return TST_CondRetParm;

				VERCondRetObtido = VER_GetChaves(vtAresta[inxAresta], &chavesObtidas);

				Ret = TST_CompararInt( VERCondRetEsperada , VERCondRetObtido ,
                                    "Retorno errado ao obter chaves da aresta." );

				if ( Ret != TST_CondRetOK || VERCondRetObtido == VER_CondRetArestaNaoExiste) return Ret;

				Ret = TST_CompararInt(chaves[0], chavesObtidas[0], "Primeira chave da aresta esta errada." );

				if ( Ret != TST_CondRetOK ) return Ret;

				return TST_CompararInt(chaves[1], chavesObtidas[1], "Segunda chave da aresta esta errada." );
			}/* fim ativa: Testar VER GET chaves da aresta */


		}/* fim de funcoes de vertice e aresta */
		
		free(rotulo);
		return TST_CondRetNaoConhec ;
	}

/***********************************************************************
*
*  $FC Funcao: TGRP -Verificar indice do vetor vertice, aresta e grafo
*
*  $FV Valor retornado
*     0 - inx nao vale
*     1 - inx vale
*
***********************************************************************/


int VerificarInx( int inx )
{
      if ( ( inx <   0 ) || ( inx >= DIM_VT))
      {
         return 0 ;
      } /* if */

      return 1 ;
}


/********** Fim do modulo de implementacao: TVER Teste vertice de strings **********/