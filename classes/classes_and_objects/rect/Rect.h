//
// Created by Cedric Zitzmann on 28.05.2021.
//

#ifndef POINT_RECT_H
#define POINT_RECT_H

#include "../color/color.h"

class Rect {

public:
    Rect(const Color &color, int x, int y, int width, int height, int sx = 0, int sy = 0): mRGB(color.getR(), color.getG(), color.getB()), mX(x), mY(y), mWidth(width), mHeight(height), mSX(sx), mSY(sy) {
        draw();
    }

    Rect(const Rect &rect): mRGB(rect.getColor().getR() - 5, rect.getColor().getG() - 5, rect.getColor().getB() - 5), mX(rect.mX), mY(rect.mY), mWidth(rect.mWidth - 3), mHeight(rect.mHeight - 3), mSX(rect.mSX), mSY(rect.mSY) {
        draw();
    }

    ~Rect() {
        undraw();
    }

    Color getColor() const { return mRGB; }

    int getX() const { return mX; }
    int getY() const { return mY; }
    int getSpeedX() const { return mSX; }
    int getSpeedY() const { return mSY; }
    int getWidth() const { return mWidth; }
    int getHeight() const { return mHeight; }

    void move(int dx, int dy);
    void draw();
    void undraw() const;

    void setSize(int hB, int hH);
    void setSpeed(int sx, int sy);
    void setColor(const Color &color);
    void scale(int scaleX, int scaleY);
    void setPos(int x, int y);

    bool fly(bool bounce = false);
    void moveOnTop(const Rect &rect);

private:
    Color mRGB;
    int mX, mY;
    int mSX, mSY;
    int mWidth, mHeight;
};


#endif //POINT_RECT_H
