#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Funciones principales
void inicializarTablero(char tablero[3][3]);
void mostrarTablero(char tablero[3][3]);
int movimientoValido(char tablero[3][3], int fila, int columna);
int verificarGanador(char tablero[3][3]);
void pedirMovimiento(char jugador, char tablero[3][3]);

int main() {
    char tablero[3][3]; // El tablero
    char jugador = 'X'; // Jugador actual
    int ganador = 0;    // Indica si hay un ganador
    int movimientos = 0; // Contador de movimientos

    inicializarTablero(tablero);

    while (movimientos < 9 && ganador == 0) {
        system("cls"); // Limpia la pantalla (Windows), usa "clear" en Linux/Mac
        printf("\n========== JUEGO TRES EN RAYA ==========\n");
        mostrarTablero(tablero);
        pedirMovimiento(jugador, tablero);

        ganador = verificarGanador(tablero);
        movimientos++;

        // Cambio de jugador
        if (ganador == 0) {
            if (jugador == 'X') {
                jugador = 'O';
            } else {
                jugador = 'X';
            }
        }
    }

    system("cls");
    printf("\n========== JUEGO TRES EN RAYA ==========\n");
    mostrarTablero(tablero);

    if (ganador == 1) {
        printf("\n?? ¡Felicidades! El jugador '%c' ha ganado. ??\n\n", jugador);
    } else {
        printf("\n?? ¡Empate! No hay ganador. ??\n\n");
    }

    return 0;
}

// Inicializa el tablero con espacios vacíos
void inicializarTablero(char tablero[3][3]) {
    int i, j; // Declaración de variables fuera del bucle
    for (i = 0; i < 3; i++) {
        for (j = 0; j < 3; j++) {
            tablero[i][j] = ' ';
        }
    }
}

// Muestra el tablero en pantalla con un formato bonito
void mostrarTablero(char tablero[3][3]) {
    int i, j; // Declaración fuera del bucle
    printf("\n     0   1   2\n");
    printf("   -------------\n");
    for (i = 0; i < 3; i++) {
        printf(" %d |", i);
        for (j = 0; j < 3; j++) {
            printf(" %c |", tablero[i][j]);
        }
        printf("\n   -------------\n");
    }
}

// Verifica si el movimiento es válido
int movimientoValido(char tablero[3][3], int fila, int columna) {
    if (fila >= 0 && fila < 3 && columna >= 0 && columna < 3 && tablero[fila][columna] == ' ') {
        return 1;
    }
    return 0;
}

// Pide el movimiento al jugador con validación
void pedirMovimiento(char jugador, char tablero[3][3]) {
    int fila = -1, columna = -1; // Declaración fuera del bucle
    char entrada[10];            // Para capturar la entrada

    while (1) {
        printf("\nTurno del jugador '%c'. Introduce fila y columna (ej: 0 1): ", jugador);
        fgets(entrada, sizeof(entrada), stdin);

        // Validar entrada
        if (sscanf(entrada, "%d %d", &fila, &columna) == 2) {
            if (movimientoValido(tablero, fila, columna)) {
                tablero[fila][columna] = jugador;
                break;
            } else {
                printf("? Movimiento inválido. La casilla está ocupada o fuera de rango. Intenta de nuevo.\n");
            }
        } else {
            printf("? Entrada inválida. Debes introducir dos números separados por un espacio. Intenta de nuevo.\n");
        }
    }
}

// Verifica si hay un ganador
int verificarGanador(char tablero[3][3]) {
    int i; // Declaración fuera del bucle

    for (i = 0; i < 3; i++) {
        // Verificar filas y columnas
        if ((tablero[i][0] == tablero[i][1] && tablero[i][1] == tablero[i][2] && tablero[i][0] != ' ') ||
            (tablero[0][i] == tablero[1][i] && tablero[1][i] == tablero[2][i] && tablero[0][i] != ' ')) {
            return 1;
        }
    }

    // Verificar diagonales
    if ((tablero[0][0] == tablero[1][1] && tablero[1][1] == tablero[2][2] && tablero[0][0] != ' ') ||
        (tablero[0][2] == tablero[1][1] && tablero[1][1] == tablero[2][0] && tablero[0][2] != ' ')) {
        return 1;
    }

    return 0; // No hay ganador
}

