#include <GL/glut.h>
#include <stdio.h>
#include <malloc.h>

void luzAmbiental(void)
{
GLfloat l_ambiente[]={1.0f, 1.0f, 1.0f, 1.0f};
    glLightModelfv(GL_LIGHT_MODEL_AMBIENT,l_ambiente);
    glLightfv(GL_LIGHT0, GL_AMBIENT, l_ambiente);

	GLfloat l_difusa[]={0.5f, 0.5f, 0.5f, 0.0f};
	GLfloat l_especular[]={0.5f, 0.5f, 0.5f, 0.0f};
	GLfloat l_posicion[]={0.0, 0.0, 5.0, 1.0};

	glLightfv(GL_LIGHT0, GL_DIFFUSE, l_difusa);
	glLightfv(GL_LIGHT0, GL_SPECULAR, l_difusa);
	glLightfv(GL_LIGHT0, GL_POSITION, l_posicion);
	//glLightfv(GL_LIGHT0, GL_AMBIENT, l_a_color);
	glEnable (GL_LIGHT0);

}

void init(void)
{
	luzAmbiental();
	glEnable(GL_LIGHTING);
	glEnable(GL_DEPTH_TEST);
    glEnable(GL_NORMALIZE);
    glDepthFunc(GL_LEQUAL);
}

GLuint texture_id[4];

int  LoadBMP(char *filename, int tex_name)
 {
    #define SAIR        {fclose(fp_archivo); return -1;}
    #define CTOI(C)     (*(int*)&C)

    GLubyte     *image;
    GLubyte     Header[0x54];
    GLuint      DataPos, imageSize;
    GLsizei     Width,Height;

    int nb = 0;


    // Abre un archivo y efectua la lectura del encabezado del archivo BMP
    FILE * fp_archivo = fopen(filename,"rb");
    if (!fp_archivo)
        return -1;
    if (fread(Header,1,0x36,fp_archivo)!=0x36)
        SAIR;
    if (Header[0]!='B' || Header[1]!='M')
        SAIR;
    if (CTOI(Header[0x1E])!=0)
        SAIR;
    if (CTOI(Header[0x1C])!=24)
        SAIR;

    // Recupera los atributos de la altura y ancho de la imagen

    Width   = CTOI(Header[0x12]);
    Height  = CTOI(Header[0x16]);
    ( CTOI(Header[0x0A]) == 0 ) ? ( DataPos=0x36 ) : ( DataPos = CTOI(Header[0x0A]) );

    imageSize=Width*Height*3;

    // Llama a la imagen
    image = (GLubyte *) malloc ( imageSize );
    int retorno;
    retorno = fread(image,1,imageSize,fp_archivo);

    if (retorno !=imageSize)
     {
        free (image);
        SAIR;
     }

    // Invierte los valores de R y B
    int t, i;

    for ( i = 0; i < imageSize; i += 3 )
     {
        t = image[i];
        image[i] = image[i+2];
        image[i+2] = t;
     }

    // Tratamiento de textura para OpenGL

    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_MODULATE);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_MODULATE);

    glTexEnvf ( GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE );

    // Manipulacion en memoria de la textura
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, Width, Height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);

    fclose (fp_archivo);
    free (image);
    return 1;
 }



void myinit(void)
{

    // Propiedades del material
	GLfloat mat_especular[] = { 1.0f, 0.0f, 0.0f, 1.0f};
	GLfloat mat_shininess[] = { 50.0f};
	GLfloat mat_ambiente[] = { 0.25f, 0.25f, 0.25f, 1.0f};
	GLfloat mat_difuso[] = { 0.5f, 0.5f, 0.5f, 1.0f};

	glClearColor (0.0, 0.0, 0.0, 0.0);

	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_especular);
	glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_difuso);
	glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambiente);

	// Parametros de las luces

	// Habilitando la luz
	glEnable(GL_LIGHTING);

	// Especifica una luz de direccion simple
	GLfloat ambiente1[] = { 0.5f,0.5f,0.5f};
	GLfloat difusa1[] = { 0.5f,0.5f,0.5f};
	GLfloat especular1[] = { 1.0f,0.0f,0.0f};
	GLfloat posicion1[] = { 0.0f,0.0f,5.0f,0.0};

	glLightfv(GL_LIGHT0, GL_AMBIENT, ambiente1);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, difusa1);
	glLightfv(GL_LIGHT0, GL_SPECULAR, especular1);
	glLightfv(GL_LIGHT0, GL_POSITION, posicion1);

	glEnable(GL_LIGHT0);

	// Especifica un solo proyector posicional
	GLfloat ambiente2[] = { 1.0f,1.0f,0.0f};
	GLfloat difuso2[] = { 1.0f,0.0f,0.0f};
	GLfloat posicion2[] = { 1.0f,0.0f,5.0f,1.0};
	GLfloat direccion2[] = {0.0f,0.0f,-5.0f};

	glLightfv(GL_LIGHT1, GL_AMBIENT, ambiente2);
	glLightfv(GL_LIGHT1, GL_DIFFUSE, difuso2);
	glLightfv(GL_LIGHT1, GL_POSITION, posicion2);
	glLightfv(GL_LIGHT1, GL_SPOT_DIRECTION, direccion2);
	glLightf(GL_LIGHT1, GL_SPOT_CUTOFF, 15.0f);

	glEnable(GL_LIGHT1);

	// prueba
	GLfloat l_ambiente[]={1.0f, 1.0f, 1.0f, 1.0f};
    glLightModelfv(GL_LIGHT_MODEL_AMBIENT,l_ambiente);
    glLightfv(GL_LIGHT0, GL_AMBIENT, l_ambiente);

	GLfloat l_difusa[]={0.5f, 0.5f, 0.5f, 0.0f};
	GLfloat l_especular[]={0.5f, 0.5f, 0.5f, 0.0f};
	GLfloat l_posicion[]={0.0, 0.0, 5.0, 1.0};

	glLightfv(GL_LIGHT2, GL_DIFFUSE, l_difusa);
	glLightfv(GL_LIGHT2, GL_SPECULAR, l_difusa);
	glLightfv(GL_LIGHT2, GL_POSITION, l_posicion);
	//glLightfv(GL_LIGHT0, GL_AMBIENT, l_a_color);
	glEnable (GL_LIGHT2);


	glDepthFunc(GL_LESS);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_AUTO_NORMAL);
    glEnable(GL_NORMALIZE);
    //nuevo depth agregado
     glDepthFunc(GL_LEQUAL);

	glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glTranslatef (0.0, 0.0, -5.0);
    glEnable(GL_TEXTURE_2D);//
    glPixelStorei(GL_UNPACK_ALIGNMENT,1);
	glGenTextures(2,texture_id);
	glBindTexture(GL_TEXTURE_2D,texture_id[0]);
	LoadBMP("aceroInox.bmp",0);
	//glGenTextures(2,&texture_id2);
	glBindTexture(GL_TEXTURE_2D,texture_id[1]);
	LoadBMP("cromo.bmp",1);
    glBindTexture(GL_TEXTURE_2D,texture_id[2]);
	LoadBMP("carbono.bmp",2);
}
	//variables globales para la rotación
	float alpha=45, beta=45;

	//variables globales para la cámara
	float eyeX=0.0f, eyeY=0.0f, eyeZ=5.0f;
	float oriX=0.0f, oriY=1.0f, oriZ=0.0f;

    //variables globales para el cálculo de los grados
	int x0, y0;
   // variables globales para  el cambio de figuras

    int opc;
   typedef enum{F1,F2,F3,F4,F5,F6,F7,F8,F9,C1,C2,C3,C4,C5,C6,C7,C8,C9,E1,E2,D1,D2,S1,S2}opcionMenu;

GLfloat ala2[] = {

    //parte de arriba
    1.0,0.5,0.5,
    1.5,0.5,-0.5,
    0.60,0.5,0.5,
    0.60,0.5,-0.7,
    -2.0,0.5,0.5,
    -2.0,0.5,-0.1,

     //parte de abajo

      1.0,0.2,0.5,
      1.5,0.2,-0.5,
      0.60,0.2,0.5,
      0.60,0.2,-0.7,
      -2.0,0.2,0.5,
      -2.0,0.2,-0.1,


      //cara lateral derecha
            1.0,0.2,0.5,
            1.5,0.2,-0.5,
            1.5,0.5,-0.5,
            1.0,0.5,0.5,
            1.0,0.2,0.5,

       //cara lateral derecha arriba
           0.60,0.2,-0.7,
           1.5,0.2,-0.5,
           1.5,0.5,-0.5,
           0.60,0.5,-0.7,
           0.60,0.2,-0.7,

       //cara trasera
          -2.0,0.2,-0.1,
          0.60,0.2,-0.7,
          0.60,0.5,-0.7,
          -2.0,0.5,-0.1,
          -2.0,0.2,-0.1,

          //cara lateral izquierda
          -2.0,0.2,-0.1,
          -2.0,0.2,0.5,
          -2.0,0.5,0.5,
          -2.0,0.5,-0.1,
          -2.0,0.2,-0.1,

          //cara frontal
          -2.0,0.2,0.5,
           1.0,0.2,0.5,
           1.0,0.5,0.5,
          -2.0,0.5,0.5,
          -2.0,0.2,0.5,

};

GLfloat normales[]={
 //parte de arriba
        0.0,1.0,0.0,
        0.0,1.0,0.0,
        0.0,1.0,0.0,
        0.0,1.0,0.0,

//parte de abajo
        0.0,-1.0,0.0,
        0.0,-1.0,0.0,
        0.0,-1.0,0.0,
        0.0,-1.0,0.0,

//cara lateral derecha
        1.0,0.0,0.0,
        1.0,0.0,0.0,
        1.0,0.0,0.0,
        1.0,0.0,0.0,

//cara trasera
        0.0,0.0,-1.0,
        0.0,0.0,-1.0,
        0.0,0.0,-1.0,
        0.0,0.0,-1.0,

//cara lateral izquierda
        -1.0,0.0,0.0,
        -1.0,0.0,0.0,
        -1.0,0.0,0.0,
        -1.0,0.0,0.0,
//cara frontal
        0.0,0.0,1.0,
        0.0,0.0,1.0,
        0.0,0.0,1.0,
        0.0,0.0,1.0

};

GLfloat miCubo2[]={
                        // tapa
                     0.5,0.5,0.5,
                     0.5,0.5,-0.5,
                     -0.5,0.5,-0.5,
                     -0.5,0.5,0.5,
                    //base
                     0.5,-0.5,0.5,
                     0.5,-0.5,-0.5,
                     -0.5,-0.5,-0.5,
                     -0.5,-0.5,0.5,

                   //cara derecha
	                  0.5,-0.5,0.5,
                      0.5,-0.5,-0.5,
                      0.5,0.5,-0.5,
                      0.5,0.5,0.5,

                    //cara trasera
                     0.5,-0.5,-0.5,
                     0.5,0.5,-0.5,
                     -0.5,0.5,-0.5,
                    -0.5,-0.5,-0.5,

                    //cara izquierda
                     -0.5,-0.5,0.5,
                     -0.5,-0.5,-0.5,
                     -0.5,0.5,-0.5,
                     -0.5,0.5,0.5,

                    // cara frontal
                     -0.5,-0.5,0.5,
                      0.5,-0.5,0.5,
                      0.5,0.5,0.5,
                     -0.5,0.5,0.5,

};
GLfloat texturas[]={
       // tapa
        0,0,
        0,1,
        1,1,
        1,0,

      // base
        0,1,
        0,0,
        1,0,
        1,1,

    //cara derecha
        0,0,
        1,0,
        1,1,
        0,1,

    // cara trasera
        1,0,
        1,1,
        0,1,
        0,0,

    //cara izquierda
        1,0,
        1,1,
        0,1,
        0,0,

    // cara frontal
        0,0,
        1,0,
        1,1,
        0,1,


};

GLfloat cola2[] = {

            //cola

             //parte superior
             0.0,0.25,0.5,
             1.0,0.25,0.25,
             1.0,0.25,-0.25,
             0.0,0.25,-0.5,
             0.0,0.25,0.5,

            //parte inferior
            0.0,-0.5,0.5,
            1.0,-0.5,0.25,
            1.0,-0.5,-0.25,
            0.0,-0.5,-0.5,
            0.0,-0.5,0.5,

             //cara lateral derecha
           1.0,-0.5,-0.25,
           1.0,-0.5,0.25,
           1.0,0.25,0.25,
           1.0,0.25,-0.25,
           1.0,-0.5,-0.25,

             //cara trasera
             0.0,-0.5,-0.5,
             1.0,-0.5,-0.25,
             1.0,0.25,-0.25,
             0.0,0.25,-0.5,
             0.0,-0.5,-0.5,

           //cara lateral izquierda
           0.0,-0.5,-0.5,
           0.0,-0.5,0.5,
           0.0,0.25,0.5,
           0.0,0.25,-0.5,
           0.0,-0.5,-0.5,

             //cara frontal
             0.0,-0.5,0.5,
             1.0,-0.5,0.25,
             1.0,0.25,0.25,
             0.0,0.25,0.5,
             0.0,-0.5,0.5,

};

void MaterialOroPulido(){

	GLfloat mat_ambient[]={  0.24725, 0.2245,0.0645 , 1.0f};
	GLfloat mat_difuse[]={0.34615 , 0.3143 , 0.0903, 1.0f};
	GLfloat mat_specular[]={0.797357, 0.723991,0.208006 , 1.0f};
	GLfloat mat_shininess[]={ 83.2};
	//GLfloat mat_posicion[]={0.0f, 5.0f, 0.0f, 1.0f};

	glMaterialfv(GL_FRONT,GL_AMBIENT,mat_ambient);
	glMaterialfv(GL_FRONT,GL_DIFFUSE,mat_difuse);
	glMaterialfv(GL_FRONT,GL_SPECULAR,mat_specular);
    glMaterialfv(GL_FRONT,GL_SHININESS,mat_shininess);
    // glFlush();
}




void MaterialOro(){

	GLfloat mat_ambient[]={  0.24725, 0.1995 ,0.0745 , 1.0f};
	GLfloat mat_difuse[]={ 0.75164 , 0.60648 ,0.22648  , 1.0f};
	GLfloat mat_specular[]={0.628281 , 0.555802  ,0.366065  , 1.0f};
	GLfloat mat_shininess[]={51.2f};
	//GLfloat mat_posicion[]={0.0f, 5.0f, 0.0f, 1.0f};

	glMaterialfv(GL_FRONT,GL_AMBIENT,mat_ambient);
	glMaterialfv(GL_FRONT,GL_DIFFUSE,mat_difuse);
	glMaterialfv(GL_FRONT,GL_SPECULAR,mat_specular);
    glMaterialfv(GL_FRONT,GL_SHININESS,mat_shininess);
    // glFlush();
}

void ala1(){

glEnableClientState(GL_NORMAL_ARRAY);
glNormalPointer(GL_FLOAT,0,normales);
    // activa y especifica el apuntado al arreglo de vértices
    glEnableClientState(GL_VERTEX_ARRAY);
        glVertexPointer(3, GL_FLOAT, 0,  ala2);

     glEnableClientState(GL_TEXTURE_COORD_ARRAY);
      glTexCoordPointer(2,GL_FLOAT,0,texturas);
      glBindTexture(GL_TEXTURE_2D,texture_id[0]);

        // dibuja un cubo
        glDrawArrays(GL_TRIANGLE_STRIP,0, 37);
       // glDrawArrays(GL_NORMAL_ARRAY_POINTER,0,7);
     glDisableClientState(GL_TEXTURE_COORD_ARRAY);
// desactiva el arreglo de vértices después de dibujar
    glDisableClientState(GL_VERTEX_ARRAY);
glDisableClientState(GL_NORMAL_ARRAY);
}

void miCubo(){
glEnableClientState(GL_NORMAL_ARRAY);
glNormalPointer(GL_FLOAT,0,normales);
    // activa y especifica el apuntado al arreglo de vértices
    glEnableClientState(GL_VERTEX_ARRAY);
        glVertexPointer(3, GL_FLOAT, 0,  miCubo2);

     glEnableClientState(GL_TEXTURE_COORD_ARRAY);
      glTexCoordPointer(2,GL_FLOAT,0,texturas);
      glBindTexture(GL_TEXTURE_2D,texture_id[1]);

        // dibuja un cubo
        glDrawArrays(GL_QUADS,0, 24);
       // glDrawArrays(GL_NORMAL_ARRAY_POINTER,0,7);
     glDisableClientState(GL_TEXTURE_COORD_ARRAY);
// desactiva el arreglo de vértices después de dibujar
    glDisableClientState(GL_VERTEX_ARRAY);
glDisableClientState(GL_NORMAL_ARRAY);

}
void cola(){

glEnableClientState(GL_NORMAL_ARRAY);
glNormalPointer(GL_FLOAT,0,normales);
    // activa y especifica el apuntado al arreglo de vértices
    glEnableClientState(GL_VERTEX_ARRAY);
        glVertexPointer(3, GL_FLOAT, 0,cola2);

     glEnableClientState(GL_TEXTURE_COORD_ARRAY);
      glTexCoordPointer(2,GL_FLOAT,0,texturas);
      glBindTexture(GL_TEXTURE_2D,texture_id[2]);

        // dibuja un cubo
        glDrawArrays(GL_TRIANGLE_STRIP,0, 30);
       // glDrawArrays(GL_NORMAL_ARRAY_POINTER,0,7);
     glDisableClientState(GL_TEXTURE_COORD_ARRAY);
// desactiva el arreglo de vértices después de dibujar
    glDisableClientState(GL_VERTEX_ARRAY);
glDisableClientState(GL_NORMAL_ARRAY);

}

void turbina(){

glPushMatrix();
glScalef(1.0,1.0,4.0);
MaterialOro();
glutSolidTorus(0.05,0.1,15,30);
glPopMatrix();
}

void Ala(){
ala1();

glPushMatrix();
glTranslatef(0.2,0.1,0.0);
glScalef(2.0,1.5,5.0);
turbina();
glPopMatrix();

glPushMatrix();
glTranslatef(-1.0,0.1,0.0);
glScalef(1.5,1.0,3.5);
turbina();
glPopMatrix();
}


void Torso(){


glPushMatrix();
glTranslatef(-0.3333,0.0,0.0);
glScalef(0.50,0.50,0.50);
miCubo();
glPopMatrix();

glPushMatrix();
glTranslatef(-0.6666,0.0,0.0);
glScalef(0.20,0.50,0.50);
miCubo();
glPopMatrix();

glPushMatrix();
glTranslatef(0.1111,0.0,0.0);
glScalef(0.40,0.50,0.50);
miCubo();
glPopMatrix();



glPushMatrix();
glTranslatef(0.6666,0.0,0.0);
glScalef(0.70,0.50,0.50);
miCubo();
glPopMatrix();
}

void avion(){

glPushMatrix();
glTranslatef(0.0,0.,0.0);
glScalef(0.85,0.40,0.65);
//TexturaEsmeralda();
Torso();
glPopMatrix();

//cola
glPushMatrix();
glTranslatef(0.86,0.06,0.0);
glScalef(0.4,0.44,0.32);
//TexturaEsmeralda();
cola();
glPopMatrix();

//ala derecha
glPushMatrix();
glTranslatef(-0.3,0.0,-0.75);
glScalef(0.40,0.333,0.30);
glRotated(95, 0.0, 1.0, 0.0);
//TexturaEsmeralda();
Ala();
glPopMatrix();

//ala izquierda
glPushMatrix();
glTranslatef(-0.15,0.0,0.75);
glScalef(0.40,0.333,0.30);
glRotated(-95, 0.0, 1.0, 0.0);
//TexturaEsmeralda();
Ala();
glPopMatrix();

//parte delantera
glPushMatrix();
glTranslatef(-0.65,-0.05,0.0);
glScalef(-0.2,-0.35,-0.32);
glRotated(0, 1.0, 10.0, 0.0);
//TexturaCobre();
cola();
glPopMatrix();

//aleta trasera
glPushMatrix();
glTranslatef(1.05,0.32,0.0);
glScalef(0.2,0.3,0.10);
//TexturaCobre();
cola();
glPopMatrix();

//ala atrás derecha
glPushMatrix();
glTranslatef(0.9,0.12,0.35);
glScalef(0.2,0.1,0.5);
glRotatef(22.5,0.0,1.0,0.0);
//TexturaCobre();
cola();
glPopMatrix();

//ala atrás izquierda
glPushMatrix();
glTranslatef(0.9,0.12,-0.35);
glScalef(0.2,0.1,0.5);
glRotatef(-22.5,0.0,1.0,0.0);
//TexturaCobre();
cola();
glPopMatrix();

//base de ruedas

glPushMatrix();
glTranslatef(0.0,-0.18,0.0);
glScalef(0.05,0.075,0.5);
//TexturaOroPulido();
cola();

glPopMatrix();

//llanta derecha

glPushMatrix();
glTranslatef(0.0,-0.27,0.1);
//TexturaCobre();
glutSolidTorus(0.03,0.04,15,30);
glPopMatrix();

//llanta izquierda

glPushMatrix();
glTranslatef(0.0,-0.27,-0.1);
//TexturaCobre();
glutSolidTorus(0.03,0.04,15,30);
glPopMatrix();

//lugar de copiloto
glPushMatrix();
glTranslatef(-0.5,0.15,0.0);
//TexturaBronce();
glutSolidSphere(0.15,30.0,30.0);
glPopMatrix();
}

void display(void)
{
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(30.0f, 1.0f, 1.0f, 10.0f);
	gluLookAt(0.0f, 0.0f, 5.0f,
			  0.0f, 0.0f, 0.0f,
			  0.0f, 1.0f, 0.0f);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glPushMatrix();

		glRotatef(alpha, 1.0f, 0.0f, 0.0f);
		glRotatef(beta, 0.0f, 1.0f, 0.0f);
		glColor3f(1.0f, 0.0f, 0.0f);        
       avion();

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

int main(int argc, char *argv[])
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(800, 800);
	glutInitWindowPosition(415, 90);
	glutCreateWindow("NAVE 3D: Vista en Perspectiva");
	myinit();
	glutDisplayFunc(display);
	//init();
	glutMouseFunc(onMouse);
	glutMotionFunc(onMotion);


	glutMainLoop();
	return 0;

}
