#include "pila.h"

typedef struct nodo {
	void *elemento;
	struct nodo *siguiente;

} nodo_t;

struct _pila_t {
	nodo_t *nodo_inicio;
	size_t tamanio;
};

pila_t *pila_crear()
{
	pila_t *pila = malloc(sizeof(pila_t));

	if (pila == NULL) {
		return NULL;
	}

	pila->nodo_inicio = NULL;
	pila->tamanio = 0;

	return pila;
	;
}

pila_t *pila_apilar(pila_t *pila, void *elemento)
{
	if (pila == NULL) {
		return NULL;
	}

	nodo_t *NuevoNodo = malloc(sizeof(nodo_t));

	if (NuevoNodo == NULL) {
		return NULL;
	}

	NuevoNodo->elemento = elemento;
	NuevoNodo->siguiente = pila->nodo_inicio;
	pila->nodo_inicio = NuevoNodo;
	pila->tamanio += 1;
	return pila;
}

void *pila_desapilar(pila_t *pila)
{
	if (pila == NULL || pila->nodo_inicio == NULL) {
		return NULL;
	}

	nodo_t *nodoActual = pila->nodo_inicio;
	pila->nodo_inicio = nodoActual->siguiente;
	void *elemento = nodoActual->elemento;
	free(nodoActual);
	pila->tamanio -= 1;
	return elemento;
}

void *pila_tope(pila_t *pila)
{
	if (pila == NULL || pila->nodo_inicio == NULL) {
		return NULL;
	}

	return pila->nodo_inicio->elemento;
}

size_t pila_tamanio(pila_t *pila)
{
	if (pila == NULL) {
		return 0;
	}

	return pila->tamanio;
}

bool pila_vacia(pila_t *pila)
{
	if (pila == NULL || pila->nodo_inicio == NULL) {
		return true;
	} else {
		return false;
	}
}

void pila_destruir(pila_t *pila)
{
	if (pila == NULL) {
		return;
	}

	while (!pila_vacia(pila)) {
		pila_desapilar(pila);
	}
	free(pila);
}