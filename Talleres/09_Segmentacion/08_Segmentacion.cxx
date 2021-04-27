#include "opencv2/imgproc.hpp"
#include "opencv2/imgcodecs.hpp"
#include "opencv2/highgui.hpp"
#include <iostream>
using namespace cv;
using namespace std;

Mat Hist_and_Backproj(Mat hue)
{
  int histSize = MAX(25, 2);
  float hue_range[] = {0, 180};
  const float *ranges = {hue_range};
  Mat hist;
  calcHist(&hue, 1, 0, Mat(), hist, 1, &histSize, &ranges, true, false);
  normalize(hist, hist, 0, 255, NORM_MINMAX, -1, Mat());
  Mat backproj;
  calcBackProject(&hue, 1, 0, hist, backproj, &ranges, 1, true);
  int w = 400, h = 400;
  int bin_w = cvRound((double)w / histSize);
  Mat histImg = Mat::zeros(h, w, CV_8UC3);
  for (int i = 0; i < 25; i++)
  {
    rectangle(histImg, Point(i * bin_w, h), Point((i + 1) * bin_w, h - cvRound(hist.at<float>(i) * h / 255.0)),
              Scalar(0, 0, 255), FILLED);
  }

  return backproj;
}

Mat sobel(Mat image, char opcion, int ksize, int scale, int delta)
{

  Mat src, src_gray;
  Mat grad;
  int ddepth = CV_16S;
  GaussianBlur(image, src, Size(3, 3), 0, 0, BORDER_DEFAULT);
  cvtColor(src, src_gray, COLOR_BGR2GRAY);
  Mat grad_x, grad_y;
  Mat abs_grad_x, abs_grad_y;
  Sobel(src_gray, grad_x, ddepth, 1, 0, ksize, scale, delta, BORDER_DEFAULT);
  Sobel(src_gray, grad_y, ddepth, 0, 1, ksize, scale, delta, BORDER_DEFAULT);
  convertScaleAbs(grad_x, abs_grad_x);
  convertScaleAbs(grad_y, abs_grad_y);
  addWeighted(abs_grad_x, 0.5, abs_grad_y, 0.5, 0, grad);
  if (opcion == 'k' || opcion == 'K')
  {
    ksize = ksize < 30 ? ksize + 2 : -1;
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
    scale = 1;
    ksize = -1;
    delta = 0;
  }
  return grad;
}

Mat CannyThreshold(Mat image, int threshold, int aperture, int kernel)
{
  Mat src_gray;
  Mat dst, edges;
  dst.create( image.size(), image.type() );
  cvtColor( image, src_gray, COLOR_BGR2GRAY );

  blur( src_gray, edges, Size(3,3) );
  Canny( edges, edges, threshold, aperture, kernel );
  dst = Scalar::all(0);
  image.copyTo(dst, edges);
  return dst;
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
  Mat image;
  image = imread(argv[1], 1);

  if (!image.data)
  {
    std::cerr << "Error: No image data" << std::endl;
    return (-1);
  }
  Mat hsv, hue;
  cvtColor(image, hsv, COLOR_BGR2HSV);
  hue.create(hsv.size(), hsv.depth());
  int ch[] = {0, 0};
  mixChannels(&hsv, 1, &hue, 1, ch, 1);
  Mat result = Hist_and_Backproj(hue);

  Mat res = sobel(image, 'k', 3, 2, 1);
  Mat res_color;
  cvtColor(res, res_color, COLOR_GRAY2BGR);
  //Canny need values
  int lowThreshold = 20;
  int max_lowThreshold = 100;
  int ratio = 3;
  int kernel_size = 3;

  Mat cannyres = CannyThreshold(image, lowThreshold, lowThreshold*ratio, kernel_size);

  Mat final = image-res_color-cannyres;
  std::stringstream ss(argv[1]);
  std::string basename;
  getline(ss, basename, '.');
  imwrite(basename + "_sobel.png", res);
  imwrite(basename + "_blckproj.png", result);
  imwrite(basename + "_canny.png", cannyres);
  imwrite(basename + "_final.png", final);
}