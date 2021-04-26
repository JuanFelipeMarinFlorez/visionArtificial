#include <opencv2/opencv.hpp>
#include <iostream>
#include <math.h>

using namespace cv;

Mat MorphGradient(Mat img);
Mat TopHat(Mat img);
Mat BottonHat(Mat img);
int erosion_size = 3;
int dilation_size = 3;
Mat element_erotion = getStructuringElement(MORPH_RECT,
                                    Size(2 * erosion_size + 1, 2 * erosion_size + 1),
                                    Point(erosion_size, erosion_size));
Mat element_dilation = getStructuringElement(MORPH_RECT,
                                    Size(2 * dilation_size + 1, 2 * dilation_size + 1),
                                    Point(dilation_size, dilation_size));

Mat MorphGradient(Mat img)
{
  Mat dilation_dst, erosion_dst;

  //Dilation de la img
  dilate( img, dilation_dst, element_dilation );


  //Erosion de la img
  erode( img, erosion_dst, element_dilation );

  return MRest(dilation_dst, erosion_dst);
}
Mat TopHat(Mat img)
{
  Mat erosion_dst, res;
  //Erosion de la img
  erode( img, erosion_dst, element_dilation );

  //Dilation de la img
  dilate( erosion_dst, res, element_dilation );

  return res;

}

Mat BottomHat(Mat img)
{
}

Mat MAddition (Mat a, Mat b){
  Mat res;
  int xa = a.size(); /* size of y */
  int ya = a[0].size(); /* size of x */

  int xb = b.size(); /* size of y */
  int yb = b[0].size(); /* size of x */
  if ((xa == xb) && (ya == yb))
  {
    for(int i = 0; i < xa; i++)
    {
      for (int j = 0; j < ya; j++)
      {
        res[i][j] = a[i][j] + b[i][j];
      }
    } 
    return res;
  }
  else return 0;
  
} 

Mat MRest (Mat a, Mat b){
  Mat res;
  int xa = a.size(); /* size of y */
  int ya = a[0].size(); /* size of x */

  int xb = b.size(); /* size of y */
  int yb = b[0].size(); /* size of x */
  if ((xa == xb) && (ya == yb))
  {
    for(int i = 0; i < xa; i++)
    {
      for (int j = 0; j < ya; j++)
      {
        res[i][j] = a[i][j] - b[i][j];
      }
    } 
    return res;
  }
  else return 0;
  
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

  //Define Element Matrix for

  image_gradient = MorphGradient(img;
  image_topHat = MorphGradient(image);
  image_bottomHat = MorphGradient(image);

  std::stringstream ss(argv[1]);
  std::string basename;
  getline(ss, basename, '.');
  imwrite(basename + "MorphologicalGradient.png", image_gradient);
  imwrite(basename + "TopHat.png", image_topHat);
  imwrite(basename + "BottomHat.png", image_bottomHat);
}


