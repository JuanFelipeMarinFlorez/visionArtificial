#include <opencv2/opencv.hpp>
#include <iostream>
#include <math.h>

using namespace cv;

Mat MorphGradient(Mat img);
Mat TopHat(Mat img);
Mat BottomHat(Mat img);
int erosion_size = 3;
int dilation_size = 3;
Mat element_erotion = getStructuringElement(MORPH_RECT,
                                    Size(2 * erosion_size + 1, 2 * erosion_size + 1),
                                    Point(erosion_size, erosion_size));
Mat element_dilation = getStructuringElement(MORPH_RECT,
                                    Size(2 * dilation_size + 1, 2 * dilation_size + 1),
                                    Point(dilation_size, dilation_size));

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

  image_gradient = MorphGradient(image);
  image_topHat = TopHat(image);
  image_bottomHat = BottomHat(image);

  std::stringstream ss(argv[1]);
  std::string basename;
  getline(ss, basename, '.');
  imwrite(basename + "MorphologicalGradient.png", image_gradient);
  imwrite(basename + "TopHat.png", image_topHat);
  imwrite(basename + "BottomHat.png", image_bottomHat);
}

Mat MorphGradient(Mat img){
  Mat dilatada;
  dilate(img,dilatada,element_dilation);
  Mat erosionada;
  erode(img,erosionada,element_erotion);

  Mat resultado = dilatada - erosionada;
  return resultado;

}
Mat TopHat(Mat img)
{
  Mat dilatada;
  Mat erosionada;
  erode(img,erosionada,element_erotion);
  dilate(erosionada,dilatada,element_dilation);
  return (img - dilatada);


}

Mat BottomHat(Mat img)
{
  Mat dilatada;
  Mat erosionada;
   dilate(img,dilatada,element_dilation);
  erode(dilatada,erosionada,element_erotion);

  return (erosionada - img);


}
