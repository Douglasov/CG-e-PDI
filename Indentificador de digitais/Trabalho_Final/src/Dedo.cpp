/**
 * @brief Aquivo que implementa os metodos referentes a uma estrutura de objeto dedo.
 * 
 * @file Dedo.cpp
 * @author Douglas Venâncio 
 * Filipe Pena
 * Marco Antonio
 * @date 2018-07-01
 */
#include "opencv2/opencv.hpp"
#include <fstream>
#include <iostream>
#include "../include/Dedo.h"

using namespace std;
using namespace cv;

dedo::dedo(imagem im)
{
  img = im;
}
void dedo::set(imagem im)
{
  img = im;
}

Mat dedo::get_descritor()
{
  return descritor;
}
/**
 * @brief Com os ponto chave detectados são computados os descritores,
 * cada imagem possui um descritor que sera usado para comparar com outros
 * descritores. 
 * 
 */
void dedo::caracterizar()
{
  Ptr<Feature2D> orb_descriptor = ORB::create();
  orb_descriptor->compute(img.get_esqueleto(), keypoints, descritor);
}
/**
 * @brief Para detectar os pontos chave é usado o Harris Corner
 * que detecta a variação de intensidade dos pixeis para definir se
 * existe ou não um cruzamento.
 * 
 */
void dedo::detectar_corner()
{
  Mat harris_corners, harris_normalised;
  int threshold_harris = 125;
  img.imagem_skelet();
  harris_corners = Mat::zeros(img.get_esqueleto().size(), CV_32FC1);
  cornerHarris(img.get_esqueleto(), harris_corners, 2, 3, 0.04, BORDER_DEFAULT);
  normalize(harris_corners, harris_normalised, 0, 255, NORM_MINMAX, CV_32FC1, Mat());

  Mat rescaled;
  convertScaleAbs(harris_normalised, rescaled);

  Mat harris_c(rescaled.rows, rescaled.cols, CV_8UC3);
  Mat in[] = {rescaled, rescaled, rescaled};

  int from_to[] = {0, 0, 1, 1, 2, 2};
  mixChannels(in, 3, &harris_c, 1, from_to, 3);

  for (int x = 0; x < harris_normalised.cols; x++)
  {
    for (int y = 0; y < harris_normalised.rows; y++)
    {
      if ((int)harris_normalised.at<float>(y, x) > threshold_harris)
      {
        // Draw or store the keypoint location here, just like you decide. In our case we will store the location of the keypoint
        circle(harris_c, Point(x, y), 5, Scalar(0, 255, 0), 1);
        circle(harris_c, Point(x, y), 1, Scalar(0, 0, 255), 1);
        keypoints.push_back(KeyPoint(x, y, 1));
      }
    }
  }

}
void dedo::mostrar_dedo()
{
  img.plotar("Dedo", 500, 500, 500);
}
void dedo::set_nome(string n)
{
  nome = n;
}
string dedo::get_nome()
{
  return nome;
}
void dedo::mostrar_nome()
{
  cout << nome << endl;
}
int dedo::get_limiar()
{
  return limiar;
}
void dedo::limpar_dedo()
{
  descritor.release();
  keypoints.clear();
}
