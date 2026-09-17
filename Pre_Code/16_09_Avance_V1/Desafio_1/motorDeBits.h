#ifndef MOTORDEBITS_H
#define MOTORDEBITS_H

void calcularBtye_desplazamiento(int fila, int columna, int totalColumnas, int &indiceByte, int &offset);

int leerFicha(unsigned char* tablero, int indiceByte, int offset);

void escribirFicha(unsigned char* tablero, int indiceByte, int offset, int valorFicha);

#endif // MOTORDEBITS_H
