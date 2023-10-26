#include <stdio.h>
#include <stdlib.h>
#include <math.h>

/*Estructura de datos*/

/*Proceso*/
typedef struct{
    int id_proceso;
    int tamanio_proceso; /*En KiloBytes*/
    float tiempo_ejecucion; /*En unidades de tiempo*/
} proceso;

/*Marco de página*/
typedef struct{
    int tamanio_marco;
    int id_proceso_asignado;
} marco_pagina;

/*Tabla de páginas*/
typedef marco_pagina tabla_paginas[2048];

typedef proceso cola_procesos[500];

/*Prototipo de funciones*/
int crear_proceso(int tamanio, float tiempo_ejecucion);

/*Programa principal*/
int main(){
    /*Variables*/
    int opcion = 0;
    tabla_paginas Tabla;
    cola_procesos Cola; /*USAR FCFS???????????????????????*/

    /*Menú y ejecución del aplicativo*/
    while(opcion!=0){
        printf("Menú:\n");
        printf("1. Agregar proceso\n");
        printf("0. Salir\n");
        printf("Ingrese una opción:\n");
        scanf("%d",&opcion);
        switch(opcion){
            case 0:
            break;

            case 1:
            break;
        }
    }
    return 0;
}

int crear_proceso(int tamanio, float tiempo_ejecucion){
    proceso Proceso;
    Proceso.id_proceso = 0;
    Proceso.tamanio_proceso = tamanio;
    Proceso.tiempo_ejecucion = tiempo_ejecucion;
    return 0;
}

int asignar_marcos(proceso Proceso, int tamanio_pagina, tabla_paginas Tabla){
    int cantidad_marcos = ceil(Proceso.tamanio_proceso / tamanio_pagina);
    for(int i=0; i<cantidad_marcos; i++){
        Tabla[i].id_proceso_asignado = Proceso.id_proceso;
    }
    /*VER LO DE LA FRAGMENTACIÓN INTERNA*/
}
