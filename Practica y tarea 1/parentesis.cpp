#include<stdio.h>
#include<stdlib.h>
//#include<conio.h>
#include<string.h>

struct nodo{

	char simbolo;							//Informacion del nodo
	struct nodo *sig;	
};

struct nodo *raiz=NULL;

void insertar (char x){										//Lega el caracter (){}[]
	struct nodo *nuevo;
	nuevo = (struct nodo*) malloc(sizeof(struct nodo));		//Reserva memoria
	nuevo->simbolo=x;
	if(raiz == NULL){					
		raiz=nuevo;							
		nuevo->sig=NULL;					
	}
	else{									
		nuevo->sig=raiz;					
		raiz=nuevo;							
	}
}

char extraer (){							//Funcion que extrae la informacion
	if(raiz != NULL){						//Si la raiz es diferente a nulo
		char info= raiz->simbolo;			//se crea la variable a extraer
		struct nodo *bor = raiz;			
		raiz=raiz->sig;						//raiz se le asigna el valor siguiente
		free(bor);
		return info;						//retorna informacion
	}
	else{
		return -1;
	}
}

void liberar(){								//Funcion para liberar la lista revio se cierre el programa
	struct nodo *reco =raiz;
	struct nodo  *bor;
	while(reco != NULL){
		bor=reco;
		reco=reco->sig;
		free(bor);
	}
}

int vacia(){								//Si la lista esta vacia
	if(raiz == NULL){
		return 1;
	}else{
		return 0;
	}
}

void cargar (char *formula){
	printf("\n\n\tIngrese la formula: ");
	gets(formula);
}

int verificar(char *formula){
	for(int f=0; f<strlen(formula);f++)
	{
		if(formula[f] == '(' || formula[f] == '{' || formula[f] == '['){
			insertar(formula[f]);
		}
		else{
			if(formula[f] == ')'){
				if(extraer() !='('){
					return 0;
				}
			}
			else
			{
				if(formula[f] == ']'){
					if(extraer() !='['){
					return 0;
			     	}
				}
				else{
					if(formula[f] == '}'){
					if(extraer() !='{'){
					return 0;
			     	}
				}
				
				}
			}	
		}
	}
	if(vacia()){
		return 1;
	}else{
		return 0;
	}
}

void menu(){
	
char formula[101];

//	system("cls");
//	system("color 0a");
	printf("\t\t\t----Parentesis Balanceados----");
	printf("\nEQUIPO 7");
	cargar(formula);
	if(verificar(formula)){
		printf("\n\tLa formula esta balanceada\n\n");
	}
	else{
		printf("\n\tLa formula no esta balanceada\n\n");
	}
	

	
}

main(){
	
	int opc;
	do
	{
	menu();
//	system("pause");
	}while(opc != 2);
	liberar();
	return 0;
}
