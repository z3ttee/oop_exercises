//
// Created by Cedric Zitzmann on 01.06.2021.
//

#ifndef POINT_GRAPHICOBJECT_H
#define POINT_GRAPHICOBJECT_H

#include "../color/color.h"

class GraphicObject {

public:
    GraphicObject(const Color &color, int x, int y, int width, int height, int sx = 0, int sy = 0): mRGB(color.getR(), color.getG(), color.getB()), mX(x), mY(y), mWidth(width), mHeight(height), mSX(sx), mSY(sy) {}
    virtual ~GraphicObject() {}

    Color getColor() const { return mRGB; }

    int getX() const { return mX; }
    int getY() const { return mY; }
    int getSpeedX() const { return mSX; }
    int getSpeedY() const { return mSY; }
    int getWidth() const { return mWidth; }
    int getHeight() const { return mHeight; }

    void move(int dx, int dy);

    virtual void draw() = 0;
    virtual void undraw() = 0;
    virtual GraphicObject *clone() const = 0;

    void setSize(int hB, int hH);
    void setSpeed(int sx, int sy);
    void setColor(const Color &color);
    void scale(int scaleX, int scaleY);
    void setPos(int x, int y);

    bool fly(bool bounce = false);

protected:
    Color mRGB;
    int mX, mY;
    int mSX, mSY;
    int mWidth, mHeight;
};


#endif
