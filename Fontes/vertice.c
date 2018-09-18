#include <stdlib.h>
#include <string.h>
#include "vertice.h"
#include "LISTA.H"


struct vertice{
	// listas de ARESTAS
	LIS_tppLista sucessores;
	LIS_tppLista antecessores;
	// a unica aresta do vertice para ele mesmo, se houver.
	Aresta reflexiva;
	void* valor;
	// identificador unico do vertice em um grafo
	int chave;
	// vertice foi visitado?
	int visitado;
	VER_TipoVer tipo;
};

struct aresta{
	int origem;
	int destino;
	char* rotulo;
};
