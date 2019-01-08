#include "Objeto.hpp"
#include <vector>
#include <stdio.h>

/**
 * @brief A Classe Fantasma que modela e implementa as funcionalidade do fantasma.  
 * 
 */
class Fantasma
{
public:	
	/**
	 * @brief Construtor da classe fantasma
	 * 
	 * @param x1 Posição na coordenada x do plano do jogo.
	 * @param y2 Posição na coordenada y do plano do jogo.
	 * @param z3 Posição na coordenada z do plano do jogo.
	 * @param raio Raio que indica o tamanho do corpo do corpo do Objeto .
	 * @param alt Altura do corpo do Fantasma.
	 */
	Fantasma(float ,float ,float ,float ,float );
	~Fantasma();
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
    void vertex(double, double, double,float,float,float);
    /**
	 * @brief Função que define os vértices e as normais invertidas em coordenadas esféricas.
	 * 
	 * @param th2 Ângulo Theta calculado para definir os vértices com base em coordenadas esféricas. 
	 * @param ph2 Ângulo Phi calculado para definir os vértices com base em coordenadas esféricas.
	 * @param raio Raio da esfera que será desenhada.
	 * @param xi Posição da esfera na coordenada x.
	 * @param yi Posição da esfera na coordenada y.
	 * @param zi Posição da esfera na coordenada z.
	 */
	void vertex2(double, double, double,float,float,float);
	/**
	 * @brief Função que gerencia o movimento do fantasma.
	 * @brief Soma nas coordenadas x, y, z o tamanho do passo mais um valor que representa o aumento da velocidade.
	 */
	void move();
	/**
	 * @brief Função que desenha o fantasma no jogo.
	 * @brief Essa função usa de conceitos de coordanas cilindricas e esféricas para desenhar o corpo e a cabeça do fantasma respectivamente.
	 * @brief A animação da "saia" do fantasma é feita usando uma função seno com parâmetro variável. 
	 */
	void desenha(bool);
	/**
	 * @brief Função que gerencia as variáveis que realizão a animação dos olhos e da "saia" do fantasma. 
	 * 
	 */
	void animacao();
	/**
	 * @brief Função que informa ao fantasma que ocorreu uma colisão, e ele precisa parar o movimento.
	 * @brief Na colisão o fantasma trava a direção para onde colidiu por um tempo, e define uma direção aleatoria para o próximo movimento. 
	 */
	void stop(int , int);
	/**
	 * @brief A função aleatório gera valores aleatórios que são usados nas tomadas de decisão do fantasma.
	 * @brief As possíveis possibilidades que o fantasma são armezenadas em um vetor e os números aleátorios são gerados com base nesse vetor.
	 * @param a Ajuda na composição da semente que gera o numero aleatório.   
	 * 
	 */
	int aleatorio(int);
	/**
	 * @brief Função que calcula a direção que o fantasma deve seguir, buscando seguir o pacman.
	 * @brief Para seguir o pacman o fantasma busca encurtar a maior distância, em x ou em z, da posição em que se encontra o pacman.
	 * @brief A lógica de perceguissão se inverte se o pacman possuir a função especial, assim a distância é almentada.
	 * @brief A perceguissão só acontece em determinada proximidade entre os dois personagens.
	 * @param px Posição do pacman na coordenada x.
	 * @param pz Posição do pacman na coordenada z.
	 * @param vida Informa se o pacman possui vidas. 
	 * 
	 */
	int praonde(float, float,bool);
	/**
	 * @brief Aumenta a vaiavel que é somada no passo do fantasma, fazendo com que o mesmo aumete a velocidade.
	 * 
	 */
	void aumentanivel();
	/**
	 * @brief Função que verifica se o pacman colidiu com o fantasma.
	 * @brief Se as coordenadas do fantasma mais o seu raio, e as coordenadas do pacman mais o raio, se os valores coincidirem colidiu.    
	 * @param px Coordenada x do pacman.
	 * @param pz Coordenada z do pacman.
	 * @param pt raio do pacman.
	 * @return 0 se não colidiu.
	 * @return 5 se colidiu. 
	 */
    int colisao(float, float, float);
	float tempo=0;
	/**
	 * @brief Conta o tempo que o fantasma fica impossibilitado de escolhar uma direção.
	 * 
	 */
	void conttempo();
	float x , y, z,altura;
	float r;//raio
	int travdir=0,travesq=0,travcima=0,travatras=0;
	

private:

	int rnd = 1; 
	//int direc;
	int direcimag;
	int animabase=0,animaolhos=1;
	glm::vec3 points_base[3];
	glm::vec3 points[3];
	float velocidade = 0.05, velnivel = 0;


private:
	void transform(void);
};