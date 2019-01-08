/**
 * @brief Aquivo que implementa os metodos referentes a uma estrutura de objeto dedo.
 * 
 * @file Dedo.h
 * @author Douglas Venâncio 
 * Filipe Pena
 * Marco Antonio
 * @date 2018-07-01
 */
#include "opencv2/opencv.hpp"
#include <fstream>
#include <iostream>
#include "Imagem.h"

using namespace std;
using namespace cv;

/**
 * @brief Classe que implementa o objeto dedo, objeto esse que
 * possui a imagem do dedo, o nome do dono do dedo e outros parâmeros. 
 * 
 */

class dedo
{
private:
  imagem img;
  Mat descritor;
  vector<KeyPoint> keypoints;
  string nome;
  int limiar = 10000;

public:
  /**
 * @brief Construtor padrão da classe dedo.
 * 
 */
  dedo() {}
  /**
 * @brief Construtor com parâmetro da classe dedo.
 * 
 * @param im Parâmetro referente a um objeto imagem.  
 */
  dedo(imagem im);
  /**
 * @brief Função que adiciona uma imagem para um opbjeto dedo
 * 
 * @param im Objeto referente a uma imagem.
 * 
 */
  void set(imagem);
  /**
   * @brief Pega o descritor de um objeto dedo.
   * 
   * @return Mat Retorna a matriz que possui esse descritor.
   */
  Mat get_descritor();
  /**
   * @brief Computa os pontos chaves e gera os descritores.
   * 
   */
  void caracterizar();
  /**
   * @brief Exibe a imagem referente ao objeto dedo.
   * 
   */
  void mostrar_dedo();
  /**
   * @brief Método que retorna o nome do individuo dono do dedo.
   * 
   * @return Nome do individuo.
   */
  string get_nome();
  /**
   * @brief Adiociona a um objeto o nome do individuo.
   * 
   * @param n string com o um nome.
   * 
   */
  void set_nome(string);
  /**
   * @brief Método que exibe o nome do individuo.
   * 
   */
  void mostrar_nome();
  /**
   * @brief Método que detecta as minúcias de uma impressão digital.
   * 
   */
  void detectar_corner();
  /**
   * @brief Retorna o parametro limiar.
   * 
   * @return Valor que pode ser usado como limiar para o resultado. 
   */
  int get_limiar();
  /**
   * @brief Limpa alguns parametros do objeto dedo.
   * 
   */
  void limpar_dedo();
};