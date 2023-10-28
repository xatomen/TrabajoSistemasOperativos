#include <stdio.h>
#include <stdlib.h>
#include <math.h>

/*Estructura de datos*/

/*Proceso*/
struct proceso{
    int id_proceso;
    int tamanio_proceso; /*En KiloBytes*/
    float tiempo_ejecucion; /*En unidades de tiempo*/
    int necesidad_marcos;
    struct proceso *next;
};

/*Marco de página*/
typedef struct{
    int tamanio_marco;
    int id_proceso_asignado;
} marco_pagina;

/*Tabla de páginas*/
typedef marco_pagina tabla_paginas[2048];

// typedef proceso cola_procesos[500];

/*Prototipo de funciones*/
int seleccionar_unidad_memoria();
int necesidad_marco(struct proceso *Proceso, int tamanio_marco);
int crear_proceso(struct proceso **Proceso, int tamanio_marco);
void imprimir_procesos(struct proceso *Proceso);
int tamano_memoria_fisica();

/*Programa principal*/
int main(){
    /*Variables*/
    int opcion;
    // tabla_paginas Tabla;
    // cola_procesos Cola; /*USAR FCFS???????????????????????*/

    /*Ingresamos tamaño de la memoria física y del tamaño de los marcos*/
    // int memoria_fisica = tamano_memoria_fisica(); /*Tamaño de la memoria física*/
    int tamanio_marco = 8*1024; /*1KB*/

    // Tabla->tamanio_marco = tamano_marco;

    struct proceso *ColaProcesos = NULL;

    /*Menú y ejecución del aplicativo*/
    while(opcion!=0){
        printf("Menú:\n");
        printf("1. Agregar proceso\n");
        printf("2. Imprimir procesos\n");
        printf("0. Salir\n");
        printf("Ingrese una opción:\n");
        scanf("%d",&opcion);
        switch(opcion){
            case 0:
            break;

            case 1:
                crear_proceso(&ColaProcesos,tamanio_marco);
            break;

            case 2:
                imprimir_procesos(ColaProcesos);
            break;
        }
    }
    return 0;
}

/*Función que permite seleccionar la unidad de memoria a la hora de crear un proceso*/
/*Retorna un factor que al multiplicarse por el tamaño de memoria indicado*/
/*Se podrá obtener la cantidad de memoria en bits*/
int seleccionar_unidad_memoria(){
    int opcion = 0;
    L1:
    printf("Seleccione la unidad de memoria:\n");
    printf("1. Bits\n");
    printf("2. Bytes\n");
    printf("3. KiloBytes\n");
    printf("4. MegaBytes\n");
    printf("5. GigaBytes\n");
    printf("6. TeraBytes\n");
    printf("7. PetaBytes\n");
    scanf("%d",&opcion);
    if(opcion>7 || opcion<1){printf("Intentelo nuevamente\n");goto L1;}
    else{
        /*Debemos transformar, la unidad definida, a bits*/
        switch(opcion){
            /*Bits*/
            case 1:return 1;break;

            /*Bytes*/
            case 2:return 8;break;

            /*KiloBytes*/
            case 3:return 8*1024;break;

            /*MegaBytes*/
            case 4:return 8*1024*1024;break;

            /*GigaBytes*/
            // case 5:return 8*1024*1024*1024;break;

            /*TeraBytes*/
            // case 6:return 8*1024*1024*1024*1024;break;

            /*PetaBytes*/
            // case 7:return 8*1024*1024*1024*1024*1024;break;
        }
    }
    return 0;
}

/*Función que retorna la necesidad de marcos de un */
int necesidad_marco(struct proceso *Proceso, int tamanio_marco){
    return ceil(Proceso->tamanio_proceso/tamanio_marco);
}

int crear_proceso(struct proceso **Proceso, int tamanio_marco){
    struct proceso *NuevoProceso = malloc(sizeof(struct proceso));
    NuevoProceso->next = NULL;
    int tamanio_proceso;
    float tiempo_ejecucion;

    /*Ingresamos los datos del proceso a crear*/
    int factor = seleccionar_unidad_memoria();  /*Cargamos el factor para transformar la memoria del proceso a bits*/
    printf("Ingrese el tamaño del proceso:\n");
    scanf("%d",&tamanio_proceso);
    printf("Ingrese el tiempo de ejecución del proceso:\n");
    scanf("%f",&tiempo_ejecucion);

    /*Asignamos los datos al proceso creado*/
    NuevoProceso->id_proceso = 0;
    NuevoProceso->tamanio_proceso = tamanio_proceso * factor; /*Tamaño del proceso en bits*/
    NuevoProceso->tiempo_ejecucion = tiempo_ejecucion;
    NuevoProceso->necesidad_marcos = necesidad_marco(NuevoProceso,tamanio_marco);  /*Calculamos cuantos marcos se necesitan para el proceso*/
    
    /*Insertamos el proceso a la cola de procesos*/
    agregar_proceso_cola(&(*Proceso),NuevoProceso);
    // if(*Proceso == NULL){
    //     *Proceso = NuevoProceso;
    // }
    // else{
    //     // crear_proceso(&(*Proceso)->next,tamanio_marco);
    //     *Proceso->next = NuevoProceso;
    // }

    return 0;
}

void agregar_proceso_cola(struct proceso **Proceso, struct proceso *NuevoProceso){
    /*Insertamos el proceso a la cola de procesos*/
    if(*Proceso == NULL){
        *Proceso = NuevoProceso;
    }
    else{
        agregar_proceso_cola(&(*Proceso)->next,NuevoProceso);
        // *Proceso->next = NuevoProceso;
    }
}

void imprimir_procesos(struct proceso *Proceso)
{
	while (Proceso != NULL)
	{
        printf("---------------------------\n");
		printf("ID: %d\n", Proceso->id_proceso);
		printf("Tamaño: %d\n", Proceso->tamanio_proceso);
        printf("Tiempo de ejecución: %f\n", Proceso->tiempo_ejecucion);
        printf("Necesidad de marcos: %d\n", Proceso->necesidad_marcos);
        printf("---------------------------\n");
        Proceso = Proceso->next;
	}
}

int tamano_memoria_fisica(){
    int factor = seleccionar_unidad_memoria();
    int tamano = 0;
    printf("Ingrese el tamaño del marco:\n");
    scanf("%d", &tamano);
    return tamano * factor;
}

// int asignar_marcos(struct proceso *Proceso, int tamanio_pagina, tabla_paginas Tabla){
//     int cantidad_marcos = floor(Proceso.tamanio_proceso / tamanio_pagina);
//     for(int i=0; i<cantidad_marcos; i++){
//         Tabla[i].id_proceso_asignado = Proceso.id_proceso;
//     }
//     /*VER LO DE LA FRAGMENTACIÓN INTERNA*/
// }
