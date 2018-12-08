#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#define N 6
#define M 10
#define LENGTH 0xFF
void
escribirMenu(int numero){
        printf("***--NUMERO DEL SORTEO %i --***\n",numero);
        printf("1. - Generar quiniela aleatoria.\n");
        printf("2. - Generar apuestas múltiples.\n");
        printf("3. - Realizar sorteo.\n");
        printf("4. - Comprobar quiniela manualmente.\n");
        printf("5. - Comprobar apuestas múltiples");
        printf("6. - Consultar sorteo actual.\n");
        printf("7. - Consultar histórico.\n");
        printf("8. - Salir.\n");
        printf("\n");
        printf("Elige una opción: ");
}
//FUNCION CASE 1
void
generar_quiniela(int tabla[N]){
        for(int i=0; i<N; i++){
                int numero = rand()%49+1;
                tabla[i] = numero;
        }

        for(int i=0; i<N; i++){
                for(int j=0; j<N-i-1; j++){
                        if(tabla[j] > tabla[j+1]){
                                int num = tabla[j];
                                tabla[j] = tabla[j+1];
                                tabla[j+1] = num;
                        }
                }
        }

        for(int i=0; i<N; i++)
                printf(" %i ",tabla[i]);
        printf("\n");
        FILE *fichero = fopen("bonoloto.txt","a+");
        for(int i=0; i<N; i++)
                fprintf(fichero," %i ",tabla[i]);
        fprintf(fichero,"\n");
        fclose(fichero);
}
//FUNCION CASE 2
void
generar_multiples_quinielas(int n_apuestas, char nomfichero[LENGTH], int numero_sorteo){
        int quiniela[N];
        char identficador[M];
        FILE *fichero_apuesta = fopen(nomfichero,"w+");
        fprintf(fichero_apuesta,"%i\n",numero_sorteo);
        for(int i=0; i<M; i++)
                identficador[i] = rand()%41+41;
        fprintf(fichero_apuesta,"%s\n",identficador);
        do{
                for(int i=0; i<N; i++){
                        int numero = rand()%49+1;
                        quiniela[i] = numero;
                }
                for(int i=0; i<N; i++){
                        for(int j=0; j<N-i-1; j++){
                                int num = quiniela[j];
                                quiniela[j] = quiniela[j+1];
                                quiniela[j+1] = num;
                        }
                }
                for(int i=0; i<N; i++)
                        fprintf(fichero_apuesta," %i ",quiniela[i]);
                fprintf(fichero_apuesta,"\n");
                n_apuestas--;
        }while(n_apuestas !=0);
        fclose(fichero_apuesta);
}
int
main(int argc, char *argv[]){
        int opcion,numenumero_apuestasro_apuestas, quiniela[N];
        char nombre[LENGTH];
        srand(time(NULL));
        int numero_sorteo;
        FILE *tubosorteo = NULL;

        do{
                if(!(tubosorteo = fopen("sorteo.txt","r"))){
                        fprintf(stderr, "No encontramos el fichero.\n");
                        return EXIT_FAILURE;
                }
                fscanf(tubosorteo,"%i",&numero_sorteo);
                fclose(tubosorteo);
                escribirMenu(numero_sorteo);
                scanf(" %i",&opcion);
                switch(opcion){
                        case 1:
                                generar_quiniela(quiniela);
                                break;
                        case 2:
                                printf("Numero de apuestas: ");
                                scanf(" %i",&numero_apuestas);
                                printf("Nombre del fichero: ");
                                scanf(" %s",nombre);
                                generar_multiples_quinielas(numero_apuestas,nombre,numero_sorteo);
                                break;
                        case 3:
                                numero_sorteo++;
                                tubosorteo = fopen("sorteo.txt","w");
                                fprintf(tubosorteo,"%i",numero_sorteo);
                                fclose(tubosorteo);
                                break;
                        case 4:
                                break;
                        case 5:
                                break;
                        case 6:
                                break;
                        case 7:
                                break;
                        case 8:
                                break;
                        default:
                                printf("Opcion incorrecta.\n");
                                break;
                };
        }while(opcion!=8);
        return EXIT_SUCCESS;
}
