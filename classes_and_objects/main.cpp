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

#define MAX_RECTS 30

#pragma clang diagnostic push
#pragma ide diagnostic ignored "EndlessLoop"

// damit wir die Funktionen aus <cstdlib> ohne std::... aufrufen können
using namespace std;

int randPM(int n, bool negatives = true);
void flyAndTriggerBounceOf(Rect &rect, Rect *rects[], int currentRectIndex, int *livingObjects, bool destroyRect = false);

int main() {
    srand(time(nullptr));
    sdlInit();  // Grafik-Fenster aufmachen

    Rect *rects[MAX_RECTS];

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
        for(auto &rect : rects) {
            rect = new Rect(Color::random(), SDL_X_SIZE / 2, SDL_Y_SIZE / 2, randPM(30, false), randPM(30, false), randPM(10), randPM(10));
        }

        // This is short for:
        // for(int i = 0; i < MAX_RECTS; ++i) {
        //     rects[i] = new Rect(Color::random(), SDL_X_SIZE / 2, SDL_Y_SIZE / 2, 5, 5, 3, 2);
        // }

        // Solange noch Objekte vorhanden sind
        for(int n = MAX_RECTS; n > 0; ) {
            sdlMilliSleep(16);

            for(int i = 0; i < n; ++i) {
                if(rects[i] != nullptr) {
                    flyAndTriggerBounceOf(*rects[i], rects, i, &n, true);
                }
            }

            sdlUpdate();
        }

        /*Rect p(Color(255, 255, 255), SDL_X_SIZE / 2, SDL_Y_SIZE / 2, 5, 5, 3, 2);
        Rect p2(Color(255, 200, 100), SDL_X_SIZE / 2, SDL_Y_SIZE / 2, 10, 10, 5, 5);
        Rect p3(Color(255, 20, 200), SDL_X_SIZE / 2, SDL_Y_SIZE / 2, 2, 3, -6, -6);
        Rect p4(Color(255, 110, 100), SDL_X_SIZE / 2, SDL_Y_SIZE / 2, 6, 6, 3, 3);
        Rect p5(Color(255, 230, 140), SDL_X_SIZE / 2, SDL_Y_SIZE / 2, 8, 12, -3, -4);*/

        /*for (;;) {
          sdlMilliSleep(16);

          flyAndTriggerBounceOf(p);
          flyAndTriggerBounceOf(p2);
          flyAndTriggerBounceOf(p3);
          flyAndTriggerBounceOf(p4);
          flyAndTriggerBounceOf(p5);

          sdlUpdate();    // die von fly intern ausgeführten Grafik-Operationen
                          // wirklich auf dem Bildschirm anzeigen
        }*/
    }

    sdlExit();
    exit(EXIT_SUCCESS);
}

/**
 * Let the rect fly and bounce of the walls
 * @param rect
 */
void flyAndTriggerBounceOf(Rect &rect, Rect *rects[], int currentRectIndex, int *livingObjects, bool destroyRect) {
    bool didBounceOf = !rect.fly(true);

    if(didBounceOf) {
        rect.scale(90, 90);

        if(rect.getHH() == 0 || rect.getHB() == 0) {
            if(destroyRect) {
                
                delete rects[currentRectIndex];
                rects[currentRectIndex] = nullptr;
                --(*livingObjects);

            } else {
                rect.setPos(SDL_X_SIZE / 2, SDL_Y_SIZE / 2);
                rect.setSpeed(randPM(10), randPM(10));
                rect.setSize(randPM(30, false), randPM(30, false));

                // Set random color is optional
                rect.setColor(Color::random());
            }
        }

    }
}

/**
 * Generates number between -n and n but not 0
 * @param n
 * @return int
 */
int randPM(int n, bool negatives) {
    int rnd;

    do {
        if(negatives) {
            rnd = (rand() % (n*2)) - n;
        } else {
            rnd = (rand() % (n) + 1);
        }
    } while (rnd == 0);

    return rnd;
}

#pragma clang diagnostic pop