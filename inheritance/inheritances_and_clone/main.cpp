// Erstes C++: Geom. Objekte: Punkt
//
// Aufruf: point
//
// Klaus Kusche, 2020

// Die C++-Version von stdlib.h (u.a. für exit(...) )
#include <cstdlib>
#include <iostream>
#include <ctime>
// Wir haben kein Terminal-I/O, daher brauchen wir <iostream> nicht.

// Der Header für meine Grafik-Funktionen
// Im selben Verzeichnis wie der aktuelle File, daher "", nicht <>
#include "include/sdlinterf.h"
#include "rect/Rect.h"
#include "circ/circ.h"

#define MILLIS_SLEEP 16

#pragma clang diagnostic push
#pragma ide diagnostic ignored "EndlessLoop"

// damit wir die Funktionen aus <cstdlib> ohne std::... aufrufen können
using namespace std;

GraphicObject *genRndGraphicObj();
inline int randPM(int n);

int snakes = 12;
int snakeLength = 10;
int objectsCount = snakes * snakeLength;

int main() {
    srand(time(nullptr));
    sdlInit();  // Grafik-Fenster aufmachen

    GraphicObject *objects[objectsCount];

    /*
     * Hier braucht man eigene { } um die Punkt-Variablen,
     * damit die Punkt-Objekte am Ende der { }
     * wieder automatisch freigegeben werden,
     * *bevor* die SDL mit sdlExit abgedreht wird
     * (sonst würde der Destruktor des Punktes p am Programmende versuchen,
     * den Punkt mit undraw() zu löschen, obwohl das Grafik-Fenster schon weg ist
     * ==> Absturz!)
     */
    {

        for(int i = 0; i < objectsCount; ++i) {
            // If index is dividable by snakeLength, add new Element
            if(i % snakeLength == 0) {
                objects[i] = genRndGraphicObj();
            } else {
                objects[i] = objects[i - 1]->clone();
                objects[i]->move(3 * objects[i]->getSpeedX(), 3 * objects[i]->getSpeedY());
            }
        }

        for(;;) {
            sdlMilliSleep(MILLIS_SLEEP);
            sdlUpdate();

            for(auto &object : objects) {
                if(object != nullptr) {
                    object->fly(true);
                }
            }
        }
    }

    sdlExit();
    exit(EXIT_SUCCESS);
}

/**
 * Randomly generate circle or rect
 * @return Pointer to an GraphicObject
 */
GraphicObject *genRndGraphicObj() {
    if(rand() % 2 == 0) {
        return new Rect(Color::random(), SDL_X_SIZE / 2, SDL_Y_SIZE / 2, 10, 10, randPM(7), randPM(7));
    } else {
        return new Circ(Color::random(), SDL_X_SIZE / 2, SDL_Y_SIZE / 2, 13, 13, randPM(7), randPM(7));
    }
}

/**
 * Generates number between -n and n but not 0
 * @param n
 * @return int
 */
inline int randPM(int n) {
    return ((rand() % n) + 1) - ((rand() % 2) * (n + 1));
}

#pragma clang diagnostic pop