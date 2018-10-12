

#include <windows.h>

#include <gl/gl.h>

#include <gl/glut.h>




// Funkcaja okre�laj�ca, co ma by� rysowane 
// (zawsze wywo�ywana, gdy trzeba przerysowa� scen�)

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
	// Przekazanie polece� rysuj�cych do wykonania

}



// Funkcja ustalaj�ca stan renderowania




void MyInit(void)

{


	glClearColor(0.5f, 0.5f, 0.5f, 1.0f);
	// Kolor okna wn�trza okna - ustawiono na szary

}

/*************************************************************************************/

// Funkcja s�u��ca do kontroli zachowania proporcji rysowanych obiekt�w
// niezale�nie od rozmiar�w okna graficznego



void ChangeSize(GLsizei horizontal, GLsizei vertical)

// Parametry horizontal i vertical (szeroko�� i wysoko�� okna) s�
// przekazywane do funkcji za ka�dym razem, gdy zmieni si� rozmiar okna

{

	GLfloat AspectRatio;

	// Deklaracja zmiennej AspectRatio okre�laj�cej proporcj� wymiar�w okna



	if (vertical == 0)
		// Zabezpieczenie pzred dzieleniem przez 0

		vertical = 1;


	glViewport(0, 0, horizontal, vertical);
	// Ustawienie wielko�ciokna okna urz�dzenia (Viewport)
	// W tym przypadku od (0,0) do (horizontal, vertical)


	glMatrixMode(GL_PROJECTION);
	// Okre�lenie uk�adu wsp�rz�dnych obserwatora

	glLoadIdentity();
	// Okre�lenie przestrzeni ograniczaj�cej

	AspectRatio = (GLfloat)horizontal / (GLfloat)vertical;
	// Wyznaczenie wsp�czynnika proporcji okna

	// Gdy okno na ekranie nie jest kwadratem wymagane jest 
	// okre�lenie okna obserwatora. 
	// Pozwala to zachowa� w�a�ciwe proporcje rysowanego obiektu
	// Do okre�lenia okna obserwatora s�u�y funkcja glOrtho(...)



	if (horizontal <= vertical)

		glOrtho(-100.0, 100.0, -100.0 / AspectRatio, 100.0 / AspectRatio, 1.0, -1.0);

	else

		glOrtho(-100.0*AspectRatio, 100.0*AspectRatio, -100.0, 100.0, 1.0, -1.0);

	glMatrixMode(GL_MODELVIEW);
	// Okre�lenie uk�adu wsp�rz�dnych    

	glLoadIdentity();

}

// G��wny punkt wej�cia programu. Program dzia�a w trybie konsoli



void main(void)

{

	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA);
	// Ustawienie trybu wy�wietlania
	// GLUT_SINGLE - pojedynczy bufor wy�wietlania
	// GLUT_RGBA - model kolor�w RGB



	glutCreateWindow("Drugi program w OpenGL");
	// Utworzenie okna i okre�lenie tre�ci napisu w nag��wku okna


	glutDisplayFunc(RenderScene);
	// Okre�lenie, �e funkcja RenderScene b�dzie funkcj� zwrotn� (callback)
	// Biblioteka GLUT b�dzie wywo�ywa�a t� funkcj� za ka�dym razem, gdy
	// trzeba b�dzie przerysowa� okno


	glutReshapeFunc(ChangeSize);
	// Dla aktualnego okna ustala funkcj� zwrotn� odpowiedzialn� za
	// zmiany rozmiaru okna

	MyInit();
	// Funkcja MyInit (zdefiniowana powy�ej) wykonuje wszelkie  
	// inicjalizacje konieczneprzed przyst�pieniem do renderowania


	glutMainLoop();
	// Funkcja uruchamia szkielet biblioteki GLUT

}

