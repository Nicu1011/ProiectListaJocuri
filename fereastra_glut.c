#include "fereastra_glut.h"

BUTON btn = {100, 100, 100, 100, 0};

void display()
{

}

void mouse(int button, int state, int x, int y)
{
	if(button == GLUT_LEFT_BUTTON)
	{
		if(state == GLUT_DOWN)
		{
			if((x <= btn.x + btn.lungime && x >= btn.x) &&
					(y <= btn.y + btn.inaltime && y >= btn.y))
			{
				btn.esteApasat = 1;
			}
		}
	}
	else if(state == GLUT_UP)
	{
		btn.esteApasat = 0;
	}
}

void glut()
{
	glutDisplayFunc(display);
	glutMouseFunc(mouse);
}
