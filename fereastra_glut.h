#ifndef FEREASTRA_GLUT_H_
#define FEREASTRA_GLUT_H_

//WINDOWS
#ifdef _WIN32
#include <windows.h>
#endif

#include <GL/glut.h>

void display();
void mouse(int button, int state, int x, int y);
void glut();

typedef struct{
	int x, y;
	int lungime, inaltime;
	int esteApasat;
} BUTON;



#endif /* FEREASTRA_GLUT_H_ */
