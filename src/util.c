#include <stdlib.h>

// mouse_GetPosition = sfVector2i
// setPos = sfVector2f

#define MAX(x, y) (((x) > (y)) ? (x) : (y))
#define MIN(x, y) (((x) < (y)) ? (x) : (y))

int intClamp(int value, int minVal, int maxVal) {
    return MAX(minVal, MIN(maxVal, value));
}

sfVector2f vectorItoF(sfVector2i vectorToCpy) {

    sfVector2f vector;

    vector.x = vectorToCpy.x - 50;
    vector.y = vectorToCpy.y - 50;

    return vector;
}