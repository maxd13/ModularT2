/***************************************************************************
*
*  $MCD Modulo de implementacao: Modulo Reconhecedor Lexico
*
*  Arquivo gerado:              ReconhecedorLexico.C
*  Letras identificadoras:      Nao se aplica (nao e' um TAD).
*
*  Nome da base de software:    Terceiro Trabalho de Programacao Modular
*
*  Projeto: Disciplinas INF 1628 / 1301
*  Gestor:  DI/PUC-Rio
*  Autores: lcrv - Luiz Carlos R Viana
*
*  $HA Historico de evolucao:
*     Versao  Autor    Data     Observacoes
*	  2.0	  lcrv   2/11/2018  Termino do desenvolvimento
*       1.0   lcrv   19/10/2018 Inicio do desenvolvimento
*  Para maiores detalhes do historico ver controle de versao no GitHub, referenciado no LeiaMe do projeto.
*
*  $ED Descricao do modulo
*     Este modulo implementa um Reconhecedor lexico. 
*	O reconhecedor deve ser executado pela linha de comando,
*	sendo passados dois parametros. 
*
*	O primeiro parametro e' o caminho do arquivo texto contendo a 
*	representacao do automato esperada por esta aplicacao.
*	O segundo parametro deve ser o caminho do arquivo texto
*	que deve ser reconhecido pelo automato. O formato esperado para
*	o arquivo de descricao do automato, pode ser encontrado no arquivo de
*	exemplo modular_automato.txt.
*	
*	Um arquivo de log, Reconhecedor.log, e' gerado na mesma pasta do executavel
*	e contem informacoes sobre os caracteres lidos um a um, e tambem sobre falhas
*	de reconhecimento.
*
*
***************************************************************************/

#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdarg.h>
#include "grafo.h"

#define BUFFER_SIZE 20

/* VARIAVEIS GLOBAIS */

static LIS_tppLista pilha_releitura;
static LIS_tppLista pilha_retorno;

/* FUNCOES DE UTILIDADE */
void push(LIS_tppLista pilha, void* valor){
	IrFinalLista(pilha);
	LIS_InserirElementoApos(pilha, valor);
}

void* pop(LIS_tppLista pilha){
	void* valor;
	IrFinalLista(pilha);
	valor = LIS_ObterValor(pilha);
	LIS_ExcluirElemento(pilha);
	return valor;
}

void* peek(LIS_tppLista pilha){
	void* valor;
	IrFinalLista(pilha);
	valor = LIS_ObterValor(pilha);
	return valor;
}

//handler de excecoes.
void handle(char* message, ...){
	va_list argptr;
	va_start(argptr, message);
	vfprintf(stderr, message, argptr);
	va_end(argptr);
	exit(EXIT_FAILURE);
}

/* FUNCOES AUXILIARES */

/* retorna true se o caractere acionar a opcao especificada pela string de rotulo da aresta.
 os rotulos seguem o regex (\\[tnrldbo]|[a-z])(\|\|(\\[tnrldbo]|[a-z]))* */
char transicionar(char* rotulo, char buscado){
	if(!rotulo || !(*rotulo)) return 0;
	//verificacao de caracteres especiais.
	if(*rotulo == '\\')
	switch(*(rotulo+1)){
	case 'f':
		return buscado == '\f';
	case 't':
		return buscado == '\t' || transicionar(rotulo+2, buscado);
	case 'n':
		return buscado == '\n' || transicionar(rotulo+2, buscado);
	case 'r':
		return buscado == '\r' || transicionar(rotulo+2, buscado);
	case 'l':
		return isalpha(buscado) || transicionar(rotulo+2, buscado);
	case 'd':
		return isdigit(buscado) || transicionar(rotulo+2, buscado);
	case 'b':
		return isspace(buscado) || transicionar(rotulo+2, buscado);
	case 'o':
		return 1;
	default:
		return 0;

	}
	//verifica se o rotulo comeca com um "ou". Nesse caso simplesmente pula o "ou".
	if(strncmp("||", rotulo, 2) == 0) return transicionar(rotulo+2, buscado);

	//verificacao de um caracter literal.
	return *rotulo == buscado || transicionar(rotulo+1, buscado);
}

char especial(char testado){
	switch(testado){
		case 'f': return '\f';
		case 't': return '\t';
		case 'n': return '\n';
		case 'r': return '\r';
		default: return '\\';
	}

	//para o compilador nao chiar com warnings.
	return -1;
}

//retorna o proximo vertice/estado do automato para qual o reconhecedor deve se mover ao ler o caractere buscado, ou NULL caso nao haja transicao para este caracter.
Vertice proximo(Grafo g, LIS_tppLista sucessores, Aresta reflexiva, char buscado){
	LIS_tpCondRet cond = LIS_CondRetOK;
	Aresta corr;
	Vertice retornado = NULL;
	char* rotulo = NULL;
	int chaves[2];
	if(!sucessores && !reflexiva) return NULL;
	if(reflexiva){
		//comparar o rotulo com o caracter buscado e ver se achou.
		VER_getRotulo(reflexiva, &rotulo);
		if(transicionar(rotulo, buscado)){
			VER_GetChaves(reflexiva, &chaves);
			VerticedeChave(g, chaves[1], &retornado);
			//se o rotulo tiver o caracter que indica qualquer outro comando, so podemos retornar o vertice no final.
			if(strcmp(rotulo, "\\o") != 0) return retornado;
		}
		rotulo = NULL;
	}
	if(!sucessores) return retornado;
	IrInicioLista(sucessores);
	while(cond != LIS_CondRetFimLista){
		corr = (Aresta) LIS_ObterValor(sucessores);
		//se a lista estiver vazia retornaremos NULL para indicar que o caracter nao foi encontrado.
		if(!corr) return NULL;
		//comparar o rotulo com o caracter buscado e ver se achou.
		VER_getRotulo(corr, &rotulo);
		if(transicionar(rotulo, buscado)){
			VER_GetChaves(corr, &chaves);
			retornado = NULL;
			VerticedeChave(g, chaves[1], &retornado);
			//se o rotulo tiver o caracter que indica qualquer outro comando, so podemos retornar o vertice no final.
			if(strcmp(rotulo, "\\o") != 0) return retornado;
		}

		//pular para o proximo elemento da lista
		cond = LIS_AvancarElementoCorrente(sucessores, 1);
		if(cond == LIS_CondRetListaVazia) return NULL;

	}

	return retornado;
}

Vertice retroceder(){
	Vertice ret = (Vertice)pop(pilha_retorno);
	VER_TipoVer tipo = VER_Intermediario;
	VER_getTipo(ret, &tipo);
	while(tipo != VER_Final){
		if(tipo == VER_Inicial) break;
		pop(pilha_releitura);
		ret = (Vertice)pop(pilha_retorno);
		VER_getTipo(ret, &tipo);
	}

	push(pilha_retorno, ret);
	return ret;
}

void exibir(LIS_tppLista pilha, int index){
	char c;
	LIS_tpCondRet cond = LIS_CondRetOK;

	printf("match %d: ", index);
	IrInicioLista(pilha);
	while(cond != LIS_CondRetFimLista){
		c = (char) LIS_ObterValor(pilha);
		if(!c) handle("500: Erro interno da aplicação.\n");

		printf("%c", c);

		cond = LIS_AvancarElementoCorrente(pilha, 1);
		if(cond == LIS_CondRetListaVazia) handle("500: Erro interno da aplicação.\n");
	}

	printf("\n");
}

/* FUNCOES PRINCIPAIS */

void reconhecer(Grafo g, char* arquivo, FILE* logfile){
	FILE* in;
	char read;
	//contador nao-final: conta o numero de vertices nao finais desde o ultimo vertice final.
	int nfcounter = 0;
	//usado para pular letras depois de uma falha de reconhecimento, e em geral para marcar a posicao do file pointer no arquivo.
	long int loop = 1;
	//numero total de lexemas reconhecidos.
	int total = 0;
	//booleano de condicao de parada para o while.
	char quit = 0;
	Vertice corrente = NULL;
	VER_TipoVer tipo;
	LIS_tppLista sucessores = NULL;
	Aresta reflexiva = NULL;

	if(!g || !arquivo) handle("500: Erro interno da aplicação.\n");

	in = fopen(arquivo, "r");
	if(!in) handle("400: Erro na leitura do arquivo solicitado.\nO arquivo existe?\n");

	//vertice 0 eh sempre o inicial.
	if(VerticedeChave(g, 0, &corrente) != GRP_CondRetOK) handle("400: Estrutura do autômato está errada.\n");

	//praticamente uma assertiva isso daqui. Considerarei mudar para um assert de fato no futuro.
	VER_getTipo(corrente, &tipo);
	if(tipo != VER_Inicial) handle("500: Estrutura do autômato está errada.\n");

	printf("Iniciando o reconhecimento do arquivo %s...\n", arquivo);

	while(!quit){
		read = fgetc(in);
		if(read == '\n') continue;
		
		push(pilha_retorno, corrente);
		VER_getTipo(corrente, &tipo);
		if(tipo == VER_Final) nfcounter = 0;
		else nfcounter++;

		
		if(read == EOF){
			quit = 1;
			read = '\f';
		}

		else if(read == '\\'){
			read = fgetc(in);
			if(read != EOF) read = especial(read);
			else {
				read = '\\';
				fseek(in, -1, SEEK_END);
			}
		}

		VER_getSucessores(corrente, &sucessores);
		VER_getReflexiva(corrente, &reflexiva);
		corrente = proximo(g, sucessores, reflexiva, tolower(read));
		

		if(!corrente){
			corrente = (Vertice) peek(pilha_retorno);
			VER_getTipo(corrente, &tipo);
			if(tipo != VER_Final) corrente = retroceder();
			VER_getTipo(corrente, &tipo);
			if(tipo != VER_Final){
				fprintf(logfile, "Falha no reconhecimento lendo caracter: %c\n", read);
				//pular os n primeiros caracteres e tentar novamente.
				if(loop <= ftell(in)){
					fseek(in, loop++, SEEK_SET);
					quit = 0;
				}
			}
			else {
				exibir(pilha_releitura, ++total);
				fprintf(logfile, "Sucesso no reconhecimento! Ultimo caracter lido: %c\n", read);
				if(nfcounter){
					fseek(in, -nfcounter, SEEK_CUR);
					quit = 0;
				}
				loop = ftell(in);
			}
			
			LIS_EsvaziarLista(pilha_releitura);
			LIS_EsvaziarLista(pilha_retorno);
			VerticedeChave(g, 0, &corrente);
			nfcounter = 0;
		}
		else {
			push(pilha_releitura, (void*)read);
			if(quit){
				VER_getTipo(corrente, &tipo);
				if(tipo != VER_Final) corrente = retroceder();
				VER_getTipo(corrente, &tipo);
				if(tipo != VER_Final){
					fprintf(logfile, "Falha no reconhecimento lendo caracter: %c\n", read);
					//pular os n primeiros caracteres e tentar novamente.
					if(loop <= ftell(in)){
						fseek(in, loop++, SEEK_SET);
						quit = 0;
					}	
				}
				else {
					exibir(pilha_releitura, ++total);
					fprintf(logfile, "Sucesso no reconhecimento! Ultimo caracter lido: %c\n", read);
					if(nfcounter){
						fseek(in, -nfcounter, SEEK_CUR);
						quit = 0;
					}
					loop = ftell(in);
				}
			
				LIS_EsvaziarLista(pilha_releitura);
				LIS_EsvaziarLista(pilha_retorno);
				VerticedeChave(g, 0, &corrente);
				nfcounter = 0;
			}
		}

		if(loop == EOF) handle("400: Erro na leitura do arquivo solicitado.\n");
	}
	
	if(ferror(in)) handle("400: Erro na leitura do arquivo solicitado.\n");

	printf("Numero de lexemas reconhecidos: %d\n", total);
	printf("finalizando o reconhecimento...\n");
	if(fclose(in)) handle("500: Não foi possível fechar o arquivo aberto para reconhecimento.\n");
	printf("Reconhecimento finalizado com sucesso!\n");
}

Grafo lerAutomato(char* arquivo){
	Grafo g = NULL;
	//chaves.
	int origem;
	int destino;
	//linha lida.
	char line[BUFFER_SIZE];
	//token atual da linha.
	char* token;
	//contador de tokens.
	char i;
	//condicoes de retorno.
	GRP_tpCondRet cond;
	VER_tpCondRet vcond;
	//vertices e arestas auxiliares.
	Vertice corrente = NULL;
	Vertice vizinho = NULL;
	Aresta aresta = NULL;
	FILE* in;

	if(!arquivo) handle("400: Erro: nenhum arquivo de especificação de autômato foi dado!\n");

	in = fopen(arquivo, "r");
	if(!in) handle("400: Erro na leitura do arquivo solicitado.\nO arquivo existe?\n");

	cond = GRP_CriarGrafo(&g);
	if(cond == GRP_CondRetFaltouMemoria) handle("500: Erro interno da aplicação: falta de memória para alocar dados.\n");

	printf("Iniciando a leitura do autômato no arquivo %s...\n", arquivo);

	while(fgets(line, BUFFER_SIZE, in)){
		//pular comentarios
		if(*line == '#') {
			//pular o resto da linha
			if(line[strlen(line) - 1] != '\n') while(fgetc(in) != '\n');
			continue;
		}
		//pular linhas que comecam com espacos
		//isso, como bonus, pula linhas em branco, alem de qualquer linha que teria
		//causado um erro de leitura por comecar com leading whitespace.
		if(isspace(*line)){
			//pular o resto da linha
			if(line[strlen(line) - 1] != '\n') while(fgetc(in) != '\n');
			continue;
		}

		//remover o \n do final
		line[strcspn(line, "\n\0")] = '\0';
		
		//tratamento do primeiro token.
		token = strtok(line, ",");
		origem = atoi(isdigit(*token) ? token : token + 1);
		if(VerticedeChave(g, origem, &corrente) != GRP_CondRetOK){
			corrente = NULL;
			vcond = VER_CriarVertice(&corrente, NULL, origem, NULL);
			if(vcond == VER_CondRetFaltouMemoria) handle("500: Erro interno da aplicação: falta de memória para alocar dados.\n");
			cond = GRP_InserirVertice(g, corrente);
			if(cond == GRP_CondRetFaltouMemoria) handle("500: Erro interno da aplicação: falta de memória para alocar dados.\n");
		}

		//modificacao de tipo de acordo com o primeiro caractere da linha.
		if(!isdigit(*token)) VER_ModificarTipo(corrente, VER_Final);
		else if(*token == '0') VER_ModificarTipo(corrente, VER_Inicial);

		//tratamento dos tokens subsequentes
		i = 1;
		while(token = strtok(NULL, ",")){
			if(i%2 == 0){
				aresta = NULL;
				vcond = VER_CriarAresta(&aresta, origem, destino, token);
				if(vcond == VER_CondRetFaltouMemoria) handle("500: Erro interno da aplicação: falta de memória para alocar dados.\n");
				cond = GRP_InserirAresta(g, aresta);
				if(cond == GRP_CondRetFaltouMemoria) handle("500: Erro interno da aplicação: falta de memória para alocar dados.\n");
				else if(cond != GRP_CondRetOK) handle("500: Erro interno da aplicação.\n");
			}
			else{
				destino = atoi(token);
				if(VerticedeChave(g, destino, &vizinho) != GRP_CondRetOK){
					vizinho = NULL;
					vcond = VER_CriarVertice(&vizinho, NULL, destino, NULL);
					if(vcond == VER_CondRetFaltouMemoria) handle("500: Erro interno da aplicação: falta de memória para alocar dados.\n");
					cond = GRP_InserirVertice(g, vizinho);
					if(cond == GRP_CondRetFaltouMemoria) handle("500: Erro interno da aplicação: falta de memória para alocar dados.\n");
				}
			}
			i++;
		}
	}
	
	if(ferror(in)) handle("400: Erro na leitura do arquivo solicitado.\n");
	printf("finalizando a leitura...\n");
	if(fclose(in)) handle("500: Não foi possível fechar o arquivo aberto para leitura do autômato.\n");
	printf("Autômato lido com sucesso!\n");
	return g;
}


int main(int argc, char **argv){
	Grafo g;
	FILE* log;
	if(argc != 3) handle("usage: %s automato.txt leitura.txt\n", argv[0]);
	
	printf("Iniciando Reconhecedor Léxico de Modular.\n");
	pilha_releitura = LIS_CriarLista(NULL);
	pilha_retorno = LIS_CriarLista(NULL);
	if(!pilha_retorno || ! pilha_releitura) handle("500: Erro interno da aplicação: falta de memória para alocar dados.\n");
	g = lerAutomato(argv[1]);

	log = fopen("Reconhecedor.log", "w");
	if(!log) handle("500: Erro na abertura do arquivo de log.\n");
	reconhecer(g, argv[2], log);
	if(fclose(log)) handle("500: Não foi possível fechar o arquivo de log da aplicacao.\n");

	printf("Fim da execução do reconhecedor.\n");
	return 0;
}

//EoF.