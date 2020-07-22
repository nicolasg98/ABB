#include "abb.h"
#include <stdbool.h>
#include <stdio.h>
#include "testing.h"
#include <stdlib.h>
#include <string.h>
#include <time.h>

void pruebas_crear_abb_vacio(){
	printf("PRUEBAS CREAR ABB VACIO\n");
	abb_t* abb = abb_crear(strcmp,NULL);

	print_test("Prueba arbol crear arbol vacio", abb);
    print_test("Prueba arbol la cantidad de elementos es 0", abb_cantidad(abb) == 0);
    //print_test("Prueba arbol obtener clave A, es NULL, no existe", !abb_obtener(abb, "A"));
    //print_test("Prueba arbol pertenece clave A, es false, no existe", !abb_pertenece(abb, "A"));
    //print_test("Prueba arbol borrar clave A, es NULL, no existe", !abb_borrar(habb, "A"));
    abb_destruir(abb);
    print_test("El árbol fue destruido", true);
    //printf("DESTRUIDO\n");
}

void pruebas_abb_guardar(){
	printf("PRUEBAS ABB GUARDAR\n");
	abb_t* abb = abb_crear(strcmp, NULL);

    char *clave1 = "perro", *valor1 = "guau";
    char *clave2 = "gato", *valor2 = "miau";
    char *clave3 = "vaca", *valor3 = "mu";
    char arreglo_claves[10] = {'a','b','c','d','e','f','g','h','i','j'};
    srand((unsigned int) time(NULL));
    char clave_elegida = arreglo_claves[rand() % 10];
    printf("la clave elegida es %c (no dar bola por ahora)\n", clave_elegida);

    /* Inserta 1 valor y luego lo borra */
    print_test("Prueba abb insertar clave1", abb_guardar(abb, clave1, valor1));
    print_test("Prueba abb la cantidad de elementos es 1", abb_cantidad(abb) == 1);
    //print_test("Prueba abb obtener clave1 es valor1", abb_obtener(abb, clave1) == valor1);
    //print_test("Prueba abb obtener clave1 es valor1", abb_obtener(abb, clave1) == valor1);
    //print_test("Prueba abb pertenece clave1, es true", abb_pertenece(abb, clave1));
    //print_test("Prueba abb borrar clave1, es valor1", abb_borrar(abb, clave1) == valor1);
    //print_test("Prueba abb la cantidad de elementos es 0", abb_cantidad(abb) == 0);

    /* Inserta otros 2 valores y no los borra (se destruyen con el hash) */
    print_test("Prueba abb insertar clave2", abb_guardar(abb, clave2, valor2));
    print_test("Prueba abb la cantidad de elementos es 1", abb_cantidad(abb) == 2);
    print_test("Prueba abb obtener clave2 es valor2", abb_obtener(abb, clave2) == valor2);
    print_test("Prueba abb obtener clave2 es valor2", abb_obtener(abb, clave2) == valor2);
    print_test("Prueba abb pertenece clave2, es true", abb_pertenece(abb, clave2));

    print_test("Prueba abb insertar clave3", abb_guardar(abb, clave3, valor3));
    print_test("Prueba abb la cantidad de elementos es 2", abb_cantidad(abb) == 3);
    print_test("Prueba abb obtener clave3 es valor3", abb_obtener(abb, clave3) == valor3);
    print_test("Prueba abb obtener clave3 es valor3", abb_obtener(abb, clave3) == valor3);
    print_test("Prueba abb pertenece clave3, es true", abb_pertenece(abb, clave3));

    abb_destruir(abb);
    print_test("El ABB fue destruido", true);
    //va a dar errores de memoria pero es porque no funciona el destruir
}

void pruebas_abb_volumen(){
    printf("\nPRUEBAS DE VOLUMEN DEL ABB\n\n");
    abb_t* abb = abb_crear(strcmp, NULL);
    print_test("ABB fue creado", true);
    print_test("Prueba arbol la cantidad de elementos es 0", abb_cantidad(abb) == 0);
    //Insertar muchos elementos
    char clave[1000][10];
    int* valor;
    int numero = 0;
    valor = &numero;
    for(int i = 0; i < 1000; i++){
        memset(clave, '\0', 12);
        srand((unsigned)(clock()));        
        for (int j = 0; j < 10; j++){            
            char letra = (char) ('a' + (rand() % 26));
            clave[i][j] = letra;
        }
        numero = rand() % 100;
        *valor = numero;
        abb_guardar(abb, clave[i], valor);
        print_test("Prueba abb la clave pertenece", abb_pertenece(abb, clave[i]));
        print_test("Prueba abb obtener clave es valor", abb_obtener(abb, clave[i]) == valor);
    }
    print_test("Prueba abb la cantidad de elementos es 1000", abb_cantidad(abb) == 1000);
    for (int i = 999; i == 0; i--){
        print_test("Prueba abb borrar clave", abb_borrar(abb, clave[i]));
    }
    abb_destruir(abb);
    //print_test("Prueba arbol la cantidad de elementos es 0", abb_cantidad(abb) == 0);
    print_test("El árbol fue destruido", true);
}

void pruebas_abb_borrar_nodo_con_dos_hijos(){
    printf("PRUEBAS ABB BORRAR (CON DOS HIJOS)...........................\n");
 
    abb_t* abb = abb_crear(strcmp, NULL);
 
    char *clave1 = "gato", *valor1 = "miau";
    char *clave2 = "perro", *valor2 = "guau";
    char *clave3 = "vaca", *valor3 = "mu";
    char *clave4 = "delfin", *valor4 = "???";
    char *clave5 = "pato", *valor5 = "quack";
    char *clave6 = "tortuga", *valor6 = "tortuga";
 
    print_test("Prueba abb insertar clave1", abb_guardar(abb, clave1, valor1));
    print_test("Prueba abb insertar clave4", abb_guardar(abb, clave4, valor4));
    print_test("Prueba abb insertar clave2", abb_guardar(abb, clave2, valor2));
    print_test("Prueba abb insertar clave3", abb_guardar(abb, clave3, valor3));
    print_test("Prueba abb insertar clave5", abb_guardar(abb, clave5, valor5));
    print_test("Prueba abb insertar clave6", abb_guardar(abb, clave6, valor6));
 
    //borro, el reemplazante no tiene hijos
    print_test("Prueba abb pertenece clave2, es verdadero", abb_pertenece(abb, clave2));
    print_test("Prueba abb borrar clave2, es valor2", abb_borrar(abb, clave2) == valor2);
    print_test("Prueba abb borrar clave2, es NULL", !abb_borrar(abb, clave2));
    print_test("Prueba abb pertenece clave2, es falso", !abb_pertenece(abb, clave2));
    print_test("Prueba abb obtener clave2, es NULL", !abb_obtener(abb, clave2));
    print_test("Prueba abb la cantidad de elementos es 5", abb_cantidad(abb) == 5);
 
    //borro la raiz, el reemplazante no tiene hijos
    print_test("Prueba abb pertenece clave1, es verdadero", abb_pertenece(abb, clave1));
    print_test("Prueba abb borrar clave1, es valor1", abb_borrar(abb, clave1) == valor1);
    print_test("Prueba abb borrar clave1, es NULL", !abb_borrar(abb, clave1));
    print_test("Prueba abb pertenece clave1, es falso", !abb_pertenece(abb, clave1));
    print_test("Prueba abb obtener clave1, es NULL", !abb_obtener(abb, clave1));
    print_test("Prueba abb la cantidad de elementos es 4", abb_cantidad(abb) == 4);
 
    //borro la nueva raiz, el reemplazante tiene un hijo
    print_test("Prueba abb pertenece clave5, es verdadero", abb_pertenece(abb, clave5));
    print_test("Prueba abb borrar clave5, es valor5", abb_borrar(abb, clave5) == valor5);
    print_test("Prueba abb borrar clave5, es NULL", !abb_borrar(abb, clave5));
    print_test("Prueba abb pertenece clave5, es falso", !abb_pertenece(abb, clave5));
    print_test("Prueba abb obtener clave5, es NULL", !abb_obtener(abb, clave5));
    print_test("Prueba abb la cantidad de elementos es 3", abb_cantidad(abb) == 3);
 
    abb_destruir(abb);
 
}


void pruebas_iter_externo_vacio(){
    printf("\nPRUEBAS ITER CON ABB VACIO\n\n");
    abb_t* abb = abb_crear(strcmp, NULL);
    print_test("ABB fue creado", true);
    print_test("Prueba arbol la cantidad de elementos es 0", abb_cantidad(abb) == 0);
    abb_iter_t* iter = abb_iter_in_crear(abb);
    print_test("Iterador externo creado", true);
    print_test("El iterador está al final", abb_iter_in_al_final(iter));
    abb_iter_in_destruir(iter);
    print_test("El iterador externo fue destruido", true);
    abb_destruir(abb);
    print_test("El árbol fue destruido", true);
}

void pruebas_iter_externo_elementos(){
    printf("\nPRUEBAS ITER ABB CON ELEMENTOS\n\n");
    abb_t* abb = abb_crear(strcmp, NULL);
    print_test("ABB fue creado", true);
    puts("Genero 3 claves e inserto cada una en el arbol que se encuentra vacío");
    char *clave1 = "perro", *valor1 = "guau";
    char *clave2 = "gato", *valor2 = "miau";
    char *clave3 = "vaca", *valor3 = "mu";
    char arreglo_claves[10] = {'a','b','c','d','e','f','g','h','i','j'};
    srand((unsigned int) time(NULL));
    char clave_elegida = arreglo_claves[rand() % 10];
    printf("la clave elegida es %c (no dar bola por ahora)\n", clave_elegida);
    /* Inserta 1 valor y luego lo borra */
    print_test("Prueba abb insertar clave1", abb_guardar(abb, clave1, valor1));  
    /* Inserta otros 2 valores y no los borra (se destruyen con el hash) */
    print_test("Prueba abb insertar clave2", abb_guardar(abb, clave2, valor2));
    print_test("Prueba abb insertar clave3", abb_guardar(abb, clave3, valor3));
    print_test("Prueba abb la cantidad de elementos es 3", abb_cantidad(abb) == 3);
    abb_iter_t* iter = abb_iter_in_crear(abb);
    print_test("Iterador externo creado", true);
    print_test("El iterador NO está al final", !abb_iter_in_al_final(iter));
    print_test("Ver actual es el úlitmo hijo izquierdo del árbol", *clave2 == *(char*)abb_iter_in_ver_actual(iter));
    print_test("Avanzar se realiza correctamente", abb_iter_in_avanzar(iter));
    print_test("Ver actual es la raíz del árbol", *clave1 == *(char*)abb_iter_in_ver_actual(iter));
    print_test("Avanzar se realiza correctamente", abb_iter_in_avanzar(iter));
    print_test("Ver actual es el hijo derecho de la raíz del árbol", *clave3 == *(char*)abb_iter_in_ver_actual(iter));
    print_test("Avanzar se realiza correctamente", abb_iter_in_avanzar(iter));
    print_test("El iterador se encuentra al final", abb_iter_in_al_final(iter));
    print_test("Avanzar es inválido", !abb_iter_in_avanzar(iter));
    abb_iter_in_destruir(iter);
    print_test("El iterador fue destruido", true);
    abb_destruir(abb);
    print_test("El ABB fue destruido", true);
}


void pruebas_iter_solo_hijos_izquierdos(){
    printf("\nPRUEBAS ITER SOLO CON HIJOS IZQUIERDOS\n\n");
    abb_t* abb = abb_crear(strcmp, NULL);
    print_test("ABB fue creado", true);
    puts("Genero 3 claves e inserto cada una en el arbol que se encuentra vacío");
    char *clave1 = "perro", *valor1 = "guau";
    char *clave2 = "gato", *valor2 = "miau";
    char *clave3 = "vaca", *valor3 = "mu";
    char arreglo_claves[10] = {'a','b','c','d','e','f','g','h','i','j'};
    srand((unsigned int) time(NULL));
    char clave_elegida = arreglo_claves[rand() % 10];
    printf("la clave elegida es %c (no dar bola por ahora)\n", clave_elegida);
    /* Inserta 1 valor y luego lo borra */
    print_test("Prueba abb insertar clave3", abb_guardar(abb, clave3, valor1));
    /* Inserta otros 2 valores y no los borra (se destruyen con el hash) */
    print_test("Prueba abb insertar clave1", abb_guardar(abb, clave1, valor2));
    print_test("Prueba abb insertar clave2", abb_guardar(abb, clave2, valor3));
    print_test("Prueba abb la cantidad de elementos es 3", abb_cantidad(abb) == 3);
    abb_iter_t* iter = abb_iter_in_crear(abb);
    print_test("Iterador externo creado", true);
    print_test("El iterador NO está al final", !abb_iter_in_al_final(iter));
    print_test("Ver actual es el último hijo izquierdo en el árbol", *clave2 == *(char*)abb_iter_in_ver_actual(iter));
    print_test("Avanzar se realiza correctamente", abb_iter_in_avanzar(iter));
    print_test("Ver actual es el primer hijo izquierdo del árbol", *clave1 == *(char*)abb_iter_in_ver_actual(iter));
    print_test("Avanzar se realiza correctamente", abb_iter_in_avanzar(iter));
    print_test("Ver actual es la raíz del árbol", *clave3 == *(char*)abb_iter_in_ver_actual(iter));
    print_test("Avanzar se realiza correctamente", abb_iter_in_avanzar(iter));
    print_test("El iterador se encuentra al final", abb_iter_in_al_final(iter));
    print_test("Avanzar es inválido", !abb_iter_in_avanzar(iter));
    abb_iter_in_destruir(iter);
    print_test("El iterador fue destruido", true);
    abb_destruir(abb);
    print_test("El árbol fue destruido", true);
}

void pruebas_iter_solo_hijos_derechos(){
    printf("\nPRUEBAS ITER SOLO CON HIJOS DERECHOS\n\n");
    abb_t* abb = abb_crear(strcmp, NULL);
    print_test("ABB fue creado", true);
    puts("Genero 3 claves e inserto cada una en el arbol que se encuentra vacío");
    char *clave1 = "perro", *valor1 = "guau";
    char *clave2 = "gato", *valor2 = "miau";
    char *clave3 = "vaca", *valor3 = "mu";
    char arreglo_claves[10] = {'a','b','c','d','e','f','g','h','i','j'};
    srand((unsigned int) time(NULL));
    char clave_elegida = arreglo_claves[rand() % 10];
    printf("la clave elegida es %c (no dar bola por ahora)\n", clave_elegida);
    /* Inserta 1 valor y luego lo borra */
    print_test("Prueba abb insertar clave2", abb_guardar(abb, clave2, valor1));  
    /* Inserta otros 2 valores y no los borra (se destruyen con el hash) */
    print_test("Prueba abb insertar clave1", abb_guardar(abb, clave1, valor2));
    print_test("Prueba abb insertar clave3", abb_guardar(abb, clave3, valor3));
    print_test("Prueba abb la cantidad de elementos es 3", abb_cantidad(abb) == 3);
    abb_iter_t* iter = abb_iter_in_crear(abb);
    print_test("Iterador externo creado", true);
    print_test("El iterador NO está al final", !abb_iter_in_al_final(iter));
    print_test("Ver actual es la raíz del arbol", *clave2 == *(char*)abb_iter_in_ver_actual(iter));
    print_test("Avanzar se realiza correctamente", abb_iter_in_avanzar(iter));
    print_test("Ver actual es el primer hijo derecho", *clave1 == *(char*)abb_iter_in_ver_actual(iter));
    print_test("Avanzar se realiza correctamente", abb_iter_in_avanzar(iter));
    print_test("Ver actual es el último hijo derecho de la raíz", *clave3 == *(char*)abb_iter_in_ver_actual(iter));
    print_test("Avanzar se realiza correctamente", abb_iter_in_avanzar(iter));
    print_test("El iterador se encuentra al final", abb_iter_in_al_final(iter));
    print_test("Avanzar es inválido", !abb_iter_in_avanzar(iter));
    abb_iter_in_destruir(iter);
    print_test("El iterador fue destruido", true);
    abb_destruir(abb);
    print_test("El árbol fue destruido", true);
}

void pruebas_iter_externo_volumen(){
    printf("\nPRUEBAS DE VOLUMEN CON ITER\n\n");
    abb_t* abb = abb_crear(strcmp, NULL);
    print_test("ABB fue creado", true);
    print_test("Prueba arbol la cantidad de elementos es 0", abb_cantidad(abb) == 0);
    //Insertar muchos elementos
    //genero una cadena de caracteres de 12 caracteres de longitud en el que cada caracter se elige aleatoriamente entre a y z
    //me aseguro asi que sea casi imposible que se repitan las claves (igual compruebo)
    char clave[12];
    for(int i = 0; i < 1000; i++){
        memset(clave, '\0', 12);
        srand((unsigned)(clock()));        
        for (int j = 0; j < 11; j++){            
            char letra = (char) ('a' + (rand() % 26));
            clave[j] = letra;
        }
        if(!abb_pertenece(abb, clave)) abb_guardar(abb, clave, NULL);
    }
    printf("%ld\n", abb_cantidad(abb));
    abb_iter_t* iter = abb_iter_in_crear(abb);
    print_test("Iterador externo creado", true);
    print_test("El iterador NO está al final", !abb_iter_in_al_final(iter));
    size_t recorrido = abb_cantidad(abb);
    bool avanza = true;
    while(!abb_iter_in_al_final(iter)){
        avanza = abb_iter_in_avanzar(iter);
        if(!avanza) break;
        recorrido--;
    }
    print_test("El iterador recorre todos los elementos del árbol", recorrido == 0);
    print_test("El iterador se encuentra al final", abb_iter_in_al_final(iter));
    print_test("Avanzar es inválido", !abb_iter_in_avanzar(iter));
    abb_iter_in_destruir(iter);
    print_test("El iterador externo fue destruido", true);
    abb_destruir(abb);
    print_test("El árbol fue destruido", true);
}

void pruebas_iter_externo_clave_vacia(){
    printf("\nPRUEBAS ITER CLAVE VACIA VALOR NULL\n\n");
    abb_t* abb = abb_crear(strcmp, NULL);
    print_test("ABB fue creado", true);
    char *vacio = "";
    print_test("Prueba abb insertar NULL", abb_guardar(abb, vacio, NULL));
    print_test("Prueba abb la cantidad de elementos es 1", abb_cantidad(abb) == 1);
    abb_iter_t* iter = abb_iter_in_crear(abb);
    print_test("Iterador externo creado", true);
    print_test("El iterador NO está al final", !abb_iter_in_al_final(iter));
    print_test("Ver actual es clave vacía", *vacio == *(char*)abb_iter_in_ver_actual(iter));
    print_test("Avanzar se realiza correctamente", abb_iter_in_avanzar(iter));
    print_test("El iterador se encuentra al final", abb_iter_in_al_final(iter));
    print_test("Avanzar es inválido", !abb_iter_in_avanzar(iter));
    abb_iter_in_destruir(iter);
    print_test("El iterador externo fue destruido", true);
    abb_destruir(abb);
    print_test("El árbol fue destruido", true);
}

bool imprimir(const char* clave, void *dato, void *extra){
    printf("%s\n", (char*)dato);
    return true;
}

void pruebas_iter_interno(){
    printf("\nPRUEBAS ITER ABB CON ELEMENTOS\n\n");
    abb_t* abb = abb_crear(strcmp, NULL);
    print_test("ABB fue creado", true);
    puts("Genero 3 claves e inserto cada una en el arbol que se encuentra vacío");
    char *clave1 = "perro", *valor1 = "guau";
    char *clave2 = "gato", *valor2 = "miau";
    char *clave3 = "vaca", *valor3 = "mu";
    char *clave4 = "ballena", *valor4 = "agua";
    char *clave5 = "atomo", *valor5 = "proton";
    print_test("Prueba abb insertar clave1", abb_guardar(abb, clave1, valor1));
    print_test("Prueba abb insertar clave2", abb_guardar(abb, clave2, valor2));
    print_test("Prueba abb insertar clave3", abb_guardar(abb, clave3, valor3));
    print_test("Prueba abb insertar clave4", abb_guardar(abb, clave4, valor4));
    print_test("Prueba abb insertar clave5", abb_guardar(abb, clave5, valor5));
    print_test("Prueba abb la cantidad de elementos es 5", abb_cantidad(abb) == 5);
    abb_in_order(abb, imprimir, NULL);
    abb_destruir(abb);
    print_test("El árbol fue destruido", true);
}


void pruebas_abb(){
    pruebas_abb_borrar_nodo_con_dos_hijos();
	pruebas_crear_abb_vacio();
	pruebas_abb_guardar();
    //pruebas_abb_volumen();
    pruebas_iter_externo_vacio();
    pruebas_iter_externo_elementos();
    pruebas_iter_externo_clave_vacia();
    pruebas_iter_solo_hijos_izquierdos();
    pruebas_iter_solo_hijos_derechos();
    pruebas_iter_externo_volumen();
    pruebas_iter_interno();
}

int main(){
	pruebas_abb();
	return 0;
}