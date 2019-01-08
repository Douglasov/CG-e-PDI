
#include "opencv2/highgui.hpp"
#include "opencv2/imgcodecs.hpp"
#include "opencv2/imgproc.hpp"
#include <algorithm>
#include <iostream>

using namespace std;
using namespace cv;


int main(int argc, char **argv)
{
  Mat src,src2;

  //lendo o arquivo
  src = imread("hue.png", 1);
  src2 = imread("img2.jpg", 1);


  cv::cvtColor(src, src, CV_BGR2GRAY);
  cv::cvtColor(src2, src2, CV_BGR2GRAY);

  namedWindow("Imagem 1", WINDOW_NORMAL);
	moveWindow("Imagem 1", 0,0);
  imshow("Imagem 1", src);

  namedWindow("Imagem 2", WINDOW_NORMAL);
	moveWindow("Imagem 2", 600,0);
  imshow("Imagem 2", src2);

  //imagem que se deseja fazer o casamento de histograma --------------------------------
  long double bind[256];
  long double hist1[256];
  fill_n(bind, 256, 0);

  //Histograma normal imagem 1
  for (int i = 0; i < src2.rows * src2.cols; i++)
  {
    bind[(uint32_t)src2.data[i]] += 1;
  }

  long double maior2=(*max_element(bind, bind + 256));

    for (int i = 0; i < 256; i++)
  {
    hist1[i]=bind[i]/maior2;
  }

  Mat plot1 = Mat::zeros(255,255, CV_8UC3);

  for (int i = 0; i < 255; i++)
  {
    line(plot1, Point(i, 255.00 * (1 - hist1[i])), Point(i + 1, 255.00 * (1 - hist1[i + 1])), Scalar(0, 255, 0), 2, 8, 0);
  }

  namedWindow("Histograma Imagem 2", WINDOW_NORMAL);
	moveWindow("Histograma Imagem 2", 600,370);
  imshow("Histograma Imagem 2", plot1);



  // fazendo histograma acumulado imagem 1
  for (int i = 0; i < 255; i++)
  {
    bind[i+1] += bind[i];
  }
  
  long double maior1=(*max_element(bind, bind + 256));

    //normalizando os bins
  for (int i = 0; i < 256; i++)
  {
    bind[i] = bind[i] / maior1;
  }

  //equalizando imagem 1 desejada
  for (int i = 0; i <src2.rows * src2.cols; i++)
  {
    src2.data[i] = bind[(int32_t)src2.data[i]]*255;
  }

  Mat plo1 = Mat::zeros(255,255, CV_8UC3);

  for (int i = 0; i < 255; i++)
  {
    line(plo1, Point(i, 255.00 * (1 - bind[i])), Point(i + 1, 255.00 * (1 - bind[i + 1])), Scalar(0, 255, 0), 2, 8, 0);
  }



 //imagem que se deseja apegar as caracteristicas do histograma --------------------------------
  //criando e preenchendo com bins com 0
  long double bin1[256];
  long double hist2[256];
  fill_n(bin1, 256, 0);

  //Histograma normal imagem 2
  for (int i = 0; i < src.rows * src.cols; i++)
  {
    bin1[(uint32_t)src.data[i]] += 1;
  }

  long double maior3=(*max_element(bin1, bin1 + 256));

    for (int i = 0; i < 256; i++)
  {
    hist2[i]=bin1[i]/maior3;
  }

  Mat plot2 = Mat::zeros(255,255, CV_8UC3);

  for (int i = 0; i < 255; i++)
  {
    line(plot2, Point(i, 255.00 * (1 - hist2[i])), Point(i + 1, 255.00 * (1 - hist2[i + 1])), Scalar(0, 255, 0), 2, 8, 0);
  }

  namedWindow("Histograma Imagem 1", WINDOW_NORMAL);
	moveWindow("Histograma Imagem 1", 0,370);
  imshow("Histograma Imagem 1", plot2);

  // fazendo histograma acumulado imagem 2
  for (int i = 0; i < 255; i++)
  {
    bin1[i+1] += bin1[i];
  }
  
  long double maior=(*max_element(bin1, bin1 + 256));

    //normalizando os bins imagem 2
  for (int i = 0; i < 256; i++)
  {
    bin1[i] = bin1[i] / maior;
  }

  //invertendo histograma acumulado imagem 2
  long double inv[256];
  fill_n(inv, 256, 0);
  
  for (int i = 0; i < 256; i++)
      inv[int(bin1[i]*255)]=i;

	 for (int i = 0; i < 256; i++)
   {
	 if(inv[i]==0)inv[i]=inv[i-1]; 
   }

   maior=(*max_element(inv, inv + 256));

   	 for (int i = 0; i < 256; i++)
   {
	 inv[i]=inv[i]/maior;
   }


    Mat plo = Mat::zeros(255,255, CV_8UC3);

     for (int i = 0; i < 255; i++)
  {
    line(plo, Point(i, 255.00 * (1 - inv[i])), Point(i + 1, 255.00 * (1 - inv[i + 1])), Scalar(0, 255, 0), 2, 8, 0);
  }

  //aplicando histograma invertido imagem 2 na imagem 1 equalizada
  for (int i = 0; i <src2.rows * src2.cols; i++)
  {
    src2.data[i] = inv[(int32_t)src2.data[i]]*255;
  }

  namedWindow("Imagem Final Casamento", WINDOW_NORMAL);
	moveWindow("Imagem Final Casamento", 1200,0);
  imshow("Imagem Final Casamento", src2);

  //histograma casamento de histogramas
  long double bin2[256];
  long double hist3[256];
  fill_n(bin2, 256, 0);

  for (int i = 0; i < src.rows * src.cols; i++)
  {
    bin2[(uint32_t)src2.data[i]] += 1;
  }

  long double maior4=(*max_element(bin2, bin2 + 256));

  for (int i = 0; i < 256; i++)
  {
    hist3[i]=bin2[i]/maior4;
  }

  Mat plot3 = Mat::zeros(255,255, CV_8UC3);

  for (int i = 0; i < 255; i++)
  {
    line(plot3, Point(i, 255.00 * (1 - hist3[i])), Point(i + 1, 255.00 * (1 - hist3[i + 1])), Scalar(0, 255, 0), 2, 8, 0);
  }
  namedWindow("Histograma Imagem Final Casamento", WINDOW_NORMAL);
	moveWindow("Histograma Imagem Final Casamento", 1200,370);
  imshow("Histograma Imagem Final Casamento", plot3);

  waitKey(0);
  return 0;
}
