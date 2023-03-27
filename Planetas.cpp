#include <iostream>
#include <cmath>
#include <fstream>

using namespace std;

// definimos ctes
#define MS 1.99e30
#define N 9

// declaro una función que lea un archivo de datos y me lo pase a una vector NxM double
void leer_vector(double vector[N],string nombre);
// declaro una función que muestre una vector NxM double
void mostrar_vector(double vector[N]);

/*
// declaramos función reescalar masa
void reesc_masa(double vector[N]);
// declaramos función calcular a(0) */

int main(void)
{

    // declaro un vector N double para masas iniciales
    double vect_m[N];
    // declaro un vector N double para velocidades iniciales
    double vect_v[N];
    // declaro un vector N double para distancias r iniciales
    double vect_r[N];

    // uso la función leer vector para m0
    leer_vector(vect_m,"m0.dat");
    // uso la función leer vector para v0
    leer_vector(vect_v,"vel0.dat");
    // uso la función leer vector para r0
    leer_vector(vect_r,"r0.dat");

    // uso la función mostrar vector para m0
    mostrar_vector(vect_m);
    cout<<"\n";
    // uso la función mostrar vector para v0
    mostrar_vector(vect_v);
    cout<<"\n";
    // uso la función mostrar vector para r0
    mostrar_vector(vect_r);

    return 0;
}

// defino la función leer vector
void leer_vector(double vector[N],string nombre)
{
    int i;
    ifstream fich;

    fich.open(nombre);

    for (i = 0; i < N; i++)
        fich >> vector[i];

    fich.close();

    return;
}

// defino la función mostrar vector
void mostrar_vector(double vector[N])
{
    int i;

    for (i = 0; i < N; i++)
        cout << vector[i] << "   ";

    return;
}
/*
void reesc_masa(double vector[N])
{
    int i, j;

    for (i =)
}
*/
// definimos funcion calcular aceleracion
