#include <stdio.h>
#include <string.h>
#include <dirent.h>
#include<fcntl.h>
#include <errno.h>
#include <sys/stat.h>
#include<stdlib.h>
#include<unistd.h>
#include <time.h>
#include<unistd.h>
#include <time.h>
#define FILAS 7
#define COLUMNAS 7
#include <sys/types.h>
#include<unistd.h>
#include <time.h>
#include <pthread.h>


struct argumentos{
    int mat1[7][7];
    int mat2[7][7];
    int matR[7][7];
    char* direccion;
};


/*recibirDireccion regresa una cadena, esta cadena es la direccion con la
que trabajará cada uno de las demás funciones*/

void crearArchivo(char* direccion){

    int fd1 = open(direccion, O_CREAT | O_WRONLY, 0666);

    close(fd1);//Cerramos el archivo
}

/*crearArchivos no regresa nada, lo que hace es crear un numero aleatorio de archivos .txt  con
contenido, recibe la direccion donde se crean los archivos (esta direccion ya tiene que estar creada)
y un iterador que ayudará a dar nombre a los archivos y colocar el contenido a los archivos*/

void escribirMatriz(int mat[7][7], char* direccion){
    //Contenido posible de los archivos
    int fd1 = open(direccion, O_WRONLY | O_APPEND, 0666);//funcion que ejecuta el comando open en la terminal, las banderas son que se crea o se escribe y lee el archivo
    int i, j;
    char*** texto = (char***)malloc(7*sizeof(char**));

    for(i = 0; i < 7; i++){
        texto[i] = (char**)malloc(7*sizeof(char*));
        for(j = 0; j < 7; j++){
            texto[i][j]= (char*)malloc(5*sizeof(char));
            sprintf(texto[i][j],"%d \t", mat[i][j]);

            write(fd1,texto[i][j], strlen(texto[i][j]));
        }
         write(fd1,"\n", 1);
    }

    close(fd1);//Cerramos el archivo
}

void* leerImprimirArchivo(void* args){
    char* contenido = (char*)malloc(1000*sizeof(char));//Esta variable guardara el contenido que tiene un archivo
    struct argumentos* arg = (struct argumentos*)args;
    int fd1 = open(arg->direccion, O_RDONLY);//Abrimos el archivo
    if(fd1 < 0){//Si la funcion regresa un -1 significa que no encontro nada en la direccion
        printf("El archivo no existe");
    }else{
        read(fd1, contenido, 1000);//Se toma el contenido que tenga el archivo abierto y se guarda
        printf("%s \n", contenido);//Lo imprimimos en pantalla
        //Se cierran los archivos
        close(fd1);
    }
}

/*inicializarMatriz1 no regresa nada, rellena la matriz del 1 al 7 en cada renglon*/
void inicializarMatriz1(int mat1[FILAS][COLUMNAS]){
    int i, j;
    int numeros[7] = {1,2,3,4,5,6,7};
    //Se llena la matriz 1 con valores del 1 al 7
    for(i = 0; i < 7; i++){
        for(j = 0; j < 7; j++){
            mat1[i][j] = numeros[j];
        }
    }
}

/*inicializarMatriz1 no regresa nada, rellena la matriz del 7 al 1 en cada renglon*/
void inicializarMatriz2(int mat2[FILAS][COLUMNAS]){
    int i, j;
    int numeros[7] = {1,2,3,4,5,6,7};
    //Se llena la matriz 2 con valores del 7 al 1
    for(i = 0; i < 7; i++){
        int k=6;
        for(j = 0; j < 7; j++){
            mat2[i][j] = numeros[k];
            k--;
        }
    }
}

/*sumarMatrices no regresa nada, suma la matriz pasada como primer parametro, con el
segundo parametro y guarda el resultado en el tercer parametro*/
void sumarMatrices(int mat1[7][7], int mat2[7][7], int mat3[7][7]){
    int i, j;
    //Se suman los elementos de las matrices
    for(i = 0; i < 7; i++){
        for(j = 0; j < 7; j++){
            mat3[i][j] = mat1[i][j] + mat2[i][j];
        }
    }
}

/*restarMatrices no regresa nada, resta la matriz pasada como primer parametro, con el
segundo parametro y guarda el resultado en el tercer parametro*/
void restarMatrices(int mat1[7][7], int mat2[7][7], int mat3[7][7]){
    int i, j;
    //Se restan los elementos de las matrices
    for(i = 0; i < 7; i++){
        for(j = 0; j < 7; j++){
            mat3[i][j] = mat1[i][j] - mat2[i][j];
        }
    }
}

/*multiplicarMatrices no regresa nada, multiplica la matriz pasada como primer parametro, con el
segundo parametro y guarda el resultado en el tercer parametro*/
void multiplicarMatrices(int mat1[7][7], int mat2[7][7], int mat3[7][7]){
    int c,d,k, sum=0;
    //Se multiplican los elementos de las matrices
    for (c = 0; c < 7; c++){
        for (d = 0; d < 7; d++){
            for (k = 0; k < 7; k++){
                sum = sum + mat1[c][k]*mat2[k][d];
            }
            mat3[c][d] = sum;
            sum = 0;
        }
    }
}


/*imprimirMatriz no regresa nada, pero imprime todos los renglones y columnas*/
void imprimirMatriz(int mat[7][7]){
    int i, j;
    printf("\n\nMatriz: ");
    //Se imprimen los elementos de la matriz
    for(i = 0; i < 7; i++){
        printf("\n");
        for(j = 0; j < 7; j++){
            printf("%d ", mat[i][j]);
        }
    }
}

//transpuesta, recibe dos matrices, lo que hace es la transpuesta del primer parametro lo coloca en el segundo
void transpuesta(int mat1[7][7], int mat2[7][7])
{
    int i, j;
    for (i = 0; i < 7; i++)
        for (j = 0; j < 7; j++)
            mat2[i][j] = mat1[j][i];
}

/*procesoSumarMatriz, permite pasarla como parametro en pthread_create
Realiza la operacion de suma entre matrices ademas de escribir el resultado de la
sumar en un archivo*/
void* procesoSumarMatriz(void* args){
    //Se hace un casting para usar la estructura
    struct argumentos* arg = (struct argumentos*) args;
    sumarMatrices(arg->mat1,arg->mat2,arg->matR);
    //Se guarda la direccion del archivo en una variable de la esctructura
    arg->direccion = "Documents/sumaDeMatrices.txt";
    crearArchivo("Documents/sumaDeMatrices.txt");
    escribirMatriz(arg->matR, "Documents/sumaDeMatrices.txt");
    //leerImprimirArchivo("Documents/sumaDeMatrices.txt");
}


/*procesoRestarMatriz, permite pasarla como parametro en pthread_create
Realiza la operacion de resta entre matrices ademas de escribir el resultado de la
resta en un archivo*/
void* procesoRestarMatriz(void* args){
    //Se hace un casting para usar la estructura
    struct argumentos* arg = (struct argumentos*) args;
    restarMatrices(arg->mat1,arg->mat2,arg->matR);
    //Se guarda la direccion del archivo en una variable de la esctructura
    arg->direccion = "Documents/restaDeMatrices.txt";
    crearArchivo("Documents/restaDeMatrices.txt");
    escribirMatriz(arg->matR, "Documents/restaDeMatrices.txt" );
    //leerImprimirArchivo("Documents/restaDeMatrices.txt" );
}


/*procesoMultiplicarMatriz, permite pasarla como parametro en pthread_create
Realiza la operacion de multiplicar matrices ademas de escribir el resultado de la
multiplicacion en un archivo*/
void* procesoMultiplicarMatriz(void* args){
    //Se hace un casting para usar la estructura
    struct argumentos* arg = (struct argumentos*) args;
    multiplicarMatrices(arg->mat1,arg->mat2,arg->matR);
    //Se guarda la direccion del archivo en una variable de la esctructura
    arg->direccion = "Documents/multDeMatrices.txt";
    crearArchivo("Documents/multDeMatrices.txt");
    escribirMatriz(arg->matR, "Documents/multDeMatrices.txt" );
    //leerImprimirArchivo("Documents/multDeMatrices.txt" );
}

/*procesoTranspuestaMatriz, permite pasarla como parametro en pthread_create
Realiza la operacion de transpuesta de una matriz, ademas de escribir el resultado de la
la transpuesta en un archivo*/
void* procesoTranspuestaMatriz(void* args){
    //Se hace un casting para usar la estructura
    struct argumentos* arg = (struct argumentos*) args;
    transpuesta(arg->mat1,arg->matR);
    //Se guarda la direccion del archivo en una variable de la esctructura
    arg->direccion = "Documents/transDeMatrices.txt";
    crearArchivo("Documents/transDeMatrices.txt");
    escribirMatriz(arg->matR, "Documents/transDeMatrices.txt" );
    //leerImprimirArchivo("Documents/transDeMatrices.txt");
}


int main(){
    struct argumentos args[5];
    pthread_t proceso[5];

    //Asignandole valores a diferentes matrices
    for(int i=0; i<5; i++){
        inicializarMatriz1(args[i].mat1);
        //imprimirMatriz(args[i].mat1);

        inicializarMatriz2(args[i].mat2);
        //imprimirMatriz(args[i].mat2);
    }



    //Creacion de hilos
    pthread_create(&proceso[0], NULL, procesoSumarMatriz,&args[0]);
    pthread_create(&proceso[1], NULL, procesoRestarMatriz,&args[1]);
    pthread_create(&proceso[2], NULL, procesoMultiplicarMatriz,&args[2]);
    pthread_create(&proceso[3], NULL, procesoTranspuestaMatriz,&args[3]);

    //Union de los hilos
    pthread_join(proceso[0], NULL);
    pthread_join(proceso[1], NULL);
    pthread_join(proceso[2], NULL);
    pthread_join(proceso[3], NULL);

    //Con un solo hilo pero con un for, se lee y se imprime el contenido de los archivos creados
    for(int i=0; i<4; i++){
        pthread_create(&proceso[4], NULL, leerImprimirArchivo,&args[i]);
    }
    pthread_join(proceso[4], NULL);


    return 0;
}
