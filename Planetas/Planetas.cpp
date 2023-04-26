#include <iostream>
#include <cmath>
#include <fstream>
#include<iomanip>

using namespace std;

// definimos ctes
#define MS 1.99e30 //kg
#define C 149.6e6 //km
#define N 9 
#define G 6.67e-20  //kg km^3/s^2 kg^2

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
void calc_a(double vector[N],double vector1[N],double vector2[N],double vector3[N]);

//declaro función calcular r(h)
void calc_rh(double h,double vector[N],double v1[N],double v2[N],double v3[N]);

//declaro función calcular w
void calc_w(double h,double vector[N],double v1[N],double v2[N]);

//declaro función calcular v(h)
void calc_vh(double h,double vector[N],double v1[N],double v2[N]);

//declaro función calcular periodo T
void calc_T(double v[N],double v1[N],double temp);

//declaro función calcular Energía
double calc_E(double ep[N],double ec[N],double v1[N],double v2[N],double v3[N],double v4[N],double v5[N]);


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

    //declaro vector auxiliar w
    double w_x[N];
    double w_y[N];

    //decl vector T periodo
    double T[N];
    //decl vectores ec y ep 
    double ec[N];
    double ep[N];    
    
    //declaro los pasos temporales h segundos y el tiempo durante el que veo el sistema solar en años
    double h;
    double t;
    //declaro los pasos de mi bucle
    int pasos;
    //declaro temporizador para el periodo
    double temp;
    //declaro ficheros salida
    ofstream pos,period,energ;
    
    //Abrimos los archivos
    period.open("Periodos.txt");
    energ.open("Energia.txt");
    pos.open("PosicionesPlanets.txt");
   


    temp=0.0;

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

    //inicializo a cero r0_y , v0_x , a_x , a_y , w_x y w_y
    inic0(vect_r_y);
    inic0(vect_v_x);
    inic0(a_x);
    inic0(a_y);
    inic0(w_x);
    inic0(w_y);

    //reescalo la masa y muestro
    reesc_masa(vect_m);
    cout<<"\n";
    //reescalo r_x y muestro
    reesc_r(vect_r_x);
    cout<<"\n";
    //reescalo v_y y muestro
    reesc_v(vect_v_y);
    cout<<"\n";

    //calulo la aceleración inicial
    calc_a(a_x,vect_m,vect_r_x,vect_r_y);
    calc_a(a_y,vect_m,vect_r_y,vect_r_x);

    mostrar_vector(a_x);
    cout<<"\n";
    mostrar_vector(a_y);
    cout<<"\n";

    cout<<"¿De cuántos días quieres los pasos temporales?: ";
    cin>>h;

    cout<<"¿El movimiento equivalente a cuantos años quieres ver del Sistema Solar?: ";
    cin>>t;

    //paso t y h a segundos
    t=t*365*24*3600;
    h=h*24*3600;

    //reescalo t y h a mi programa
    t=t*sqrt(G*MS/(C*C*C));
    h=h*sqrt(G*MS/(C*C*C));

    //miro cuantos pasos tendrá mi bucle
    pasos=t/h;

    int n;
    //empiezo el bucle
    for(n=0;n<pasos;n++){


        //calculo rh
        calc_rh(h,vect_r_x,vect_r_x,vect_v_x,a_x);
        calc_rh(h,vect_r_y,vect_r_y,vect_v_y,a_y);
        //imprimo posiciones nuevas
        int i;
        for (i=0;i<N;i++){
            pos<<vect_r_x[i]<<", "<<vect_r_y[i]<<"\n";
        }
        pos<<"\n";

        //calculo w
        calc_w(h,w_x,vect_v_x,a_x);
        calc_w(h,w_y,vect_v_y,a_y);

        //calculo la nueva aceleración
        calc_a(a_x,vect_m,vect_r_x,vect_r_y);
        calc_a(a_y,vect_m,vect_r_y,vect_r_x);

        //calculo la nueva velocidad
        calc_vh(h,vect_v_x,w_x,a_x);
        calc_vh(h,vect_v_y,w_y,a_y);

        temp=h+temp;

        //calculo periodo
        calc_T(T,vect_r_y,temp);

        //inicializo energias
        inic0(ec);
        inic0(ep);

        //Sacamos el output al archivo de energia
        energ<<" "<<temp/(sqrt(G*MS/(C*C*C))*3600*24)<<" "<<calc_E<<"\n";

    }

        //imprimo periodo
        int j;
        for (j=1;j<N;j++){
            period<<scientific<<setprecision(6)<<T[j]/(sqrt(G*MS/(C*C*C))*3600*24)<<"\n";
        }

        //cierro archivos
        pos.close();
        period.close();
        energ.close();

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

// definimos funciones para calcular cosas
void calc_a(double vector[N],double vector1[N],double vector2[N],double vector3[N]){
    int i,j;
    
    for(i=1;i<N;i++){
        for(j=0;j<N;j++){
            if(i!=j){
            vector[i]=vector[i]+((vector1[j])*(vector2[i]-vector2[j]))/(pow(sqrt(((vector2[i]-vector2[j])*(vector2[i]-vector2[j]))+((vector3[i]-vector3[j])*(vector3[i]-vector3[j]))),3));
            }
            
        }
        vector[i]=-vector[i];

    }
    return;
}

void calc_rh(double h, double vector[N], double v1[N], double v2[N], double v3[N]){
    int i;

    for(i=0;i<N;i++){
        vector[i]=v1[i]+h*v2[i]+(h*h/2)*v3[i];
    }
}

void calc_w(double h, double vector[N], double v1[N], double v2[N]){
    int i;

    for(i=0;i<N;i++){
        vector[i]=v1[i]+(h/2)*v2[i];
    }
}

void calc_vh(double h, double vector[N], double v1[N], double v2[N]){
    int i;

    for(i=1;i<N;i++){
        vector[i]=v1[i]+(h/2)*v2[i];
    }  
}

void calc_T(double v[N], double v1[N],double temp){
    int i;
    for(i=1;i<N;i++){
        if(v[i]==0){
            if(v1[i]>=0){
             v[N]=2*temp;
            }
        }
    }
    return;
}

double calc_E(double ep[N],double ec[N], double v1[N], double v2[N], double v3[N], double v4[N], double v5[N]){
    int i,j;
    double SumE,Energia;
    SumE=0.0;
    Energia=0.0;

    for(i=1;i<N;i++){
            for(j=0;j<N;j++){
                if(i!=j){
                    //EPotencial
                    ep[i]= ep[i] + G*(v1[i]*v1[j])/(sqrt(((v2[i]-v2[j])*(v2[i]-v2[j]))+((v3[i]-v3[j])*(v3[i]-v3[j]))));
                    Energia= Energia + ec[i];
                }
                //ECinética
                ec[i]= v1[i]*(v4[i]*v4[i]+v5[i]*v5[i])/(2-Energia);
                SumE = SumE+ec[i];
            }
    }
    return SumE;
    
}
