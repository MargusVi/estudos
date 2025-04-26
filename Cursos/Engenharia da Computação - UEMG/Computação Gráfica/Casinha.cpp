 void Desenha(void) // Função de redesenho da janela de visualização
 {
 // Limpa a janela de visualização com a cor branca
 	glClearColor(1,1,1,0); 
	glClear(GL_COLOR_BUFFER_BIT);
 // Define a cor de desenho: vermelho
 	glColor3f(1,0,0); 
// Desenha um triângulo no centro da janela
 	glBegin(GL_TRIANGLES);
 		glVertex2f(-0.5,-0.5);
 		glVertex2f( 0.0, 0.5);
 		glVertex2f( 0.5,-0.5);
 	glEnd();
 	glFlush(); //Executa os comandos OpenGL
}

