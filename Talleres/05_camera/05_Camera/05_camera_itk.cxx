#include "itkImageFileReader.h"
#include "itkImageFileWriter.h"
#include "itkAffineTransform.h"
#include "itkResampleImageFilter.h"
#include "itkWindowedSincInterpolateImageFunction.h"
#include "itkPoint.h"
#include "itkAzimuthElevationToCartesianTransform.h"

// Output image type: 2-Dimal 1-byte grayscale
const unsigned int Dim = 2;
constexpr unsigned int Radius = 3;
typedef unsigned char             TPixel;
typedef itk::Image< TPixel, Dim > TImage;
// Input image type: 2-Dimal 1-byte rgb
typedef unsigned char                   TRGBResolution;
typedef itk::RGBPixel< TRGBResolution > TRGBPixel;
typedef itk::Image< TRGBPixel, Dim >    TColorImage;
using ScalarType = double;
// Type definitions

typedef itk::ImageFileReader< TColorImage > TReader;
typedef itk::ImageFileWriter< TImage > TWriter;
typedef itk::ImageFileWriter< TColorImage > TColorWriter;
typedef itk::WindowedSincInterpolateImageFunction<TColorImage, Radius> InterpolatorType;
typedef itk::ResampleImageFilter<TColorImage, TColorImage> ResampleImageFilterType ;
typedef itk::AffineTransform<ScalarType, Dim> TransformType ;
typedef itk::Matrix<ScalarType, Dim + 1, Dim + 1> MatrixType;
typedef itk::Point<double, 3> PointType;
typedef itk::AzimuthElevationToCartesianTransform<double, 3> AzimuthElevationToCartesian;




int main(int argc, char * argv[])
{
  if( argc < 2 )
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
  TReader::Pointer reader = TReader::New( );
  reader->SetFileName( argv[ 1 ] );
  try
  {
    reader->Update( );

  }
  catch( itk::ExceptionObject& err )
  {
    std::cerr << "Error: " << err << std::endl;
    return( 1 );

  } // yrt
  TColorImage* img = reader->GetOutput( );
  TColorImage::SizeType inputSize = img->GetLargestPossibleRegion( ).GetSize( );

  
  MatrixType matrix;
  matrix[0][0] = std::cos(25);
  matrix[0][1] = std::sin(25);
  matrix[0][2] = 0.;

  matrix[1][0] = -matrix[0][1];
  matrix[1][1] = matrix[0][0];
  matrix[1][2] = 0.;

  matrix[2][0] = -100.;
  matrix[2][1] = -50.;
  matrix[2][2] = 1.;

  ResampleImageFilterType::Pointer resample = ResampleImageFilterType::New();
  resample->SetInput(img);
  resample->SetReferenceImage(img);
  resample->UseReferenceImageOn();
  resample->SetSize(inputSize);
  
  InterpolatorType::Pointer interpolator = InterpolatorType::New();

  resample->SetInterpolator(interpolator);
  TransformType::Pointer transform = TransformType::New();

  TransformType::ParametersType parameters(Dim * Dim + Dim);
  for (unsigned int i = 0; i < Dim; i++)
  {
    for (unsigned int j = 0; j < Dim; j++)
    {
      parameters[i * Dim + j] = matrix[i][j];
    }
  }
  for (unsigned int i = 0; i < Dim; i++)
  {
    parameters[i + Dim * Dim] = matrix[i][Dim];
  }
  transform->SetParameters(parameters);

  resample->SetTransform(transform);

  PointType spherical;
  spherical[0] = 0.0;
  spherical[1] = 45; 
  spherical[2] = 1;
  AzimuthElevationToCartesian::Pointer azimuthElevation = AzimuthElevationToCartesian::New();
  PointType cartesian = azimuthElevation->TransformAzElToCartesian(spherical);
   
   MatrixType matrix2;
  matrix2[0][0] = cartesian[0];
  matrix2[0][1] = cartesian[1];
  matrix2[0][2] = cartesian[2];

  ResampleImageFilterType::Pointer resample2 = ResampleImageFilterType::New();
  resample2->SetInput(img);
  resample2->SetReferenceImage(img);
  resample2->UseReferenceImageOn();
  resample2->SetSize(inputSize);
  
  InterpolatorType::Pointer interpolator2 = InterpolatorType::New();

  resample->SetInterpolator(interpolator2);
  TransformType::Pointer transform2 = TransformType::New();

  TransformType::ParametersType parameters2(Dim * Dim + Dim);
  for (unsigned int i = 0; i < 1; i++)
  {
    for (unsigned int j = 0; j < 3; j++)
    {
      parameters2[i * Dim + j] = matrix2[i][j];
    }
  }
  for (unsigned int i = 0; i < 1; i++)
  {
    parameters2[i + Dim * Dim] = matrix2[i][Dim];
  }
  transform2->SetParameters(parameters2);

  resample2->SetTransform(transform2);

  // Write results
  std::stringstream ss( argv[ 1 ] );
  std::string basename;
  getline( ss, basename, '.' );

  TWriter::Pointer writer = TWriter::New( );
  TColorWriter::Pointer cwriter = TColorWriter::New();
  
  cwriter->SetInput( resample->GetOutput() );
  cwriter->SetFileName( basename + "_transformacion_afin.png" );
  try
  {
    cwriter->Update( );

  }
  catch( itk::ExceptionObject& err )
  {
    std::cerr << "Error: " << err << std::endl;
    return( 1 );

  } // yrt

  cwriter->SetInput( resample2->GetOutput() );
  cwriter->SetFileName( basename + "_transformacion2.png" );
  try
  {
    cwriter->Update( );

  }
  catch( itk::ExceptionObject& err )
  {
    std::cerr << "Error: " << err << std::endl;
    return( 1 );

  } // yrt


   
   return (0);

}