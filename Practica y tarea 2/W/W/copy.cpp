#include <iostream>
#include <string>

using namespace std;

void copy_file(string ruta, string destino)
{
 FILE * archivo; 
 string cadena; 
 if (archivo = fopen(ruta.c_str(), "r"))
 {
  cadena = "copy " + ruta + " " + destino;   
  system(cadena.c_str());    
  fclose(archivo);    
 }
 else
 {
   cout << "El archivo no existe" << endl;  
 }  
}

void init()
{
  cout << "Ruta del archivo: ";
  string ruta;
  getline(cin, ruta);
  cout << "Destino: ";
  string destino;
  getline(cin, destino);
  copy_file(ruta, destino);
  init();   
}


int main(int argc, char *argv[])
{
 init();
 system("PAUSE");
 return 0;
}
