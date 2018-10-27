#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include "grafo.h"

#define BUFFER_SIZE 20

static LIS_tppLista pilha_releitura;
static LIS_tppLista pilha_retorno;

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
	return *rotulo == buscado || transicionar(rotulo+2, buscado);
}

char especial(char testado){
	switch(testado){
		case 'f': return '\f';
		case 't': return '\t';
		case 'n': return '\n';
		case 'r': return '\nr';
		default: return '\\';
	}

	//para o compilador nao chiar com warnings.
	return -1;
}

Vertice proximo(Grafo g, LIS_tppLista sucessores, char buscado){
	LIS_tpCondRet cond = LIS_CondRetOK;
	Aresta corr;
	Vertice retornado = NULL;
	char* rotulo = NULL;
	int chaves[2];

	IrInicioLista(sucessores);
	while(cond != LIS_CondRetFimLista){
		corr = (Aresta) LIS_ObterValor(sucessores);
		//se a lista estiver vazia retornaremos NULL para indicar que o caracter nao foi encontrado.
		if(!corr) return NULL;
		//comparar o rotulo com o caracter buscado e ver se achou.
		VER_getRotulo(corr, &rotulo);
		if(transicionar(rotulo, buscado)){
			VER_GetChaves(corr, &chaves);
			VerticedeChave(g, chaves[1], &retornado);
			//se o rotulo tiver o caracter que indica qualquer outro comando, so podemos retornar o vertice no final.
			if(strcmp(rotulo, "\o") != 0) return retornado;
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
		if(!c){
			fprintf(stderr, "500: Erro interno da aplicação.\n");
			exit(1);
		}

		printf("%c", c);

		cond = LIS_AvancarElementoCorrente(pilha, 1);
		if(cond == LIS_CondRetListaVazia){
			fprintf(stderr, "500: Erro interno da aplicação.\n");
			exit(1);
		}
	}

	printf("\n");
}

void reconhecer(Grafo g, char* arquivo){
	FILE* in;
	char read;
	//contador nao-final: conta o numero de vertices nao finais desde o ultimo vertice final.
	int nfcounter = 0;
	//usado para pular letras depois de uma falha de reconhecimento, e em geral para marcar a posicao do file pointer no arquivo.
	long int loop = 0;
	//numero total de lexemas reconhecidos.
	int total = 0;
	//booleano de condicao de parada para o while.
	char quit = 0;
	Vertice corrente = NULL;
	VER_TipoVer tipo;
	LIS_tppLista sucessores = NULL;

	if(!g || !arquivo){
		fprintf(stderr, "500: Erro interno da aplicação.\n");
		exit(1);
	}
	in = fopen(arquivo, "r");
	if(!in){
		fprintf(stderr, "400: Erro na leitura do arquivo solicitado.\nO arquivo existe?\n");
		exit(1);
	}

	//vertice 0 eh sempre o inicial.
	if(VerticedeChave(g, 0, &corrente) != GRP_CondRetOK){
		fprintf(stderr, "400: Estrutura do autômato está errada.\n");
		exit(1);
	}

	VER_getTipo(corrente, &tipo);
	if(tipo != VER_Inicial){
		fprintf(stderr, "500: Estrutura do autômato está errada.\n");
		exit(1);
	}

	printf("Iniciando o reconhecimento do arquivo %s...\n", arquivo);

	while(!quit){
		push(pilha_retorno, corrente);
		VER_getTipo(corrente, &tipo);
		if(tipo == VER_Final) nfcounter = 0;
		else nfcounter++;

		read = fgetc(in);
		if(read == EOF){
			quit = 1;
			read = '\f';
		}

		if(read == '\\'){
			read = fgetc(in);
			if(read != EOF) read = especial(read);
			else {
				read = '\\';
				fseek(in, -1, SEEK_CUR);
			}
		}

		VER_getSucessores(corrente, &sucessores);
		corrente = proximo(g, sucessores, tolower(read));

		if(!corrente){
			corrente = (Vertice) peek(pilha_retorno);
			VER_getTipo(corrente, &tipo);
			if(tipo != VER_Final) corrente = retroceder();
			VER_getTipo(corrente, &tipo);
			if(tipo != VER_Final){
				fprintf(stderr, "Falha no reconhecimento..Continuando.\n");
				//pular os n primeiros caracteres e tentar novamente.
				fseek(in, loop++, SEEK_SET);
				quit = 0;
			}
			else {
				exibir(pilha_releitura, ++total);
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
					fprintf(stderr, "Falha no reconhecimento..Continuando.\n");
					//pular os n primeiros caracteres e tentar novamente.
					fseek(in, loop++, SEEK_SET);
					LIS_EsvaziarLista(pilha_releitura);
					LIS_EsvaziarLista(pilha_retorno);
					VerticedeChave(g, 0, &corrente);
					nfcounter = 0;
					quit = 0;	
				}
				else {
					exibir(pilha_releitura, ++total);
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

		if(loop == EOF){
			fprintf(stderr, "400: Erro na leitura do arquivo solicitado.\n");
			exit(1);
		}
	}
	
	if(ferror(in)){
		fprintf(stderr, "400: Erro na leitura do arquivo solicitado.\n");
		exit(1);
	}

	printf("Numero de lexemas reconhecidos: %d\n", total);
	printf("finalizando o reconhecimento...\n");
	if(fclose(in)){
		fprintf(stderr, "500: Não foi possível fechar o arquivo aberto para reconhecimento.\n");
		exit(1);
	}
}

Grafo lerAutomato(char* arquivo){
	Grafo g = NULL;
	char read;
	//flag para saber se estamos no inicio de linha ou nao.
	char start = 1;
	//flag para saber se estamos em modo de leitura de key de um vertice ou rotulo de aresta.
	char key = 1;
	//a chave do vertice atual.
	int chave;
	//input buffer de strings
	char input[BUFFER_SIZE];
	//buffer auxiliar
	char aux[BUFFER_SIZE];
	//numero de caracteres lidos de uma vez.
	char nread;
	GRP_tpCondRet cond;
	VER_tpCondRet vcond;
	Vertice corrente = NULL;
	Vertice anterior = NULL;
	FILE* in;

	if(!arquivo){
		fprintf(stderr, "400: Erro: nenhum arquivo de especificação de autômato foi dado!\n");
		exit(1);
	}
	in = fopen(arquivo, "r");
	if(!in){
		fprintf(stderr, "400: Erro na leitura do arquivo solicitado.\nO arquivo existe?\n");
		exit(1);
	}

	cond = GRP_CriarGrafo(&g);
	if(cond == GRP_CondRetFaltouMemoria){
		fprintf(stderr, "500: Erro interno da aplicação: falta de memória para alocar dados.\n");
		exit(1);
	}

	printf("Iniciando a leitura do autômato no arquivo %s...\n", arquivo);
	while((read = fgetc(in)) != EOF){
		if(read == '\n'){
			start = 1;
			continue;
		}
		if(isspace(read)) continue;
		if(read == ','){
			key = !key;
			if(start) start = 0;
			continue;
		}
		if(key){
			nread = fscanf(in, "%[^,]", input);
			if(nread > 0){
				if(isdigit(read)){
					*aux = read;
					*(aux + 1) = '\0';
					strcat(aux, input);
					strcpy(input, aux);
				}
			}
			else{
				if(!isdigit(read)){
					fprintf(stderr, "400: Estrutura do autômato está errada.\n");
					exit(1);
				}
				*input = read;
				*(input+1) = '\0';
			}

			chave = atoi(input);
			cond = VerticedeChave(g, chave, &corrente);
			if(cond == GRP_CondRetOK){
				if(start){
					anterior = corrente;
					continue;
				}

			}

			vcond = VER_CriarVertice(&corrente, NULL, chave, NULL);
			if(chave == 0) VER_ModificarTipo(corrente, VER_Inicial);
			else if(read == 'f') VER_ModificarTipo(corrente, VER_Final);


		}
		else{
		
		}


	}
	
	if(ferror(in)){
		fprintf(stderr, "400: Erro na leitura do arquivo solicitado.\n");
		exit(1);
	}

	if(fclose(in)){
		fprintf(stderr, "500: Não foi possível fechar o arquivo aberto para leitura do autômato.\n");
		exit(1);
	}
	printf("Autômato lido com sucesso!\n");
	return g;
}


int main(){
	pilha_releitura = LIS_CriarLista(NULL);
	pilha_retorno = LIS_CriarLista(NULL);
	if(!pilha_retorno || ! pilha_releitura){
		fprintf(stderr, "500: Erro interno da aplicação: falta de memória para alocar dados.\n");
		exit(1);
	}


	return 0;
}