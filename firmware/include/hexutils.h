#ifndef HEXUTILS_H
#define HEXUTILS_H

#include <stdint.h>
#include <stdlib.h>
#include <math.h>

typedef struct {
    int x;
    int y;
} Point;

typedef struct {
    int q;
    int r;
} Hex;

inline Point hex_to_pixel(Hex h, int size) {
    const double sqrt3 = 1.73205080757; // Pre-calculated value of sqrt(3)
    int x = size * (3.0/2 * h.q);
    int y = size * (sqrt3 * (h.r*2 + h.q)/2);
    return (Point){x, y};
}

inline Hex pixel_to_hex(int x, int y, int size) {
    const double sqrt3 = 1.73205080757; // Pre-calculated value of sqrt(3)
    int q = (2.0/3 * x) / size;
    int r = (-1.0/3 * x + sqrt3/3 * y) / size;
    return (Hex){q, r};
}

inline int hex_distance(Hex h1, Hex h2) {
    return (abs(h1.q - h2.q) + abs(h1.r - h2.r) + abs((-h1.q-h1.r) - (-h2.q-h2.r))) / 2;
}

inline int hex_get_heading(Hex start, Hex end) {
    Hex dif=(Hex){end.q-start.q, end.r-start.r};
    if (dif.q < 0) {
        return dif.r > 0 ? 4:5;
    }
    else if (dif.q == 0) {
        return dif.r > 0 ? 3 : 0;
    }
    else {
        return dif.r == 0 ? 2 : 1;
    }
}

inline int hex_equal(Hex h1, Hex h2) {
    return (h1.q == h2.q) && (h1.r == h2.r);
}

#endif // HEXUTILS_H