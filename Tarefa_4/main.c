#include "core.h"

#define FACE_SIZE 0.6f

Color colors[6] = {RED, GREEN, BLUE, YELLOW, CYAN, MAGENTA};
Square faces_1[6];
Square faces_2[6];

float angle = 45.0;
float f_aspect;

Vec3 pos_1 = {-0.5f, 0.0f, -0.5f};
Vec3 pos_2 = {0.5f, 0.0f, 0.5f};

Vec3 cam_pos = {0.0f, 0.0f, 3.0f};

GLUquadric *quadratic;

void configure_projection() {
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(angle, f_aspect, 0.5, 500);
}

void configure_visualization() {

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(
        cam_pos.x, cam_pos.y, cam_pos.z, // Pos
        0.0f, 0.0f, 0.0f, // Alvo
        0.0f, 1.0f, 0.0f // Up
    );

    return;
}

void resize_window(GLsizei w, GLsizei h) {

    if (!h) h = 1;

    glViewport(0, 0, w, h);

    f_aspect = (float) w/ (float) h;

    configure_projection();

    return;
}

void keyboard(unsigned char key, int x, int y) {

    switch (key) {

        // Esc
        case 27:
            exit(0);
            break;

        case 'A':
        case 'a':
            cam_pos.x -= 0.1;
            break;

        case 'D':
        case 'd':
            cam_pos.x += 0.1;
            break;

        case 'W':
        case 'w':
            cam_pos.z -= 0.1;
            break;

        case 'S':
        case 's':
            cam_pos.z += 0.1;
            break;

        case ' ':
            cam_pos.y += 0.1;
            break;
    }

    glutPostRedisplay();

    return;
}

void draw() {

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    primitive_draw_cube(pos_1, faces_1, colors);
    primitive_draw_cube(pos_2, faces_2, colors);
    //gluSphere(quadratic, 0.5, 100, 100);

    configure_visualization();
    glFlush();

    return;
}

void init() {

    for (size_t i = 0; i < 6; i++) {
        faces_1[i] = square_new(0.0f, 0.0f, 0.0f, FACE_SIZE);
        faces_2[i] = square_new(0.0f, 0.0f, 0.0f, FACE_SIZE);
    }

    quadratic = gluNewQuadric();

    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
    glEnable(GL_BLEND);
    glEnable(GL_DEPTH_TEST);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    return;
}

int main(int argc, char* argv[]) {

    glutInit(&argc, argv);

    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);

    glutInitWindowSize(800, 800);
    glutCreateWindow("Brasil");

    glutDisplayFunc(draw);

    glutReshapeFunc(resize_window);

    glutKeyboardFunc(keyboard);

    init();

    glutMainLoop();

    return 0;
}