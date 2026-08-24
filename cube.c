#include "core.h"

Square face;
Vec3 origin = {.x = 0.0f, .y = 0.0f, .z = 0.0f};

void draw() {

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    draw_square(face);

    glPushMatrix();
    glRotatef(90.0f, 1.0f, 0.0f, 0.0f);
    draw_square(face);
    glPopMatrix();

    glPushMatrix();
    glRotatef(89.0f, 0.0f, 1.0f, 0.0f);
    draw_square(face);
    glPopMatrix();

    glPushMatrix();
    glRotatef(90.0f, 0.0f, 0.0f, 1.0f);
    draw_square(face);
    glPopMatrix();

    glPushMatrix();
    glRotatef(90.0f, 0.0f, 1.0f, 0.0f);
    draw_square(face);
    glPopMatrix();

    glPushMatrix();
    glRotatef(90.0f, 0.0f, 1.0f, 0.0f);
    draw_square(face);
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

    return;
}

void init() {

    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
    glEnable(GL_DEPTH_TEST);

    face = square_new(origin.x, origin.y, origin.z, 0.3, RED);

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