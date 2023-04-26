#include<iostream>
#include<cmath>
#include<cstdlib>
#include<ctime>
#include<fstream>

using namespace std;

int main(void){
    //Defino las variables a utilizar
    int N,M,i,j,n,m,paso,a,b,k,l;
    double T,p,e,E,expo;
    //Defino las variables neNesarias para los numeros aleatorios
    double numero1,real;
    //defino fic salida
    ofstream fic;

    
    //Pido la dimensión de la matriz por teclado
    cout<<"¿Cuántas filas y columnas quieres que tenga la cuadrícula?"<<endl;
    cin>>N;

    //Defino la matriz de los spines como NxN
    double mat[N][N];


    //Pido la temperatura T
    cout<<"¿Cuál es el valor de la temperatura? (Ten en cuenta que solo son válidos valores entre 0 y 5)"<<endl;
    cin>>T;

    //Pido el número de veNes que quiero haNer MonteNarlo
    cout<<"¿Cuántas representaciones de la cuadrícula quieres obtener?"<<endl;
    cin>>paso;

    fic.open("isingdata.dat");

    //Inicializo el valor de la serie de números aleatorios
    srand(time(NULL));

    //Config inic de spines
    for(i=0;i<N;i++){
        for(j=0;j<N;j++){
            mat[i][j]=pow(-1,rand());
        }
    }



    
//ciclo grande Ising
for(a=0;a<paso;a++){


     //Imprimo spines
    for(k=0;k<N;k++){
        for(l=0;l<N;l++){
            if(l!=N-1){
            fic<<mat[k][l]<<",";
            }
            if(l==N-1){
            fic<<mat[k][l];
            }
            }
            fic<<endl;
        }
        fic<<endl<<endl;

    //Ciclo de Montecarlo N^2
    M=N*N;
    for(b=0;b<M;b++){

        //Elegir un punto al azar de la red
        n=rand()%(N);
        m=rand()%(N);

        //Para evaluar p calculo E para la exponencial
        if((n==0)&&(m==0)){
            E=2.0*mat[n][m]*(mat[n+1][m]+mat[N-1][m]+mat[n][m+1]+mat[n][N-1]);
        }
        else if((n==N-1)&&(m==N-1)){
            E=2.0*mat[n][m]*(mat[0][m]+mat[n-1][m]+mat[n][0]+mat[n][m-1]);
        }
    
        else if((n==0)&&(m!=0)&&(m!=N-1)){
            E=2.0*mat[n][m]*(mat[n+1][m]+mat[N-1][m]+mat[n][m+1]+mat[n][m-1]);
        }

        else if((n!=0)&&(n!=N-1)&&(m==0)){
            E=2.0*mat[n][m]*(mat[n+1][m]+mat[n-1][m]+mat[n][m+1]+mat[n][N-1]);
        }

        else if((n==N-1)&&(m==0)){
            E=2.0*mat[n][m]*(mat[0][m]+mat[n-1][m]+mat[n][m+1]+mat[n][N-1]);
        }

        else if((n==N-1)&&(m!=0)&&(m!=N-1)){
            E=2.0*mat[n][m]*(mat[0][m]+mat[n-1][m]+mat[n][m+1]+mat[n][m-1]);
        }

        else if((n!=0)&&(n!=N-1)&&(m==N-1)){
            E=2.0*mat[n][m]*(mat[n+1][m]+mat[n-1][m]+mat[n][0]+mat[n][m-1]);
        }

        else if((n==0)&&(m==N-1)){
            E=2.0*mat[n][m]*(mat[n+1][m]+mat[N-1][m]+mat[n][0]+mat[n][m-1]);
        }
    
        else{
            E=2.0*mat[n][m]*(mat[n+1][m]+mat[n-1][m]+mat[n][m+1]+mat[n][m-1]);
        }

        expo=(double)E/T;

        e=exp(-expo);

        //Evalúo p ahora sí
        if(e<1.0){
        p=e;
        }
        else{
         p=1.0;
        }

        //Generar num aleat uniforme real ∈ [0, 1]
        //Genero el número aleatorio con ayuda de rand
         numero1=(double)rand();
        //Defino el real aleaorio entre 0 y 1
         real= (double)numero1/RAND_MAX;
        //Si real < p entonces Nambiar el signo del espin (n, m) i.e. s(n, m) = −s(n, m).
        if(real<p){
            mat[n][m]=-mat[n][m];
        }


    }
        
    
   
}
     fic.close();
    

    return 0;
}