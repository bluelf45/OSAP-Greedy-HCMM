#ifndef FUNCTION_H
#define FUNCTION_H

#include <bits/stdc++.h> 
using namespace std ;
//Codigos Comentados en Functions.cpp
struct Entidad{//Struct para guardar Informacion de Entidades
    int id;
    int group_id;
    int space;
};
struct Room{//Struct para guardar Informacion de Habitaciones
    int id;
    int floor;
    int capacity;
    int tam_LA;
    vector<int> Adjacent;
};
struct Constraint{//Struct para guardar Informacion de Restricciones
    int id;
    int Type;
    int Soft_Hard;
    int Param1;
    int Param2;
    int Cumplimiento;
};
struct Solution{//Struct de la Solucion
    vector<int>Decision;//Entidad es la id, valor es la id de la habitacion
    vector<int>SpaceXRoom; //Espacio Usado en cada Habitacion
    vector<int>BadSoftCons;
};

int Allocation(Solution Sol, Constraint Cons);

int No_Allocation(Solution Sol, Constraint Cons);

int All_Allocated(Solution Sol);//Todas las entidades Asignadas

int Capacity(Solution Sol, Constraint Cons);

int Same_Rooms(Solution Sol, Constraint Cons);

int Dif_Rooms(Solution Sol, Constraint Cons);

int Not_Sharing(Solution Sol, Constraint Cons);

int Adjacency(Solution Sol, vector<Room> Rooms, int Param1, int Param2);

int Nearby(Solution Sol, Constraint Cons, vector<Room> Rooms);

int AwayFrom(Solution Sol, Constraint Cons, vector<Room> Rooms);

int ConsPen(int type);

int Restricciones(Solution Sol, Constraint Cons, vector<Room> Rooms, int i);

int Penalizacion(vector<Constraint> Restricciones, Solution Sol, vector<Room> Rooms);

int BestLocalRoom(vector<Constraint> Restricciones, Solution Solucion, vector<Room> Rooms, Entidad Ent);

#endif