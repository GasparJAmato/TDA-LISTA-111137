#include "lista.h"
#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>

typedef struct nodo {
	void *elemento;
	struct nodo *siguiente;

} nodo_t;

struct lista {
	nodo_t *nodo_inicio;
	
};

struct lista_iterador {
	nodo_t *actual;
	nodo_t *anterior;
};

lista_t *lista_crear()
{	
	lista_t *lista = malloc(sizeof(lista_t));

	if(lista == NULL){

		printf("ERROR: no se pudo asignar memoria correctamente");
		return NULL;
		
	}

	lista->nodo_inicio = NULL;
	
	return lista;
}

lista_t *lista_insertar(lista_t *lista, void *elemento)
{	
	if(lista == NULL || elemento == NULL){
		return NULL;
	}

	nodo_t *NuevoNodo = (nodo_t *)malloc(sizeof(nodo_t));

	if(NuevoNodo == NULL){
		printf("ERROR: no se pudo reservar memoria correctamente");
		return NULL;
	}

	NuevoNodo->elemento = elemento;
	NuevoNodo->siguiente = NULL;


	if(lista->nodo_inicio == NULL){
		lista->nodo_inicio = NuevoNodo;

		return lista;
	}

	nodo_t *nodoActual = lista->nodo_inicio;

	while(nodoActual->siguiente != NULL){
		nodoActual = nodoActual->siguiente;
	}


	nodoActual->siguiente = NuevoNodo;

	return lista;
}

lista_t *lista_insertar_en_posicion(lista_t *lista, void *elemento,
				    size_t posicion)
{	
	if(lista == NULL ){
		return NULL;
	}

	nodo_t *NuevoNodo = (nodo_t *)malloc(sizeof(nodo_t));

	if(NuevoNodo == NULL){
		printf("ERROR: no se pudo reservar memoria correctamente");
		return NULL;
	}

	NuevoNodo->elemento = elemento;
	NuevoNodo->siguiente = NULL;


    if (posicion == 0) {
        NuevoNodo->siguiente = lista->nodo_inicio;
        lista->nodo_inicio = NuevoNodo;
        return lista;
    }

	nodo_t *nodoActual = lista->nodo_inicio;
	nodo_t *anterior = NULL;


	for(size_t i = 0; i < posicion; i++){
		
		if(nodoActual == NULL){
			printf("ERROR: la posicion elegida esta fuera de rango");
			free(NuevoNodo);
			return NULL;
		}

		anterior = nodoActual;
		nodoActual = nodoActual->siguiente;
	}

		anterior->siguiente = NuevoNodo;
		NuevoNodo->siguiente = nodoActual;
		
	
	return lista;
}

void *lista_quitar(lista_t *lista)
{	

	if(lista == NULL || lista->nodo_inicio == NULL){
		printf("ERROR: la lista no existe o no tiene elementos");
		return NULL;
	}

	nodo_t *nodoActual = lista->nodo_inicio;
	nodo_t *anterior = NULL;

	if (lista->nodo_inicio->siguiente == NULL) {
		
	    void *elemento = lista->nodo_inicio->elemento;
    	free(lista->nodo_inicio);
    	lista->nodo_inicio = NULL;
    	return elemento;	
	}

	while(nodoActual->siguiente != NULL){
		anterior = nodoActual;
		nodoActual = nodoActual->siguiente;
	}

	void *elemento = nodoActual->elemento;

	free(nodoActual);
	
    
    anterior->siguiente = NULL;
 
    


	return elemento;
}

void *lista_quitar_de_posicion(lista_t *lista, size_t posicion)
{	
	if(lista == NULL){
		return NULL;
	}

	nodo_t *nodoActual = lista->nodo_inicio;
	nodo_t *anterior = NULL;

    if (posicion == 0) {
        
        lista->nodo_inicio = nodoActual->siguiente;

		void *elemento = nodoActual->elemento;

		free(nodoActual);

        return elemento;
    }

	for(size_t i = 0; i < posicion; i++){
		
		if(nodoActual == NULL){

			printf("ERROR: la posicion elegida esta fuera de rango");			
			return NULL;
			
		}

		anterior = nodoActual;
		nodoActual = nodoActual->siguiente;
	}

	anterior->siguiente = nodoActual->siguiente;

	void *elemento = nodoActual->elemento;

	free(nodoActual);

	return elemento;
}

void *lista_elemento_en_posicion(lista_t *lista, size_t posicion)
{
    if (lista == NULL || lista->nodo_inicio == NULL) {
      
        return NULL;
    }

    size_t rango = lista_tamanio(lista);

    if (posicion >= rango) {
        
        return NULL;
    }

    nodo_t *nodoActual = lista->nodo_inicio;
    size_t posicionActual = 1;

    while (posicionActual != posicion) {
        posicionActual++;
        nodoActual = nodoActual->siguiente;
    }

    return nodoActual->elemento;
}

void *lista_buscar_elemento(lista_t *lista, int (*comparador)(void *, void *),
			    void *contexto)
{	
	if(lista == NULL || comparador == NULL || contexto == NULL || lista->nodo_inicio == NULL){
		return NULL;
	}
	
	size_t rango = lista_tamanio(lista);
	nodo_t *nodoActual = lista->nodo_inicio;

	for(size_t i = 0; i < rango; i++ ){
		if(comparador(nodoActual->elemento, contexto) == 0){
			return nodoActual->elemento;
		}
	}
	return NULL;
}

void *lista_primero(lista_t *lista)
{
	if(lista == NULL || lista->nodo_inicio == NULL){
		return NULL;
	}
	nodo_t *nodoActual = lista->nodo_inicio;
	return nodoActual->elemento;
}

void *lista_ultimo(lista_t *lista)
{	
	if(lista == NULL || lista->nodo_inicio == NULL){
		return NULL;
	}

	nodo_t *nodoActual = lista->nodo_inicio;

    while (nodoActual->siguiente != NULL) {
        nodoActual = nodoActual->siguiente;
    }
	return nodoActual->elemento;
}

bool lista_vacia(lista_t *lista)
{	
	if(lista == NULL || lista->nodo_inicio == NULL){
		return true;
	}else{
		return false;
	}
	
}

size_t lista_tamanio(lista_t *lista)
{	

	if(lista == NULL){
		return 0;
	}

	nodo_t *nodoActual = lista->nodo_inicio;
	size_t tamanio = 0;

	while(nodoActual != NULL){
		tamanio++;
		nodoActual = nodoActual->siguiente;
	}
	return tamanio;
}

void lista_destruir(lista_t *lista)
{
	if(lista == NULL ){
		return;
	}
	nodo_t *nodoActual = lista->nodo_inicio;
	while(nodoActual != NULL){

        nodo_t *nodoAEliminar = nodoActual;
        nodoActual = nodoActual->siguiente;
        free(nodoAEliminar); 
	}
	free(lista);
}

void lista_destruir_todo(lista_t *lista, void (*funcion)(void *))
{
	nodo_t *nodoActual = lista->nodo_inicio;

    while (nodoActual != NULL) {

        nodo_t *nodoAEliminar = nodoActual;
        nodoActual = nodoActual->siguiente;

        if (funcion != NULL) {

            funcion(nodoAEliminar->elemento);
        }

        free(nodoAEliminar);
		
    }
	free(lista);
	
}

lista_iterador_t *lista_iterador_crear(lista_t *lista)
{
	lista_iterador_t* iterador = NULL;

    if(lista == NULL){
        return NULL;
    }
    iterador = malloc(sizeof(lista_iterador_t));
    if (iterador == NULL){
        return NULL;
    }
    
    
    iterador->actual = lista->nodo_inicio;
	iterador->anterior = NULL;

    return iterador;
}

bool lista_iterador_tiene_siguiente(lista_iterador_t *iterador)
{
	if(iterador == NULL){
		return false;
	}

	return iterador->actual->siguiente != NULL;
	
	
}

bool lista_iterador_avanzar(lista_iterador_t *iterador)
{
	if(iterador == NULL){
		return false;
	}

	if(lista_iterador_tiene_siguiente(iterador)){
		iterador->anterior = iterador->actual;
		iterador->actual = iterador->actual->siguiente;
		return true;
	}else{
		return false;
	}

}

void *lista_iterador_elemento_actual(lista_iterador_t *iterador)
{
	if(iterador == NULL || iterador->actual == NULL ){
		return NULL;
	}

	return iterador->actual->elemento;
}

void lista_iterador_destruir(lista_iterador_t *iterador)
{	
	if(iterador == NULL){
		return;
	}

	free(iterador);
}

size_t lista_con_cada_elemento(lista_t *lista, bool (*funcion)(void *, void *),
			       void *contexto)
{

    if(lista == NULL || contexto == NULL || funcion == NULL || lista_tamanio(lista) == 0){
        return 0;
    }
	
	size_t iterados = 0;
	nodo_t *nodoActual = lista->nodo_inicio;

	while(funcion(nodoActual, contexto) && nodoActual->siguiente != NULL){
		iterados++;
		nodoActual = nodoActual->siguiente;
	}
	iterados++;

	return iterados;
}
