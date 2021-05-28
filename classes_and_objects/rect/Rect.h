//
// Created by Cedric Zitzmann on 28.05.2021.
//

#ifndef POINT_RECT_H
#define POINT_RECT_H

#include "../color.h"

class Rect {

public:
    Rect(const Color &color, int x, int y, int hB, int hH, int sx = 0, int sy = 0): mRGB(color.getR(), color.getG(), color.getB()), mX(x), mY(y), mHB(hB), mHH(hH), mSX(sx), mSY(sy) {
        draw();
    }

    Color getColor() const { return mRGB; }

    int getX() const { return mX; }
    int getY() const { return mY; }
    int getSX() const { return mSX; }
    int getSY() const { return mSY; }
    int getHB() const { return mHB; }
    int getHH() const { return mHH; }

    void move(int dx, int dy);
    void draw();
    void undraw();

    void setSize(int hB, int hH);
    void setSpeed(int sx, int sy);
    void setColor(const Color &color);
    void scale(int scaleX, int scaleY);
    void setPos(int x, int y);

    bool fly(bool bounce = false);

private:
    Color mRGB;
    int mX, mY;
    int mSX, mSY;
    int mHB, mHH;
};


#endif //POINT_RECT_H
