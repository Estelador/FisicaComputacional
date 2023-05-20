#include<iostream>
#include<cmath>
#include<fstream>

using namespace std;

//defino mis constantes
#define G 6.67e-11
#define Ml 0.07349e24
#define Mt 5.9736e24
#define dtl 3.844e8
#define w 2.6617e-6
#define Rt 6.378160e6
#define Rl 1.7374e6
#define pasos 450000

//defino las funciones a utilizar
double punto_r(double r_c, double phi_c, double p_phi, double t);
double punto_phi(double r_c, double phi_c, double t);

int main(void){

    //defino mis variables a utilizar
    int i;
    double m,v_esc,theta,h,r_c,phi_c,r_l,phi_l,p_r,p_phi,v,k[4][4];
    ofstream pos,Hprima;

    //pido masa cohete
    cout<<"¿Cual es la masa del cohete?"<<endl;
    cin>>m;

    //pido angulo cohete
    cout<<"¿Con qué ángulo quiere que despegue el cohete respecto al eje x?"<<endl;
    cin>>theta;

    //pido velocidad cohete
    cout<<"¿Con qué velocidad quiere que despegue el cohete? (recuerda que la velocidad de escape es 11200 m/s)"<<endl;
    cin>>v_esc;

    //pido paso
    cout<<"¿De cuanto quiere el paso temporal?"<<endl;
    cin>>h;

    //inicializo parámetros
    r_l=dtl;
    phi_l=0.0;
    r_c=Rt;
    phi_c=0.0;
    v=v_esc;

    //reescalo
    r_l=r_l/(1.0*dtl);
    r_c=r_c/(1.0*dtl);
    v=v/(1.0*dtl);

    //defino las p
    p_r=v*cos(theta);
    p_phi=r_c*v*sin(theta);

    pos.open("planets_data.dat");
    Hprima.open("hprima.dat");

    for(i=0;i<pasos;i++){

        //escribo posiciones cada 200 pasos y la H prima
        if((i%500)==0){
            pos<<"0.0, 0.0"<<endl<<r_c*cos(phi_c)<<", "<<r_c*sin(phi_c)<<endl<<r_l*cos(w*i*h*1.0)<<", "<<r_l*sin(w*i*h*1.0)<<endl<<endl;
            Hprima<<(p_r*p_r/2.0)+(p_phi*p_phi/(2.0*r_c*r_c))-((G/(dtl*dtl*dtl))*((Mt/r_c)+(Ml/(sqrt(1.0+r_c*r_c-2.0*r_c*cos(phi_c-1.0*w*i*h))))))<<endl;
        }

        //evaluo los k (primera coordenada es el superindice y la segunda indica de que magnitud es, r, phi, p_r o p_phi)
        k[0][0]=h*p_r;
        k[0][1]=h*p_phi/(r_c*r_c);
        k[0][2]=h*punto_r(r_c, phi_c, p_phi, i*h);
        k[0][3]=h*punto_phi(r_c, phi_c, i*h);

        k[1][0]=h*(p_r+k[0][2]/2.0);
        k[1][1]=h*(p_phi+k[0][3]/2.0)/(((r_c+k[0][0]/2.0)*(r_c+k[0][0]/2.0)));
        k[1][2]=h*punto_r(r_c+ k[0][2]/2.0, phi_c + k[0][1]/2.0, p_phi+ k[0][3]/2.0, i*h);
        k[1][3]=h*punto_phi(r_c+ k[0][0]/2.0, phi_c+k[0][1]/2.0, i*h);

        k[2][0]=h*(p_r+k[1][2]/2.0);
        k[2][1]=h*(p_phi+k[1][3]/2.0)/(((r_c+k[1][0]/2.0)*(r_c+k[1][0]/2.0)));
        k[2][2]=h*punto_r(r_c+ k[1][2]/2.0, phi_c + k[1][1]/2.0, p_phi+ k[1][3]/2.0, i*h);
        k[2][3]=h*punto_phi(r_c+ k[1][0]/2.0, phi_c+k[1][1]/2.0, i*h);

        k[3][0]=h*(p_r+k[2][2]); 
        k[3][1]=h*(p_phi+k[2][3])/(((r_c+k[2][0])*(r_c+k[2][0])));
        k[3][2]=h*punto_r(r_c+ k[2][2], phi_c + k[2][1], p_phi+ k[2][3], i*h);
        k[3][3]=h*punto_phi(r_c+ k[2][0], phi_c+k[2][1], i*h);

        //calculo valores de:
        p_phi= p_phi + (k[0][3]+2.0*k[1][3]+2.0*k[2][3]+k[3][3])/6.0;
        r_c=r_c + (k[0][0]+2.0*k[1][0]+2.0*k[2][0]+k[3][0])/6.0;
        phi_c= phi_c + (k[0][1]+2.0*k[1][1]+2.0*k[2][1]+k[3][1])/6.0;
        p_r= p_r + (k[0][2]+2.0*k[1][2]+2.0*k[2][2]+k[3][2])/6.0;
    }

    pos.close();
    Hprima.close();

    return 0;
}


double punto_r(double r_c, double phi_c, double p_phi, double t){

    double punto_r,DELTA, mu,rprima;

    DELTA=G*Mt/(1.0*dtl*dtl*dtl);
    mu=Ml/(1.0*Mt);
    rprima=sqrt(1.0+r_c*r_c-2.0*r_c*cos(phi_c-1.0*w*t));

    punto_r=p_phi*p_phi/(r_c*r_c*r_c)-DELTA*(1.0/(r_c*r_c)+mu/(rprima*rprima*rprima)*(r_c-cos(phi_c-1.0*w*t)));



    return punto_r;
}

double punto_phi(double r_c, double phi_c, double t){


    double punto_phi,DELTA, mu,rprima;

    DELTA=G*Mt/(1.0*dtl*dtl*dtl);
    mu=Ml/(1.0*Mt);
    rprima=sqrt(1.0+r_c*r_c-2.0*r_c*cos(phi_c-1.0*w*t));

    punto_phi=-DELTA*mu*r_c*sin(phi_c-1.0*w*t)/(rprima*rprima*rprima);



    return punto_phi;
}