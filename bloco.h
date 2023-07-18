//Cria��o dos tipos de bloco
#include <GL/glut.h>
#include <GL/gl.h>
#include <GL/glu.h>

/*
- Detalhamento do Mapa
	- Ch�o: 0
	- Agua: 1
	- Tijolo: 2
	- Metal: 3
	- Arbusto: 4
	- Pista: 5
	- Aguia: 6
	- Parede: 7
*/

// Vertices do objeto
#define N_VERTICES 8
const GLfloat vertices[N_VERTICES][3] = {
    { -0.5, -0.5, -0.5 }, //0
    { -0.5, -0.5,  0.5 }, //1
    {  0.5, -0.5,  0.5 }, //2
    {  0.5, -0.5, -0.5 }, //3
 	{ -0.5,  0.5,  0.5 }, //4
    {  0.5,  0.5,  0.5 }, //5 
    {  0.5,  0.5, -0.5 }, //6
    { -0.5,  0.5, -0.5 }  //7
};

// Faces do objeto (Triangulos)
#define N_FACES 12
const GLuint faces[N_FACES][3] = {
    {0, 4, 7},
    {0, 1, 4},
    {1, 5, 4},
 	{1, 2, 5},
    {2, 6, 5},
    {2, 3, 6},
  	{3, 7, 6},
    {3, 0, 7},
    {7, 5, 6},
 	{7, 4, 5},
	{3, 1, 0},
	{3, 2, 1}
};

// Vetores normais dos vertices do objeto
GLfloat vertex_normals[N_VERTICES][3];

// Vetores normais das faces do objeto
GLfloat face_normals[N_FACES][3];

//Estrutura criada para facilitar o entendimento no calculo das normais
struct vertice{
    float x;
    float y;
    float z;
};
  
void normalizar(vertice * n){
	GLfloat length;
	
	length = (GLfloat) sqrt((n->x * n->x) + (n->y * n->y) + (n->z * n->z));
		
	if (length == 0.0f) length =  1.0f;

	n->x = n->x / length;
	n->y = n->y / length;
	n->z = n->z / length;
}
    
void calcularNormaisFaces(){
    float x[3], y[3], z[3];
    vertice a, b, n;
        
    for(int i = 0; i < N_FACES; i++){
        x[0] = vertices[faces[i][0]][0];
        y[0] = vertices[faces[i][0]][1];
        z[0] = vertices[faces[i][0]][2];
    
        x[1] = vertices[faces[i][1]][0];
        y[1] = vertices[faces[i][1]][1];
        z[1] = vertices[faces[i][1]][2];
    
        x[2] = vertices[faces[i][2]][0];
        y[2] = vertices[faces[i][2]][1];
        z[2] = vertices[faces[i][2]][2];
        
        a.x = x[2]- x[0]; //
        a.y = y[2]- y[0];
        a.z = z[2]- z[0];
        
        b.x = x[2]- x[1];
        b.y = y[2]- y[1];
        b.z = z[2]- z[1];
        
        n.x = a.y * b.z - a.z * b.y;
        n.y = a.z * b.x - a.x * b.z;
        n.z = a.x * b.y - a.y * b.x;
       
        normalizar(&n);
        
        face_normals[i][0] = n.x;
        face_normals[i][1] = n.y;
        face_normals[i][2] = n.z;
    }
}

void calcularNormaisVertices(){
    vertice n;
    for(unsigned int i = 0; i < N_VERTICES; i++){
        n.x = 0.0;
        n.y = 0.0;
        n.z = 0.0;
        for(int j = 0; j < N_FACES; j++){
            if(faces[j][0] == i || faces[j][1] == i || faces[j][2] == i){
                n.x += face_normals[j][0];
                n.y += face_normals[j][1];
                n.z += face_normals[j][2];
            }
        }
        
        n.x /= 3.0;
        n.y /= 3.0;
        n.z /= 3.0;        
        
        normalizar(&n);
        
        vertex_normals[i][0] = n.x;
        vertex_normals[i][1] = n.y;
        vertex_normals[i][2] = n.z;        

    }
    
}


/*
 * Desenha o objeto, triangulo por triangulo, definindo os vetores
 * normais de cada vertice (ideal para usar com Gouraud shading).
 */
void draw_object_smooth(void){
    GLuint i;
    calcularNormaisVertices();
    calcularNormaisFaces();

    // Desenha todos os triangulos do objeto
    glBegin(GL_TRIANGLES);
        for (i=0; i<N_FACES; i++){
            glNormal3fv(vertex_normals[faces[i][0]]);
            glVertex3fv(vertices[faces[i][0]]);

            glNormal3fv(vertex_normals[faces[i][1]]);
            glVertex3fv(vertices[faces[i][1]]);

            glNormal3fv(vertex_normals[faces[i][2]]);
            glVertex3fv(vertices[faces[i][2]]);
        }
    glEnd();
}

/*
 * Desenha o objeto, triangulo por triangulo, utilizando um vetor
 * normal para cada triangulo (ideal para usar com Flat shading).
 */
void draw_object_flat(void){
    GLuint i;
    calcularNormaisVertices();
    calcularNormaisFaces();
    glBegin(GL_TRIANGLES);
        for (i=0; i<N_FACES; i++){
            glNormal3fv(face_normals[i]);
            glVertex3fv(vertices[faces[i][0]]);
            glVertex3fv(vertices[faces[i][1]]);
            glVertex3fv(vertices[faces[i][2]]);
        }
    glEnd();
}


void parede(int i, int j){
	glPushMatrix();
		glColor3f(0.3, 0.3, 0.3);
		glTranslatef (j*1, i*1, 0.5);
		glScalef (1.0, 1.0, 1.0);
		draw_object_smooth();
    glPopMatrix();
}

void tijolo(int i, int j){
	glPushMatrix();
		glColor3f(1.0, 0.5, 0.0);
		glTranslatef (j*1, i*1, 0.5);
		glScalef (1.0, 1.0, 0.8);
		draw_object_smooth();
    glPopMatrix();
}

void metal(int i, int j){
	glPushMatrix();
		glColor3f(0.9, 0.9, 0.9);
		glTranslatef (j*1, i*1, 0.5);
		glScalef (1.0, 1.0, 0.8);
		draw_object_smooth();
    glPopMatrix();
}

void arbusto(int i, int j){
	glPushMatrix();
		glColor3f(0.0, 0.8, 0.0);
		glTranslatef (j*1, i*1, 0.5);
		glScalef (1.0, 1.0, 0.8);
		draw_object_smooth();
    glPopMatrix();
}

//Implementar o mais parecido possivel.
void aguia(int i, int j){
	glPushMatrix();
		glColor3f(0.6, 0.6, 0.6);
		glTranslatef (j*1, i*1, 0.5);
		glScalef (1.0, 1.0, 0.8);
		draw_object_smooth();
    glPopMatrix();
}

void chao(int i, int j){
	glPushMatrix();
		glColor3f(0.1, 0.1, 0.1);
		glTranslatef (j*1, i*1, 0.5);
		glScalef (1.0, 1.0, 0.1);
		draw_object_smooth();
    glPopMatrix();
}

void agua(int i, int j){
	glPushMatrix();
		glColor3f(0.0, 0.1, 1.0);
		glTranslatef (j*1, i*1, 0.5);
		glScalef (1.0, 1.0, 0.1);
		draw_object_smooth();
    glPopMatrix();
}

void gelo(int i, int j){
	glPushMatrix();
		glColor3f(0.3, 0.3, 1.0);
		glTranslatef (j*1, i*1, 0.5);
		glScalef (1.0, 1.0, 0.1);
		draw_object_smooth();
    glPopMatrix();
}