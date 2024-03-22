#include<stdio.h>
#include<stdlib.h>

int main(){
	char mode[4]="";
	char buf[100]="C:\Users\jona-\Documents\Prueba";
	scanf("%s", mode);
	int i = atoi(mode);
	chmod(buf,i);
}
