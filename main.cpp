// Nombre: Carlos Mauricio Angles Quispe

// Implementación de una Heurística para Resolver el Problema de Transporte.

// El proceso del programa es el siguiente:
// 1. Solicita al usuario el número de ofertantes y demandantes.
// 2. Solicita las ofertas.
// 3. Solicita las demandas.
// 4. Solicita la matriz de costos, que indica el costo de enviar una unidad de bienes
//    desde cada ofertante a cada demandante.
// 5. Aplica el método heurístico.
// 6. Imprime la matriz de asignación final y el costo total asociado.

#include <iostream>
using namespace std;

const int INF = 1000000;

// Funcion para imprimir la solucion final
void imprimirSolucion(int asignacion[][10], int ofertantes, int demandantes) {
    cout << "Matriz de Asignacion:" << endl;
    for (int i = 0; i < ofertantes; i++) {
        for (int j = 0; j < demandantes; j++) {
            cout << asignacion[i][j] << "\t";
        }
        cout << endl;
    }
}

// Método heuristico para resolver el problema de transporte
void metodoHeuristico(int costo[][10], int oferta[], int demanda[], int ofertantes, int demandantes) {
    int asignacion[10][10] = {0};
    bool filaHecha[10] = {0};
    bool columnaHecha[10] = {0};

    int costoTotal = 0;

    while (true) {
        int costoMaximo = -1;
        int filaMax = -1, columnaMax = -1;

        // Encontrar la celda con el costo maximo
        for (int i = 0; i < ofertantes; i++) {
            for (int j = 0; j < demandantes; j++) {
                if (!filaHecha[i] && !columnaHecha[j] && costo[i][j] > costoMaximo) {
                    costoMaximo = costo[i][j];
                    filaMax = i;
                    columnaMax = j;
                }
            }
        }

        // Si no se encuentran mas celdas validas, romper el ciclo
        if (filaMax == -1 || columnaMax == -1) {
            break;
        }

        int costoMinimo = INF;
        int filaMin = -1, columnaMin = -1;

        // Encontrar el costo minimo en la misma fila del costo maximo
        for (int j = 0; j < demandantes; j++) {
            if (!columnaHecha[j] && costo[filaMax][j] < costoMinimo) {
                costoMinimo = costo[filaMax][j];
                filaMin = filaMax;
                columnaMin = j;
            }
        }

        // Encontrar el costo minimo en la misma columna del costo maximo
        for (int i = 0; i < ofertantes; i++) {
            if (!filaHecha[i] && costo[i][columnaMax] < costoMinimo) {
                costoMinimo = costo[i][columnaMax];
                filaMin = i;
                columnaMin = columnaMax;
            }
        }

        // Asignar la cantidad correspondiente de oferta o demanda
        int asignado = (oferta[filaMin] < demanda[columnaMin]) ? oferta[filaMin] : demanda[columnaMin];
        asignacion[filaMin][columnaMin] = asignado;
        costoTotal += asignado * costoMinimo;

        oferta[filaMin] -= asignado;
        demanda[columnaMin] -= asignado;

        // Marcar la fila o columna como completada si su oferta o demanda llega a cero
        if (oferta[filaMin] == 0) filaHecha[filaMin] = true;
        if (demanda[columnaMin] == 0) columnaHecha[columnaMin] = true;
    }

    imprimirSolucion(asignacion, ofertantes, demandantes);
    cout << "Z= " << costoTotal << endl;
}

int main() {
    int ofertantes, demandantes;

    cout << "Ingrese el numero de Ofertantes: ";
    cin >> ofertantes;
    cout << "Ingrese el numero de Demandantes: ";
    cin >> demandantes;

    int costo[10][10];
    int oferta[10];
    int demanda[10];

    cout << "Ingrese las Ofertas:" << endl;
    for (int i = 0; i < ofertantes; i++) {
        cout << "Oferta " << i + 1 << ": ";
        cin >> oferta[i];
    }

    cout << "Ingrese las Demandas:" << endl;
    for (int i = 0; i < demandantes; i++) {
        cout << "Demanda " << i + 1 << ": ";
        cin >> demanda[i];
    }

    cout << "Ingrese la matriz de costos:" << endl;
    for (int i = 0; i < ofertantes; i++) {
        for (int j = 0; j < demandantes; j++) {
            cout << "Costo del Ofertante " << i + 1 << " al Demandante " << j + 1 << ": ";
            cin >> costo[i][j];
        }
    }
    metodoHeuristico(costo, oferta, demanda, ofertantes, demandantes);

    return 0;
}
