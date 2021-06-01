//
// Created by Cedric Zitzmann on 28.05.2021.
//

class Color {
public:
    Color(int r = 0, int g = 0, int b = 0): mR(r), mG(g), mB(b){}

    int getR() const { return mR; }
    int getG() const { return mG; }
    int getB() const { return mB; }

    static Color random();

private:
    int mR, mG, mB;

};

#ifndef POINT_COLOR_H
#define POINT_COLOR_H

#endif //POINT_COLOR_H
