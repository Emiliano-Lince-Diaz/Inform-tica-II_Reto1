#include <iostream>
#include "motorDeBits.h"
#include "manejoMemoria.h"
#include "interfazUsuario.h"
#include "logicaJuego.h"

using namespace std;

const int FILAS = 0;
const int COLUMNAS = 1;
const int BYTESRESERVADOS = 2;
const int MOV_USUARIO = 3;
const int FICHAS_ELIMINADAS = 4;
const int COMBOS = 5;
const int CASCADAS = 6;
const int PUNTOS = 7;
const int TOTAL_ELIMINACIONES = 8;

int main(){

    int estadoJuego[9] = {0};

    mostrarMenuInicio(estadoJuego[FILAS], estadoJuego[COLUMNAS]);

    unsigned char* tablero = inicializarTablero(estadoJuego);

    cout << "Bytes reservados: " << estadoJuego[BYTESRESERVADOS] << endl;

    inicializarSemillaAleatoria(); // Arrancamos el motor de azar
    generarFichasAleatorias(tablero, estadoJuego[FILAS], estadoJuego[COLUMNAS]);

    bool jugando = true;

    while(jugando){

        cout << "\n================== ESTADISTICAS ACTUALES ==================" << endl;
        cout << " Puntaje Total                : " << estadoJuego[PUNTOS] << endl;
        cout << " Movimientos realizados       : " << estadoJuego[MOV_USUARIO] << endl;
        cout << " Total Fichas Eliminadas      : " << estadoJuego[FICHAS_ELIMINADAS] << endl;
        cout << " Total Eliminaciones (Accion) : " << estadoJuego[TOTAL_ELIMINACIONES] << endl;
        cout << " Total de Combos              : " << estadoJuego[COMBOS] << endl;
        cout << " Cascadas Generadas           : " << estadoJuego[CASCADAS] << endl;
        cout << " Tamano actual del Tablero    : " << estadoJuego[FILAS] << "x" << estadoJuego[COLUMNAS] << endl;
        cout << "===========================================================" << endl;

        imprimirTableroFichas(tablero, estadoJuego[FILAS], estadoJuego[COLUMNAS]);

        imprimirTableroBinario(tablero, estadoJuego[FILAS], estadoJuego[COLUMNAS], estadoJuego);

        int opcion = mostrarMenuPartida();

        switch(opcion){
        case OPCION_ELIMINAR_FICHA:
            estadoJuego[MOV_USUARIO]++;
            estadoJuego[TOTAL_ELIMINACIONES]++;
            eliminarFicha(tablero, estadoJuego);
            gravedad(tablero,estadoJuego);
            rellenar(tablero, estadoJuego);
            cout << "\nEvaluando tablero..." << endl;
            funcion_cascadas(tablero, estadoJuego);
            break;

        case OPCION_AGREGAR_FILA:
            estadoJuego[MOV_USUARIO]++;
            tablero=agregarFila(tablero,estadoJuego);
            funcion_cascadas(tablero, estadoJuego);
            break;

        case OPCION_ELIMINAR_FILA:
            estadoJuego[MOV_USUARIO]++;
            estadoJuego[TOTAL_ELIMINACIONES]++;
            tablero=eliminarFila(tablero,estadoJuego);
            funcion_cascadas(tablero, estadoJuego);
            break;

        case OPCION_AGREGAR_COLUMNA:
            estadoJuego[MOV_USUARIO]++;
            tablero = agregarColumna(tablero, estadoJuego);
            funcion_cascadas(tablero, estadoJuego);
            break;

        case OPCION_ELIMINAR_COLUMNA:
            estadoJuego[MOV_USUARIO]++;
            estadoJuego[TOTAL_ELIMINACIONES]++;
            tablero = eliminarColumna(tablero, estadoJuego);
            funcion_cascadas(tablero, estadoJuego);
            break;

        case OPCION_AYUDA:
            mostrarAyuda();
            break;

        case OPCION_SALIR:
            jugando = false;
            cout << "\n================ PUNTUACION FINAL ================" << endl;
            cout << "Puntaje alcanzado: " << estadoJuego[PUNTOS] << endl;
            cout << "Gracias por jugar Sweet Crush." << endl;
            break;
        }
    }

    delete[] tablero;
    cout << "Memoria liberada" << endl;

    return 0;
}