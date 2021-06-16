//
// Created by Cedric Zitzmann on 01.06.2021.
//

#include "circ.h"
#include "../include/sdlinterf.h"

void Circ::draw() {
    sdlDrawCirc(this->mX, this->mY, this->getWidth(), this->getHeight(), this->getColor().getR(), this->getColor().getG(), this->getColor().getB());
}

void Circ::undraw() {
    sdlDrawCirc(this->mX, this->mY, this->getWidth(), this->getHeight(), 0, 0, 0);
}

GraphicObject * Circ::clone() const {
    return new Circ(*this);
}