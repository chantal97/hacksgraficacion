#include <GL/glut.h>
#include <stdio.h>
#include <malloc.h>

GLUquadricObj *q;

GLfloat eyeX=2.3, eyeY=2.5, eyeZ=3.0;
//GLfloat eyeX=2.3, eyeY=1.3, eyeZ=2.0;
	//variables globales para la rotación
   float alpha=45, beta=45;

    //variables globales para el cálculo de los grados
	int x0, y0;

GLfloat light_amb[] = {0.4f, 0.5f, 0.6f, 1.0f};
GLfloat light_dif[] = {0.4f, 0.5f, 0.6f, 1.0f};
GLfloat light_spe[] = {0.4f, 0.5f, 0.6f, 1.0f};
GLfloat light_pos[] = {2.0f, 6.0f, 3.0f, 1.0f};

GLfloat light_red_amb[] = {0.9f, 0.1f, 0.1f, 1.0f};
GLfloat light_red_dif[] = {0.8f, 0.1f, 0.1f, 1.0f};
GLfloat light_red_pos[] = {0.0f, 7.0f, 0.0f, 1.0f};

GLfloat gold_Ka[4] = { 0.64725f, 0.5995f, 0.0745f, 1.0f };
GLfloat gold_Kd[4] = { 0.75164f, 0.60648f, 0.22648f, 1.0f };
GLfloat gold_Ks[4] = { 0.628281f, 0.555802f, 0.366065f, 1.0f };
GLfloat gold_Ke = 51.2;

GLfloat ruby_Ka[4]  = { 0.1745f, 0.01175f, 0.01175f, 0.55f };
GLfloat ruby_Kd[4]  = { 0.61424f, 0.04136f, 0.04136f, 0.55f };
GLfloat ruby_Ks[4]  = { 0.727811f, 0.626959f, 0.626959f, 0.55f };
GLfloat ruby_Ke = 76.8;

GLfloat silver_Ka[4]  = { 0.23125f, 0.23125f, 0.23125f, 1.0f };
GLfloat silver_Kd[4]  = { 0.2775f, 0.2775f, 0.2775f, 1.0f };
GLfloat silver_Ks[4]  = { 0.773911f, 0.773911f, 0.773911f, 1.0f };
GLfloat silver_Ke = 51.2;

GLfloat emerald_Ka[4]  = { 0.0215f, 0.1745f, 0.0215f, 0.55f };
GLfloat emerald_Kd[4]  = { 0.07568f, 0.61424f, 0.07568f, 0.55f };
GLfloat emerald_Ks[4]  = { 0.633f, 0.727811f, 0.633f, 0.55f };
GLfloat emerald_Ke = 76.8;

GLfloat bronze_Ka[4]  = { 0.2125f, 0.1275f, 0.054f, 1.0f };
GLfloat bronze_Kd[4]  = { 0.714f, 0.4284f, 0.18144f, 1.0f };
GLfloat bronze_Ks[4]  = { 0.393548f, 0.271906f, 0.166721f, 1.0f };
GLfloat bronze_Ke = 25.6;

GLfloat pearl_Ka[4]  = { 0.95f, 0.90725f, 0.90725f, 0.922f };
GLfloat pearl_Kd[4]  = { 1.0f, 0.829f, 0.829f, 0.922f };
GLfloat pearl_Ks[4]  = { 0.996648f, 0.996648f, 0.996648f, 0.922f };
GLfloat pearl_Ke = 11.264;

GLfloat silverP_Ka[4]  = { 0.23125f, 0.23125f, 0.23125f, 1.0f };
GLfloat silverP_Kd[4]  = { 0.2775f, 0.2775f ,0.2775f , 1.0f };
GLfloat silverP_Ks[4]  = { 0.773911f, 0.773911f, 0.773911f, 0.773911f };
GLfloat silverP_Ke = 89.6;

GLfloat obsidian_Ka[4]  = {0.05375f, 0.05f, 0.06625f, 0.82f };
GLfloat obsidian_Kd[4]  = { 0.18275f, 0.17f ,0.22525f ,0.82f };
GLfloat obsidian_Ks[4]  = { 0.332741f, 0.328634f, 0.346435f, 0.82f };
GLfloat obsidian_Ke = 38.4 ;

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
  //  glTexEnvf ( GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE );
    // Manipulacion en memoria de la textura
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, Width, Height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);

    fclose (fp_archivo);
    free (image);
    return 1;
 }


void init(void)
{
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glLightfv(GL_LIGHT0, GL_AMBIENT, light_amb);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, light_dif);
	glLightfv(GL_LIGHT0, GL_SPECULAR, light_spe);
	glLightfv(GL_LIGHT0, GL_POSITION, light_pos);
	glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
	glShadeModel(GL_SMOOTH);
    glFrontFace(GL_CCW);
	glEnable(GL_NORMALIZE);
    glClearColor(0.1f, 0.2f, 0.4f, 1.0f);
    glEnableClientState(GL_VERTEX_ARRAY);
///PARTE DE LAS TEXTURAS

   // glDisableClientState(GL_TEXTURE_COORD_ARRAY);
   // glDisable(GL_TEXTURE_2D);
}
void drawCube(void)
{
	GLfloat squareFront[] = {-1.0, 1.0, 1.0, -1.0, -1.0, 1.0, 1.0, 1.0, 1.0, 1.0, -1.0, 1.0};
	GLfloat squareBack[] = {1.0, 1.0, -1.0, 1.0, -1.0, -1.0, -1.0, 1.0, -1.0, -1.0, -1.0, -1.0};
	GLfloat squareRight[] = {1.0, 1.0, 1.0, 1.0, -1.0, 1.0, 1.0, 1.0, -1.0, 1.0, -1.0, -1.0};
	GLfloat squareLeft[] = {-1.0, 1.0, -1.0, -1.0, -1.0, -1.0, -1.0, 1.0, 1.0, -1.0, -1.0, 1.0};
	GLfloat squareBottom[] = {-1.0, -1.0, 1.0, -1.0, -1.0, -1.0, 1.0, -1.0, 1.0, 1.0, -1.0, -1.0};
	GLfloat squareTop[] = {1.0, 1.0, 1.0, 1.0, 1.0, -1.0, -1.0, 1.0, 1.0, -1.0, 1.0, -1.0};



	glVertexPointer(3, GL_FLOAT, 0, squareFront);
	glNormal3f(0.0f ,0.0f ,1.0f);
	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);


	glVertexPointer(3, GL_FLOAT, 0, squareBack);
	glNormal3f(0.0f ,0.0f ,-1.0f);
	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);


	glVertexPointer(3, GL_FLOAT, 0, squareRight);
	glNormal3f(1.0f ,0.0f ,0.0f);
	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);


	glVertexPointer(3, GL_FLOAT, 0, squareLeft);
	glNormal3f(-1.0f ,0.0f ,0.0f);
	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);


	glVertexPointer(3, GL_FLOAT, 0, squareBottom);
	glNormal3f(0.0f ,-1.0f ,0.0f);
	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

	glVertexPointer(3, GL_FLOAT, 0, squareTop);
	glNormal3f(0.0f ,1.0f ,0.0f);
	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);


}

void drawCubeT(void)
{
	GLfloat squareFront[] = {-1.0, 1.0, 1.0, -1.0, -1.0, 1.0, 1.0, 1.0, 1.0, 1.0, -1.0, 1.0};
	GLfloat squareBack[] = {1.0, 1.0, -1.0, 1.0, -1.0, -1.0, -1.0, 1.0, -1.0, -1.0, -1.0, -1.0};
	GLfloat squareRight[] = {1.0, 1.0, 1.0, 1.0, -1.0, 1.0, 1.0, 1.0, -1.0, 1.0, -1.0, -1.0};
	GLfloat squareLeft[] = {-1.0, 1.0, -1.0, -1.0, -1.0, -1.0, -1.0, 1.0, 1.0, -1.0, -1.0, 1.0};
	GLfloat squareBottom[] = {-1.0, -1.0, 1.0, -1.0, -1.0, -1.0, 1.0, -1.0, 1.0, 1.0, -1.0, -1.0};
	GLfloat squareTop[] = {1.0, 1.0, 1.0, 1.0, 1.0, -1.0, -1.0, 1.0, 1.0, -1.0, 1.0, -1.0};

    GLfloat squareFrontT[]={0.0,0.0,1.0,0.0,1.0,1.0,0.0,1.0};
    GLfloat squareBackT[]={ 1.0,0.0,1.0,1.0,0.0,1.0,0.0,0.0};
    GLfloat squareRightT[]={0.0,0.0,1.0,0.0,1.0,1.0,0.0,1.0};
    GLfloat squareLeftT[]={1.0,0.0,1.0,1.0,0.0,1.0,0.0,0.0};
    GLfloat squareBottomT[]={0.0,1.0,0.0,0.0,1.0,0.0,1.0,1.0};
    GLfloat squareTopT[]={0.0,0.0,0.0,1.0,1.0,1.0,1.0,0.0};


            glEnable(GL_TEXTURE_2D);//
              glEnableClientState(GL_TEXTURE_COORD_ARRAY);
    glPixelStorei(GL_UNPACK_ALIGNMENT,1);
	glGenTextures(2,texture_id);

     	glBindTexture(GL_TEXTURE_2D,texture_id[0]);
         LoadBMP("tapiz.bmp",0);

	glTexCoordPointer(2,GL_FLOAT,0,squareFrontT);
	glVertexPointer(3, GL_FLOAT, 0, squareFront);
	glNormal3f(0.0f ,0.0f ,1.0f);
   // glBindTexture(GL_TEXTURE_2D,texture_id[0]);
	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);


	glTexCoordPointer(2,GL_FLOAT,0,squareBackT);
	glVertexPointer(3, GL_FLOAT, 0, squareBack);
	glNormal3f(0.0f ,0.0f ,-1.0f);
   // glBindTexture(GL_TEXTURE_2D,texture_id[0]);
	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);


	glTexCoordPointer(2,GL_FLOAT,0, squareRightT);
	glVertexPointer(3, GL_FLOAT, 0, squareRight);
	glNormal3f(1.0f ,0.0f ,0.0f);
 //   glBindTexture(GL_TEXTURE_2D,texture_id[0]);
	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);


	glTexCoordPointer(2,GL_FLOAT,0,squareLeftT);
	glVertexPointer(3, GL_FLOAT, 0, squareLeft);
	glNormal3f(-1.0f ,0.0f ,0.0f);
//	glBindTexture(GL_TEXTURE_2D,texture_id[0]);
	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);


	glTexCoordPointer(2,GL_FLOAT,0,squareBottomT);
	glVertexPointer(3, GL_FLOAT, 0, squareBottom);
	glNormal3f(0.0f ,-1.0f ,0.0f);
    //glBindTexture(GL_TEXTURE_2D,texture_id[0]);
	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);


	glTexCoordPointer(2,GL_FLOAT,0,squareTopT);
	glVertexPointer(3, GL_FLOAT, 0, squareTop);
	glNormal3f(0.0f ,1.0f ,0.0f);
  //  glBindTexture(GL_TEXTURE_2D,texture_id[0]);
	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
    glDisable(GL_TEXTURE_2D);


}

void drawCubeFloor(void)
{
	GLfloat squareFront[] = {-1.0, 1.0, 1.0, -1.0, -1.0, 1.0, 1.0, 1.0, 1.0, 1.0, -1.0, 1.0};
	GLfloat squareBack[] = {1.0, 1.0, -1.0, 1.0, -1.0, -1.0, -1.0, 1.0, -1.0, -1.0, -1.0, -1.0};
	GLfloat squareRight[] = {1.0, 1.0, 1.0, 1.0, -1.0, 1.0, 1.0, 1.0, -1.0, 1.0, -1.0, -1.0};
	GLfloat squareLeft[] = {-1.0, 1.0, -1.0, -1.0, -1.0, -1.0, -1.0, 1.0, 1.0, -1.0, -1.0, 1.0};
	GLfloat squareBottom[] = {-1.0, -1.0, 1.0, -1.0, -1.0, -1.0, 1.0, -1.0, 1.0, 1.0, -1.0, -1.0};
	GLfloat squareTop[] = {1.0, 1.0, 1.0, 1.0, 1.0, -1.0, -1.0, 1.0, 1.0, -1.0, 1.0, -1.0};

    GLfloat squareFrontT[]={0.0,0.0,1.0,0.0,1.0,1.0,0.0,1.0};
    GLfloat squareBackT[]={ 1.0,0.0,1.0,1.0,0.0,1.0,0.0,0.0};
    GLfloat squareRightT[]={0.0,0.0,1.0,0.0,1.0,1.0,0.0,1.0};
    GLfloat squareLeftT[]={1.0,0.0,1.0,1.0,0.0,1.0,0.0,0.0};
    GLfloat squareBottomT[]={0.0,1.0,0.0,0.0,1.0,0.0,1.0,1.0};
    GLfloat squareTopT[]={0.0,0.0,0.0,1.0,1.0,1.0,1.0,0.0};


            glEnable(GL_TEXTURE_2D);//
              glEnableClientState(GL_TEXTURE_COORD_ARRAY);
    glPixelStorei(GL_UNPACK_ALIGNMENT,1);
	glGenTextures(2,texture_id);

     	glBindTexture(GL_TEXTURE_2D,texture_id[1]);
         LoadBMP("maderpiso.bmp",1);

	glTexCoordPointer(2,GL_FLOAT,0,squareFrontT);
	glVertexPointer(3, GL_FLOAT, 0, squareFront);
	glNormal3f(0.0f ,0.0f ,1.0f);
   // glBindTexture(GL_TEXTURE_2D,texture_id[0]);
	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);


	glTexCoordPointer(2,GL_FLOAT,0,squareBackT);
	glVertexPointer(3, GL_FLOAT, 0, squareBack);
	glNormal3f(0.0f ,0.0f ,-1.0f);
   // glBindTexture(GL_TEXTURE_2D,texture_id[0]);
	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);


	glTexCoordPointer(2,GL_FLOAT,0, squareRightT);
	glVertexPointer(3, GL_FLOAT, 0, squareRight);
	glNormal3f(1.0f ,0.0f ,0.0f);
 //   glBindTexture(GL_TEXTURE_2D,texture_id[0]);
	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);


	glTexCoordPointer(2,GL_FLOAT,0,squareLeftT);
	glVertexPointer(3, GL_FLOAT, 0, squareLeft);
	glNormal3f(-1.0f ,0.0f ,0.0f);
//	glBindTexture(GL_TEXTURE_2D,texture_id[0]);
	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);


	glTexCoordPointer(2,GL_FLOAT,0,squareBottomT);
	glVertexPointer(3, GL_FLOAT, 0, squareBottom);
	glNormal3f(0.0f ,-1.0f ,0.0f);
    //glBindTexture(GL_TEXTURE_2D,texture_id[0]);
	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);


	glTexCoordPointer(2,GL_FLOAT,0,squareTopT);
	glVertexPointer(3, GL_FLOAT, 0, squareTop);
	glNormal3f(0.0f ,1.0f ,0.0f);
  //  glBindTexture(GL_TEXTURE_2D,texture_id[0]);
	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
    glDisable(GL_TEXTURE_2D);


}

void drawCubeAlacena(void)
{
	GLfloat squareFront[] = {-1.0, 1.0, 1.0, -1.0, -1.0, 1.0, 1.0, 1.0, 1.0, 1.0, -1.0, 1.0};
	GLfloat squareBack[] = {1.0, 1.0, -1.0, 1.0, -1.0, -1.0, -1.0, 1.0, -1.0, -1.0, -1.0, -1.0};
	GLfloat squareRight[] = {1.0, 1.0, 1.0, 1.0, -1.0, 1.0, 1.0, 1.0, -1.0, 1.0, -1.0, -1.0};
	GLfloat squareLeft[] = {-1.0, 1.0, -1.0, -1.0, -1.0, -1.0, -1.0, 1.0, 1.0, -1.0, -1.0, 1.0};
	GLfloat squareBottom[] = {-1.0, -1.0, 1.0, -1.0, -1.0, -1.0, 1.0, -1.0, 1.0, 1.0, -1.0, -1.0};
	GLfloat squareTop[] = {1.0, 1.0, 1.0, 1.0, 1.0, -1.0, -1.0, 1.0, 1.0, -1.0, 1.0, -1.0};

    GLfloat squareFrontT[]={0.0,0.0,1.0,0.0,1.0,1.0,0.0,1.0};
    GLfloat squareBackT[]={ 1.0,0.0,1.0,1.0,0.0,1.0,0.0,0.0};
    GLfloat squareRightT[]={0.0,0.0,1.0,0.0,1.0,1.0,0.0,1.0};
    GLfloat squareLeftT[]={1.0,0.0,1.0,1.0,0.0,1.0,0.0,0.0};
    GLfloat squareBottomT[]={0.0,1.0,0.0,0.0,1.0,0.0,1.0,1.0};
    GLfloat squareTopT[]={0.0,0.0,0.0,1.0,1.0,1.0,1.0,0.0};


            glEnable(GL_TEXTURE_2D);//
              glEnableClientState(GL_TEXTURE_COORD_ARRAY);
    glPixelStorei(GL_UNPACK_ALIGNMENT,1);
	glGenTextures(2,texture_id);

     	glBindTexture(GL_TEXTURE_2D,texture_id[2]);
         LoadBMP("madera.bmp",2);

	glTexCoordPointer(2,GL_FLOAT,0,squareFrontT);
	glVertexPointer(3, GL_FLOAT, 0, squareFront);
	glNormal3f(0.0f ,0.0f ,1.0f);
   // glBindTexture(GL_TEXTURE_2D,texture_id[0]);
	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);


	glTexCoordPointer(2,GL_FLOAT,0,squareBackT);
	glVertexPointer(3, GL_FLOAT, 0, squareBack);
	glNormal3f(0.0f ,0.0f ,-1.0f);
   // glBindTexture(GL_TEXTURE_2D,texture_id[0]);
	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);


	glTexCoordPointer(2,GL_FLOAT,0, squareRightT);
	glVertexPointer(3, GL_FLOAT, 0, squareRight);
	glNormal3f(1.0f ,0.0f ,0.0f);
 //   glBindTexture(GL_TEXTURE_2D,texture_id[0]);
	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);


	glTexCoordPointer(2,GL_FLOAT,0,squareLeftT);
	glVertexPointer(3, GL_FLOAT, 0, squareLeft);
	glNormal3f(-1.0f ,0.0f ,0.0f);
//	glBindTexture(GL_TEXTURE_2D,texture_id[0]);
	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);


	glTexCoordPointer(2,GL_FLOAT,0,squareBottomT);
	glVertexPointer(3, GL_FLOAT, 0, squareBottom);
	glNormal3f(0.0f ,-1.0f ,0.0f);
    //glBindTexture(GL_TEXTURE_2D,texture_id[0]);
	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);


	glTexCoordPointer(2,GL_FLOAT,0,squareTopT);
	glVertexPointer(3, GL_FLOAT, 0, squareTop);
	glNormal3f(0.0f ,1.0f ,0.0f);
  //  glBindTexture(GL_TEXTURE_2D,texture_id[0]);
	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
    glDisable(GL_TEXTURE_2D);


}
void Piso(){

	glPushMatrix();
	    glTranslatef(0.0,0.045,0.0);
		glScalef(2.5, 0.05, 2.5);
		drawCubeFloor();
	glPopMatrix();

}
void ParedesExteriores(){
	glMaterialfv(GL_FRONT, GL_AMBIENT, pearl_Ka);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, pearl_Kd);
	glMaterialfv(GL_FRONT, GL_SPECULAR, pearl_Ks);
	glMaterialf(GL_FRONT, GL_SHININESS, pearl_Ke);
//pared izquierda
 glPushMatrix();
   glTranslatef(-2.5,0.5,0.0);
   glScalef(0.005,0.5,2.5);
   drawCube();
   glPopMatrix();

//pared frontal
 glPushMatrix();
   glTranslatef(0.0,0.5,2.5);
   glRotatef(90.0,0.0,1.0,0.0);
   glScalef(0.005,0.5,2.5);
   drawCube();
   glPopMatrix();

//pared derecha
 glPushMatrix();
   glTranslatef(2.5,0.5,0.0);
   glScalef(0.005,0.5,2.5);
   drawCube();
   glPopMatrix();

//pared trasera
 glPushMatrix();
   glTranslatef(0.0,0.5,-2.5);
   glRotatef(90.0,0.0,1.0,0.0);
   glScalef(0.005,0.5,2.5);
   drawCube();
   glPopMatrix();
}

void ParedesInteriores(){

//pared izquierda

 glPushMatrix();
   glTranslatef(-2.4,0.5,0.0);
   glScalef(0.10,0.5,2.5);
   drawCubeT();
  glPopMatrix();

//pared frontal
 glPushMatrix();
   glTranslatef(0.0,0.5,2.4);
   glRotatef(90.0,0.0,1.0,0.0);
   glScalef(0.10,0.5,2.5);
   drawCubeT();
   glPopMatrix();

//pared derecha
 glPushMatrix();
   glTranslatef(2.4,0.5,0.0);
   glScalef(0.10,0.5,2.5);
   drawCubeT();
   glPopMatrix();

//pared trasera
 glPushMatrix();
   glTranslatef(0.0,0.5,-2.4);
   glRotatef(90.0,0.0,1.0,0.0);
   glScalef(0.10,0.5,2.5);
   drawCubeT();
   glPopMatrix();

// pared divisora
 glPushMatrix();
   glTranslatef(0.0,0.5,-1.05);
   glScalef(0.10,0.5,1.25);
   drawCubeT();
   glPopMatrix();

}

void silla(){
    glPushMatrix();

	glMaterialfv(GL_FRONT, GL_AMBIENT, bronze_Ka);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, bronze_Kd);
	glMaterialfv(GL_FRONT, GL_SPECULAR, bronze_Ks);
	glMaterialf(GL_FRONT, GL_SHININESS, bronze_Ke);

    glScalef(0.1,0.15,0.1);
    //pata trasera izquierda
    glPushMatrix();
    glTranslatef(-1.0,-1.0,-1.0);
    glScalef(0.2,1.0,0.2);
    drawCube();
    glPopMatrix();
     //pata trasera derecha
    glPushMatrix();
    glTranslatef(1.0,-1.0,-1.0);
    glScalef(0.2,1.0,0.2);
    drawCube();
    glPopMatrix();

     //pata delantera izquierda
    glPushMatrix();
    glTranslatef(-1.0,-1.0,1.0);
    glScalef(0.2,1.0,0.2);
    drawCube();
    glPopMatrix();

     //pata delantera derecha
    glPushMatrix();
    glTranslatef(1.0,-1.0,1.0);
    glScalef(0.2,1.0,0.2);
    drawCube();
    glPopMatrix();

    //asiento
    glPushMatrix();
    glTranslatef(0.0,0.0,0.0);
    glScalef(1.2,0.2,1.2);
    drawCube();
    glPopMatrix();

    //respaldo
    glPushMatrix();
    glTranslatef(0.0,1.0,-1.0);
    glScalef(1.2,1.0,0.2);
    drawCube();
    glPopMatrix();

    glPopMatrix();
}

void mesa(){
    glPushMatrix();

    glRotatef(90.0,0.0,1.0,0.0);
    glScalef(0.2,0.25,0.2);

    	/*glMaterialfv(GL_FRONT, GL_AMBIENT, silver_Ka);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, silver_Kd);
	glMaterialfv(GL_FRONT, GL_SPECULAR, silver_Ks);
	glMaterialf(GL_FRONT, GL_SHININESS, silver_Ke);
	*/
		glMaterialfv(GL_FRONT, GL_AMBIENT, ruby_Ka);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, ruby_Kd);
	glMaterialfv(GL_FRONT, GL_SPECULAR, ruby_Ks);
	glMaterialf(GL_FRONT, GL_SHININESS, ruby_Ke);
  //tabla
  glPushMatrix();
  glScalef(1.0,0.2,1.5);
  drawCube();
  glPopMatrix();

  	glMaterialfv(GL_FRONT, GL_AMBIENT, bronze_Ka);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, bronze_Kd);
	glMaterialfv(GL_FRONT, GL_SPECULAR, bronze_Ks);
	glMaterialf(GL_FRONT, GL_SHININESS, bronze_Ke);
  //pata delantera izq
  glPushMatrix();
  glTranslatef(-0.8,-0.85,1.05);
  glScalef(0.2,0.75,0.2);
  drawCube();
  glPopMatrix();
  //pata delantera derecha
  glPushMatrix();
  glTranslatef(0.8,-0.85,1.05);
  glScalef(0.2,0.75,0.2);
  drawCube();
  glPopMatrix();
  //PATA TRASERA IZQUIERDA
  glPushMatrix();
  glTranslatef(-0.8,-0.85,-1.05);
  glScalef(0.2,0.75,0.2);
  drawCube();
  glPopMatrix();
  //PATA TRASERA DERECHA
  glPushMatrix();
  glTranslatef(0.8,-0.85,-0.85);
  glScalef(0.2,0.75,0.2);
  drawCube();
  glPopMatrix();

  glPopMatrix();
}

void manijas(){

    ///manijas del refrigerador
    	glMaterialfv(GL_FRONT, GL_AMBIENT, silverP_Ka);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, silverP_Kd);
	glMaterialfv(GL_FRONT, GL_SPECULAR, silverP_Ks);
	glMaterialf(GL_FRONT, GL_SHININESS, silverP_Ke);
//barra larga
    glPushMatrix();
    glScalef(0.05,0.15,0.03);
    drawCube();
    glPopMatrix();
//barra corta superior

    glPushMatrix();
    glTranslatef(0.0,0.12,0.06);
    glRotatef(90.0,1.0,0.0,0.0);
    glScalef(0.05,0.03,0.03);
    drawCube();
    glPopMatrix();

//barra corta inferior

    glPushMatrix();
    glTranslatef(0.0,-0.12,0.06);
    glRotatef(90.0,1.0,0.0,0.0);
    glScalef(0.05,0.03,0.03);
    drawCube();
    glPopMatrix();
}

void refrigerador(){
		glMaterialfv(GL_FRONT, GL_AMBIENT, pearl_Ka);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, pearl_Kd);
	glMaterialfv(GL_FRONT, GL_SPECULAR, pearl_Ks);
	glMaterialf(GL_FRONT, GL_SHININESS, pearl_Ke);

    glPushMatrix();
    //parte superior
    glScalef(0.2,0.2,0.2);
    drawCube();
    glPopMatrix();

    glPushMatrix();
    //parteinferior
    glTranslatef(0.0,-0.5,0.0);
    glScalef(0.2,0.5,0.2);
    drawCube();
    glPopMatrix();


    glPushMatrix();
    		glMaterialfv(GL_FRONT, GL_AMBIENT, obsidian_Ka);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, obsidian_Kd);
	glMaterialfv(GL_FRONT, GL_SPECULAR, obsidian_Ks);
	glMaterialf(GL_FRONT, GL_SHININESS, obsidian_Ke);

    glTranslatef(0.0,-0.2,0.0);
    glScalef(0.2,0.02,0.2);
    drawCube();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0.15,0.0,-0.25);
    glScalef(0.5,0.75,0.5);
    manijas();
    glPopMatrix();

        glPushMatrix();
    glTranslatef(0.15,-0.5,-0.25);
    glScalef(0.5,1.5,0.5);
    manijas();
    glPopMatrix();
}

void alacena(){

  glPushMatrix();
  glTranslatef(0.0,0.72,0.1);
  glScalef(0.55,0.62,0.5);
    drawCubeAlacena();
  glPopMatrix();

  glPushMatrix();
  glTranslatef(1.25,0.72,0.1);
  glScalef(0.525,0.62,0.5);
    drawCubeAlacena();
  glPopMatrix();

  glPushMatrix();
  glTranslatef(-1.25,0.72,0.1);
  glScalef(0.525,0.62,0.5);
    drawCubeAlacena();
  glPopMatrix();

    glMaterialfv(GL_FRONT, GL_AMBIENT, obsidian_Ka);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, obsidian_Kd);
	glMaterialfv(GL_FRONT, GL_SPECULAR, obsidian_Ks);
	glMaterialf(GL_FRONT, GL_SHININESS, obsidian_Ke);

glPushMatrix();
glTranslatef(-0.95,0.75,0.65);
//glScalef();
glutSolidSphere(0.09,30.0,30.0);
glPopMatrix();

glPushMatrix();
glTranslatef(0.95,0.75,0.65);
//glScalef();
glutSolidSphere(0.09,30.0,30.0);
glPopMatrix();

    glMaterialfv(GL_FRONT, GL_AMBIENT, bronze_Ka);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, bronze_Kd);
	glMaterialfv(GL_FRONT, GL_SPECULAR, bronze_Ks);
	glMaterialf(GL_FRONT, GL_SHININESS, bronze_Ke);

	///base
	//tabla
glPushMatrix();
glScalef(2.0,0.1,0.5);
    drawCube();
glPopMatrix();

    //pata izquierda
glPushMatrix();
glTranslatef(-1.80,-0.6,0.0);
glScalef(0.1,0.5,0.5);
    drawCube();
glPopMatrix();

    //pata derecha
glPushMatrix();
glTranslatef(1.80,-0.6,0.0);
glScalef(0.1,0.5,0.5);
    drawCube();
glPopMatrix();

//cajones

glPushMatrix();
glTranslatef(-1.9,0.7,0.0);
glScalef(0.1,0.65,0.5);
    drawCube();
glPopMatrix();

glPushMatrix();
glTranslatef(-0.65,0.7,0.0);
glScalef(0.1,0.65,0.5);
    drawCube();
glPopMatrix();

glPushMatrix();
glTranslatef(0.65,0.7,0.0);
glScalef(0.1,0.65,0.5);
    drawCube();
glPopMatrix();
glPushMatrix();

glTranslatef(1.9,0.7,0.0);
glScalef(0.1,0.65,0.5);
    drawCube();
glPopMatrix();

glPushMatrix();
glTranslatef(0.0,1.45,0.0);
glScalef(2.0,0.1,1.0);
    drawCube();
glPopMatrix();
}

void estufa(){

}

void comedor(){

glPushMatrix();
//silla trasera
    glTranslatef(-1.0,0.5,-2.0);
    silla();
glPopMatrix();

glPushMatrix();
//silla delantera
    glTranslatef(-1.0,0.5,-1.2);
    glRotatef(180.0,0.0,1.0,0.0);
    silla();
glPopMatrix();

glPushMatrix();
//silla izquierda
    glTranslatef(-1.5,0.5,-1.6);
    glRotatef(90.0,0.0,1.0,0.0);
    silla();
glPopMatrix();

glPushMatrix();
//silla izquierda
    glTranslatef(-0.5,0.5,-1.6);
    glRotatef(-90.0,0.0,1.0,0.0);
    silla();
glPopMatrix();


glPushMatrix();
    glTranslatef(-1.0,0.5,-1.6);
    mesa();
glPopMatrix();

glPushMatrix();
    glTranslatef(-0.45,1.0,-0.75);
    glRotatef(90.0,0.0,1.0,0.0);
    refrigerador();
glPopMatrix();

glPushMatrix();

///alacena
    glTranslatef(-2.0,0.5,-1.6);
    glRotatef(90.0,0.0,1.0,0.0);
    glScalef(0.35,0.45,0.2);
    alacena();
glPopMatrix();

}

/*void spinDisplay(void)
{
	eyeX = (eyeX - 0.0025f);
	if (eyeX <= -2.3) eyeX = 2.3;

	glutPostRedisplay();
}*/


void displaySolid(void)
{
	// fijar la camara
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	double winHt = 2.0;
	glOrtho(-winHt*64/48.0, winHt*64/48.0, -winHt, winHt, 0.1, 100.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(eyeX, eyeY, eyeZ, 0.0, 0.25, 0.0, 0.0, 1.0, 0.0);

	// Dibujar
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);

	glPushMatrix();

		glRotatef(alpha, 1.0f, 0.0f, 0.0f);
		glRotatef(beta, 0.0f, 1.0f, 0.0f);
		glColor3f(1.0f, 0.0f, 0.0f);

   Piso();
    ParedesExteriores();
     ParedesInteriores();
     comedor();
     //alacena();
    glPopMatrix();
	glFlush();
	//glutSwapBuffers();
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

int main(int argc, char **argv)
{
 glutInit(&argc, argv);
 glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB| GLUT_DEPTH);
 glutInitWindowSize(840, 680);
 glutInitWindowPosition(100, 45);
 glutCreateWindow("Escena 3D");
 glutDisplayFunc(displaySolid);
 init();
 //glutIdleFunc(spinDisplay);
 glViewport(0, 0, 640, 480);
 	glutMouseFunc(onMouse);
	glutMotionFunc(onMotion);
 glutMainLoop();
 return 0;
}
