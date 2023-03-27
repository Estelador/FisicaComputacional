#include<iostream>
#include<cmath>
#include<fstream>


using namespace std;

//definimos ctes
#define MS 1.99e30
#define N 10
#define M 3

//declaro una función que lea un archivo de datos y me lo pase a una matriz NxM double
void leer_matriz(double matrix[N][M]);
//declaro una función que muestre una matriz NxM double
void mostrar_matriz(double matrix[N][M]);


//declaramos función reescalar masa
void reesc_masa(double matrix[N][M]);
//declaramos función calcular a(0)


int main(void){

    //declaro una matriz NxM double
    double matrix[N][M];

    //uso la función leer matriz
    leer_matriz(matrix);

    //uso la función mostrar matriz
    mostrar_matriz(matrix);

    return 0;
}

//defino la función leer matriz
void leer_matriz(double matrix[N][M]){
    int i,j;
    ifstream fich;

    fich.open("datos0.dat");

    for(i=0;i<N;i++)
        for(j=0;j<M;j++)
            fich>>matrix[i][j];


    fich.close();

    return;
}

//defino la función mostrar matriz
void mostrar_matriz(double matrix[N][M])
{   int i,j;
    
    for(i=0;i<N;i++)
        for(j=0;j<M;j++)
            cout<<matrix[i][j]<<"   ";

    return;
}

/*void reesc_masa(double matrix[N][M]){
    int i,j;

    for(i=)
}*/



//definimos funcion calcular aceleracion

