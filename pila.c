#include "pila.h"
#include <stdlib.h>
#define CAP_INICIAL 6
#define TAM_REDIMENSION 2
#define REDIMENSION_MIN 4

/* Definición del struct pila proporcionado por la cátedra.
 */
struct pila {
    void** datos;
    size_t cantidad;  // Cantidad de elementos almacenados.
    size_t capacidad;  // Capacidad del arreglo 'datos'.
};

/* *****************************************************************
 *                    PRIMITIVAS DE LA PILA
 * *****************************************************************/


pila_t* pila_crear(void){
	pila_t *pila = malloc(sizeof(pila_t));
	if(pila == NULL) return NULL;
	pila->cantidad = 0;
	pila->capacidad = CAP_INICIAL;
	pila->datos = malloc(CAP_INICIAL * sizeof(void *));
	if(pila->datos == NULL) {
        free(pila);
        return NULL;
    }
	return pila;
}


bool pila_redimensionar(pila_t *pila, size_t nueva_cap){
	void **nuevo = realloc(pila->datos, nueva_cap * sizeof(void *));
	if(!nuevo) return false;
	pila->datos = nuevo;
	pila->capacidad = nueva_cap;
	return true;
}


void pila_destruir(pila_t *pila){
	free(pila->datos);
	free(pila);
}


bool pila_esta_vacia(const pila_t *pila){
	return pila->cantidad == 0;
}


bool pila_apilar(pila_t *pila, void* valor){
	if(!pila) return false;
	if (pila->cantidad == pila->capacidad) {
		if(!pila_redimensionar(pila, TAM_REDIMENSION * pila->capacidad)) return false;
	}
	pila->datos[pila->cantidad] = valor;
	pila->cantidad++;
	return true;
}


void* pila_ver_tope(const pila_t *pila){
	if(pila_esta_vacia(pila)) return NULL;
	return pila->datos[pila->cantidad-1];
}


void* pila_desapilar(pila_t *pila){
	if(pila_esta_vacia(pila)) return NULL;
	pila->cantidad -= 1;
	void *r = pila->datos[pila->cantidad];
	const size_t CAP_MINIMA = pila->capacidad/REDIMENSION_MIN;
	if(pila->cantidad <= CAP_MINIMA && pila->capacidad > CAP_INICIAL) pila_redimensionar(pila, pila->capacidad / TAM_REDIMENSION);
	return r;
}


// ...
