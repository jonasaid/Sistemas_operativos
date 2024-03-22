#include <stdio.h>

void rombo(int na, int ne, int ns, int ni);

void romboabajo(int na, int ne, int ns, int ni);

int main(){
	
	int n; 
	
	printf("Ingresa el numero de la diagonal\n");
	scanf("%i", &n);
	printf("%i\n\n", n);
	int n2,n3,n4;
	
	n2= n/2;
	n3= 2*n2;
	n4 = n2;
	
	rombo(n, n2, n3,1); 
	
	printf("\n");
	
	romboabajo(n, n2, 2,n2); 
	
	return 0;
}

void rombo(int na, int ne, int ns,int ni){
	
	int i,j,k,l,r,m;
	
	if(ns == 0){
		for(r = 0; r<3;r++){
			for(i = 0; i<na; i++){
				printf("*");
			}
		}
	}	
	
	else{
		for(i = 0; i< ne; i++){
		
			printf(" "); 
		
		} 
				
		for(j = 0 ; j < ni ; j++){ 
		
			printf("*");
					
		}for(k = 0; k < ns; k++){
			
				printf(" ");
				}
	 	
	 	for(m = ns; m < na; m++){
		
			printf("*"); 

					
		}for(k = 0; k < ns; k++){
			
				printf(" ");
			
				}
		
		for(j = 0 ; j < ni ; j++){ 
		
			printf("*");
					
		}for(k = 0; k < ns; k++){
			
				printf(" ");
			
				}
		
		printf("\n");
		
		rombo(na,ne,ns-2,ni+1); 
	
	}
}
void romboabajo(int na, int ne, int ns,int ni){
	
	int i,j,k,l,r,m;
	
	if(ns == 2*(ne+1)){
		printf(" "); 
	}	
	
	else{
		for(i = 0; i< ne; i++){
		
			printf(" "); 
		
		} 
				
		for(j = 0 ; j < ni ; j++){ 
		
			printf("*");
					
		}for(k = 0; k < ns; k++){
			
				printf(" ");
				}
	 	
	 	for(m = ns; m < na; m++){
		
			printf("*"); 

					
		}for(k = 0; k < ns; k++){
			
				printf(" ");
			
				}
		
		for(j = 0 ; j < ni ; j++){ 
		
			printf("*");
					
		}for(k = 0; k < ns; k++){
			
				printf(" ");
			
				}
		
		printf("\n");
		
		romboabajo(na,ne,ns+2,ni-1); 
	
	}
}
