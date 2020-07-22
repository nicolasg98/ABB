#define _GNU_SOURCE
#include "abb.h"
#include "pila.h"
#include <string.h>
#include <stddef.h>
#include <stdlib.h>
#include <stdbool.h>
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
	nodo_abb_t* nodo_abb = malloc(sizeof(nodo_abb_t));
	if(!nodo_abb) return NULL;
	nodo_abb->izq = NULL;
	nodo_abb->der = NULL;
	nodo_abb->clave = key;
	nodo_abb->dato = valor;
	return nodo_abb;
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
    if(!clave) return NULL;
    size_t largo = strlen(clave);
    char* clave_aux = malloc((largo + 1) * sizeof(char));
    if(!clave_aux) return NULL;
    strcpy(clave_aux, clave);
    return clave_aux;
}
 
nodo_abb_t* abb_nodo_buscar(const abb_t* arbol, nodo_abb_t* nodo, const char* clave){
    if(!nodo || (arbol->cant == 0)) return NULL;
    if(arbol->comparar(nodo->clave, clave) == 0) {
        return nodo;
    }
    else if(arbol->comparar(nodo->clave, clave) > 0){
        return abb_nodo_buscar(arbol, nodo->izq, clave);
    } else return abb_nodo_buscar(arbol, nodo->der, clave);
}
 
nodo_abb_t* buscar_padre(abb_t* arbol, nodo_abb_t* nodo, const char* clave){
    if(!nodo) return NULL;
    else if(arbol->comparar(nodo->clave, clave) > 0){
        if((!nodo->izq) || (arbol->comparar(nodo->izq->clave, clave) == 0)){
            return nodo;
        }
        return buscar_padre(arbol, nodo->izq, clave);
    }else if(arbol->comparar(nodo->clave, clave) < 0){
        if((!nodo->der) || (arbol->comparar(nodo->der->clave, clave) == 0)){
            return nodo;
        }
        else return buscar_padre(arbol, nodo->der, clave);
    }
    return NULL; //si es que no tiene padre
}
 
bool guardar_en_abb_no_vacio(abb_t* arbol, nodo_abb_t* nodo_abb, nodo_abb_t* nuevo){
    if(!arbol || !nodo_abb) return false;
    nodo_abb_t* padre = buscar_padre(arbol, nodo_abb, nuevo->clave);
    if(arbol->comparar(padre->clave, nuevo->clave) < 0) padre->der = nuevo;
    else if(arbol->comparar(padre->clave, nuevo->clave) > 0) padre->izq = nuevo;
    nuevo->izq = NULL;
    nuevo->der = NULL;
    arbol->cant ++;
    return true;
}
 
bool abb_pertenece(const abb_t *arbol, const char *clave){
    if(!abb_nodo_buscar(arbol, arbol->raiz, clave)) return false;
    return true;
}
 
bool abb_guardar(abb_t *arbol, const char *clave, void *dato){
    if(abb_pertenece(arbol, clave)){
        nodo_abb_t* encontrado = abb_nodo_buscar(arbol, arbol->raiz, clave);
        void* a_destruir = encontrado->dato;
        encontrado->dato = dato;
        if(arbol->destruir) arbol->destruir(a_destruir);
        return true;
    }
    char* clave_aux = crear_clave(clave);
    if(!clave_aux) return false;
    nodo_abb_t* nuevo = nodo_crear(clave_aux, dato);
    if(!nuevo){
        free(clave_aux);
        return false;
    }else{
        if(abb_cantidad(arbol) == 0){
            arbol->raiz = nuevo;
            arbol->raiz->izq = NULL;
            arbol->raiz->der = NULL;
            arbol->cant ++;
            return true;
        }
        else if(!guardar_en_abb_no_vacio(arbol, arbol->raiz, nuevo)) return false;
        return true;
    }
}
 
void *abb_obtener(const abb_t *arbol, const char *clave){
    nodo_abb_t* nodo = abb_nodo_buscar(arbol, arbol->raiz, clave);
    if(!nodo) return NULL;
    return nodo->dato;
}
 
size_t abb_cantidad(abb_t *arbol){
    return arbol->cant;
}
 
void* nodo_destruir(nodo_abb_t* nodo){
    char* clave_aux = nodo->clave;
    void* dato_aux = nodo->dato;
    free(clave_aux);
    free(nodo);
    return dato_aux;
}
 
void* borrar_nodo_sin_hijos(abb_t* arbol, nodo_abb_t* nodo, const char* clave){
    nodo_abb_t* padre = buscar_padre(arbol, arbol->raiz, clave);
    if(padre){
        if(arbol->comparar(padre->clave, nodo->clave) > 0) padre->izq = NULL;
        else padre->der = NULL;
    }
    else{
        arbol->raiz->izq = NULL;
        arbol->raiz->der = NULL;
    }
    return nodo_destruir(nodo);
}
 
void* borrar_nodo_con_un_hijo(abb_t* arbol, const char* clave, nodo_abb_t* nodo, nodo_abb_t* hijo){
    nodo_abb_t* padre = buscar_padre(arbol, arbol->raiz, clave);
    if(!padre) arbol->raiz = hijo;
    else{
        if(padre->izq){
            if(arbol->comparar(padre->izq->clave, nodo->clave) == 0) padre->izq = hijo;
        }
        if(padre->der){
            if(arbol->comparar(padre->der->clave, nodo->clave) == 0) padre->der = hijo;
        }
    }
    if(abb_cantidad(arbol) == 1) arbol->raiz = NULL;
    return nodo_destruir(nodo);
}
 
nodo_abb_t* buscar_reemplazante(abb_t* arbol, nodo_abb_t* nodo_a_borrar, nodo_abb_t* reemplazante){
    if(reemplazante->der) reemplazante = reemplazante->der;
    while(reemplazante->izq){
        reemplazante = reemplazante->izq;
    }
    return reemplazante;
}
 
void* borrar_nodo_con_dos_hijos(abb_t* arbol, nodo_abb_t* reemplazante, nodo_abb_t* nodo_a_borrar, char* clave_reemplazante){
    char* clave_aux = crear_clave(clave_reemplazante);
    void* dato;
    if(!reemplazante->der){
        dato = borrar_nodo_sin_hijos(arbol, reemplazante, reemplazante->clave);
    }
    else {
        dato = borrar_nodo_con_un_hijo(arbol, reemplazante->clave, reemplazante, reemplazante->der);
    }
    nodo_abb_t* nodo = abb_nodo_buscar(arbol, arbol->raiz, nodo_a_borrar->clave);
    char* a_borrar = nodo->clave;
    nodo->clave = crear_clave(clave_aux);
    void* dato_aux = nodo->dato;
    nodo->dato = dato;
    dato = dato_aux;
    free(a_borrar);
    free(clave_aux);
    return dato;
}
 
void *abb_borrar(abb_t *arbol, const char *clave){
    void* dato;
    char* clave_aux;
    nodo_abb_t* nodo = abb_nodo_buscar(arbol, arbol->raiz, clave);
    if(!nodo) return NULL;
    if((!nodo->izq) && (!nodo->der)){
        printf("CASO SIN HIJOS\n");
        dato = borrar_nodo_sin_hijos(arbol, nodo, clave);
    }
    else if((!nodo->izq) || (!nodo->der)){
        printf("CASO UN HIJO\n");
        nodo_abb_t* hijo;
        if(nodo->izq) hijo = nodo->izq;
        else hijo = nodo->der;
        dato = borrar_nodo_con_un_hijo(arbol, clave, nodo, hijo);
    }
    else{
        printf("CASO DOS HIJOS\n");
        nodo_abb_t* reemplazante = buscar_reemplazante(arbol, nodo, nodo);
        clave_aux = reemplazante->clave;
        dato = borrar_nodo_con_dos_hijos(arbol, reemplazante, nodo, clave_aux);
    }
    arbol->cant --;
    return dato;
}
 
void _abb_destruir(abb_t* arbol, nodo_abb_t* nodo){
    if(!nodo) return;
    if(nodo->izq){
        _abb_destruir(arbol, nodo->izq);
    }
    if(nodo->der){
        _abb_destruir(arbol, nodo->der);
    }
    printf("destruyo a %s.........\n",nodo->clave);
    void* a_borrar = abb_borrar(arbol, nodo->clave);
    if(arbol->destruir) arbol->destruir(a_borrar);
}
 
void abb_destruir(abb_t *arbol){
    if(!arbol) return;
    if(abb_cantidad(arbol) > 0) _abb_destruir(arbol, arbol->raiz);
    free(arbol);
}


void _iterador_interno(abb_t* arbol, nodo_abb_t* nodo, bool visitar(const char*, void*, void*), void* extra){
	if(!nodo) return;
	_iterador_interno(arbol, nodo->izq, visitar, extra);
	visitar(nodo->clave, nodo->dato, extra);
	_iterador_interno(arbol, nodo->der, visitar, extra);
}

//iter interno
void abb_in_order(abb_t *arbol, bool visitar(const char *, void *, void *), void *extra){
	nodo_abb_t* nodo = arbol->raiz;
	if(!nodo) return;
	_iterador_interno(arbol, nodo, visitar, extra);
}


/* *****************************************************************
 *           DEFINICION Y PRIMITIVAS DEL ITERADOR EXTERNO
 * *****************************************************************/


struct abb_iter{
	const abb_t* abb;
	pila_t* pila;
};

abb_iter_t *abb_iter_in_crear(const abb_t *arbol){
	abb_iter_t* iter_inorder = malloc(sizeof(abb_iter_t));
	if(!iter_inorder) return NULL;
	iter_inorder->abb = arbol;
	iter_inorder->pila = pila_crear();
	if(arbol->raiz != NULL) pila_apilar(iter_inorder->pila, arbol->raiz);
	nodo_abb_t* nodo = arbol->raiz;
	while(nodo != NULL){
		if(nodo->izq != NULL){
			nodo = nodo->izq;
			pila_apilar(iter_inorder->pila, nodo);
		}else break;
	}
	return iter_inorder;
}

bool abb_iter_in_avanzar(abb_iter_t *iter){
	if(abb_iter_in_al_final(iter)) return false;
	nodo_abb_t* nodo = pila_desapilar(iter->pila);
	if(!nodo) return false;
	if(nodo->der != NULL){
		nodo = nodo->der;
		if(abb_pertenece(iter->abb, nodo->clave)){
			pila_apilar(iter->pila, nodo);
			while(nodo->izq != NULL){
				pila_apilar(iter->pila, nodo->izq);
				nodo = nodo->izq;
			}
		}
	}
	return true;
}

const char *abb_iter_in_ver_actual(const abb_iter_t *iter){
	if(abb_iter_in_al_final(iter)) return NULL;
	nodo_abb_t* nodo_tope = pila_ver_tope(iter->pila);
	if(!nodo_tope) return NULL;
	return nodo_tope->clave;
}

bool abb_iter_in_al_final(const abb_iter_t *iter){
	return pila_esta_vacia(iter->pila);
}

void abb_iter_in_destruir(abb_iter_t* iter){
	while(!pila_esta_vacia(iter->pila)){
		free(pila_desapilar(iter->pila));
	}
	pila_destruir(iter->pila);
	free(iter);
}