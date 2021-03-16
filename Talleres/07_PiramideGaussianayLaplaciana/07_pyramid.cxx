#include <stdio.h>
#include <opencv2/opencv.hpp>

using namespace cv;

Mat pydown(Mat imgsrc);
Mat pyup(Mat imgsrc);

int main(int argc, char **argv)
{
    // Variable Declarations
    Mat Pyramid[7];
    Mat laplacianPyramid[7];

    // Get command line arguments
    if (argc < 2)
    {
        std::cerr << "Usage: " << argv[0] << " image_file" << std::endl;
        return (-1);

    } // fi

    // Review given command line arguments
    std::cout << "-------------------------" << std::endl;
    for (int a = 0; a < argc; a++)
        std::cout << argv[a] << std::endl;
    std::cout << "-------------------------" << std::endl;
    // Read an image
    Mat image;
    image = imread(argv[1], 1);

    if (!image.data)
    {
        std::cerr << "Error: No image data" << std::endl;
        return (-1);

    } // fi

    Pyramid[2] = pydown(image);
    Pyramid[1] = pydown(Pyramid[2]);
    Pyramid[0] = pydown(Pyramid[1]); 

    imwrite( "4.png", image);
    imwrite( "3.png", Pyramid[2] );
    imwrite( "2.png", Pyramid[1] );
    imwrite( "1.png", Pyramid[0] );

}

Mat pydown(Mat imgsrc)
{
    Mat auximg(Size(imgsrc.cols, imgsrc.rows), CV_8UC1);
    Point anchor;
    double delta;
    int ddepth;
    anchor = Point(-1, -1);
    delta = 0;
    ddepth = -1;
    float GaussianKernelData[] = {0.00390625, 0.015625, 0.0234375, 0.015625, 0.00390625,
                                  0.015625, 0.0625, 0.09375, 0.0625, 0.015625,
                                  0.0234375, 0.09375, 0.140625, 0.09375, 0.0234375,
                                  0.015625, 0.0625, 0.09375, 0.0625, 0.015625,
                                  0.00390625, 0.015625, 0.0234375, 0.015625, 0.00390625};

    Mat kernel(5, 5, CV_32F, GaussianKernelData);

    Mat reduceimg(Size(imgsrc.cols / 2, imgsrc.rows / 2), CV_8UC1);

    filter2D(imgsrc, auximg, ddepth, kernel, anchor, delta, BORDER_DEFAULT);

    MatIterator_<Vec3b> it, nIt, end, endr;
    it = auximg.begin<Vec3b>();
    nIt = reduceimg.begin<Vec3b>();
    end = auximg.end<Vec3b>();
    endr = reduceimg.end<Vec3b>();
    int flag = 0;

    for (; it != end && nIt != endr; it = it + 2, ++nIt, flag++)
    {
        if (flag == reduceimg.rows)
        {
            flag = 0;
            it += auximg.rows;
        }
        else
        {
            (*nIt) = (*it);
        }
    }
    return reduceimg;
}

Mat pyup(Mat imgsrc, Size size)
{
}