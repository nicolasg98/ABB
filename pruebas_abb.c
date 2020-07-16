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
    printf("DESTRUIDO\n");
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

    //abb_destruir(abb);
    //va a dar errores de memoria pero es porque no funciona el destruir
}

void pruebas_abb(){
	pruebas_crear_abb_vacio();
	pruebas_abb_guardar();	
}

int main(){
	pruebas_abb();
	return 0;
}