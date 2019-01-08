/** @file Fantasma.cpp
 * @brief Implementação da classe Fantasma. 
*/
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <iostream>
#include <time.h>
#include "Fantasma.hpp"

Fantasma::Fantasma(float x1, float y1, float z1, float raio, float alt)
{
    x = x1;
    y = y1;
    z = z1;
    r = raio;
    altura = alt;
}

void Fantasma::vertex(double th2, double ph2, double raio, float xi, float yi, float zi)
{
    double xd = (raio * sin(th2 * M_PI / 180) * cos(ph2 * M_PI / 180)) + xi;
    double yd = (raio * cos(th2 * M_PI / 180) * cos(ph2 * M_PI / 180)) + yi;
    double zd = (raio * sin(ph2 * M_PI / 180)) + zi;
    glVertex3d(xd, yd, zd);
    glNormal3f(xd, yd, zd);
}

void Fantasma::vertex2(double th2, double ph2, double raio, float xi, float yi, float zi)
{
    double xd = (raio * sin(th2 * M_PI / 180) * cos(ph2 * M_PI / 180)) + xi;
    double yd = (raio * cos(th2 * M_PI / 180) * cos(ph2 * M_PI / 180)) + yi;
    double zd = (raio * sin(ph2 * M_PI / 180)) + zi;
    glVertex3d(xd, yd, zd);
    glNormal3f(-xd, -yd, -zd);
}

void Fantasma::animacao()
{
    
	//valor segundo o tempo para animar a base do fantasma
    
    animabase = int(animabase + (180* M_PI / 180))%360;
    
	//valor segundo o tempo para animar os olhos do fantasma
    
    animaolhos = (animaolhos + 1) % 26;
}

void Fantasma::desenha(bool aux)
{
    double h = altura;

    glColor3f(0.9, 0.9, 0.9);
    
	 //Rotaciona a imagem do fantas para direção que ele esta andando
    
    glPushMatrix();
    if (rnd == 1)
    {
        glTranslatef(x, y, z);
        glRotatef(-90, 0, 1, 0);
        glTranslatef(-x, -y, -z);
        direcimag = 1;
    }
    else if (rnd == 2)
    {
        glTranslatef(x, y, z);
        glRotatef(-270, 0, 1, 0);
        glTranslatef(-x, -y, -z);
        direcimag = 2;
    }

    else if (rnd == 4)
    {
        glTranslatef(x, y, z);
        glRotatef(-180, 0, 1, 0);
        glTranslatef(-x, -y, -z);
        direcimag = 4;
    }

    else if (rnd == 3)
    {
        direcimag = 3;
    }

    else
    {
        if (direcimag == 2)
        {
            glTranslatef(x, y, z);
            glRotatef(-90, 0, 1, 0);
            glTranslatef(-x, -y, -z);
        }

        else if (direcimag == 1)
        {
            glTranslatef(x, y, z);
            glRotatef(-270, 0, 1, 0);
            glTranslatef(-x, -y, -z);
        }

        else if (direcimag == 4)
        {
            glTranslatef(x, y, z);
            glRotatef(-180, 0, 1, 0);
            glTranslatef(-x, -y, -z);
        }
    }

    
	 //movimenta a imagem do fantasma pelo mapa
    
    glTranslatef(x, y, z);


    
	 //Desenho da base do fantasma desenhando o modulo do seno em volta do circulo da base que se movimenta
    
    glCullFace(GL_FRONT);
    glBegin(GL_TRIANGLE_STRIP);
    if (aux)
                glColor3f(1.2, 0, 0);
            else
                glColor3f(0.9, 0.9, 0.9);
    for (int i = 0; i <= 360; i = i + 10)
    {
        glVertex3d((r * cos(i * M_PI / 180)), 0 , (r * sin(i * M_PI / 180)));
        glNormal3d((r * cos(i * M_PI / 180)), 0 , (r * sin(i * M_PI / 180)));
        glVertex3d((r * cos(i * M_PI / 180)) , -abs(( h / 3 * sin(3* i * M_PI / 180 + animabase))) , (r * sin(i * M_PI / 180)));
        glNormal3d((r * cos(i * M_PI / 180)) , 0 , (r * sin(i * M_PI / 180)) );
    }
    glEnd();
    glCullFace(GL_BACK);

    
	 //Desenho de um cilindro que é corpo do fantasma 
    
    for (double j = 0; j < h; j = j + (h / 10))
    {
        glBegin(GL_TRIANGLE_STRIP);
        for (double i = 0; i <= 360; i = i + 10)
        {
            //corpo
            if (aux)
                glColor3f(1.2, 0, 0);
            else
                glColor3f(0.9, 0.9, 0.9);
            glVertex3d((r * cos(i * M_PI / 180)) , j , (r * sin(i * M_PI / 180)) );
            glNormal3d((r * cos(i * M_PI / 180)) , 0 , (r * sin(i * M_PI / 180)) );
            glVertex3d((r * cos(i * M_PI / 180)) , j + h / 10 , (r * sin(i * M_PI / 180)) );
            glNormal3d((r * cos(i * M_PI / 180)) , 0 , (r * sin(i * M_PI / 180)) );
        }
        glEnd();
    }

    
	 //Animação dos olhos troca de cor
    

    if (animaolhos < 13)
    {
        glColor3f(1, 0, 0);
    }
    else
    {
        glColor3f(0, 0, 1);
    }

    
	 //desenho dos olhos do fantasma utilizando esferas
    
    double heye = (8 * h / 10);
    double angeye = 330;

    for (double ph2 = -90; ph2 < 90; ph2 += 10)
    {
        glBegin(GL_TRIANGLE_STRIP);
        for (double th2 = 0; th2 <= 360; th2 += 10)
        {
            vertex(th2, ph2, r / 4, (r * 0.9 * cos(angeye * M_PI / 180)) ,  heye, (r * 0.9 * sin(angeye * M_PI / 180)) );
            vertex(th2, ph2 + 10, r / 4, (r * 0.9 * cos(angeye * M_PI / 180)) ,  heye, (r * 0.9 * sin(angeye * M_PI / 180)) );
        }
        glEnd();
    }

    angeye = 30;

    for (double ph2 = -90; ph2 < 90; ph2 += 10)
    {
        glBegin(GL_TRIANGLE_STRIP);
        for (double th2 = 0; th2 <= 360; th2 += 10)
        {
            vertex(th2, ph2, r / 4, (r * 0.9 * cos(angeye * M_PI / 180)) ,  heye, (r * 0.9 * sin(angeye * M_PI / 180)) );
            vertex(th2, ph2 + 10, r / 4, (r * 0.9 * cos(angeye * M_PI / 180)) ,  heye, (r * 0.9 * sin(angeye * M_PI / 180)) );
        }
        glEnd();
    }

    
	 //desenho da cabeça do fantasma utilizando metade de uma esfera
    
    glPushMatrix();
    glTranslatef(0, h, 0);
    if (aux)
                glColor3f(1.2, 0, 0);
            else
                glColor3f(0.9, 0.9, 0.9);
    for (double ph2 = -90; ph2 < 90; ph2 += 10)
    {
        glBegin(GL_TRIANGLE_STRIP);
        for (double th2 = -90; th2 <= 90; th2 += 10)
        {
            vertex(th2, ph2, r, 0, 0 , 0);
            vertex(th2, ph2 + 10, r, 0, 0 , 0);
        }
        glEnd();
    }
    glPopMatrix();

    //
    glPopMatrix();
}
int Fantasma::aleatorio(int a)
{
    
	 //trava de direção movimentação do fantasma qunado há uma colisão
    
    std::vector<int> vec;
    if (travdir == 0)
        vec.push_back(1);
    if (travesq == 0)
        vec.push_back(2);
    if (travcima == 0)
        vec.push_back(3);
    if (travatras == 0)
        vec.push_back(4);

    
	 //calculo de direção aleatoria da movimentação do fantasma
    
    if(vec.size()!=0)
    {
    srand(time(NULL) + a);
    rnd = vec[(rand() % vec.size())];
    }
    vec.clear();
}


int Fantasma::praonde(float px, float pz, bool vida)
{
    
	 //calculo da IA do fantasma para movimentação no eixo x caso o pacman esta em uma distancia de 15 no eixo x do fantasma
    
    
    if (abs(px - x) > abs(pz - z) && abs(px - x) < 15)
    {
        
	    //caso o pacman não tenha vida o fantasma se movimenta no eixo x seguindo o pacman 
        
        if (!vida)
        {
            velocidade = 0.05;
            if ((px - x) > 0)
            {
                if(travcima==0)
                rnd = 3;
            }
            else
            {
                if(travatras==0)
                rnd = 4;
            }
        }
        
	    //caso o pacman tenha vida o fantasma se movimenta no eixo x fugindo do pacman
        
        else
        {
            velocidade = 0.08;
            if ((px - x) > 0)
            {   
                if(travatras==0)
                {
                travcima=1;  
                rnd = 4;
                }
            }
            else
            {
                if(travcima==0)
                {
                travatras=1;    
                rnd = 3;
                }
            }
        }
    }
    
	 //calculo da IA do fantasma para movimentação no eixo y caso o pacman esta em uma distancia de 15 no eixo y do fantasma
    
    else if (!(abs(px - x) >= abs(pz - z)) && abs(pz - z) < 15)
    {
        
	    //caso o pacman não tenha vida o fantasma se movimenta no eixo y seguindo o pacman 
        
        if (!vida)
        {
            
            velocidade = 0.05;
            if ((pz - z) > 0)
            
            {
                
                if(travdir==0)
                rnd = 1;
            }
                
            else
            {
                if(travesq==0)
                rnd = 2;
            }
        }
        
	    //caso o pacman tenha vida o fantasma se movimenta no eixo x fugindo do pacman
        
        else
        {
            velocidade = 0.08;
            if ((pz - z) > 0)
            {
                if(travesq==0)
                {
                travdir=1;
                rnd = 2;
                }
            }
            else
            {
                if(travdir==0)
                {
                travesq=1;    
                rnd = 1;
                }
            }
        }
    }
}

void Fantasma::move()
{
    
	//move o fantasma para a baixo
    
    if (rnd == 2)
    {
        z = z - (velocidade + velnivel);
    }
    
	//move o fantasma para a cima
    
    else if (rnd == 1)
    {
        z = z + (velocidade + velnivel);
    }
    
	//move o fantasma para a esquerda
    
    else if (rnd == 4)
    {
        x = x - (velocidade + velnivel);
    }
    
	//move o fantasma para a direita
    
    else if (rnd == 3)
    {
        x = x + (velocidade + velnivel);
    }
}

void Fantasma::aumentanivel()
{
    velnivel = velnivel + 0.05;
}


void Fantasma::stop(int bateu, int aux)
{
    
	//caso o fantasma colida com uma parede acima dele faz com que ele retorne uma
    //quantia insignificante para na direção contraria da colisão, ativa a trava de movimentação para cima e calcula
    //uma direção de movimentação aleatoria
    
    if (bateu == 1)
    {
        travcima = 1;
        x = x - 0.1;
        aleatorio(aux);
    }

        
	//caso o fantasma colida com uma parede abaixo dele faz com que ele retorne uma
    //quantia insignificante para na direção contraria da colisão, ativa a trava de movimentação para baixo e calcula
    //uma direção de movimentação aleatoria
    
    if (bateu == 2)
    {
        travatras = 1;
        x = x + 0.1;
        aleatorio(aux);
    }

        
	//caso o fantasma colida com uma parede a direita dele faz com que ele retorne uma
    //quantia insignificante para na direção contraria da colisão, ativa a trava de movimentação para direita e calcula
    //uma direção de movimentação aleatoria
    
    if (bateu == 3)
    {
        travdir = 1;
        z = z - 0.1;
        aleatorio(aux);
    }

    
	//caso o fantasma colida com uma parede esquerda dele faz com que ele retorne uma
    //quantia insignificante para na direção contraria da colisão, ativa a trava de movimentação para esquerda e calcula
    //uma direção de movimentação aleatoria
    
    if (bateu == 4)
    {
        travesq = 1;
        z = z + 0.1;
        aleatorio(aux);
    }
}

void Fantasma::conttempo()
{


    tempo=tempo+0.01;
    if (tempo > 300)
    {
        tempo = 0;
        travdir = 0;
        travesq = 0;
        travcima = 0;
        travatras = 0;
    }
}

int Fantasma::colisao(float px, float pz, float pt)
{
    if ((px + pt) >= x && (px - pt) <= x && (pz + pt) >= z && (pz - pt) <= z)
    {
        return 5;
    }
    else
        return 0;
}
Fantasma::~Fantasma()
{
}