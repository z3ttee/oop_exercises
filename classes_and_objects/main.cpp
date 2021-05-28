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

#pragma clang diagnostic push
#pragma ide diagnostic ignored "EndlessLoop"

// damit wir die Funktionen aus <cstdlib> ohne std::... aufrufen können
using namespace std;

int randPM(int n);
void flyAndTriggerBounceOf(Rect &rect);

int main(void) {
    srand(time(nullptr));
    sdlInit();  // Grafik-Fenster aufmachen

  // Hier braucht man eigene { } um die Punkt-Variablen,
  // damit die Punkt-Objekte am Ende der { }
  // wieder automatisch freigegeben werden,
  // *bevor* die SDL mit sdlExit abgedreht wird
  // (sonst würde der Destruktor des Punktes p am Programmende versuchen,
  // den Punkt mit undraw() zu löschen, obwohl das Grafik-Fenster schon weg ist
  // ==> Absturz!)
  { 
    // In der folgenden Zeile stecken gleich 2 Konstruktor-Aufrufe:
    // * Zuerst wird mit Color(...) ein Objekt der Klasse Color angelegt.
    //   Es ist anonym (kein Name, keine eigene Variable)
    //   und temporär (wird als Parameter an den Rect-Konstruktor übergeben
    //   und verschwindet dann gleich wieder).
    // * Dann wird eine neue Variable p angelegt,
    //   die ein Objekt der Klasse Rect enthält,
    //   Dieser Punkt p wird durch den Aufruf des Konstruktors
    //   auf "weiß" und "Fenster-Mitte" initialisiert.

    Rect p(Color(255, 255, 255), SDL_X_SIZE / 2, SDL_Y_SIZE / 2, 5, 5, 3, 2);
    Rect p2(Color(255, 200, 100), SDL_X_SIZE / 2, SDL_Y_SIZE / 2, 10, 10, 5, 5);

    for (;;) {
      sdlMilliSleep(20);   // "Bremse"

      flyAndTriggerBounceOf(p);
      flyAndTriggerBounceOf(p2);

      sdlUpdate();    // die von fly intern ausgeführten Grafik-Operationen
                      // wirklich auf dem Bildschirm anzeigen
    } 
  }

  sdlExit();  // Grafik-Fenster zumachen

  exit(EXIT_SUCCESS);
}

/**
 * Let the rect fly and bounce of the walls
 * @param rect
 */
void flyAndTriggerBounceOf(Rect &rect) {
    bool didBounceOf = !rect.fly(true);

    if(didBounceOf) {
        rect.scale(90, 90);

        if(rect.getHH() == 0 || rect.getHB() == 0) {
            rect.setPos(SDL_X_SIZE / 2, SDL_Y_SIZE / 2);
            rect.setSpeed(randPM(10), randPM(10));
            rect.setSize(rand() % 30 + 1, rand() % 30 + 1);

            // Set random color is optional
            rect.setColor(Color(rand() % 255 + 10, rand() % 255 + 10, rand() % 255 + 10));
        }
    }
}

/**
 * Generates number between -n and n but not 0
 * @param n
 * @return int
 */
int randPM(int n) {
    int rnd = 0;

    do {
        rnd = (rand() % (n*2)) - n;
    } while (rnd == 0);

    return rnd;
}

#pragma clang diagnostic pop