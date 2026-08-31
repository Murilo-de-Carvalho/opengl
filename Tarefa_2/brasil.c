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

#define MAX_WIDTH 1600
#define MAX_HEIGHT 900

#define HALF_WIDTH 800
#define HALF_HEIGHT 450

#define CENTER_X 0
#define CENTER_Y 0

#define RECTANGLE_Z 0.0f
#define DIAMOND_Z 0.5f
#define CIRCLE_Z 1.0f

typedef struct _color_rgb {
    GLubyte r;
    GLubyte g;
    GLubyte b;
} Color_RGB;

typedef struct _vec2d {
    float x;
    float y;
} Vec2D;

Color_RGB green = (Color_RGB) {.r = 0, .g = 146, .b = 62};
Color_RGB yellow = (Color_RGB) {.r = 248, .g = 193.0, .b = 0};
Color_RGB blue = (Color_RGB) {.r = 1, .g = 33, .b = 105};
Color_RGB red = (Color_RGB) {.r = 219, .g = 0, .b = 0};

Color_RGB rectangle_color;
Color_RGB diamond_color;
Color_RGB circle_color;

Vec2D pos_rectangle;
Vec2D pos_diamond;
Vec2D pos_circle;

int selected = RECTANGLE;

void rectangle(float cx, float cy, float size_x, float size_y) {

    glColor3ub(rectangle_color.r, rectangle_color.g, rectangle_color.b);

    glBegin(GL_QUADS);
        glVertex3f(cx - size_x, cy - size_y, RECTANGLE_Z);
        glVertex3f(cx - size_x, cy + size_y, RECTANGLE_Z);
        glVertex3f(cx + size_x, cy + size_y, RECTANGLE_Z);
        glVertex3f(cx + size_x, cy - size_y, RECTANGLE_Z);
    glEnd();

    return;
}

void diamond(float cx, float cy, float margin_x, float margin_y, float padding) {

    glColor3ub(diamond_color.r, diamond_color.g, diamond_color.b);

    glBegin(GL_QUADS);
        glVertex3f(cx                     , cy - margin_y + padding, DIAMOND_Z);
        glVertex3f(cx - margin_x + padding, cy                     , DIAMOND_Z);
        glVertex3f(cx                     , cy + margin_y - padding, DIAMOND_Z);
        glVertex3f(cx + margin_x - padding, cy                     , DIAMOND_Z);
    glEnd();

    return;
}

void elipsis(float cx, float cy, float radius_x, float radius_y) {

    glColor3ub(circle_color.r, circle_color.g, circle_color.b);

    glBegin(GL_TRIANGLE_FAN);
        for (int i = 0; i < ELIPSIS_SEGMENTS; i++) {
            float angle = 2.0f * PI * (float)i / (float) ELIPSIS_SEGMENTS;

            float x = radius_x * cosf(angle);
            float y = radius_y * sinf(angle);

            glVertex3f(x + cx, y + cy, CIRCLE_Z);
        }
        
    glEnd();

    return;
}

void draw() {

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    elipsis(pos_circle.x, pos_circle.y, 0.315f, 0.315f);
    
    diamond(pos_diamond.x, pos_diamond.y, 0.9f, 0.63f, 0.0765f);
    
    rectangle(pos_rectangle.x, pos_rectangle.y, 0.9f, 0.63f);

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

        // Esc
        case 27:
            exit(0);

        case '1':
            selected = RECTANGLE;
            break;
        case '2':
            selected = DIAMOND;
            break;
        case '3':
            selected = CIRCLE;
            break;

        // Reset
        case 'E':
        case 'e':
            rectangle_color = green;
            diamond_color = yellow;
            circle_color = blue;
            pos_rectangle = (Vec2D) {.x = CENTER_X, .y = CENTER_Y};
            pos_diamond = (Vec2D) {.x = CENTER_X, .y = CENTER_Y};
            pos_circle = (Vec2D) {.x = CENTER_X, .y = CENTER_Y};
            break;

        case 'R':
        case 'r':
            if (selected == RECTANGLE) rectangle_color = red;
            else if (selected == DIAMOND) diamond_color = red;
            else if (selected == CIRCLE) circle_color = red;
            break;

        case 'G':
        case 'g':
            if (selected == RECTANGLE) rectangle_color = green;
            else if (selected == DIAMOND) diamond_color = green;
            else if (selected == CIRCLE) circle_color = green;
            break;

        case 'B':
        case 'b':
            if (selected == RECTANGLE) rectangle_color = blue;
            else if (selected == DIAMOND) diamond_color = blue;
            else if (selected == CIRCLE) circle_color = blue;
            break;

        case 'Y':
        case 'y':
            if (selected == RECTANGLE) rectangle_color = yellow;
            else if (selected == DIAMOND) diamond_color = yellow;
            else if (selected == CIRCLE) circle_color = yellow;
            break;
    }

    glutPostRedisplay();

    return;
}

float mouse_x_to_ortho(int x) {
    float fx = (float) x;
    return (0.00125 * fx) - 1;
}

float mouse_y_to_ortho(int y) {
    float fy = (float) y;
    // Axis is inverted, so we multiply by -1
    return -1 * ((0.00222222222f * fy) - 1);
}

void mouse(int button, int state, int x, int y) {

    if (button == GLUT_LEFT_BUTTON && state == GLUT_UP) {
        switch (selected) {
            case RECTANGLE:
                pos_rectangle.x = mouse_x_to_ortho(x);
                pos_rectangle.y = mouse_y_to_ortho(y);
                break;
            
            case DIAMOND:
                pos_diamond.x = mouse_x_to_ortho(x);
                pos_diamond.y = mouse_y_to_ortho(y);
                break;

            case CIRCLE:
                pos_circle.x = mouse_x_to_ortho(x);
                pos_circle.y = mouse_y_to_ortho(y);
                break;
        }

    }

    glutPostRedisplay();

    return;
}

void init() {

    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
    glEnable(GL_DEPTH_TEST);

    rectangle_color = green;
    diamond_color = yellow;
    circle_color = blue;

    pos_rectangle = (Vec2D) {.x = CENTER_X, .y = CENTER_Y};
    pos_diamond = (Vec2D) {.x = CENTER_X, .y = CENTER_Y};
    pos_circle = (Vec2D) {.x = CENTER_X, .y = CENTER_Y};

    return;
}

int main(int argc, char* argv[]) {

    glutInit(&argc, argv);

    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);

    glutInitWindowSize(MAX_WIDTH, MAX_HEIGHT);
    glutCreateWindow("Brasil");

    glutDisplayFunc(draw);

    glutReshapeFunc(resize_window);

    glutKeyboardFunc(keyboard);

    glutMouseFunc(mouse);

    init();

    glutMainLoop();

    return 0;
}