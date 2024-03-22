#include <stdio.h>
#include <sys/stat.h>
#include<unistd.h>
#include <sys/types.h>
#include <pthread.h>
#include <stdlib.h>


//funcion que imprime el identificador de el hilo
void* idHilo(void* p) {
    printf("El identificador del hilo es= %ld\n", pthread_self());
    pthread_exit(NULL);
    return NULL;
}

//imprime el mensaje de Practica 2
void* imprimirMensaje(void* mensaje){
    char* cadena = (char*) mensaje;
    printf("%s \n", cadena);
    return NULL;
}

int main(){
    pthread_t hilo[15];

    int identificador = fork();
    // creacion de un proceso por copia exacta
    if(identificador == 0){
        //imprimir el id del proceso
        printf("El identificador del proceso hijo es= %d\n", identificador);
        //creacion de los hilos
        for(int i=0; i<15; i++){
            pthread_create(&hilo[i], NULL, idHilo, NULL);

            for(int j=0; j<10; j++){
                pthread_create(&hilo[j], NULL, idHilo, NULL);

                //creacion de los hilos terminales
                for(int k=0; k<5; k++){
                    pthread_create(&hilo[k], NULL, imprimirMensaje, "Practica 2");
                }
            }
        }
        // esperar la terminación de los hilos.
        for(int i=0; i<15; i++){
            pthread_join(hilo[i], NULL);
            for(int j=0; j<10; j++){
                    pthread_join(hilo[j], NULL);
                    for(int k=0; k<5; k++){
                        pthread_join(hilo[k], NULL);
                    }
            }
        }

        exit(0);
    }
    return 0;
}
