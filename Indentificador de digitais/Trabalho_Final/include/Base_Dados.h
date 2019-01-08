/**
 * @brief A base de dados é uma estrutura que armazena algumas impressões digitais em uma estrurura.
 * 
 * @file Base_Dados.h
 * @author Douglas Venâncio 
 * Filipe Pena
 * Marco Antonio
 * @date 2018-07-01
 */
#include "Dedo.h"
#include "opencv2/opencv.hpp"
#include <fstream>
#include <iostream>

using namespace std;
using namespace cv;
/**
 * @brief Classe que implementa um objeto que é a base de dados que guarda informações sobre diversas impressões digitais.
 * 
 */
class base
{
    private:
    vector<dedo> bd;
    vector<float> result;

    public:
    /**
     * @brief Construtor Padrão da classe.
     * 
     */
    base(){}
    /**
     * @brief Set the dedo object
     * 
     * @param d Objeto do tipo dedo.
     */
    void set_dedo(dedo);
    /**
     * @brief Função que realiza a comparação de uma impressão digital com as que existem na base de dados.
     * 
     * @param d Objeto do tipo dedo.
     */
    void comparar(dedo);
    /**
     * @brief Calcula o resultado da comparação e define o resultado.
     * 
     */
    void resultado();
    /**
     * @brief Método que pega a quantidade de objetos na base de dados.
     * 
     * @return Retorna um inteiro correspondente ao resultado.
     */
    int get_quantidade();
    /**
     * @brief Função que exibe o resultado.
     * 
     */
    void mostrar_resultados();
};