
#include <windows.h> //Para PAUSE
#include <conio.h>
#include <stdio.h>   //Para PRINTF y SCANF
//#include <iostream>  //Para CIN y COUT
#include <stdlib.h>  //Para random

#define UP      72
#define DOWN    80
#define RIGHT   77
#define LEFT    75
#define ESC     27

int body[200][2];	// Cuerpo de la serpiente (sus puntos)
int n = 1;			// Contador para recorrer el cuerpo
int tam = 4;		// Tamaño de la serpiente
int x=10, y=12;		// Posición de la cabeza
int dir = 2;		// Dirección de movimiento
int xf, yf;			// Posición de la comida
int clock, steps;	// Cambios de velocidad y pasos
int score = 0;		// Puntuación
int delay = 150;	// Tiempo entre pasos
bool end = false;	// Indicador de fin del juego

char tecla;			// Tecla pulsada por el jugador
char userName[20];	// Nombre del jugador
char vel = 'G';		// Indicador de velocidad

// Situar el cursor en un punto de la consola
void gotoxy(int x, int y) {

    HANDLE meh;
    meh = GetStdHandle(STD_OUTPUT_HANDLE);

    COORD SPos;
    SPos.X = x;
    SPos.Y = y;

    SetConsoleCursorPosition(meh, SPos);
}

// Dibujar los límites del juego
void limit() {

    // ESQUINAS
    gotoxy(3,  3 ); printf("%c", 201);
    gotoxy(77, 3 ); printf("%c", 187);
    gotoxy(3,  23); printf("%c", 200);
    gotoxy(77, 23); printf("%c", 188);

    // HORIZONTALES
    for(int i=4; i<77; i++) {
        gotoxy(i, 3); printf("%c", 205);
        gotoxy(i, 23); printf("%c", 205);
    }

    // VERTICALES
    for(int i=4; i<23; i++) {
        gotoxy(3,  i); printf("%c", 186);
        gotoxy(77, i); printf("%c", 186);
    }
}

// Borrar el final de la serpiente
void eraseBody() {

    gotoxy(body[n][0], body[n][1]);
    printf(" ");
}

// Actualizar la información del cuerpo
void save_pos() {

    body[n][0] = x;
    body[n][1] = y;
    n++;
    if(n == tam) n = 1;
}

// Dibujar el inicio de la serpiente
void createBody() {

	gotoxy(x, y);
	printf("*");
}

// Comprobar si se ha alcanzado la comida
void food() {

    if(x == xf && y == yf) {

        xf = rand()%73 + 4;
        yf = rand()%19 + 4;
        gotoxy(xf, yf); printf("%c", 4);
        tam++;
        if(vel == 'G') score += 15;
        else if(vel == 'F') score += 20;
        else if(vel == 'E') score += 25;
        else if(vel == 'D') score += 30;
        else if(vel == 'C') score += 35;
        else if(vel == 'B') score += 40;
        else score += 45;
    }
}

// Obtener instrucciones del jugador
void direction() {

    if(kbhit()) {

        tecla = getch();

        switch(tecla) {

            case UP:
                if(dir != 1) dir = 0;
                break;

            case DOWN:
                if(dir != 0) dir = 1;
                break;

            case RIGHT:
                if(dir != 3) dir = 2;
                break;

            case LEFT:
                if(dir != 2) dir = 3;
                break;
        }
    }
}

// Comprobar si la serpiente ha muerto
bool gameOver() {

    if (y == 3 || y == 23  || x == 3 || x == 77) {
        end = true;
        return true;
    }

    for(int i=tam-1; i>0; i--) {

        if(body[i][0] == x && body[i][1] == y ) {
            end = true;
            return true;
        }
    }

    return false;
}


int main() {

    printf("\n    SNAKE BY PABLO DÁVILA HERRERO");
    printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\nName: ");
    scanf("%s", userName);

    // Inicialización
    limit(); // Límite caja
    xf = rand()%73 + 4; // Comida
    yf = rand()%19 + 4;
    gotoxy(xf, yf); printf("%c", 4);

    while(tecla != ESC && gameOver() != true) {

        eraseBody();
        save_pos();

        steps++;
        food();

        direction();
        direction();
        if(dir == 0) y--;
        else if(dir == 1) y++;
        else if(dir == 2) x++;
        else x--;
        createBody();

        // Incremento de velocidad cada 80 pasos
        clock++;
        if(clock == 80 && delay != 60) {

            delay -= 15;
            clock = 0;

            if     (delay == 135) vel = 'F';
            else if(delay == 120) vel = 'E';
            else if(delay == 105) vel = 'D';
            else if(delay ==  90) vel = 'C';
            else if(delay ==  75) vel = 'B';
            else vel = 'A';
        }

        // Imprimir información
        gotoxy(4, 2); printf("SCORE: %d    STEPS: %d    VEL: %c", score, steps, vel);

        Sleep(delay);
    }

    if(end == true) {

        FILE *Log;
        Log = fopen ("Score history.txt", "a");

        fprintf(Log, "\n\nuserName: %s\nScore: %i\nSteps: %i", userName, score, steps);
    }

    printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
    system("pause");
    return 0;
}

