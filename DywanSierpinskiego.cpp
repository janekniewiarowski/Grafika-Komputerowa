

#include <windows.h>

#include <gl/gl.h>

#include <gl/glut.h>




// Funkcaja okreœlaj¹ca, co ma byæ rysowane 
// (zawsze wywo³ywana, gdy trzeba przerysowaæ scenê)

typedef GLfloat point2[2];

// funkcja generujaca losowe kolory naszych obiektow
float randomColor()
{
	return ((float)(rand() % 10) + 1) / 10;
}


void dywan(point2 p1, GLfloat bok, int poziom)
{
	int iloscZaglebien = 3;

	if (poziom == iloscZaglebien)
		return;

	for (int i = 1; i < 4; i++)
	{
		for (int j = 1; j < 4; j++)
		{
			if (i % 2 != 0 || j % 2 != 0)
			{
				if (poziom == iloscZaglebien - 1)
				{
					glBegin(GL_POLYGON);
					glColor3f(randomColor(), randomColor(), randomColor());
					glVertex2f(p1[0] + (bok / 3)*(i - 1), p1[1] + (bok / 3)*(j - 1));
					glColor3f(randomColor(), randomColor(), randomColor());
					glVertex2f(p1[0] + (bok / 3)*i, p1[1] + (bok / 3)*(j - 1));
					glColor3f(randomColor(), randomColor(), randomColor());
					glVertex2f(p1[0] + (bok / 3)*i, p1[1] + (bok / 3)*j);
					glColor3f(randomColor(), randomColor(), randomColor());
					glVertex2f(p1[0] + (bok / 3)*(i - 1), p1[1] + (bok / 3)*j);
					glEnd();
				}

				point2 punkt;
				int kolejnyPoziom = poziom + 1;
				int kolejnyBok = (bok / 3);
				punkt[0] = p1[0] + (bok / 3)*(i - 1);
				punkt[1] = p1[1] + (bok / 3)*(j - 1);
				dywan(punkt, kolejnyBok, kolejnyPoziom);
			}

		}
	}

}


void RenderScene(void)

{
	point2 p1;
	p1[0] = -100;
	p1[1] = -100;
	GLfloat bok = 200;
	int poziom = 0;
	dywan(p1, bok, poziom);


	glFlush();
	// Przekazanie poleceñ rysuj¹cych do wykonania

}



// Funkcja ustalaj¹ca stan renderowania




void MyInit(void)

{


	glClearColor(0.5f, 0.5f, 0.5f, 1.0f);
	// Kolor okna wnêtrza okna - ustawiono na szary

}

/*************************************************************************************/

// Funkcja s³u¿¹ca do kontroli zachowania proporcji rysowanych obiektów
// niezale¿nie od rozmiarów okna graficznego



void ChangeSize(GLsizei horizontal, GLsizei vertical)

// Parametry horizontal i vertical (szerokoœæ i wysokoœæ okna) s¹
// przekazywane do funkcji za ka¿dym razem, gdy zmieni siê rozmiar okna

{

	GLfloat AspectRatio;

	// Deklaracja zmiennej AspectRatio okreœlaj¹cej proporcjê wymiarów okna



	if (vertical == 0)
		// Zabezpieczenie pzred dzieleniem przez 0

		vertical = 1;


	glViewport(0, 0, horizontal, vertical);
	// Ustawienie wielkoœciokna okna urz¹dzenia (Viewport)
	// W tym przypadku od (0,0) do (horizontal, vertical)


	glMatrixMode(GL_PROJECTION);
	// Okreœlenie uk³adu wspó³rzêdnych obserwatora

	glLoadIdentity();
	// Okreœlenie przestrzeni ograniczaj¹cej

	AspectRatio = (GLfloat)horizontal / (GLfloat)vertical;
	// Wyznaczenie wspó³czynnika proporcji okna

	// Gdy okno na ekranie nie jest kwadratem wymagane jest 
	// okreœlenie okna obserwatora. 
	// Pozwala to zachowaæ w³aœciwe proporcje rysowanego obiektu
	// Do okreœlenia okna obserwatora s³u¿y funkcja glOrtho(...)



	if (horizontal <= vertical)

		glOrtho(-100.0, 100.0, -100.0 / AspectRatio, 100.0 / AspectRatio, 1.0, -1.0);

	else

		glOrtho(-100.0*AspectRatio, 100.0*AspectRatio, -100.0, 100.0, 1.0, -1.0);

	glMatrixMode(GL_MODELVIEW);
	// Okreœlenie uk³adu wspó³rzêdnych    

	glLoadIdentity();

}

// G³ówny punkt wejœcia programu. Program dzia³a w trybie konsoli



void main(void)

{

	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA);
	// Ustawienie trybu wyœwietlania
	// GLUT_SINGLE - pojedynczy bufor wyœwietlania
	// GLUT_RGBA - model kolorów RGB



	glutCreateWindow("Drugi program w OpenGL");
	// Utworzenie okna i okreœlenie treœci napisu w nag³ówku okna


	glutDisplayFunc(RenderScene);
	// Okreœlenie, ¿e funkcja RenderScene bêdzie funkcj¹ zwrotn¹ (callback)
	// Biblioteka GLUT bêdzie wywo³ywa³a t¹ funkcjê za ka¿dym razem, gdy
	// trzeba bêdzie przerysowaæ okno


	glutReshapeFunc(ChangeSize);
	// Dla aktualnego okna ustala funkcjê zwrotn¹ odpowiedzialn¹ za
	// zmiany rozmiaru okna

	MyInit();
	// Funkcja MyInit (zdefiniowana powy¿ej) wykonuje wszelkie  
	// inicjalizacje konieczneprzed przyst¹pieniem do renderowania


	glutMainLoop();
	// Funkcja uruchamia szkielet biblioteki GLUT

}

