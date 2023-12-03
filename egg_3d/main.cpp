/*************************************************************************************/

//  Szkielet programu do tworzenia modelu sceny 3-D z wizualizacj� osi 
//  uk�adu wsp�rzednych

/*************************************************************************************/

#include <windows.h>
#include <gl/gl.h>
#include <gl/glut.h>
#include <math.h>
#include "main.h"
#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

const double pi = 3.14159265358979323846;

typedef float point3[3];

int N = 20; // Ilo�� przedzia��w boku kwadratu

int model = 1;  // 1- punkty, 2- siatka, 3 - wype�nione tr�jk�ty

static GLfloat theta[] = { 0.0, 0.0, 0.0 }; // trzy k�ty obrotu

/*************************************************************************************/

// Funkcja obliczaj�ca wsp�rz�dne powierzchni opisanej r�wnaniami parametrycznymi

float calculate(char xyz, float u, float v)
{
    float result;

    if (u >= 0 && u <= 1 && v >= 0 && v <= 1)
    {
        // x(u, v)
        if (xyz == 'x')
        {
            result = (-90.0 * powf(u, 5) + 225.0 * powf(u, 4) - 270.0 * powf(u, 3) + 180.0 * powf(u, 2) - 45.0 * u) * cos(float(pi) * v);
        }
        // y(u, v)
        else if (xyz == 'y')
        {
            result = (160.0 * powf(u, 4) - 320.0 * powf(u, 3) + 160 * powf(u, 2));
        }
        // z(u, v)
        else if (xyz == 'z')
        {
            result = (-90.0 * powf(u, 5) + 225.0 * powf(u, 4) - 270.0 * powf(u, 3) + 180.0 * powf(u, 2) - 45.0 * u) * sin(float(pi) * v);
        }

        return result;
    }

    return NULL;
}

/*************************************************************************************/

// Funkcja rysuj�ca chmur� punkt�w

void model_1(void)
{
    point3* points;
    points = new point3[N*N];

    float u, v;

    glBegin(GL_POINTS);

    for (int i = 0; i < N; i++)
    {
        u = (1.0 / N) * (i + 1);

        for (int j = 0; j < N; j++)
        {
            v = (1.0 / N) * (j + 1);

            points[(N * i) + j][0] = { calculate('x', u, v) };
            points[(N * i) + j][1] = { calculate('y', u, v) };
            points[(N * i) + j][2] = { calculate('z', u, v) };

            glVertex3fv(points[(N * i) + j]);
        }
    }

    glEnd();

    delete[] points;
}

/*************************************************************************************/

// Funkcja rysuj�ca siatk� punkt�w

void model_2(void)
{
    float u, v;
    glBegin(GL_LINES);

    // Rysowanie siatki jajka
    for (int i = 0; i < N - 1; i++)
    {
        for (int j = 0; j < N - 1; j++)
        {
            // Pionowe linie siatki
            glVertex3f(calculate('x', (1.0 / (N - 1)) * i, (1.0 / (N - 1)) * j),
                calculate('y', (1.0 / (N - 1)) * i, (1.0 / (N - 1)) * j),
                calculate('z', (1.0 / (N - 1)) * i, (1.0 / (N - 1)) * j));

            glVertex3f(calculate('x', (1.0 / (N - 1)) * (i + 1), (1.0 / (N - 1)) * j),
                calculate('y', (1.0 / (N - 1)) * (i + 1), (1.0 / (N - 1)) * j),
                calculate('z', (1.0 / (N - 1)) * (i + 1), (1.0 / (N - 1)) * j));

            // Poziome linie siatki
            glVertex3f(calculate('x', (1.0 / (N - 1)) * i, (1.0 / (N - 1)) * j),
                calculate('y', (1.0 / (N - 1)) * i, (1.0 / (N - 1)) * j),
                calculate('z', (1.0 / (N - 1)) * i, (1.0 / (N - 1)) * j));

            glVertex3f(calculate('x', (1.0 / (N - 1)) * i, (1.0 / (N - 1)) * (j + 1)),
                calculate('y', (1.0 / (N - 1)) * i, (1.0 / (N - 1)) * (j + 1)),
                calculate('z', (1.0 / (N - 1)) * i, (1.0 / (N - 1)) * (j + 1)));
        }
    }

    glEnd();
}

/*************************************************************************************/

// Funkcja rysuj�ca obiekt w postaci wype�nionych tr�jk�t�w

void model_3(void)
{
    // Inicjalizacja generatora liczb pseudolosowych
    srand(static_cast<unsigned int>(time(nullptr)));

    glBegin(GL_TRIANGLES);

    // Rysowanie tr�jk�t�w jajka
    for (int i = 0; i < N - 1; i++)
    {
        for (int j = 0; j < N - 1; j++)
        {
            float u0 = (1.0 / (N - 1)) * i;
            float v0 = (1.0 / (N - 1)) * j;

            float u1 = (1.0 / (N - 1)) * (i + 1);
            float v1 = (1.0 / (N - 1)) * j;

            float u2 = (1.0 / (N - 1)) * i;
            float v2 = (1.0 / (N - 1)) * (j + 1);

            float u3 = (1.0 / (N - 1)) * (i + 1);
            float v3 = (1.0 / (N - 1)) * (j + 1);

            // Losowy kolor
            glColor3f(static_cast<float>(rand()) / RAND_MAX,
                static_cast<float>(rand()) / RAND_MAX,
                static_cast<float>(rand()) / RAND_MAX);

            // Pierwszy tr�jk�t
            glVertex3f(calculate('x', u0, v0), calculate('y', u0, v0), calculate('z', u0, v0));
            glVertex3f(calculate('x', u1, v1), calculate('y', u1, v1), calculate('z', u1, v1));
            glVertex3f(calculate('x', u2, v2), calculate('y', u2, v2), calculate('z', u2, v2));

            // Losowy kolor
            glColor3f(static_cast<float>(rand()) / RAND_MAX,
                static_cast<float>(rand()) / RAND_MAX,
                static_cast<float>(rand()) / RAND_MAX);

            // Drugi tr�jk�t
            glVertex3f(calculate('x', u1, v1), calculate('y', u1, v1), calculate('z', u1, v1));
            glVertex3f(calculate('x', u3, v3), calculate('y', u3, v3), calculate('z', u3, v3));
            glVertex3f(calculate('x', u2, v2), calculate('y', u2, v2), calculate('z', u2, v2));
        }
    }

    glEnd();
}

/*************************************************************************************/

// Funkcja obracaj�ca jajko

void spinEgg()
{

    theta[0] -= 0.5;
    if (theta[0] > 360.0) theta[0] -= 360.0;

    theta[1] -= 0.5;
    if (theta[1] > 360.0) theta[1] -= 360.0;

    theta[2] -= 0.5;
    if (theta[2] > 360.0) theta[2] -= 360.0;

    glutPostRedisplay(); // Od�wie�enie zawarto�ci aktualnego okna
}


/*************************************************************************************/

// Funkcja rysuj�ca osie uk�adu wsp�rz�dnych



void Axes(void)
{

    point3  x_min = { -5.0, 0.0, 0.0 };
    point3  x_max = { 5.0, 0.0, 0.0 };
    // pocz�tek i koniec obrazu osi x

    point3  y_min = { 0.0, -5.0, 0.0 };
    point3  y_max = { 0.0,  5.0, 0.0 };
    // pocz�tek i koniec obrazu osi y

    point3  z_min = { 0.0, 0.0, -5.0 };
    point3  z_max = { 0.0, 0.0,  5.0 };
    //  pocz�tek i koniec obrazu osi y
    glColor3f(1.0f, 0.0f, 0.0f);  // kolor rysowania osi - czerwony
    glBegin(GL_LINES); // rysowanie osi x
    glVertex3fv(x_min);
    glVertex3fv(x_max);
    glEnd();

    glColor3f(0.0f, 1.0f, 0.0f);  // kolor rysowania - zielony
    glBegin(GL_LINES);  // rysowanie osi y

    glVertex3fv(y_min);
    glVertex3fv(y_max);
    glEnd();

    glColor3f(0.0f, 0.0f, 1.0f);  // kolor rysowania - niebieski
    glBegin(GL_LINES); // rysowanie osi z

    glVertex3fv(z_min);
    glVertex3fv(z_max);
    glEnd();

}

/*************************************************************************************/

// Funkcja okre�laj�ca co ma by� rysowane (zawsze wywo�ywana gdy trzeba
// przerysowa� scen�)



void RenderScene(void)
{

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    // Czyszczenie okna aktualnym kolorem czyszcz�cym

    glLoadIdentity();
    // Czyszczenie macierzy bie��cej
    Axes();
    // Narysowanie osi przy pomocy funkcji zdefiniowanej wy�ej
    glColor3f(0.0f, 1.0f, 0.0f); 
    // Ustawienie koloru rysowania na bia�y
    glRotatef(theta[0], 1.0, 0.0, 0.0);

    glRotatef(theta[1], 0.0, 1.0, 0.0);

    glRotatef(theta[2], 0.0, 0.0, 1.0);

    glTranslatef(0.0f, -4.0f, 0.0f);
    // Przesuni�cie obiektu wzgl�dem osi Y 
    glRotatef(30.0f, 1.0f, 0.0f, 0.0f);  
    // Obr�t o 30 stopni

    // Rysowanie modeli
    if (model == 1)
    {
        model_1();
        // Rysowanie chmury punkt�w
    }
    if (model == 2)
    {
        model_2();
        // Rysowanie siatki punkt�w
    }
    if (model == 3)
    {
        model_3();
        // Rysowanie jajka z�o�onego z kolorowych tr�jk�t�w
    }
    
    glFlush();
    // Przekazanie polece� rysuj�cych do wykonania


    glutSwapBuffers();
    //
}

/*************************************************************************************/

// Funkcja ustalaj�ca stan renderowania



void MyInit(void)
{

    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    // Kolor czyszc�cy (wype�nienia okna) ustawiono na czarny

}

/*************************************************************************************/

// Funkcja ma za zadanie utrzymanie sta�ych proporcji rysowanych
// w przypadku zmiany rozmiar�w okna.
// Parametry vertical i horizontal (wysoko�� i szeroko�� okna) s�
// przekazywane do funkcji za ka�dym razem gdy zmieni si� rozmiar okna.



void ChangeSize(GLsizei horizontal, GLsizei vertical)
{

    GLfloat AspectRatio;
    // Deklaracja zmiennej AspectRatio  okre�laj�cej proporcj�
    // wymiar�w okna 
    if (vertical == 0)  // Zabezpieczenie przed dzieleniem przez 0
        vertical = 1;
    glViewport(0, 0, horizontal, vertical);
    // Ustawienie wielko�ciokna okna widoku (viewport)
    // W tym przypadku od (0,0) do (horizontal, vertical)  
    glMatrixMode(GL_PROJECTION);
    // Prze��czenie macierzy bie��cej na macierz projekcji 
    glLoadIdentity();
    // Czyszcznie macierzy bie��cej            
    AspectRatio = (GLfloat)horizontal / (GLfloat)vertical;
    // Wyznaczenie wsp�czynnika  proporcji okna
    // Gdy okno nie jest kwadratem wymagane jest okre�lenie tak zwanej
    // przestrzeni ograniczaj�cej pozwalaj�cej zachowa� w�a�ciwe
    // proporcje rysowanego obiektu.
    // Do okreslenia przestrzeni ograniczj�cej s�u�y funkcja
    // glOrtho(...)            
    if (horizontal <= vertical)

        glOrtho(-7.5, 7.5, -7.5 / AspectRatio, 7.5 / AspectRatio, 10.0, -10.0);
    else

        glOrtho(-7.5 * AspectRatio, 7.5 * AspectRatio, -7.5, 7.5, 10.0, -10.0);
    glMatrixMode(GL_MODELVIEW);
    // Prze��czenie macierzy bie��cej na macierz widoku modelu                                   

    glLoadIdentity();
    // Czyszcenie macierzy bie��cej
}

/*************************************************************************************/

// Funkcja obs�uguj�ca klawisze klawiatury
void keys(unsigned char key, int x, int y)
{
    if (key == 'q') model = 1;
    if (key == 'w') model = 2;
    if (key == 'e') model = 3;

    RenderScene(); // przerysowanie obrazu sceny
}

/*************************************************************************************/

// G��wny punkt wej�cia programu. Program dzia�a w trybie konsoli



void main(int argc, char** argv)
{
    glutInit(&argc, argv);

    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);

    glutInitWindowSize(300, 300);

    glutCreateWindow("Uk�ad wsp�rz�dnych 3-D");

    cout << "Model 1 (Chmura punktow): q" << endl;
    cout << "Model 2 (Siatka punktow): w" << endl;
    cout << "Model 3 (Kolorowe trojkaty): e" << endl;

    glutKeyboardFunc(keys);
    // W��czenie obs�ugi zdarze� klawiatury
    glutDisplayFunc(RenderScene);
    // Okre�lenie, �e funkcja RenderScene b�dzie funkcj� zwrotn�
    // (callback function).  Bedzie ona wywo�ywana za ka�dym razem
    // gdy zajdzie potrzba przeryswania okna 
    glutReshapeFunc(ChangeSize);
    // Dla aktualnego okna ustala funkcj� zwrotn� odpowiedzialn�
    // zazmiany rozmiaru okna      
    MyInit();
    // Funkcja MyInit() (zdefiniowana powy�ej) wykonuje wszelkie
    // inicjalizacje konieczne  przed przyst�pieniem do renderowania
    glEnable(GL_DEPTH_TEST);
    // W��czenie mechanizmu usuwania powierzchni niewidocznych
    glutIdleFunc(spinEgg);
    // W��czenie obracania si� jajka
    glutMainLoop();
    // Funkcja uruchamia szkielet biblioteki GLUT
}

/*************************************************************************************/