#include <iostream>
#include "motorDeBits.h"

using namespace std;

int main()
{
    
    unsigned char pruebaTablero[3] = {0,0,0}
    int pruebaByte = 0;
    int pruebaOffset = 0;

    calcularBtye_desplazamiento(2,3,5,pruebaByte,pruebaOffset);

    cout<<"Coordenada (2,3): "<<endl;
    cout<<"Queda en el byte: "<<pruebaByte<<endl;
    cout<<"Con offset: "<<pruebaOffset;

    return 0;
}

//-------------------------------------------------------------------------------------------------------------------------
#include <iostream>
#include "motorDeBits.h"

using namespace std;

int main()
{
    unsigned char miTablero[3] = {0, 0, 0};

    cout << "--- PRUEBAS AVANZADAS DE LECTURA DE BITS ---" << endl << endl;

    // ==========================================
    // PRUEBA 4: Extremo inferior (Offset 0) con ruido
    // Queremos leer la ficha '7' (111 en binario) en el offset 0.
    // Además, encenderemos otros bits en ese mismo byte para generar "basura".
    // Byte: 1 0 1 1 1 (1 1 1) -> Los 3 bits de la derecha son nuestra ficha (7).
    // Ese byte completo en decimal es 191 (128 + 32 + 16 + 8 + 4 + 2 + 1).
    miTablero[0] = 191;

    int resultado4 = leerFicha(miTablero, 0, 0);
    cout << "Prueba 4 (Offset 0 con ruido): Esperado = 7, Obtenido = " << resultado4 << endl;


    // ==========================================
    // PRUEBA 5: Extremo superior de 1 byte (Offset 5) con ruido
    // Queremos leer la ficha '2' (010 en binario) en el offset 5.
    // (0 1 0) 1 1 1 1 1 -> Los 3 bits de la izquierda son nuestra ficha. Los 5 de la derecha son basura.
    // Ese byte completo en decimal es 95 (64 + 16 + 8 + 4 + 2 + 1).
    miTablero[0] = 95;

    int resultado5 = leerFicha(miTablero, 0, 5);
    cout << "Prueba 5 (Offset 5 con ruido): Esperado = 2, Obtenido = " << resultado5 << endl;


    // ==========================================
    // PRUEBA 6: Situación "2 + 1" (Offset 6) rodeada de ruido total
    // Queremos leer la ficha '5' (101 en binario).
    // Primeros 2 bits (01) van al offset 6 del Byte 0. Llenamos el resto del Byte 0 de unos (basura).
    // Byte 0: (0 1) 1 1 1 1 1 1 -> Decimal 127
    // Último bit (1) va al offset 0 del Byte 1. Llenamos el resto de unos.
    // Byte 1: 1 1 1 1 1 1 1 (1) -> Decimal 255
    miTablero[0] = 127;
    miTablero[1] = 255;

    int resultado6 = leerFicha(miTablero, 0, 6);
    cout << "Prueba 6 (Offset 6 rodeado de 1s): Esperado = 5, Obtenido = " << resultado6 << endl;


    // ==========================================
    // PRUEBA 7: Situación "1 + 2" (Offset 7) rodeada de ruido total
    // Queremos leer la ficha '6' (110 en binario).
    // Primer bit (0) va al offset 7 del Byte 0. Llenamos el resto de unos.
    // Byte 0: (0) 1 1 1 1 1 1 1 -> Decimal 127
    // Últimos 2 bits (11) van al offset 0 del Byte 1. Llenamos el resto de unos.
    // Byte 1: 1 1 1 1 1 1 (1 1) -> Decimal 255
    miTablero[0] = 127;
    miTablero[1] = 255;

    int resultado7 = leerFicha(miTablero, 0, 7);
    cout << "Prueba 7 (Offset 7 rodeado de 1s): Esperado = 6, Obtenido = " << resultado7 << endl;

    return 0;
}

//--------------------------------------------------------------------------------------------------------------------------------------------------------
#include <iostream>
#include "motorDeBits.h"

using namespace std;

int main()
{
    cout << "--- PRUEBAS EXTREMAS DE ESCRITURA Y LECTURA ---" << endl << endl;

    // ==========================================
    // PRUEBA 1: Sobrescritura (El borrador)
    // Objetivo: Verificar que la máscara destructora limpie bien los bits viejos antes de pegar los nuevos.
    unsigned char tableroPrueba1[1] = {0}; // 1 byte en cero
    
    // 1. Escribimos la ficha 7 (111) en el offset 3
    escribirFicha(tableroPrueba1, 0, 3, 7);
    
    // 2. En ese mismo lugar exacto, escribimos la ficha 0 (000) para borrarla
    escribirFicha(tableroPrueba1, 0, 3, 0);
    
    // 3. Leemos de nuevo
    int leido1 = leerFicha(tableroPrueba1, 0, 3);
    cout << "Prueba 1 (Sobrescritura): Esperado = 0, Obtenido = " << leido1 << endl;


    // ==========================================
    // PRUEBA 2: Integridad Cruzada (Vecinos)
    // Objetivo: Verificar que escribir una ficha que se parte en dos bytes no corrompe a su vecina.
    unsigned char tableroPrueba2[2] = {0, 0}; // 2 bytes en cero
    
    // 1. Escribimos la ficha A (valor 1) cómoda en un solo byte (offset 3)
    escribirFicha(tableroPrueba2, 0, 3, 1);
    
    // 2. Escribimos la ficha B (valor 2) en el offset 6. 
    // ¡OJO! Esto desencadena el caso "2+1" y altera el Byte 0 y el Byte 1.
    escribirFicha(tableroPrueba2, 0, 6, 2);
    
    // 3. Leemos la ficha A para ver si el proceso anterior la dañó
    int leido2 = leerFicha(tableroPrueba2, 0, 3);
    cout << "Prueba 2 (Vecinos cruzados): Esperado = 1, Obtenido = " << leido2 << endl;


    // ==========================================
    // PRUEBA 3: Llenado Total (Simulación de Tablero Real)
    // Objetivo: Llenar un tablero de 2x2 usando matemáticas y verificar que todo quede en su sitio.
    // 2x2 = 4 fichas = 12 bits = 2 bytes requeridos.
    unsigned char tableroPrueba3[2] = {0, 0}; 
    
    int totalColumnas = 2;
    int byte_idx = 0;
    int offset = 0;
    
    // Fichas a inyectar: 1, 2, 3, 4
    int valores[4] = {1, 2, 3, 4};
    
    cout << "\nPrueba 3 (Llenado Total 2x2):" << endl;
    
    // CICLO DE ESCRITURA
    for(int f = 0; f < 2; f++) {
        for(int c = 0; c < 2; c++) {
            // Calculamos en qué bits cae la coordenada
            calcularBtye_desplazamiento(f, c, totalColumnas, byte_idx, offset);
            
            // Calculamos qué ficha le toca del arreglo de valores
            int valorAInyectar = valores[f * totalColumnas + c];
            
            // Escribimos la ficha
            escribirFicha(tableroPrueba3, byte_idx, offset, valorAInyectar);
        }
    }
    
    // CICLO DE LECTURA (Para comprobar)
    for(int f = 0; f < 2; f++) {
        for(int c = 0; c < 2; c++) {
            calcularBtye_desplazamiento(f, c, totalColumnas, byte_idx, offset);
            int valorEsperado = valores[f * totalColumnas + c];
            
            int leido3 = leerFicha(tableroPrueba3, byte_idx, offset);
            cout << " -> Coordenada (" << f << "," << c << "): Esperado = " << valorEsperado << ", Obtenido = " << leido3 << endl;
        }
    }

    return 0;
}


//--------------------------------------------------------------------------------------------------------------------------------------------------------------
#include <iostream>
#include "motorDeBits.h"

using namespace std;

int main()
{
    cout << "=============================================" << endl;
    cout << "      PRUEBAS DEL MOTOR DE BITS" << endl;
    cout << "=============================================" << endl << endl;


    // =========================================================
    // PRUEBA 1
    // Todos los valores posibles (0-7)
    // en todos los offsets posibles (0-7)
    // =========================================================

    cout << "PRUEBA 1: Todos los valores y todos los offsets" << endl;

    bool prueba1Correcta = true;

    for (int offset = 0; offset <= 7; offset++)
    {
        for (int valor = 0; valor <= 7; valor++)
        {
            unsigned char tablero[2] = {0, 0};

            // Escribimos la ficha
            escribirFicha(tablero, 0, offset, valor);

            // La leemos
            int resultado = leerFicha(tablero, 0, offset);

            if (resultado != valor)
            {
                prueba1Correcta = false;

                cout << "ERROR -> "
                     << "Offset: " << offset
                     << " | Escrito: " << valor
                     << " | Leido: " << resultado
                     << endl;
            }
        }
    }

    if (prueba1Correcta)
    {
        cout << "RESULTADO: Todas las combinaciones valor/offset fueron correctas."
             << endl;
    }

    cout << endl;


    // =========================================================
    // PRUEBA 2
    // Verificar que los bits vecinos no sean modificados
    // =========================================================

    cout << "PRUEBA 2: Integridad de los bits vecinos" << endl;

    bool prueba2Correcta = true;

    for (int offset = 0; offset <= 7; offset++)
    {
        for (int valor = 0; valor <= 7; valor++)
        {
            unsigned char tablero[2] = {255, 255};

            // Guardamos la memoria original
            unsigned char byteOriginal0 = tablero[0];
            unsigned char byteOriginal1 = tablero[1];

            // Escribimos una ficha
            escribirFicha(tablero, 0, offset, valor);

            // Volvemos a leer la ficha
            int resultado = leerFicha(tablero, 0, offset);

            if (resultado != valor)
            {
                prueba2Correcta = false;

                cout << "ERROR DE LECTURA -> "
                     << "Offset: " << offset
                     << " | Escrito: " << valor
                     << " | Leido: " << resultado
                     << endl;
            }

            // -------------------------------------------------
            // Verificamos manualmente los bits que NO
            // pertenecen a la ficha.
            //
            // Para hacer esto reconstruimos la máscara de bits
            // que sí pertenecen a la ficha.
            // -------------------------------------------------

            if (offset <= 5)
            {
                unsigned char mascara = (unsigned char)(7 << offset);

                unsigned char vecinosOriginales =
                    byteOriginal0 & (unsigned char)(~mascara);

                unsigned char vecinosActuales =
                    tablero[0] & (unsigned char)(~mascara);

                if (vecinosOriginales != vecinosActuales)
                {
                    prueba2Correcta = false;

                    cout << "ERROR DE VECINOS -> "
                         << "Offset: " << offset
                         << " | Valor: " << valor
                         << endl;
                }
            }
            else if (offset == 6)
            {
                unsigned char mascaraByte0 = (unsigned char)(3 << 6);

                unsigned char vecinosOriginales0 =
                    byteOriginal0 & (unsigned char)(~mascaraByte0);

                unsigned char vecinosActuales0 =
                    tablero[0] & (unsigned char)(~mascaraByte0);

                unsigned char vecinosOriginales1 =
                    byteOriginal1 & (unsigned char)(~1);

                unsigned char vecinosActuales1 =
                    tablero[1] & (unsigned char)(~1);

                if (vecinosOriginales0 != vecinosActuales0 ||
                    vecinosOriginales1 != vecinosActuales1)
                {
                    prueba2Correcta = false;

                    cout << "ERROR DE VECINOS -> "
                         << "Offset: " << offset
                         << " | Valor: " << valor
                         << endl;
                }
            }
            else if (offset == 7)
            {
                unsigned char mascaraByte0 = (unsigned char)(1 << 7);

                unsigned char vecinosOriginales0 =
                    byteOriginal0 & (unsigned char)(~mascaraByte0);

                unsigned char vecinosActuales0 =
                    tablero[0] & (unsigned char)(~mascaraByte0);

                unsigned char vecinosOriginales1 =
                    byteOriginal1 & (unsigned char)(~3);

                unsigned char vecinosActuales1 =
                    tablero[1] & (unsigned char)(~3);

                if (vecinosOriginales0 != vecinosActuales0 ||
                    vecinosOriginales1 != vecinosActuales1)
                {
                    prueba2Correcta = false;

                    cout << "ERROR DE VECINOS -> "
                         << "Offset: " << offset
                         << " | Valor: " << valor
                         << endl;
                }
            }
        }
    }

    if (prueba2Correcta)
    {
        cout << "RESULTADO: Ninguna escritura modifico los bits vecinos."
             << endl;
    }

    cout << endl;


    // =========================================================
    // PRUEBA 3
    // Sobrescritura de una ficha
    // =========================================================

    cout << "PRUEBA 3: Sobrescritura de fichas" << endl;

    bool prueba3Correcta = true;

    for (int offset = 0; offset <= 7; offset++)
    {
        for (int valorInicial = 0; valorInicial <= 7; valorInicial++)
        {
            for (int valorNuevo = 0; valorNuevo <= 7; valorNuevo++)
            {
                unsigned char tablero[2] = {0, 0};

                escribirFicha(tablero, 0, offset, valorInicial);

                escribirFicha(tablero, 0, offset, valorNuevo);

                int resultado =
                    leerFicha(tablero, 0, offset);

                if (resultado != valorNuevo)
                {
                    prueba3Correcta = false;

                    cout << "ERROR -> "
                         << "Offset: " << offset
                         << " | Inicial: " << valorInicial
                         << " | Nuevo: " << valorNuevo
                         << " | Leido: " << resultado
                         << endl;
                }
            }
        }
    }

    if (prueba3Correcta)
    {
        cout << "RESULTADO: Todas las sobrescrituras fueron correctas."
             << endl;
    }

    cout << endl;


    // =========================================================
    // PRUEBA 4
    // Direccionamiento matematico
    // =========================================================

    cout << "PRUEBA 4: Calculo de byte y offset" << endl;

    bool prueba4Correcta = true;

    int filas = 5;
    int columnas = 5;

    for (int fila = 0; fila < filas; fila++)
    {
        for (int columna = 0; columna < columnas; columna++)
        {
            int indiceByte = 0;
            int offset = 0;

            calcularBtye_desplazamiento(
                fila,
                columna,
                columnas,
                indiceByte,
                offset
            );

            int indiceLineal =
                fila * columnas + columna;

            int bitInicial =
                indiceLineal * 3;

            int byteEsperado =
                bitInicial / 8;

            int offsetEsperado =
                bitInicial % 8;

            if (indiceByte != byteEsperado ||
                offset != offsetEsperado)
            {
                prueba4Correcta = false;

                cout << "ERROR -> "
                     << "Coordenada (" << fila << ","
                     << columna << ")"
                     << " | Byte esperado: " << byteEsperado
                     << " | Byte obtenido: " << indiceByte
                     << " | Offset esperado: " << offsetEsperado
                     << " | Offset obtenido: " << offset
                     << endl;
            }
        }
    }

    if (prueba4Correcta)
    {
        cout << "RESULTADO: Todo el direccionamiento fue correcto."
             << endl;
    }

    cout << endl;


    // =========================================================
    // PRUEBA 5
    // Tablero 2x2 completo
    // =========================================================

    cout << "PRUEBA 5: Tablero 2x2" << endl;

    unsigned char tablero2x2[2] = {0, 0};

    int valores2x2[4] = {
        1, 2,
        3, 4
    };

    for (int fila = 0; fila < 2; fila++)
    {
        for (int columna = 0; columna < 2; columna++)
        {
            int indiceByte = 0;
            int offset = 0;

            calcularBtye_desplazamiento(
                fila,
                columna,
                2,
                indiceByte,
                offset
            );

            int valor =
                valores2x2[fila * 2 + columna];

            escribirFicha(
                tablero2x2,
                indiceByte,
                offset,
                valor
            );
        }
    }

    bool prueba5Correcta = true;

    for (int fila = 0; fila < 2; fila++)
    {
        for (int columna = 0; columna < 2; columna++)
        {
            int indiceByte = 0;
            int offset = 0;

            calcularBtye_desplazamiento(
                fila,
                columna,
                2,
                indiceByte,
                offset
            );

            int esperado =
                valores2x2[fila * 2 + columna];

            int obtenido =
                leerFicha(
                    tablero2x2,
                    indiceByte,
                    offset
                );

            cout << "Coordenada ("
                 << fila << ","
                 << columna << ")"
                 << " | Esperado: " << esperado
                 << " | Obtenido: " << obtenido
                 << endl;

            if (esperado != obtenido)
            {
                prueba5Correcta = false;
            }
        }
    }

    if (prueba5Correcta)
    {
        cout << "RESULTADO: Tablero 2x2 correcto."
             << endl;
    }

    cout << endl;


    // =========================================================
    // PRUEBA 6
    // Tablero 3x3 con valores variados
    // =========================================================

    cout << "PRUEBA 6: Tablero 3x3" << endl;

    unsigned char tablero3x3[4] = {0, 0, 0, 0};

    int valores3x3[9] = {
        1, 7, 3,
        4, 2, 6,
        5, 0, 3
    };

    for (int fila = 0; fila < 3; fila++)
    {
        for (int columna = 0; columna < 3; columna++)
        {
            int indiceByte = 0;
            int offset = 0;

            calcularBtye_desplazamiento(
                fila,
                columna,
                3,
                indiceByte,
                offset
            );

            int valor =
                valores3x3[fila * 3 + columna];

            escribirFicha(
                tablero3x3,
                indiceByte,
                offset,
                valor
            );
        }
    }

    bool prueba6Correcta = true;

    for (int fila = 0; fila < 3; fila++)
    {
        for (int columna = 0; columna < 3; columna++)
        {
            int indiceByte = 0;
            int offset = 0;

            calcularBtye_desplazamiento(
                fila,
                columna,
                3,
                indiceByte,
                offset
            );

            int esperado =
                valores3x3[fila * 3 + columna];

            int obtenido =
                leerFicha(
                    tablero3x3,
                    indiceByte,
                    offset
                );

            if (esperado != obtenido)
            {
                prueba6Correcta = false;

                cout << "ERROR -> "
                     << "Coordenada (" << fila
                     << "," << columna << ")"
                     << " | Esperado: " << esperado
                     << " | Obtenido: " << obtenido
                     << endl;
            }
        }
    }

    if (prueba6Correcta)
    {
        cout << "RESULTADO: Tablero 3x3 correcto."
             << endl;
    }

    cout << endl;


    // =========================================================
    // RESUMEN
    // =========================================================

    cout << "=============================================" << endl;
    cout << "              FIN DE PRUEBAS" << endl;
    cout << "=============================================" << endl;

    return 0;
}