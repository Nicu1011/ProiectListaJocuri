#ifndef FEREASTRA_GLUT_H_
#define FEREASTRA_GLUT_H_


//WINDOWS
#ifdef _WIN32
#include <windows.h>
#endif

#include <GL/glut.h>
#include "fisier.h"

#define WINDOW_W 620
#define WINDOW_H 480
#define ADD_W 480
#define ADD_H 320

#define SCREEN_W 1920
#define SCREEN_H 1080

#define KEY_ESC 27
#define KEY_UP GLUT_KEY_UP
#define KEY_DOWN GLUT_KEY_DOWN

#define SCROLL_SPEED ROW_H
#define REFRESH_MS 33 //16...17 -> 60fps, 33...34 -> 30 fps

#define TOAST_W WINDOW_W
#define TOAST_H ROW_H*4

#define HEADER_W ROW_W
#define HEADER_H ROW_H
#define FOOTER_W ROW_W
#define FOOTER_H ROW_H*4

#define ROW_W WINDOW_W
#define ROW_H WINDOW_H/16

#define TEXT_XOFFSET 0
#define TEXT_YOFFSET ROW_H/4

#define CLASAMENT_XOFFSET 5
#define NUME_XOFFSET WINDOW_W/15
#define TIMP_XOFFSET WINDOW_W/2.5
#define PRET_XOFFSET WINDOW_W/1.5
#define NOTA_XOFFSET WINDOW_W - 75
#define FAV_XOFFSET WINDOW_W - 25
#define MAX_DISPLAYTEXT_LEN WINDOW_W/45

struct button{
	int x, y;
	int width, height;
	char* text;
	int textXOffset, textYOffset;
	int apasat;
};
typedef struct button BUTTON;

struct jocrow{
	JOCVIDEO* joc;
	int x, y;
	int width, height;
	int textXOffset, textYOffset;
};
typedef struct jocrow JOCROW;

void drawText(int x, int y, const char* text, int ignore_max_len);
void drawButton(BUTTON b);
void drawTable(JOCROW rows[], int count);
void drawRow(JOCROW row, int selectat);
void drawToast();
void setToast(const char* text, int timp);
void drawDetails();

void makeglut(int* argc, char** argv);

void display();
void keyboard(unsigned char key, int x, int y);
void special(int key, int x, int y);
void resize(int width, int height);
void timer(int time);

void makeglut_add();

void display_add();
void keyboard_add(unsigned char key, int x, int y);
void resize_add(int width, int height);
void timer_add(int time);

void formeaza_table(JOCROW* table, NODJOC* lista);


#endif /* FEREASTRA_GLUT_H_ */
