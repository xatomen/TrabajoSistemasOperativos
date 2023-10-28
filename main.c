#include <stdio.h>
#include <stdlib.h>
#include <math.h>

/*Estructura de datos*/

/*Proceso*/
struct proceso{
    int id_proceso;
    long double tamanio_proceso; /*En KiloBytes*/
    long double tiempo_ejecucion; /*En unidades de tiempo*/
    long double necesidad_marcos;
    long double marcos_asignados;
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
long double seleccionar_unidad_memoria();
long double necesidad_marco(struct proceso *Proceso, long double tamanio_marco);
int crear_proceso(struct proceso **Proceso, long double tamanio_marco);
void agregar_proceso_cola(struct proceso **Proceso, struct proceso *NuevoProceso);
void imprimir_procesos(struct proceso *Proceso);
long double tamano_memoria_fisica();
long double tamano_marco_pagina();
long double necesidad_bloques(struct proceso *Proceso);
int asignar_bloques(struct proceso *Proceso, long double cantidad_marcos);


/*Programa principal*/
int main(){
    /*Variables*/
    int opcion;
    // tabla_paginas Tabla;
    // cola_procesos Cola; /*USAR FCFS???????????????????????*/

    /*Ingresamos tamaño de la memoria física y del tamaño de los marcos*/
    printf("Memoria fisica:\n");
    long double memoria_fisica = tamano_memoria_fisica(); /*Tamaño de la memoria física*/
    printf("Tamano marco:\n");
    long double tamanio_marco = tamano_marco_pagina();
    long double cantidad_marcos = memoria_fisica/tamanio_marco;

    printf("Tamano memoria fisica: %Lf\n",memoria_fisica);
    printf("Tamano marco: %Lf\n",tamanio_marco);
    printf("Cantidad marcos: %Lf\n",cantidad_marcos);

    // Tabla->tamanio_marco = tamano_marco;

    struct proceso *ColaProcesos = NULL;

    /*Menú y ejecución del aplicativo*/
    while(opcion!=0){
        printf("Menu:\n");
        printf("1. Agregar proceso\n");
        printf("2. Imprimir procesos\n");
        printf("3. Asignar bloques\n");
        printf("0. Salir\n");
        printf("Ingrese una opcion:\n");
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

            case 3:
                asignar_bloques(&ColaProcesos,cantidad_marcos);
            break;
        }
    }
    return 0;
}

/*Función que permite seleccionar la unidad de memoria a la hora de crear un proceso*/
/*Retorna un factor que al multiplicarse por el tamaño de memoria indicado*/
/*Se podrá obtener la cantidad de memoria en bits*/
long double seleccionar_unidad_memoria(){
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
            case 5:return 8*1024*1024*1024;break;

            /*TeraBytes*/
            case 6:return 8*1024*1024*1024*1024;break;

            /*PetaBytes*/
            case 7:return 8*1024*1024*1024*1024*1024;break;
        }
    }
}

/*Función que retorna la necesidad de marcos de un */
long double necesidad_marco(struct proceso *Proceso, long double tamanio_marco){
    return ceil(Proceso->tamanio_proceso/tamanio_marco);
}

int crear_proceso(struct proceso **Proceso, long double tamanio_marco){
    struct proceso *NuevoProceso = malloc(sizeof(struct proceso));
    NuevoProceso->next = NULL;
    long double tamanio_proceso;
    long double tiempo_ejecucion;

    /*Ingresamos los datos del proceso a crear*/
    long double factor = seleccionar_unidad_memoria();  /*Cargamos el factor para transformar la memoria del proceso a bits*/
    printf("Ingrese el tamano del proceso:\n");
    scanf("%Lf",&tamanio_proceso);
    printf("Ingrese el tiempo de ejecución del proceso:\n");
    scanf("%Lf",&tiempo_ejecucion);

    /*Asignamos los datos al proceso creado*/
    NuevoProceso->id_proceso = 0;
    NuevoProceso->tamanio_proceso = tamanio_proceso * factor; /*Tamaño del proceso en bits*/
    NuevoProceso->tiempo_ejecucion = tiempo_ejecucion;
    NuevoProceso->necesidad_marcos = necesidad_marco(NuevoProceso,tamanio_marco);  /*Calculamos cuantos marcos se necesitan para el proceso*/
    NuevoProceso->marcos_asignados = 0;

    /*Insertamos el proceso a la cola de procesos*/
    agregar_proceso_cola(&(*Proceso),NuevoProceso);

    return 0;
}

void agregar_proceso_cola(struct proceso **Proceso, struct proceso *NuevoProceso){
    /*Insertamos el proceso a la cola de procesos*/
    if(*Proceso == NULL){
        *Proceso = NuevoProceso;
    }
    else{
        agregar_proceso_cola(&(*Proceso)->next,NuevoProceso);
    }
}

void imprimir_procesos(struct proceso *Proceso){
	while (Proceso != NULL){
        printf("---------------------------\n");
		printf("ID: %d\n", Proceso->id_proceso);
		printf("Tamaño: %Lf\n", Proceso->tamanio_proceso);
        printf("Tiempo de ejecucion: %Lf\n", Proceso->tiempo_ejecucion);
        printf("Necesidad de marcos: %Lf\n", Proceso->necesidad_marcos);
        printf("Marcos asignados: %Lf\n", Proceso->marcos_asignados);
        printf("---------------------------\n");
        Proceso = Proceso->next;
	}
}

long double tamano_memoria_fisica(){
    long double factor = seleccionar_unidad_memoria();
    long double tamano = 0;
    printf("Ingrese el tamano de la memoria fisica:\n");
    scanf("%Lf", &tamano);
    return tamano * factor;
}

long double tamano_marco_pagina(){
    long double factor = seleccionar_unidad_memoria();
    long double tamano = 0;
    printf("Ingrese el tamano del marco:\n");
    scanf("%Lf", &tamano);
    return tamano * factor;
}

/*VER ESTO!!!!!!!*/
long double necesidad_bloques(struct proceso *Proceso){
    printf("funcion necesidad bloques\n");
    long double necesidad = 0;
    printf("while\n");
    while (Proceso != NULL){
        printf("iteracion\n");
        necesidad = necesidad + Proceso->necesidad_marcos;
        printf("necesidad: %Lf\n",necesidad);
        printf("necesidad bloques proceso: %Lf",Proceso->necesidad_marcos);
        system("pause");
        Proceso = Proceso->next;
        
	}
    return necesidad;
}

int asignar_bloques(struct proceso *Proceso, long double cantidad_marcos){
    
    printf("declaracion\n");
    long double asignacion_proporcional;
    printf("funcion\n");
    long double total_necesidad = necesidad_bloques(Proceso);

    printf("while\n");
    while (Proceso != NULL){
        asignacion_proporcional = (Proceso->necesidad_marcos/total_necesidad)*cantidad_marcos;
        if(asignacion_proporcional<1){Proceso->necesidad_marcos = 1;}
        else{Proceso->necesidad_marcos = floor(asignacion_proporcional);}
        Proceso = Proceso->next;
	}

    /*VER LO DE LA FRAGMENTACIÓN INTERNA*/
}
