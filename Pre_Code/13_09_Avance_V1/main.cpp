#include <iostream>
#include "motorDeBits.h"
#include "manejoMemoria.h"

using namespace std;

const int FILAS = 0;
const int COLUMNAS = 1;
const int BYTESRESERVADOS = 2;

int main(){

    int estadoJuego[3] = {0};

    cout<<"Ingrese la cantidad de filas del tablero: "<<endl;cin>>estadoJuego[FILAS];
    cout<<"Ingrese la cantidad de columnas del tablero: "<<endl;cin>>estadoJuego[COLUMNAS];

    cout << "Creando tablero de " << estadoJuego[FILAS] << "x" << estadoJuego[COLUMNAS] << endl;

    unsigned char* tablero = inicializarTablero(estadoJuego);

    int totalFichas = estadoJuego[FILAS] * estadoJuego[COLUMNAS];
    int bitsNecesitados = totalFichas * 3;

    cout<<"Total de fichas: "<<totalFichas<<endl;
    cout<<"Bits requeridos: "<<bitsNecesitados<<endl;
    cout<<"Bytes reservados: "<<estadoJuego[BYTESRESERVADOS]<<endl;

    delete[] tablero;
    cout<<"Memoria liberada"<<endl;

    return 0;
}