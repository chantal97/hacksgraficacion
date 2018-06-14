//JUAN CARLOS CONDE RAMÍREZ
//OBJETOS 3D - ILUMINACION
#include <GL/glut.h>
#include <stdio.h>

	//Matriz de colores
	float colores[9][3]=
	{
	    {1.0,1.0,1.0}, //0 blanco
		{1.0,0.0,0.0}, //1 rojo
		{0.0,1.0,0.0}, //2 verde
		{0.0,0.0,1.0}, //3 azul
        {1.0,1.0,0.0}, //4 amarillo
        {1.0,0.0,1.0}, //5 magneta
        {0.0,1.0,1.0}, //6 cian
        {0.5,0.5,0.5}, //7 gris
        {0.0,0.0,0.0}, //8 negro
	};

	int color  = 8;     // color de FIGURA
	int colorf = 8;     // color de FONDO
	int colorl = 3;     // color de LUZ
	//int colordif= 2; //color difuso de ambiental (verde)
    int coloresp= 5;//color especular ambiental
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

	GLfloat l_difusa[]={colores[color][0], colores[color][1], colores[color][2], 1.0f};
	GLfloat l_especular[]={colores[coloresp][0], colores[coloresp][1], colores[coloresp][2], 1.0f};
	GLfloat l_posicion[]={0.0, 0.0, 5.0, 1.0};

	glLightfv(GL_LIGHT0, GL_DIFFUSE, l_difusa);
	glLightfv(GL_LIGHT0, GL_SPECULAR, l_difusa);
	glLightfv(GL_LIGHT0, GL_POSITION, l_posicion);
	//glLightfv(GL_LIGHT0, GL_AMBIENT, l_a_color);
	glEnable (GL_LIGHT0);
}

void luzUno(void)
{
	GLfloat l_difusa[]={colores[1][0], colores[1][1], colores[1][2], 0.0f};
	GLfloat l_especular[]={colores[8][0], colores[8][1], colores[8][2], 0.0f};
	GLfloat l_posicion[]={0.0f, 5.0f, 0.0f, 1.0f};

	glLightfv(GL_LIGHT1, GL_DIFFUSE, l_difusa);
	glLightfv(GL_LIGHT1, GL_SPECULAR, l_difusa);
	glLightfv(GL_LIGHT1, GL_POSITION, l_posicion);
	//glEnable (GL_LIGHT1);
}

void luzDos(void){

    GLfloat l_difusa[]={colores[4][0], colores[4][1], colores[4][2], 0.0f};
	GLfloat l_especular[]={colores[6][0], colores[6][1], colores[6][2], 0.0f};
	GLfloat l_posicion[]={-5.0f, 0.0f, 0.0f, 1.0f};

	glLightfv(GL_LIGHT2, GL_DIFFUSE, l_difusa);
	glLightfv(GL_LIGHT2, GL_SPECULAR, l_difusa);
	glLightfv(GL_LIGHT2, GL_POSITION, l_posicion);

    //glEnable (GL_LIGHT2);

}

void luzTres(void)
{
	GLfloat l_difusa[]={colores[5][0], colores[5][1], colores[5][2], 1.0f};
	GLfloat l_especular[]={colores[1][0], colores[1][1], colores[1][2], 1.0f};

	GLfloat l_posicion[]={0.0f,0.0f, 5.0f, 1.0f};
	GLfloat spot_direccion[]={0.0f,0.0f, -5.0f, 1.0f};

	glLightfv(GL_LIGHT3, GL_DIFFUSE, l_difusa);
	glLightfv(GL_LIGHT3, GL_SPECULAR, l_difusa);
	glLightfv(GL_LIGHT3, GL_POSITION, l_posicion);

	glLightf(GL_LIGHT3, GL_SPOT_CUTOFF, 3.0);
	glLightf(GL_LIGHT3, GL_SPOT_EXPONENT, 2.0);
	glLightfv(GL_LIGHT1, GL_SPOT_DIRECTION, spot_direccion);
	//glEnable (GL_LIGHT3);
}

void init(void)
{
	luzAmbiental();
	glEnable(GL_LIGHTING);
	glEnable(GL_DEPTH_TEST);
	//glClearColor(colores[colorf][0],colores[colorf][1],colores[colorf][2], 0.0f);
}

void display(void)
{

glClearColor(colores[colorf][0],colores[colorf][1],colores[colorf][2], 0.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	gluPerspective(20.0f, 1.0f, 1.0f, 10.0f);
	gluLookAt(0.0f, 0.0f, 5.0f,
			  0.0f, 0.0f, 0.0f,
			  0.0f, 1.0f, 0.0f);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glPushMatrix();

		glTranslatef(xpos,ypos,0);

		if(opc != 9)
			glScalef(inc,inc,inc);
		else
			glScalef(inc-0.15,inc-0.15,inc-0.15);

		glRotatef(alpha, 1.0f, 0.0f, 0.0f);
		glRotatef(beta, 0.0f, 1.0f, 0.0f);

		glColor3f(1.0f, 1.0f, 1.0f);

		switch(opc)
		{
			case 1:
				glutSolidCube(0.5);
				break;
            case 2:
                glutSolidCone(1,2,30,30);
                break;
            case 3:
				glutSolidSphere(1,25,25);
				break;
			case 4:
				glutSolidTeapot(1);
				break;
			case 5:
				glutSolidTorus(0.4,0.8,10,50);
				break;
			case 6:
				glutSolidIcosahedron();
				break;
			case 7:
				glutSolidDodecahedron();
				break;
			case 8:
				glutSolidOctahedron();
				break;
			case 9:
				glutSolidTetrahedron();
				break;
		}

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

		case F2:
            opc=2;
            break;
        case F3:
			opc=3;
			break;
		case F4:
			opc=4;
			break;
		case F5:
			opc=5;
			break;
		case F6:
			opc=6;
			break;
		case F7:
			opc=7;
			break;
		case F8:
			opc=8;
			break;
		case F9:
			opc=9;
			break;

		case C1:
			colorf=8;
			break;
        case C2:
			colorf=0;
			break;

		case C3:
            color=2;
            break;

		case C4:
            color=1;
            break;

		 case C5:
			color=3;
			break;

		 case C6:
			color=4;
			break;

		 case C7:
			color=5;
			break;

		 case C8:
			color=6;
			break;

		 case C9:
			color=7;
			break;


		case E1:
			glEnable(GL_LIGHT1);
			break;
		case E2:
		    glEnable(GL_LIGHT2);

            break;

		case D1:
           glDisable(GL_LIGHT1);
            break;

		case D2:
            glDisable(GL_LIGHT2);
            break;
	}

	luzAmbiental();
	luzUno();
	luzDos();
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
	glutAddMenuEntry("Cone", F2);
    glutAddMenuEntry("Esfera", F3);
    glutAddMenuEntry("Vasija", F4);
    glutAddMenuEntry("Dona", F5);
    glutAddMenuEntry("Icosahedron", F6);
    glutAddMenuEntry("Docahedron", F7);
    glutAddMenuEntry("Octahedron", F8);
    glutAddMenuEntry("Tetahedron", F9);
	/*
        AQUI VAN LAS OPCIONES
    */

	//----------------------------------------------------------

    // NUVEL 2 DE SUB-MENU PARA COLOR DE FONDO
	menuFONDO = glutCreateMenu(menuFiguras);
	glutAddMenuEntry("Negro", C1);
    glutAddMenuEntry("Blanco", C2);
	/*
        AQUI VAN LAS OPCIONES
    */

	//----------------------------------------------------------

        // NIVEL 3 DE SUB-MENUS PARA ACTIVAR LUCES
        on = glutCreateMenu(menuFiguras);
        /*
            AQUI VAN LAS OPCIONES
        */
	glutAddMenuEntry("Activar luz 1", E1);
    glutAddMenuEntry("Activar luz 2", E2);
        // NIVEL 3 DE SUB-MENUS PARA DESACTIVAR LUCES
        off = glutCreateMenu(menuFiguras);
        /*
            AQUI VAN LAS OPCIONES
        */
	glutAddMenuEntry("Desactivar luz 1", D1);
    glutAddMenuEntry("Desactivar luz 2", D2);
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
    glutAddMenuEntry("Verde", C3);
    glutAddMenuEntry("Rojo", C4);
    glutAddMenuEntry("Azul", C5);
    glutAddMenuEntry("Amarillo", C6);
    glutAddMenuEntry("Magneta", C7);
    glutAddMenuEntry("Cian", C8);
    glutAddMenuEntry("Gris", C9);

    // MENU PRINCIPAL (NIVEL 1)
	menuMain = glutCreateMenu(menuFiguras);
    glutAddSubMenu("Figura 3D", menuFIGURA);
    glutAddSubMenu("Fondo", menuFONDO);
    glutAddSubMenu("Color Figuras: ", menuCOLOR);
    glutAddSubMenu("Activar Luces:", on);
    glutAddSubMenu("Desactivar Luces: ", off);
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
	glutInitWindowSize(500, 500);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("Figuras 3D");
	init();
	glutDisplayFunc(display);
	glutSpecialFunc(ControlTeclado);
	glutMouseFunc(onMouse);
	glutMotionFunc(onMotion);
	creacionMenu();
	glutMainLoop();

	return 0;
}
