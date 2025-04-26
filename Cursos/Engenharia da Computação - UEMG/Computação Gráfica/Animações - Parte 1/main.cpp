#include <GL/glut.h>
#include <stdio.h>

int cx, cy, d, largura, altura, clickquadrado;

void GerenciaMouse(int button, int state, int x, int y) {
    switch(button) {
        case GLUT_LEFT_BUTTON:
            if (state == GLUT_DOWN) {
                if (x >= cx && x <= cx + d && y >= altura - cy - d && y <= altura - cy) {
                    clickquadrado = 1;
                    printf("\nPressionado na posicao: %d , %d", x, y);
                }
            }
            if (state == GLUT_UP) {
                clickquadrado = 0;
                printf("\nSolto na posicao: %d , %d", x, y);
            }
            break;
        case GLUT_RIGHT_BUTTON:
            printf("\nBotao direito.");
            break;
        default:
            break;
    }
    glutPostRedisplay();
}

void MousePassivo(int x, int y) {
    printf("Mouse ANDANDO solto na janela. Posicao: (%d, %d)\n", x, y);
}

void MouseMovendo(int x, int y) {
    if (clickquadrado) {
        cx = x - d / 2;
        cy = altura - y - d / 2;
        printf("Mouse ANDANDO pressionado na janela. Posicao: (%d, %d)\n", x, y);
    }
    glutPostRedisplay();
}

void Inicializa() {
    cx = 200;
    cy = 200;
    d = 50;
    largura = 400;
    altura = 400;
    clickquadrado = 0;
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
}

void Desenha() {
    glClear(GL_COLOR_BUFFER_BIT);
    glBegin(GL_QUADS);
        glColor3f(1.0f, 0.0f, 0.0f);
        glVertex2i(cx, cy + d);
        glColor3f(0.0f, 1.0f, 0.0f);
        glVertex2i(cx + d, cy + d);
        glColor3f(0.0f, 0.0f, 1.0f);
        glVertex2i(cx + d, cy);
        glColor3f(1.0f, 1.0f, 0.0f);
        glVertex2i(cx, cy);
    glEnd();
    glFlush();
}

void AlteraJanela(GLsizei w, GLsizei h) {
    largura = w;
    altura = h;
    if (h == 0) h = 1;

    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    if (w <= h) gluOrtho2D(0, largura, 0, altura * h / w);
    else gluOrtho2D(0, largura * w / h, 0, altura);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(400, 400);
    glutInitWindowPosition(400, 100);
    glutCreateWindow("Trabalhando com o mouse");

    Inicializa();
    glutDisplayFunc(Desenha);
    glutReshapeFunc(AlteraJanela);
    glutPassiveMotionFunc(MousePassivo);
    glutMotionFunc(MouseMovendo);
    glutMouseFunc(GerenciaMouse);

    glutMainLoop();
    return 0;
}
