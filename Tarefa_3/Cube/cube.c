#include "core.h"

#define FACE_SIZE 0.5f
#define X_AXIS 0
#define Y_AXIS 1
#define Z_AXIS 2

Square face;
Vec3 origin = {.x = 0.0f, .y = 0.0f, .z = 0.0f};

Vec3 rot_x = {.x = 1.0f, .y = 0.0f, .z = 0.0f};
Vec3 rot_y = {.x = 0.0f, .y = 1.0f, .z = 0.0f};
Vec3 rot_z = {.x = 0.0f, .y = 0.0f, .z = 1.0f};

Vec3 trans_x = {.x = FACE_SIZE/2.0f, .y = 0.0f, .z = 0.0f};
Vec3 trans_y = {.x = 0.0f, .y = FACE_SIZE/2.0f, .z = 0.0f};
Vec3 trans_z = {.x = 0.0f, .y = 0.0f, .z = FACE_SIZE/2.0f};

int selected = X_AXIS;

Vec3 input_axis;

Color my_cyan    = CYAN;
Color my_magenta = MAGENTA;
Color my_yellow  = YELLOW;

Color my_purple  = PURPLE;
Color my_orange  = ORANGE;
Color my_grey    = GREY;

Color my_red     = RED;
Color my_green   = GREEN;
Color my_blue    = BLUE;

void draw() {

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glPushMatrix();

        glBegin(GL_LINES);
            glColor4ub(my_blue.r, my_blue.g, my_blue.b, my_blue.a);
            glVertex3f(face.pos.x, face.pos.y, face.pos.z);
            glVertex3f(0.0f, 0.0f, 1.0f);
        glEnd();

        glTranslatef(trans_z.x, trans_z.y, trans_z.z);
        draw_square(face, my_cyan);

    glPopMatrix();

    // rot: x = 0, y = 0, z = -1
    glPushMatrix();
        glTranslatef(trans_z.x, trans_z.y, -trans_z.z);
        glRotatef(90.0f, rot_z.x, rot_z.y, rot_z.z);
        draw_square(face, my_magenta);
    glPopMatrix();

    // rot: x = 1, y = 0, z = 0
    glPushMatrix();

        glBegin(GL_LINES);
            glColor4ub(my_red.r, my_red.g, my_red.b, my_red.a);
            glVertex3f(face.pos.x, face.pos.y, face.pos.z);
            glVertex3f(1.0f, 0.0f, 0.0f);
        glEnd();

        glTranslatef(trans_y.x, trans_y.y, trans_y.z);
        glRotatef(90.0f, rot_x.x, rot_x.y, rot_x.z);
        draw_square(face, my_yellow);

    glPopMatrix();

    // rot: x = -1, y = 0, z = 0
    glPushMatrix();
        glTranslatef(trans_y.x, -trans_y.y, trans_y.z);
        glRotatef(90.0f, -rot_x.x, rot_x.y, rot_x.z);
        draw_square(face, my_grey);
    glPopMatrix();

    // rot: x = 0, y = 1, z = 0
    glPushMatrix();

        glBegin(GL_LINES);
            glColor4ub(my_green.r, my_green.g, my_green.b, my_green.a);
            glVertex3f(face.pos.x, face.pos.y, face.pos.z);
            glVertex3f(0.0f, 1.0f, 0.0f);
        glEnd();

        glTranslatef(trans_x.x, trans_x.y, trans_x.z);
        glRotatef(90.0f, rot_y.x, rot_y.y, rot_y.z);
        draw_square(face, my_purple);

    glPopMatrix();

    // rot: x = 0, y = -1, z = 0
    glPushMatrix();
        glTranslatef(-trans_x.x, trans_x.y, trans_x.z);
        glRotatef(90.0f, rot_y.x, -rot_y.y, rot_y.z);
        draw_square(face, my_orange);
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

    glRotatef(45, 1.0f, 0.0f, 0.0f);
    glRotatef(45, 0.0f, 1.0f, 0.0f);
    //glRotatef(45, 1.0f, 0.0f, 1.0f);
    //glRotatef(90, 0.0f, 0.0f, 1.0f);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    return;
}

void keyboard(unsigned char key, int x, int y) {

    switch (key) {

        // Esc
        case 27:
            exit(0);
            break;

        case '1':
            selected = X_AXIS;
            input_axis = rot_x;
            break;

        case '2':
            selected = Y_AXIS;
            input_axis = rot_y;
            break;

        case '3':
            selected = Z_AXIS;
            input_axis = rot_z;
            break;

        case 'A':
        case 'a':
            glRotatef(15, input_axis.x, input_axis.y, input_axis.z);
            break;

        case 'D':
        case 'd':
            glRotatef(15, -input_axis.x, -input_axis.y, -input_axis.z);
            break;

        case 'W':
        case 'w':
            my_cyan.a    = MIN(255, my_cyan.a    + 16);
            my_magenta.a = MIN(255, my_magenta.a + 16);
            my_grey.a    = MIN(255, my_grey.a    + 16);
            my_yellow.a  = MIN(255, my_yellow.a  + 16);
            my_purple.a  = MIN(255, my_purple.a  + 16);
            my_orange.a  = MIN(255, my_orange.a  + 16);
            break;

        case 'S':
        case 's':
            my_cyan.a    = MAX(64, my_cyan.a    - 16);
            my_magenta.a = MAX(64, my_magenta.a - 16);
            my_grey.a    = MAX(64, my_grey.a    - 16);
            my_yellow.a  = MAX(64, my_yellow.a  - 16);
            my_purple.a  = MAX(64, my_purple.a  - 16);
            my_orange.a  = MAX(64, my_orange.a  - 16);
            break;
    }

    glutPostRedisplay();

    return;
}

void init() {

    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
    glEnable(GL_BLEND);
    glEnable(GL_DEPTH_TEST);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    face = square_new(origin.x, origin.y, origin.z, FACE_SIZE);
    input_axis = rot_x;

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