#ifndef FUNCTION_H
#define FUNCTION_H

#include <bits/stdc++.h> 
using namespace std ;
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
};
struct Solution{
    vector<vector<int>> Decision;//Rooms x Entities
    vector<int> NonUsedSpace; //Espacio no utilizado por habitacion, ordenado segun id
    vector<int> OverUsedSpace;//Espacio Sobre utilizado por habitacion, ordenado segun id
    vector<int> nEh; //Numero Entidades en habitacion indice
}

bool All_Allocated(Solution Sol, int E, int R);//Todas las entidades Asignadas
bool Allocation(Solution Sol, Entidad E, Room R);
bool No_Allocation(Solution Sol, Entidad E, Room R);
bool Dif_Rooms(Solution Sol, Entidad E1, Entidad E2, Room R);
bool Same_Rooms(Solution Sol, Entidad E1, Entidad E2, Room R):
bool Not_Sharing(Solution Sol, Entidad E, Room R, int Entities);
void Adjacency();
void Nearby();
void AwayFrom();
void Capacity();

#endif