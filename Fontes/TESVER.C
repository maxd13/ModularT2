/***************************************************************************
*  $MCI Modulo de implementacao: Modulo de teste especifico
*
*  Arquivo gerado:              TESVER.C
*  Letras identificadoras:      TVER
*
*  Nome da base de software:    Segundo Trabalho de Programacao Modular
*
*  Projeto: Disciplinas INF 1628 / 1301
*  Gestor:  DI/PUC-Rio
*  Autores: bpf - Breno Perricone Fischer
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
*     Comandos de teste especificos para testar o modulo vertice:
*
*     "=iniciar"     - inicia o contexto de teste.
*     "=resetar"     - reinicia o contexto de teste, destruindo primeiro.
*     "=criarver"    - chama a funcao VER_CriarVertice( )
*     "=criarare"    - chama a funcao VER_CriarAresta( )
*     "=destver"     - chama a funcao VER_DestruirVertice( )
*     "=destare"     - chama a funcao VER_DestruirAresta( )
*	"=removare"    - chama a funcao VER_RemoverAresta ( )
*     "=insare"      - chama a funcao VER_InserirAresta( )               
*     "=modif"       - chama a funcao VER_ModificarTipo( )
*     "=marcar"      - chama a funcao VER_MarcVERisitado( )
*     "=visitado"    - chama a funcao VER_Visitado( )
*     "=getvalor"    - chama a funcao VER_getValor( )
*	"=getsucessor" - chama a funcao VER_getSucessores( )
*	"=getante"	   - chama a funcao VER_getAntecessores ( )
*	"=getrefle"    - chama a funcao VER_getReflexiva ( )
*     "=getchave"    - chama a funcao VER_getChave( )
*     "=gettipo"     - chama a funcao VER_getTipo( )
*     "=getrotulo"   - chama a funcao VER_getRotulo( )
*     "=getchaves"   - chama a funcao VER_GetChaves( )
*
***************************************************************************/

#include <string.h>
#include <stdio.h>
#include <malloc.h>
#include "TST_Espc.h"
#include "generico.h"
#include "lerparm.h"
#include "vertice.h"



/* Tabela dos nomes dos comandos de teste especificos */
#define START_CMD		    "=iniciar"
#define RESET_CMD		    "=resetar"
#define CRIAR_VER_CMD	    "=criarver"
#define CRIAR_ARE_CMD       "=criarare"
#define DEST_VER_CMD	    "=destver"
#define DEST_ARE_CMD        "=destare"
#define REMOV_ARE_CMD	    "=removare"
#define INS_ARE_CMD	    "=insare"
#define MODIF_CMD	 	    "=modif"
#define MARCAR_CMD          "=marcar"
#define VISITADO_CMD        "=visitado"
#define GET_VALOR_CMD       "=getvalor"
#define GET_SUC_CMD	    "=getsucessor"
#define GET_ANT_CMD	    "=getante"
#define GET_REF_CMD	    "=getrefle"
#define GET_CHAVE_CMD       "=getchave"
#define GET_TIPO_CMD        "=gettipo"
#define GET_CHAVES_CMD      "=getchaves"
#define GET_ROTULO_CMD      "=getrotulo"



#define MAX_NUM 100
#define DIM_VT 10
#define MAX_LABEL_SIZE 20

Vertice vtVertice[ DIM_VT ] ;
Aresta vtAresta[ DIM_VT ] ;
char* StrBuffer[MAX_NUM];
int pos = 0;

/***** Prototipos das funcoes encapuladas no modulo *****/

	static int VerificarInx( int inxVertice ) ;

/*****  Codigo das funcoes exportadas pelo modulo  *****/


/***********************************************************************
*
*  $FC Funcao: TVER Efetuar operacoes de teste especificas para vertice
*
*  $ED Descricao da funcao
*     Efetua os diversos comandos de teste especificos para o modulo
*     vertice sendo testado.
*     Podem ser criados ate 10 vertices, identificados pelos indices 0 a 10
*
*  $EP Parametros
*     $P ComandoTeste - String contendo o comando
*
*  $FV Valor retornado
*     Ver TST_tpCondRet definido em TST_ESPC.H
*
***********************************************************************/

   TST_tpCondRet TST_EfetuarComando( char * ComandoTeste )
   {

      VER_tpCondRet CondRetObtido   = VER_CondRetOK ;
      VER_tpCondRet CondRetEsperada = VER_CondRetFaltouMemoria ;
                                      /* inicializa para qualquer coisa */
	  int chave = 0 ;
	  int chaves[2];
	  int chavesObtidas[2];

	  int inxVertice = -1 ;
	  int inxAresta = -1 ;

	  char* rotulo = (char*) malloc(sizeof(char)*MAX_NUM);

	  LIS_tppLista sucessores = NULL;
	  LIS_tppLista antecessores = NULL;

	  Aresta reflexiva = NULL;
	  
	  int ValorObtido = -1 ;
	  int ValorEsperado = -1 ;

	  TST_tpCondRet Ret ;

	  int origem, destino = -1 ;
	  VER_TipoVer tipo = VER_Intermediario;
	  VER_TipoVer tipoObtido = VER_Intermediario;

        int  NumLidos = -1 ;
	  int i;
     

	 
	/* Efetuar Iniciar contexto de vertices */

	  if ( strcmp( ComandoTeste , START_CMD) == 0){
		  for( i = 0 ; i < DIM_VT ; i++)
		  {
			  vtAresta[i] = NULL;
			  vtVertice[i] = NULL;
			  StrBuffer[i] = NULL;
		  } /* for */
		  for(; i < MAX_NUM; i++) StrBuffer[i] = NULL;
		  return TST_CondRetOK;
	  } 
	/* fim ativa: Efetuar iniciar contexto de vertices */

	
	/* Efetuar Reset de teste de vertice */

		if ( strcmp( ComandoTeste , RESET_CMD ) == 0 ){
			for( i = 0 ; i < DIM_VT ; i++ )
            {
				if(vtAresta[i]) VER_DestruirAresta(vtAresta[i]);
				if(vtVertice[i]) VER_DestruirVertice(vtVertice[i]);
				if(StrBuffer[i]) free(StrBuffer[i]);
				vtAresta[i] = NULL;
				vtVertice[i] = NULL;
            } /* for */
			for(; i < MAX_NUM; i++){
				if(StrBuffer[i]) free(StrBuffer[i]);
				StrBuffer[i] = NULL;
			}

            return TST_CondRetOK ;
		}
	/* fim ativa: Efetuar Reset de teste de vertice */


    /* Testar VER Criar vertice */

         if ( strcmp( ComandoTeste , CRIAR_VER_CMD ) == 0 ){

			 StrBuffer[pos] = (char*) malloc(sizeof(char)*MAX_NUM);

			 NumLidos = LER_LerParametros( "isii" , &inxVertice, StrBuffer[pos], &chave, &CondRetEsperada );

			 if ( (NumLidos != 4) || ( ! VerificarInx( inxVertice )) ){
				return TST_CondRetParm;
			}/* if */

			 CondRetObtido = VER_CriarVertice ( &vtVertice[inxVertice], StrBuffer[pos++], chave, free) ;

			 return TST_CompararInt( CondRetEsperada , CondRetObtido ,
                                    "Retorno errado ao criar vertice." );

         } /* fim ativa: Testar VER Criar Vertice */

      /* Testar VER Criar aresta */

         else if ( strcmp( ComandoTeste , CRIAR_ARE_CMD ) == 0 ){

			 NumLidos = LER_LerParametros( "iiisi" , &inxAresta, &origem, &destino, rotulo , &CondRetEsperada);

			 if ( NumLidos != 5 || !VerificarInx(inxAresta)) return TST_CondRetParm;

			 CondRetObtido = VER_CriarAresta(&(vtAresta[inxAresta]), origem, destino, rotulo);

			 return TST_CompararInt( CondRetEsperada , CondRetObtido ,
                                    "Retorno errado ao criar aresta." );

         } /* fim ativa: Testar VER Criar aresta */

      /* Testar VER Destruir vertice */

         else if ( strcmp( ComandoTeste , DEST_VER_CMD ) == 0 ){

            NumLidos = LER_LerParametros( "i" , &inxVertice);

            if ( NumLidos != 1 || !VerificarInx(inxVertice)) return TST_CondRetParm;

            VER_DestruirVertice(vtVertice[inxVertice]);
		vtVertice[ inxVertice ] = NULL ;

            return TST_CondRetOK ;

         } /* fim ativa: Testar VER Destruir vertice */

      /* Testar VER Destruir aresta */

         else if ( strcmp( ComandoTeste , DEST_ARE_CMD ) == 0 ){

            NumLidos = LER_LerParametros( "i" , &inxAresta);

			if ( NumLidos != 1 || !VerificarInx(inxAresta)) return TST_CondRetParm;

            VER_DestruirAresta(vtAresta[inxAresta]);
		vtAresta[ inxAresta ] = NULL ;

            return TST_CondRetOK ;

         } /* fim ativa: Testar VER Destruir aresta */

      /* Testar VER Inserir aresta */

         else if ( strcmp( ComandoTeste , INS_ARE_CMD ) == 0 ){

            NumLidos = LER_LerParametros( "iii", &inxVertice, &inxAresta, &CondRetEsperada);

            if ( NumLidos != 3 || !VerificarInx(inxVertice) || !VerificarInx(inxAresta) ) return TST_CondRetParm;

            CondRetObtido = VER_InserirAresta(vtVertice[inxVertice], vtAresta[inxAresta]);

            return TST_CompararInt( CondRetEsperada , CondRetObtido ,
                                    "Retorno errado ao inserir aresta." );

         } /* fim ativa: Testar VER Inserir aresta */

	  /* Testar VER Remover aresta */
		 else if ( strcmp( ComandoTeste , REMOV_ARE_CMD ) == 0 ){

			 NumLidos = LER_LerParametros( "iii", &inxVertice, &inxAresta, &CondRetEsperada);

			 if ( NumLidos != 3 || !VerificarInx(inxVertice) || !VerificarInx(inxAresta) ) return TST_CondRetParm;

			 CondRetObtido = VER_RemoverAresta(vtVertice[inxVertice], vtAresta[inxAresta]);

			 vtAresta[inxAresta] = NULL;

			 return TST_CompararInt( CondRetEsperada , CondRetObtido ,
                                    "Retorno errado ao remover aresta." );

		 }
	  /* fim ativa: Testar VER Remover aresta */

      /* Testar VER Modificar tipo do vertice */

         else if ( strcmp( ComandoTeste , MODIF_CMD ) == 0 ){

			 NumLidos = LER_LerParametros( "iii", &inxVertice, &tipo, &CondRetEsperada);

			 if ( NumLidos != 3 || !VerificarInx(inxVertice)) return TST_CondRetParm;

			 CondRetObtido = VER_ModificarTipo(vtVertice[inxVertice], tipo);

			 return TST_CompararInt( CondRetEsperada , CondRetObtido ,
                                    "Retorno errado ao modificar tipo do vertice." );

         } /* fim ativa: Testar VER Modificar tipo do vertice */

      /* Testar VER Marcar visitado */

         else if ( strcmp( ComandoTeste , MARCAR_CMD ) == 0 ){

			 NumLidos = LER_LerParametros( "ii", &inxVertice, &CondRetEsperada);

			 if ( NumLidos != 2 || !VerificarInx(inxVertice)) return TST_CondRetParm;

			 CondRetObtido = VER_MarcarVisitado(vtVertice[inxVertice]);

			 return TST_CompararInt( CondRetEsperada , CondRetObtido ,
                                   "Retorno errado ao marcar visitado." );

         } /* fim ativa: Testar VER Marcar visitado */

		 /* Testar VER Ver visitado */

		 else if ( strcmp( ComandoTeste , VISITADO_CMD ) == 0 ){

			 NumLidos = LER_LerParametros( "iii", &inxVertice, &ValorEsperado, &CondRetEsperada);

			 if ( NumLidos != 3 || !VerificarInx(inxVertice)) return TST_CondRetParm;

			 CondRetObtido = VER_Visitado(vtVertice[inxVertice], &ValorObtido);

			 Ret = TST_CompararInt( CondRetEsperada , CondRetObtido ,
                                   "Retorno errado ao ver visitado." );

			 if ( Ret != TST_CondRetOK || CondRetObtido == VER_CondRetVerticeNaoExiste) return Ret;

			 return TST_CompararInt( ValorEsperado , ValorObtido ,
                                     "Visitacao do vertice esta errada." ) ;

         }
		 /* fim ativa: Testar VER Ver visitado */

      /* Testar VER Get valor do vertice */

         else if ( strcmp( ComandoTeste , GET_VALOR_CMD ) == 0 ){
			 
			 StrBuffer[pos] = (char*) malloc(sizeof(char)*MAX_NUM);

			 NumLidos = LER_LerParametros( "isi", &inxVertice, StrBuffer[pos], &CondRetEsperada);

			 if ( NumLidos != 3 || !VerificarInx(inxVertice)) return TST_CondRetParm;

			 CondRetObtido = VER_getValor(vtVertice[inxVertice], (void**) &StrBuffer[pos+1]);

			 Ret = TST_CompararInt( CondRetEsperada , CondRetObtido ,
                                   "Retorno errado ao obter valor do vertice." );

			 if ( Ret != TST_CondRetOK  || CondRetObtido == VER_CondRetVerticeNaoExiste) return Ret;

			 pos += 2;
			 return TST_CompararString( StrBuffer[pos-2] , StrBuffer[pos-1],
                                     "Valor do vertice esta errado" ) ;

         } /* fim ativa: Testar VER Get valor do vertice */

		 /* Testar VER Get sucessores */

		 else if ( strcmp( ComandoTeste , GET_SUC_CMD ) == 0 ){

			 NumLidos = LER_LerParametros( "iii", &inxVertice, &ValorEsperado, &CondRetEsperada);

			 if ( NumLidos != 3 || !VerificarInx(inxVertice)) return TST_CondRetParm;

			 CondRetObtido = VER_getSucessores(vtVertice[inxVertice], &sucessores);

			 Ret = TST_CompararInt( CondRetEsperada , CondRetObtido ,
                                   "Retorno errado ao obter sucessores." );

			 if ( Ret != TST_CondRetOK  || CondRetObtido == VER_CondRetVerticeNaoExiste) return Ret;

			 return TST_CompararInt( ValorEsperado, (sucessores && LIS_ObterValor(sucessores) ? 1 : 0), "Existencia de sucessores nao bate com o esperado." );

		 }
		 /* fim ativa: Testar VER Get sucessores */

		 /* Testar VER Get antecessores */

		 else if ( strcmp( ComandoTeste , GET_ANT_CMD ) == 0 ){

			 NumLidos = LER_LerParametros( "iii", &inxVertice, &ValorEsperado, &CondRetEsperada);

			 if ( NumLidos != 3 || !VerificarInx(inxVertice)) return TST_CondRetParm;

			 CondRetObtido = VER_getAntecessores(vtVertice[inxVertice], &antecessores);

			 Ret = TST_CompararInt( CondRetEsperada , CondRetObtido ,
                                   "Retorno errado ao obter antecessores." );

			 if ( Ret != TST_CondRetOK || CondRetObtido == VER_CondRetVerticeNaoExiste ) return Ret;

			 return TST_CompararInt( ValorEsperado, (antecessores && LIS_ObterValor(antecessores) ? 1 : 0), "Existencia de antecessores nao bate com o esperado." );

		 }
		 /* fim ativa: Testar VER Get antecessores */

		 /* Testar VER Get reflexiva */

		 else if ( strcmp( ComandoTeste , GET_REF_CMD ) == 0 ){

			 NumLidos = LER_LerParametros( "iii", &inxVertice, &inxAresta, &CondRetEsperada);

			 if ( NumLidos != 3 || !VerificarInx(inxVertice) || !VerificarInx(inxAresta)) return TST_CondRetParm;

			 CondRetObtido = VER_getReflexiva(vtVertice[inxVertice], &reflexiva);

			 Ret = TST_CompararInt( CondRetEsperada , CondRetObtido ,
                                   "Retorno errado ao obter reflexiva." );

			 if ( Ret != TST_CondRetOK || CondRetObtido == VER_CondRetVerticeNaoExiste ) return Ret;

			 return TST_CompararInt( 1, (reflexiva == vtAresta[inxAresta] ? 1 : 0), "Aresta reflexiva esta errada." );

		 }
		 /* fim ativa: Testar VER Get reflexiva */

	   /* Testar VER Get chave do vertice */
	   else if ( strcmp( ComandoTeste , GET_CHAVE_CMD) == 0 ){

		   NumLidos = LER_LerParametros( "iii", &inxVertice, &ValorEsperado, &CondRetEsperada);

		   if ( NumLidos != 3 || !VerificarInx(inxVertice)) return TST_CondRetParm;

		   CondRetObtido = VER_getChave(vtVertice[inxVertice], &ValorObtido);

		   Ret = TST_CompararInt( CondRetEsperada , CondRetObtido ,
                                   "Retorno errado ao obter chave do vertice." );

		   if ( Ret != TST_CondRetOK || CondRetObtido == VER_CondRetVerticeNaoExiste) return Ret;

		   return TST_CompararInt( ValorEsperado, ValorObtido, "Chave do vertice esta errada." );


         }
	   /* fim ativa: Testar VER Get chave do vertice  */

	   /* Testar VER Get tipo do vertice */

	   else if ( strcmp( ComandoTeste , GET_TIPO_CMD) == 0 ){

		   NumLidos = LER_LerParametros( "iii" , &inxVertice, &tipo, &CondRetEsperada);

		   if ( NumLidos != 3 || !VerificarInx(inxVertice)) return TST_CondRetParm;

		   CondRetObtido = VER_getTipo(vtVertice[inxVertice], &tipoObtido);

		   Ret = TST_CompararInt( CondRetEsperada , CondRetObtido ,
                                   "Retorno errado ao obter tipo do vertice." );

		   if ( Ret != TST_CondRetOK || CondRetObtido == VER_CondRetVerticeNaoExiste) return Ret;

		   return TST_CompararInt( tipo, tipoObtido, "Tipo do vertice esta errado." );

         } /* fim ativa: Testar VER GET tipo do vertice */

	   /* Testar VER Get rotulo da aresta */

	   else if ( strcmp( ComandoTeste , GET_ROTULO_CMD) == 0 ){

		   NumLidos = LER_LerParametros( "isi", &inxAresta, rotulo, &CondRetEsperada );
		   
		   if ( NumLidos != 3 || !VerificarInx(inxAresta)) return TST_CondRetParm;

		   CondRetObtido = VER_getRotulo(vtAresta[inxAresta], &StrBuffer[pos]);

		   Ret = TST_CompararInt( CondRetEsperada , CondRetObtido ,
                                   "Retorno errado ao obter rotulo da aresta." );

		   if ( Ret != TST_CondRetOK || CondRetObtido == VER_CondRetArestaNaoExiste) return Ret;

		   return TST_CompararString(rotulo, StrBuffer[pos++], "Rotulo da aresta esta errado." );
	   }
	   /* fim ativa: Testar VER GET rotulo da aresta */

	   /* Testar VER Get chaves da aresta */

	   else if ( strcmp( ComandoTeste , GET_CHAVES_CMD) == 0 ){

		   NumLidos = LER_LerParametros( "iiii", &inxAresta, &chaves[0], &chaves[1], &CondRetEsperada );
		   
		   if ( NumLidos != 4 || !VerificarInx(inxAresta)) return TST_CondRetParm;

		   CondRetObtido = VER_GetChaves(vtAresta[inxAresta], &chavesObtidas);

		   Ret = TST_CompararInt( CondRetEsperada , CondRetObtido ,
                                    "Retorno errado ao obter chaves da aresta." );

		   if ( Ret != TST_CondRetOK || CondRetObtido == VER_CondRetArestaNaoExiste) return Ret;

		   Ret = TST_CompararInt(chaves[0], chavesObtidas[0], "Primeira chave da aresta esta errada." );

		   if ( Ret != TST_CondRetOK ) return Ret;

		   return TST_CompararInt(chaves[1], chavesObtidas[1], "Segunda chave da aresta esta errada." );

	   }
	   /* fim ativa: Testar VER GET chaves da aresta */
	free(rotulo);
      return TST_CondRetNaoConhec ;

   } /* Fim funcao: TVER Efetuar operacoes de teste especificas para vertices */


/***********************************************************************
*
*  $FC Funcao: TVER -Verificar indice do vetor vertice e aresta
*
*  $FV Valor retornado
*     0 - inxVertice nao vale
*     1 - inxVertice vale
*
***********************************************************************/


   int VerificarInx( int inxVertice )
{

      if ( ( inxVertice <   0 )
        || ( inxVertice >= DIM_VT))
      {
         return 0 ;
      } /* if */

      return 1 ;

}


/********** Fim do modulo de implementacao: TVER Teste vertice de strings **********/