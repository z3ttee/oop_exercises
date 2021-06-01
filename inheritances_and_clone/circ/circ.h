//
// Created by Cedric Zitzmann on 01.06.2021.
//

#ifndef POINT_CIRC_H
#define POINT_CIRC_H

#include "../parent/GraphicObject.h"

class Circ: public GraphicObject {

public:
    Circ(const Color &color, int x, int y, int width, int height, int sx = 0, int sy = 0) : GraphicObject(color, x, y, width, height, sx, sy) {
        draw();
    }

    virtual ~Circ() override {
        undraw();
    }

    virtual void draw() override;
    virtual void undraw() override;
    GraphicObject *clone() const override;

};


#endif //POINT_CIRC_H
