#include <stdio.h>
#include <stdlib.h>
#include <math.h>

/*Estructura de datos*/

/*Proceso*/
typedef struct{
    int id_proceso;
    int tamanio_proceso; /*En KiloBytes*/
    float tiempo_ejecucion; /*En unidades de tiempo*/
    int necesidad_marcos;
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
int crear_proceso(proceso Proceso, marco_pagina Marco);

/*Programa principal*/
int main(){
    /*Variables*/
    int opcion = 0;
    tabla_paginas Tabla;
    cola_procesos Cola; /*USAR FCFS???????????????????????*/

    int memoria_fisica = tamano_memoria_fisica(); /*Tamaño de la memoria física*/
    int tamano_marco = 8*1024; /*1KB*/
    


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

/*Función que permite seleccionar la unidad de memoria a la hora de crear un proceso*/
/*Retorna un factor que al multiplicarse por el tamaño de memoria indicado*/
/*Se podrá obtener la cantidad de memoria en bits*/
int seleccionar_unidad_memoria(){
    int opcion = 0;
    L1:
    printf("Seleccione la unidad de memoria:");
    printf("1. Bits\n");
    printf("2. Bytes\n");
    printf("3. KiloBytes\n");
    printf("4. MegaBytes\n");
    printf("5. GigaBytes\n");
    printf("6. TeraBytes\n");
    printf("7. PetaBytes\n");
    scanf("%d",&opcion);
    if(opcion>7 || opcion<1){goto L1;}
    else{
        /*Debemos transformar, la unidad definida, a bits*/
        switch(opcion){
            /*Bits*/
            case 1:
                return 1;
            break;

            /*Bytes*/
            case 2:
                return 8;
            break;

            /*KiloBytes*/
            case 3:
                return 8*1024;
            break;

            /*MegaBytes*/
            case 4:
                return 8*1024*1024;
            break;

            /*GigaBytes*/
            case 5:
                return 8*1024*1024*1024;
            break;

            /*TeraBytes*/
            case 6:
                return 8*1024*1024*1024*1024;
            break;

            /*PetaBytes*/
            case 7:
                return 8*1024*1024*1024*1024*1024;
            break;
        }
    }
    return 0;
}

/*Función que retorna la necesidad de marcos de un */
int necesidad_marco(marco_pagina Marco, proceso Proceso){
    return ceil(Proceso.tamanio_proceso/Marco.tamanio_marco);
}

int crear_proceso(proceso Proceso, marco_pagina Marco){
    proceso Proceso;
    int tamanio;
    float tiempo_ejecucion;

    /*Ingresamos los datos del proceso a crear*/
    printf("Ingrese el tamaño del proceso:\n");
    scanf("%d",&tamanio);
    printf("Ingrese el tiempo de ejecución del proceso:\n");
    scanf("%d",&tiempo_ejecucion);

    /*Asignamos los datos al proceso creado*/
    Proceso.id_proceso = 0;
    int factor = seleccionar_unidad_memoria();  /*Cargamos el factor para transformar la memoria del proceso a bits*/
    Proceso.tamanio_proceso = tamanio * factor; /*Tamaño del proceso en bits*/
    Proceso.tiempo_ejecucion = tiempo_ejecucion;
    Proceso.necesidad_marcos = necesidad_marco(Marco,Proceso);  /*Calculamos cuantos marcos se necesitan para el proceso*/
    
    /*Insertamos el proceso a la cola de procesos*/
    /*-----------------------------*/
    /*-----------------------------*/
    /*-----------------------------*/

    return 0;
}

int tamano_memoria_fisica(){
    int factor = seleccionar_unidad_memoria();
    int tamano = 0;
    printf("Ingrese el tamaño del marco:\n");
    scanf("%d", &tamano);
    return tamano * factor;
}

int asignar_marcos(proceso Proceso, int tamanio_pagina, tabla_paginas Tabla){
    int cantidad_marcos = floor(Proceso.tamanio_proceso / tamanio_pagina);
    for(int i=0; i<cantidad_marcos; i++){
        Tabla[i].id_proceso_asignado = Proceso.id_proceso;
    }
    /*VER LO DE LA FRAGMENTACIÓN INTERNA*/
}
