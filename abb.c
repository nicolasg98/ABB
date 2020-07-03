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

char* crear_clave(const char* clave){
	size_t largo = strlen(clave);
	char* clave_aux = malloc((largo + 1) * sizeof(char));
	if(!clave_aux) return NULL;
	strcpy(clave_aux, clave);
	return clave_aux;
}

nodo_abb_t* abb_nodo_buscar(abb_t* arbol, nodo_abb_t* nodo, const char* clave){
	if(!nodo) return NULL;
	if(arbol->comparar(nodo->clave, clave) == 0) return nodo;
	else if(arbol->comparar(nodo->clave, clave) > 0){
		abb_nodo_buscar(arbol, nodo->izq, clave);
	}else abb_nodo_buscar(arbol, nodo->der, clave);
}

nodo_abb_t* buscar_padre(abb_t* arbol, nodo_abb_t* nodo, const char* clave){
	if(!nodo) return NULL;
	else if(arbol->comparar(nodo->clave, clave) > 0){
		if(!nodo->izq) return nodo;
		abb_nodo_buscar(arbol, nodo->izq, clave);
	}else if(arbol->comparar(nodo->clave, clave) < 0){
		if(!nodo->der) return nodo;
		else abb_nodo_buscar(arbol, nodo->der, clave);
	}
}

bool guardar_en_abb_no_vacio(abb_t* arbol, nodo_abb_t* nodo_abb, nodo_abb_t* nuevo){
	if(!arbol || !nodo_abb) return false;
	if(abb_pertenece(arbol, nuevo->clave)){
		void* a_destruir = nodo_abb->dato;
		nodo_abb->dato = nuevo->dato;
		if(arbol->destruir) arbol->destruir(a_destruir);
		return true;
	}
	nodo_abb_t* padre = buscar_padre(arbol, nodo_abb, nuevo->clave);
	if(arbol->comparar(padre->clave, nuevo->clave) < 0) padre->der = nuevo;
	else if(arbol->comparar(padre->clave, nuevo->clave) > 0) padre->izq = nuevo;
	return true;
}

bool abb_guardar(abb_t *arbol, const char *clave, void *dato){
	char* clave_aux = crear_clave(clave);
	if(!clave_aux) return false;
	nodo_abb_t* nuevo = nodo_crear(clave_aux, dato);
	if(!nuevo){
		free(clave_aux);
		return false;
	}
	if(abb_cantidad(arbol) == 0){
		arbol->raiz = nuevo;
		arbol->cantidad ++;
		return true;
	}
	else if(!guardar_en_abb_no_vacio(arbol, arbol->raiz, nuevo)) return false;
	arbol->cantidad ++;
	return true;
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
