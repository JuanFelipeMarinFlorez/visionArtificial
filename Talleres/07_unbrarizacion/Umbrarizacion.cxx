
#include <opencv2/opencv.hpp>
#include <iostream>
#include <math.h>

using namespace cv;

Mat cumsum(Mat nums) {
  Mat result(Size(nums.cols, nums.rows), CV_8UC1);
  float sum = 0;
   MatIterator_<Vec3b> it, nIt, end, endr;
    it = nums.begin<Vec3b>();
    nIt = result.begin<Vec3b>();
    end = nums.end<Vec3b>();
    endr = result.end<Vec3b>();
    for (; it != end && nIt != endr; it++,nIt++)
    {
            sum += (*it)[0];
            (*nIt)[0] = sum;
        
    }
  return result;
}


Mat Otso_fun (Mat img){

  //Se difumina una img con un filtro gaussiano
  Mat blur;
  GaussianBlur(img,blur,Size(5,5),0,0);

  //Para encontrar el umbral normalizado y su función de distribución
  Mat hist, hist_norm;
  int histSize = 256;
  float range[] = { 0, 256 }; 
  int channels[]={0};
  const float* histRange = { range };
  calcHist(&blur,1,channels,Mat(),hist,1,&histSize,&histRange, true,false);
  hist_norm = hist.reshape(1,1)/sum(hist);

//A partir de aqui toca pasar de python a c++ porque está el código en python
  Mat Q= cumsum(hist_norm);
//std::cout<<hist_norm<<std::endl;
  //std::cout<<"hola"<<std::endl;
  //std::cout<<Q<<std::endl;
  /*bins = np.arange(256)
  fn_min = np.inf
  thresh = -1

  for(int i; 0<i<=256; i++){
    p1,p2 = np.hsplit(hist_norm,[i]) # probabilities
      q1,q2 = Q[i],Q[255]-Q[i] # cum sum of classes
      if q1 < 1.e-6 or q2 < 1.e-6:
          continue
      b1,b2 = np.hsplit(bins,[i]) # weights
      m1,m2 = np.sum(p1*b1)/q1, np.sum(p2*b2)/q2
      v1,v2 = np.sum(((b1-m1)**2)*p1)/q1,np.sum(((b2-m2)**2)*p2)/q2
      fn = v1*q1 + v2*q2
      if fn < fn_min:
          fn_min = fn
          thresh = i
  }*/
  return blur;    
}

int main ( int argc, char** argv )
{
  // Declare variables
  Mat src;

    // Get command line arguments
  if ( argc < 2 ) {
    std::cerr << "Usage: " << argv[ 0 ] << " image_file" << std::endl;
    return( -1 );
  }

  // Review given command line arguments
  std::cout << "-------------------------" << std::endl;
  for( int a = 0; a < argc; a++ )
    std::cout << argv[ a ] << std::endl;
  std::cout << "-------------------------" << std::endl;

  const char* imageName = argc >=2 ? argv[1] : "lena.jpg";

  // Loads an image
  src = imread( imageName);
  if( src.empty() ) {
    printf(" Error opening image\n");
    printf(" Program Arguments: [image_name -- default lena.jpg] \n");
    return EXIT_FAILURE;
  }

  //Crea la matriz de destino
  Mat dest=Otso_fun(src);
    Size size(src.cols,src.rows);


  

  //para el nombre de la nueva imagen
    std::stringstream ss( argv[ 1 ] );
    std::string basename;
    getline( ss, basename, '.' );

   //channels 
  
   imwrite( basename + "resultado.png", dest );
   
   return(0);

}