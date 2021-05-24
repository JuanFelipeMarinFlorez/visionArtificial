#include <iostream>
#include <queue>
#include "opencv2/imgproc.hpp"
#include "opencv2/imgcodecs.hpp"
#include "opencv2/highgui.hpp"

using namespace cv;

Mat componentes(Mat grayImg);
Mat centros(Mat img, Mat img2);

int main(int argc, char const *argv[])
{
    Mat image, etiqueta, histograma, distancias, resultado;
    int histSize = 256;

    image = imread(argv[1], 1);
    if (!image.data)
    {
        std::cerr << "Error: No image data" << std::endl;
        return (-1);
    }
    etiqueta = componentes(image);

    imwrite("resultado.png", etiqueta);

    distanceTransform(etiqueta,distancias, DIST_L1,3);
    imwrite("resultado2.png", distancias);

    resultado= centros(etiqueta,distancias);

    imwrite("resultado3.png", resultado);


    return 0;
}

Mat componentes(Mat Img)
{
    Mat grayImg, histograma, histograma2;
    cvtColor(Img, grayImg, COLOR_BGR2GRAY);
    int graymax_X = grayImg.cols;
    int graymax_Y = grayImg.rows;
    Mat etiquetas = Mat::zeros(graymax_Y, graymax_X, CV_8UC1);
    std::queue<Point> colaPixeles;
    int numEtiqueta = 1;
    for (int i = 0; i < graymax_Y; i++)
    {
        for (int j = 0; j < graymax_X; j++)
        {
            if (grayImg.at<uchar>(i, j) == 255 && etiquetas.at<uchar>(i, j) == 0)
            {
                colaPixeles.push(Point(j, i));
                etiquetas.at<uchar>(i, j) = numEtiqueta;
                //--------------------------------------------------------------
                do
                {
                    Point punto_actual = colaPixeles.front();
                    colaPixeles.pop();

                    if (punto_actual.x - 1 >= 0 && punto_actual.y - 1 >= 0 &&
                        punto_actual.x - 1 < graymax_X && punto_actual.y - 1 < graymax_Y)
                    {
                        if (grayImg.at<uchar>(punto_actual.y - 1, punto_actual.x - 1) == 255 &&
                            etiquetas.at<uchar>(punto_actual.y - 1, punto_actual.x - 1) == 0)
                        {
                            etiquetas.at<uchar>(punto_actual.y - 1, punto_actual.x - 1) = numEtiqueta;
                            colaPixeles.push(Point(punto_actual.x - 1, punto_actual.y - 1));
                        }
                    }
                    if (punto_actual.x - 1 >= 0 && punto_actual.y >= 0 &&
                        punto_actual.x - 1 < graymax_X && punto_actual.y < graymax_Y)
                    {
                        if (grayImg.at<uchar>(punto_actual.y, punto_actual.x - 1) == 255 &&
                            etiquetas.at<uchar>(punto_actual.y, punto_actual.x - 1) == 0)
                        {
                            etiquetas.at<uchar>(punto_actual.y, punto_actual.x - 1) = numEtiqueta;
                            colaPixeles.push(Point(punto_actual.x - 1, punto_actual.y));
                        }
                    }

                    if (punto_actual.x - 1 >= 0 && punto_actual.y + 1 >= 0 &&
                        punto_actual.x - 1 < graymax_X && punto_actual.y + 1 < graymax_Y)
                    {
                        if (grayImg.at<uchar>(punto_actual.y + 1, punto_actual.x - 1) == 255 &&
                            etiquetas.at<uchar>(punto_actual.y + 1, punto_actual.x - 1) == 0)
                        {
                            etiquetas.at<uchar>(punto_actual.y + 1, punto_actual.x - 1) = numEtiqueta;
                            colaPixeles.push(Point(punto_actual.x - 1, punto_actual.y + 1));
                        }
                    }
                    if (punto_actual.x >= 0 && punto_actual.y - 1 >= 0 &&
                        punto_actual.x < graymax_X && punto_actual.y - 1 < graymax_Y)
                    {
                        if (grayImg.at<uchar>(punto_actual.y - 1, punto_actual.x) == 255 &&
                            etiquetas.at<uchar>(punto_actual.y - 1, punto_actual.x) == 0)
                        {
                            etiquetas.at<uchar>(punto_actual.y - 1, punto_actual.x) = numEtiqueta;
                            colaPixeles.push(Point(punto_actual.x, punto_actual.y - 1));
                        }
                    }
                    if (punto_actual.x >= 0 && punto_actual.y + 1 >= 0 &&
                        punto_actual.x < graymax_X && punto_actual.y + 1 < graymax_Y)
                    {
                        if (grayImg.at<uchar>(punto_actual.y + 1, punto_actual.x) == 255 &&
                            etiquetas.at<uchar>(punto_actual.y + 1, punto_actual.x) == 0)
                        {
                            etiquetas.at<uchar>(punto_actual.y + 1, punto_actual.x) = numEtiqueta;
                            colaPixeles.push(Point(punto_actual.x, punto_actual.y + 1));
                        }
                    }
                    if (punto_actual.x + 1 >= 0 && punto_actual.y - 1 >= 0 &&
                        punto_actual.x + 1 < graymax_X && punto_actual.y - 1 < graymax_Y)
                    {
                        if (grayImg.at<uchar>(punto_actual.y - 1, punto_actual.x + 1) == 255 &&
                            etiquetas.at<uchar>(punto_actual.y - 1, punto_actual.x + 1) == 0)
                        {
                            etiquetas.at<uchar>(punto_actual.y - 1, punto_actual.x + 1) = numEtiqueta;
                            colaPixeles.push(Point(punto_actual.x + 1, punto_actual.y - 1));
                        }
                    }
                    if (punto_actual.x + 1 >= 0 && punto_actual.y >= 0 &&
                        punto_actual.x + 1 < graymax_X && punto_actual.y < graymax_Y)
                    {
                        if (grayImg.at<uchar>(punto_actual.y, punto_actual.x + 1) == 255 &&
                            etiquetas.at<uchar>(punto_actual.y, punto_actual.x + 1) == 0)
                        {
                            etiquetas.at<uchar>(punto_actual.y, punto_actual.x + 1) = numEtiqueta;
                            colaPixeles.push(Point(punto_actual.x + 1, punto_actual.y));
                        }
                    }
                    if (punto_actual.x + 1 >= 0 && punto_actual.y + 1 >= 0 &&
                        punto_actual.x + 1 < graymax_X && punto_actual.y + 1 < graymax_Y)
                    {
                        if (grayImg.at<uchar>(punto_actual.y + 1, punto_actual.x + 1) == 255 &&
                            etiquetas.at<uchar>(punto_actual.y + 1, punto_actual.x + 1) == 0)
                        {
                            etiquetas.at<uchar>(punto_actual.y + 1, punto_actual.x + 1) = numEtiqueta;
                            colaPixeles.push(Point(punto_actual.x + 1, punto_actual.y + 1));
                        }
                    }
                } while (!colaPixeles.empty());
                numEtiqueta += 1;
                //--------------------------------------------------------------
            }
        }
    }
    float etiquetaN = (float)numEtiqueta;
    float range[] = {0, etiquetaN}; 
    const float *histRange = {range};
    calcHist(&etiquetas, 1, 0, Mat(), histograma, 1, &numEtiqueta, &histRange, true, false);
    int max = 0;
    int etiquetamax = 0;
    std::cout<<"Regiones identificadas antes de eliminar las regiones menores al 15% del tamaño de la mas grande"<<std::endl;
    for (int i = 1; i < numEtiqueta; i++)
    {
        std::cout<<"Región #: "<<i<<std::endl;
        std::cout<<"Tamaño: "<<histograma.at<float>(0, i)<<std::endl;
        if (histograma.at<float>(0, i) > max)
        {
        
            max = histograma.at<float>(0, i);
        }
    }

    int umbral= max*0.15;

    for (int i = 0; i < graymax_Y; i++)
    {
        for (int  j = 0; j < graymax_X; j++)
        {
            if(etiquetas.at<uchar>(i, j)!= 0 && etiquetas.at<uchar>(i, j) == 0){

                for (int k=0 ;k<numEtiqueta; k++ ){
                    if(histograma.at<float>(0, k) < umbral && etiquetas.at<uchar>(i, j)==k ){
                        etiquetas.at<uchar>(i, j)=0;
                       
                    }
                }

            }
        }
        
    }

    calcHist(&etiquetas, 1, 0, Mat(), histograma2, 1, &numEtiqueta, &histRange, true, false);
    std::cout<<"Regiones identificadas despues de eliminar las regiones menores al 15% del tamaño de la mas grande"<<std::endl;
    int cont=1;
    for (int i = 1; i < numEtiqueta; i++)
    {
        if(histograma2.at<float>(0, i) != 0 ){
            std::cout<<"Región #: "<<cont<<std::endl;
        std::cout<<"Tamaño: "<<histograma2.at<float>(0, i)<<std::endl;
        cont++;
        }
        
        
    }

    return etiquetas;
}

Mat centros(Mat img, Mat img2){

    int graymax_X = img.cols;
    int graymax_Y = img.rows;
    std::queue<Point> colaPixeles;
    std::queue<Point> colaPixeles2;
    int numetiquetas=0;
    int cont=1;
     for (int i = 0; i < graymax_Y; i++)
    {
        for (int j = 0; j < graymax_X; j++)
        {
            if (img.at<uchar>(i, j) !=0 && img.at<uchar>(i, j)>numetiquetas)
            {
                std::cout<<Point(j, i)<<std::endl;
                int maximo=0;
                colaPixeles.push(Point(j, i));
                colaPixeles2.push(Point(j, i));
                do
                {
                    Point punto_actual = colaPixeles.front();
                    colaPixeles.pop();
                    if(img2.at<uchar>(punto_actual.y, punto_actual.x) >maximo){
                       maximo=img2.at<uchar>(punto_actual.y, punto_actual.x) ; 
                    }

                    if (punto_actual.x - 1 >= 0 && punto_actual.y - 1 >= 0 &&
                        punto_actual.x - 1 < graymax_X && punto_actual.y - 1 < graymax_Y)
                    {
                        if (img.at<uchar>(punto_actual.y - 1, punto_actual.x - 1) != 0 &&
                         img.at<uchar>(punto_actual.y - 1, punto_actual.x - 1)>numetiquetas)
                        {
                            colaPixeles.push(Point(punto_actual.x - 1, punto_actual.y - 1));
                            colaPixeles2.push(Point(punto_actual.x - 1, punto_actual.y - 1));
                        }
                    }
                    if (punto_actual.x - 1 >= 0 && punto_actual.y >= 0 &&
                        punto_actual.x - 1 < graymax_X && punto_actual.y < graymax_Y)
                    {
                        if (img.at<uchar>(punto_actual.y, punto_actual.x - 1) != 0 &&
                         img.at<uchar>(punto_actual.y , punto_actual.x - 1)>numetiquetas)
                        {

                            colaPixeles.push(Point(punto_actual.x - 1, punto_actual.y));
                            colaPixeles2.push(Point(punto_actual.x - 1, punto_actual.y));
                        }
                    }

                    if (punto_actual.x - 1 >= 0 && punto_actual.y + 1 >= 0 &&
                        punto_actual.x - 1 < graymax_X && punto_actual.y + 1 < graymax_Y)
                    {
                        if (img.at<uchar>(punto_actual.y + 1, punto_actual.x - 1) != 0 &&
                         img.at<uchar>(punto_actual.y + 1, punto_actual.x - 1)>numetiquetas )
                        {
                            colaPixeles.push(Point(punto_actual.x - 1, punto_actual.y + 1));
                            colaPixeles2.push(Point(punto_actual.x - 1, punto_actual.y + 1));
                        }
                    }
                    if (punto_actual.x >= 0 && punto_actual.y - 1 >= 0 &&
                        punto_actual.x < graymax_X && punto_actual.y - 1 < graymax_Y)
                    {
                        if (img.at<uchar>(punto_actual.y - 1, punto_actual.x) != 0  &&
                         img.at<uchar>(punto_actual.y - 1, punto_actual.x )>numetiquetas)
                        {
                            colaPixeles.push(Point(punto_actual.x, punto_actual.y - 1));
                            colaPixeles2.push(Point(punto_actual.x, punto_actual.y - 1));
                        }
                    }
                    if (punto_actual.x >= 0 && punto_actual.y + 1 >= 0 &&
                        punto_actual.x < graymax_X && punto_actual.y + 1 < graymax_Y)
                    {
                        if (img.at<uchar>(punto_actual.y + 1, punto_actual.x) != 0 &&
                         img.at<uchar>(punto_actual.y +1, punto_actual.x )>numetiquetas)
                        {
                            colaPixeles.push(Point(punto_actual.x, punto_actual.y + 1));
                            colaPixeles2.push(Point(punto_actual.x, punto_actual.y + 1));
                        }
                    }
                    if (punto_actual.x + 1 >= 0 && punto_actual.y - 1 >= 0 &&
                        punto_actual.x + 1 < graymax_X && punto_actual.y - 1 < graymax_Y)
                    {
                        if (img.at<uchar>(punto_actual.y - 1, punto_actual.x + 1) != 0 &&
                         img.at<uchar>(punto_actual.y - 1, punto_actual.x + 1)>numetiquetas)
                        {
                            colaPixeles.push(Point(punto_actual.x + 1, punto_actual.y - 1));
                            colaPixeles2.push(Point(punto_actual.x + 1, punto_actual.y - 1));
                        }
                    }
                    if (punto_actual.x + 1 >= 0 && punto_actual.y >= 0 &&
                        punto_actual.x + 1 < graymax_X && punto_actual.y < graymax_Y)
                    {
                        if (img.at<uchar>(punto_actual.y, punto_actual.x + 1) != 0 &&
                         img.at<uchar>(punto_actual.y , punto_actual.x + 1)>numetiquetas)
                        {
                            colaPixeles.push(Point(punto_actual.x + 1, punto_actual.y));
                            colaPixeles2.push(Point(punto_actual.x + 1, punto_actual.y));
                        }
                    }
                    if (punto_actual.x + 1 >= 0 && punto_actual.y + 1 >= 0 &&
                        punto_actual.x + 1 < graymax_X && punto_actual.y + 1 < graymax_Y)
                    {
                        if (img.at<uchar>(punto_actual.y + 1, punto_actual.x + 1) != 0 &&
                         img.at<uchar>(punto_actual.y + 1, punto_actual.x + 1) >numetiquetas)
                        {
                            colaPixeles.push(Point(punto_actual.x + 1, punto_actual.y + 1));
                            colaPixeles2.push(Point(punto_actual.x + 1, punto_actual.y + 1));
                        }
                    }
                } while (!colaPixeles.empty());

                std::queue<Point> colaPixelesMaximos;
                do
                {
                    Point punto_actual = colaPixeles2.front();
                    colaPixeles2.pop();

                    if(img2.at<uchar>(punto_actual.y, punto_actual.x) == maximo){
                        colaPixelesMaximos.push(punto_actual);
                    }

                } while (!colaPixeles2.empty());

                Point centro(0,0);

                if(colaPixelesMaximos.size() >1){
                    int tam=colaPixelesMaximos.size();
                    int acumx=0;
                    int acumy=0;

                    do
                    {
                        Point punto_actual = colaPixelesMaximos.front();
                        colaPixelesMaximos.pop();
                        acumx += punto_actual.x;
                        acumy += punto_actual.y;
                        
                    } while (!colaPixelesMaximos.empty());

                    centro.x= acumx/tam;
                    centro.y=acumy/tam;

            
                }
                else{
                    Point punto_actual = colaPixelesMaximos.front();
                    colaPixelesMaximos.pop();
                    centro.x= punto_actual.x;
                    centro.y= punto_actual.y;

                }

                img2.at<uchar>(centro.y,centro.x)= 255;
                std::cout<<"centro región "<<cont<<centro<<std::endl;

                
                numetiquetas=img.at<uchar>(i, j);
                cont++;
            }
        }
    }

    return img2;

}