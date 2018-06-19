//JUAN CARLOS CONDE RAMÍREZ
//OBJETOS 3D - ILUMINACION
#include <stdio.h>
#include <GL/glut.h>
#include <GL/gl.h>

	//Matriz de colores
	float colores[4][3]=
	{
	    {1.0,1.0,1.0}, //0 blanco
		{1.0,0.0,0.0}, //1 rojo
		{0.0,1.0,0.0}, //2 verde
		{0.0,0.0,1.0}, //3 azul
	};

	int color  = 2;     // color de FIGURA
	int colorf = 0;     // color de FONDO
	int colorl = 3;     // color de LUZ

	//variables globales para la rotacion
	float alpha, beta;
	int x0, y0;
	int opc;

	//Variables globales para las transformaciones
	float xpos=0, ypos=0, inc=0.5;

	//Menu de figuras a elegir
	typedef enum{F1,F2,F3,F4,F5,F6,F7,F8,F9,C1,C2,C3,C4,C5,C6,C7,C8,C9,E1,E2,D1,D2,S1,S2}opcionMenu;

void luzAmbiental(void)
{
	GLfloat l_difusa[]={0.22f, 0.17f, 0.12f, 0.0f};
	GLfloat l_especular[]={0.22f, 0.17f, 0.12f, 0.0f};
	GLfloat l_posicion[]={0.0, 0.0, 5.0, 1.0};
	GLfloat l_a_color[]={0.22f, 0.17f, 0.12f, 0.0f};
	
	glLightfv(GL_LIGHT0, GL_DIFFUSE, l_difusa);
	glLightfv(GL_LIGHT0, GL_SPECULAR, l_difusa);
	// glLightfv(GL_LIGHT0, GL_POSITION, l_posicion);
	glLightfv(GL_LIGHT0, GL_AMBIENT, l_a_color);
	glEnable (GL_LIGHT0);
	glutPostRedisplay();
}

void luzUno(void)
{
	GLfloat l_difusa[]={colores[2][0], colores[2][1], colores[2][2], 0.0f};
	GLfloat l_especular[]={colores[2][0], colores[2][1], colores[2][2], 0.0f};
	GLfloat l_posicion[]={0.0f, 5.0f, 0.0f, 1.0f};

	glLightfv(GL_LIGHT1, GL_DIFFUSE, l_difusa);
	glLightfv(GL_LIGHT1, GL_SPECULAR, l_difusa);
	glLightfv(GL_LIGHT1, GL_POSITION, l_posicion);
	//glEnable (GL_LIGHT1);
}

void luzTres(void)
{
	GLfloat l_difusa[]={colores[0][0], colores[0][1], colores[0][2], 0.0f};
	GLfloat l_especular[]={colores[0][0], colores[0][1], colores[0][2], 0.0f};

	GLfloat l_posicion[]={0.0, 0.0, 0.0, 1.0};
	GLfloat spot_direccion[]={0.0, 0.0, 0.0, 0.0};

	glLightfv(GL_LIGHT3, GL_DIFFUSE, l_difusa);
	glLightfv(GL_LIGHT3, GL_SPECULAR, l_difusa);
	glLightfv(GL_LIGHT3, GL_POSITION, l_posicion);

	glLightf(GL_LIGHT3, GL_SPOT_CUTOFF, 3.0);
	glLightf(GL_LIGHT3, GL_SPOT_EXPONENT, 2.0);
	glLightfv(GL_LIGHT1, GL_SPOT_DIRECTION, spot_direccion);
	//glEnable (GL_LIGHT3);
}


void miCubo(){

    //glPolygonMode(GL_FRONT,GL_LINE);
    //base
	glColor3f(1.0f, 0.0f, 0.0f);

    glBegin(GL_QUADS);
		glNormal3f(0.0,-1.0,0.0);    
		glVertex3f(0.5,-0.5,0.5);
		glVertex3f(0.5,-0.5,-0.5);
		glVertex3f(-0.5,-0.5,-0.5);
		glVertex3f(-0.5,-0.5,0.5);
    glEnd();

    //cara derecha
    glBegin(GL_QUADS);
		glNormal3f(1.0,0.0,0.0);
    	glVertex3f(0.5,-0.5,0.5);
    	glVertex3f(0.5,-0.5,-0.5);
    	glVertex3f(0.5,0.5,-0.5);
    	glVertex3f(0.5,0.5,0.5);    
    glEnd();

    //caratrasera
    glBegin(GL_QUADS);
		glNormal3f(0.0,0.0,-1.0);
		glVertex3f(0.5,-0.5,-0.5);
		glVertex3f(0.5,0.5,-0.5);
		glVertex3f(-0.5,0.5,-0.5);
		glVertex3f(-0.5,-0.5,-0.5);    
    glEnd();
    //cara izquierda
    glBegin(GL_QUADS);
		glNormal3f(-1.0,0.0,0.0);
		glVertex3f(-0.5,-0.5,0.5);
		glVertex3f(-0.5,-0.5,-0.5);
		glVertex3f(-0.5,0.5,-0.5);
		glVertex3f(-0.5,0.5,0.5);		
    glEnd();
    //cara frontal
    glBegin(GL_QUADS);
		glNormal3f(0.0,0.0,1.0);
		glVertex3f(-0.5,-0.5,0.5);
		glVertex3f(0.5,-0.5,0.5);
		glVertex3f(0.5,0.5,0.5);
		glVertex3f(-0.5,0.5,0.5);		
    glEnd();
    //tapa
    glBegin(GL_QUADS);
		glNormal3f(0.0,1.0,0.0);
		glVertex3f(0.5,0.5,0.5);
		glVertex3f(0.5,0.5,-0.5);
		glVertex3f(-0.5,0.5,-0.5);
		glVertex3f(-0.5,0.5,0.5);    
    glEnd();


}

void silla(){
    //pata trasera izquierda
    glPushMatrix();
        glTranslatef(-0.5,-0.5,-0.5);
        glScalef(0.2,1.0,0.2);
        miCubo();
    glPopMatrix();
     //pata trasera derecha
    glPushMatrix();
        glTranslatef(0.5,-0.5,-0.5);
        glScalef(0.2,1.0,0.2);
        miCubo();
    glPopMatrix();

     //pata delantera izquierda
    glPushMatrix();
        glTranslatef(-0.5,-0.5,0.5);
        glScalef(0.2,1.0,0.2);
        miCubo();
    glPopMatrix();

     //pata delantera derecha
    glPushMatrix();
        glTranslatef(0.5,-0.5,0.5);
        glScalef(0.2,1.0,0.2);
        miCubo();
    glPopMatrix();

    //asiento
    glPushMatrix();
        glTranslatef(0.0,0.0,0.0);
        glScalef(1.2,0.2,1.2);
        miCubo();
    glPopMatrix();

    //respaldo
    glPushMatrix();
        glTranslatef(0.0,0.5,-0.5);
        glScalef(1.2,1.0,0.2);
        miCubo();
    glPopMatrix();
}

void init(void)
{
	luzAmbiental();
	glEnable(GL_LIGHTING);
	glEnable(GL_DEPTH_TEST);
}

void display(void)
{
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	gluPerspective(30.0f, 1.0f, 1.0f, 10.0f);
	gluLookAt(0.0f, 0.0f, 10.0f,
			  0.0f, 0.0f, 0.0f,
			  0.0f, 1.0f, 0.0f);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	luzAmbiental();
	glPushMatrix();

		glTranslatef(xpos,ypos,0);	
		glRotatef(alpha, 1.0f, 0.0f, 0.0f);
		glRotatef(beta, 0.0f, 1.0f, 0.0f);
		silla();

	glPopMatrix();

	glFlush();
	glutSwapBuffers();
}

//Accion del mouse
void onMouse(int button, int state, int x, int y)
{
	if ( (button == GLUT_LEFT_BUTTON) & (state == GLUT_DOWN) )
	{
		x0 = x;
		y0 = y;
	}
}

//Incremento o decremente de los angulos de rotacion
void onMotion(int x, int y)
{
	alpha = (alpha + (y - y0));
	beta = (beta + (x - x0));
	x0 = x; y0 = y;
	glutPostRedisplay();
}

void menuFiguras(int opcion)
{
	switch(opcion)
	{
		case F1:
			opc=1;
			break;
		case C1:
			colorf=0;
			break;
		case E1:
			glEnable(GL_LIGHT1);
			break;
	}

	luzAmbiental();
	luzUno();
	luzTres();

	glutPostRedisplay();
}

//Creacion de menu y submenus
void creacionMenu(void)
{
	int menuFIGURA, menuFONDO, menuCOLOR, menuLUCES, menuMain;
	int on, off;

    //----------------------------------------------------------

    // NIVEL 2 DE SUB-MENU PARA TIPO DE FIGURA
	menuFIGURA = glutCreateMenu(menuFiguras);
	glutAddMenuEntry("Cube", F1);
	/*
        AQUI VAN LAS OPCIONES
    */

	//----------------------------------------------------------

    // NUVEL 2 DE SUB-MENU PARA COLOR DE FONDO
	menuFONDO = glutCreateMenu(menuFiguras);
	/*
        AQUI VAN LAS OPCIONES
    */

	//----------------------------------------------------------

        // NIVEL 3 DE SUB-MENUS PARA ACTIVAR LUCES
        on = glutCreateMenu(menuFiguras);
        /*
            AQUI VAN LAS OPCIONES
        */

        // NIVEL 3 DE SUB-MENUS PARA DESACTIVAR LUCES
        off = glutCreateMenu(menuFiguras);
        /*
            AQUI VAN LAS OPCIONES
        */

    // NIVEL 2 DE SU-MENUS
	menuLUCES = glutCreateMenu(menuFiguras);
	/*
        AQUI VAN LOS SUB-MENUS DE NIVEL 3
    */

	//----------------------------------------------------------

    // NIVEL 2 DE SUB-MENUS
	menuCOLOR = glutCreateMenu(menuFiguras);
	/*
        AQUI VAN LAS OPCIONES
    */

    // MENU PRINCIPAL (NIVEL 1)
	menuMain = glutCreateMenu(menuFiguras);
    glutAddSubMenu("Figura 3D", menuFIGURA);
	/*
        AQUI VAN LOS SUB-MENUS DE NIVEL 2
    */

	glutAttachMenu(GLUT_RIGHT_BUTTON);
}

void ControlTeclado(int Key, int x, int y)
{
	switch(Key)
	{
		//TRASLACION
		case GLUT_KEY_RIGHT:
			xpos+=0.05;
			break;
		case GLUT_KEY_LEFT:
			xpos-=0.05;
			break;
		case GLUT_KEY_UP:
			ypos+=0.05;
			break;
		case GLUT_KEY_DOWN:
			ypos-=0.05;
			break;
		//ESCALAMIENTO
		case GLUT_KEY_HOME:
			inc+=0.05;
			break;
		case GLUT_KEY_END:
			if(inc > 0.0)
				inc-=0.05;
			break;
	}
	glutPostRedisplay();
}

int main(int argc, char **argv)
{
    glutInit(&argc, argv);

	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(700, 700);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("Figuras 3D");
	glutDisplayFunc(display);
	glutSpecialFunc(ControlTeclado);
	glutMouseFunc(onMouse);
	glutMotionFunc(onMotion);
	creacionMenu();
    init();	
	glutMainLoop();

    return 0;
}