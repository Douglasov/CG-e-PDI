/** @file Fruta.cpp
 * @brief Implementação da classe Fruta. 
*/

x#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "Fruta.hpp"

Fruta::Fruta(float x1, float y1, float z1, float raio, bool t)
{
    x = x1;
    y = y1;
    z = z1;
    r = raio;
    tipo = t;
}

void Fruta::vertex(double th2, double ph2, double raio, float xi, float yi, float zi)
{
    double xd = (raio * sin(th2 * M_PI / 180) * cos(ph2 * M_PI / 180)) + xi;
    double yd = (raio * cos(th2 * M_PI / 180) * cos(ph2 * M_PI / 180)) + yi;
    double zd = (raio * sin(ph2 * M_PI / 180)) + zi;
    glVertex3d(xd, yd, zd);
    glNormal3f(xd, yd, zd);
}

void Fruta::vertex2(double th2, double ph2, double raio, float xi, float yi, float zi)
{
    double xd = (raio * sin(th2 * M_PI / 180) * cos(ph2 * M_PI / 180)) + xi;
    double yd = (raio * cos(th2 * M_PI / 180) * cos(ph2 * M_PI / 180)) + yi;
    double zd = (raio * sin(ph2 * M_PI / 180)) + zi;
    glVertex3d(xd, yd, zd);
    glNormal3f(-xd, -yd, -zd);
}

void Fruta::desenha()
{
    float rho, theta;
    int i, j;
	    
    if (tipo)
        glColor3f(0.0f, 0.0f, 1.0f);
    else
        glColor3f(1.0f, 1.0f, 0.0f);
    int th2, ph2;

		
	//Salva o estado da matriz do modelview
    
    glPushMatrix();
		
	//Efetua o deslocamento na cena para o ponto (x,y,z) 
    
    glTranslatef(x, y, z);
    {
        	
		//Desenha a fruta com uma "triangle strip" de raio ph2
        for (ph2 = -90; ph2 < 90; ph2 += 20)
        {
            glBegin(GL_TRIANGLE_STRIP);
            for (th2 = 0; th2 <= 360; th2 += 20)
            {
                vertex(th2, ph2, r, 0, 0, 0);
                vertex(th2, ph2 + 20, r, 0, 0, 0);
            }
            glEnd();
        }
    }
    glPopMatrix();
}

bool Fruta::colisao(float px, float pz, float pt)
{
	//Detecta a colisao com a fruta considerando seu centro na cena
    if ((px + pt) >= x && (px - pt) <= x && (pz + pt) >= z && (pz - pt) <= z)
        return true;
    else
        return false;
}

Fruta::~Fruta()
{}