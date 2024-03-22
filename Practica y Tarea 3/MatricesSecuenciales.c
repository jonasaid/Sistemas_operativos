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

void transpuesta(int mat1[7][7], int mat2[7][7])
{
    int i, j;
    for (i = 0; i < 7; i++)
        for (j = 0; j < 7; j++)
            mat2[i][j] = mat1[j][i];
}

void imprimirMatrizChar(char** mat){
    int i, j;
    printf("\n\nMatriz: ");
    //Se imprimen los elementos de la matriz
    for(i = 0; i < 7; i++){
        printf("\n");
        for(j = 0; j < 7; j++){
            printf("%c ", mat[i][j]);
        }
    }
}

int main(){
    int mat1[7][7], mat2[7][7], matSum[7][7], matRes[7][7], matMul[7][7], matTrans[7][7];

    inicializarMatriz1(mat1);
    imprimirMatriz(mat1);

    inicializarMatriz2(mat2);
    imprimirMatriz(mat2);

    sumarMatrices(mat1,mat2,matSum);
    imprimirMatriz(matSum);
    crearArchivo("Documents/sumaDeMatrices.txt");
    escribirMatriz(matSum, "Documents/sumaDeMatrices.txt");

    restarMatrices(mat1,mat2,matRes);
    imprimirMatriz(matRes);
    crearArchivo("Documents/restaDeMatrices.txt");
    escribirMatriz(matRes, "Documents/restaDeMatrices.txt" );

    multiplicarMatrices(mat1,mat2,matMul);
    imprimirMatriz(matMul);
    crearArchivo("Documents/multDeMatrices.txt");
    escribirMatriz(matMul, "Documents/multDeMatrices.txt" );

    transpuesta(mat1,matTrans);
    imprimirMatriz(matTrans);
    crearArchivo("Documents/transDeMatrices.txt");
    escribirMatriz(matTrans, "Documents/transDeMatrices.txt" );


    return 0;
}
