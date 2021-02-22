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

   cv::Mat t(2,3,CV_64F, Scalar(0.0));

   //translate 
   /*
    t.at<double>(0,0) = 1;      
    t.at<double>(0,2) = -42;   
    t.at<double>(1,1) = 1; 
     t.at<double>(1,2) = -37; 
   */
     // girar 
    t.at<double>(0,0) = sin(35);    
    t.at<double>(0,1) = cos(35);   
    t.at<double>(0,2) = 0;   
    t.at<double>(1,0) = -cos(35); 
    t.at<double>(1,1) = sin(35); 
     t.at<double>(1,2) = 0;
    /*
    t.at<double>(0,0) = 0.65532;    
    t.at<double>(0,1) = -0.45886;   
    t.at<double>(0,2) = -44.50126;   
    t.at<double>(1,0) = 0.45886; 
    t.at<double>(1,1) = 0.65532; 
     t.at<double>(1,2) = 4.97472; 
     */

    Mat dest;
    Size size(image.cols,image.rows);
    warpAffine(image, dest, t, size, INTER_LINEAR, BORDER_CONSTANT);

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

