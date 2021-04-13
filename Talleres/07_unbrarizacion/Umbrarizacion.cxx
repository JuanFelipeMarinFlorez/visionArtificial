#include <opencv2/opencv.hpp>
#include <iostream>
#include <math.h>

using namespace cv;

long double Otso_fun(Mat img);

int main(int argc, char **argv)
{
  // Declare variables
  Mat src;

  // Get command line arguments
  if (argc < 2)
  {
    std::cerr << "Usage: " << argv[0] << " image_file" << std::endl;
    return (-1);
  }

  // Review given command line arguments
  std::cout << "-------------------------" << std::endl;
  for (int a = 0; a < argc; a++)
    std::cout << argv[a] << std::endl;
  std::cout << "-------------------------" << std::endl;

  const char *imageName = argc >= 2 ? argv[1] : "lena.jpg";

  // Loads an image
  src = imread(imageName);
  if (src.empty())
  {
    printf(" Error opening image\n");
    printf(" Program Arguments: [image_name -- default lena.jpg] \n");
    return EXIT_FAILURE;
  }
  //Calcular el Umbral de OTSU

  long double threshold_value = Otso_fun(src);
  std::cout << "Umbral calculado con el Algoritmo de Otsu: " << threshold_value << std::endl;

  //Crea la matriz de destino
  Mat blur, blur2, dest1, dest2, dest3;
  GaussianBlur(src, blur, Size(5, 5), 0, 0);
  Size size(src.cols, src.rows);

  cvtColor(blur, blur2, COLOR_BGR2GRAY);

  //Aplicar el Umbral a la imagen con filtro gaussiano

  threshold(blur2, dest1, threshold_value, 255, THRESH_BINARY);
  threshold(blur2, dest2, threshold_value, 255, THRESH_TOZERO);

  //Comparación con la función de OPENCV

  double ocv_threshold_value = threshold(blur2, dest3, 1, 255, THRESH_OTSU);
  std::cout << "Umbral calculado con el Algoritmo de Otsu de OpenCV: " << ocv_threshold_value << std::endl;

  //para el nombre de la nueva imagen
  std::stringstream ss(argv[1]);
  std::string basename;
  getline(ss, basename, '.');

  //channels

  imwrite(basename + "binary.png", dest1);
  imwrite(basename + "thresholded.png", dest2);
  imwrite(basename + "OCV_Thresholded.png", dest3);

  return (0);
}

long double Otso_fun(Mat img)
{
  Mat blur;
  GaussianBlur(img, blur, Size(5, 5), 0, 0);

  int bins_num = 256;

  // Crear el histograma
  long double histogram[256];

  // Todas las intensidades inicializadas en 0
  for (int i = 0; i < 256; i++)
  {
    histogram[i] = 0;
  }

  // Llenar las intensidades
  for (int y = 0; y < blur.rows; y++)
  {
    for (int x = 0; x < blur.cols; x++)
    {
      histogram[(int)blur.at<uchar>(y, x)]++;
    }
  }
  // Calculate the bin_edges
  long double bin_edges[256];
  bin_edges[0] = 0.0;
  long double increment = 0.99609375;
  for (int i = 1; i < 256; i++)
  {
    bin_edges[i] = bin_edges[i - 1] + increment;
  }
  // Calculate bin_mids
  long double bin_mids[256];
  for (int i = 0; i < 256; i++)
  {
    bin_mids[i] = (bin_edges[i] + bin_edges[i + 1]) / 2;
  }

  // Iterate over all thresholds (indices) and get the probabilities weight1, weight2
  long double weight1[256];
  weight1[0] = histogram[0];
  for (int i = 1; i < 256; i++)
  {
    weight1[i] = histogram[i] + weight1[i - 1];
  }
  int total_sum = 0;
  for (int i = 0; i < 256; i++)
  {
    total_sum = total_sum + histogram[i];
  }
  long double weight2[256];
  weight2[0] = total_sum;
  for (int i = 1; i < 256; i++)
  {
    weight2[i] = weight2[i - 1] - histogram[i - 1];
  }
  // Calculate the class means: mean1 and mean2
  long double histogram_bin_mids[256];
  for (int i = 0; i < 256; i++)
  {
    histogram_bin_mids[i] = histogram[i] * bin_mids[i];
  }
  long double cumsum_mean1[256];
  cumsum_mean1[0] = histogram_bin_mids[0];
  for (int i = 1; i < 256; i++)
  {
    cumsum_mean1[i] = cumsum_mean1[i - 1] + histogram_bin_mids[i];
  }
  long double cumsum_mean2[256];
  cumsum_mean2[0] = histogram_bin_mids[255];
  for (int i = 1, j = 254; i < 256 && j >= 0; i++, j--)
  {
    cumsum_mean2[i] = cumsum_mean2[i - 1] + histogram_bin_mids[j];
  }
  long double mean1[256];
  for (int i = 0; i < 256; i++)
  {
    mean1[i] = cumsum_mean1[i] / weight1[i];
  }
  long double mean2[256];
  for (int i = 0, j = 255; i < 256 && j >= 0; i++, j--)
    mean2[j] = cumsum_mean2[i] / weight2[j];

  // Calculate Inter_class_variance
  long double Inter_class_variance[255];
  long double dnum = 10000000000;
  for (int i = 0; i < 255; i++)
  {
    Inter_class_variance[i] = ((weight1[i] * weight2[i] * (mean1[i] - mean2[i + 1])) / dnum) * (mean1[i] - mean2[i + 1]);
  }
  // Maximize interclass variance
  long double maxi = 0;
  int getmax = 0;
  for (int i = 0; i < 255; i++)
  {
    if (maxi < Inter_class_variance[i])
    {
      maxi = Inter_class_variance[i];
      getmax = i;
    }
  }
  return bin_mids[getmax];
}