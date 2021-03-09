#include <stdio.h>
#include <opencv2/opencv.hpp>

using namespace cv;

int main(int argc, char **argv)
{
  // Declarar varibles
  Mat dst[5];
  Mat dst11;
  Mat kernel;
  Mat kernel2;
  Point anchor;
  double delta;
  int ddepth;
  int kernel_size = 3;
  int kernel2_size = 11;


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

  // Initialize arguments for the filter
  anchor = Point(-1, -1);
  delta = 0;
  ddepth = -1;

  // definir filtro
  kernel = Mat::ones(kernel_size, kernel_size, CV_32F) / (float)(kernel_size * kernel_size);
  kernel2 = Mat::ones(kernel2_size, kernel2_size, CV_32F) / (float)(kernel2_size * kernel2_size);

  // Apply filter 3*3 Five Times
  filter2D(image, dst[0], ddepth, kernel, anchor, delta, BORDER_DEFAULT);

  for (int i = 0; i < 4; i++)
  {
    filter2D(dst[i], dst[i + 1], ddepth, kernel, anchor, delta, BORDER_DEFAULT);
  }
  // Apply filter 11*11 One Time

  filter2D(image, dst11, ddepth, kernel2, anchor, delta, BORDER_DEFAULT);

  std::stringstream ss(argv[1]);
  std::string basename;
  getline(ss, basename, '.');
  std::string name[5];
  name[0] = "1";
  name[1] = "2";
  name[2] = "3";
  name[3] = "4";
  name[4] = "5";
  for (int i = 0; i < 5; i++)
  {
    imwrite(basename + "_filtro_" + name[i] + "_.png", dst[i]);
  }

  imwrite(basename + "_filtro_11*11_.png", dst11);

  return (0);
}