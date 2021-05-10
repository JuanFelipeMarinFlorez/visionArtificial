#include "opencv2/imgproc.hpp"
#include "opencv2/imgcodecs.hpp"
#include "opencv2/highgui.hpp"
#include <iostream>
#include <string.h>
#include <ctime>
#include <queue>

using namespace cv;

Mat segmentacion(Mat image, int seedX, int seedY);
Mat segmentacion_color (Mat image, int seedX[], int seedY[], int numSeeds);

int main(int argc, char const *argv[])
{
    srand((unsigned)time(0));
    //PASOS DEL ALGORITMO
    //1: Leer la imagen (Se pasa por parametros, se puede recibir a color.)
    //2: Leer las semillas (Por parametros, o aleatoriamente)
    //3:

    //Verificación de Comandos
    // forma ideal de ejecutar : ./11_seedSegmentation  <image_file> <N° of seeds>
    //                                <r (random seed) / s (set seed)> <a (average) / v (variance)>
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
        // for (int i = 0; i < numberSeeds; i++)
        // {
        //     std::cout << "seedX: " << seedX[i] << std::endl;
        //     std::cout << "seedy: " << seedY[i] << std::endl;
        // }
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

    //----------------------------------------------------------------------
    // Llamado a funcion de segmentar:
    Mat prueba = segmentacion_color(image, seedX, seedY, numberSeeds);
    imwrite("solucion.png",prueba);
}

Mat segmentacion(Mat image, int seedX, int seedY)
{
    Mat grayImage;
    cvtColor(image, grayImage, COLOR_BGR2GRAY);
    Mat image_segmentated = Mat::zeros(image.rows, image.cols, CV_8UC1);
    std::queue<Point> colaPixeles;
    //Vec3b Intesidades = image.at<Vec3f>(seedY, seedX);
    colaPixeles.push(Point(seedX, seedY));
    image_segmentated.at<Vec3b>(seedY, seedX)[0] = 255;
    do
    {   
       
        Point punto_actual = colaPixeles.front();
        colaPixeles.pop();
        int prom = -1;
        int acum=0;
        int promedio=0;
        int rango=8;
        int lista_intensidades[8];
        if (punto_actual.x -1 > 0 && punto_actual.y -1 > 0 && 
            punto_actual.x -1 < grayImage.rows && punto_actual.y -1 < grayImage.cols)
        {
            lista_intensidades[0] = grayImage.at<Vec3b>(punto_actual.y - 1, punto_actual.x - 1)[0];
            acum++;
        }
        if (punto_actual.x -1 > 0 && punto_actual.y  > 0 && 
            punto_actual.x -1 < grayImage.rows && punto_actual.y < grayImage.cols)
        {
            lista_intensidades[acum] = grayImage.at<Vec3b>(punto_actual.y , punto_actual.x - 1)[0];
            acum++;
        }

        if (punto_actual.x -1 > 0 && punto_actual.y +1 > 0 && 
            punto_actual.x -1 < grayImage.rows && punto_actual.y +1< grayImage.cols)
        {
            lista_intensidades[acum] = grayImage.at<Vec3b>(punto_actual.y +1, punto_actual.x - 1)[0];
            acum++;
        }
        if (punto_actual.x  > 0 && punto_actual.y -1  > 0 && 
            punto_actual.x  < grayImage.rows && punto_actual.y -1 < grayImage.cols)
        {
            lista_intensidades[acum] = grayImage.at<Vec3b>(punto_actual.y -1, punto_actual.x )[0];
            acum++;
        }
        if (punto_actual.x > 0 && punto_actual.y +1 > 0 && 
            punto_actual.x  < grayImage.rows && punto_actual.y +1< grayImage.cols)
        {
            lista_intensidades[acum] = grayImage.at<Vec3b>(punto_actual.y +1, punto_actual.x )[0];
            acum++;
        }
        if (punto_actual.x +1 > 0 && punto_actual.y -1 > 0 && 
            punto_actual.x +1 < grayImage.rows && punto_actual.y -1< grayImage.cols)
        {
            lista_intensidades[acum] = grayImage.at<Vec3b>(punto_actual.y -1, punto_actual.x +1)[0];
            acum++;
        }
        if (punto_actual.x +1 > 0 && punto_actual.y  > 0 && 
            punto_actual.x +1 < grayImage.rows && punto_actual.y < grayImage.cols)
        {
            lista_intensidades[acum] = grayImage.at<Vec3b>(punto_actual.y , punto_actual.x +1)[0];
            acum++;
        }
        if (punto_actual.x +1 > 0 && punto_actual.y +1 > 0 && 
            punto_actual.x +1 < grayImage.rows && punto_actual.y +1 < grayImage.cols)
        {
            lista_intensidades[acum] = grayImage.at<Vec3b>(punto_actual.y +1, punto_actual.x +1)[0];
            acum++;
        }

        for(int i=0; i<acum; i++){
           promedio+=lista_intensidades[i]; 
        }
        promedio/=acum;


        if (punto_actual.x -1 > 0 && punto_actual.y -1 > 0 && 
            punto_actual.x -1 < grayImage.rows && punto_actual.y -1 < grayImage.cols)
        {

            if( std::abs(grayImage.at<Vec3b>(punto_actual.y - 1, punto_actual.x - 1)[0] - promedio) < rango  ){
                if(image_segmentated.at<Vec3b>(punto_actual.y - 1, punto_actual.x - 1)[0]!= 255){
                    image_segmentated.at<Vec3b>(punto_actual.y - 1, punto_actual.x - 1)[0]= 255;
                    image_segmentated.at<Vec3b>(punto_actual.y - 1, punto_actual.x - 1)[1]= 255;
                    image_segmentated.at<Vec3b>(punto_actual.y - 1, punto_actual.x - 1)[2]= 255;
                    colaPixeles.push(Point( punto_actual.x - 1,punto_actual.y - 1 ));
                }
                
            }
        }
        if (punto_actual.x -1 > 0 && punto_actual.y  > 0 && 
            punto_actual.x -1 < grayImage.rows && punto_actual.y < grayImage.cols)
        {
            if( std::abs(grayImage.at<Vec3b>(punto_actual.y , punto_actual.x - 1)[0] - promedio) < rango  ){
                if(image_segmentated.at<Vec3b>(punto_actual.y , punto_actual.x - 1)[0]!= 255){
                    image_segmentated.at<Vec3b>(punto_actual.y , punto_actual.x - 1)[0]= 255;
                    image_segmentated.at<Vec3b>(punto_actual.y , punto_actual.x - 1)[1]= 255;
                    image_segmentated.at<Vec3b>(punto_actual.y , punto_actual.x - 1)[2]= 255;
                    colaPixeles.push(Point( punto_actual.x - 1,punto_actual.y  ));
                }
                
            }
        }

        if (punto_actual.x -1 > 0 && punto_actual.y +1 > 0 && 
            punto_actual.x -1 < grayImage.rows && punto_actual.y +1< grayImage.cols)
        {
            if( std::abs(grayImage.at<Vec3b>(punto_actual.y + 1, punto_actual.x - 1)[0] - promedio) < rango  ){
                if(image_segmentated.at<Vec3b>(punto_actual.y + 1, punto_actual.x - 1)[0]!= 255){
                    image_segmentated.at<Vec3b>(punto_actual.y + 1, punto_actual.x - 1)[0]= 255;
                    image_segmentated.at<Vec3b>(punto_actual.y + 1, punto_actual.x - 1)[1]= 255;
                    image_segmentated.at<Vec3b>(punto_actual.y + 1, punto_actual.x - 1)[2]= 255;
                    colaPixeles.push(Point( punto_actual.x - 1,punto_actual.y + 1 ));
                }
                
            }
        }
        if (punto_actual.x  > 0 && punto_actual.y -1  > 0 && 
            punto_actual.x  < grayImage.rows && punto_actual.y -1 < grayImage.cols)
        {
           if( std::abs(grayImage.at<Vec3b>(punto_actual.y - 1, punto_actual.x )[0] - promedio) < rango ){
                if(image_segmentated.at<Vec3b>(punto_actual.y - 1, punto_actual.x )[0]!= 255){
                    image_segmentated.at<Vec3b>(punto_actual.y - 1, punto_actual.x )[0]= 255;
                     image_segmentated.at<Vec3b>(punto_actual.y - 1, punto_actual.x )[1]= 255;
                      image_segmentated.at<Vec3b>(punto_actual.y - 1, punto_actual.x )[2]= 255;
                    colaPixeles.push(Point( punto_actual.x ,punto_actual.y - 1 ));
                }
                    
            }
        }
        if (punto_actual.x > 0 && punto_actual.y +1 > 0 && 
            punto_actual.x  < grayImage.rows && punto_actual.y +1< grayImage.cols)
        {
            if( std::abs(grayImage.at<Vec3b>(punto_actual.y + 1, punto_actual.x )[0] - promedio) <rango  ){
                if(image_segmentated.at<Vec3b>(punto_actual.y + 1, punto_actual.x )[0]!= 255){
                    image_segmentated.at<Vec3b>(punto_actual.y + 1, punto_actual.x )[0]= 255;
                    image_segmentated.at<Vec3b>(punto_actual.y + 1, punto_actual.x )[1]= 255;
                    image_segmentated.at<Vec3b>(punto_actual.y + 1, punto_actual.x )[2]= 255;
                    colaPixeles.push(Point( punto_actual.x ,punto_actual.y + 1 ));
                }
            }
        }
        if (punto_actual.x +1 > 0 && punto_actual.y -1 > 0 && 
            punto_actual.x +1 < grayImage.rows && punto_actual.y -1< grayImage.cols)
        {
            if( std::abs(grayImage.at<Vec3b>(punto_actual.y - 1, punto_actual.x + 1)[0] - promedio) <rango  ){
                if(image_segmentated.at<Vec3b>(punto_actual.y - 1, punto_actual.x + 1)[0]!= 255){
                    image_segmentated.at<Vec3b>(punto_actual.y - 1, punto_actual.x + 1)[0]= 255;
                     image_segmentated.at<Vec3b>(punto_actual.y - 1, punto_actual.x + 1)[1]= 255;
                      image_segmentated.at<Vec3b>(punto_actual.y - 1, punto_actual.x + 1)[2]= 255;
                    colaPixeles.push(Point( punto_actual.x + 1,punto_actual.y - 1 ));
                }

                
            }
        }
        if (punto_actual.x +1 > 0 && punto_actual.y  > 0 && 
            punto_actual.x +1 < grayImage.rows && punto_actual.y < grayImage.cols)
        {
            if( std::abs(grayImage.at<Vec3b>(punto_actual.y , punto_actual.x + 1)[0] - promedio) < rango  ){
                if(image_segmentated.at<Vec3b>(punto_actual.y , punto_actual.x + 1)[0]!= 255){
                    image_segmentated.at<Vec3b>(punto_actual.y , punto_actual.x + 1)[0]= 255;
                    image_segmentated.at<Vec3b>(punto_actual.y , punto_actual.x + 1)[1]= 255;
                    image_segmentated.at<Vec3b>(punto_actual.y , punto_actual.x + 1)[2]= 255;
                    colaPixeles.push(Point( punto_actual.x + 1,punto_actual.y  ));
                }
            }
        }
        if (punto_actual.x +1 > 0 && punto_actual.y +1 > 0 && 
            punto_actual.x +1 < grayImage.rows && punto_actual.y +1 < grayImage.cols)
        {
            if( std::abs(grayImage.at<Vec3b>(punto_actual.y + 1, punto_actual.x + 1)[0] - promedio) < rango ){
                if(image_segmentated.at<Vec3b>(punto_actual.y + 1, punto_actual.x + 1)[0]!= 255){
                    image_segmentated.at<Vec3b>(punto_actual.y + 1, punto_actual.x + 1)[0]= 255;
                    image_segmentated.at<Vec3b>(punto_actual.y + 1, punto_actual.x + 1)[1]= 255;
                    image_segmentated.at<Vec3b>(punto_actual.y + 1, punto_actual.x + 1)[2]= 255;
                    colaPixeles.push(Point( punto_actual.x + 1,punto_actual.y + 1 ));
                }
                
            }
        }
        

        
    } while ( !colaPixeles.empty());

    Mat final = image_segmentated - grayImage;

    return final;
}

Mat segmentacion_color (Mat image, int seedX[], int seedY[], int numSeeds)
{
    Mat image_segmentated = Mat::zeros(image.rows, image.cols, CV_8UC1);
    std::queue<Point> colaPixeles;
    //Vec3b Intesidades = image.at<Vec3f>(seedY, seedX);

    for (int i=0; i < numSeeds; i++)
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
        int acum=0;
        int promedior=0, promediog=0, promediob=0;
        int rango=8;
        int lista_intensidadesr[8], lista_intensidadesg[8], lista_intensidadesb[8];
        if (punto_actual.x -1 > 0 && punto_actual.y -1 > 0 && 
            punto_actual.x -1 < image.rows && punto_actual.y -1 < image.cols)
        {
            lista_intensidadesb[0] = image.at<Vec3b>(punto_actual.y - 1, punto_actual.x - 1)[0];
            lista_intensidadesg[0] = image.at<Vec3b>(punto_actual.y - 1, punto_actual.x - 1)[1];
            lista_intensidadesr[0] = image.at<Vec3b>(punto_actual.y - 1, punto_actual.x - 1)[2];

            acum++;
        }
        if (punto_actual.x -1 > 0 && punto_actual.y  > 0 && 
            punto_actual.x -1 < image.rows && punto_actual.y < image.cols)
        {
            lista_intensidadesb[acum] = image.at<Vec3b>(punto_actual.y , punto_actual.x - 1)[0];
            lista_intensidadesg[acum] = image.at<Vec3b>(punto_actual.y , punto_actual.x - 1)[1];
            lista_intensidadesr[acum] = image.at<Vec3b>(punto_actual.y , punto_actual.x - 1)[2];

            acum++;
        }

        if (punto_actual.x -1 > 0 && punto_actual.y +1 > 0 && 
            punto_actual.x -1 < image.rows && punto_actual.y +1< image.cols)
        {
            lista_intensidadesb[acum] = image.at<Vec3b>(punto_actual.y +1, punto_actual.x - 1)[0];
            lista_intensidadesg[acum] = image.at<Vec3b>(punto_actual.y +1, punto_actual.x - 1)[1];
            lista_intensidadesr[acum] = image.at<Vec3b>(punto_actual.y +1, punto_actual.x - 1)[2];

            acum++;
        }
        if (punto_actual.x  > 0 && punto_actual.y -1  > 0 && 
            punto_actual.x  < image.rows && punto_actual.y -1 < image.cols)
        {
            lista_intensidadesb[acum] = image.at<Vec3b>(punto_actual.y -1, punto_actual.x )[0];
            lista_intensidadesg[acum] = image.at<Vec3b>(punto_actual.y -1, punto_actual.x )[1];
            lista_intensidadesr[acum] = image.at<Vec3b>(punto_actual.y -1, punto_actual.x )[2];

            acum++;
        }
        if (punto_actual.x > 0 && punto_actual.y +1 > 0 && 
            punto_actual.x  < image.rows && punto_actual.y +1< image.cols)
        {
            lista_intensidadesb[acum] = image.at<Vec3b>(punto_actual.y +1, punto_actual.x )[0];
            lista_intensidadesg[acum] = image.at<Vec3b>(punto_actual.y +1, punto_actual.x )[1];
            lista_intensidadesr[acum] = image.at<Vec3b>(punto_actual.y +1, punto_actual.x )[2];
            acum++;
        }
        if (punto_actual.x +1 > 0 && punto_actual.y -1 > 0 && 
            punto_actual.x +1 < image.rows && punto_actual.y -1< image.cols)
        {
            lista_intensidadesb[acum] = image.at<Vec3b>(punto_actual.y -1, punto_actual.x +1)[0];
            lista_intensidadesg[acum] = image.at<Vec3b>(punto_actual.y -1, punto_actual.x +1)[1];
            lista_intensidadesr[acum] = image.at<Vec3b>(punto_actual.y -1, punto_actual.x +1)[2];

            acum++;
        }
        if (punto_actual.x +1 > 0 && punto_actual.y  > 0 && 
            punto_actual.x +1 < image.rows && punto_actual.y < image.cols)
        {
            lista_intensidadesb[acum] = image.at<Vec3b>(punto_actual.y , punto_actual.x +1)[0];
            lista_intensidadesg[acum] = image.at<Vec3b>(punto_actual.y , punto_actual.x +1)[1];
            lista_intensidadesr[acum] = image.at<Vec3b>(punto_actual.y , punto_actual.x +1)[2];
            acum++;
        }
        if (punto_actual.x +1 > 0 && punto_actual.y +1 > 0 && 
            punto_actual.x +1 < image.rows && punto_actual.y +1 < image.cols)
        {
            lista_intensidadesb[acum] = image.at<Vec3b>(punto_actual.y +1, punto_actual.x +1)[0];
            lista_intensidadesg[acum] = image.at<Vec3b>(punto_actual.y +1, punto_actual.x +1)[1];
            lista_intensidadesr[acum] = image.at<Vec3b>(punto_actual.y +1, punto_actual.x +1)[2];

            acum++;
        }
        
        //Promedio para c/u
        for(int i=0; i<acum; i++){
           promedior+=lista_intensidadesr[i]; 
           promediog+=lista_intensidadesg[i]; 
           promediob+=lista_intensidadesb[i]; 
        }
        promedior/=acum;
        promediog/=acum;
        promediob/=acum;

        if (punto_actual.x -1 > 0 && punto_actual.y -1 > 0 && 
            punto_actual.x -1 < image.rows && punto_actual.y -1 < image.cols)
        {

            if( std::abs(image.at<Vec3b>(punto_actual.y - 1, punto_actual.x - 1)[0] - promediob) < rango && 
                std::abs(image.at<Vec3b>(punto_actual.y - 1, punto_actual.x - 1)[1] - promediog) < rango &&
                std::abs(image.at<Vec3b>(punto_actual.y - 1, punto_actual.x - 1)[2] - promedior) < rango
            ){
                if(image_segmentated.at<Vec3b>(punto_actual.y - 1, punto_actual.x - 1)[0]!= 255){
                    image_segmentated.at<Vec3b>(punto_actual.y - 1, punto_actual.x - 1)[0]= 255;
                    image_segmentated.at<Vec3b>(punto_actual.y - 1, punto_actual.x - 1)[1]= 255;
                    image_segmentated.at<Vec3b>(punto_actual.y - 1, punto_actual.x - 1)[2]= 255;
                    colaPixeles.push(Point( punto_actual.x - 1,punto_actual.y - 1 ));
                }
                
            }
        }
        if (punto_actual.x -1 > 0 && punto_actual.y  > 0 && 
            punto_actual.x -1 < image.rows && punto_actual.y < image.cols)
        {
            if( std::abs(image.at<Vec3b>(punto_actual.y , punto_actual.x - 1)[0] - promediob) < rango &&
                std::abs(image.at<Vec3b>(punto_actual.y , punto_actual.x - 1)[1] - promediog) < rango &&
                std::abs(image.at<Vec3b>(punto_actual.y , punto_actual.x - 1)[2] - promedior) < rango 
             ){
                if(image_segmentated.at<Vec3b>(punto_actual.y , punto_actual.x - 1)[0]!= 255){
                    image_segmentated.at<Vec3b>(punto_actual.y , punto_actual.x - 1)[0]= 255;
                    image_segmentated.at<Vec3b>(punto_actual.y , punto_actual.x - 1)[1]= 255;
                    image_segmentated.at<Vec3b>(punto_actual.y , punto_actual.x - 1)[2]= 255;
                    colaPixeles.push(Point( punto_actual.x - 1,punto_actual.y  ));
                }
                
            }
        }

        if (punto_actual.x -1 > 0 && punto_actual.y +1 > 0 && 
            punto_actual.x -1 < image.rows && punto_actual.y +1< image.cols)
        {
            if( std::abs(image.at<Vec3b>(punto_actual.y + 1, punto_actual.x - 1)[0] - promediob) < rango &&
                std::abs(image.at<Vec3b>(punto_actual.y + 1, punto_actual.x - 1)[1] - promediog) < rango &&
                std::abs(image.at<Vec3b>(punto_actual.y + 1, punto_actual.x - 1)[2] - promedior) < rango  
            
            ){
                if(image_segmentated.at<Vec3b>(punto_actual.y + 1, punto_actual.x - 1)[0]!= 255){
                    image_segmentated.at<Vec3b>(punto_actual.y + 1, punto_actual.x - 1)[0]= 255;
                    image_segmentated.at<Vec3b>(punto_actual.y + 1, punto_actual.x - 1)[1]= 255;
                    image_segmentated.at<Vec3b>(punto_actual.y + 1, punto_actual.x - 1)[2]= 255;
                    colaPixeles.push(Point( punto_actual.x - 1,punto_actual.y + 1 ));
                }
                
            }
        }
        if (punto_actual.x  > 0 && punto_actual.y -1  > 0 && 
            punto_actual.x  < image.rows && punto_actual.y -1 < image.cols)
        {
           if(  std::abs(image.at<Vec3b>(punto_actual.y - 1, punto_actual.x )[0] - promediob) < rango &&
                std::abs(image.at<Vec3b>(punto_actual.y - 1, punto_actual.x )[1] - promediog) < rango &&
                std::abs(image.at<Vec3b>(punto_actual.y - 1, punto_actual.x )[2] - promedior) < rango 
           ){
                if(image_segmentated.at<Vec3b>(punto_actual.y - 1, punto_actual.x )[0]!= 255){
                    image_segmentated.at<Vec3b>(punto_actual.y - 1, punto_actual.x )[0]= 255;
                     image_segmentated.at<Vec3b>(punto_actual.y - 1, punto_actual.x )[1]= 255;
                      image_segmentated.at<Vec3b>(punto_actual.y - 1, punto_actual.x )[2]= 255;
                    colaPixeles.push(Point( punto_actual.x ,punto_actual.y - 1 ));
                }
                    
            }
        }
        if (punto_actual.x > 0 && punto_actual.y +1 > 0 && 
            punto_actual.x  < image.rows && punto_actual.y +1< image.cols)
        {
            if( std::abs(image.at<Vec3b>(punto_actual.y + 1, punto_actual.x )[0] - promediob) <rango &&
                std::abs(image.at<Vec3b>(punto_actual.y + 1, punto_actual.x )[1] - promediog) <rango &&
                std::abs(image.at<Vec3b>(punto_actual.y + 1, punto_actual.x )[2] - promedior) <rango  
                ){
                if(image_segmentated.at<Vec3b>(punto_actual.y + 1, punto_actual.x )[0]!= 255){
                    image_segmentated.at<Vec3b>(punto_actual.y + 1, punto_actual.x )[0]= 255;
                    image_segmentated.at<Vec3b>(punto_actual.y + 1, punto_actual.x )[1]= 255;
                    image_segmentated.at<Vec3b>(punto_actual.y + 1, punto_actual.x )[2]= 255;
                    colaPixeles.push(Point( punto_actual.x ,punto_actual.y + 1 ));
                }
            }
        }
        if (punto_actual.x +1 > 0 && punto_actual.y -1 > 0 && 
            punto_actual.x +1 < image.rows && punto_actual.y -1< image.cols)
        {
            if( std::abs(image.at<Vec3b>(punto_actual.y - 1, punto_actual.x + 1)[0] - promediob) <rango &&
                std::abs(image.at<Vec3b>(punto_actual.y - 1, punto_actual.x + 1)[1] - promediog) <rango &&
                std::abs(image.at<Vec3b>(punto_actual.y - 1, punto_actual.x + 1)[2] - promedior) <rango 
            
            ){
                if(image_segmentated.at<Vec3b>(punto_actual.y - 1, punto_actual.x + 1)[0]!= 255){
                    image_segmentated.at<Vec3b>(punto_actual.y - 1, punto_actual.x + 1)[0]= 255;
                     image_segmentated.at<Vec3b>(punto_actual.y - 1, punto_actual.x + 1)[1]= 255;
                      image_segmentated.at<Vec3b>(punto_actual.y - 1, punto_actual.x + 1)[2]= 255;
                    colaPixeles.push(Point( punto_actual.x + 1,punto_actual.y - 1 ));
                }

                
            }
        }
        if (punto_actual.x +1 > 0 && punto_actual.y  > 0 && 
            punto_actual.x +1 < image.rows && punto_actual.y < image.cols)
        {
            if( std::abs(image.at<Vec3b>(punto_actual.y , punto_actual.x + 1)[0] - promediob) < rango &&
                std::abs(image.at<Vec3b>(punto_actual.y , punto_actual.x + 1)[1] - promediog) < rango &&
                std::abs(image.at<Vec3b>(punto_actual.y , punto_actual.x + 1)[2] - promedior) < rango  
            
            ){
                if(image_segmentated.at<Vec3b>(punto_actual.y , punto_actual.x + 1)[0]!= 255){
                    image_segmentated.at<Vec3b>(punto_actual.y , punto_actual.x + 1)[0]= 255;
                    image_segmentated.at<Vec3b>(punto_actual.y , punto_actual.x + 1)[1]= 255;
                    image_segmentated.at<Vec3b>(punto_actual.y , punto_actual.x + 1)[2]= 255;
                    colaPixeles.push(Point( punto_actual.x + 1,punto_actual.y  ));
                }
            }
        }
        if (punto_actual.x +1 > 0 && punto_actual.y +1 > 0 && 
            punto_actual.x +1 < image.rows && punto_actual.y +1 < image.cols)
        {
            if( std::abs(image.at<Vec3b>(punto_actual.y + 1, punto_actual.x + 1)[0] - promediob) < rango &&
                std::abs(image.at<Vec3b>(punto_actual.y + 1, punto_actual.x + 1)[1] - promediog) < rango &&
                std::abs(image.at<Vec3b>(punto_actual.y + 1, punto_actual.x + 1)[2] - promedior) < rango 
            
            ){
                if(image_segmentated.at<Vec3b>(punto_actual.y + 1, punto_actual.x + 1)[0]!= 255){
                    image_segmentated.at<Vec3b>(punto_actual.y + 1, punto_actual.x + 1)[0]= 255;
                    image_segmentated.at<Vec3b>(punto_actual.y + 1, punto_actual.x + 1)[1]= 255;
                    image_segmentated.at<Vec3b>(punto_actual.y + 1, punto_actual.x + 1)[2]= 255;
                    colaPixeles.push(Point( punto_actual.x + 1,punto_actual.y + 1 ));
                }
                
            }
        }
        

        
    } while ( !colaPixeles.empty());

    return image_segmentated;

}