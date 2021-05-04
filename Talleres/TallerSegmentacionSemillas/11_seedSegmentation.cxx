#include "opencv2/imgproc.hpp"
#include "opencv2/imgcodecs.hpp"
#include "opencv2/highgui.hpp"
#include <iostream>
#include <string.h>
#include <ctime>

using namespace cv;

int main(int argc, char const *argv[])
{
    srand((unsigned)time(0));
    //PASOS DEL ALGORITMO
    //1: Leer la imagen (Se pasa por parametros, se puede recibir a color.)
    //2: Leer las semillas (Por parametros, o aleatoriamente)
    //3:

    //Verificación de Comandos
    // forma ideal de ejecutar : ./11_seedSegmentation <image_file> <r (random seed) / s (set seed)>
    //                                 <a (average) / v (variance)> <N° of seeds>
    //                            [<x coordinate1> <y coordinate1> <x coordinate2> <y coordinate2> (ETC)]

    if (argc < 5)
    {
        std::cerr << "Usage: " << argv[0] << "image_file N°_of_seeds r(random seed)/s(set seed) a(average)/v(variance) (x_coordinate1 y_coordinate1 x_coordinate2 y_coordinate2 (ETC))" << std::endl;
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

    if (strcmp(argv[3], "r") == 0)
    {
        for (int i = 0; i < numberSeeds; i++)
        {
            seedX[i] = std::rand() % (image.cols) + 0;
            seedY[i] = std::rand() % (image.rows) + 0;
        }
        for (int i = 0; i < numberSeeds; i++)
        {
            std::cout << "seedX: " << seedX[i] << std::endl;
            std::cout << "seedy: " << seedY[i] << std::endl;
        }
    }
    else if (strcmp(argv[3], "s") == 0)
    {
        int i, j;
        if (argc == (5 + (numberSeeds * 2)))
        {
            for (i = 0, j = 0; i < numberSeeds; i++, j += 2)
            {
                seedX[i] = atoi(argv[5 + j]);
                seedY[i] = atoi(argv[6 + j]);
            }
            for (int i = 0; i < numberSeeds; i++)
            {
                std::cout << "seedX: " << seedX[i] << std::endl;
                std::cout << "seedy: " << seedY[i] << std::endl;
            }
        }
        else
        {
            std::cerr << "Error: Numbers of seed doesnt match" << std::endl;
            return (-1);
        }
    }
}
