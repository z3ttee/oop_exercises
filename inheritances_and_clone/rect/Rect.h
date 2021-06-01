//
// Created by Cedric Zitzmann on 28.05.2021.
//

#ifndef POINT_RECT_H
#define POINT_RECT_H

#include "../parent/GraphicObject.h"

class Rect: public GraphicObject {

public:
    Rect(const Color &color, int x, int y, int width, int height, int sx = 0, int sy = 0) : GraphicObject(color, x, y, width, height, sx, sy) {
        draw();
    }

    virtual ~Rect() override {
        undraw();
    }

    /*virtual Rect *clone() const override {
        return new Rect(*this);
    }*/

    virtual void draw() override;
    virtual void undraw() override;
    GraphicObject *clone() const override;
};


#endif //POINT_RECT_H
