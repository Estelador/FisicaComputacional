#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "complex.h"

#define PI 3.1415927
#define N 1000

int main(){
    //Variables
    int i,j;
    int nciclos,Nt;
    double k0, lambda, s;
    double norma,A_m, pos, pos2, dx, dp, dEc, dEt,Ep;
    double V[N+1],A_p[N+1],A_p_aux[N+1];
    fcomplex A_0[N+1], b[N-1], chi[N+1], alpha[N], beta[N], phi[N+1];
    fcomplex x,y;
    fcomplex aux[N-1];
    fcomplex der[N+1], der2[N+1], mom, mom2, Ec, Ec2, Et, Et2;
    
    //Ficheros
    FILE *sch, *pot;
    FILE *resultados,*posicion,*momento,*etotal,*ecin,*epot;
    
    sch=fopen("sch.txt","w");
    pot=fopen("pot.txt","w");
    posicion=fopen("posicion.txt","w");
    momento=fopen("momento.txt","w");
    etotal=fopen("etotal.txt","w");
    ecin=fopen("ecin.txt","w");
    epot=fopen("epot.txt","w");

    
    //Escribimos el numero de ciclos para calcular k0
    
    printf("Introduzca el numero de ciclos: \n ");
    scanf("%i",&nciclos);
    k0= (2.0*PI*nciclos)/(N*1.0);
    
    //Hallamos ahora el valor de s
    s=1.0/(4.0*k0*k0);
    
    //Escribimos el valor de lambda deseado
    printf("Introduzca el valor de lambda: \n ");
    scanf("%lf",&lambda);
    
    //Definimos el potencial
    for(j=0;j<=N;j++){
        if ((j>=((2.0*N)/5.0))&&(j<=((3.0*N)/5.0))){
            V[j]=lambda*k0*k0;
            
        }else{
            V[j]=0.0;
        }
    }

    //Inicializamos la norma de la funcion de onda
    norma=0.0;
    
    //Definimos la funcion de onda inicial phi[j]
    phi[0].r=phi[N].r=0.0;
    
    for (j=1; j<=(N-1); j++){
        //Realizamos la operacion separando parte real y compleja
        phi[j]=RCmul(exp(-(8.0*pow(4*j-N,2))/(1.0*N*N)),Complex(cos(k0*j),sin(k0*j)));
        norma = norma + pow(Cabs(phi[j]),2); //Hallamos la norma
    }
    phi[0].i=phi[N].i=0.0;
    //Normalizamos la funcion de onda
    for(j=0;j<=N;j++){
        phi[j].r=phi[j].r/sqrt(norma);
        phi[j].i=phi[j].r/sqrt(norma);
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
    
    Nt=1000;
    
    //Realizamos la iteracion recursiva
    for (i=1;i<=Nt;i++){
        //Hallamos los vectores b y beta
        for (j=1;j<=(N-1);j++){
            b[j]=Cmul(Complex(0.0,4.0/(s*1.0)),phi[j]);
        }
        beta[N-1].r=0.0;
        beta[N-1].i=0.0;
        for(j=0;j<=(N-2);j++){
            //Hallamos por partes separadas x e y
            x= Csub(b[(N-1)-j],beta[(N-1)-j]);
            y= Cadd(A_0[(N-1)-j],alpha[(N-1)-j]);
            
            //Hallamos el vector beta
            beta[(N-2)-j]=Cdiv(x,y);
        }
        //Inicializamos el vector chi en 0 y en N
        chi[0].r=chi[N].r=0.0;
        chi[0].i=chi[N].i=0.0;
        //Hallamos el vector chi
        for (j=0;j<=(N-1);j++){
            chi[j+1]=Cadd(Cmul(alpha[j],chi[j]),beta[j]);
        }
        
        norma=0.0;
        for (j=0;j<=N;j++){
            phi[j]= Csub(chi[j],phi[j]);
            norma= norma+ pow(Cabs(phi[j]),2); //Recalculamos la norma
            
        }
        //Inicializamos el operador derivada
        der[0]=Csub(phi[1],phi[0]);
        der[0]=Csub(phi[N],phi[N-1]);
        
        //Hallamos las derivadas primera y segunda de la funcion de onda
        for(j=1;j<=(N-1);j++){
            der[j]=Csub(phi[j+1],phi[j-1]);
            der[j].r=der[j].r/2.0;
            der[j].i=der[j].i/2.0;
        }
        
        //Inicializamos el operador segunda derivada
        der2[0]=Csub(der[1],der[0]);
        der2[0]=Csub(der[N],der[N-1]);
        
        for(j=1;j<=(N-1);j++){
            der2[j]=Csub(der[j+1],der[j-1]);
            der2[j].r=der2[j].r/2.0;
            der2[j].i=der2[j].i/2.0;
        }
        
        //Hallamos el operador posicion, posicion al cuadrado, momento y energia cinetica y potencial
        //Inicializmos los operadores
        pos=0.0;
        pos2=0.0;
        mom.r=mom.i=0.0;
        mom2.r=mom2.i=0.0;
        Ec.r=Ec.i=0.0;
        Et.r=Et.i=0.0;
        Et2.r=Et2.i=0.0;
        
        for(j=0;j<=N;j++){
            pos=pos+j*pow(Cabs(phi[j]),2);
            pos2=pos2+j*j*pow(Cabs(phi[j]),2);
            
            mom=Cadd(mom,Cmul(Conjg(phi[j]),der[j]));
            mom2=Cadd(mom2,Cmul(Cmul(Conjg(phi[j]),Conjg(phi[j])),der2[j]));
            
            Ec=Csub(Ec,Cmul(Conjg(phi[j]),der2[j]));
            
            Ep=Ep+V[j]*pow(Cabs(phi[j]),2);
            
            Et=Cadd(Et,Cmul(Conjg(phi[j]),(Cadd(RCmul(-1.0,der2[j]),RCmul(V[j],phi[j])))));
            //Et2=Cadd(Et,Cmul(Cmul(Conjg(phi[j]),(Cadd(RCmul(-1.0,der2[j]),RCmul(V[j],phi[j])))),Cmul(Conjg(phi[j]),(Csub(RCmul(-1.0,der2[j]),RCmul(V[j],phi[j]))))));
            
            
            
        }
        //Escribimos en un fichero la medida de los observables obtenidos
        dx=sqrt(-pos*pos+pos2);
        fprintf(posicion,"%i \t %le \t %le \n",i,pos,dx);
        
        mom=Cmul(Complex(0.0,-1.0),mom);
        dp=sqrt(-Real(mom)*Real(mom)+Real(Et));
        fprintf(momento,"%i \t %le \t %le \n",i,Real(mom),dp);
        
        dEt=sqrt(-Real(Et)*Real(Et)+Real(Et2));
        fprintf(etotal,"%i \t %le \n",i,Real(Et));
        
        fprintf(ecin,"%i \t %le \n",i,Real(Ec));
        
        fprintf(epot,"%i \t %le \n",i,Ep);

    }

    fclose(pot);
    fclose(sch);
    fclose(momento);
    fclose(posicion);
    fclose(etotal);
    fclose(ecin);
    fclose(epot);
    
    
    return 0;
}



