#ifndef GW_COMMONTYPE_H
#define GW_COMMONTYPE_H

namespace GW {

struct Color {
    union {
        struct {
            unsigned r, g, b, a;
        };

        struct {
            float rf, gf, bf, af;
        };
    };

    Color(unsigned red, unsigned green, unsigned blue, unsigned alpha):
        r(red), g(green), b(blue), a(alpha) {}
    Color(unsigned red, unsigned green, unsigned blue):
        r(red), g(green), b(blue), a(255) {}

    Color(int red, int green, int blue, int alpha):
        r(red), g(green), b(blue), a(alpha) {}
    Color(int red, int green, int blue):
        r(red), g(green), b(blue), a(255) {}

    Color(float red, float green, float blue, float alpha):
        rf(red), gf(green), bf(blue), af(alpha) {}
    Color(float red, float green, float blue):
        rf(red), gf(green), bf(blue), af(1) {}
};


struct Point2D {
    union {
        struct {
            unsigned x, y;
        };

        struct {
            float xf, yf;
        };
    };

    Point2D() = default;
    Point2D(unsigned x, unsigned y): x(x), y(y){}
    Point2D(int x, int y): x(x), y(y) {}
    Point2D(float x, float y): xf(x), yf(y) {}

    unsigned *get_unsigned_array() { return new unsigned int[2] {x, y}; }
    float *get_float_array() { return new float[2] {xf, yf}; }
};


struct Point3D {
    union {
        struct {
            unsigned x, y ,z;
        };

        struct {
            float xf, yf, zf;
        };
    };

    Point3D(unsigned x, unsigned y, unsigned z):
        x(x), y(y), z(z) {}

    Point3D(int x, int y, int z):
        x(x), y(y), z(z) {}

    Point3D(float x, float y, float z):
        xf(x), yf(y), zf(z) {}

    unsigned *get_unsigned_array() { return new unsigned int[3] {x, y, z}; }
    float *get_float_array() { return new float[3] {xf, yf, zf}; }
};

};

#endif  // GWELT_COMMONTYPE_H
