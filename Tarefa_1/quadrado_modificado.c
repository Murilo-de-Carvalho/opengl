//*****************************************************
//
// QuadradoVerde.c
// Um programa OpenGL simples que abre uma janela GLUT
// e faz o desenho de um quadrado verde em fundo branco
//
//*****************************************************

// =======================================================
// Resposta: A função glutReshapeFunc() estava comentada,
// então, ao modificar as dimensões da janela, a imagem
// deixaria de ser um quadrado e se adaptaria ao formato
// da janela.
// =======================================================

#include <stdlib.h>
#include <GL/glut.h>

// Funcao de  callback de redesenho da janela de visualizacao
void Desenha(void)
{
	// Limpa a janela de visualizacao com a cor
	// de fundo definida previamente
	glClear(GL_COLOR_BUFFER_BIT);

	// Desenha um quadrado no qual os vertices possuem a cor verde
	glBegin(GL_QUADS);
		//Vertices em ordem anti-horaria:
		glVertex2f(-0.8f,-0.8f);
		glVertex2f(-0.8f,0.8f);
		glVertex2f(0.8f,0.8f);
		glVertex2f(0.8f,-0.8f);
	glEnd();

	// Executa os comandos OpenGL para atualizar o frame buffer (exibe o desenho da tela)
	glFlush();
}

// Funcao callback chamada quando o tamanho da janela eh alterado
void AlteraTamanhoJanela(GLsizei w, GLsizei h)
{
	// Evita a divisao por zero
	if(h == 0) h = 1;

	// Especifica as dimensoes da Viewport
	glViewport(0, 0, w, h);

	// Inicializa o sistema de coordenadas
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	// Estabelece a janela de selecao (esquerda, direita, inferior,
	// superior) mantendo a proporcao com a janela de visualizacao
	if (w <= h)
		gluOrtho2D (-1.0f, 1.0f, -1.0f*h/w, 1.0f*h/w);
	else
		gluOrtho2D (-1.0f*w/h, 1.0f*w/h, -1.0f, 1.0f);
}

// Funcao callback chamada para gerenciar eventos de teclas
void Teclado (unsigned char key, int x, int y)
{
	if (key == 27)
		exit(0);
		
	 switch (key) {
            case 'R': 
            case 'r':// muda a cor corrente para vermelho
                     glColor3f(1.0f, 0.0f, 0.0f);
                     break;
            case 'G':
            case 'g':// muda a cor corrente para verde
                     glColor3f(0.0f, 1.0f, 0.0f);
                     break;
            case 'B':
            case 'b':// muda a cor corrente para azul
                     glColor3f(0.0f, 0.0f, 1.0f);
                     break;
    }
    glutPostRedisplay();
}
       
// Função callback chamada para gerenciar eventos do mouse
void GerenciaMouse(int button, int state, int x, int y)
{
    if (button == GLUT_LEFT_BUTTON)
         if (state == GLUT_DOWN) {
                  // Executarah uma acao definida pelo programador 
                 // quando o usuario clicar com o botao do mouse (LMB)
                 
         }
    glutPostRedisplay();
}

// Função callback chamada para gerenciar eventos do teclado   
// para teclas especiais, tais como F1, PgDn e Home
void TeclasEspeciais(int key, int x, int y)
{
    if(key == GLUT_KEY_UP) {
        glColor3f(1.0f, 0.0f, 0.0f);
           //acao definida ao pressionar a tecla seta acima
    }
    if(key == GLUT_KEY_DOWN) {
        glColor3f(0.0f, 0.0f, 1.0f);
         //acao definida ao pressionar a tecla seta abaixo
    }
    glutPostRedisplay();
}

// Funcao responsavel por inicializar parametros e variaveis
void Inicializa (void)
{
	// Define a cor de fundo da janela de visualizaca como branca
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	
	// Altera a cor dos vertices para verde inicialmente
	glColor3f(0.0f, 1.0f, 0.0f);

}

// Programa Principal
int main(int argc, char **argv)
{
	glutInit(&argc, argv);

	// Define do modo de operacao da GLUT
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);

	// Especifica a posicao inicial da janela GLUT
	glutInitWindowPosition(5,5);

	// Especifica o tamanho inicial em pixels da janela GLUT
	glutInitWindowSize(450,450);

	// Cria a janela passando como argumento o titulo da mesma
	glutCreateWindow("Quadrado OpenGL");

	// Registra a funcao callback de redesenho da janela de visualizacao
	glutDisplayFunc(Desenha);

	// Registra a funcao callback de redimensionamento da janela de visualizacao
	glutReshapeFunc(AlteraTamanhoJanela);

	// Registra a funcao callback para tratamento das teclas ASCII
	glutKeyboardFunc (Teclado);
	// Registra a funcao callback para tratamento do mouse
	glutMouseFunc(GerenciaMouse);
	// Registra a funcao callback para tratamento das teclas especiais (F1, Home, etc...)
        glutSpecialFunc(TeclasEspeciais); 

	// Chama a funcao responsavel por fazer as inicializacoes
	Inicializa();

	// Inicia o processamento e aguarda interacoes do usuario
	glutMainLoop();

	return 0;
}
