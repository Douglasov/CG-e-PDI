/**
 * @brief A base de dados é uma estrutura que armazena algumas impressões digitais em uma estrurura.
 * 
 * @file Base_Dados.cpp
 * @author Douglas Venâncio 
 * Filipe Pena
 * Marco Antonio
 * @date 2018-07-01
 */
#include "../include/Base_Dados.h"
#include "opencv2/opencv.hpp"
#include <fstream>
#include <iostream>
using namespace std;
using namespace cv;

/**
 * @brief Adiciona na base de dados um novo objeto.
 * 
 * @param Recebe esse objeto como parâmetro da função
 */

void base::set_dedo(dedo d)
{
    bd.push_back(d);
}

/**
 * @brief Realiza a comparação dos descritores de um dedo com os outros da base de dados.
 * Para realizar essa comparação é usado o ORB, ele calcula uma distancia entre uma imagem e outra, que servira de 
 * parametro para classificação. 
 * 
 * @param Recebe esse objeto que sera comparado como um parâmetro do método.
 */

void base::comparar(dedo d)
{
    Ptr<DescriptorMatcher> matcher = DescriptorMatcher::create("BruteForce-Hamming");
    vector<DMatch> matches;
    float menorscore=100000;
    for (int i = 0; i < bd.size(); i++)
    {
        matcher->match(d.get_descritor(), bd[i].get_descritor(), matches);
        float score = 0.0;
        for (int j = 0; j < matches.size(); j++)
        {
            DMatch current_match = matches[j];
            
            score = score + current_match.distance;
        }
        result.push_back(score);
        cout << endl
             << "Matching Score = " << score << endl;
        if(score<menorscore)
        {
            menorscore=score;

        }
    }
}

/**
 * @brief Função que encontra a menor distância encontrada no método comparar. 
 * 
 */

void base::resultado()
{
    int r = -1, aux=100000;
    for (int i = 0; i < bd.size(); i++)
    {
        if (result[i] < bd[i].get_limiar())
        {
            if (aux > result[i])
            {
                aux = result[i];
                r = i;
            }
        }
    }
    if (r != -1)
    {
        cout << "O dedo é de: " << bd[r].get_nome() << endl;
    }
    result.clear();
    
}
void base::mostrar_resultados()
{
    for (int i = 0; i < result.size(); i++)
    {
        cout << result[i] << endl;
    }    
}
/**
 * @brief Retorna o número de objetos no banco de dados. 
 * 
 * @return Inteiro com o número de objetos.
 */
int base::get_quantidade()
{
    return bd.size();
}