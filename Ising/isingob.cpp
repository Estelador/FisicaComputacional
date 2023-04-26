#include <iostream>
#include <cmath>
#include<cstdlib>
#include<ctime>
#include<fstream>

using namespace std;

int main(void){
    //Definom las variables a utilizar
    int F,C,M,i,j,n,m,N,a,b,k,l;
    double T,p,e,E;
    //Defino las variables necesarias para los numeros aleatorios
    double numero1,real;
    //defino fich salida
    ofstream fich;
    //Defino la matriz de los spines como FxC
    double mat[F][C];
    


    //Pido la dimensión de la matriz por teclado
    cout<<"¿Cuántas filas y columnas quieres que tenga la cuadrícula?"<<endl;
    cin>>F;

    C=F;

    //Pido la temperatura T
    cout<<"¿Cuál es el valor de la temperatura? (Ten en cuenta que solo son válidos valores entre 0 y 5)"<<endl;
    cin>>T;

    //Pido el número de veces que quiero hacer Montecarlo
    cout<<"¿Cuántas representaciones de la cuadrícula quieres obtener?"<<endl;
    cin>>N;

    //Inicializo el valor de la serie de números aleatorios
    srand(time(NULL));

    //Config inic de spines
    for(i=0;i<F;i++){
        for(j=0;j<C;j++){
            mat[i][j]=pow((-1),(rand()));
        }
    }


    fich.open("isingdatos.txt");
    
//Ciclo grande Ising
for(a=0;a<N;a++){


     //Imprimo spines
    for(k=0;k<F;k++){
        for(l=0;l<C;l++){
            fich<<mat[k][l]<<" ";
            }
            fich<<endl;
        }
        fich<<endl<<endl;

    //Ciclo de Montecarlo N^2
    M=F*F;
    for(b=0;b<M;b++){

        //Elegir un punto al azar de la red
        n=rand()%(F);
        m=rand()%(C);

        //Evaluar p
        //Calculo la exponencial
        if((n==0)&&(m==0)){
            E=(2*mat[n][m])*(mat[n+1][m]+mat[F-1][m]+mat[n][m+1]+mat[n][C-1]);
        }
        if((n==F-1)&&(m==C-1)){
            E=(2*mat[n][m])*(mat[0][m]+mat[n-1][m]+mat[n][0]+mat[n][m-1]);
        }
    
        if((n==0)&&(m!=0)&&(m!=C-1)){
            E=(2*mat[n][m])*(mat[n+1][m]+mat[F-1][m]+mat[n][m+1]+mat[n][m-1]);
        }

        if((n!=0)&&(n!=F-1)&&(m==0)){
            E=(2*mat[n][m])*(mat[n+1][m]+mat[n-1][m]+mat[n][m+1]+mat[n][C-1]);
        }

        if((n==F-1)&&(m==0)){
            E=(2*mat[n][m])*(mat[0][m]+mat[n-1][m]+mat[n][m+1]+mat[n][C-1]);
        }

        if((n==F-1)&&(m!=0)&&(m!=C-1)){
            E=(2*mat[n][m])*(mat[0][m]+mat[n-1][m]+mat[n][m+1]+mat[n][m-1]);
        }

        if((n!=0)&&(n!=F-1)&&(m==C-1)){
            E=(2*mat[n][m])*(mat[n+1][m]+mat[n-1][m]+mat[n][0]+mat[n][m-1]);
        }

        if((n==0)&&(m==C-1)){
            E=(2*mat[n][m])*(mat[n+1][m]+mat[F-1][m]+mat[n][0]+mat[n][m-1]);
        }
    
        else{
            E=(2*mat[n][m])*(mat[n+1][m]+mat[n-1][m]+mat[n][m+1]+mat[n][m-1]);
        }

        e=E/T;

        e=exp(-e);

        //Evalúo p ahora sí
        if(e<1){
        p=e;
        }
        if(e>=1){
         p=1;
        }

        //Generar num aleat uniforme real ∈ [0, 1]
        //Genero el número aleatorio con ayuda de rand
         numero1=rand();
        //Defino el real aleaorio entre 0 y 1
         real= numero1/RAND_MAX;
        //Si real < p entonces cambiar el signo del espin (n, m) i.e. s(n, m) = −s(n, m).
        if(real<p){
            mat[m][n]=-mat[m][n];
        }


    }
        
    
   
}
     fich.close();
    

    return 0;
}