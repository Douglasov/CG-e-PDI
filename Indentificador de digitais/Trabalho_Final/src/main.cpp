/**
 * @brief Classe principal do trabalho
 * 
 * @file main.cpp
 * @author Douglas Venâncio 
 * Filipe Pena
 * Marco Antonio
 * @date 2018-07-01
 */
#include "opencv2/core/utility.hpp"
#include "opencv2/imgproc.hpp"
#include "opencv2/imgcodecs.hpp"
#include "opencv2/highgui.hpp"
#include <opencv2/opencv.hpp>
#include "../include/Base_Dados.h"
//#include "../include/Histograma.h"
#include <iostream>
using namespace cv;
using namespace std;

const char *keys =
    {
        "{help h||}{@image |../src/img/d1_5.png|input image name}{@image |../src/img/110_8.tif|input image name}"};

int main(int argc, const char **argv)
{
    CommandLineParser parser(argc, argv, keys);
    string filename = parser.get<string>(0);
    imagem img(filename);
    dedo d1;
    base b1;
    vector<imagem> banco_i;
    int cont = 10;
    int menu = -1;
    int op=-1;
                //cadastrando digitais são 10 imagens imagens de nome i+5 sao da mesma pessoa exemplo a imagem 6.png e 1.png são da mesma pessoa
                for (int i = 0; i < cont; i++)
            {
                string nome = format("../src/base/%d.png", i + 1);
                imagem aux(nome);
                cout << nome << endl;
                banco_i.push_back(aux);
            }
            for (int i = 0; i < cont; i++)
            {
                if (!banco_i[i].temimagem())
                {
                    cout << "imagem não encontrada" << endl;
                }
                histograma H1(banco_i[i].getImagem().data, banco_i[i].getlinhas(), banco_i[i].getcolunas());
                H1.calcular();
                H1.normalizar();
                banco_i[i].transformacao_linear(127, 127, 255, 0);
                dedo aux;
                aux.set(banco_i[i]);
                aux.detectar_corner();
                aux.caracterizar();
                aux.set_nome(format("Induviduo_%d", (i%5)+1));
                b1.set_dedo(aux);

            }
            cout << "A base de dados possui: " << b1.get_quantidade() << endl;


    while (menu != 0)
    {
        cout << "MENU" << endl;
        cout << "1 ---------------- Procurar" << endl;
        cout << "2 ---------------- Tratar Imagem" << endl;
        cout << "0 ---------------- Sair" << endl
             << endl;
        cout << "entre com a opcao: ";
        cin >> menu;
        cout << endl;

        switch (menu)
        {

        case 1:
        {
                cout << "Qual individuo você deseja identificar:" << endl;
        cout << "individuo 1" << endl;
        cout << "individuo 2 " << endl;
        cout << "individuo 3 " << endl;
        cout << "individuo 4 " << endl;
        cout << "individuo 5 " << endl
             << endl;
        cout << "entre com a opcao: ";
        cin>>op;
        switch(op)
        {
        case 1:
        {
        img.setImagem("../src/img/d1_5.png");
        break;
        }
            case 2:
        {
        img.setImagem("../src/img/d2_4.png");
        break;
        }
            case 3:
        {
        img.setImagem("../src/img/d3_3.png");
        break;
        }
            case 4:
        {
        img.setImagem("../src/img/d4_2.png");
        break;
        }
            case 5:
        {
        img.setImagem("../src/img/d5_3.png");
        break;
        }
        }
        histograma H1(img.getImagem().data, img.getlinhas(), img.getcolunas());
        H1.calcular();
        H1.normalizar();
        img.transformacao_linear(127, 127, 255, 0); 
        d1.set(img);
        //d1.mostrar_dedo();
        d1.detectar_corner();
        d1.caracterizar();
        b1.comparar(d1);
        b1.resultado();
        b1.mostrar_resultados();
        d1.limpar_dedo();
        break;
        }
        case 2:
        {
        imagem im("../src/img/dedo.jpg");
        histograma H(im.getImagem().data, im.getlinhas(), im.getcolunas());
        H.calcular();
        H.normalizar();
        cout << "Aguarde ..." << endl;
        //criando mascara

        im.plotar("Imagem Normal", 300, 500, 500);
        im.transformacao_linear_mascara(H.OtsuThreshold(), H.OtsuThreshold(), 0, 255);
        im.plotar_mascara("Imagem Mascara", 300, 500, 500);

    
        im.filtrobilateral();
        im.plotar("Imagem Filtro Bilateral", 300, 500, 500);

        im.equalizar_clahe(15);
        im.plotar("Imagem Equalizada", 300, 500, 500);

        im.limiarizacaolocalcommascara(255,THRESH_BINARY,40, 4);
        im.plotar("Imagem Limiarizada", 300, 500, 500);

        // Filtros morfologicos
        im.dilatacao();
        im.plotar("Imagem Dilatada", 300, 500, 500);
        im.erosao();
        im.plotar("Imagem Erodida", 300, 500, 500);
        im.moda(7);
        im.plotar("Imagem Final (filtro de moda) ", 300, 500, 500);
        im.imagem_skelet();
        im.plotar_skelet("Imagem Esqueleto ", 300, 500, 500);

        waitKey(0);
        destroyAllWindows();
        break;
        }
        }

    }

    
    return 0;
}
/** 
 * @mainpage Projeto de PDI: Indentificação de Digitais
 * 
 * @section sec_intro Introdução
 *
 * O projeto tem o objetivo de identificar uma impressão digital em uma base de dados que acompanha o trabalho.
 * Nesta documentação seram detalhadas as informações necessárias para compilar, executar e usar o programa. 
 * 
 * Para facilitar o entendimento a explicação do programa serão divididas em duas etapas.
 * A primeira referente ao processamento de uma foto de um dedo e a segunda referente a classificação.  
 * 
 * @section sec_install Compilando, Executando e Usando o Programa 
 * 
 * @subsection  ssec1 Compilando e Executando 
 * 
 * Para Compilar e executar o código é necessario entrar na pasta build, e executar os seguintes comandos.
 * 
 * - cmake ..
 * - make 
 * - ./Digital_Pattern 
 * 
 * @subsection ssec2 Menu
 * 
 * A imagem Abaixo mostra o menu inicial do programa.
 * 
 * \image html imagens\menu.png
 * 
 * A primeira opção possibilita buscar no banco de dados uma digital
 * com o mesmo padrão de uma imagem desejada. Para facilitar foram carregadas algumas opções de imagem
 * para pesquisar no banco. A imagem abaixo mostra essas opções, e o resultado de uma consulta. 
 * 
 * \image html imagens\menu2.png
 * 
 * A segunda opção do menu executa a etapa de tratamento de uma imagem. Essa imagem tratada, 
 * já acompanha o projeto. Todas as etapas do processamento são exibidas na tela em forma de imagens.
 * 
 * A ultima opção do menu tem o objetivo de fechar o programa. 
 * 
 * As imagens referentes a base de dados, esta no diretório src/base, e as demais fotos estão
 * no diretório src/img.
 * 
 * @section sec_summary Resumo
 *
 * @subsection ssec3 Processamento de imagens
 * 
 * Nesta etapa é reslizado o tratamento de uma imagem, para que seja possível realizar
 * a indentificação dos padrões da digital. O fluxograma seguinte exemplifica as etapas.
 * 
 * \image html imagens\Fluxograma_1.PNG
 * 
 * 
 * As imagens seguintes ilustram as etapas mostradas no fluxograma.
 * 
 * - A primeira imagem mostra a foto do dedo em escala de cinza.
 * 
 * \image html imagens\img1.png
 * 
 * - A segunda mostra a imagem da mascara usada seguimentar o dedo.
 * Threshold.  
 * 
 * \image html imagens\img2.png
 * 
 * 
 * - A terceira imagem mostra a equalização da imagem, realizada para destacar as linhas do deto. 
 * 
 * \image html imagens\img3.png
 * 
 * - A proxima imagem mostra a imagem binaria. 
 *  
 * 
 * \image html imagens\img8.png
 * 
 * -E a última mostra o esqueleto da imagem.
 * 
 * \image html imagens\img9.png
 * 
 * @subsection ssec4 Identificação da Digital
 * 
 * Esta etapa mostra a parte da detecção das caracteristicas e comparação com outras impressões digitais. 
 * O fluxograma abaixo mostra as etapas do processo. 
 * 
 * \image html imagens\Fluxograma_2.PNG
 * 
 * - A imagem abaixo mostra as Minúcias detectadas usando o Harris Corner.
 * 
 * \image html imagens\minucias.png
 * 
 * - A Proxima imagem mostra o casamento de duas imagens, realizando as comparações das caracteristicas
 * de cada uma.
 * 
 * \image html imagens\match.png
 * 
 * @author Douglas Venâncio
 * @author Filipe Pena
 * @author Marco Vinha 
 * @date Junho de 2018
 */