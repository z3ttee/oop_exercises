
#define MIN_RGB 30

#include <cstdlib>
#include "color.h"

Color Color::random() {
    return {
        rand() % 255 + MIN_RGB,
        rand() % 255 + MIN_RGB,
        rand() % 255 + MIN_RGB
    };
}