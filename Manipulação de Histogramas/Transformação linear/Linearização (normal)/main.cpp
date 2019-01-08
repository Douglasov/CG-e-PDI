
#include "opencv2/highgui.hpp"
#include "opencv2/imgcodecs.hpp"
#include "opencv2/imgproc.hpp"
#include <algorithm>
#include <iostream>

using namespace std;
using namespace cv;

long double *transformacaolinear(long double I1, long double I2, long double k1, long double k2)
{
  long double *transf = new long double[256];
  //k1 e k2 os 2 intervalos de cinza normalizados

  k1 = k1 / 255;
  k2 = k2 / 255;

  for (int i = 0; i < 256; i++)
  {
    if (i < I1)
    {
      transf[i] = k1;
    }
    else if (i < I2 && i >= I1)
    {
      transf[i] = ((((k2 - k1) / (I2 - I1)) * (i - I1)) + k1);
    }
    else if (i >= I2)
    {
      transf[i] = k2;
    }
  }
  return transf;
}

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

  namedWindow("Imagem 1", WINDOW_NORMAL);
	moveWindow("Imagem 1", 0,0);
  imshow("Imagem 1", src);

  //histograma normal---------------------------------------------------------------------------------------------------
  //criando e preenchendo com bins com 0
  long double bin1[256];
  fill_n(bin1, 256, 0);

  //Histograma normal
  for (int i = 0; i < src.rows * src.cols; i++)
  {
    bin1[(uint32_t)src.data[i]] += 1;
  }

  int maior = (*max_element(bin1, bin1 + 256));

  //normalizando os bins
  for (int i = 0; i < 256; i++)
  {
    bin1[i] = bin1[i] / maior;
  }

    Mat plot1 = Mat::zeros(255, 255, CV_8UC3);

  for (int i = 0; i < 255; i++)
  {
    line(plot1, Point(i, 255.00 * (1 - bin1[i])), Point(i + 1, 255.00 * (1 - bin1[i + 1])), Scalar(0, 0, 255), 2, 8, 0);
  }

  namedWindow("Imagem 1 Histograma", WINDOW_NORMAL);
	moveWindow("Imagem 1 Histograma", 0,400);
  imshow("Imagem 1 Histograma", plot1);

  //transformacao linear--------------------------------------------------------------------------------------
  //normal nível(brilho)=(I1+I2)/2 e largura(contraste) (I2-I1)
  long double *transf=transformacaolinear(0,170,50,255);
  Mat Imgtranf=src;
  for (int i = 0; i < src.rows * src.cols; i++)
  {
  Imgtranf.data[i] = transf[(int32_t)Imgtranf.data[i]]*255;
  }

  namedWindow("Imagem 1 Transformacao Linear (normal)", WINDOW_NORMAL);
	moveWindow("Imagem 1 Transformacao Linear (normal)", 600,0);
  imshow("Imagem 1 Transformacao Linear (normal)", Imgtranf);

  //criando e preenchendo com bins com 0
  long double bintranf[256];
  fill_n(bintranf, 256, 0);

  //Histograma normal
  for (int i = 0; i < Imgtranf.rows * Imgtranf.cols; i++)
  {
    bintranf[(uint32_t)Imgtranf.data[i]] += 1;
  }

  maior = (*max_element(bintranf, bintranf + 256));

  //normalizando os bin
  for (int i = 0; i < 256; i++)
  {
    bintranf[i] = bintranf[i] / maior;
  }

  //gerando o histograma
  Mat plot2 = Mat::zeros(255, 255, CV_8UC3);

  for (int i = 0; i < 255; i++)
  {
    line(plot2, Point(i, 255.00 * (1 - bintranf[i])), Point(i + 1, 255.00 * (1 - bintranf[i + 1])), Scalar(0, 0, 255), 2, 8, 0);
  }

  namedWindow("Histograma transformacao linear (normal)", WINDOW_NORMAL);
	moveWindow("Histograma transformacao linear (normal)", 600,400);
  imshow("Histograma transformacao linear (normal)", plot2);


  waitKey(0);
  return 0;
}
