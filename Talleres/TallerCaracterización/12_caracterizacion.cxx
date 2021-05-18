#include <iostream>
#include <queue>
#include "opencv2/imgproc.hpp"
#include "opencv2/imgcodecs.hpp"
#include "opencv2/highgui.hpp"

using namespace cv;

Mat componentes(Mat grayImg);

int main(int argc, char const *argv[])
{
    Mat image, etiqueta;
    image = imread(argv[1], 1);
    if (!image.data)
    {
        std::cerr << "Error: No image data" << std::endl;
        return (-1);
    }
    etiqueta = componentes(image);
    imwrite("etiqueta.png", etiqueta);
    return 0;
}

Mat componentes(Mat grayImg)
{
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
                std::cout<<"entre al punto: X: " << j << ", y: " << i <<std::endl;
                colaPixeles.push(Point(j, i));
                //--------------------------------------------------------------
                while (!colaPixeles.empty())
                {
                    std::cout<<"Entre al while"<<std::endl;
                    Point punto_actual = colaPixeles.front();
                    std::cout<<colaPixeles.front();
                    colaPixeles.pop();
                    etiquetas.at<uchar>(i, j) = numEtiqueta;
                    if (punto_actual.x - 1 > 0 && punto_actual.y - 1 > 0 &&
                        punto_actual.x - 1 < graymax_X && punto_actual.y - 1 < graymax_Y)
                    {
                        if (grayImg.at<uchar>(punto_actual.y - 1, punto_actual.x - 1) == 255 
                            && etiquetas.at<uchar>(punto_actual.y - 1, punto_actual.x - 1) == 0)
                        {
                            colaPixeles.push(Point(punto_actual.x - 1, punto_actual.y - 1));
                        }
                    }
                    if (punto_actual.x - 1 > 0 && punto_actual.y > 0 &&
                        punto_actual.x - 1 < graymax_X && punto_actual.y < graymax_Y)
                    {
                        if (grayImg.at<uchar>(punto_actual.y, punto_actual.x - 1) == 255 
                            && etiquetas.at<uchar>(punto_actual.y, punto_actual.x - 1) == 0) 
                        {
                            colaPixeles.push(Point(punto_actual.x - 1, punto_actual.y));
                        }
                    }

                    if (punto_actual.x - 1 > 0 && punto_actual.y + 1 > 0 &&
                        punto_actual.x - 1 < graymax_X && punto_actual.y + 1 < graymax_Y)
                    {
                        if (grayImg.at<uchar>(punto_actual.y + 1, punto_actual.x - 1) == 255 
                            && etiquetas.at<uchar>(punto_actual.y + 1, punto_actual.x - 1) == 0)
                        {

                            colaPixeles.push(Point(punto_actual.x - 1, punto_actual.y + 1));
                        }
                    }
                    if (punto_actual.x > 0 && punto_actual.y - 1 > 0 &&
                        punto_actual.x < graymax_X && punto_actual.y - 1 < graymax_Y)
                    {
                        if (grayImg.at<uchar>(punto_actual.y - 1, punto_actual.x) == 255 
                            && etiquetas.at<uchar>(punto_actual.y - 1, punto_actual.x) == 0)
                        {
                            colaPixeles.push(Point(punto_actual.x, punto_actual.y - 1));
                        }
                    }
                    if (punto_actual.x > 0 && punto_actual.y + 1 > 0 &&
                        punto_actual.x < graymax_X && punto_actual.y + 1 < graymax_Y)
                    {
                        if (grayImg.at<uchar>(punto_actual.y + 1, punto_actual.x) == 255 
                            && etiquetas.at<uchar>(punto_actual.y + 1, punto_actual.x) == 0)
                        {
                            colaPixeles.push(Point(punto_actual.x, punto_actual.y + 1));
                        }
                    }
                    if (punto_actual.x + 1 > 0 && punto_actual.y - 1 > 0 &&
                        punto_actual.x + 1 < graymax_X && punto_actual.y - 1 < graymax_Y)
                    {
                        if (grayImg.at<uchar>(punto_actual.y - 1, punto_actual.x + 1) == 255 
                            && etiquetas.at<uchar>(punto_actual.y - 1, punto_actual.x + 1) == 0)
                        {
                            colaPixeles.push(Point(punto_actual.x + 1, punto_actual.y - 1));
                        }
                    }
                    if (punto_actual.x + 1 > 0 && punto_actual.y > 0 &&
                        punto_actual.x + 1 < graymax_X && punto_actual.y < graymax_Y)
                    {
                        if (grayImg.at<uchar>(punto_actual.y, punto_actual.x + 1) == 255 
                            && etiquetas.at<uchar>(punto_actual.y, punto_actual.x + 1) == 0)
                        {
                            colaPixeles.push(Point(punto_actual.x + 1, punto_actual.y));
                        }
                    }
                    if (punto_actual.x + 1 > 0 && punto_actual.y + 1 > 0 &&
                        punto_actual.x + 1 < graymax_X && punto_actual.y + 1 < graymax_Y)
                    {
                        if (grayImg.at<uchar>(punto_actual.y + 1, punto_actual.x + 1) == 255 
                            && etiquetas.at<uchar>(punto_actual.y + 1, punto_actual.x + 1) == 0)
                        {
                            colaPixeles.push(Point(punto_actual.x + 1, punto_actual.y + 1));
                        }
                    }

                }
                numEtiqueta+=5;
                //--------------------------------------------------------------
            }
        }
    }
    return etiquetas;
}