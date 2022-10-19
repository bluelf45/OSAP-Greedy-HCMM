#include <bits/stdc++.h> // importa todo
using namespace std ;

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
        cout << "Instancia Abierta\n";
    }else{
        cout << "Error en apertura de archivo";
        return 1;
    }
    string Linea;
    vector <int> Cantidades;
    while(getline(Instancia, Linea)){
        cout << Linea << "\n";
    }
    return 0;
}
