#include <math.h>
#include <stdio.h>

float der(float A, float deltax) {
    if (deltax == 0.0) {
        return A;
    }
    return (cos(A + deltax) - (A - deltax)) / (2 * deltax);
}