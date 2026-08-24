#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
// #include <GL/glew.h>
// #include <GL/gl.h>
// #include <GL/glu.h>
#include <GL/glut.h>

#define PI 3.14159265358979323846f
#define ELIPSIS_SEGMENTS 180

#define byte unsigned char

/* typedef struct _rgb {
    byte r;
    byte g;
    byte b;
} RGB;

typedef struct _rgba {
    byte r;
    byte g;
    byte b;
    byte a;
} RGBA; */

typedef struct _color {
    float r;
    float g;
    float b;
    float a;
} Color;

typedef struct _vec2 {
    float x;
    float y;
} Vec2;

typedef struct _vec3 {
    float x;
    float y;
    float z;
} Vec3;

typedef struct _triangle {
    Vec3 pos;
    float barycenter;
    Color color;
} Triangle;

typedef struct _square {
    Vec3 pos;
    float size;
    Color color;
} Square;

typedef struct _rectangle {
    Vec3 pos;
    float size_x;
    float size_y;
    Color color;
} Rectangle;

typedef struct _circle {
    Vec3 pos;
    float radius;
    Color color;
} Circle;

typedef struct _elipsis {
    Vec3 pos;
    float radius_x;
    float radius_y;
    Color color;
} Elipsis;

typedef struct _poly3 {
    Vec3 v1;
    Vec3 v2;
    Vec3 v3;
    Color color;
} Poly3;

typedef struct _poly4 {
    Vec3 v1;
    Vec3 v2;
    Vec3 v3;
    Vec3 v4;
    Color color;
} Poly4;

#define RED    (Color) {.r = 219, .g = 0,   .b = 0,   .a = 255}
#define GREEN  (Color) {.r = 0,   .g = 146, .b = 62,  .a = 255}
#define BLUE   (Color) {.r = 1,   .g = 33,  .b = 105, .a = 255}
#define YELLOW (Color) {.r = 248, .g = 193, .b = 0,   .a = 255}

Square square_new(float x, float y, float z, float size, Color color) {
    return (Square) {
        .pos.x = x,
        .pos.y = y,
        .pos.z = z,
        .size = size,
        .color = color
    };
}

Rectangle rectangle_new(float x, float y, float z, float size_x, float size_y, Color color) {
    return (Rectangle) {
        .pos.x = x,
        .pos.y = y,
        .pos.z = z,
        .size_x = size_x,
        .size_y = size_y,
        .color = color
    };
}

Poly4 poly4_new(Vec3 v1, Vec3 v2, Vec3 v3, Vec3 v4, Color color) {
    return (Poly4) {
        .v1 = v1,
        .v2 = v2,
        .v3 = v3,
        .v4 = v4,
        .color = color
    };
}

void draw_square_raw(Vec3 pos, float size, Color color) {

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

void draw_rectangle_raw(Vec3 pos, float size_x, float size_y, Color color) {

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

void draw_circle_raw(Vec3 pos, float radius, Color color) {

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

void draw_elipsis_raw(Vec3 pos, float radius_x, float radius_y, Color color) {

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

void draw_square(Square s) {

    float relative_size = s.size;

    glColor4ub(s.color.r, s.color.g, s.color.b, s.color.a);

    glBegin(GL_QUADS);
        glVertex3f(s.pos.x - relative_size, s.pos.y - relative_size, s.pos.z);
        glVertex3f(s.pos.x - relative_size, s.pos.y + relative_size, s.pos.z);
        glVertex3f(s.pos.x + relative_size, s.pos.y + relative_size, s.pos.z);
        glVertex3f(s.pos.x + relative_size, s.pos.y - relative_size, s.pos.z);
    glEnd();

    return;
}

void draw_rectangle(Rectangle r) {

    float relative_size_x = r.size_x;
    float relative_size_y = r.size_y;

    glColor4ub(r.color.r, r.color.g, r.color.b, r.color.a);

    glBegin(GL_QUADS);
        glVertex3f(r.pos.x - relative_size_x, r.pos.y - relative_size_y, r.pos.z);
        glVertex3f(r.pos.x - relative_size_x, r.pos.y + relative_size_y, r.pos.z);
        glVertex3f(r.pos.x + relative_size_x, r.pos.y + relative_size_y, r.pos.z);
        glVertex3f(r.pos.x + relative_size_x, r.pos.y - relative_size_y, r.pos.z);
    glEnd();

    return;
}

void draw_circle(Circle c) {

    glColor4ub(c.color.r, c.color.g, c.color.b, c.color.a);

    glBegin(GL_TRIANGLE_FAN);

        for (int i = 0; i < ELIPSIS_SEGMENTS; i++) {
            float angle = 2.0f * PI * (float)i / (float) ELIPSIS_SEGMENTS;

            float x = c.radius * cosf(angle);
            float y = c.radius * sinf(angle);

            glVertex3f(x + c.pos.x, y + c.pos.y, c.pos.z);
        }

    glEnd();

    return;
}

void draw_elipsis(Elipsis e) {

    glColor4ub(e.color.r, e.color.g, e.color.b, e.color.a);

    glBegin(GL_TRIANGLE_FAN);

        for (int i = 0; i < ELIPSIS_SEGMENTS; i++) {
            float angle = 2.0f * PI * (float)i / (float) ELIPSIS_SEGMENTS;

            float x = e.radius_x * cosf(angle);
            float y = e.radius_y * sinf(angle);

            glVertex3f(x + e.pos.x, y + e.pos.y, e.pos.z);
        }

    glEnd();

    return;
}

void draw_poly4(Poly4 p) {

    glColor4ub(p.color.r, p.color.g, p.color.b, p.color.a);

    glBegin(GL_QUADS);
        glVertex3f(p.v1.x, p.v1.y, p.v1.z);
        glVertex3f(p.v2.x, p.v2.y, p.v2.z);
        glVertex3f(p.v3.x, p.v3.y, p.v3.z);
        glVertex3f(p.v4.x, p.v4.y, p.v4.z);
    glEnd();

    return;
}