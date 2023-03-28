#include <iostream>
#include <cmath>
#include <fstream>

using namespace std;

// definimos ctes
#define MS 1.99e30
#define C 149.6e6
#define N 9
#define G 6.67e-18

// declaro una función que lea un archivo de datos y me lo pase a una vector NxM double
void leer_vector(double vector[N],string nombre);
// declaro una función que muestre una vector NxM double
void mostrar_vector(double vector[N]);

//declaro la función inicializar a cero vector
void inic0(double vector[N]);


// declaramos función reescalar masa
void reesc_masa(double vector[N]);
// declaramos función reescalar r
void reesc_r(double vector[N]);
// declaramos función reescalar v
void reesc_v(double vector[N]);


// declaramos función calcular a(0)
void calc_a0(double vector[N],double vector1[N],double vector2[N]);

int main(void)
{

    // declaro un vector N double para masas
    double vect_m[N];
    // declaro un vector N double para velocidades v_y
    double vect_v_y[N];
    // declaro un vector N double para velocidades v_x
    double vect_v_x[N];
    // declaro un vector N double para distancias r_x
    double vect_r_x[N];
    // declaro un vector N double para distancias r_y
    double vect_r_y[N];

    //declaro un vector N double para aceleraciones a_x
    double a_x[N];
    //declaro un vector N double para aceleraciones a_y
    double a_y[N];

    // uso la función leer vector para m0
    leer_vector(vect_m,"m0.dat");
    // uso la función leer vector para v0
    leer_vector(vect_v_y,"vel0.dat");
    // uso la función leer vector para r0
    leer_vector(vect_r_x,"r0.dat");

    // uso la función mostrar vector para m0
    mostrar_vector(vect_m);
    cout<<"\n";
    // uso la función mostrar vector para v0_y
    mostrar_vector(vect_v_y);
    cout<<"\n";
    // uso la función mostrar vector para r0_x
    mostrar_vector(vect_r_x);
    cout<<"\n";

    //inicializo a cero r0_y , v0_x , a_x y a_y
    inic0(vect_r_y);
    inic0(vect_v_x);
    inic0(a_x);
    inic0(a_y);

    //reescalo la masa y muestro
    reesc_masa(vect_m);
    cout<<"\n";
    //reescalo r_x y muestro
    reesc_r(vect_r_x);
    cout<<"\n";
    //reescalo v_y y muestro
    reesc_v(vect_v_y);
    cout<<"\n";

    //calulo la aceleración
    calc_a0(a_x,vect_m,vect_r_x);
    
    calc_a0(a_y,vect_m,vect_r_y);

    cout<<a_x[1]<<"\n";

    mostrar_vector(a_x);
    cout<<"\n";
    mostrar_vector(a_y);
    cout<<"\n";




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

//defino la función inicializar a cero vector
void inic0(double vector[N]){
    int i;

    for(i=0;i<N;i++)
        vector[i]=0;

    return;
}
//defino las funciones reescalar masa y r
void reesc_masa(double vector[N])
{
    int i;

    for (i=0; i<N; i++){
        vector[i]=vector[i]/MS;
        cout<<vector[i]<<"  ";
    }
    return;
}
void reesc_r(double vector[N]){
    int i;

    for (i=0; i<N; i++){
        vector[i]=vector[i]/C;
        cout<<vector[i]<<"  ";
    }
    return;
}
void reesc_v(double vector[N])
{
    int i;

    for (i=0; i<N; i++){
        vector[i]=vector[i]*pow(((C)/(G*MS)),0.5);
        cout<<vector[i]<<"  ";
    }
    return;
}

// definimos funcion calcular aceleracion
void calc_a0(double vector[N],double vector1[N],double vector2[N]){
    int i,j;
    
    for(i=0;i<N;i++){

        for(j=0;j<N;j++){
            if(i=!0){
            vector[i]=(vector1[j])*(vector2[i]-vector2[j])/(pow((abs(vector2[i]-vector2[j])),3));
            }
        }

        vector[i]=-vector[i];
    }
    return;
}
