#include "motorDeBits.h"

void calcularBtye_desplazamiento(int fila, int columna, int totalColumnas, int &indiceByte, int &offset){
    int indiceLineal = (fila * totalColumnas) + columna;

    int bitInicial = indiceLineal * 3;

    indiceByte = bitInicial / 8;

    offset = bitInicial % 8;
}

int leerFicha(unsigned char* tablero, int indiceByte, int offset){
    int valorFicha = 0;

    if(offset<=5){
        valorFicha = (tablero[indiceByte] >> offset) & 7;
    }

    else if(offset == 6){
        int byte1 = (tablero[indiceByte] >> offset) & 3;

        int byte2 = (tablero[indiceByte + 1] & 1) << 2;

        valorFicha = byte1 | byte2;
    }

    else if(offset == 7){
        int byte1 = (tablero[indiceByte] >> offset) & 1;

        int byte2 = (tablero[indiceByte + 1] & 3) << 1;

        valorFicha = byte1 | byte2;
    }

    return valorFicha;

}

void escribirFicha(unsigned char* tablero, int indiceByte, int offset, int valorFicha){

    if(offset <= 5){
        tablero[indiceByte] = tablero[indiceByte] & ~(7 << offset);

        tablero[indiceByte] = tablero[indiceByte] | (valorFicha << offset);
    }

    else if(offset == 6){
        int bitsByte1 = valorFicha & 3;

        tablero[indiceByte] = tablero[indiceByte] & ~(3 << offset);

        tablero[indiceByte] = tablero[indiceByte] | (bitsByte1 << offset);

        int bitsByte2 = (valorFicha >> 2) & 1;

        tablero[indiceByte + 1] = tablero[indiceByte + 1] & ~(1);

        tablero[indiceByte + 1] = tablero[indiceByte + 1] | bitsByte2;

    }

    else if(offset == 7){
        int bitsByte1 = valorFicha & 1;

        tablero[indiceByte] = tablero[indiceByte] & ~(1 << offset);

        tablero[indiceByte] = tablero[indiceByte] | (bitsByte1 << offset);

        int bitsByte2 = (valorFicha >> 1) & 3;

        tablero[indiceByte + 1] = tablero[indiceByte + 1] & ~(3);

        tablero[indiceByte + 1] = tablero[indiceByte + 1] | bitsByte2;
    }

}