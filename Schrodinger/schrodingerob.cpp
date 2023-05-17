#include<iostream>
#include<cmath>
#include<fstream>
#include<complex>

using namespace std;

//defino mis parámetros iniciales
#define N 1000
#define ncicl N/16
#define lamb 1
#define pi 3.14
#define pasos 1000

int main(void){

    //Defino las variables
    int j,n;
    complex<double> phi_j0[N],alph[N],bet[N],xi[N],i;
    double s,k_0,V_j[N],norma;
    ofstream schr,fnorma;

    //defino x_0 y sigma (donde esta centrada y anchura de la función de onda)
    double sigma,x_0;
    sigma=N/20.0;
    x_0=N/8.0;

    //defino i
    i=complex<double>(0.0,1.0); 

    //calcular k_0
    k_0=2*pi*ncicl/N;
    //calcular s
    s=1.0/(4.0*k_0*k_0);
    //calculo condiciones contorno phi_j0
    phi_j0[0]=0;
    phi_j0[N-1]=0;
    /* version 1 de la funcion de onda (demasiado ancha) 
    //calculo phi_j0
    for(j=1;j<N-1;j++){
        phi_j0[j]= exp(j*1.0*k_0*i)*exp(-8.0*(4.0*j-N)*(4.0*j-N)/(N*N));
    } 
    */
   //version 2 de la función de onda
    for(j=1;j<N-1;j++){
        phi_j0[j]= exp(j*1.0*k_0*i)*exp(-1.0*(j-x_0)*(j-x_0)/(2*sigma*sigma));
    } 

    //calcular V_j
    for(j=0;j<N;j++){
        if((j>=2*N/5)&&(j<=3*N/5)){
            V_j[j]=lamb*k_0*k_0;
        }
        else{
            V_j[j]=0.0;
        }

    }
    
    //inicializar alph
    alph[N-2]=0.0;

    //calcular alpha
    for(j=N-2;j>0;j--){
        alph[j-1]=-1.0/(-2.0+2.0*(i/s)+alph[j]-V_j[j]);
    }
    
    schr.open("schrodinger_data.dat"); 
    fnorma.open("fnorma.dat");

    //inicio ciclo
    for(n=0;n<pasos;n++){
        //escribir en el ficheros los valores de la funcion de onda, sumarlos todos y representar suma
        norma=0.0;
        
        for(j=0;j<N;j++){
            norma=norma + norm(phi_j0[j]);
            schr<<j<<", "<<norm(phi_j0[j])<<", "<<real(phi_j0[j])<<", "<<imag(phi_j0[j])<<", "<<V_j[j]<<endl;
        }

        //incicializar y calcular beta
        bet[N-2]=0.0;
        for(j=N-2;j>0;j--){
            bet[j-1]=(1.0/(-2.0+2.0*(i/s)+alph[j]-V_j[j]))*(4.0*i*(phi_j0[j]/s)-bet[j]);
        }

        //calcular xi
        xi[0]=0.0;    
        for(j=0;j<N-2;j++){
            xi[j+1]= alph[j]*xi[j]+bet[j];
        }

        //calcular función de onda
        for(j=0;j<N;j++){
            phi_j0[j]=xi[j]-phi_j0[j];
        }
         
    
        fnorma<<norma<<endl;
        schr<<endl;
    }
    
    schr.close();
    fnorma.close();


    return 0;
}