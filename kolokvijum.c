#include <math.h>		
#include <stdio.h>
#include <stdlib.h>		
#include "Glut.h"

const double Xmin = 0.0, Xmax = 5.0;
const double Ymin = 0.0, Ymax = 5.0;

typedef struct {
    double x;
    double y;
} Player;

Player playerPlus = { 2.5, 2.5 }; // Pozicija igrača Plus
Player playerCircle = { 0.5, 0.5 }; // Pozicija igrača Kružić

void drawMaze() {
    glColor3f(1.0f, 1.0f, 1.0f); // Bela boja
    glLineWidth(3.0); // Debljina linije

    // Spoljni zidovi
    glBegin(GL_LINES);
    glVertex2d(0.0, 0.0);
    glVertex2d(5.0, 0.0);
    glEnd();

    glBegin(GL_LINES);
    glVertex2d(5.0, 0.0);
    glVertex2d(5.0, 5.0);
    glEnd();

    glBegin(GL_LINES);
    glVertex2d(5.0, 5.0);
    glVertex2d(0.0, 5.0);
    glEnd();

    glBegin(GL_LINES);
    glVertex2d(0.0, 5.0);
    glVertex2d(0.0, 0.0);
    glEnd();

    // Unutrasnji zidovi
    glBegin(GL_LINES);
    glVertex2d(1.0, 1.0);
    glVertex2d(4.0, 1.0);
    glEnd();

    glBegin(GL_LINES);
    glVertex2d(4.0, 1.0);
    glVertex2d(4.0, 4.0);
    glEnd();

    glBegin(GL_LINES);
    glVertex2d(4.0, 4.0);
    glVertex2d(1.0, 4.0);
    glEnd();

    glBegin(GL_LINES);
    glVertex2d(1.0, 4.0);
    glVertex2d(1.0, 1.0);
    glEnd();

    glBegin(GL_LINES);
    glVertex2d(2.0, 2.0);
    glVertex2d(3.0, 2.0);
    glEnd();

    glBegin(GL_LINES);
    glVertex2d(3.0, 2.0);
    glVertex2d(3.0, 3.0);
    glEnd();

    glBegin(GL_LINES);
    glVertex2d(3.0, 3.0);
    glVertex2d(2.0, 3.0);
    glEnd();

    glBegin(GL_LINES);
    glVertex2d(2.0, 3.0);
    glVertex2d(2.0, 2.0);
    glEnd();
}

void drawPlayer(Player player, float r, float g, float b) {
    glColor3f(r, g, b); // Boja igrača
    glRectd(player.x - 0.1, player.y - 0.1, player.x + 0.1, player.y + 0.1); // Kvadrat za igrača Plus
    // Alternativno, možete koristiti GL_TRIANGLE_FAN da nacrtate krug za igrača Kružić
}

void drawScene(void)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    drawMaze();

    // Crtamo igrače
    drawPlayer(playerPlus, 1.0f, 0.0f, 0.0f); // Crvena boja za igrača Plus
    drawPlayer(playerCircle, 0.0f, 0.0f, 1.0f); // Plava boja za igrača Kružić

    glutSwapBuffers();
}

void specialKeys(int key, int x, int y) {
    switch (key) {
    case GLUT_KEY_UP:
        playerPlus.y += 0.1; // Pomeraj igrača Plus na gore
        break;
    case GLUT_KEY_DOWN:
        playerPlus.y -= 0.1; // Pomeraj igrača Plus na dole
        break;
    case GLUT_KEY_LEFT:
        playerPlus.x -= 0.1; // Pomeraj igrača Plus levo
        break;
    case GLUT_KEY_RIGHT:
        playerPlus.x += 0.1; // Pomeraj igrača Plus desno
        break;
    }
    glutPostRedisplay(); // Ponovno iscrtavanje prozora
}

void keyboard(unsigned char key, int x, int y) {
    switch (key) {
    case 'w':
        playerCircle.y += 0.1; // Pomeraj igrača Kružić na gore
        break;
    case 's':
        playerCircle.y -= 0.1; // Pomeraj igrača Kružić na dole
        break;
    case 'a':
        playerCircle.x -= 0.1; // Pomeraj igrača Kružić levo
        break;
    case 'd':
        playerCircle.x += 0.1; // Pomeraj igrača Kružić desno
        break;
    }
    glutPostRedisplay(); // Ponovno iscrtavanje prozora
}

void initRendering()
{
    glClearColor(0.0, 0.0, 0.0, 1.0);
}

void resizeWindow(int w, int h)
{
    double scale, center;
    double windowXmin, windowXmax, windowYmin, windowYmax;

    glViewport(0, 0, w, h);

    w = (w == 0) ? 1 : w;
    h = (h == 0) ? 1 : h;
    if ((Xmax - Xmin) / w < (Ymax - Ymin) / h) {
        scale = ((Ymax - Ymin) / h) / ((Xmax - Xmin) / w);
        center = (Xmax + Xmin) / 2;
        windowXmin = center - (center - Xmin) * scale;
        windowXmax = center + (Xmax - center) * scale;
        windowYmin = Ymin;
        windowYmax = Ymax;
    }
    else {
        scale = ((Xmax - Xmin) / w) / ((Ymax - Ymin) / h);
        center = (Ymax + Ymin) / 2;
        windowYmin = center - (center - Ymin) * scale;
        windowYmax = center + (Ymax - center) * scale;
        windowXmin = Xmin;
        windowXmax = Xmax;
    }

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(windowXmin, windowXmax, windowYmin, windowYmax, -1, 1);

}

int main(int argc, char** argv)
{
    glutInit(&argc, argv);

    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);

    glutInitWindowPosition(10, 60);
    glutInitWindowSize(360, 360);

    glutCreateWindow("Kolokvijum_ime_prezime");

    initRendering();

    glutReshapeFunc(resizeWindow);

    glutDisplayFunc(drawScene);

    glutMainLoop();

    return(0);
}
