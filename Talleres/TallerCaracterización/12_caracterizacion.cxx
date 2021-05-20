#include <iostream>
#include <queue>
#include "opencv2/imgproc.hpp"
#include "opencv2/imgcodecs.hpp"
#include "opencv2/highgui.hpp"

using namespace cv;

Mat componentes(Mat grayImg);

int main(int argc, char const *argv[])
{
    Mat image, etiqueta, histograma;
    int histSize = 256;

    image = imread(argv[1], 1);
    if (!image.data)
    {
        std::cerr << "Error: No image data" << std::endl;
        return (-1);
    }
    etiqueta = componentes(image);
    return 0;
}

Mat componentes(Mat Img)
{
    Mat grayImg, histograma;
    cvtColor(Img, grayImg, COLOR_BGR2GRAY);
    int graymax_X = grayImg.cols;
    int graymax_Y = grayImg.rows;
    int hola;
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
    float range[] = {0, etiquetaN}; //the upper boundary is exclusive
    const float *histRange = {range};
    calcHist(&etiquetas, 1, 0, Mat(), histograma, 1, &numEtiqueta, &histRange, true, false);
    int max = 0;
    int etiquetamax = 0;
    for (int i = 1; i < numEtiqueta; i++)
    {
        if (histograma.at<float>(0, i) > max)
        {
        
            max = histograma.at<float>(0, i);
        }
    }
    std::cout << max << std::endl;

    return etiquetas;
}