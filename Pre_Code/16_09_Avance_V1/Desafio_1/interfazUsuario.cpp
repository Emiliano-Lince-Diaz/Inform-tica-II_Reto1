#include <iostream>
#include <iomanip>
#include "interfazUsuario.h"
#include "motorDeBits.h"

using namespace std;

int leerEnteroValidado(const char* mensaje, int minimo){
    int valor;
    bool valido = false;

    do{
        cout << mensaje;
        cin >> valor;

        if(cin.fail()){
            // El usuario ingresó algo que no es un número.
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "Entrada invalida. Debe ingresar un numero." << endl;
        }
        else if(valor < minimo){
            cout << "El valor debe ser mayor o igual a " << minimo << "." << endl;
        }
        else{
            valido = true;
        }

    }while(!valido);

    return valor;
}


void mostrarMenuInicio(int &filas, int &columnas){
    cout << "=================================================" << endl;
    cout << "               BIENVENIDO A SWEET CRUSH           " << endl;
    cout << "=================================================" << endl;

    filas    = leerEnteroValidado("Ingrese la cantidad de filas del tablero: ", 1);
    columnas = leerEnteroValidado("Ingrese la cantidad de columnas del tablero: ", 1);

    cout << endl;
}

int mostrarMenuPartida(){
    cout << endl << "----------------- MENU EN PARTIDA -----------------" << endl;
    cout << OPCION_ELIMINAR_FICHA   << ". Eliminar ficha"   << endl;
    cout << OPCION_AGREGAR_FILA     << ". Agregar fila"     << endl;
    cout << OPCION_ELIMINAR_FILA    << ". Eliminar fila"    << endl;
    cout << OPCION_AGREGAR_COLUMNA  << ". Agregar columna"  << endl;
    cout << OPCION_ELIMINAR_COLUMNA << ". Eliminar columna" << endl;
    cout << OPCION_AYUDA            << ". Ayuda"            << endl;
    cout << OPCION_SALIR            << ". Salir"            << endl;
    cout << "----------------------------------------------------" << endl;

    int opcion = leerEnteroValidado("Seleccione una opcion: ", OPCION_ELIMINAR_FICHA);

    while(opcion > OPCION_SALIR){
        cout << "Opcion fuera de rango. Intente de nuevo." << endl;
        opcion = leerEnteroValidado("Seleccione una opcion: ", OPCION_ELIMINAR_FICHA);
    }

    return opcion;
}


void mostrarAyuda(){
    cout << endl << "===================== AYUDA =====================" << endl;
    cout << OPCION_ELIMINAR_FICHA   << ": Elimina la ficha en la posicion (fila, columna) indicada." << endl;
    cout << OPCION_AGREGAR_FILA     << ": Agrega una fila nueva en la posicion indicada."            << endl;
    cout << OPCION_ELIMINAR_FILA    << ": Elimina la fila indicada."                                 << endl;
    cout << OPCION_AGREGAR_COLUMNA  << ": Agrega una columna nueva en la posicion indicada."          << endl;
    cout << OPCION_ELIMINAR_COLUMNA << ": Elimina la columna indicada."                               << endl;
    cout << OPCION_AYUDA            << ": Muestra este mensaje de ayuda."                             << endl;
    cout << OPCION_SALIR            << ": Sale del juego."                                            << endl;
    cout << "==================================================" << endl << endl;
}


char obtenerSimboloFicha(int valorFicha){
    switch(valorFicha){
    case 0: return '.';  // Estado vacio
    case 1: return 'B';  // beta
    case 2: return 'W';  // omega
    case 3: return 'S';  // sigma
    case 4: return 'G';  // gamma
    case 5: return 'T';  // theta
    case 6: return 'U';  // mu
    case 7: return 'X';  // Estado Eliminacion
    default: return '?'; // No deberia ocurrir (solo hay 3 bits = 0..7)
    }
}

void imprimirTableroFichas(unsigned char* tablero, int filas, int columnas){
    int indiceByte, offset, valorFicha;

    cout << endl << "TABLERO DE JUEGO" << endl;

    // Encabezado con el indice de cada columna
    cout << "     ";
    for(int columna = 0; columna < columnas; columna++){
        cout << setw(3) << columna;
    }
    cout << endl;

    for(int fila = 0; fila < filas; fila++){
        cout << setw(3) << fila << " |";

        for(int columna = 0; columna < columnas; columna++){
            calcularBtye_desplazamiento(fila, columna, columnas, indiceByte, offset);
            valorFicha = leerFicha(tablero, indiceByte, offset);

            cout << setw(3) << obtenerSimboloFicha(valorFicha);
        }

        cout << endl;
    }

    cout << endl;
}


void imprimirTableroBinario(unsigned char* tablero, int filas, int columnas){
    cout << endl << "TABLERO EN BINARIO (vista profesor)" << endl;

    // Calculamos el total de bytes reales que tiene el tablero
    int bytesTotales = ((3 * filas * columnas) + 7) / 8;

    // Recorremos la memoria byte por byte
    for(int i = 0; i < bytesTotales; i++){
        cout << "Byte " << setw(2) << i << ": ";

        // Imprimimos cada bit de izquierda (bit 7) a derecha (bit 0)
        for(int bit = 7; bit >= 0; bit--){
            cout << ((tablero[i] >> bit) & 1);
        }

        cout << endl;
    }

    cout << endl;
}