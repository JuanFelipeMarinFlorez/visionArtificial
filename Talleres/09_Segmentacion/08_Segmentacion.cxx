#include "opencv2/imgproc.hpp"
#include "opencv2/imgcodecs.hpp"
#include "opencv2/highgui.hpp"
#include <iostream>
using namespace cv;
using namespace std;

Mat sobel(Mat image, char opcion, int ksize, int scale, int delta)
{
                          
  Mat src, src_gray;
  Mat grad;
  int ddepth = CV_16S;

  
  // Remove noise by blurring with a Gaussian filter ( kernel size = 3 )
    GaussianBlur(image, src, Size(3, 3), 0, 0, BORDER_DEFAULT);
    // Convert the image to grayscale
    cvtColor(src, src_gray, COLOR_BGR2GRAY);
    Mat grad_x, grad_y;
    Mat abs_grad_x, abs_grad_y;
    Sobel(src_gray, grad_x, ddepth, 1, 0, ksize, scale, delta, BORDER_DEFAULT);
    Sobel(src_gray, grad_y, ddepth, 0, 1, ksize, scale, delta, BORDER_DEFAULT);
    // converting back to CV_8U
    convertScaleAbs(grad_x, abs_grad_x);
    convertScaleAbs(grad_y, abs_grad_y);
    addWeighted(abs_grad_x, 0.5, abs_grad_y, 0.5, 0, grad);

    if (opcion == 'k' || opcion == 'K')
    {
      ksize = ksize < 30 ? ksize+2 : -1;
    }
    if (opcion == 's' || opcion == 'S')
    {
      scale++;
    }
    if (opcion == 'd' || opcion == 'D')
    {
      delta++;
    }
    if (opcion == 'r' || opcion == 'R')
    {
      scale =  1;
      ksize = -1;
      delta =  0;
    }

  return src;
}

int main(int argc, char **argv)
{
  // argumentos por linea de comandos
  if (argc < 2)
  {
    std::cerr << "Usage: " << argv[0] << " image_file" << std::endl;
    return (-1);
  } // fi

  // Checar los argumentos recibidos
  std::cout << "-------------------------" << std::endl;
  for (int a = 0; a < argc; a++)
    std::cout << argv[a] << std::endl;
  std::cout << "-------------------------" << std::endl;
  // Leer Imagen
  Mat image, image_gradient, image_topHat, image_bottomHat;
  image = imread(argv[1], 1);

  if (!image.data)
  {
    std::cerr << "Error: No image data" << std::endl;
    return (-1);

  } // fi

  Mat res = sobel(image,'k' , 3,2,1);
  res = sobel(res,'k' , 3,2,1);

  std::stringstream ss(argv[1]);
  std::string basename;
  getline(ss, basename, '.');
  imwrite(basename + "_segmentada.png", res );
  
}


