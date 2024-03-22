#include <iostream>
#include <string>

using namespace std;

void copy_file(string ruta, string destino){		//funcion oara copiar archivos

	FILE * archivo;									//Puntero que apunte a un archivo
	string cadena;
	if(archivo = fopen(ruta.c_str(), "r")) 			//Comprobar si existe el archivo
	{
		cadena = "copy" + ruta + " " + destino;		//Esto para incluir el comando, ruta, un espacio, el destino donde se copiara
		system(cadena.c_str());						//ejecutar el comando
	}else{
		cout<<"El archivo no existe";
	}
}
void init(){

	cout<<endl<<"Ruta del archivo que se quiere copiar: "<<endl;
	string ruta;
	getline(cin,ruta);
	cout<<"Destino: ";
	string destino;
	getline(cin,destino);
	copy_file(ruta,destino);
	init();
}

int main(int argc, char const *argv[])
{
	init();
	return 0;
}



