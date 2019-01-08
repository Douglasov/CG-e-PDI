/**
 * @brief Classe utilizada para manipulação do histograma
 * 
 * @file Histograma.h
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

using namespace cv;
using namespace std;

/**
 * @brief Classe que implementa o histograma de uma imagem
 * 
 */
class histograma
{
    uint8_t *img_dados;
    int linhas, colunas;
    vector<float> vetor;
    vector<float> aux;
    double maior;
    Mat plot = Mat::zeros(255, 255, CV_8UC3);
    int threshold;

  public:
      /**
     * @brief Construtor Padrão da classe.
     * 
     * 
     */
    histograma() {}
      /**
     * @brief Construtor da classe.
     * @param *d vetor de pixiels de uma imagem
     * @param l inteiro numero de linhas
     * @param c inteiro numero de colunas
     * 
     */
    histograma(uint8_t *, int, int);
      /**
     * @brief destrutor Padrão da classe.
     * 
     * 
     */
    ~histograma() {}
      /**
     * @brief Função que calcula o histograma da imagem
     * 
     * 
     */
    void calcular();
     /**
     * @brief Função que calcula o histograma da imagem apenas na area dentro de uma mascara
     * @param masc Variavel do tipo mat que deve conter a mascara ser usada na funçao
     * 
     */
    void calcularMasc(Mat);
    /**
     * @brief Função que que normaliza e mostra o histograma baseando no maior valor do histograma
     * 
     * 
     */
    void normalizar_mostrar();
    /**
     * @brief Função que que normaliza o histograma baseando no numero de pixels da imagem
     * 
     * 
    */
    void normalizar();
    /**
     * @brief Função que mostra o histograma em forma de grafico
     * @param vermelho Inteiro que passa o valor de R em RGB que influenciara na cor com que o grafico e plotado
     * @param verde Inteiro que passa o valor de G em RGB que influenciara na cor com que o grafico e plotado
     * @param azul Inteiro que passa o valor de B em RGB que influenciara na cor com que o grafico e plotado
     * @param nome String que passa o nome da janela que ira conter o gráfico do histogra
     * @param tam Inteiro que passa o tamanho da janela que ira conter o gráfico do histograma
     * @param move posicao x na tela da janela do histograma
     * @param y posicao y na tela da janela do histograma
     * 
    */
    void plotar(int, int, int, String, int, int, int);
    /**
     * @brief Função que faz o histograma acumulado apenas da imagem dentro da mascara
     * @param masc Variavel do tipo MAT que deve conter a mascara ser usada na funçao
     * 
    */
    void acumulado_masc(Mat);
    /**
     * @brief Função que faz o histograma acumulado da imagem
     * 
     * 
    */
    void acumulado();
    /**
     * @brief Função que faz a tranformção linear do histograma
     * @param I1  Inteiro parametro I1 da transformação linear
     * @param I2  Inteiro parametro I2 da transformação linear
     * @param K1  Inteiro parametro K1 da transformação linear
     * @param K2  Inteiro parametro K2 da transformação linear
     * 
    */
    void linear(int,int,double, double);
    /**
     * @brief Função que retorna o vetor do histograma
     * @return Retorna uma variavel do tipo vector com o histograma
     * 
    */
    vector<float> getvetor();
    /**
     * @brief Função que inverte x e y do histograma de moda a conseguir a operação inversa do histograma para um equalização
     * 
     * 
    */
    void inverter();
        /**
     * @brief Função que encontra o limiar de threshold em uma imagem em escala de cinza a partir do metodo de Otsu
     * @return Retorna uma varivel do tipo int com o limiar calculado
     * 
    */
    int OtsuThreshold();
};