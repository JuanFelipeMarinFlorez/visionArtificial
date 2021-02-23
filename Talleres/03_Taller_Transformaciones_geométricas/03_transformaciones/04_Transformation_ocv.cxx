#include <stdio.h>
#include <opencv2/opencv.hpp>

using namespace cv;

// Functions

int main(int argc, char **argv)
{
   // Get command line arguments
   if (argc < 2)
   {
      std::cerr << "Usage: " << argv[0] << " image_file" << std::endl;
      return (-1);

   } // fi

   // Review given command line arguments
   std::cout << "-------------------------" << std::endl;
   for (int a = 0; a < argc; a++)
      std::cout << argv[a] << std::endl;
   std::cout << "-------------------------" << std::endl;

   Mat image;
   image = imread(argv[1], 1);

   if (!image.data)
   {
      std::cerr << "Error: No image data" << std::endl;
      return (-1);

   } // fi

   //Create Traslation Matrix

   Mat Translate(2,3,CV_64F, Scalar(0,0));

   // Fill spaces with values (-42,37)

   Translate.at<double>(0,0) = 1;    
   Translate.at<double>(1,1) = 1; 
   Translate.at<double>(0,2) = -42;
   Translate.at<double>(1,2) = 37;

   //Create Rotation Matrix

   Mat Rotate = getRotationMatrix2D(Point2f(0,0),35,1);

   // Apply Translation and rotation

   Mat traslation, rotation, res_img;

   warpAffine(image, traslation, Translate, image.size(),BORDER_CONSTANT,0);
   warpAffine(traslation, rotation, Rotate, traslation.size(),BORDER_CONSTANT,0);
   //Scale 

   resize(rotation, res_img, res_img.size(), 0.1, 0.1, INTER_LINEAR);

   

   std::stringstream ss(argv[1]);
   std::string basename;
   getline(ss, basename, '.');

   imwrite(basename + "_Traslate.png", traslation);
   imwrite(basename + "_Rotate.png", rotation);
   imwrite(basename + "_Final.png", res_img);
}

