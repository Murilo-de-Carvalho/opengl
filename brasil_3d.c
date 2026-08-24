#include "core.h"

Rectangle rectangle;
Poly4 diamond;
Circle circle;

#define Z_RECTANGLE -0.5f
#define Z_DIAMOND    0.0f
#define Z_CIRCLE     0.5f

Vec3 origin = {.x = 0.0f, .y = 0.0f, .z = 0.0f};
Vec3 circle_pos = {.x = 0.0f, .y = 0.0f, Z_CIRCLE};

//int selected = RECTANGLE;

void draw() {

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glPushMatrix();
    glRotatef(89.0f, 0.0f, 1.0f, 0.0f);
    draw_rectangle(rectangle);
    draw_poly4(diamond);
    draw_circle_raw(circle_pos, 0.315f, BLUE);
    glPopMatrix();

    glFlush();

    return;
}

void resize_window(GLsizei w, GLsizei h) {

    if (!h) h = 1;

    glViewport(0, 0, w, h);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    glOrtho(
        -1.0f, 1.0f,
        -1.0f, 1.0f,
        -5.0f, 5.0f
    );

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    /* if (w <= h)
        gluOrtho2D(-1.0f, 1.0f, -1.0f * h/w, 1.0f * h/w);
    else
        gluOrtho2D(-1.0f * w/h, 1.0f * w/h, -1.0, 1.0f); */

    return;
}

void init() {

    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
    glEnable(GL_DEPTH_TEST);

    Vec3 v1 = {origin.x                 , origin.y - 0.63f + 0.0765f, Z_DIAMOND};
    Vec3 v2 = {origin.x - 0.9f + 0.0765f, origin.y                  , Z_DIAMOND};
    Vec3 v3 = {origin.x                 , origin.y + 0.63f - 0.0765f, Z_DIAMOND};
    Vec3 v4 = {origin.x + 0.9f - 0.0765f, origin.y                  , Z_DIAMOND};

    rectangle = rectangle_new(origin.x, origin.y, Z_RECTANGLE, 0.9f, 0.63f, GREEN);
    diamond = poly4_new(v1, v2, v3, v4, YELLOW);

    return;
}

int main(int argc, char* argv[]) {

    glutInit(&argc, argv);

    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);

    glutInitWindowSize(800, 800);
    glutCreateWindow("Brasil");

    glutDisplayFunc(draw);

    glutReshapeFunc(resize_window);

    init();

    glutMainLoop();

    return 0;
}