#include <stdio.h>
#include <time.h>
#include <sys/stat.h>	 //llamadas a sistema
#include <unistd.h>	 //write
#include <string.h>     // Función strlen() 
#include <fcntl.h>      //función open()
#include <stdlib.h>     //write() y close() 


int main ( int argc, char* argv[] )
{
  
   int i;
   char* nombres[10];
 
   nombres[0] = calloc(100,sizeof(char));
   printf("Escriba el directorio donde se crearan los archivos:\n");
   scanf("%s",nombres[0]); 
      
    for(i=1; i<=10; i++) nombres[i]=nombres[0];
    
   char* a[10]={"1","2","3","4","5"
   		,"6","7","8","9","10"};  //nombre de archivo
    
   char* cadena[15]={"1","2","3","4","5","6",
   "7","8","9","10","11","12","13","14","15"}; //contenido del archivo

   srand(time(NULL));
   int numero_arch = rand()%10;

   printf("Se crearan %d archivos:\n", numero_arch);

    for ( i = 0; i < numero_arch; i++) 
    {
	  int contenido = rand()%15;
	  
	   strcat(nombres[i],a[i]);
	  
	   int fichero = open (nombres[i], O_CREAT|O_WRONLY,0644); 

	   if (fichero==-1){

		printf("Error al abrir fichero:");
		exit(1);
	   }
	   write(fichero, cadena[contenido], strlen(cadena[contenido]));
	   close(fichero);

   }
   return 0;

}
