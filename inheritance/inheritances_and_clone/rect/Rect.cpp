//
// Created by Cedric Zitzmann on 28.05.2021.
//

#include "../include/sdlinterf.h"
#include "Rect.h"

void Rect::draw() {
    sdlDrawRect(mX, mY, mWidth, mHeight, mRGB.getR(), mRGB.getG(), mRGB.getB());
}

void Rect::undraw() {
    sdlDrawRect(mX, mY, mWidth, mHeight, 0, 0, 0);
}

GraphicObject * Rect::clone() const {
    return new Rect(*this);
}