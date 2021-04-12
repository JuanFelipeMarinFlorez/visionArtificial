
#include <opencv2/opencv.hpp>
#include <iostream>
#include <math.h>

using namespace cv;

Otso_fun (Mat img){

  //Se difumina una img con un filtro gaussiano
  Mat blur = cv.GaussianBlur(img,(5,5),0)

  //Para encontrar el umbral normalizado y su función de distribución
  Mat hist, hist_norm;
  hist = cv.calcHist([blur],[0],None,[256],[0,256])
  hist_norm = hist.ravel()/hist.sum()

//A partir de aqui toca pasar de python a c++ porque está el código en python
  Q = hist_norm.cumsum()
  bins = np.arange(256)
  fn_min = np.inf
  thresh = -1

  for(int i; 0<i<=256; i++) 
  {
    p1,p2 = np.hsplit(hist_norm,[i]) # probabilities
      q1,q2 = Q[i],Q[255]-Q[i] # cum sum of classes
      if q1 < 1.e-6 or q2 < 1.e-6:
          continue
      b1,b2 = np.hsplit(bins,[i]) # weights
      # finding means and variances
      m1,m2 = np.sum(p1*b1)/q1, np.sum(p2*b2)/q2
      v1,v2 = np.sum(((b1-m1)**2)*p1)/q1,np.sum(((b2-m2)**2)*p2)/q2
      # calculates the minimization function
      fn = v1*q1 + v2*q2
      if fn < fn_min:
          fn_min = fn
          thresh = i
  }
      
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
  src = imread( imageName , IMREAD_COLOR ); // Load an image
  if( src.empty() ) {
    printf(" Error opening image\n");
    printf(" Program Arguments: [image_name -- default lena.jpg] \n");
    return EXIT_FAILURE;
  }

  //Crea la matriz de destino
  Mat dest;
    Size size(src.cols,src.rows);


  

  //para el nombre de la nueva imagen
    std::stringstream ss( argv[ 1 ] );
    std::string basename;
    getline( ss, basename, '.' );

   //channels 
  
   imwrite( basename + "resultado.png", dest );
   
   return(0);

}