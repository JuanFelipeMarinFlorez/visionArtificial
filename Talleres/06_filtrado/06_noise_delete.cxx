#include <stdio.h>
#include <opencv2/opencv.hpp>

using namespace cv;

int main(int argc, char **argv)
{
    Mat image;
    Mat dst;
    Point anchor;
    double delta;
    int ddepth;
    float data[] = {-1,-1,-1,-1,-1,
                    -1, 2, 2, 2,-1,
                    -1, 2, 8, 2,-1,
                    -1, 2, 2, 2,-1,
                    -1,-1,-1,-1,-1};
    float data2[] = {-1,-1,-1,
                     -1, 9,-1,
                     -1,-1,-1};
    Mat kernel(3, 3, CV_32F, data2);
    Mat kernel2(5,5,CV_32F, data);
    Mat kernel_prom;
    kernel_prom = Mat::ones(3, 3, CV_32F) / (float)(3 * 3);
    anchor = Point(-1, -1);
    delta = 0;
    ddepth = -1;
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
    image = imread(argv[1], 1);

    if (!image.data)
    {
        std::cerr << "Error: No image data" << std::endl;
        return (-1);

    } // fi

    filter2D(image, dst, ddepth, kernel_prom, anchor, delta, BORDER_DEFAULT);
    filter2D(dst, dst, ddepth, kernel_prom, anchor, delta, BORDER_DEFAULT);
    filter2D(dst, dst, ddepth, kernel_prom, anchor, delta, BORDER_DEFAULT);
    filter2D(dst, dst, ddepth, kernel_prom, anchor, delta, BORDER_DEFAULT);
    filter2D(dst, dst, ddepth, kernel_prom, anchor, delta, BORDER_DEFAULT);
    filter2D(dst, dst, ddepth, kernel_prom, anchor, delta, BORDER_DEFAULT);
    filter2D(dst, dst, ddepth, kernel_prom, anchor, delta, BORDER_DEFAULT);
    filter2D(dst, dst, ddepth, kernel, anchor, delta, BORDER_DEFAULT);
    filter2D(dst, dst, ddepth, kernel, anchor, delta, BORDER_DEFAULT);
    filter2D(dst, dst, ddepth, kernel, anchor, delta, BORDER_DEFAULT);
    filter2D(dst, dst, ddepth, kernel, anchor, delta, BORDER_DEFAULT);
    medianBlur(image, dst, 3);
    medianBlur(image, dst, 3);
    medianBlur(image, dst, 3);
    medianBlur(image, dst, 3);
    medianBlur(image, dst, 3);
    medianBlur(image, dst, 3);
    medianBlur(image, dst, 3);
    medianBlur(image, dst, 3);
    medianBlur(image, dst, 3);
    medianBlur(image, dst, 3);
    medianBlur(image, dst, 3);
    medianBlur(image, dst, 3);
    medianBlur(image, dst, 3);





    
    

    



    std::stringstream ss(argv[1]);
    std::string basename;
    getline(ss, basename, '.');
    imwrite(basename + "_Noise_delete.png", dst);
}