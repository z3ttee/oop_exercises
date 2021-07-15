//
// Created by Cedric Zitzmann on 06.07.2021.
//

#include "../parent/GraphicObject.h"

class Composition: public GraphicObject {

public:

    Composition(int x, int y, int sx, int sy, int objectsSize) : GraphicObject(Color(0,0,0), x, y, 0, 0, sx, sy), objectsSize(objectsSize), objectsCount(0) ,objects(new GraphicObject*[objectsSize]) {}
    virtual ~Composition() override {
        undraw();
    }

    virtual void draw() override;
    virtual void undraw() override;
    GraphicObject *clone() const override;

protected:
    GraphicObject **objects;
    int objectsCount;
    int objectsSize;
};
