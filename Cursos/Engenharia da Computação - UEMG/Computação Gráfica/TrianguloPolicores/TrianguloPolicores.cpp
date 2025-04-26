#include <gl/glut.h>
#include <stdio.h>

float cx = 0, cy = 0;
float d = 50;
float r = 0; //Rotação
float s = 1.0; //Tamanho

void DesenhaTriangulo() {
    glBegin(GL_TRIANGLES);
    	glColor3f(1, 0, 0);
    	glVertex3f(cx - d, cy - d, 0);
    	glColor3f(0, 1, 0);
    	glVertex3f(cx, cy + d, 0);
    	glColor3f(0, 0, 1);
    	glVertex3f(cx + d, cy - d, 0);
    glEnd();
}

void Desenha() {
    glClear(GL_COLOR_BUFFER_BIT);

    glLoadIdentity();
    glTranslatef(cx, cy, 0);
    glRotatef(r, 0, 0, 1);
    glScalef(s, s, 1.0);

    DesenhaTriangulo();

    glutSwapBuffers();
}

void AlteraTamanhoJanela(GLsizei w, GLsizei h) {
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-w / 2, w / 2, -h / 2, h / 2, -1, 1);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void InputTeclado(unsigned char key, int x, int y) {
    switch (key) {
        case 'r':
            r += 180;
            break;
        case 's':
            s *= 1.5;
            break;
        case 't':
            cx = rand() % 800 - 400;
            cy = rand() % 600 - 300;
            break;
    }
    glutPostRedisplay();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(800, 600);
    glutCreateWindow("Triângulo Policores");

    glutDisplayFunc(Desenha);
    glutReshapeFunc(AlteraTamanhoJanela);
    glutKeyboardFunc(InputTeclado);

    glClearColor(0, 0, 0, 1);

    glutMainLoop();
    return 0;
}

