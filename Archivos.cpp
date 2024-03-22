#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<sys/stat.h>
#include<unistd.h>
#include<string.h>
#include<fcntl.h>

int main(){
	
	int i, numA, conte, fichero;
	char*name[10];
	name[0] = calloc(100,sizeof(char));
	printf("Escriba la direccion dende se crearan los archivos: ");
	scanf("%s", name[0]);
	
		for(i=1; i<=10; i++)
			name[i]=name[0];
	
	char*n[10] ={"1","2","3","4","5","6","7","8","9","10"};
	
	char*cont[15] ={"1","2","3","4","5","6","7","8","9","10","11","12","13","14","15"};
	
	srand(time(NULL));
    numA = rand()%10;
	
	for(i=0; i<numA; i++){
		
		conte=rand()%15;
		strcat(name[i], n[i]);	
		
		fichero = open(name[i], O_CREAT|O_WRONLY,0644);
			if(fichero == -1){
				printf("Error");
				exit(1);
			}
			write(fichero, cont[conte], strlen(cont[conte]));
			close(fichero);
	}
	
	return 0;
}

