#ifndef HCMM_H
#define HCMM_H

#include <bits/stdc++.h> 
#include "Functions.h"
using namespace std ;

int Mejor(Solution Sn, Solution Sa, vector<Room> Rooms, vector<Constraint> Restricciones);

vector<Solution> GenerarVecindario(Solution Solucion, vector<Entidad> Entidades, vector<Room> Rooms);

Solution BestNeighbour(Solution Sa, vector<Entidad> Entidades, vector<Room> Rooms, vector<Constraint> Restricciones);

#endif