//
// Created by Cedric Zitzmann on 01.06.2021.
//

#include "../include/sdlinterf.h"
#include "GraphicObject.h"

void GraphicObject::setSize(int hB, int hH) {
    undraw();
    mWidth = hB;
    mHeight = hH;
    draw();
}

void GraphicObject::scale(int scaleX, int scaleY) {
    undraw();
    mWidth = (mWidth * scaleX) / 100;
    mHeight = (mHeight * scaleY) / 100;
    draw();
}

void GraphicObject::setSpeed(int sx, int sy) {
    mSX = sx;
    mSY = sy;
}

void GraphicObject::setColor(const Color &color) {
    mRGB = color;
    draw();
}

void GraphicObject::setPos(int x, int y){
    undraw();
    mX = x;
    mY = y;
    draw();
}

void GraphicObject::move(int dx, int dy) {
    undraw();
    mX += dx;
    mY += dy;
    draw();
}

bool GraphicObject::fly(bool bounce) {
    bool ret = true;

    if (((mSX > 0) && (mX >= SDL_X_SIZE - mSX - mWidth)) ||
        ((mSX < 0) && (mX < -mSX + mWidth))) {

        if (bounce) {
            // Vorzeichen der x-Richtung umdrehen ==> Punkt fliegt in Gegenrichtung
            mSX = -mSX;
            ret = false;
        } else {
            // nicht fliegen!
            return false;
        }
    }


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