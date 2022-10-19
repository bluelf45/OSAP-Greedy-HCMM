#include <bits/stdc++.h> // importa todo
using namespace std ;
struct Entidad{
    int id;
    int group_id;
    int space;
};
struct Room{
    int id;
    int floor;
    int capacity;
    int tam_LA;
    vector<int> Adjacent;
};
struct Constraint{
    int id;
    int Type;
    int Soft_Hard;
    int Param1;
    int Param2;
};

int main () {
    // Aumenta la velocidad del cout y del cin
    ios_base :: sync_with_stdio ( false ) ;
    cin . tie ( NULL ) ;
    cout . setf ( ios :: fixed ) ;
    //Apertura del texto de Instancia con los datos
    fstream Instancia;
    string NombreInstancia = "s100_v100.txt";
    Instancia.open(NombreInstancia, ios::in);
    if(Instancia.is_open()){
        cout << ">>>Instancia Abierta<<<\n";
    }else{
        cout << "Error en apertura de archivo";
        return 1;
    }
    string Linea;
    vector <int> Cantidades; //Entidades | Rooms | Floors | Constraints | Hard Constraints | Soft Constraints
    vector <Entidad> Entidades; // Array de Entidades
    vector <Room> Rooms; // Array de Habitaciones
    vector <Constraint> Constraints;
    int Type = 0; // 0 = Cantidades | 1 = Entidades | 2 = Habitaciones | 3 = Restricciones
    Entidad temp;
    Room tempRoom;
    Constraint tempCons;
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
                for( int i = 4; i < tokens.size(); i++){
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
    cout << ">>>Problema Almacenado<<<" << endl;
    return 0;
}
