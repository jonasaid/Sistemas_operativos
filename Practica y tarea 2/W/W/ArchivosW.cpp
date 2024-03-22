#include<stdio.h>
#include<stdlib.h>
#include<windows.h>
#include<time.h>
#include<string.h>
#include<iostream>
using namespace std;

HANDLE creaA(char* ,HANDLE, int);
int llenar(HANDLE,int);

int main(int argc, char const *argv[])
{
	srand(time(NULL));
	HANDLE hfile=NULL;

	int i,nArchivos;
	nArchivos=rand()%10+1;
	char dir[30];
	printf("\nDirectorio donde se crearan los archivos: ");
	scanf("%s", dir);

		for (i = 0; i < nArchivos; ++i)
		{
			llenar(creaA(dir,hfile,i),i);
			CloseHandle(hfile);
		}
		system("pause");

	return 0;
}

HANDLE creaA(char* dir, HANDLE hfile, int i){

	char nombreA[15];
	char dirC[50];
	sprintf(nombreA,"Archivo%d.txt", i+1);
	sprintf(dirC,"%s\\Archivo%d.txt", dir+1);

	hfile= CreateFile(dirC,GENERIC_WRITE,0,NULL,CREATE_ALWAYS,FILE_ATTRIBUTE_NORMAL,NULL);

	if(hfile == INVALID_HANDLE_VALUE){
		printf("\nERROR");
		return 0;
	}else{
		printf("\nCreado%s\n", nombreA);
		return hfile;
	}
}

int llenar (HANDLE hfile, int i){
	if(hfile == INVALID_HANDLE_VALUE)
		printf("\nERROR");
	string contenido[200]={"H","A","P","S"};

	DWORD nToWrite=strlen(contenido[i]);
	DWORD nWriten=0;

		WriteFile(hfile,(void*)contenido[i],nToWrite,&nWriten,NULL);

		if(nToWrite == nWriten)
			printf("\nEscritura exitosa\n");
		else if(nWriten>0)
			printf("\nEscritura Parcial\n");
		else
			printf("\nError\n");
		return 0;
}
