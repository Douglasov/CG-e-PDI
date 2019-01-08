#include "opencv2/highgui.hpp"
#include "opencv2/imgcodecs.hpp"
#include "opencv2/imgproc.hpp"
#include <algorithm>
#include <iostream>

using namespace std;
using namespace cv;


int main(int argc, char **argv)
{
  Mat src;

  //lendo o arquivo
  src = imread("hue.png", 1);

  if (src.empty())
  {
    return -1;
  }

  cv::cvtColor(src, src, CV_BGR2GRAY);

  namedWindow("Imagem Normal", WINDOW_NORMAL);
	moveWindow("Imagem Normal", 0,0);
  imshow("Imagem Normal", src);

  //criando e preenchendo com bins com 0
  long double bin1[256];
  fill_n(bin1, 256, 0);

  //Histograma normal
  for (int i = 0; i < src.rows * src.cols; i++)
  {
    bin1[(uint32_t)src.data[i]] += 1;
  }

  // fazendo histograma acumulado
  for (int i = 0; i < 255; i++)
  {
    bin1[i+1] += bin1[i];
  }
  
  int maior=(*max_element(bin1, bin1 + 256));

  //normalizando os bins
  for (int i = 0; i < 256; i++)
  {
    bin1[i] = bin1[i] / maior;
  }

  //equalizando a imagem
  for (int i = 0; i < src.rows * src.cols; i++)
  {
    src.data[i] = bin1[(uint32_t)src.data[i]]*255;
  }

  namedWindow("Imagem Equalizada", WINDOW_NORMAL);
	moveWindow("Imagem Equalizada", 0,400);
  imshow("Imagem Equalizada", src);

  for (int i = 0; i < src.rows * src.cols; i++)
  {
    bin1[(uint32_t)src.data[i]] += 1;
  }

  maior=(*max_element(bin1, bin1 + 256));

  //normalizando os bins
  for (int i = 0; i < 256; i++)
  {
    bin1[i] = bin1[i] / maior;
  }

  //gerando o histograma acumulado
  Mat plo = Mat::zeros(255, 255, CV_8UC3);

  for (int i = 0; i < 255; i++)
  {
    line(plo, Point(i, 255.00 * (1 - bin1[i])), Point(i + 1, 255.00 * (1 - bin1[i + 1])), Scalar(0, 0, 255), 2, 8, 0);
  }

  namedWindow("Histograma Imagem Equalizada", WINDOW_NORMAL);
	moveWindow("Histograma Imagem Equalizada", 550,0);
  imshow("Histograma Imagem Equalizada", plo);
  waitKey(0);
  return 0;
}