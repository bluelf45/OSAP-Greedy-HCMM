#include "HCMM.h"
#include "Functions.h"
#include <bits/stdc++.h> // importa todo
using namespace std ;
int Mejor(Solution Sn, Solution Sa, vector<Room> Rooms, vector<Constraint> Restricciones){
    float Nn = Penalizacion(Restricciones, Sn, Rooms) + UsagePenalty(Sn);
    float Na = Penalizacion(Restricciones, Sa, Rooms) + UsagePenalty(Sa);
    if(Nn <= Na){
        return -2;
    }
    if( Nn == -1){
        return -1;
    }
    //En caso de que las restricciones duras se cumplan y la penalizacion sea menor que el minimo anterior, se asignara la nueva penalizacion
    if(Nn > Na){
        return Nn;
    }
    return -1;
}
//Solucion->Desicion ->[RoomEnt0, RoomEnt1, ...., RoomEntN]
vector<Solution> GenerarVecindario(Solution Solucion, vector<Entidad> Entidades, vector<Room> Rooms){
    //SWAP
    vector<Solution> Vecindario;
    //Tal vez randomizar?
    for (int i =0; i < int(Entidades.size())/2; i++){
        //Guardar informacion para programar mas facil
        Solution temp = Solucion;
        int Entidad1 = i;
        int Entidad2 = i+1;
        int aux1 = temp.Decision[Entidad1];//ID habitacion [i]
        int aux2 = temp.Decision[Entidad2];//ID habitacion [i + 1]
        //Realizar el swap
        temp.SpaceXRoom[aux1] += Entidades[Entidad1].space;
        temp.SpaceXRoom[aux2] += Entidades[Entidad2].space;
        temp.Decision[Entidad1] = aux2;
        temp.Decision[Entidad2] = aux1;
        temp.SpaceXRoom[aux2] -= Entidades[Entidad1].space;
        temp.SpaceXRoom[aux1] -= Entidades[Entidad2].space;

        Vecindario.push_back(temp);
    }
    return Vecindario;
}
Solution BestNeighbour(Solution Sa, vector<Entidad> Entidades, vector<Room> Rooms, vector<Constraint> Restricciones){
    //Generar Vecindario
    vector<Solution> Vecindario;
    Vecindario = GenerarVecindario(Sa, Entidades, Rooms);
    //Buscar Mejor solucion.
    Solution BestSolution = Vecindario[0];
    for(int i = 1; i<int(Vecindario.size()); i++){
        int N = Mejor(Vecindario[i], BestSolution, Rooms, Restricciones);
        if(N > -1){
            BestSolution = Vecindario[i];
        }
    }
    return BestSolution;
}