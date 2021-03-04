#include <stdio.h>
#include <opencv2/opencv.hpp>

using namespace cv;


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
  Size size(2230,1248);

 

  cv::Point2f src_p[4];
    cv::Point2f dst_p[4];


    src_p[0] = cv::Point2f(0, 0);
    src_p[1] = cv::Point2f(   2230, 0);
    src_p[3] = cv::Point2f(  2230,    1248);
    src_p[2] = cv::Point2f(0,   1248);

    dst_p[0] = cv::Point2f(  216, 639);
    dst_p[1] = cv::Point2f(  2385,   780);
    dst_p[2] = cv::Point2f(  162,  1909);
    dst_p[3] = cv::Point2f(2397, 1876);

/*Camera
    float numCornersHor =  2230;
    float numCornersVer = 1248;
    int numSquares = numCornersHor * numCornersVer;
    Size board_sz = Size(numCornersHor, numCornersVer);
    VideoCapture capture = VideoCapture(0);
    vector<vector<Point3f>> object_points;
    vector<vector<Point2f>> image_points;
    Mat intrinsic = Mat(3, 3, CV_32FC1);
    Mat distCoeffs;
    vector<Mat> rvecs;
    vector<Mat> tvecs;
    intrinsic.ptr<float>(0)[0] = 1;
    intrinsic.ptr<float>(1)[1] = 1;

    cv:: calibrateCamera(dst_p, src_p, image.size(), intrinsic, distCoeffs, rvecs, tvecs);
*/


  Mat salida;
   salida= getPerspectiveTransform(dst_p,src_p);
   Mat dst;
   warpPerspective(image,dst, salida,size,INTER_LINEAR);

  std::stringstream ss( argv[ 1 ] );
  std::string basename;
  getline( ss, basename, '.' );
  imwrite( basename + "_camera.png", dst );
   
   return(0);
}

