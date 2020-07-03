#define _GNU_SOURCE
#include "abb.h"
#include <string.h>
#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>


/* *****************************************************************
 *                DEFINICION Y PRIMITIVAS DEL NODO
 * *****************************************************************/

typedef struct nodo_abb{
	struct nodo_abb* izq;
	struct nodo_abb* der;
	char* clave;
	void* dato;
}nodo_abb_t;

nodo_abb_t* nodo_crear(char* key, void* valor){
	nodo_abb_t* nodo_abb = malloc(sizeof(nodo_t));
	if(!nodo) return NULL;
	nodo_abb->izq = NULL;
	nodo_abb->der = NULL;
	nodo_abb->clave = key;
	nodo_abb->dato = valor;
	return nodo_abb;
}

void nodo_destruir(nodo_abb_t* nodo){
	free(nodo);
}


/* *****************************************************************
 *                DEFINICION Y PRIMITIVAS DEL ABB
 * *****************************************************************/

//Definición del struct lista
struct abb{
	nodo_abb_t* raiz;
	size_t cant;
	abb_comparar_clave_t comparar;
	abb_destruir_dato_t destruir;
};

abb_t* abb_crear(abb_comparar_clave_t cmp, abb_destruir_dato_t destruir_dato){
	abb_t* abb = malloc(sizeof(abb_t));
	if(!abb) return NULL;
	abb->raiz = NULL;
	abb->cant = 0;
	abb->comparar = cmp;
	abb->destruir = destruir_dato;
	return abb;
}

nodo_abb_t* abb_nodo_buscar(abb_t* arbol, nodo_abb_t* nodo, const char* clave){
	if(!nodo) return NULL;
	if(arbol->comparar(arbol->raiz->clave, nodo->clave) == 1){
		abb_nodo_buscar(arbol, nodo->izq, clave);
	}else if(arbol->comparar(arbol->raiz->clave, nodo->clave) == 1){
		abb_nodo_buscar(arbol, nodo->der, clave);
	}
	return nodo;
}

bool abb_pertenece(const abb_t *arbol, const char *clave){
	if(!abb_nodo_buscar(arbol, arbol->raiz, clave)) return false;
	return true;
}

void *abb_obtener(const abb_t *arbol, const char *clave){
	nodo_abb_t* nodo = abb_nodo_buscar(arbol, arbol->raiz, clave);
	if(!nodo) return NULL;
	return nodo->dato;
}


void abb_destruir(abb_t *arbol){
	while(abb_pertenece(arbol, arbol->raiz->clave)){
		destruir_dato(abb_obtener(arbol, arbol->raiz->clave));
	}
	free(arbol->raiz);
	free(arbol);
}

//iter interno
void abb_in_order(abb_t *arbol, bool visitar(const char *, void *, void *), void *extra){

}