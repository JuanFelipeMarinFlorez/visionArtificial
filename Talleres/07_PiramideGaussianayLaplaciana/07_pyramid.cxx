#include <stdio.h>
#include <opencv2/opencv.hpp>

using namespace cv;

Mat pydown(Mat imgsrc);
Mat pyup(Mat imgsrc);
Mat compare(Mat nImg, Mat oImg);
Mat resizer(Mat image, float newSize);
void laplacian(Mat pyramid[]);

int main(int argc, char **argv)
{
    // Variable Declarations
    Mat Pyramid[7];

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
    Pyramid[3] = image;
    Pyramid[4] = pyup(image);
    Pyramid[5] = pyup(Pyramid[4]);
    Pyramid[6] = pyup(Pyramid[5]);

    imwrite("Gaussian_7.png", Pyramid[6]);
    imwrite("Gaussian_6.png", Pyramid[5]);
    imwrite("Gaussian_5.png", Pyramid[4]);
    imwrite("Gaussian_4.png", image);
    imwrite("Gaussian_3.png", Pyramid[2]);
    imwrite("Gaussian_2.png", Pyramid[1]);
    imwrite("Gaussian_1.png", Pyramid[0]);

    laplacian(Pyramid);
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

Mat pyup(Mat imgsrc)
{
    Point anchor;
    double delta;
    int ddepth;
    anchor = Point(-1, -1);
    delta = 0;
    ddepth = -1;
    float GaussianKernelData[] = {0.0078125, 0.03125, 0.046875, 0.03125, 0.0078125,
                                  0.03125, 0.125, 0.1875, 0.125, 0.03125,
                                  0.046875, 0.1875, 0.28125, 0.375, 0.09375,
                                  0.03125, 0.125, 0.1875, 0.125, 0.03125,
                                  0.0078125, 0.03125, 0.046875, 0.03125, 0.0078125};

    float GaussianKernelData2[] = {0.015625, 0.0625, 0.09375, 0.0625, 0.015625,
                                  0.0625, 0.25, 0.375, 0.25, 0.0625,
                                  0.09375, 0.375, 0.5625, 0.375, 0.09375,
                                  0.0625, 0.25, 0.375, 0.25, 0.0625,
                                  0.015625, 0.0625, 0.09375, 0.0625, 0.015625};                       

    Mat kernel(5, 5, CV_32F, GaussianKernelData2);

    Mat augmentedimg(Size(imgsrc.cols * 2, imgsrc.rows * 2), CV_8UC1);

    augmentedimg = Mat::zeros(Size(imgsrc.cols * 2, imgsrc.rows * 2), CV_8UC1);

    MatIterator_<Vec3b> it, nIt, end, endr;
    it = imgsrc.begin<Vec3b>();
    nIt = augmentedimg.begin<Vec3b>();
    end = imgsrc.end<Vec3b>();
    endr = augmentedimg.end<Vec3b>();
    int flag = 0;

    for (; it != end && nIt != endr; ++it, nIt += 2, flag++)
    {
        if (flag == imgsrc.rows)
        {
            flag = 0;
            nIt += augmentedimg.rows;
        }
        else
        {
            (*nIt) = (*it);
        }
    }

    filter2D(augmentedimg, augmentedimg, ddepth, kernel, anchor, delta, BORDER_DEFAULT);

    return augmentedimg;
}

Mat compare(Mat nImg, Mat oImg)
{
    Mat image = Mat::zeros(nImg.size(), CV_8UC1);
    MatIterator_<Vec3b> nIt, oIt, nEnd, oEnd, it, end;
    it = image.begin<Vec3b>();
    nIt = nImg.begin<Vec3b>();
    oIt = oImg.begin<Vec3b>();
    end = image.end<Vec3b>();
    nEnd = nImg.end<Vec3b>();
    oEnd = oImg.end<Vec3b>();
    int value = 0;
    for (; nIt != nEnd && oIt != oEnd && it != end; ++it, ++nIt, ++oIt)
    {
        value = (*oIt)[0] - (*nIt)[0];
        (*it)[0] = value;
    }
    return image;
}

void laplacian(Mat pyramid[])
{
    Mat laplacian[7];
    Mat auximg;
    laplacian[0] = pyramid[0];
    for (int i = 0; i < 6; i++)
    {
        auximg = resizer(pyramid[i], 2);
        laplacian[i + 1] = compare(auximg, pyramid[i + 1]);
    }

    imwrite("LaPlacian_7.png", laplacian[6]);
    imwrite("LaPlacian_6.png", laplacian[5]);
    imwrite("LaPlacian_5.png", laplacian[4]);
    imwrite("LaPlacian_4.png", laplacian[3]);
    imwrite("LaPlacian_3.png", laplacian[2]);
    imwrite("LaPlacian_2.png", laplacian[1]);
    imwrite("LaPlacian_1.png", laplacian[0]);
}

Mat resizer(Mat image, float newSize)
{
    Mat res_img;
    resize(image, res_img, Size(), newSize, newSize, INTER_LINEAR);
    return res_img;
}
