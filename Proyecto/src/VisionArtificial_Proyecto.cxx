#include <opencv2/opencv.hpp>
#include <iostream>
#include <math.h>

using namespace cv;

int histSize = 256;
float energy, contrast, homogenity;
Mat symb = Mat::zeros(1, histSize, CV_32FC1);

float esHoja(Mat image)
{
  Mat grayImg, dst;
  cvtColor(image, grayImg, COLOR_BGR2GRAY);
  threshold(grayImg, dst, 0, 255, THRESH_OTSU);
  GaussianBlur(dst, dst, Size(3, 3), 0);
  Mat aux = dst;
  float prob = 0;
  int maxX = image.cols;
  int maxY = image.rows;
  int minx = 1025;
  int miny = 1025;
  int maxx = 0;
  int maxy = 0;
  if (dst.at<uchar>(0, 0) == 255)
  {
    bitwise_not(aux, dst);
  }
  for (int i = 0; i < maxY; i++)
  {
    for (int j = 0; j < maxX; j++)
    {
      if (dst.at<uchar>(j, i) == 255)
      {
        if (j < minx)
        {
          minx = j;
        }
        if (j > maxx)
        {
          maxx = j;
        }
        if (i < miny)
        {
          miny = i;
        }
        if (i > maxy)
        {
          maxy = i;
        }
      }
    }
  }

  double perimetery = maxx - minx;
  double perimeterx = maxy - miny;

  double ratio = perimeterx / perimetery;

  if (ratio > 0.7 && ratio < 0.8)
  {
    prob += 1.0;
  }

  return prob;
}

float esTetrapack(Mat image)
{

  Mat grayImg, dst;
  cvtColor(image, grayImg, COLOR_BGR2GRAY);
  threshold(grayImg, dst, 0, 255, THRESH_OTSU);
  GaussianBlur(dst, dst, Size(3, 3), 0);
  Mat aux = dst;
  float prob = 0;
  int maxX = image.cols;
  int maxY = image.rows;
  int minx = 1025;
  int miny = 1025;
  int maxx = 0;
  int maxy = 0;
  if (dst.at<uchar>(0, 0) == 255)
  {
    bitwise_not(aux, dst);
  }
  for (int i = 0; i < maxY; i++)
  {
    for (int j = 0; j < maxX; j++)
    {
      if (dst.at<uchar>(j, i) == 255)
      {
        if (j < minx)
        {
          minx = j;
        }
        if (j > maxx)
        {
          maxx = j;
        }
        if (i < miny)
        {
          miny = i;
        }
        if (i > maxy)
        {
          maxy = i;
        }
      }
    }
  }

  double perimetery = maxx - minx;
  double perimeterx = maxy - miny;

  double ratio = perimeterx / perimetery;

  if (ratio > 0.35 && ratio < 0.43)
  {
    prob += 0.7;
  }

  std::vector<Mat> bgr_planes;
  split(image, bgr_planes);
  int histSize = 256;
  float range[] = {0, 256}; //the upper boundary is exclusive
  const float *histRange = {range};
  bool uniform = true, accumulate = false;
  Mat b_hist, g_hist, r_hist;
  calcHist(&bgr_planes[0], 1, 0, Mat(), b_hist, 1, &histSize, &histRange, uniform, accumulate);
  calcHist(&bgr_planes[1], 1, 0, Mat(), g_hist, 1, &histSize, &histRange, uniform, accumulate);
  calcHist(&bgr_planes[2], 1, 0, Mat(), r_hist, 1, &histSize, &histRange, uniform, accumulate);

  long int total = 0;
  for (int i = 160; i < 250; i++)
  {
    total += (long int)b_hist.at<float>(0, i);
    total += (long int)g_hist.at<float>(0, i);
    total += (long int)r_hist.at<float>(0, i);
  }
  if (total > 500000 && total < 660000)
  {
    prob += 0.3;
  }

  return prob;
}

std::vector<float> entropy(Mat seq, Size size)
{
  std::vector<float> v;
  int index = size.height;
  int cnt = 0;
  float entr = 0;
  float total_size = size.height * size.width; //total size of all symbols in an image

  for (int i = 0; i < index; i++)
  {
    float sym_occur = seq.at<float>(0, i); //the number of times a sybmol has occured
    if (sym_occur > 0)                     //log of zero goes to infinity
    {
      cnt++;
      entr += (sym_occur / total_size) * (log2(total_size / sym_occur));
    }
  }

  int i = 0;
  for (int j = 0; j < 256; j++)
  {
    energy = seq.at<float>(i, j) * seq.at<float>(i, j);
    contrast = contrast + (i - j) * (i - j) * seq.at<float>(i, j);
    homogenity = homogenity + seq.at<float>(i, j) / (1 + abs(i - j));
  }

  v = {entr, energy, contrast, homogenity};

  return v;
}

Mat histograma(Mat image)
{
  // allcoate memory for no of pixels for each intensity value
  Mat histogram = Mat::zeros(Size(1, 256), CV_8UC1);

  // initialize all intensity values to 0
  for (int i = 0; i < 256; i++)
  {
    //std::cout<<i<<"\n";
    histogram.at<float>(0, i) = 0;
    //std::cout<<histogram.at<float>(0,i)<<"\n";
  }

  // calculate the no of pixels for each intensity values
  for (int y = 0; y < image.rows; y++)
    for (int x = 0; x < image.cols; x++)
    {
      std::cout << (int)image.at<uchar>(y, x) << "\n";
      histogram.at<float>(0, (int)image.at<uchar>(y, x))++;
      std::cout << histogram.at<float>(0, (int)image.at<uchar>(y, x)) << "\n";
    }

  return histogram;
}

float calc_prom_valores(std::vector<float> valores)
{
  float promedio = 0;
  float max_entropia = -309.502, min_entropia = -26770.8;
  float max_energia = 41895500000, min_energia = 0;
  float max_contraste = 18988200000, min_contraste = 4179000000;
  float max_homogeneidad = 417695, min_homogeneidad = 378049;

  if (min_entropia <= valores[0] && max_entropia >= valores[0])
    promedio = promedio + 12.5;

  if (min_energia <= valores[1] && max_energia >= valores[1])
    promedio = promedio + 12.5;

  if (min_contraste <= valores[2] && max_contraste >= valores[2])
    promedio = promedio + 12.5;

  if (min_homogeneidad <= valores[3] && max_homogeneidad >= valores[3])
    promedio = promedio + 12.5;

  return promedio;
}

float calc_prom_color(Mat img)
{
  int cafes = 0;
  cv::Size s = img.size();
  int rows = s.height;
  int cols = s.width;
  int total = rows * cols;

  for (int i = 0; i < img.rows; i++)
  {
    for (int j = 0; j < img.cols; j++)
    {
      if ((int)img.at<Vec3b>(j, i)[2] < 180 && (int)img.at<Vec3b>(j, i)[2] > 70)
      {
        if ((int)img.at<Vec3b>(j, i)[1] < 150 && (int)img.at<Vec3b>(j, i)[1] > 48)
        {
          if ((int)img.at<Vec3b>(j, i)[0] < 110 && (int)img.at<Vec3b>(j, i)[0] > 12)
          {
            cafes++;
          }
        }
      }

      if ((int)img.at<Vec3b>(j, i)[2] == 255)
      {
        if ((int)img.at<Vec3b>(j, i)[1] == 255)
        {
          if ((int)img.at<Vec3b>(j, i)[0] == 255)
          {
            total = total - 1;
          }
        }
      }
    }
  }

  float proba;
  proba = cafes * 50 / total;

  return proba;
}

Mat Calc_objeto(Mat dst1, int x, int y, int maxx, int minx, int maxy, int miny, bool colors)
{
  Mat objeto;

  if (colors == true)
  {
    std::vector<Mat> bgr_planes;
    split(dst1, bgr_planes);
    bgr_planes[0] = Calc_objeto(bgr_planes[0], x, y, maxx, minx, maxy, miny, false);
    bgr_planes[1] = Calc_objeto(bgr_planes[1], x, y, maxx, minx, maxy, miny, false);
    bgr_planes[2] = Calc_objeto(bgr_planes[2], x, y, maxx, minx, maxy, miny, false);
    merge(bgr_planes, objeto);

    return objeto;
  }

  objeto = Mat::zeros(Size(x, y), CV_8UC1);

  MatIterator_<Vec3b> it = dst1.begin<Vec3b>();
  MatIterator_<Vec3b> end = dst1.end<Vec3b>();

  MatIterator_<Vec3b> itobj = objeto.begin<Vec3b>();

  int ry = 0, rx = 0, cont = 0;
  for (; it != end; ++it, cont++)
  {
    //std::cout<<"x: "<<rx<<"\n y: "<<ry<<"\n";
    //std::cout<<"it: "<<(*it)<<"\n ";

    if (rx < maxx && rx > minx && ry < maxy && ry > miny)
    {
      (*itobj) = (*it);
      itobj++;
    }

    if (rx == 1023)
    {
      ry++;
      rx = 0;
    }
    else
    {
      rx++;
    }

    //std::cout<<"x: "<<rx<<"\n y; "<<ry<<"\n";
  }

  return objeto;
}

float esMadera(Mat img)
{
  //Declaracion de variables
  Point anchor;
  double delta;
  int ddepth;
  float data[] = {-1, -1, -1,
                  -1, 9, -1,
                  -1, -1, -1};
  Mat kernel(3, 3, CV_32F, data);
  anchor = Point(-1, -1);
  delta = 0;
  ddepth = -1;

  Mat image = img, dst, dst1, resta;
  float proba = 0;

  cvtColor(img, dst, COLOR_BGR2GRAY);

  filter2D(dst, dst1, ddepth, kernel, anchor, delta, BORDER_DEFAULT);

  resta = dst - dst1;

  int minx = 1025, miny = 1025, maxx = -1, maxy = -1;

  //Encuentro los minimos y maximos
  MatIterator_<Vec3b> it = dst1.begin<Vec3b>();
  MatIterator_<Vec3b> end = dst1.end<Vec3b>();
  int x = 0;
  int y = 0;
  minx = 1025;
  miny = 1025;
  maxx = 0;
  maxy = 0;

  // En esta sección de la funcion se encuentra el rectangulo donde se encuentra la imagen
  for (; it != end; ++it, x++)
  {
    if (x == 1024)
    {
      y++;
      x = 0;
    }
    if ((*it)[0] != 255)
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

  //func
  Mat objeto = Calc_objeto(dst1, maxx - minx - 1, maxy - miny - 1, maxx, minx, maxy, miny, false);

  Mat histogramap, histogramao;
  float range[] = {0, 256}; //the upper boundary is exclusive
  const float *histRange = {range};
  bool uniform = true, accumulate = false;

  calcHist(&objeto, 1, 0, Mat(), histogramao, 1, &histSize, &histRange, uniform, accumulate);

  std::vector<float> entropiao = entropy(histogramao, histogramao.size());

  Mat color_obj = Calc_objeto(image, maxx - minx - 1, maxy - miny - 1, maxx, minx, maxy, miny, true);
  proba = proba + calc_prom_color(color_obj);
  proba = proba + calc_prom_valores(entropiao);

  if (proba < 50)
  {
    proba = 0;
  }
  else
  {
    proba = 1;
  }
  return proba;
}

float esBotellaVive100(Mat img)
{

  Mat dst, dst3, bw_hist;
  int x, y, minx, miny, maxx, maxy;
  MatIterator_<Vec3b> it, end;
  double otsu;
  int umbral;
  bool black = false;
  int puntox = 0;
  int puntoy = 0;
  int numbins = 256;
  float range[] = {0, 256};
  const float *histRange = {range};
  int maximo = 0;
  float verdes = 0;
  float probabilidad = 0;

  cvtColor(img, dst, COLOR_BGR2GRAY);
  otsu = threshold(dst, dst3, 0, 255, THRESH_OTSU);
  it = dst3.begin<Vec3b>();
  end = dst3.end<Vec3b>();
  x = 0;
  y = 0;
  minx = 1025;
  miny = 1025;
  maxx = 0;
  maxy = 0;

  // En esta sección de la funcion se encuentra el rectangulo donde se encuentra la imagen
  for (; it != end; ++it, x++)
  {
    if (x == 1024)
    {
      y++;
      x = 0;
    }
    if ((*it)[0] != 255)
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
  umbral = maxy - miny;
  umbral = umbral * (0.33);
  for (int j = miny + umbral; j < maxy - 100; j++)
  {
    int cont = 0;
    black = false;
    while (!black)
    {

      if ((int)dst3.at<uchar>(j, cont) == 255)
      {
        cont++;
      }
      if ((int)dst3.at<uchar>(j, cont) != 255 || cont == 1023)
      {
        if (cont > maximo)
        {

          maximo = cont;
          puntoy = j;
          puntox = maximo;
        }
        black = true;
      }
    }
  }
  calcHist(&dst3, 1, 0, Mat(), bw_hist, 1, &numbins, &histRange);
  for (int i = minx; i < maxx; i++)
  {
    for (int j = miny; j < maxy; j++)
    {
      if ((int)img.at<Vec3b>(j, i)[0] > 20 && (int)img.at<Vec3b>(j, i)[0] < 90)
      {
        if ((int)img.at<Vec3b>(j, i)[1] > 70 && (int)img.at<Vec3b>(j, i)[1] < 160)
        {
          if ((int)img.at<Vec3b>(j, i)[2] > 0 && (int)img.at<Vec3b>(j, i)[2] < 50)
          {
            verdes++;
          }
        }
      }
    }
  }
  if (puntox - minx > 11 && puntox - minx < 55)
  {
    probabilidad += 0.7;
  }

  if (verdes * 100 / bw_hist.at<float>(0, 0) > 10)
  {
    probabilidad += 0.3;
  }
  return probabilidad;
}

int main(int argc, char **argv)
{
  Mat image;
  image = imread(argv[1], 1);
  if (!image.data)
  {
    std::cerr << "Error: No image data" << std::endl;
    return (-1);
  }

  float probaHoja = 0.0, probaMadera = 0.0, probaBotella = 0.0, probaTetrapack = 0.0;
  probaHoja = esHoja(image);
  probaMadera = esMadera(image);
  probaBotella = esBotellaVive100(image);
  probaTetrapack = esTetrapack(image);

  float valores[4];
  valores[0] = probaHoja;
  valores[1] = probaMadera;
  valores[2] = probaBotella;
  valores[3] = probaTetrapack;

  float max = 0.0;
  int maxindice = -1;

  for (int i = 0; i < 4; i++)
  {
    if (valores[i] > max)
    {
      max = valores[i];
      maxindice = i;
    }
  }
  switch (maxindice)
  {
  case 0:
    std::cout << "El objeto dentro de la imagen es posiblemente una Hoja" << std::endl;
    break;

  case 1:
    std::cout << "El objeto dentro de la imagen es posiblemente Madera" << std::endl;
    break;

  case 2:
    std::cout << "El objeto dentro de la imagen es posiblemente una Botella de vive 100 verde" << std::endl;
    break;
  case 3:
    std::cout << "El objeto dentro de la imagen es posiblemente una caja de Tetrapack" << std::endl;
    break;
    
  }
}