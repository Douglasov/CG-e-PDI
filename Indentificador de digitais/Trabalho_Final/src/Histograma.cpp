#include "../include/Histograma.h"

using namespace std;
using namespace cv;

histograma::histograma(uint8_t *d, int l, int c)
{
    img_dados = d;
    threshold = 0;
    linhas = l;
    colunas = c;
    for (int i = 0; i < 256; i++)
        vetor.push_back(0);
}

void histograma::inverter()
{
    vector<float> aux2;
    for (int i = 0; i < 256; i++)
        aux2.push_back(0);
    for (int i = 0; i < 256; i++)
        aux2[vetor[i] * 255] = i / 255.00;
    for (int i = 1; i < 256; i++)
        if (aux2[i] == 0)
            aux2[i] = aux2[i - 1];
    vetor = aux2;
}

vector<float> histograma::getvetor()
{
    return vetor;
}

void histograma::calcularMasc(Mat masc)
{

    for (int i = 0; i < linhas * colunas; i++)
    {
        if (masc.data[i] == 255)
            vetor[(uint32_t)img_dados[i]] += 1;
    }
}

void histograma::calcular()
{
    for (int i = 0; i < linhas * colunas; i++)
    {
        vetor[(uint32_t)img_dados[i]] += 1;
    }
}

void histograma::normalizar_mostrar()
{
    maior = vetor[0];
    for (int i = 1; i < 256; i++)
    {
        if (maior <= vetor[i])
            maior = vetor[i];
    }
    for (int i = 0; i < 256; i++)
        vetor[i] /= maior;
    cout << maior << endl;
}

void histograma::normalizar()
{
    for (int i = 0; i < 256; i++)
        vetor[i] /= linhas * colunas;
}

void histograma::plotar(int vermelho, int verde, int azul, String nome, int tam, int move, int y)
{
    for (int i = 0; i < 255; i++)
    {
        cv::line(plot, cv::Point(i, 255.00 * (1 - vetor[i])), cv::Point(i + 1, 255.00 * (1 - vetor[i + 1])), Scalar(255 * azul, 255 * verde, 255 * vermelho), 2, 8, 0);
    }
    namedWindow(nome, WINDOW_NORMAL);
    resizeWindow(nome, tam, tam);
    moveWindow(nome, move, y);
    imshow(nome, plot);
}

void histograma::acumulado()
{
    calcular();
    for (int i = 0; i < 255; i++)
        vetor[i + 1] += vetor[i];
    normalizar();
}

void histograma::acumulado_masc(Mat masc)
{
    calcularMasc(masc);
    for (int i = 0; i < 255; i++)
        vetor[i + 1] += vetor[i];
    normalizar();
}

void histograma::linear(int I1, int I2, double K1, double K2)
{
    K1 /= 255;
    K2 /= 255;
    for (int i = 0; i < 256; i++)
        aux.push_back(0);
    for (int i = 0; i < 256; i++)
    {
        if (i < I1)
            aux[i] = K1;
        else if (i < I2 && i >= I1)
            aux[i] = (((K2 - K1) / (I2 - I1)) * (i - I1) + K1);
        else
            aux[i] = K2;
    }
    vetor = aux;
}
int histograma::OtsuThreshold()
{
    double probability[256], mean[256];
    double max_between, between[256];

    for (int i = 0; i < 256; i++)
    {
        probability[i] = 0.0;
        mean[i] = 0.0;
        between[i] = 0.0;
    }

    probability[0] = vetor[0];

    for (int i = 1; i < 256; i++)
    {
        probability[i] = probability[i - 1] + vetor[i];
        mean[i] = mean[i - 1] + i * vetor[i];
    }

    threshold = 0;
    max_between = 0.0;

    for (int i = 0; i < 255; i++)
    {
        if (probability[i] != 0.0 && probability[i] != 1.0)
            between[i] = pow(mean[255] * probability[i] - mean[i], 2) / (probability[i] * (1.0 - probability[i]));
        else
            between[i] = 0.0;
        if (between[i] > max_between)
        {
            max_between = between[i];
            threshold = i;
        }
    }
    return threshold;
}