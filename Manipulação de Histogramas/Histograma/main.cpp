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
  src = imread("img2.jpg", 1);

  if (src.empty())
  {
    return -1;
  }

  namedWindow("Imagem 1", WINDOW_NORMAL);
	moveWindow("Imagem 1", 0,0);
  imshow("Imagem 1", src);

  //dividindo os pixels da matriz em rgb
  vector<Mat> rgb;
  split(src, rgb);

  //criando e preenchendo com bins com 0
  long double bin1[256];
  fill_n(bin1, 256, 0);
  long double bin2[256];
  fill_n(bin2, 256, 0);
  long double bin3[256];
  fill_n(bin3, 256, 0);

  //distribuindo nos bins os respectivos valores de r g e b
  for (int i = 0; i < rgb[1].rows * rgb[1].cols; i++)
  {
    bin1[(uint32_t)rgb[0].data[i]] += 1;
    bin2[(uint32_t)rgb[1].data[i]] += 1;
    bin3[(uint32_t)rgb[2].data[i]] += 1;
  }
  
  //normalizando os bins
  for (int i = 0; i < 256; i++)
  {
    bin1[i] = bin1[i] / (*max_element(bin1, bin1 + 256));
    bin2[i] = bin2[i] / (*max_element(bin2, bin2 + 256));
    bin3[i] = bin3[i] / (*max_element(bin3, bin3 + 256));
  }

  //gerando o histograma
  Mat plot = Mat::zeros(255, 255, CV_8UC3);

  for (int i = 0; i < 255; i++)
  {
    line(plot, Point(i, 255.00 * (1 - bin1[i])), Point(i + 1, 255.00 * (1 - bin1[i + 1])), Scalar(0, 0, 255), 2, 8, 0);
    line(plot, Point(i, 255.00 * (1 - bin2[i])), Point(i + 1, 255.00 * (1 - bin2[i + 1])), Scalar(0, 255, 0), 2, 8, 0);
    line(plot, Point(i, 255.00 * (1 - bin3[i])), Point(i + 1, 255.00 * (1 - bin3[i + 1])), Scalar(255, 0, 0), 2, 8, 0);
  }

  namedWindow("Histograma Imagem 1", WINDOW_NORMAL);
	moveWindow("Histograma Imagem 1", 0,370);
  imshow("Histograma Imagem 1", plot);
  waitKey(0);
  return 0;
}