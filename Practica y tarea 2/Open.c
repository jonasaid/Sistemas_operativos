#include<stdio.h>
#include <string.h>
#include <dirent.h>
#include<fcntl.h>
#include <errno.h>
#include <sys/stat.h>
#include<stdlib.h>
#include<unistd.h>
#include <time.h>

/*numAleatorio regresa un numero aleatorio entre 1 y 9*/
int numAleatorio(){
    int numero;
    numero = 1+(rand() % 10);
    return numero;
}

/*recibirDireccion regresa una cadena, esta cadena es la direccion con la
que trabajará cada uno de las demás funciones*/
char* recibirDireccion(){
    char* direccion = (char*)malloc(200*sizeof(char));

    printf("Escribe la direccion: ");
    scanf("%s", direccion);

    return direccion;
}


/*crearArchivos no regresa nada, lo que hace es crear un numero aleatorio de archivos .txt  con
contenido, recibe la direccion donde se crean los archivos (esta direccion ya tiene que estar creada)
y un iterador que ayudará a dar nombre a los archivos y colocar el contenido a los archivos*/
void crearArchivos(char* direccion, int iterador){
    char** cadenas = (char *[]){"HOLA","ESTO","Es","UN","EJEMPLO","DE","LLAMADAS","AL","SISTEMA","."}; //Contenido posible de los archivos
    char* reset = (char*)malloc(200*sizeof(char));//Variable auxiliar donde almacenmos la dirección
    char* numero = (char*)malloc(6*sizeof(char));//cadena donde se guarda "iterador.txt", donde iterador es mayor o igual a 0 y menor que 10

    strcpy(reset, direccion);//Copiamos la direccion original en la variable auxilair
    sprintf(numero, "%d.txt", iterador);//Guardamos el nombre del archivo, este va a depender del valor del iterador
    strcat(reset, numero);//Concatenamos el valor de la variable auxiliar con el nombre del archivo

    //reset ahora tiene la direccion completa de donde se creara el archivo y como se llama, ejemplo: "Documents/0.txt"

    int fd1 = open(reset, O_CREAT | O_WRONLY, 0666);//funcion que ejecuta el comando open en la terminal, las banderas son que se crea o se escribe y lee el archivo

    write(fd1,cadenas[iterador], strlen(cadenas[iterador]));//Dentro de este archivo ponemos el contenido

    close(fd1);//Cerramos el archivo
}

/*copiarArchivos no regresa nada, el usuario indica los archivos que quiere copiar (colocando la diraccion de estos), a otra direcceeción
(igualmente indicada por el usuario). Esta funcion recibe como parametro una cadena que es la direccion donde estan los archivos que se van
a copiar. */
/*NOTA: Cuando se piden los archivos se colocan todos en una fila, el programa sabra cuantos archivos diferentes son por los espacios colocados,
ejemplo: "9.txt 0.txt 5.txt 2.txt" */
void copiarArchivos(char* direccion){
    char* nuevaDireccion = (char*)malloc(200*sizeof(char));//direccion de donde se copiaran los archivos
    char* lsArchivos = (char*)malloc(200*sizeof(char));//lista de archivos que se van a copiar
    char** archivos = (char**)malloc(sizeof(char*)*10);//una matriz que va a guardar los archivos por separado

    printf("Que archivos quieres copiar? \n");
    printf("Coloca los archivos separandolo solo por un espacio. Ejemplo: 9.txt 0.txt 5.txt 2.txt \n");
    scanf(" %[^\n]", lsArchivos);//Este formato de especificacion me indica que al leer la cadena no la corte al leer un espacio

    int contadorLetra=0;
    int contadorArch=0;
    archivos[0] = (char*)malloc(6*sizeof(char));

    for(int i=0; i<strlen(lsArchivos); i++){

        archivos[contadorArch][contadorLetra] = lsArchivos[i];//Guardando los caracteres que hacen parte del nombre del archivo
        contadorLetra++;
        if(lsArchivos[i+1] == ' '){//Si se encuentra un espacio
            i++;
            contadorArch++;//Se cambia la fila de la matriz pq se va a guardar un nuevo archivo
            archivos[contadorArch] = (char*)malloc(6*sizeof(char));
            contadorLetra = 0;
        }
    }


    printf("Donde deseas copiar estos archivos \n");
    scanf("%s", nuevaDireccion);//La direccion donde se van a copiar

    for(int i=0; i<contadorArch+1; i++){

        char* reset = (char*)malloc(100*sizeof(char));//la variable auxiliar

        strcpy(reset, direccion);//se guarda la direccion en la variable auxiliar
        strcat(reset, archivos[i]);//se concatena la direccion con el archivo
        char* contenido = (char*)malloc(50*sizeof(char));//Esta variable guardara el contenido que tiene un archivo
        int fd1 = open(reset, O_RDONLY);//Abrimos el archivo
        if(fd1 < 0){//Si la funcion regresa un -1 significa que no encontro nada en la direccion
            printf("El archivo no existe");
        }else{
            read(fd1, contenido, 50);//Se toma el contenido que tenga el archivo abierto y se guarda
            printf("%s \n", contenido);//Lo imprimimos en pantalla

            strcpy(reset, nuevaDireccion);//En la variable auxiliar se guarda la nueva direccion
            strcat(reset, archivos[i]);//Se concatena la nueva direccion y el archivo que se va a copiar

            //Se copia el archivo en la nueva direccion
            int fd2 = open(reset, O_CREAT | O_WRONLY, 0666);
            write(fd2,contenido, 50);

            //Se cierran los archivos
            close(fd1);
            close(fd2);
        }
    }

}

/*cambiarPermisos no regresa nada, pero recibe la direccion del archivo al que se le quieren cambiar los permisos*/
void cambiarPermisos (char* direccion){
    int* permisos = (int*)malloc(4*sizeof(int));
    printf("Escribe los numeros necesarios para cambiar los permisos del archivo, por ejemplo 777: ");
    scanf("%o", permisos);//se leen los permisos, este formato de especificación es para leer numeros en base 8 (octal)
    chmod (direccion, *permisos);//Esto ejecuta en la terminal el comando chmod con la direccion y los permisos dados por el usuario
}

/*mostrarDetalles no regresa nada, recibe la direccion de la cual se quieren mostrar los detalles, nombre de archivos, tamaño y fecha*/
void mostrarDetalles(char* direccion){
    DIR *dir;// tipo de datos de los objetos de flujo de directorio.
    struct dirent *sd; //estructura que es necesaria para acceder al nombre del archivo, viene dentro de la descripcion de readdir
    struct stat fileinfo; //estructura que es necesaria para acceder a la fecha, hora  y tamaño del archivo

    dir = opendir(direccion);//Guardamos el flujo del directorio

    if(dir == NULL){//Si no tiene nada, salir de la funcion de inmediato
        printf("No se puede abrir el directorio");
        exit(1);
    }

    while( (sd = readdir(dir)) !=  NULL){//Mientras el flujo sea distinto de nulo se mostraran los detalles

              printf("Nombre del archivo: %s, ",sd->d_name);//Muestra el nombre
              printf("Tamaño del archivo: %ld bytes, ",fileinfo.st_size);//Muestra el tamaño
              printf("Hora y fecha de acceso: %s.\n",ctime(&fileinfo.st_atime));//Muestra fecha y hora
    }
    closedir(dir);//Cerrar el flujo del archivo
}

void menu(){
    printf("1.Crear un numero aleatorio archivos con contenido \n");
    printf("2.Cambiar los permisos de un archivo \n");
    printf("3.Mostrar los detalles de un archivo \n");
    printf("4.Copiar archivos en un directorio distinto especificado \n");
    printf("5. Salir \n");
    printf("Elije una opcion:");
}

int main(){
    char* direccion = (char*)malloc(200*sizeof(char));

    int opcion;
    do{
        menu();
        scanf("%d", &opcion);
     switch (opcion)
     {
          case 1:
            printf("Da la direccion del directorio donde quieras que se creen los archivos \n");
            printf("Ejemplo: Documents/ \n");
            direccion = recibirDireccion();
            srand(time(NULL));
            int num = numAleatorio();

            for(int i = 0; i< num; i++){
                crearArchivos(direccion, i);
            }
             break;
          case 2:
            printf("Da la direccion del archivo al cual quieras cambiar los permisos\n");
            printf("Ejemplo: Documents/0.txt \n");
            direccion = recibirDireccion();
            cambiarPermisos(direccion);
             break;
          case 3:
            printf("Da la direccion del directorio del cual quieras saber los detalles \n");
            printf("Ejemplo: Documents/ \n");
            direccion = recibirDireccion();
            mostrarDetalles(direccion);
            printf("Estos fueron los detalles \n");
             break;
          case 4:
             printf("Da la direccion del directorio del cual estan los archivos que quieras copiar \n");
             direccion = recibirDireccion();
             copiarArchivos(direccion);
             break;
         case 5:
             printf("Adios \n");
             break;
          default:
             printf("\nNo has seleccionado una opcion valida, intenta de nuevo \n");
         }
    }while(opcion != 5);

    exit(0);
}
