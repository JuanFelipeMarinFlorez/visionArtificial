#include <stdio.h>
#include <opencv2/opencv.hpp>

using namespace cv;


int main(int argc, char** argv )
{
  // Declarar varibles
  Mat dst;
  Mat kernel;
  Point anchor;
  double delta;
  int ddepth;
  int kernel_size = 3;
  const char* window_name = "filter2D Demo";


  // Get command line arguments
  if ( argc < 2 )
  {
  	std::cerr << "Usage: " << argv[ 0 ] << " image_file" << std::endl;
    return( -1 );

  } // fi

  // Review given command line arguments
  std::cout << "-------------------------" << std::endl;
  for( int a = 0; a < argc; a++ )
    std::cout << argv[ a ] << std::endl;
   std::cout << "-------------------------" << std::endl;
   // Read an image
   Mat image;
   image = imread( argv[1], 1 );

   if ( !image.data )
   {
      std::cerr << "Error: No image data" << std::endl;
      return( -1);
   
   }// fi

  // Initialize arguments for the filter
    anchor = Point( -1, -1 );
    delta = 0;
    ddepth = -1;

  // definir filtro
   kernel = Mat::ones( kernel_size, kernel_size, CV_32F )/ (float)(kernel_size*kernel_size);

   // Apply filter
    filter2D(image, dst, ddepth , kernel, anchor, delta, BORDER_DEFAULT );
    

    std::stringstream ss( argv[ 1 ] );
    std::string basename;
    getline( ss, basename, '.' );
    imwrite( basename + "_filtro1.png", dst );
  

   return(0);
}

