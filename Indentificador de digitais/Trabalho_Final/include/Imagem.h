/**
 * @brief Classe utilizada para o tratamento de imagens
 * 
 * @file Imagem.h
 * @author Douglas Venâncio 
 * Filipe Pena
 * Marco Antonio
 * @date 2018-07-01
 */
#include "opencv2/core/utility.hpp"
#include "opencv2/imgproc.hpp"
#include "opencv2/imgcodecs.hpp"
#include "opencv2/highgui.hpp"
#include <iostream>
#include <string.h>
#include <fstream>

#include "Histograma.h"

using namespace cv;
using namespace std;

/**
 * @brief Classe que implementa uma imagem e as possiveis operações feitas nela
 * 
*/
class imagem
{
    Mat img;
    Mat mascara;
    int linhas, colunas;
    Mat esqueleto;

  public:
      /**
     * @brief Construtor Padrão da classe.
     * 
     * 
     */
    imagem() {}
      /**
     * @brief Construtor Padrão da classe.
     * @param file String que deve conter o caminho que contem uma imagem
     * 
     */
    imagem(String);
      /**
     * @brief Destrutor Padrão da classe.
     * 
     * 
     */
    ~imagem() {}
      /**
     * @brief Função que aplica a transformacao linear na imagem
     * @param I1  Inteiro parametro I1 da transformação linear
     * @param I2  Inteiro parametro I2 da transformação linear
     * @param K1  Inteiro parametro K1 da transformação linear
     * @param K2  Inteiro parametro K2 da transformação linear
     * 
     */
    void transformacao_linear(int, int, int, int);
      /**
     * @brief Função que faz uma mascara para separar a imagem em 2 objetos ou 
     * classes de pixeis dentro da imagem utilizando a transformação linear
     * @param I1  Inteiro parametro I1 da transformação linear
     * @param I2  Inteiro parametro I2 da transformação linear
     * @param K1  Inteiro parametro K1 da transformação linear
     * @param K2  Inteiro parametro K2 da transformação linear
     * 
     */
    void transformacao_linear_mascara(int, int, int, int);
      /**
     * @brief Função que retorna as linhas da imagem
     * @return Retorna um inteiro com as linhas da imagem 
     * 
     */
    int getlinhas();
      /**
     * @brief Função que troca a imagem contida na classe
     * @param file String que deve conter o caminho que contem uma imagem
     * 
     */
    void set(String);
       /**
     * @brief Função que retorna as colunas da imagem
     * @return Retorna um inteiro com as colunas da imagem 
     * 
     */
    int getcolunas();
        /**
     * @brief Função que aumenta a imagem ou seja aumenta os pixels da imagem
     * 
     * 
     */
    void aumenta_imagem();
            /**
     * @brief Função que encontra o maior numero de um vetor
     * @return Retorna um inteiro com maior numero do vetor
     * 
     */
    int maior_vet(vector<float> v);
                /**
     * @brief Função que aplica o filtro de moda na imagem
     * @param kernel_size Inteiro que determina a ordem do kernel que se deseja aplicar o filtro de moda na imagem
     * 
     */
    void moda(int);
                    /**
     * @brief Função que verifica se tem imagem carrega na classe
     * @return Retorna umavariavel bool que retorna true caso tenha uma imagem e false caso não tenha
     * 
     */
    bool temimagem();
    /**
     * @brief Função que retorna a imagem contina na classe
     * @return Retorna uma variavel do tipo Mat que contem a imagem contida na classe
     * 
     */
    Mat getImagem();
        /**
     * @brief Função que aplica o filtro bilateral na imagem com o kernel de ordem 3
     * 
     * 
     */
    void filtrobilateral();
        /**
     * @brief Função que retorna a mascara da imagem contina na classe
     * @return Retorna uma variavel do tipo Mat que contem a mascara da imagem contida na classe
     * 
     */
    Mat getMascara();
    /**
     * @brief Função que aplica a esqueletização na imagem e armazana na classe separadamente
     * 
     * 
     */
    void imagem_skelet();
        /**
     * @brief Função que faz a equalização local da imagem
     * @param a Variavel que defini a amplifcação de contraste
     * 
     */
    void equalizar_clahe(double);
      /**
     * @brief Função que plota imagem contida na imagem na classe
    * @param nome String que passa o nome da janela que ira conter a imagem
     * @param tam Inteiro que passa o tamanho da janela que ira conter a imagem
     * @param move posicao x na tela da janela da imagem
     * @param y posicao y na tela da janela da imagem
     * 
     */
    void plotar(String, int, int, int);
          /**
     * @brief Função que plota a mascara da imagem contida na imagem na classe
     * @param nome String que passa o nome da janela que ira conter a mascara
     * @param tam Inteiro que passa o tamanho da janela que ira conter a mascara
     * @param move posicao x na tela da janela da mascara
     * @param y posicao y na tela da janela da mascara
     * 
     */
    void plotar_mascara(String, int, int, int);
      /**
     * @brief Função que faz a equalização por histograma acumulado da imagem a partir de um histograma
     * mostrando o grafico do histograma acumulado do histograma que foi usado para fazer a equalização
     * @param tam Inteiro que passa o tamanho da janela que ira conter o gráfico do histograma
     * @param move posicao x na tela da janela do histograma
     * @param y posicao y na tela da janela do histograma
     * 
     */
    void transformacao_aculmulado(histograma, int, int, int);
    /**
     * @brief Função que faz o casamento do histograma em uma imagem a partir do histograma de duas imagem mostrando 
     * o grafico do histograma do primero histograma acumulado e do segundo histograma acumulado e invertido  
     * @param tam Inteiro que passa o tamanho da janela que ira conter o gráfico do histogra
     * @param move posicao x na tela da janela do histograma
     * @param y posicao y na tela da janela do histograma
     * 
     */
    void casamento_de_histograma(histograma,histograma, int, int, int);
    /**
     * @brief Função que aplica a transformação linear apenas na parte da imagem, contida dentro da amascara
     * 
     * @param I1  Inteiro parametro I1 da transformação linear
     * @param I2  Inteiro parametro I2 da transformação linear
     * @param K1  Inteiro parametro K1 da transformação linear
     * @param K2  Inteiro parametro K2 da transformação linear
     * 
     */
    void transformacao_mascara(int,int,int,int);
      /**
     * @brief Função que aplica o filtro de bordas de canny na imagem
     * 
     */
    void filtro_canny(int,int,int);

    /**
     * @brief Função que aplica o filtro de mediana na imagem com o kernel de ordem 3 na imagem
     * 
     */
    void filtro_mediana();
    /**
     * @brief Função que aplica o filtro de gabor no angulo de 30, kernel de ordem 3 e frequencia 2 na imagem
     */
    void Filtro_gabor();
    /**
     * @brief Função que aplica uma erosão da imagem com kernel de ordem 3 retangular ou seja de vizinhança 8 
     * 
     */
    void erosao();
    /**
     * @brief Função que aplica uma dilatação da imagem com kernel de ordem 3 retangular ou seja de vizinhança 8 
     * 
     */
    void dilatacao();
        /**
     * @brief Função que aplica limiarização local um kernel de 40
     * 
     */
    void limiarizacaolocal();
      /**
     * @brief Função que aplica limiarização local apenas na região da imagem dentro da mascara
     * 
     * @param maxValue inteiro que significa valor maximo que um pixel tera na binarizacao
     * @param thresholdType inteiro que é a opção do tipo do threshold que se deseja executar
     * @param blockSize inteiro determina a ordem do kernel que sera aplicado na imagem 
     * ou seja o tamanho das areas que sera feito o threshold local 
     * @param C valor subtraido do valor do limiar do threshhold obtido ou seja um ajuste fino
     * 
     */
    void limiarizacaolocalcommascara( double maxValue, int thresholdType, int blockSize, double C);
      /**
     * @brief Função que retorna o esqueleto da imagem
     * @return Retorna uma Variavel Mat com a imagem esqueletizada
     */
    Mat get_esqueleto();
      /**
     * @brief Função utlizada para encontrar o centro das formas para esqueletização e diminuir sua grosura
     * @param im a imagem binaria a ser avaliada e alterada
     * @param iter define se a interação sera a interação sera 0=par ou 1=impar
     */
    void thinningIteration(Mat& im, int iter);
    /**
* @brief Função para skeletizar a imagem
*
* @param  im  uma varivel do tipo Mat que contem uma imagem binaria
*/
    void skeletizar(Mat& im);
      /**
* @brief Função que mostra o esqueleto da imagem contida na classe
     * @param nome String que passa o nome da janela que ira conter a imagem skeletizada
     * @param tam Inteiro que passa o tamanho da janela que ira conter a imagem skeletizada
     * @param move posicao x na tela da janela da imagem skeletizada
     * @param y posicao y na tela da janela da imagem skeletizada
     * 
*/
    void plotar_skelet(String nome, int tam, int move, int y);

          /**
* @brief Função que modifica a imagem da classe
     * 
*/
    void setImagem(String file);
};