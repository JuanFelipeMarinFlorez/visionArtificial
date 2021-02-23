#include <stdio.h>
#include <opencv2/opencv.hpp>

using namespace cv;
// functions

Mat resizer(Mat image, float newSize);



int main(int argc, char** argv )
{
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

    // rotar 
    Mat r(2,3,CV_64F, Scalar(0.0));
    r.at<double>(0,0) = -cos(35); 
    r.at<double>(0,1) = -sin (35);
    r.at<double>(1,0) = sin (35);
    r.at<double>(1,1) = -cos (35);

    //trasladar
    Mat t(2,3,CV_64F, Scalar(0.0));
    t.at<double>(0,0) = 1;      
    t.at<double>(0,2) = -42;   
    t.at<double>(1,1) = 1; 
    t.at<double>(1,2) = -37;

    //Escalar
    Mat s(2,3,CV_64F, Scalar(0.0));
    s.at<double>(0,0) = 0.8; 
    s.at<double>(1,1) = 0.8;
    

    Mat dest;
    Size size(image.cols,image.rows);
    warpAffine(image, dest, s, size, INTER_LINEAR, BORDER_CONSTANT);
    warpAffine(dest, dest, r, size, INTER_LINEAR, BORDER_CONSTANT);
    warpAffine(dest, dest, t, size, INTER_LINEAR, BORDER_CONSTANT);

    //imshow("outputImage", dest);
    std::stringstream ss( argv[ 1 ] );
    std::string basename;
    getline( ss, basename, '.' );

   //channels 
  
   imwrite( basename + "_R.png", dest );
   
   return(0);
}



Mat resizer(Mat image, float newSize){
   Mat res_img;
  resize(image, res_img, Size(), newSize, newSize, INTER_LINEAR);
  return res_img;
}
