#include "cola.h"

typedef struct nodo {
	void *elemento;
	struct nodo *siguiente;

} nodo_t;

struct _cola_t {
	nodo_t *nodo_inicio;
	nodo_t *nodo_final;
	size_t tamanio;
};

cola_t *cola_crear()
{
	cola_t *cola = malloc(sizeof(cola_t));

	if (cola == NULL) {
		return NULL;
	}

	cola->nodo_inicio = NULL;

	return cola;
}

cola_t *cola_encolar(cola_t *cola, void *elemento)
{
	if (cola == NULL) {
		return NULL;
	}

	nodo_t *NuevoNodo = (nodo_t *)malloc(sizeof(nodo_t));

	if (NuevoNodo == NULL) {
		return NULL;
	}

	NuevoNodo->elemento = elemento;
	NuevoNodo->siguiente = NULL;

	if (cola->nodo_inicio == NULL) {
		cola->nodo_inicio = NuevoNodo;

		cola->tamanio += 1;
		return cola;
	}

	nodo_t *nodoActual = cola->nodo_inicio;

	while (nodoActual->siguiente != NULL) {
		nodoActual = nodoActual->siguiente;
	}

	nodoActual->siguiente = NuevoNodo;

	cola->tamanio += 1;
	return cola;
}

void *cola_desencolar(cola_t *cola)
{
	if (cola == NULL) {
		return NULL;
	}

	nodo_t *nodoActual = cola->nodo_inicio;

	cola->nodo_inicio = nodoActual->siguiente;
	void *elemento = nodoActual->elemento;

	free(nodoActual);
	cola->tamanio -= 1;

	return elemento;
}

void *cola_frente(cola_t *cola)
{
	if (cola == NULL || cola->nodo_inicio == NULL) {
		return NULL;
	}

	return cola->nodo_inicio->elemento;
}

size_t cola_tamanio(cola_t *cola)
{
	if (cola == NULL) {
		return 0;
	}

	return cola->tamanio;
}

bool cola_vacia(cola_t *cola)
{
	if (cola == NULL || cola->nodo_inicio == NULL) {
		return true;
	} else {
		return false;
	}
}

void cola_destruir(cola_t *cola)
{
	if (cola == NULL) {
		return;
	}

	while (!cola_vacia(cola)) {
		cola_desencolar(cola);
	}

	free(cola);
}
