#include "Functions.h"
#include <bits/stdc++.h> // importa todo
using namespace std ;

//Restriccion de que la entidad 1(Cons.Param1) este alojada en la habitacion(Cons.Param2)
int Allocation(Solution Sol, Constraint Cons){//0
    if (Sol.Decision[Cons.Param1] == Cons.Param2) {
        return 0;
    }
    return 1;
}

//Restriccion de que la entidad 1(Cons.Param1) no este alojada en la habitacion(Cons.Param2)
int No_Allocation(Solution Sol, Constraint Cons){//1
    if (Sol.Decision[Cons.Param1] != Cons.Param2) {
        return 0;
    }else if(Sol.Decision[Cons.Param1] == Cons.Param2){
        return 1;
    }
    return 1;
}

//Asegurarse de que todas las habitaciones esten en una habitacion
int All_Allocated(Solution Sol){//2
    for(int i =0; i< int(Sol.Decision.size()); i++){
        if (Sol.Decision[i] == -1){
            return 1;
        }
    }
    return 0;
}

//Restriccion de que la capacidad de la Habitacion(Cons.Param1) no sea menor a 0, o sea, que no este sobreusada
int Capacity(Solution Sol, Constraint Cons){//3
    if(Sol.SpaceXRoom[Cons.Param1] < 0){
        return 1;
    }else{
        return 0;
    }
}

//Checkear que la Entidad 1(Cons.Param1) este en la misma habitacion de Entidad 2(Cons.Param2)
int Same_Rooms(Solution Sol, Constraint Cons){//4
    if(Sol.Decision[Cons.Param1] == -1 || Sol.Decision[Cons.Param1] == -1){
        return 0;
    }
    if (Sol.Decision[Cons.Param1] == Sol.Decision[Cons.Param2]){
        return 0;
    }
    return 1;
}

//Checkear que la Entidad 1(Cons.Param1) este en una habitacion diferente de Entidad 2(Cons.Param2)
int Dif_Rooms(Solution Sol, Constraint Cons){//5
    if(Sol.Decision[Cons.Param1] == -1 || Sol.Decision[Cons.Param1] == -1){
        return 0;
    }
    if (Sol.Decision[Cons.Param1] != Sol.Decision[Cons.Param2]){
        return 0;
    }
    return 1;
}

//Revisa el Arreglo de la solucion para asegurarse de que no se compartan los IDs de las Habitaciones
int Not_Sharing(Solution Sol, Constraint Cons){//6
    if(Sol.Decision[Cons.Param1] == -1){
        return 0;
    }
    for(int i = 0; i < int(Sol.Decision.size()); i++){
        if((Sol.Decision[Cons.Param1] == Sol.Decision[i]) && (i!=Cons.Param1)){
            return 1;
        }
    }
    return 0;
}

//R1 Habitacion entidad 1/R2 Habitacion Entidad 2
//Revisa la lista de Adjacencia de la Habitacion 2 para saber si la habitacion 1 es Adjacente
int Adjacency(Solution Sol, vector<Room> Rooms, int Param1, int Param2){//7
    if(Sol.Decision[Param1] == -1 || Sol.Decision[Param2] == -1){
        return 0;
    }
    Room R1 = Rooms[Sol.Decision[Param1]];
    Room R2 = Rooms[Sol.Decision[Param2]];
    for (int i=0; i<int(R2.Adjacent.size()); i++){
        if(R1.id==R2.Adjacent[i]){
            return 0;
        }
    }
    return 1;
}

//Reviasr que las entidades esten en habitaciones cercanas, tal que las habitaciones esten en el mismo piso
int Nearby(Solution Sol, Constraint Cons, vector<Room> Rooms){//8
    if(Sol.Decision[Cons.Param1] == -1 || Sol.Decision[Cons.Param2] == -1){
        return 0;
    }
    else{
        if(Rooms[Sol.Decision[Cons.Param1]].floor == Rooms[Sol.Decision[Cons.Param2]].floor){
            return 0;
        }
        return 1;
    }
}

//Reviasr que las entidades esten en habitaciones Lejanas, tal que las habitaciones NO esten en el mismo piso
int AwayFrom(Solution Sol, Constraint Cons, vector<Room> Rooms){//9
    if(Sol.Decision[Cons.Param1] == -1 || Sol.Decision[Cons.Param2] == -1){
        return 0;
    }
    else{
        if(Rooms[Cons.Param1].floor != Rooms[Cons.Param2].floor){
            return 0;
        }
        return 1;
    }
}

//Penalizacion de cada tipo de restriccion
int ConsPen(int type){
    int n = 0;
    switch(type){
        case 0:
            return 20;
        case 1:
            return 10;
        case 2:
            break;
        case 3:
            return  10;
        case 4:
            return  10;
        case 5:
            return  10;
        case 6:
            return  50;
        case 7:
            return  10;
        case 8:
            return 10;
        case 9:
            return 10;
    }
    return n;   
}

//Switch case que selecciona que Funcion de Restriccion a de llamar
int Restricciones(Solution Sol, Constraint Cons, vector<Room> Rooms){
    int n = 0;
    switch(Cons.Type){
        case 0:
            n=Allocation(Sol, Cons);
            break;
        case 1:
            n=No_Allocation(Sol, Cons);
            break;
        case 2:
            break;
        case 3:
            n=Capacity(Sol, Cons);
            break;
        case 4:
            n=Same_Rooms(Sol, Cons);
            break;
        case 5:
            n=Dif_Rooms(Sol, Cons);
            break;
        case 6:
            n=Not_Sharing(Sol, Cons);
            break;
        case 7:
            n=Adjacency(Sol, Rooms, Cons.Param1, Cons.Param2);
            break;
        case 8:
            n=Nearby(Sol, Cons, Rooms);
            break;
        case 9:
            n=AwayFrom(Sol, Cons, Rooms);
            break;
    }
    return n;
    //int true = 1 / false = 0;
}

//(Funcion Objetivo) Sumatoria de las penalizaciones de las restricciones 
int Penalizacion(vector<Constraint> Cons, Solution Sol, vector<Room> Rooms) {
    int suma = 0;
    int N;
    for (int i =0; i<int(Cons.size()); i++){
        N = Restricciones(Sol, Cons[i], Rooms);
        if(N == -1 && Cons[i].Soft_Hard == 1){
            return -1;
        }
        suma += (ConsPen(Cons[i].Type) * N);
    }
    return suma;
}

//Seleccionar la mejor habitacion segun la menor penalizacion que conlleva el seleccionar tal habitacion
int BestLocalRoom(vector<Constraint> Restricciones, Solution Solucion, vector<Room> Rooms, Entidad Ent){//Buscar Habitacion con menos penalizacion
    int Minimo = 3000000;
    int BestRoom;
    int N;
    for(int i = 0; i< int(Rooms.size()); i++){
        //Instanciar Habitacion para probar las restricciones
        Solucion.Decision[Ent.id] = Rooms[i].id;
        Solucion.SpaceXRoom[Rooms[i].id] -= Ent.space;
        N = Penalizacion(Restricciones, Solucion, Rooms);
        if( N == -1){
            return -1;
        }
        //En caso de que las restricciones duras se cumplan y la penalizacion sea menor que el minimo anterior, se asignara la nueva penalizacion
        if(N != -1){
            if(Minimo > N){
                Minimo = N;
                BestRoom = i;
            }
        }
    }
    return BestRoom;
}
