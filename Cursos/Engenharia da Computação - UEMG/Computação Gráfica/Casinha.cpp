 void Desenha(void) // Fun��o de redesenho da janela de visualiza��o
 {
 // Limpa a janela de visualiza��o com a cor branca
 	glClearColor(1,1,1,0); 
	glClear(GL_COLOR_BUFFER_BIT);
 // Define a cor de desenho: vermelho
 	glColor3f(1,0,0); 
// Desenha um tri�ngulo no centro da janela
 	glBegin(GL_TRIANGLES);
 		glVertex2f(-0.5,-0.5);
 		glVertex2f( 0.0, 0.5);
 		glVertex2f( 0.5,-0.5);
 	glEnd();
 	glFlush(); //Executa os comandos OpenGL
}

