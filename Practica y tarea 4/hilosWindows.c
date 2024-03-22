#include <Windows.h>
#include <stdio.h>
#include <process.h>

//funcion que imprime el identificador de el hilo
DWORD WINAPI idHilo(LPVOID p) {
    printf("El identificador del hilo es= %d \n", GetCurrentThreadId()); 
}

//imprime el mensaje de Practica 2
DWORD WINAPI imprimirMensaje(LPVOID mensaje){
    char* cadena = (char*) mensaje;
    printf("%s \n", cadena);
}

int main(){
    HANDLE hilos[15];
    HANDLE proceso;
    STARTUPINFO sinfo;        
    PROCESS_INFORMATION pinfo;        
    memset(&sinfo, 0, sizeof(STARTUPINFO));
    memset(&pinfo, 0, sizeof(PROCESS_INFORMATION));
    
    sinfo.dwFlags = STARTF_USESHOWWINDOW;
    sinfo.wShowWindow = SW_SHOWMAXIMIZED;
    
    BOOL bSucess = CreateProcess("C:\\Users\\jona-\\Documents\\Jona\\ESCOM\\semestre 4\\Sistemas Operativos\\Practica y tarea 4\\notepad.exe",
                                NULL, NULL, NULL, FALSE, CREATE_DEFAULT_ERROR_MODE, NULL, NULL, &sinfo, &pinfo);
    printf( "El id del proceso hijo: %d\n", _getpid() );
    
    for(int i=0; i<15; i++){
        hilos[i] = CreateThread(NULL, 0, idHilo, NULL, 0, NULL);

        for(int j=0; j<10; j++){
            hilos[j] = CreateThread(NULL, 0, idHilo, NULL, 0, NULL);

            //creacion de los hilos terminales
            for(int k=0; k<5; k++){
                hilos[k] = CreateThread(NULL, 0, imprimirMensaje, "Practica 2", 0, NULL);
            }
        }
    }
    
    for(int i=0; i<15; i++){
        WaitForSingleObject(hilos[i], INFINITE);
        
        for(int j=0; j<10; j++){
            WaitForSingleObject(hilos[j], INFINITE);

            for(int k=0; k<5; k++){
                WaitForSingleObject(hilos[k], INFINITE);
            }
        }
    }

    for(int i=0; i<15; i++){
        CloseHandle(hilos[i]);
        
        for(int j=0; j<10; j++){
            CloseHandle(hilos[j]);

            for(int k=0; k<5; k++){
                CloseHandle(hilos[k]);
            }
        }
    }
    
    return 0;
}