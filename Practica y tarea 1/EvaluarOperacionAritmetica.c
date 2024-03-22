#include <stdio.h>
#include <string.h> 
#include <stdlib.h> 

/*introducirExpresion, no regresa nada. 
Esta funcion pide al usuario que introduzca la expresión a evaluar*/
void introducirExpresion(char *numero){
    printf("Introduce la expresion: ");
    fgets(numero, 256, stdin);
}

/*identificarOperador, regresa un numero dependiendo de que operador sea, 
si es un parentesis regresa un -1 y si es un operando un 0*/
int identificarOperador(char operador){
    if (operador == '+'){
        return 1;
    }else if (operador == '-'){
        return 2;
    }else if (operador == '/'){
        return 3;
    }else if (operador == '*'){
        return 4;
    }else if (operador == '(' || operador == ')'){
        return -1;
    }else{
        return 0;
    }
}

/*ejecutarOperacion: regresa el valor de alguna operación (suma, resta, 
multiplicación y división), identificando cual es el valor del operador,
requiere 3 valores enteros*/
int ejecutarOperacion(int numero1, int numero2, int operador){
    if (operador == 1){
        return numero1+numero2;
    }else if (operador == 2){
        return numero1-numero2;
    }else if (operador == 3){
        return numero1/numero2;
    }else if (operador == 4){
        return numero1*numero2;
    }else{
        return 0;
    }
}

/*cuentaDigitos: regresa de cuantos digitos es algun numero,
para ello requiere la cadena que contiene la expresión y la posicion
a partir de la que empieza el numero*/
int cuentaDigitos(char* numero, int posicion){
    int contador = 0;

    while (identificarOperador(numero[posicion]) == 0){
        posicion++;
        contador++;                  
    }    
    return contador; 
}

/*convertirAEntero: convierte una cadena a entero, dicha cadena 
simboliza un numero y la convierte a tipo entero, para eso necesita
saber de cuantos digitos es el numero, la cadena y posicion en la que 
se encuentra el numero. Regresa el numero que convirtio*/
int convertirAEntero(int digitos, int posicion, char* numero){
    char nuevoNum[255];
    char* numeroF;
    int i;
    for (i = 0; i < digitos; i++){
        nuevoNum[i] = numero[posicion];//Aquí almacenamos solamente la cadena del numero
        posicion++;
    }

    int numeroR = atoi(nuevoNum);//esta función sirve para hacer un casting de tipo apuntador a caracter a entero 
    return numeroR;    
}

int main (){
    char numero[255];
    //Solicitamos la cadena
    introducirExpresion(numero);

    int posicionParentesisA, resultado, i;   
   
    //Se iterara hasta que se termine de recorrer toda la cadena dada.
	for(i=0; i<strlen(numero); i++){
    
        //Guardamos la posicion del ultimo parentesis de apertura (este solo es un indicador de que parte se esta evaluando de la expresión)
        if (numero[i] == '('){
            posicionParentesisA = i; 
        //Si se encuentra el parentesis de cierre:    
        }else if(numero[i] == ')'){
            int numero1, operador, numero2, digitos;

            //Si lo que esta despues de '(' es un numero, entonces:
            if (identificarOperador(numero[posicionParentesisA+1]) == 0){
                
                //Mide la longitud del numero, conviertelo a entero y cambia la posicion del 
                //parentesis de apertura a donde termina el primer numero
                digitos = cuentaDigitos(numero, posicionParentesisA+1);
                numero1 = convertirAEntero(digitos, posicionParentesisA+1, numero);
                posicionParentesisA += digitos;

                //Se sabe que despues del primer numero viene el operador, por tanto identificar
                //cual es el operador (+,-,/ o *). cambia la posicion del parentesis de apertura
                //a la posicion del operador
                digitos = cuentaDigitos(numero, posicionParentesisA+1);
                operador = identificarOperador(numero[posicionParentesisA+1]);
                posicionParentesisA++;

                //Mide la longitud del segundo numero, conviertelo a entero y cambia la posicion del 
                //parentesis de apertura a donde termina el segundo numero
                digitos = cuentaDigitos(numero, posicionParentesisA+1);
                numero2 = convertirAEntero(digitos, posicionParentesisA+1, numero);  
                posicionParentesisA += digitos;

                //Obtenidos los dos numeros de forma entera y sabiendo cual es el operador
                //se realiza la operación y se obtiene el resultado, dicho resultado, será 
                //el nuevo numero1, ya que, sabemos que este resultado tendra que operarse con 
                //algun otro numero más adelante
                resultado = ejecutarOperacion(numero1, numero2, operador);
                numero1 = resultado;

                //La posicion del parentesis de apertura se cambia a la del iterador i, sabiendo que todo
                //lo anterior ya fue evaluado.
                posicionParentesisA = i;
                

            //El caso "else" representa el instante en que se hizo la evaluación de los parentesis mas internos 
            //y seobtuvo un resultado, este resultado se guarda como el primer numero.    
            }else{

                //Se sabe que despues del primer numero viene el operador, por tanto identificar
                //cual es el operador (+,-,/ o *). cambia la posicion del parentesis de apertura
                //a la posicion del operador. 
                digitos = cuentaDigitos(numero, posicionParentesisA+1);
                operador = identificarOperador(numero[posicionParentesisA+1]);
                posicionParentesisA++;

                //Mide la longitud del segundo numero, conviertelo a entero y cambia la posicion del 
                //parentesis de apertura a donde termina el segundo numero
                digitos = cuentaDigitos(numero, posicionParentesisA+1);
                numero2 = convertirAEntero(digitos, posicionParentesisA+1, numero);  
                posicionParentesisA += digitos; 

                //Obtenidos los dos numeros de forma entera y sabiendo cual es el operador
                //se realiza la operación y se obtiene el resultado, dicho resultado, será 
                //el nuevo numero1, ya que, sabemos que este resultado tendra que operarse con 
                //algun otro numero más adelante
                resultado = ejecutarOperacion(numero1, numero2, operador);       
                numero1 = resultado;
                
                //La posicion del parentesis de apertura se cambia a la del iterador i, sabiendo que todo
                //lo anterior ya fue evaluado.
                posicionParentesisA = i;
                
            }        
        }
    }

    //Se imprime el resultado
    printf("%d", resultado);
    return 0;
}

