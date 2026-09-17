#include <iostream>
#include "motorDeBits.h"
#include "manejoMemoria.h"
#include "interfazUsuario.h"
#include "logicaJuego.h"

using namespace std;

const int FILAS = 0;
const int COLUMNAS = 1;
const int BYTESRESERVADOS = 2;
const int ELIM_USUARIO = 3;
const int FICHAS_ELIMINADAS = 4;
const int COMBOS = 5;
const int CASCADAS = 6;
const int PUNTOS = 7;

int main(){

    int estadoJuego[8] = {0};

    mostrarMenuInicio(estadoJuego[FILAS], estadoJuego[COLUMNAS]);

    unsigned char* tablero = inicializarTablero(estadoJuego);

    cout << "Bytes reservados: " << estadoJuego[BYTESRESERVADOS] << endl;

    inicializarSemillaAleatoria(); // Arrancamos el motor de azar
    generarFichasAleatorias(tablero, estadoJuego[FILAS], estadoJuego[COLUMNAS]);

    bool jugando = true;

    while(jugando){
        imprimirTableroFichas(tablero, estadoJuego[FILAS], estadoJuego[COLUMNAS]);

        imprimirTableroBinario(tablero, estadoJuego[FILAS], estadoJuego[COLUMNAS]);

        int opcion = mostrarMenuPartida();

        switch(opcion){
        case OPCION_ELIMINAR_FICHA:
            // TODO: conectar con el Modulo 3 (logica del juego) -> eliminacion por usuario
            eliminarFicha(tablero, estadoJuego);
            gravedad(tablero,estadoJuego);
            generarFichasAleatorias(tablero, estadoJuego[FILAS], estadoJuego[COLUMNAS]);
            cout << "\nEvaluando tablero..." << endl;
            funcion_cascadas(tablero, estadoJuego);
            break;

        case OPCION_AGREGAR_FILA:
            // TODO: conectar con el Modulo 2 (gestor de memoria) -> expandir memoria
            cout << "Funcion pendiente: se conectara con el modulo de gestor de memoria." << endl;
            break;

        case OPCION_ELIMINAR_FILA:
            // TODO: conectar con el Modulo 2 (gestor de memoria) -> reducir memoria
            cout << "Funcion pendiente: se conectara con el modulo de gestor de memoria." << endl;
            break;

        case OPCION_AGREGAR_COLUMNA:
            // TODO: conectar con el Modulo 2 (gestor de memoria) -> expandir memoria
            cout << "Funcion pendiente: se conectara con el modulo de gestor de memoria." << endl;
            break;

        case OPCION_ELIMINAR_COLUMNA:
            // TODO: conectar con el Modulo 2 (gestor de memoria) -> reducir memoria
            cout << "Funcion pendiente: se conectara con el modulo de gestor de memoria." << endl;
            break;

        case OPCION_AYUDA:
            mostrarAyuda();
            break;

        case OPCION_SALIR:
            jugando = false;
            cout << "Gracias por jugar Sweet Crush." << endl;
            break;
        }
    }

    delete[] tablero;
    cout << "Memoria liberada" << endl;

    return 0;
}