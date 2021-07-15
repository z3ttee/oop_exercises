//
// Created by Cedric Zitzmann on 06.07.2021.
//

#include "comp.h"

Composition::Composition(const Composition &orig): GraphicObject(orig), objectsSize(orig.objectsSize), objectsCount(orig.objectsCount), objects(new GraphicObject *[objectsSize]) {

}

GraphicObject * Composition::clone() const {

    return new Composition(*this);
}

void Composition::draw() {

}

void Composition::undraw() {

}
