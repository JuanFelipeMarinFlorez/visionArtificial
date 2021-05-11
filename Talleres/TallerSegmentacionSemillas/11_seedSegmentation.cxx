#include "opencv2/imgproc.hpp"
#include "opencv2/imgcodecs.hpp"
#include "opencv2/highgui.hpp"
#include <iostream>
#include <string.h>
#include <ctime>
#include <queue>

using namespace cv;

Mat segmentacion(Mat grayImage, int seedX[], int seedY[], int numSeeds, int permisividad);
Mat segmentacion_color(Mat image, int seedX[], int seedY[], int numSeeds, int permisividad);

int main(int argc, char const *argv[])
{
    srand((unsigned)time(0));
    //PASOS DEL ALGORITMO
    //1: Leer la imagen (Se pasa por parametros, se puede recibir a color.)
    //2: Leer las semillas (Por parametros, o aleatoriamente)
    //3:

    //Verificación de Comandos
    // forma ideal de ejecutar : ./11_seedSegmentation  <image_file> <N° of seeds>
    //                                <r (random seed) / s (set seed)> <a (average) / v (variance)> <rgb/gs(grayscale)>
    //                            [<x coordinate1> <y coordinate1> <x coordinate2> <y coordinate2> (ETC)]

    if (argc < 7)
    {
        std::cerr << "Usage: " << argv[0] << "image_file N°_of_seeds r(random seed)/s(set seed) a(average)/v(variance) rgb/gs(grayscale) permisivness (x_coordinate1 y_coordinate1 x_coordinate2 y_coordinate2 (ETC))" << std::endl;
        return (-1);
    }

    //Leyendo la imagen

    Mat image;
    image = imread(argv[1], 1);
    if (!image.data)
    {
        std::cerr << "Error: No image data" << std::endl;
        return (-1);
    }

    //Leyendo las Semillas

    int seedX[atoi(argv[1])];
    int seedY[atoi(argv[1])];
    int numberSeeds = atoi(argv[2]);
    int max_X = image.cols;
    int max_Y = image.rows;
    int permisividad = (atoi(argv[6]));
    std::cout << "Imagen a segmentar: " << argv[1] << std::endl;
    std::cout << "N° de semillas: " << argv[2] << std::endl;
    std::cout << "Posicion de semilla: " << argv[3] << std::endl;
    std::cout << "Permisividad: " << permisividad << std::endl;

    if (strcmp(argv[3], "r") == 0)
    {
        for (int i = 0; i < numberSeeds; i++)
        {
            seedX[i] = std::rand() % (max_X) + 0;
            seedY[i] = std::rand() % (max_Y) + 0;
        }
        // for (int i = 0; i < numberSeeds; i++)
        // {
        //     std::cout << "seedX: " << seedX[i] << std::endl;
        //     std::cout << "seedy: " << seedY[i] << std::endl;
        // }
    }
    else if (strcmp(argv[3], "s") == 0)
    {
        int i, j;
        if (argc == (7 + (numberSeeds * 2)))
        {
            for (i = 0, j = 0; i < numberSeeds; i++, j += 2)
            {
                seedX[i] = atoi(argv[7 + j]);
                seedY[i] = atoi(argv[8 + j]);
            }

            // BORRAR_COUTS
            // --------------------------------------------------
            // for (int i = 0; i < numberSeeds; i++)
            // {
            //     std::cout << "seedX: " << seedX[i] << std::endl;
            //     std::cout << "seedy: " << seedY[i] << std::endl;
            // }
            // --------------------------------------------------
        }
        else
        {
            std::cerr << "Error: Numbers of seed doesnt match" << std::endl;
            return (-1);
        }
    }
    Mat imgsegmentacion(image.size(),CV_8UC1);
    Mat grayImage(image.size(), CV_8UC1);

    std::stringstream ss(argv[1]);
    std::string basename;
    getline(ss, basename, '.');
    //----------------------------------------------------------------------
    // Llamado a funcion de segmentar:
    if (strcmp(argv[5], "rgb") == 0)
    {
        imgsegmentacion = segmentacion_color(image, seedX, seedY, numberSeeds, permisividad);
        imwrite(basename + "_segmentacion_binaria.png", imgsegmentacion);
        imwrite(basename + "_umbralizada.png", image & imgsegmentacion);
    }
    else if (strcmp(argv[5], "gs") == 0)
    {
        cvtColor(image, grayImage, COLOR_BGR2GRAY);
        imgsegmentacion = segmentacion_color(image, seedX, seedY, numberSeeds, permisividad);
        std::cout<<grayImage.size()<<std::endl;
        std::cout<<image.size()<<std::endl;
        imwrite(basename + "_segmentacion_binaria.png", imgsegmentacion);
        imwrite(basename + "_umbralizada.png", image & imgsegmentacion);
    }
    else
    {
        std::cerr << "Error: Param of type of image wrong. Use rgb for color images or gs for grayscale" << std::endl;
        return (-1);
    }

    return((0));
}

Mat segmentacion(Mat grayImage, int seedX[], int seedY[], int numSeeds, int permisividad)
{
    int graymax_X = grayImage.cols;
    int graymax_Y = grayImage.rows;
    int max_X = grayImage.cols;
    int max_Y = grayImage.rows;
    Mat image_segmentated = Mat::zeros(max_Y, max_X, CV_8UC1);
    std::queue<Point> colaPixeles;
    //Vec3b Intesidades = image.at<Vec3f>(seedY, seedX);
    for (int i = 0; i < numSeeds; i++)
    {
        colaPixeles.push(Point(seedX[i], seedY[i]));
        image_segmentated.at<uchar>(seedY[i], seedX[i]) = 255;
    }

    do
    {

        Point punto_actual = colaPixeles.front();
        colaPixeles.pop();
        int prom = -1;
        int acum = 0;
        int promedio = 0;
        int rango = permisividad;
        int lista_intensidades[8];
        if (punto_actual.x - 1 > 0 && punto_actual.y - 1 > 0 &&
            punto_actual.x - 1 < graymax_X && punto_actual.y - 1 < graymax_Y)
        {
            lista_intensidades[0] = grayImage.at<uchar>(punto_actual.y - 1, punto_actual.x - 1);
            acum++;
        }
        if (punto_actual.x - 1 > 0 && punto_actual.y > 0 &&
            punto_actual.x - 1 < graymax_X && punto_actual.y < graymax_Y)
        {
            lista_intensidades[acum] = grayImage.at<uchar>(punto_actual.y, punto_actual.x - 1);
            acum++;
        }

        if (punto_actual.x - 1 > 0 && punto_actual.y + 1 > 0 &&
            punto_actual.x - 1 < graymax_X && punto_actual.y + 1 < graymax_Y)
        {
            lista_intensidades[acum] = grayImage.at<uchar>(punto_actual.y + 1, punto_actual.x - 1);
            acum++;
        }
        if (punto_actual.x > 0 && punto_actual.y - 1 > 0 &&
            punto_actual.x < graymax_X && punto_actual.y - 1 < graymax_Y)
        {
            lista_intensidades[acum] = grayImage.at<uchar>(punto_actual.y - 1, punto_actual.x);
            acum++;
        }
        if (punto_actual.x > 0 && punto_actual.y + 1 > 0 &&
            punto_actual.x < graymax_X && punto_actual.y + 1 < graymax_Y)
        {
            lista_intensidades[acum] = grayImage.at<uchar>(punto_actual.y + 1, punto_actual.x);
            acum++;
        }
        if (punto_actual.x + 1 > 0 && punto_actual.y - 1 > 0 &&
            punto_actual.x + 1 < graymax_X && punto_actual.y - 1 < graymax_Y)
        {
            lista_intensidades[acum] = grayImage.at<uchar>(punto_actual.y - 1, punto_actual.x + 1);
            acum++;
        }
        if (punto_actual.x + 1 > 0 && punto_actual.y > 0 &&
            punto_actual.x + 1 < graymax_X && punto_actual.y < graymax_Y)
        {
            lista_intensidades[acum] = grayImage.at<uchar>(punto_actual.y, punto_actual.x + 1);
            acum++;
        }
        if (punto_actual.x + 1 > 0 && punto_actual.y + 1 > 0 &&
            punto_actual.x + 1 < graymax_X && punto_actual.y + 1 < graymax_Y)
        {
            lista_intensidades[acum] = grayImage.at<uchar>(punto_actual.y + 1, punto_actual.x + 1);
            acum++;
        }

        for (int i = 0; i < acum; i++)
        {
            promedio += lista_intensidades[i];
        }
        promedio /= acum;

        if (punto_actual.x - 1 > 0 && punto_actual.y - 1 > 0 &&
            punto_actual.x - 1 < graymax_X && punto_actual.y - 1 < graymax_Y)
        {

            if (std::abs(grayImage.at<uchar>(punto_actual.y - 1, punto_actual.x - 1) - promedio) < rango)
            {
                if (image_segmentated.at<uchar>(punto_actual.y - 1, punto_actual.x - 1) != 255)
                {
                    image_segmentated.at<uchar>(punto_actual.y - 1, punto_actual.x - 1) = 255;
                    image_segmentated.at<uchar>(punto_actual.y - 1, punto_actual.x - 1) = 255;
                    image_segmentated.at<uchar>(punto_actual.y - 1, punto_actual.x - 1) = 255;
                    colaPixeles.push(Point(punto_actual.x - 1, punto_actual.y - 1));
                }
            }
        }
        if (punto_actual.x - 1 > 0 && punto_actual.y > 0 &&
            punto_actual.x - 1 < graymax_X && punto_actual.y < graymax_Y)
        {
            if (std::abs(grayImage.at<uchar>(punto_actual.y, punto_actual.x - 1) - promedio) < rango)
            {
                if (image_segmentated.at<uchar>(punto_actual.y, punto_actual.x - 1) != 255)
                {
                    image_segmentated.at<uchar>(punto_actual.y, punto_actual.x - 1) = 255;
                    image_segmentated.at<uchar>(punto_actual.y, punto_actual.x - 1) = 255;
                    image_segmentated.at<uchar>(punto_actual.y, punto_actual.x - 1) = 255;
                    colaPixeles.push(Point(punto_actual.x - 1, punto_actual.y));
                }
            }
        }

        if (punto_actual.x - 1 > 0 && punto_actual.y + 1 > 0 &&
            punto_actual.x - 1 < graymax_X && punto_actual.y + 1 < graymax_Y)
        {
            if (std::abs(grayImage.at<uchar>(punto_actual.y + 1, punto_actual.x - 1) - promedio) < rango)
            {
                if (image_segmentated.at<uchar>(punto_actual.y + 1, punto_actual.x - 1) != 255)
                {
                    image_segmentated.at<uchar>(punto_actual.y + 1, punto_actual.x - 1) = 255;
                    image_segmentated.at<uchar>(punto_actual.y + 1, punto_actual.x - 1) = 255;
                    image_segmentated.at<uchar>(punto_actual.y + 1, punto_actual.x - 1) = 255;
                    colaPixeles.push(Point(punto_actual.x - 1, punto_actual.y + 1));
                }
            }
        }
        if (punto_actual.x > 0 && punto_actual.y - 1 > 0 &&
            punto_actual.x < graymax_X && punto_actual.y - 1 < graymax_Y)
        {
            if (std::abs(grayImage.at<uchar>(punto_actual.y - 1, punto_actual.x) - promedio) < rango)
            {
                if (image_segmentated.at<uchar>(punto_actual.y - 1, punto_actual.x) != 255)
                {
                    image_segmentated.at<uchar>(punto_actual.y - 1, punto_actual.x) = 255;
                    image_segmentated.at<uchar>(punto_actual.y - 1, punto_actual.x) = 255;
                    image_segmentated.at<uchar>(punto_actual.y - 1, punto_actual.x) = 255;
                    colaPixeles.push(Point(punto_actual.x, punto_actual.y - 1));
                }
            }
        }
        if (punto_actual.x > 0 && punto_actual.y + 1 > 0 &&
            punto_actual.x < graymax_X && punto_actual.y + 1 < graymax_Y)
        {
            if (std::abs(grayImage.at<uchar>(punto_actual.y + 1, punto_actual.x) - promedio) < rango)
            {
                if (image_segmentated.at<uchar>(punto_actual.y + 1, punto_actual.x) != 255)
                {
                    image_segmentated.at<uchar>(punto_actual.y + 1, punto_actual.x) = 255;
                    image_segmentated.at<uchar>(punto_actual.y + 1, punto_actual.x) = 255;
                    image_segmentated.at<uchar>(punto_actual.y + 1, punto_actual.x) = 255;
                    colaPixeles.push(Point(punto_actual.x, punto_actual.y + 1));
                }
            }
        }
        if (punto_actual.x + 1 > 0 && punto_actual.y - 1 > 0 &&
            punto_actual.x + 1 < graymax_X && punto_actual.y - 1 < graymax_Y)
        {
            if (std::abs(grayImage.at<uchar>(punto_actual.y - 1, punto_actual.x + 1) - promedio) < rango)
            {
                if (image_segmentated.at<uchar>(punto_actual.y - 1, punto_actual.x + 1) != 255)
                {
                    image_segmentated.at<uchar>(punto_actual.y - 1, punto_actual.x + 1) = 255;
                    image_segmentated.at<uchar>(punto_actual.y - 1, punto_actual.x + 1) = 255;
                    image_segmentated.at<uchar>(punto_actual.y - 1, punto_actual.x + 1) = 255;
                    colaPixeles.push(Point(punto_actual.x + 1, punto_actual.y - 1));
                }
            }
        }
        if (punto_actual.x + 1 > 0 && punto_actual.y > 0 &&
            punto_actual.x + 1 < graymax_X && punto_actual.y < graymax_Y)
        {
            if (std::abs(grayImage.at<uchar>(punto_actual.y, punto_actual.x + 1) - promedio) < rango)
            {
                if (image_segmentated.at<uchar>(punto_actual.y, punto_actual.x + 1) != 255)
                {
                    image_segmentated.at<uchar>(punto_actual.y, punto_actual.x + 1) = 255;
                    image_segmentated.at<uchar>(punto_actual.y, punto_actual.x + 1) = 255;
                    image_segmentated.at<uchar>(punto_actual.y, punto_actual.x + 1) = 255;
                    colaPixeles.push(Point(punto_actual.x + 1, punto_actual.y));
                }
            }
        }
        if (punto_actual.x + 1 > 0 && punto_actual.y + 1 > 0 &&
            punto_actual.x + 1 < graymax_X && punto_actual.y + 1 < graymax_Y)
        {
            if (std::abs(grayImage.at<uchar>(punto_actual.y + 1, punto_actual.x + 1) - promedio) < rango)
            {
                if (image_segmentated.at<uchar>(punto_actual.y + 1, punto_actual.x + 1) != 255)
                {
                    image_segmentated.at<uchar>(punto_actual.y + 1, punto_actual.x + 1) = 255;
                    image_segmentated.at<uchar>(punto_actual.y + 1, punto_actual.x + 1) = 255;
                    image_segmentated.at<uchar>(punto_actual.y + 1, punto_actual.x + 1) = 255;
                    colaPixeles.push(Point(punto_actual.x + 1, punto_actual.y + 1));
                }
            }
        }

    } while (!colaPixeles.empty());

    image_segmentated;

    return image_segmentated;
}

Mat segmentacion_color(Mat image, int seedX[], int seedY[], int numSeeds, int permisividad)
{
    int max_X = image.cols;
    int max_Y = image.rows;
    Mat image_segmentated = Mat::zeros(max_Y, max_X, CV_8UC3);
    std::queue<Point> colaPixeles;
    //Vec3b Intesidades = image.at<Vec3f>(seedY, seedX);

    for (int i = 0; i < numSeeds; i++)
    {
        colaPixeles.push(Point(seedX[i], seedY[i]));
        image_segmentated.at<Vec3b>(seedY[i], seedX[i])[0] = 255;

        image_segmentated.at<Vec3b>(seedY[i], seedX[i])[1] = 255;

        image_segmentated.at<Vec3b>(seedY[i], seedX[i])[2] = 255;
    }

    do
    {

        Point punto_actual = colaPixeles.front();
        colaPixeles.pop();
        int prom = -1;
        int acum = 0;
        int promedior = 0, promediog = 0, promediob = 0;
        int rango = permisividad;
        int lista_intensidadesr[8], lista_intensidadesg[8], lista_intensidadesb[8];
        if (punto_actual.x - 1 > 0 && punto_actual.y - 1 > 0 &&
            punto_actual.x - 1 < max_X && punto_actual.y - 1 < max_Y)
        {
            lista_intensidadesb[0] = image.at<Vec3b>(punto_actual.y - 1, punto_actual.x - 1)[0];
            lista_intensidadesg[0] = image.at<Vec3b>(punto_actual.y - 1, punto_actual.x - 1)[1];
            lista_intensidadesr[0] = image.at<Vec3b>(punto_actual.y - 1, punto_actual.x - 1)[2];

            acum++;
        }
        if (punto_actual.x - 1 > 0 && punto_actual.y > 0 &&
            punto_actual.x - 1 < max_X && punto_actual.y < max_Y)
        {
            lista_intensidadesb[acum] = image.at<Vec3b>(punto_actual.y, punto_actual.x - 1)[0];
            lista_intensidadesg[acum] = image.at<Vec3b>(punto_actual.y, punto_actual.x - 1)[1];
            lista_intensidadesr[acum] = image.at<Vec3b>(punto_actual.y, punto_actual.x - 1)[2];

            acum++;
        }

        if (punto_actual.x - 1 > 0 && punto_actual.y + 1 > 0 &&
            punto_actual.x - 1 < max_X && punto_actual.y + 1 < max_Y)
        {
            lista_intensidadesb[acum] = image.at<Vec3b>(punto_actual.y + 1, punto_actual.x - 1)[0];
            lista_intensidadesg[acum] = image.at<Vec3b>(punto_actual.y + 1, punto_actual.x - 1)[1];
            lista_intensidadesr[acum] = image.at<Vec3b>(punto_actual.y + 1, punto_actual.x - 1)[2];

            acum++;
        }
        if (punto_actual.x > 0 && punto_actual.y - 1 > 0 &&
            punto_actual.x < max_X && punto_actual.y - 1 < max_Y)
        {
            lista_intensidadesb[acum] = image.at<Vec3b>(punto_actual.y - 1, punto_actual.x)[0];
            lista_intensidadesg[acum] = image.at<Vec3b>(punto_actual.y - 1, punto_actual.x)[1];
            lista_intensidadesr[acum] = image.at<Vec3b>(punto_actual.y - 1, punto_actual.x)[2];

            acum++;
        }
        if (punto_actual.x > 0 && punto_actual.y + 1 > 0 &&
            punto_actual.x < max_X && punto_actual.y + 1 < max_Y)
        {
            lista_intensidadesb[acum] = image.at<Vec3b>(punto_actual.y + 1, punto_actual.x)[0];
            lista_intensidadesg[acum] = image.at<Vec3b>(punto_actual.y + 1, punto_actual.x)[1];
            lista_intensidadesr[acum] = image.at<Vec3b>(punto_actual.y + 1, punto_actual.x)[2];
            acum++;
        }
        if (punto_actual.x + 1 > 0 && punto_actual.y - 1 > 0 &&
            punto_actual.x + 1 < max_X && punto_actual.y - 1 < max_Y)
        {
            lista_intensidadesb[acum] = image.at<Vec3b>(punto_actual.y - 1, punto_actual.x + 1)[0];
            lista_intensidadesg[acum] = image.at<Vec3b>(punto_actual.y - 1, punto_actual.x + 1)[1];
            lista_intensidadesr[acum] = image.at<Vec3b>(punto_actual.y - 1, punto_actual.x + 1)[2];

            acum++;
        }
        if (punto_actual.x + 1 > 0 && punto_actual.y > 0 &&
            punto_actual.x + 1 < max_X && punto_actual.y < max_Y)
        {
            lista_intensidadesb[acum] = image.at<Vec3b>(punto_actual.y, punto_actual.x + 1)[0];
            lista_intensidadesg[acum] = image.at<Vec3b>(punto_actual.y, punto_actual.x + 1)[1];
            lista_intensidadesr[acum] = image.at<Vec3b>(punto_actual.y, punto_actual.x + 1)[2];
            acum++;
        }
        if (punto_actual.x + 1 > 0 && punto_actual.y + 1 > 0 &&
            punto_actual.x + 1 < max_X && punto_actual.y + 1 < max_Y)
        {
            lista_intensidadesb[acum] = image.at<Vec3b>(punto_actual.y + 1, punto_actual.x + 1)[0];
            lista_intensidadesg[acum] = image.at<Vec3b>(punto_actual.y + 1, punto_actual.x + 1)[1];
            lista_intensidadesr[acum] = image.at<Vec3b>(punto_actual.y + 1, punto_actual.x + 1)[2];

            acum++;
        }

        //Promedio para c/u
        for (int i = 0; i < acum; i++)
        {
            promedior += lista_intensidadesr[i];
            promediog += lista_intensidadesg[i];
            promediob += lista_intensidadesb[i];
        }
        promedior /= acum;
        promediog /= acum;
        promediob /= acum;
        if (punto_actual.x - 1 > 0 && punto_actual.y - 1 > 0 &&
            punto_actual.x - 1 < max_X && punto_actual.y - 1 < max_Y)
        {

            if (std::abs(image.at<Vec3b>(punto_actual.y - 1, punto_actual.x - 1)[0] - promediob) < rango &&
                std::abs(image.at<Vec3b>(punto_actual.y - 1, punto_actual.x - 1)[1] - promediog) < rango &&
                std::abs(image.at<Vec3b>(punto_actual.y - 1, punto_actual.x - 1)[2] - promedior) < rango)
            {
                if (image_segmentated.at<Vec3b>(punto_actual.y - 1, punto_actual.x - 1)[0] != 255)
                {
                    image_segmentated.at<Vec3b>(punto_actual.y - 1, punto_actual.x - 1)[0] = 255;
                    image_segmentated.at<Vec3b>(punto_actual.y - 1, punto_actual.x - 1)[1] = 255;
                    image_segmentated.at<Vec3b>(punto_actual.y - 1, punto_actual.x - 1)[2] = 255;
                    colaPixeles.push(Point(punto_actual.x - 1, punto_actual.y - 1));
                }
            }
        }
        if (punto_actual.x - 1 > 0 && punto_actual.y > 0 &&
            punto_actual.x - 1 < max_X && punto_actual.y < max_Y)
        {
            if (std::abs(image.at<Vec3b>(punto_actual.y, punto_actual.x - 1)[0] - promediob) < rango &&
                std::abs(image.at<Vec3b>(punto_actual.y, punto_actual.x - 1)[1] - promediog) < rango &&
                std::abs(image.at<Vec3b>(punto_actual.y, punto_actual.x - 1)[2] - promedior) < rango)
            {
                if (image_segmentated.at<Vec3b>(punto_actual.y, punto_actual.x - 1)[0] != 255)
                {
                    image_segmentated.at<Vec3b>(punto_actual.y, punto_actual.x - 1)[0] = 255;
                    image_segmentated.at<Vec3b>(punto_actual.y, punto_actual.x - 1)[1] = 255;
                    image_segmentated.at<Vec3b>(punto_actual.y, punto_actual.x - 1)[2] = 255;
                    colaPixeles.push(Point(punto_actual.x - 1, punto_actual.y));
                }
            }
        }

        if (punto_actual.x - 1 > 0 && punto_actual.y + 1 > 0 &&
            punto_actual.x - 1 < max_X && punto_actual.y + 1 < max_Y)
        {
            if (std::abs(image.at<Vec3b>(punto_actual.y + 1, punto_actual.x - 1)[0] - promediob) < rango &&
                std::abs(image.at<Vec3b>(punto_actual.y + 1, punto_actual.x - 1)[1] - promediog) < rango &&
                std::abs(image.at<Vec3b>(punto_actual.y + 1, punto_actual.x - 1)[2] - promedior) < rango

            )
            {
                if (image_segmentated.at<Vec3b>(punto_actual.y + 1, punto_actual.x - 1)[0] != 255)
                {
                    image_segmentated.at<Vec3b>(punto_actual.y + 1, punto_actual.x - 1)[0] = 255;
                    image_segmentated.at<Vec3b>(punto_actual.y + 1, punto_actual.x - 1)[1] = 255;
                    image_segmentated.at<Vec3b>(punto_actual.y + 1, punto_actual.x - 1)[2] = 255;
                    colaPixeles.push(Point(punto_actual.x - 1, punto_actual.y + 1));
                }
            }
        }
        if (punto_actual.x > 0 && punto_actual.y - 1 > 0 &&
            punto_actual.x < max_X && punto_actual.y - 1 < max_Y)
        {
            if (std::abs(image.at<Vec3b>(punto_actual.y - 1, punto_actual.x)[0] - promediob) < rango &&
                std::abs(image.at<Vec3b>(punto_actual.y - 1, punto_actual.x)[1] - promediog) < rango &&
                std::abs(image.at<Vec3b>(punto_actual.y - 1, punto_actual.x)[2] - promedior) < rango)
            {
                if (image_segmentated.at<Vec3b>(punto_actual.y - 1, punto_actual.x)[0] != 255)
                {
                    image_segmentated.at<Vec3b>(punto_actual.y - 1, punto_actual.x)[0] = 255;
                    image_segmentated.at<Vec3b>(punto_actual.y - 1, punto_actual.x)[1] = 255;
                    image_segmentated.at<Vec3b>(punto_actual.y - 1, punto_actual.x)[2] = 255;
                    colaPixeles.push(Point(punto_actual.x, punto_actual.y - 1));
                }
            }
        }
        if (punto_actual.x > 0 && punto_actual.y + 1 > 0 &&
            punto_actual.x < max_X && punto_actual.y + 1 < max_Y)
        {
            if (std::abs(image.at<Vec3b>(punto_actual.y + 1, punto_actual.x)[0] - promediob) < rango &&
                std::abs(image.at<Vec3b>(punto_actual.y + 1, punto_actual.x)[1] - promediog) < rango &&
                std::abs(image.at<Vec3b>(punto_actual.y + 1, punto_actual.x)[2] - promedior) < rango)
            {
                if (image_segmentated.at<Vec3b>(punto_actual.y + 1, punto_actual.x)[0] != 255)
                {
                    image_segmentated.at<Vec3b>(punto_actual.y + 1, punto_actual.x)[0] = 255;
                    image_segmentated.at<Vec3b>(punto_actual.y + 1, punto_actual.x)[1] = 255;
                    image_segmentated.at<Vec3b>(punto_actual.y + 1, punto_actual.x)[2] = 255;
                    colaPixeles.push(Point(punto_actual.x, punto_actual.y + 1));
                }
            }
        }
        if (punto_actual.x + 1 > 0 && punto_actual.y - 1 > 0 &&
            punto_actual.x + 1 < max_X && punto_actual.y - 1 < max_Y)
        {
            if (std::abs(image.at<Vec3b>(punto_actual.y - 1, punto_actual.x + 1)[0] - promediob) < rango &&
                std::abs(image.at<Vec3b>(punto_actual.y - 1, punto_actual.x + 1)[1] - promediog) < rango &&
                std::abs(image.at<Vec3b>(punto_actual.y - 1, punto_actual.x + 1)[2] - promedior) < rango

            )
            {
                if (image_segmentated.at<Vec3b>(punto_actual.y - 1, punto_actual.x + 1)[0] != 255)
                {
                    image_segmentated.at<Vec3b>(punto_actual.y - 1, punto_actual.x + 1)[0] = 255;
                    image_segmentated.at<Vec3b>(punto_actual.y - 1, punto_actual.x + 1)[1] = 255;
                    image_segmentated.at<Vec3b>(punto_actual.y - 1, punto_actual.x + 1)[2] = 255;
                    colaPixeles.push(Point(punto_actual.x + 1, punto_actual.y - 1));
                }
            }
        }
        if (punto_actual.x + 1 > 0 && punto_actual.y > 0 &&
            punto_actual.x + 1 < max_X && punto_actual.y < max_Y)
        {
            if (std::abs(image.at<Vec3b>(punto_actual.y, punto_actual.x + 1)[0] - promediob) < rango &&
                std::abs(image.at<Vec3b>(punto_actual.y, punto_actual.x + 1)[1] - promediog) < rango &&
                std::abs(image.at<Vec3b>(punto_actual.y, punto_actual.x + 1)[2] - promedior) < rango

            )
            {
                if (image_segmentated.at<Vec3b>(punto_actual.y, punto_actual.x + 1)[0] != 255)
                {
                    image_segmentated.at<Vec3b>(punto_actual.y, punto_actual.x + 1)[0] = 255;
                    image_segmentated.at<Vec3b>(punto_actual.y, punto_actual.x + 1)[1] = 255;
                    image_segmentated.at<Vec3b>(punto_actual.y, punto_actual.x + 1)[2] = 255;
                    colaPixeles.push(Point(punto_actual.x + 1, punto_actual.y));
                }
            }
        }
        if (punto_actual.x + 1 > 0 && punto_actual.y + 1 > 0 &&
            punto_actual.x + 1 < max_X && punto_actual.y + 1 < max_Y)
        {
            if (std::abs(image.at<Vec3b>(punto_actual.y + 1, punto_actual.x + 1)[0] - promediob) < rango &&
                std::abs(image.at<Vec3b>(punto_actual.y + 1, punto_actual.x + 1)[1] - promediog) < rango &&
                std::abs(image.at<Vec3b>(punto_actual.y + 1, punto_actual.x + 1)[2] - promedior) < rango

            )
            {
                if (image_segmentated.at<Vec3b>(punto_actual.y + 1, punto_actual.x + 1)[0] != 255)
                {
                    image_segmentated.at<Vec3b>(punto_actual.y + 1, punto_actual.x + 1)[0] = 255;
                    image_segmentated.at<Vec3b>(punto_actual.y + 1, punto_actual.x + 1)[1] = 255;
                    image_segmentated.at<Vec3b>(punto_actual.y + 1, punto_actual.x + 1)[2] = 255;
                    colaPixeles.push(Point(punto_actual.x + 1, punto_actual.y + 1));
                }
            }
        }

    } while (!colaPixeles.empty());

    return image_segmentated;
}