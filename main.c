#include <stdio.h>
#include <string.h>

void ordenamientoLlegada(int duraciones[], int llegadas[], int num, char IDs[num][3],int tiemposRestantes[]);
void ordenamientoTR(int duraciones[], int llegadas[], int num, char IDs[num][3], int comp, int tiemposRestantes[], int conteo);
int main() {
    int num;
    printf("Ingrese el numero de procesos\n");
    scanf("%d", &num);
    char IDs[num][3];
    int duraciones[num];
    int llegadas[num];
    int tiemposRestantes[num];
    int tiemposEspera[num];
    int tiemposTotales[num];
    double totalTE = 0;
    double totalTT = 0;
    double promedioTE = 0;
    double promedioTT = 0;
    int fin = 0;
    int conteo = 0;
    int temp = 0;
    char identificador[3];
    int cuenta = 0;
    int suma = 0;
    int cambio = 0;
    int parcial = 0;

    for(int i = 0; i<num; i++){
        printf("Ingrese el identificador del proceso %d\n", (i+1));
        scanf("%s", IDs[i]);
        printf("Ingrese la duracion del proceso %s\n", IDs[i]);
        scanf("%d", &duraciones[i]);
        tiemposRestantes[i] = duraciones[i];
        printf("Ingrese la llegada del proceso %s\n", IDs[i]);
        scanf("%d", &llegadas[i]);
    }
    ordenamientoLlegada(duraciones, llegadas, num, IDs, tiemposRestantes);
    ordenamientoTR(duraciones, llegadas, num, IDs, llegadas[conteo], tiemposRestantes, conteo);
    suma = llegadas[0];
    while(conteo<num){
        if(cambio == 0){
            cuenta = conteo;
            fin = suma + tiemposRestantes[conteo];
            cambio = 1;
        }
        if(llegadas[cuenta+1]<=fin&&cuenta!=num-1&&tiemposRestantes[conteo]>0) {
            cuenta = cuenta + 1;
            ordenamientoTR(duraciones, llegadas, num, IDs, llegadas[cuenta], tiemposRestantes, conteo);
            if(llegadas[conteo+1]>suma){
                parcial = llegadas[conteo+1]-suma;
                suma = suma + parcial;
                tiemposRestantes[conteo] = tiemposRestantes[conteo] - parcial;
            }
            if (tiemposRestantes[conteo+1] < tiemposRestantes[conteo]&&tiemposRestantes[conteo]>0) {
                temp = llegadas[conteo+1];
                llegadas[conteo+1] = llegadas[conteo];
                llegadas[conteo] = temp;
                temp = duraciones[conteo+1];
                duraciones[conteo+1] = duraciones[conteo];
                duraciones[conteo] = temp;
                temp = tiemposRestantes[conteo+1];
                tiemposRestantes[conteo+1] = tiemposRestantes[conteo];
                tiemposRestantes[conteo] = temp;
                strcpy(identificador, IDs[conteo+1]);
                strcpy(IDs[conteo+1], IDs[conteo]);
                strcpy(IDs[conteo], identificador);
                cambio = 0;
            }
        }else{
            suma = suma + tiemposRestantes[conteo];
            tiemposRestantes[conteo] = 0;
            tiemposEspera[conteo] = suma -llegadas[conteo] -duraciones[conteo];
            tiemposTotales[conteo]=tiemposEspera[conteo]+duraciones[conteo];
            totalTE = totalTE + (double)tiemposEspera[conteo];
            totalTT = totalTT + (double)tiemposTotales[conteo];
            conteo = conteo + 1;
            cambio = 0;
        }
    }
    promedioTE = totalTE/(double)num;
    promedioTT = totalTT/(double)num;
    for(int i = 0; i<num; i++){
        printf("%s Duracion: %d Llegada: %d TiempoE: %d TiempoT: %d\n", IDs[i], duraciones[i], llegadas[i], tiemposEspera[i], tiemposTotales[i]);
    }
    printf("Totales Tiempo de espera: %.1f\n", totalTE);
    printf("Totales Tiempo total: %.1f\n", totalTT);
    printf("Promedio Tiempo de espera: %.1f\n", promedioTE);
    printf("Promedio Tiempo total: %.1f\n", promedioTT);
    return 0;
}
void ordenamientoLlegada(int duraciones[], int llegadas[], int num, char IDs[num][3], int tiemposRestantes[]){
    int aux;
    char idTemp[3];
    for(int i = 0; i < num; i++){
        for(int j = i; j < num; j++){
            if(llegadas[i]>llegadas[j]){
                aux = llegadas[j];
                llegadas[j] = llegadas[i];
                llegadas[i] = aux;
                aux = duraciones[j];
                duraciones[j] = duraciones[i];
                duraciones[i] = aux;
                aux = tiemposRestantes[j];
                tiemposRestantes[j] = tiemposRestantes[i];
                tiemposRestantes[i] = aux;
                strcpy(idTemp, IDs[j]);
                strcpy(IDs[j], IDs[i]);
                strcpy(IDs[i], idTemp);
            }
        }
    }
}

void ordenamientoTR(int duraciones[], int llegadas[], int num, char IDs[num][3], int comp, int tiemposRestantes[], int conteo){
    int aux;
    char idTemp[3];
    int cant = 0;

    for(int i = 0; i<num; i++) {
        if(llegadas[i]<=comp){
            cant++;
        }
    }

    for(int i = conteo+1; i < cant; i++){
        for(int j = i; j < cant; j++){
            if(tiemposRestantes[i]>tiemposRestantes[j]){
                aux = llegadas[j];
                llegadas[j] = llegadas[i];
                llegadas[i] = aux;
                aux = duraciones[j];
                duraciones[j] = duraciones[i];
                duraciones[i] = aux;
                aux = tiemposRestantes[j];
                tiemposRestantes[j] = tiemposRestantes[i];
                tiemposRestantes[i] = aux;
                strcpy(idTemp, IDs[j]);
                strcpy(IDs[j], IDs[i]);
                strcpy(IDs[i], idTemp);
            }
        }
    }
}
