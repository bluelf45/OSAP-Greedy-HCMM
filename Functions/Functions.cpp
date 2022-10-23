#include "Functions.h"
#include <bits/stdc++.h> // importa todo
using namespace std ;

bool All_Allocated(Solution Sol, int Ent, int Rooms){
    int sum;
    for(int i = 0; i<Ent; i++){
        sum = 0;
        for(int j = 0; j<Rooms; j++){
            if (Sol.Decision[j][i] ==1) {
                sum++;
            }
        }
        if(sum > 1 || sum == 0){
            return false;
        }
    }
    return true;
}

bool Allocation(Solution Sol, Entidad E, Room R){
    if (Sol.Decision[R.id][E.id] == 1) {
        return true;
    }else {
        return false;
    }
}
bool No_Allocation(Solution Sol, Entidad E, Room R){
    if (Sol.Decision[R.id][E.id] == 0) {
        return true;
    }else {
        return false;
    }
}
bool Dif_Rooms(Solution Sol, Entidad E1, Entidad E2, Room R){
    if((Sol.Decision[R.id][E1.id] == 1 && Sol.Decision[R.id][E2.id] != 1) || (Sol.Decision[R.id][E1.id] != 1 && Sol.Decision[R.id][E2.id] == 1)){
        return true;
    }else{
        return false;
    }
}
bool Same_Rooms(Solution Sol, Entidad E1, Entidad E2, Room R){
    if(Sol.Decision[R.id][E1.id] == 1 && Sol.Decision[R.id][E2.id] == 1){
        return true;
    }else{
        return false;
    }
}
bool Not_Sharing(Solution Sol, Entidad E, Room R, int Entities){
    int suma = 0;
    for (int i = 0 ; i < Entities ; i++){
        suma += Sol.Decision[R.id][i];
    }
    if (suma <= 1){
        return true;
    }else{
        return false;
    }
}

//R1 Habitacion entidad 1/R2 Habitacion Entidad 2
bool Adjacency(Solution Sol,Room R1, Room R2){
    for (int i = 0; i<R2.size(); i++){
        if (R1.id == R2.Adjacent[i]{
            return true
        })
    }
    return false;
}
//void Nearby();
//void AwayFrom();
void Capacity(Solution Sol, Room R1, vector<Entidad> Entidades){
    int sum;
    for (int i = 0; i < ; i++){
        sum+= Sol[R1.id][i] * Entidades[i].space;
    }
    if(sum > R1.capacity){
        return false;
    }else{
        return true;
    }
}