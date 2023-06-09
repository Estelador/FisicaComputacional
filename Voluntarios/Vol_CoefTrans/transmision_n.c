#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "complex.h"
#include "gsl_rng.h"

#define PI 3.1415927
#define N 200

gsl_rng *tau;

int main(){
    
    //Ficheros
    FILE *resultados,*potencial;
    //Abrimos fichero
    resultados=fopen("resultados.txt","w");
    potencial=fopen("pot_n.txt","w");
    
    //Variables externa
    extern gsl_rng *tau;
    //Variables
    int i,j,k;
    int nciclos,Nd,Nexp,t,Ntransmision,n,d;
    double k0, lambda,s,r;
    double norma,n1,n2,Pi,Pd,aleat,aleat1,T;
    double V[N+1],A_p[N+1],A_p_aux[N+1];
    fcomplex A_0[N+1], b[N-1], chi[N+1], alpha[N], beta[N], phi[N+1];
    fcomplex x,y;
    fcomplex aux[N-1];
    
    //Inicializacion de la semilla
    int semilla=18234957;
    tau= gsl_rng_alloc(gsl_rng_taus);
    gsl_rng_set(tau,semilla);

    
    //Escribimos el numero de ciclos para calcular k0
    
    printf("Introduzca el numero de ciclos: \n");
    scanf("%i",&nciclos);
    k0= (2.0*PI*nciclos)/(N*1.0);
    
    //Hallamos ahora el valor de s
    s=1.0/(4.0*k0*k0);
    
    //Escribimos el valor de lambda deseado
    printf("Introduzca el valor de lambda: \n");
    scanf("%lf",&lambda);
    
    //printf("Introduzca el valor de d: \n");
    //scanf("%i",&d);
    
    //printf("Introduzca el numero de barreras de potencial: \n");
    //scanf("%i",&n);
    
    
    //Definimos el potencial V[j] con 3 barreras equidistanciadas N/5
    for(j=0;j<=N;j++){
        if((j>=0)&&(j<=N/5)){
            V[j]=lambda*k0*k0;
        }
        else{
            V[j]=0.0;
        }
    }
    for(j=0;j<=N;j++){
        if((j>=2*N/5)&&(j<=3*N/5)){
            V[j]=lambda*k0*k0;
            
        }
        if(j>(3*N/5)){
            V[j]=0.0;
            
        }
    }
    
    for(j=0;j<=N;j++){
        if((j>=4*N/5)&&(j<=N)){
            V[j]=lambda*k0*k0;
            
        }
    }

    for(j=0;j<=N;j++){
        fprintf(potencial,"%i \t %lf \n",j,V[j]);
    }
    
    beta[N-1].r=beta[N-1].i=0.0;
    chi[0].r=chi[0].i=0.0;
    chi[N].r=chi[N].i=0.0;
    
    //Definimos la funcion de onda inicial phi[j]
    phi[0].r=phi[N].r=0.0;
    //Introducimos el numero de pasos de repeticion de cada experimento
    printf("Introduzca el tiempo de su experimento:\n");
    scanf("%i",&Nd);
    
    printf("Introduzca el numero de experimentos: \n");
    scanf("%i",&Nexp);
    
    //Inicializamos el factor de transmision
    Ntransmision=0;
    
    //Realizamos la iteracion recursiva
    for (k=0;k<Nexp;k++){
        
        //Escribimos la funcion de onda inicial phi[j]
        phi[0].r=phi[N].r=0.0;
        phi[0].i=phi[N].i=0.0;
        
        for (j=1; j<=(N-1); j++){
            //Realizamos la operacion separando parte real y compleja
            phi[j]=RCmul(exp(-(8.0*pow(4*j-N,2))/(1.0*N*N)),Complex(cos(k0*j),sin(k0*j)));
        }
        
        //Hallamos A0
        for(j=0;j<=N;j++){
            A_0[j]=Complex(-2-V[j],2.0/s);
        }
        
        alpha[N-1].r=0.0;
        alpha[N-1].i=0.0;
        
        //Inicializamos el vector aux a 0
        for(j=0;j<=(N-2);j++){
            aux[j].r=0.0;
            aux[j].i=0.0;
        }
        
        for (j=0;j<=(N-2);j++){
            aux[j]=Cadd(A_0[(N-1)-j],alpha[(N-1)-j]);
            alpha[(N-2)-j]=Cdiv(Complex(-1.0,0.0),aux[j]);
        }
        //Usamos una variable r para determinar si tenemos que generar nuevas ondas o que siga pasando el tiempo
        //printf("%lf \t",(1.0*k)/(Nexp*1.0));
        //printf("%i \n", Ntransmision);
        r=0.0;
        t=0;

        while(r==0.0){
            //Hallamos los vectores b y beta
            for (j=1;j<=(N-1);j++){
                b[j]=Cmul(Complex(0.0,4.0/(s*1.0)),phi[j]);
            }
            //beta[N-1].r=0.0;
            //beta[N-1].i=0.0;
            for(j=0;j<=(N-2);j++){
                //Hallamos por partes separadas x e y
                x= Csub(b[(N-1)-j],beta[(N-1)-j]);
                y= Cadd(A_0[(N-1)-j],alpha[(N-1)-j]);
                
                //Hallamos el vector beta
                beta[(N-2)-j]=Cdiv(x,y);
            }
            //Inicializamos el vector chi en 0 y en N
            //chi[0].r=chi[N].r=0.0;
          //  chi[0].i=chi[N].i=0.0;
            //Hallamos el vector chi
            for (j=0;j<=(N-1);j++){
                chi[j+1]=Cadd(Cmul(alpha[j],chi[j]),beta[j]);
            }
            
            norma=0.0;
            for (j=0;j<=N;j++){
                phi[j]= Csub(chi[j],phi[j]);
                norma = norma + Cabs(phi[j])*Cabs(Conjg((phi[j]))); //Recalculamos la norma
            }
            //Ahora pasamos un cierto tiempo t para que detecte donde estan las nuevas ondas generadas si a derecha o a izquierda
            t=t+1;
            if(t==Nd){
                fprintf(resultados,"%i \t", t);
                Pd=0.0;
                for(j=(4*N/5);j<=N;j++){
                    Pd=Pd+Cabs(phi[j])*Cabs(Conjg((phi[j])));
                }
                //Generamos un numero aleatorio entre 0 y 1
                aleat=gsl_rng_uniform(tau);
                fprintf(resultados,"%lf \t %lf \t",aleat,Pd);
                if(aleat<Pd){
                    Ntransmision=Ntransmision+1;
                    r=r+1;
                }else{
                    for(j=(4*N/5);j<=N;j++){
                        phi[j].r=phi[j].r=0.0;
                    }
                    //Normalizamos la funcion de onda
                    n1=0.0;
                    for(j=0;j<=N;j++){
                        n1=n1+Cabs(phi[j])*Cabs(Conjg((phi[j])));
                    }
                    for(j=0;j<=N;j++){
                        phi[j].r=phi[j].r/sqrt(n1);
                        phi[j].i=phi[j].i/sqrt(n1);
                    }
                    //Inicializamos la probabilidad hacia la izquierda
                    Pi=0.0;
                    for(j=0;j<=N/5;j++){
                        Pi=Pi+Cabs(phi[j])*Cabs(Conjg((phi[j])));
                    }
                    //Generamos otro numero aleatorio entre 0 y 1
                    aleat1=gsl_rng_uniform(tau);
                    fprintf(resultados,"%lf \t %lf \n",aleat1,Pi);
                    if(aleat1<Pi){
                        r=r+1;
                    }else{
                        for(j=0;j<=N/5;j++){
                            phi[j].r=phi[j].r=0.0;
                        }
                        //Renormalizamos la onda al cambiar la situacion fisica
                        n2=0.0;
                        for(j=0;j<=N;j++){
                            n2=n2+Cabs(phi[j])*Cabs(Conjg((phi[j])));
                        }
                        for(j=0;j<=N;j++){
                            phi[j].r=phi[j].r/sqrt(n2);
                            phi[j].i=phi[j].i/sqrt(n2);
                        }
                        //Ponemos a 0 el tiempo para dejar evolucionar el sistema nuevamente
                        t=0;
                    }
                }
            }
        }
    }
                
    T=(1.0*Ntransmision)/(Nexp*1.0);
    printf("%i \t",Ntransmision);
    printf("%lf \n",T);
    fclose(potencial);
    fclose(resultados);
                
    return 0;
    
}



