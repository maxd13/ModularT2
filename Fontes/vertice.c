#include <stdlib.h>
#include "vertice.h"


struct vertice{
	// listas de ARESTAS
	Lista sucessores;
	Lista antecessores;
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
	float peso;
	char* rotulo;
};
