#ifndef CORE_H
#define CORE_H

#ifndef MAX_POLYN_SIDES
    #define MAX_POLYN_SIDES 32
#endif

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include <GL/glut.h>
// #include <GL/glew.h>
// #include <GL/gl.h>
// #include <GL/glu.h>

#define PI 3.14159265358979323846f
#define ELIPSIS_SEGMENTS 180

#define byte unsigned char

#define MAX(a, b) a > b ? a : b
#define MIN(a, b) a < b ? a : b

#define RED     (Color) {.r = 219, .g = 0,   .b = 0,   .a = 255}
#define GREEN   (Color) {.r = 0,   .g = 146, .b = 62,  .a = 255}
#define BLUE    (Color) {.r = 1,   .g = 33,  .b = 105, .a = 255}

#define YELLOW  (Color) {.r = 248, .g = 193, .b = 0,   .a = 255}
#define CYAN    (Color) {.r = 19,  .g = 218, .b = 233, .a = 255}
#define MAGENTA (Color) {.r = 250, .g = 45,  .b = 208, .a = 255}

#define PURPLE  (Color) {.r = 174, .g = 55,  .b = 255, .a = 255}
#define ORANGE  (Color) {.r = 255, .g = 124, .b = 5,   .a = 255}
#define GREY    (Color) {.r = 169, .g = 169, .b = 169, .a = 255}



// ================================
//            ND Structs
// ================================

typedef struct _vec3 {
    float x;
    float y;
    float z;
} Vec3;

typedef struct _poly3 {
    Vec3 v1;
    Vec3 v2;
    Vec3 v3;
} Poly3;

typedef struct _poly4 {
    Vec3 v1;
    Vec3 v2;
    Vec3 v3;
    Vec3 v4;
} Poly4;

typedef struct _polyn {
    Vec3 v[MAX_POLYN_SIDES];
} PolyN;



// ================================
//            2D Structs
// ================================

typedef struct _color {
    byte r;
    byte g;
    byte b;
    byte a;
} Color;

typedef struct _vec2 {
    float x;
    float y;
} Vec2;

typedef struct _triangle {
    Vec3 pos;
    float barycenter;
} Triangle;

typedef struct _square {
    Vec3 pos;
    float size;
} Square;

typedef struct _rectangle {
    Vec3 pos;
    float size_x;
    float size_y;
} Rectangle;

typedef struct _circle {
    Vec3 pos;
    float radius;
} Circle;

typedef struct _elipsis {
    Vec3 pos;
    float radius_x;
    float radius_y;
} Elipsis;



// ================================
//            3D Structs
// ================================

typedef struct _cube {
    Vec3 pos;
    Square faces[6];
} Cube;

typedef struct _cuboid {
    Vec3 pos;
    Rectangle faces[6];
} Cuboid;

typedef struct _tetrahedron {
    Vec3 pos;
    Triangle base;
    Poly3 trigs[3];
} Tetrahedron;

typedef struct _pyramid {
    Vec3 pos;
    Square base;
    Poly3 trigs[4];
} Pyramid;

typedef struct _sphere {
    Vec3 pos;
    float radius;
} Sphere;

typedef struct _ellipsoid {
    Vec3 pos;
    float radius_x;
    float radius_y;
    float radius_z;
} Ellipsoid;



// ================================
//         Create functions
// ================================

Triangle triangle_new(float x, float y, float z, float barycenter) {
    return (Triangle) {
        .pos.x = x,
        .pos.y = y,
        .pos.z = z,
        .barycenter = barycenter
    };
}

Square square_new(float x, float y, float z, float size) {
    return (Square) {
        .pos.x = x,
        .pos.y = y,
        .pos.z = z,
        .size = size
    };
}

Rectangle rectangle_new(float x, float y, float z, float size_x, float size_y) {
    return (Rectangle) {
        .pos.x = x,
        .pos.y = y,
        .pos.z = z,
        .size_x = size_x,
        .size_y = size_y
    };
}

Circle circle_new(float x, float y, float z, float radius) {
    return (Circle) {
        .pos.x = x,
        .pos.y = y,
        .pos.z = z,
        .radius = radius
    };
}

Elipsis elipsis_new(float x, float y, float z, float radius_x, float radius_y) {
    return (Elipsis) {
        .pos.x = x,
        .pos.y = y,
        .pos.z = z,
        .radius_x = radius_x,
        .radius_y = radius_y
    };
}

Poly3 poly3_new(Vec3 v1, Vec3 v2, Vec3 v3) {
    return (Poly3) {
        .v1 = v1,
        .v2 = v2,
        .v3 = v3
    };
}

Poly4 poly4_new(Vec3 v1, Vec3 v2, Vec3 v3, Vec3 v4) {
    return (Poly4) {
        .v1 = v1,
        .v2 = v2,
        .v3 = v3,
        .v4 = v4,
    };
}

PolyN polyn_new(Vec3 v[MAX_POLYN_SIDES]) {

    PolyN p;

    for (size_t i = 0; i < MAX_POLYN_SIDES; i++) {
        p.v[i] = v[i];
    }

    return p;
}



// ================================
//          Draw Functions
// ================================

void primitive_draw_square(Vec3 pos, float size, Color color) {

    float relative_size = size/2.0f;

    glColor4ub(color.r, color.g, color.b, color.a);

    glBegin(GL_QUADS);
        glVertex3f(pos.x - relative_size, pos.y - relative_size, pos.z);
        glVertex3f(pos.x - relative_size, pos.y + relative_size, pos.z);
        glVertex3f(pos.x + relative_size, pos.y + relative_size, pos.z);
        glVertex3f(pos.x + relative_size, pos.y - relative_size, pos.z);
    glEnd();

    return;
}

void primitive_draw_rectangle(Vec3 pos, float size_x, float size_y, Color color) {

    float relative_size_x = size_x/2.0f;
    float relative_size_y = size_y/2.0f;

    glColor4ub(color.r, color.g, color.b, color.a);

    glBegin(GL_QUADS);
        glVertex3f(pos.x - relative_size_x, pos.y - relative_size_y, pos.z);
        glVertex3f(pos.x - relative_size_x, pos.y + relative_size_y, pos.z);
        glVertex3f(pos.x + relative_size_x, pos.y + relative_size_y, pos.z);
        glVertex3f(pos.x + relative_size_x, pos.y - relative_size_y, pos.z);
    glEnd();

    return;
}

void primitive_draw_circle(Vec3 pos, float radius, Color color) {

    glColor4ub(color.r, color.g, color.b, color.a);

    glBegin(GL_TRIANGLE_FAN);

        for (int i = 0; i < ELIPSIS_SEGMENTS; i++) {
            float angle = 2.0f * PI * (float)i / (float) ELIPSIS_SEGMENTS;

            float x = radius * cosf(angle);
            float y = radius * sinf(angle);

            glVertex3f(x + pos.x, y + pos.y, pos.z);
        }

    glEnd();

    return;
}

void primitive_draw_elipsis(Vec3 pos, float radius_x, float radius_y, Color color) {

    glColor4ub(color.r, color.g, color.b, color.a);

    glBegin(GL_TRIANGLE_FAN);

        for (int i = 0; i < ELIPSIS_SEGMENTS; i++) {
            float angle = 2.0f * PI * (float)i / (float) ELIPSIS_SEGMENTS;

            float x = radius_x * cosf(angle);
            float y = radius_y * sinf(angle);

            glVertex3f(x + pos.x, y + pos.y, pos.z);
        }

    glEnd();

    return;
}

void primitive_draw_poly3(Vec3 v1, Vec3 v2, Vec3 v3, Color color) {

    glColor4ub(color.r, color.g, color.b, color.a);

    glBegin(GL_TRIANGLES);
        glVertex3f(v1.x, v1.y, v1.z);
        glVertex3f(v2.x, v2.y, v2.z);
        glVertex3f(v3.x, v3.y, v3.z);
    glEnd();

    return;
}

void primitive_draw_poly4(Vec3 v1, Vec3 v2, Vec3 v3, Vec3 v4, Color color) {

    glColor4ub(color.r, color.g, color.b, color.a);

    glBegin(GL_QUADS);
        glVertex3f(v1.x, v1.y, v1.z);
        glVertex3f(v2.x, v2.y, v2.z);
        glVertex3f(v3.x, v3.y, v3.z);
        glVertex3f(v4.x, v4.y, v4.z);
    glEnd();

    return;
}

void primitive_draw_polyn(Vec3 v[MAX_POLYN_SIDES], Color color) {

    glColor4ub(color.r, color.g, color.b, color.a);

    glBegin(GL_POLYGON);
        for (size_t i = 0; i < MAX_POLYN_SIDES; i++) {
            glVertex3f(v[i].x, v[i].y, v[i].z);
        }
    glEnd();

    return;
}

void draw_square(Square s, Color color) {
    primitive_draw_square(s.pos, s.size, color);
}


void primitive_draw_cube(Vec3 pos, Square faces[6], Color colors[6]) {

    /* for (size_t i = 0; i < 6; i++) {
        faces[i].pos = pos;
    } */

    Vec3 trans_x = {.x = faces[0].size/2.0f, .y = 0.0f, .z = 0.0f};
    Vec3 trans_y = {.x = 0.0f, .y = faces[0].size/2.0f, .z = 0.0f};
    Vec3 trans_z = {.x = 0.0f, .y = 0.0f, .z = faces[0].size/2.0f};

    Vec3 rot_x = {.x = 1.0f, .y = 0.0f, .z = 0.0f};
    Vec3 rot_y = {.x = 0.0f, .y = 1.0f, .z = 0.0f};
    Vec3 rot_z = {.x = 0.0f, .y = 0.0f, .z = 1.0f};

    glPushMatrix();

        glTranslatef(pos.x, pos.y, pos.z);
        glTranslatef(trans_z.x, trans_z.y, trans_z.z);
        draw_square(faces[0], colors[0]);

    glPopMatrix();

    glPushMatrix();

        glTranslatef(pos.x, pos.y, pos.z);
        glTranslatef(trans_z.x, trans_z.y, -trans_z.z);
        glRotatef(90.0f, rot_z.x, rot_z.y, rot_z.z);
        draw_square(faces[0], colors[1]);

    glPopMatrix();

    glPushMatrix();

        glTranslatef(pos.x, pos.y, pos.z);
        glTranslatef(trans_y.x, trans_y.y, trans_y.z);
        glRotatef(90.0f, rot_x.x, rot_x.y, rot_x.z);
        draw_square(faces[0], colors[2]);

    glPopMatrix();

    glPushMatrix();

        glTranslatef(pos.x, pos.y, pos.z);
        glTranslatef(trans_y.x, -trans_y.y, trans_y.z);
        glRotatef(90.0f, -rot_x.x, rot_x.y, rot_x.z);
        draw_square(faces[0], colors[3]);

    glPopMatrix();

    glPushMatrix();

        glTranslatef(pos.x, pos.y, pos.z);
        glTranslatef(trans_x.x, trans_x.y, trans_x.z);
        glRotatef(90.0f, rot_y.x, rot_y.y, rot_y.z);
        draw_square(faces[0], colors[4]);

    glPopMatrix();

    glPushMatrix();

        glTranslatef(pos.x, pos.y, pos.z);
        glTranslatef(-trans_x.x, trans_x.y, trans_x.z);
        glRotatef(90.0f, rot_y.x, -rot_y.y, rot_y.z);
        draw_square(faces[0], colors[5]);

    glPopMatrix();

    return;
}



// ================================
//             Wrappers            
// ================================


void draw_rectangle(Rectangle r, Color color) {
    primitive_draw_rectangle(r.pos, r.size_x, r.size_y, color);
}

void draw_circle(Circle c, Color color) {
    primitive_draw_circle(c.pos, c.radius, color);
}

void draw_elipsis(Elipsis e, Color color) {
    primitive_draw_elipsis(e.pos, e.radius_x, e.radius_y, color);
}

void draw_poly3(Poly3 p, Color color) {
    primitive_draw_poly3(p.v1, p.v2, p.v3, color);
}

void draw_poly4(Poly4 p, Color color) {
    primitive_draw_poly4(p.v1, p.v2, p.v3, p.v4, color);
}

void draw_polyn(PolyN p, Color color) {
    primitive_draw_polyn(p.v, color);
}

#endif