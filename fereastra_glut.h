#ifndef FEREASTRA_GLUT_H_
#define FEREASTRA_GLUT_H_


/* WINDOWS */
#ifdef _WIN32
#include <windows.h>
#endif

#include <GL/glut.h>
#include "fisier.h"

#define SCREEN_W 1920
#define SCREEN_H 1080

#define WINDOW_W 620
#define WINDOW_H 480

#define ADD_W 620
#define ADD_H 480
#define BACK_W 360
#define BACK_H 480
#define GRAF_W 620
#define GRAF_H 620

#define KEY_ESC 27
#define KEY_UP GLUT_KEY_UP
#define KEY_DOWN GLUT_KEY_DOWN
#define KEY_LEFT GLUT_KEY_LEFT
#define KEY_RIGHT GLUT_KEY_RIGHT

#define SCROLL_SPEED ROW_H
#define REFRESH_MS 33
/* 16...17 -> 60fps, 33...34 -> 30 fps */

#define TOAST_W WINDOW_W
#define TOAST_H WINDOW_H/4

#define HEADER_W ROW_W
#define HEADER_H ROW_H

#define FOOTER_W ROW_W
#define FOOTER_H WINDOW_H/4
#define FOOTERROW_H FOOTER_H/8
#define FOOTERROW_W FOOTER_W/3
#define FOOTERTEXT_XOFFSET 5
#define FOOTERTEXT_YOFFSET FOOTERROW_H/4

#define ROW_W WINDOW_W
#define ROW_H WINDOW_H/32
#define ROWTEXT_XOFFSET 0
#define ROWTEXT_YOFFSET ROW_H/4

#define CLASAMENT_XOFFSET 5
#define NUME_XOFFSET WINDOW_W/15
#define TIMP_XOFFSET WINDOW_W/2.5
#define PRET_XOFFSET WINDOW_W/1.5
#define NOTA_XOFFSET WINDOW_W - 75
#define FAV_XOFFSET WINDOW_W - 20
#define MAX_DISPLAYTEXT_LEN 20

#define ADDROW_H ADD_H/(NR_PARAMETRI+1)
#define ADDTEXT_XOFFSET 5

#define BACKROW_W BACK_W
#define BACKROW_H BACK_H/16
#define BACKTEXT_XOFFSET 5
#define BACKTEXT_YOFFSET BACKROW_H/4
#define BACK_SCROLL_SPEED BACKROW_H

#define GRAF_OFFSETY 20

struct jocrow{
	JOCVIDEO* joc;
	int x, y;
	int width, height;
	int textXOffset, textYOffset;
};
typedef struct jocrow JOCROW;

/* ferestre */
extern int fereastra_main;
extern int fereastra_add;
extern int fereastra_backup;
extern int fereastra_graf;

/* date randuri */
extern NODJOC* lista;
extern JOCROW* table;
extern int count;
extern MONEDA moneda_selectat;

/* scroll randuri */
extern int scrollY;
extern int maxscrollY;
extern int minscrollY;

/* selectie randuri */
extern int index_selectat;

/* toast */
extern char text_toast[50];
extern int visibil;
extern int start;
extern int duration;

/* main */
void drawText(int x, int y, const char* text, int ignore_max_len);
void drawTable(JOCROW rows[], int count);
void drawRow(JOCROW row, int selectat);
void drawToast();
void setToast(const char* text, int timp);
void drawHeader();
void drawFooter();

void makeglut(int* argc, char** argv);
void exit_main();

void display();
void keyboard(unsigned char key, int x, int y);
void special(int key, int x, int y);
void timer(int value);

/* adaugare */
extern JOCVIDEO* input_joc;
extern int index_parametru;
extern char input_text[NR_PARAMETRI][100];

void drawAdaugare();

void makeglut_add();
void exit_add();

void display_add();
void keyboard_add(unsigned char key, int x, int y);
void timer_add(int value);

/* backup */
extern char backup_list[MAX_BACKUPS][100];
extern int backup_count;
extern int index_backup;

extern int backup_scrollY;
extern int backupmax_scrollY;
extern int backupmin_scrollY;

void drawBackups();

void load_backups();
void makeglut_backup();
void exit_backup();

void display_backup();
void keyboard_backup(unsigned char key, int x, int y);
void special_backup(int key, int x, int y);
void timer_backup(int value);

/* grafic */
void drawGraf();

void makeglut_graf();
void exit_graf();

void display_graf();
void keyboard_graf(unsigned char key, int x, int y);
void special_graf(int key, int x, int y);
void timer_graf(int value);

/* diverse */
void formeaza_table(JOCROW* table, NODJOC* lista);


#endif /* FEREASTRA_GLUT_H_ */
