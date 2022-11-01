#include <bits/stdc++.h> // importa todo
#include "Functions/Functions.h"
#include <algorithm>
using namespace std ;

bool FLAG(Solution Sol){
    for(int i = 0; i<int(Sol.Decision.size()); i++){
        if (Sol.Decision[i] == -1 || Sol.Decision[i] == 0){
            return false;
        }
    }
    return true;
}
bool CompareById(const Entidad &a, const Entidad &b)
{
    return a.id < b.id;
}
tuple<int, int> BadUsedSpace(Solution Sol){
    int NU = 0;
    int SU = 0;
    for(int i =0; i<int(Sol.SpaceXRoom.size()); i++){
        if (Sol.BadSoftCons[i] > 0){
            NU += Sol.BadSoftCons[i];
        }else{
            SU += Sol.BadSoftCons[i];
        }
    }
    return make_tuple(NU, SU);
}

int main () {
    // Aumenta la velocidad del cout y del cin
    ios_base :: sync_with_stdio ( false ) ;
    cin . tie ( NULL ) ;
    cout . setf ( ios :: fixed ) ;
    //Apertura del texto de Instancia con los datos
    fstream Instancia;//Archivo Instancia
    string PATH = "Instancias/Instancias_OSAP/";//Path a la carpeta con las Instancias
    string NombreInstancia = "nott1";//Nombre del txt de las instancias
    Instancia.open(PATH+NombreInstancia + ".txt", ios::in);//Apertura de Instancia
    if(Instancia.is_open()){
        cout << ">>>Instancia Abierta<<<\n";
    }else{
        cout << "Error en apertura de archivo";
        return 1;
    }
    string Linea;//String para leer las lineas del archivo
    vector <int> Cantidades; //Entidades | Rooms | Floors | Constraints | Hard Constraints | Soft Constraints
    vector <Entidad> Entidades; // Vector de Entidades
    vector <Room> Rooms; // Vector de Habitaciones
    vector <Constraint> HardConstraints;//Vector de Restricciones
    vector <Constraint> Constraints;//Vector de Restricciones
    int Type = 0; // 0 = Cantidades | 1 = Entidades | 2 = Habitaciones | 3 = Restricciones
    //Variables temporales para agregarlas a los Vectores
    Entidad temp;
    Room tempRoom;
    Constraint tempCons;
    //Lectura y Almacenamiento del Problema
    while(getline(Instancia, Linea)){
        //Separate String by spaces
        stringstream ss(Linea);
        istream_iterator<string> begin(ss);
        istream_iterator<string> end;
        vector<string> tokens(begin, end);
        //Almacenamiento de Inputs en diferentes vectores para facilidad de uso.
        if(!tokens.empty()){
            if (Type == 0){
                if(tokens[0].compare("ENTITIES") == 0){
                    Type++;

                }else{
                    Cantidades.push_back(stoi(tokens[1]));
                }
            }else if (Type == 1){
                if(tokens[0].compare("ROOMS") == 0){
                    Type++;

                }else{
                    temp.id = stoi(tokens[0]);
                    temp.group_id = stoi(tokens[1]);
                    temp.space = stoi(tokens[2]);
                    Entidades.push_back(temp);
                }
            }else if (Type == 2) {
                if(tokens[0].compare("CONSTRAINTS") == 0){
                    Type++;

                }else{
                    tempRoom.id = stoi(tokens[0]);
                    tempRoom.floor = stoi(tokens[1]);
                    tempRoom.capacity = stoi(tokens[2]);
                    tempRoom.tam_LA = stoi(tokens[3]);
                }
                for( long unsigned int i = 4; i < tokens.size(); i++){
                    tempRoom.Adjacent.push_back(stoi(tokens[i]));
                }
                Rooms.push_back(tempRoom);
            }else if(Type == 3){
                tempCons.id = stoi(tokens[0]);
                tempCons.Type = stoi(tokens[1]);
                tempCons.Soft_Hard = stoi(tokens[2]);
                tempCons.Param1 = stoi(tokens[3]);
                tempCons.Param2 = stoi(tokens[4]); 
                Constraints.push_back(tempCons);
            }
        }
    }
    cout << "Entidades: " << Cantidades[0]<< endl;
    cout << ">>>Instancia Almacenado<<<" << endl;
    Instancia.close();
    //Comenzar a trabajar en la solucion Inicial
    Solution Output;
    time_t start, end;
    cout << ">>>Solucion Inicial Iniciada<<<" << endl;
    //Funcion Miope -> siguiente Entidad en ID
    //Punto Partida -> Entidad con ID 0
    //Funcion de Evaluacion -> Cumplir con Restriccion Fuerte
    //Cumpliendo siempre ALL_ALLOCATED
    int R;
    //Inicio tiempo de ejecucion
    time(&start);
    //While Principal de Greedy
    while(FLAG(Output)){    
        for (int i = 0; i < Cantidades[0]; i++){
            Output.Decision.push_back(-1);
        }
        for (int j = 0; j< Cantidades[1]; j++){
            Output.SpaceXRoom.push_back(int(Rooms[j].capacity));
        }
        //Ordenar Entidades en esta linea pero no se como hacerlo aun ayuda
        random_shuffle(Entidades.begin(), Entidades.end());
        //Buscar los optimos locales
        for(int i = 0; i<Cantidades[0]; i++){
            R = BestLocalRoom(Constraints, Output, Rooms, Entidades[i]);
            //asignar habitacion a la Entidad
            if(R == -1){
                Output.Decision.clear();
                Output.SpaceXRoom.clear();
                break;
            }
            Output.Decision[i] = R;
            Output.SpaceXRoom[R] -= Entidades[i].space;
        }
    }
    //Calcular el tiempo de ejecucion
    time(&end);
    double time_taken = double(end - start);
    cout << "Tiempo de Ejecucion: " << fixed
         << time_taken << setprecision(5);
    cout << " segundos " << endl; 
    cout << ">>>Solucion Inicial Creada<<<" << endl;
    //volver a ordenar las entidades por orden de ID
    sort(Entidades.begin(), Entidades.end(), CompareById);
    //Encontrar Restricciones blandas que no se cumplieron
    for(int i = 0; i < int(Constraints.size()); i++){
        if(Constraints[i].Soft_Hard == 0){
            Output.BadSoftCons.push_back(Constraints[i].id);
        }
    }
    //Generar Archivo de Salida OUTPUT.out
    //Formato segun lo acordado en el Informe
    ofstream OUTPUT;
    OUTPUT.open(NombreInstancia+".out", ios::out);
    OUTPUT << to_string(int(Output.BadSoftCons.size())) << " ";
    for(int i = 0; i<int(Output.BadSoftCons.size()); i++){
        OUTPUT << to_string(Output.BadSoftCons[i]) << " ";
    }
    OUTPUT << endl;
    int NU, SU;
    tie(NU, SU) = BadUsedSpace(Output);
    OUTPUT << to_string(NU - SU)<< " " << to_string(NU) << " " <<  to_string(SU) <<endl;
    for(int i = 0; i < int(Rooms.size()) - 1; i++){
        OUTPUT << to_string(i) << " ";
        if(Output.SpaceXRoom[i] > 0){//NU
            OUTPUT << to_string(Output.SpaceXRoom[i]) << " 0";
        }else{
            OUTPUT  << "0 "<< to_string(-Output.SpaceXRoom[i]);
        }
        OUTPUT << " "<<to_string(count(Output.Decision.begin(), Output.Decision.end(), i))<< " ";
        for(int j = 0; j< int(Output.Decision.size()); j++){
            if(Output.Decision[j] == i){
                OUTPUT << to_string(j) << " ";
            }
        }
        OUTPUT << endl;
    }
    OUTPUT.close();
    //HILL CLIMBING *PROXIMAMENTE*
    return 0;
}

