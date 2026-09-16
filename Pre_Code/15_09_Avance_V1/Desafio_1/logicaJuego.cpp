#include "logicaJuego.h"
#include "motorDeBits.h"
#include "interfazUsuario.h"
#include <cstdlib> // Para rand() y srand()
#include <ctime>   // Para time()
#include <iostream>

using namespace std;

void inicializarSemillaAleatoria() {
    // Usamos la hora actual del sistema operativo como semilla inicial
    srand(time(0));
}

void generarFichasAleatorias(unsigned char* tablero, int filas, int columnas) {
    int indiceByte, offset;

    for (int fila = 0; fila < filas; fila++) {
        for (int columna = 0; columna < columnas; columna++) {

            // Calculamos donde estamos parados
            calcularBtye_desplazamiento(fila, columna, columnas, indiceByte, offset);

            // Solo generamos si la posicion actual esta vacia (Estado Libre = 0)
            if (leerFicha(tablero, indiceByte, offset) == 0) {

                int fichaAleatoria;
                bool fichaValida;

                // Bucle de prevención: repetimos hasta encontrar una ficha que no forme linea de 3
                do {
                    fichaValida = true;
                    fichaAleatoria = (rand() % 6) + 1; // Genera un número del 1 al 6

                    // --- PREVENCIÓN HORIZONTAL (Mirar a la izquierda) ---
                    if (columna >= 2) {
                        int byteIzq1, offsetIzq1, byteIzq2, offsetIzq2;

                        calcularBtye_desplazamiento(fila, columna - 1, columnas, byteIzq1, offsetIzq1);
                        int fichaIzq1 = leerFicha(tablero, byteIzq1, offsetIzq1);

                        calcularBtye_desplazamiento(fila, columna - 2, columnas, byteIzq2, offsetIzq2);
                        int fichaIzq2 = leerFicha(tablero, byteIzq2, offsetIzq2);

                        // Si la que generamos es igual a las dos de la izquierda, es invalida
                        if (fichaAleatoria == fichaIzq1 && fichaAleatoria == fichaIzq2) {
                            fichaValida = false;
                        }
                    }

                    // --- PREVENCIÓN VERTICAL (Mirar hacia arriba) ---
                    // Solo revisamos si sigue siendo valida despues de la prueba horizontal
                    if (fichaValida && fila >= 2) {
                        int byteArr1, offsetArr1, byteArr2, offsetArr2;

                        calcularBtye_desplazamiento(fila - 1, columna, columnas, byteArr1, offsetArr1);
                        int fichaArr1 = leerFicha(tablero, byteArr1, offsetArr1);

                        calcularBtye_desplazamiento(fila - 2, columna, columnas, byteArr2, offsetArr2);
                        int fichaArr2 = leerFicha(tablero, byteArr2, offsetArr2);

                        // Si la que generamos es igual a las dos de arriba, es invalida
                        if (fichaAleatoria == fichaArr1 && fichaAleatoria == fichaArr2) {
                            fichaValida = false;
                        }
                    }

                } while (!fichaValida);

                // Si salio del bucle do-while, significa que la ficha es 100% segura. La escribimos.
                escribirFicha(tablero, indiceByte, offset, fichaAleatoria);
            }
        }
    }
}

void eliminarFicha(unsigned char* tablero, int* estadoJuego){
    int filas = estadoJuego[0];
    int columnas = estadoJuego[1];

    int filaEscogida = -1;
    int columnaEscogida = -1;
    bool coordenadaValida = false;

    while(!coordenadaValida){
        filaEscogida = leerEnteroValidado("Ingrese la fila: ",0);
        columnaEscogida = leerEnteroValidado("Ingrese la columna: ",0);

        if(filaEscogida < filas && columnaEscogida < columnas){
            coordenadaValida = true;
        }
        else{
            cout<<"Coordenada invalida, ingresa el valor de una fila maximo: "<<(filas - 1)<<" y una columna maximo: "<<(columnas - 1)<<endl;
        }
    }

    int indiceByte = 0;
    int offset = 0;
    calcularBtye_desplazamiento(filaEscogida,columnaEscogida,columnas,indiceByte,offset);
    escribirFicha(tablero, indiceByte, offset, 0);
    estadoJuego[3] = estadoJuego[3] + 1;
    cout << "Ficha ubicada en la posicion (" << filaEscogida << ", " << columnaEscogida << ") ha sido eliminada." << endl;
}

void gravedad(unsigned char *tablero, int* estadoJuego){
    int filas = estadoJuego[0];
    int columnas = estadoJuego[1];

    for(int columna=0;columna<columnas;columna++){
        int filaEscribir=filas-1;

        for(int filaLeer=filas-1; filaLeer >=0; filaLeer--){
            int byteLeer,offsetLeer;
            calcularBtye_desplazamiento(filaLeer,columna,columnas,byteLeer,offsetLeer);
            int fichaActual = leerFicha(tablero, byteLeer,offsetLeer);

            if(fichaActual!=0){
                if(filaLeer!=filaEscribir){
                    int byteEscribir,offsetEscribir;
                    calcularBtye_desplazamiento(filaEscribir,columna,columnas,byteEscribir,offsetEscribir);
                    escribirFicha(tablero,byteEscribir,offsetEscribir,fichaActual);
                    escribirFicha(tablero,byteLeer,offsetLeer,0);
                }
                filaEscribir--;
            }
        }
    }
}

