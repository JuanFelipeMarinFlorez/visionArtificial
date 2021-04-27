#include <opencv2/opencv.hpp>
#include <iostream>
#include <math.h>

using namespace cv;

void writeImg(Mat *img, int x, int y);

int main(int argc, char **argv)
{

  //Declaracion de variables
  Point anchor;
  double delta;
  int ddepth;
  anchor = Point(-1, -1);
  delta = 0;
  ddepth = -1;

  Mat image, dst, dst2, dst3;
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

  image = imread(argv[1], 1);

  if (!image.data)
  {
    std::cerr << "Error: No image data" << std::endl;
    return (-1);

  } // fi

  cvtColor(image, dst, COLOR_BGR2GRAY);

  float KernelData1[] = {-1, -1, -1,
                         -1, 9, -1,
                         -1, -1, -1};

  float KernelData4[] = {-1, -1, 0,
                         -1, 0, 1,
                         0, 1, 1};

  float KernelData2[] = {0.0625, 0.25, 0.0625,
                         0.25, 0.5, 0.25,
                         0.0625, 0.25, 0.0625};

  Mat kernel1(3, 3, CV_32F, KernelData1);
  Mat kernel2(3, 3, CV_32F, KernelData2);
  Mat kernel4(3, 3, CV_32F, KernelData4);

  //filter2D(dst, dst, ddepth, kernel4, anchor, delta, BORDER_DEFAULT);

  double otsu = threshold(dst, dst3, 0, 255, THRESH_OTSU);

  //filter2D(dst2, dst2, ddepth, kernel1, anchor, delta, BORDER_DEFAULT);

  //dst2 contiene la imagen de referencia ya umbralizada.

  float KernelData3[] = {1, 0, 250,
                         0, 1, 0};

  Mat kernel(2, 3, CV_32F, KernelData3);



  std::stringstream ss(argv[1]);
  std::string basename;
  getline(ss, basename, '.');
  imwrite(basename + "_binary.png", dst3);

  //warpAffine(dst2, dst3, kernel, image.size(), BORDER_CONSTANT, 0);
  int x, y, minx, miny, maxx, maxy;
  MatIterator_<Vec3b> it, end;
  it = dst3.begin<Vec3b>();
  end = dst3.end<Vec3b>();
  x = 0;
  y = 0;
  minx = 1025;
  miny = 1025;
  maxx = 0;
  maxy = 0;
  for (; it != end; ++it, x++)
  {
    if (x == 1024)
    {
      y++;
      x = 0;
    }
    if ((*it)[0] == 0)
    {
      if (x < minx)
      {
        minx = x;
      }
      if (x > maxx)
      {
        maxx = x;
      }
      if (y < miny)
      {
        miny = y;
      }
      if (y > maxy)
      {
        maxy = y;
      }
    }
  }
  std::cout << "minX: " << minx << std::endl;
  std::cout << "minY: " << miny << std::endl;
  std::cout << "maxX: " << maxx << std::endl;
  std::cout << "maxY: " << maxy << std::endl;

  int perimeterx = maxx - minx;
  int perimetery = maxy - miny;
  int centerx = perimeterx / 2;
  int centery = perimetery / 2;
  int movex = 0;
  int movey = 0;

  //centerx = centerx + minx;
  //centery = centery + miny;

  movex = centerx - 512;

  movey = centery - 512;

  Mat white(dst3.rows, dst3.cols, CV_8UC1, Scalar::all(255));
  Mat *white2 = &white;
  int x2, y2;
  x2 = 0;
  y2 = 0;
  it = dst3.begin<Vec3b>();
  end = dst3.end<Vec3b>();
  for (; it != end; ++it, x2++)
  {
    if (x2 == 1024)
    {
      y2++;
      x2 = 0;
    }
    if ((*it)[0] == 0)
    {
      white.at<uchar>(y2 + movey, x2 + movex) = 0;
    }
  }


  //channels

  return 0;
}
void writeImg(Mat *img, int x, int y)
{
  MatIterator_<Vec3b> it, end;
  it = img->begin<Vec3b>();
  end = img->end<Vec3b>();
  int itx = 0;
  int ity = 0;

  for (; it != end; it++, itx++)
  {
    if (itx == 1024)
    {
      ity++;
      itx = 0;
    }
    if (itx == x && ity == y)
    {
      (*it)[0] = 0;
      std::cout << "Hecho" << std::endl;
      std::cout << "x: " << itx << std::endl;
      std::cout << "y: " << ity << std::endl;
    }
  }
}