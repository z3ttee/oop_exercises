//
// Created by Cedric Zitzmann on 28.05.2021.
//

#include "../include/sdlinterf.h"
#include "Rect.h"

void Rect::setSize(int hB, int hH) {
    undraw();
    mWidth = hB;
    mHeight = hH;
    draw();
}

void Rect::scale(int scaleX, int scaleY) {
    undraw();
    mWidth = (mWidth * scaleX) / 100;
    mHeight = (mHeight * scaleY) / 100;
    draw();
}

void Rect::setSpeed(int sx, int sy) {
    mSX = sx;
    mSY = sy;
}

void Rect::setColor(const Color &color) {
    mRGB = color;
    draw();
}

void Rect::setPos(int x, int y){
    undraw();
    mX = x;
    mY = y;
    draw();
}

void Rect::move(int dx, int dy) {
    undraw();
    mX += dx;
    mY += dy;
    draw();
}

bool Rect::fly(bool bounce) {
    bool ret = true;
    // Die Ursprungs-Koordinaten (0/0) des SDL-Fensters sind links oben
    // ==> x wächst nach rechts von 0 bis SDL_X_SIZE - 1
    // ==> y wächst nach unten von 0 bis SDL_Y_SIZE - 1
    // Prüfung auf Rand in waagrechter Richtung (x-Richtung): Rand, wenn ...
    // ... der Punkt nach rechts fliegt (mSX > 0)
    //     und weniger als mSX vom rechten Rand (SDL_X_SIZE) entfernt ist
    // ... oder der Punkt nach links fliegt (mSX < 0)
    //     und weniger als mSX (-mSX weil mSX < 0) vom linken Rand (0) weg ist
    if (((mSX > 0) && (mX >= SDL_X_SIZE - mSX - mWidth)) ||
        ((mSX < 0) && (mX < -mSX + mWidth))) {
        // Punkt würde in x-Richtung rausfliegen
        if (bounce) {
            // Vorzeichen der x-Richtung umdrehen ==> Punkt fliegt in Gegenrichtung
            mSX = -mSX;
            ret = false;
        } else {
            // nicht fliegen!
            return false;
        }
    }

    // dieselbe Prüfung für die y-Position des Punktes:
    // fliegt nach unten ==> mindestens mSY Abstand vom unteren Rand (SDL_Y_SIZE)
    // fliegt nach oben ==> mindestens -mSY Abstand vom oberen Rand (0)
    if (((mSY > 0) && (mY >= SDL_Y_SIZE - mSY - mHeight)) ||
        ((mSY < 0) && (mY < -mSY + mHeight))) {
        if (bounce) {
            mSY = -mSY;
            ret = false;
        }
        else {
            return false;
        }
    }

    move(mSX, mSY);
    return ret;
}

void Rect::draw() {
    sdlDrawRect(mX, mY, mWidth, mHeight, mRGB.getR(), mRGB.getG(), mRGB.getB());
}

void Rect::undraw() const {
    sdlDrawRect(mX, mY, mWidth, mHeight, 0, 0, 0);
}

void Rect::moveOnTop(const Rect &rect) {
    this->undraw();
    this->mX = rect.mX;
    this->mY = rect.mY;
    this->draw();
}