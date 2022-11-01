#include "HCMM.h"
#include <bits/stdc++.h> // importa todo
using namespace std ;
int Mejor(int Sn, int Sc){
    return 1;
}
int Random(Solution Solucion){
    srand(time(0));
    return rand(int(Solucion.Decision.size()));
}
int BestQualityPoint(int Sc){
    return 1;
}
int HillClimbing(Solution Solucion){
    bool local = false;
    int Sc = Random(Solucion);
    while(!local){
        Sn = BestQualityPoint(Sc);
        if(Mejor(Sn, Sc)){
            Sc = Sn;
        }
        else{
            local = true;
        }
    }
    return Sc;
}