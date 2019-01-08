#include "Objeto.hpp"

/**
	 * @brief A Classe Fruta implementa a modelagem da fruta e suas funcionalidades
	 */
class Fruta
{
public:	
	Fruta(float x,float y,float z,float r, bool);
	~Fruta();

	/**
	 * @brief Função que define os vértices e as normais em coordenadas esféricas.
	 * 
	 * @param th2 Ângulo Theta calculado para definir os vértices com base em coordenadas esféricas. 
	 * @param ph2 Ângulo Phi calculado para definir os vértices com base em coordenadas esféricas.
	 * @param raio Raio da esfera que será desenhada.
	 * @param xi Posição da esfera na coordenada x.
	 * @param yi Posição da esfera na coordenada y.
	 * @param zi Posição da esfera na coordenada z.
	 */
    void vertex(double th2, double ph2, double raio,float xi,float yi,float zi);
	/**
	 * @brief Função que define os vértices e as normais inversas em coordenadas esféricas.
	 * 
	 * @param th2 Ângulo Theta calculado para definir os vértices com base em coordenadas esféricas. 
	 * @param ph2 Ângulo Phi calculado para definir os vértices com base em coordenadas esféricas.
	 * @param raio Raio da esfera que será desenhada.
	 * @param xi Posição da esfera na coordenada x.
	 * @param yi Posição da esfera na coordenada y.
	 * @param zi Posição da esfera na coordenada z.
	 */
    void vertex2(double th2, double ph2, double raio,float xi,float yi,float zi);
	/**@brief Função responsável pela parte visual da fruta ou seja seu desenho
	*/
	void desenha();
	/**@brief Função por verificar se houve a colisão de algum objeto com a fruta
		 * @param px Posição x do objeto
		 * @param pz Posição z do objeto
		 * @param pt Posição distancia da aresta da hitbox do centro do objeto
		 * @return true se houve a colisão
		 * @return false se não houve a colisão
	*/
	bool colisao(float, float, float);

private:

	float x , y, z;
	float r;//raio
	bool tipo; // false se comida, true se especial
	int direc;
	int direcimag;
	int aux = true;

	glm::vec3 points_base[3];
	glm::vec3 points[3];


private:

	void transform(void);
};