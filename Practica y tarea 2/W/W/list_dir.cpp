#include<iostream>
#include<dirent.h>
#include<string>

using namespace std;

void list_dir(string dir){				      //Funcion para listar

	DIR * directorio;					      //puntero que apunte a un objeto DIR
	struct dirent * elemento;			      //con esta estructura nos permitira entrar en los datos
	string elem;						      //guardaremos el archivo o carpeta
	if (directorio = opendir(dir.c_str()))    //Si se puede abrir el directorio
	{
		while(elemento = readdir(directorio)) //Leera 1 a 1 los elementos con el directorio abierto en el momento
		{
			elem= elemento->d_name;			  //
			cout<<elem<<endl;				  //
		}
	}
	closedir(directorio);
}

void init(){

	cout<<"Ingrese la ruta del directorio: ";
	string dir;
	getline(cin,dir);
	list_dir(dir);
	init();

}

int main(int argc, char const *argv[])
{

	init();
	system("pause");
	return 0;
}
