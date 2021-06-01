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

#define MAX_RECTS 40
#define MILLIS_SLEEP 100

#pragma clang diagnostic push
#pragma ide diagnostic ignored "EndlessLoop"

// damit wir die Funktionen aus <cstdlib> ohne std::... aufrufen können
using namespace std;

int randPM(int n, bool negatives = true);
int randPos(int range, int dist);
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
        /*for(auto &rect : rects) {
            rect = new Rect(Color::random(), SDL_X_SIZE / 2, SDL_Y_SIZE / 2, randPM(30, false), randPM(30, false), randPM(10), randPM(10));
        }*/

        // This is short for:
        // for(int i = 0; i < MAX_RECTS; ++i) {
        //     rects[i] = new Rect(Color::random(), SDL_X_SIZE / 2, SDL_Y_SIZE / 2, 5, 5, 3, 2);
        // }

        // First rect in middle of screen
        rects[0] = new Rect(Color::random(), SDL_X_SIZE / 2, SDL_Y_SIZE / 2, SDL_X_SIZE / 5, SDL_Y_SIZE / 5);

        // Update window
        sdlUpdate();
        sdlMilliSleep(MILLIS_SLEEP);

        // Other elements in array are a copy of the previous one with random positions
        for(int i = 1; i < MAX_RECTS; ++i) {

            // call "Copy constructor"
            rects[i] = new Rect(*rects[i - 1]);

            // Set random pos
            rects[i]->setPos(randPos(SDL_X_SIZE, rects[i]->getWidth()), randPos(SDL_Y_SIZE, rects[i]->getHeight()));

            // Update window
            sdlUpdate();
            sdlMilliSleep(MILLIS_SLEEP);
        }



        // Set last rect to center of middle of left side of the screen
        rects[MAX_RECTS - 1]->setPos(SDL_X_SIZE / 4, SDL_Y_SIZE / 2);

        // Update window
        sdlUpdate();
        sdlMilliSleep(MILLIS_SLEEP);

        // Count backwards and moveOnTop
        for(int i = MAX_RECTS - 2; i >= 0; --i) {
            rects[i]->moveOnTop(*rects[i + 1]);

            // Update window
            sdlUpdate();
            sdlMilliSleep(MILLIS_SLEEP);
        }




        rects[0]->setPos(3 * SDL_X_SIZE / 4, SDL_Y_SIZE / 2);

        // Update window
        sdlUpdate();
        sdlMilliSleep(MILLIS_SLEEP);

        // Count forward
        for(int i = 1; i < MAX_RECTS; ++i) {
            rects[i]->moveOnTop(*rects[i - 1]);

            // Update window
            sdlUpdate();
            sdlMilliSleep(MILLIS_SLEEP);
        }


        // Count backwards and destroy objects
        for(int i = MAX_RECTS - 1; i >= 0; --i) {
            delete rects[i];

            // Update window
            sdlUpdate();
            sdlMilliSleep(MILLIS_SLEEP);
        }

        // Solange noch Objekte vorhanden sind
        /*for(int n = MAX_RECTS; n > 0; ) {
            sdlMilliSleep(16);

            for(int i = 0; i < n; ++i) {
                if(rects[i] != nullptr) {
                    flyAndTriggerBounceOf(*rects[i], rects, i, &n, true);
                }
            }

            sdlUpdate();
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

        if(rect.getHeight() == 0 || rect.getWidth() == 0) {
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
inline int randPM(int n, bool negatives) {
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

/**
 * Generate random position between range and distance
 * @param range Range
 * @param dist Distance
 * @return Random int
 */
inline int randPos(int range, int dist) {
    return dist + rand() % (range - 2 * dist);
}

#pragma clang diagnostic pop