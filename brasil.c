#include <stdio.h>
// #include <GL/glew.h>
// #include <GL/gl.h>
// #include <GL/glu.h>
#include <GL/glut.h>
#include <math.h>

#define PI 3.14159265358979323846
#define ELIPSIS_SEGMENTS 360

#define RECTANGLE 0
#define DIAMOND 1
#define CIRCLE 2

typedef struct _vec3 {
    float x;
    float y;
    float z;
} Vec3;

Vec3 green = (Vec3) {.x = 0.0f, .y = 146.0f/255.0f, .z = 62.0f/255.0f};
Vec3 yellow = (Vec3) {.x = 248.0f/255.0f, .y = 193.0f/255.0f, .z = 0.0f};
Vec3 blue = (Vec3) {.x = 1.0f/255.0f, .y = 33.0f/255.0f, .z = 105.0f/255.0f};
Vec3 red = (Vec3) {.x = 219.0f/255.0f, .y = 0.0f, .z = 0.0f};

GLfloat rectangle_color[3];
GLfloat diamond_color[3];
GLfloat circle_color[3];

int selected = RECTANGLE;

void elipsis(float cx, float cy, float radius_x, float radius_y) {

    glColor3fv(circle_color);

    glBegin(GL_TRIANGLE_FAN);
        for (int i = 0; i < ELIPSIS_SEGMENTS; i++) {
            float angle = 2.0f * PI * (float)i / (float) ELIPSIS_SEGMENTS;

            float x = radius_x * cosf(angle);
            float y = radius_y * sinf(angle);

            glVertex3f(x + cx, y + cy, 1.0f);
        }
        
    glEnd();

    return;
}

void diamond(float cx, float cy, float margin_x, float margin_y, float padding) {

    glColor3fv(diamond_color);

    glBegin(GL_QUADS);
        glVertex3f(cx                     , cy - margin_y + padding, 0.5f);
        glVertex3f(cx - margin_x + padding, cy                     , 0.5f);
        glVertex3f(cx                     , cy + margin_y - padding, 0.5f);
        glVertex3f(cx + margin_x - padding, cy                     , 0.5f);
    glEnd();

    return;
}

void rectangle(float cx, float cy, float size_x, float size_y) {

    glColor3fv(rectangle_color);

    glBegin(GL_QUADS);
        glVertex3f(cx - size_x, cy - size_y, 0.0f);
        glVertex3f(cx - size_x, cy + size_y, 0.0f);
        glVertex3f(cx + size_x, cy + size_y, 0.0f);
        glVertex3f(cx + size_x, cy - size_y, 0.0f);
    glEnd();

    return;
}

void draw() {

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    rectangle(0.0f, 0.0f, 0.9f, 0.63f);

    diamond(0.0f, 0.0f, 0.9f, 0.63f, 0.0765f);

    elipsis(0.0f, 0.0f, 0.315f, 0.315f);

    glFlush();

    return;
}

void resize_window(GLsizei w, GLsizei h) {

    if (!h) h = 1;

    glViewport(0, 0, w, h);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    if (w <= h)
        gluOrtho2D(-1.0f, 1.0f, -1.0f * h/w, 1.0f * h/w);
    else
        gluOrtho2D(-1.0f * w/h, 1.0f * w/h, -1.0, 1.0f);

    return;
}

void keyboard(unsigned char key, int x, int y) {

    switch (key) {

        case '1':
            selected = RECTANGLE;
            break;
        case '2':
            selected = DIAMOND;
            break;
        case '3':
            selected = CIRCLE;
            break;

        case 'R':
        case 'r':
            if (selected == RECTANGLE) {rectangle_color[0] = red.x; rectangle_color[1] = red.y; rectangle_color[2] = red.z;}
            else if (selected == DIAMOND) {diamond_color[0] = red.x; diamond_color[1] = red.y; diamond_color[2] = red.z;}
            else if (selected == CIRCLE) {circle_color[0] = red.x; circle_color[1] = red.y; circle_color[2] = red.z;}
            break;

        case 'G':
        case 'g':
            if (selected == RECTANGLE) rectangle_color[0] = green.x, rectangle_color[1] = green.y, rectangle_color[2] = green.z;
            else if (selected == DIAMOND) diamond_color[0] = green.x, diamond_color[1] = green.y, diamond_color[2] = green.z;
            else if (selected == CIRCLE) circle_color[0] = green.x, circle_color[1] = green.y, circle_color[2] = green.z;
            break;

        case 'B':
        case 'b':
            if (selected == RECTANGLE) rectangle_color[0] = blue.x, rectangle_color[1] = blue.y, rectangle_color[2] = blue.z;
            else if (selected == DIAMOND) diamond_color[0] = blue.x, diamond_color[1] = blue.y, diamond_color[2] = blue.z;
            else if (selected == CIRCLE) circle_color[0] = blue.x, circle_color[1] = blue.y, circle_color[2] = blue.z;
            break;

        case 'Y':
        case 'y':
            if (selected == RECTANGLE) rectangle_color[0] = yellow.x, rectangle_color[1] = yellow.y, rectangle_color[2] = yellow.z;
            else if (selected == DIAMOND) diamond_color[0] = yellow.x, diamond_color[1] = yellow.y, diamond_color[2] = yellow.z;
            else if (selected == CIRCLE) circle_color[0] = yellow.x, circle_color[1] = yellow.y, circle_color[2] = yellow.z;
            break;

    }

    glutPostRedisplay();

    return;
}

void init() {

    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
    glEnable(GL_DEPTH_TEST);

    rectangle_color[0] = green.x;
    diamond_color[0] = yellow.x;
    circle_color[0] = blue.x;

    rectangle_color[1] = green.y;
    diamond_color[1] = yellow.y;
    circle_color[1] = blue.y;

    rectangle_color[2] = green.z;
    diamond_color[2] = yellow.z;
    circle_color[2] = blue.z;

    return;
}

int main(int argc, char* argv[]) {

    glutInit(&argc, argv);

    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);

    glutInitWindowSize(1600, 900);
    glutCreateWindow("Brasil");

    glutDisplayFunc(draw);

    glutReshapeFunc(resize_window);

    glutKeyboardFunc(keyboard);

    init();

    glutMainLoop();

    return 0;
}
