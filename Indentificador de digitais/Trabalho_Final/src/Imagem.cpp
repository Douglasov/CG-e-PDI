#include "../include/Imagem.h"
using namespace std;
using namespace cv;
using cv::CLAHE;

imagem::imagem(String file)
{
    img = imread(file, 0);
    mascara = imread(file, 0);
    linhas = img.rows;
    colunas = img.cols;
}
void imagem::set(String file)
{
    img = imread(file, 0);
    mascara = imread(file, 0);
    linhas = img.rows;
    colunas = img.cols;
}
int imagem::getlinhas()
{
    return linhas;
}
int imagem::getcolunas()
{
    return colunas;
}
bool imagem::temimagem()
{
    if (img.data)
        return true;
    return false;
}
void imagem::plotar(String nome, int tam, int move, int y)
{
    namedWindow(nome, WINDOW_NORMAL);
    resizeWindow(nome, tam, tam);
    moveWindow(nome, move, y);
    imshow(nome, img);
}
void imagem::plotar_mascara(String nome, int tam, int move, int y)
{
    namedWindow(nome, WINDOW_NORMAL);
    resizeWindow(nome, tam, tam);
    moveWindow(nome, move, y);
    imshow(nome, mascara);
}
void imagem::transformacao_linear(int I1, int I2, int K1, int K2)
{
    for (int i = 0; i < linhas * colunas; i++)
    {
        if ((uint32_t)img.data[i] < I1)
            img.data[i] = K1;
        else if ((uint32_t)img.data[i] < I2 && (uint32_t)img.data[i] >= I1)
            img.data[i] = (((K2 - K1) / (I2 - I1)) * ((uint32_t)img.data[i] - I1) + K1);
        else if ((uint32_t)img.data[i] >= I2)
            img.data[i] = K2;
    }
}
void imagem::transformacao_linear_mascara(int I1, int I2, int K1, int K2)
{
    for (int i = 0; i < linhas * colunas; i++)
    {
        if ((uint32_t)mascara.data[i] < I1)
            mascara.data[i] = K1;
        else if ((uint32_t)mascara.data[i] < I2 && (uint32_t)mascara.data[i] >= I1)
            mascara.data[i] = (((K2 - K1) / (I2 - I1)) * ((uint32_t)mascara.data[i] - I1) + K1);
        else if ((uint32_t)mascara.data[i] >= I2)
            mascara.data[i] = K2;
    }
}
void imagem::transformacao_mascara(int I1, int I2, int K1, int K2)
{
    for (int i = 0; i < img.rows * img.cols; i++)
    {
        if ((uint32_t)mascara.data[i] == 0)
        {
            if ((uint32_t)img.data[i] < I1)
                img.data[i] = K1;
            else if ((uint32_t)img.data[i] < I2 && (uint32_t)img.data[i] >= I1)
                img.data[i] = (((K2 - K1) / (I2 - I1)) * ((uint32_t)img.data[i] - I1) + K1);
            else if ((uint32_t)img.data[i] >= I2)
                img.data[i] = K2;
        }
    }
}
void imagem::transformacao_aculmulado(histograma acumulado, int tam, int move, int y)
{
    acumulado.acumulado();
    acumulado.plotar(0, 0, 1, "Histograma Acumulado", tam, move, y);

    vector<float> aux3 = acumulado.getvetor();
    for (int i = 0; i < linhas * colunas; i++)
    {
        if (mascara.data[i] == 255)
            img.data[i] = aux3[(uint32_t)img.data[i]] * 255;
    }
}
void imagem::casamento_de_histograma(histograma h1, histograma h2, int tam, int move, int y)
{
    h1.acumulado();
    h1.plotar(1, 0, 0, "Acumulado Imagem", tam, 0 * move, y);
    h2.acumulado();
    h2.plotar(1, 0, 0, "Acumulado e inversa referencia", tam, 1 * move, y);
    h2.inverter();
    h2.plotar(0, 0, 1, "Acumulado e inversa referencia", tam, 1 * move, y);
    vector<float> aux3 = h1.getvetor();
    vector<float> aux4 = h2.getvetor();
    for (int i = 0; i < linhas * colunas; i++)
        img.data[i] = aux4[aux3[(uint32_t)img.data[i]] * 255] * 255;
}
void imagem::filtro_canny(int max, int raio, int k)
{
    Mat borda, result;
    Canny(img, borda, max, raio, k);
    borda.convertTo(result, CV_8U);
    //imshow("image", result);
}

void imagem::filtro_mediana()
{
    Mat result;
    medianBlur(img, result, 3);
    img = result;
}
void imagem::Filtro_gabor()
{
    Mat src_f, temp;
    img.convertTo(src_f, CV_32F);
    int k = 3;
    double sig = 0.5, lm = 0.012, gm = 0.0125, ps = 0.015;
    double theta = 30;

    Mat kernel1;
    Mat dest;
    kernel1 = cv::getGaborKernel(cv::Size(k, k), sig, theta, lm, gm, ps, CV_32F);
    filter2D(src_f, dest, CV_32F, kernel1);

    img = dest;
}

void imagem::erosao()
{
    int erosion_size = 1;
    Mat element = getStructuringElement(cv::MORPH_RECT,
                                        cv::Size(2 * erosion_size + 1, 2 * erosion_size + 1),
                                        cv::Point(erosion_size, erosion_size));
    erode(img, img, element);
}

void imagem::dilatacao()
{
    int erosion_size = 1;
    Mat element = getStructuringElement(cv::MORPH_RECT,
                                        cv::Size(2 * erosion_size + 1, 2 * erosion_size + 1),
                                        cv::Point(erosion_size, erosion_size));
    dilate(img, img, element);
}
void imagem::filtrobilateral()
{
    Mat src;
    double kernel_length = 3;
    bilateralFilter(img, src, 9, 75, 75);
    img = src;
}

Mat imagem::getImagem()
{
    return img;
}

void imagem::setImagem(String file)
{
    img = imread(file, 0);
    mascara = imread(file, 0);
    linhas = img.rows;
    colunas = img.cols;
}

Mat imagem::getMascara()
{
    return mascara;
}
void imagem::equalizar_clahe(double a)
{
    Ptr<CLAHE> clahe = createCLAHE();
    clahe->setClipLimit(a);
    Mat dst;
    clahe->apply(img, dst);
    img = dst;
}

void imagem::thinningIteration(Mat& im, int iter)
{
    Mat marker = Mat::zeros(im.size(), CV_8UC1);
    for (int i = 1; i < im.rows-1; i++)
    {
        for (int j = 1; j < im.cols-1; j++)
        {
            uchar p2 = im.at<uchar>(i-1, j);
            uchar p3 = im.at<uchar>(i-1, j+1);
            uchar p4 = im.at<uchar>(i, j+1);
            uchar p5 = im.at<uchar>(i+1, j+1);
            uchar p6 = im.at<uchar>(i+1, j);
            uchar p7 = im.at<uchar>(i+1, j-1);
            uchar p8 = im.at<uchar>(i, j-1);
            uchar p9 = im.at<uchar>(i-1, j-1);

            int A  = (p2 == 0 && p3 == 1) + (p3 == 0 && p4 == 1) +
                     (p4 == 0 && p5 == 1) + (p5 == 0 && p6 == 1) +
                     (p6 == 0 && p7 == 1) + (p7 == 0 && p8 == 1) +
                     (p8 == 0 && p9 == 1) + (p9 == 0 && p2 == 1);
            int B  = p2 + p3 + p4 + p5 + p6 + p7 + p8 + p9;
            int m1 = iter == 0 ? (p2 * p4 * p6) : (p2 * p4 * p8);
            int m2 = iter == 0 ? (p4 * p6 * p8) : (p2 * p6 * p8);

            if (A == 1 && (B >= 2 && B <= 6) && m1 == 0 && m2 == 0)
                marker.at<uchar>(i,j) = 1;
        }
    }

    im &= ~marker;
}


void imagem::skeletizar(Mat& im)
{
	 
    im /= 255;

    Mat prev = Mat::zeros(im.size(), CV_8UC1);
    Mat diff;

    do {
        thinningIteration(im, 0);
        thinningIteration(im, 1);
        absdiff(im, prev, diff);
        im.copyTo(prev);
    }
    while (countNonZero(diff) > 0);

    im *= 255;
}


void imagem::imagem_skelet()
{
    Mat convert=img.clone();
    
    skeletizar(convert);
    esqueleto = convert;
    
    //namedWindow("Skeleton Image", CV_WINDOW_NORMAL);
    //imshow("Skeleton Image", esqueleto);
}

void imagem::plotar_skelet(String nome, int tam, int move, int y)
{

    namedWindow(nome, WINDOW_NORMAL);
    resizeWindow(nome, tam, tam);
    moveWindow(nome, move, y);
    imshow(nome, esqueleto);
}


void imagem::limiarizacaolocal()
{
    adaptiveThreshold(img, img, 255, ADAPTIVE_THRESH_GAUSSIAN_C,
                      THRESH_BINARY, 40, 5);
}


void imagem::limiarizacaolocalcommascara(double maxValue, int thresholdType, int blockSize, double C)
{
    Mat mask = mascara;
    Mat invertMask, noN, conv, kernel(cv::Size(blockSize, blockSize), CV_32F);

    //negando a mascara
    cv::bitwise_not(mask, invertMask);

    //colocando 0 nos bits fora da mascara
    img = img - invertMask;

    {
        {
            //aplicando mediana no local da limiarizacao
            cv::blur(img, conv, cv::Size(blockSize, blockSize));
            //gausiano que deu ruim
            //cv::GaussianBlur(img,conv,cv::Size(blockSize,blockSize),0,0);
        }

        {
            //aplicando mediana na mascara
            cv::blur(mask, noN, cv::Size(blockSize, blockSize));
            //gausiano que deu ruim
            //cv::GaussianBlur(mask,noN,cv::Size(blockSize,blockSize),0,0);
        }
    }

    //removendo tudo fora da mascara
    if (thresholdType == cv::THRESH_BINARY_INV)
    {
        img = 255 * (conv / noN) - img;
    }
    else
    {
        img = img - 255 * (conv / noN);
    }


    cv::threshold(img, img, C, maxValue, cv::THRESH_BINARY);

    cv::bitwise_and(mask, img, img);
}

void imagem::aumenta_imagem()
{
    Mat aux;
    Size t(colunas * 4, linhas * 4);
    resize(img, aux, t, 0, 0, INTER_CUBIC);
    img = aux;
}
int imagem::maior_vet(vector<float> vet)
{
    int maior = 0;
    int ind = 0;
    for (int i = 0; i < vet.size(); i++)
        if (vet[i] > maior)
        {
            maior = vet[i];
            ind = i;
        }

    return ind;
}
void imagem::moda(int kernel_size)
{

    Mat nova = img.clone();
    vector<float> vet;
    for (int i = 0; i < 256; i++)
        vet.push_back(0);

    int k = (kernel_size / 2);
    for (int i = 0; i < img.rows; i++)
        for (int j = 0; j < img.cols; j++)
        {
            for (int ki = 0; ki < kernel_size; ki++)
                for (int kj = 0; kj < kernel_size; kj++)
                    if (i + ki - k > 0 && i + ki - k < img.rows && j + kj - k > 0 && j + kj - k < img.cols)
                        vet[img.at<uchar>(i + ki - k, j + kj - k)] += 1;

            nova.at<uchar>(i, j) = maior_vet(vet);
            for (int i = 0; i < 256; i++)
                vet[i] = 0;
        }
    img = nova;
}
Mat imagem::get_esqueleto()
{
    return esqueleto;
}
