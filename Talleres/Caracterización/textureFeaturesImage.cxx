#include "itkImage.h"
#include "itkImageFileReader.h"
#include "itkImageFileWriter.h"
#include "itkHistogramToTextureFeaturesFilter.h"
#include "itkScalarImageToCooccurrenceMatrixFilter.h"
#include "itkVectorContainer.h"
#include "itkAddImageFilter.h"
#include "itkMultiplyImageFilter.h"
#include "itkRegionOfInterestImageFilter.h"
#include "itkRescaleIntensityImageFilter.h"

//definitions of used types
typedef itk::Image<unsigned char, 2> InternalImageType;
typedef itk::Image<unsigned char, 2> VisualizingImageType;
typedef itk::Neighborhood<float, 2> NeighborhoodType;
typedef itk::Statistics::ScalarImageToCooccurrenceMatrixFilter<InternalImageType> Image2CoOccuranceType;
typedef Image2CoOccuranceType::HistogramType HistogramType;
typedef itk::Statistics::HistogramToTextureFeaturesFilter<HistogramType> Hist2FeaturesType;
typedef InternalImageType::OffsetType OffsetType;
typedef itk::AddImageFilter <InternalImageType> AddImageFilterType;
typedef itk::MultiplyImageFilter<InternalImageType> MultiplyImageFilterType;
typedef itk::RescaleIntensityImageFilter< InternalImageType, InternalImageType > RescaleFilterType;
typedef itk::RegionOfInterestImageFilter<InternalImageType,InternalImageType> roiType;
typedef itk::ImageFileReader<InternalImageType> ReaderType;

//calculate features for one offset
void calcTextureFeatureROI ( OffsetType offset, InternalImageType::Pointer inputImage, unsigned int roiSize )
{
    
  Image2CoOccuranceType::Pointer glcmGenerator = Image2CoOccuranceType::New( );
  glcmGenerator->SetOffset( offset );
  glcmGenerator->SetNumberOfBinsPerAxis( 16 ); //reasonable number of bins
  glcmGenerator->SetPixelValueMinMax( 0, 255 ); //for input UCHAR pixel type

  Hist2FeaturesType::Pointer featureCalc = Hist2FeaturesType::New( );
    
  //region of interest
  roiType::Pointer roi = roiType::New( );
  roi->SetInput( inputImage );
    
  InternalImageType::RegionType window;
  InternalImageType::RegionType::SizeType size;
  size.Fill( roiSize ); //window size
  window.SetSize( size );
  window.SetIndex( 0, 0 );
  window.SetIndex( 1, 0 );
    
  roi->SetRegionOfInterest( window );
  roi->Update( );
    
  glcmGenerator->SetInput( roi->GetOutput( ) );
  glcmGenerator->Update( );
    
  featureCalc->SetInput( glcmGenerator->GetOutput( ) );
  featureCalc->Update( );
    
  std::cout << "Inertia: " << featureCalc->GetInertia( ) << std::endl;
  std::cout << "Correlation: " << featureCalc->GetCorrelation( ) << std::endl;
  std::cout << "Energy: " << featureCalc->GetEnergy( ) << std::endl;
  std::cout << "Entropy: " << featureCalc->GetEntropy( ) << std::endl;
  std::cout << "Homogeneity: " << featureCalc->GetInverseDifferenceMoment( ) << std::endl;

}

int main ( int argc, char* argv[] )
{
  if( argc < 3 )
  {
    std::cerr << "Usage: " << argv[0] << " <image_file> <roi_size>" << std::endl;
    return EXIT_FAILURE;
  }
  
  std::string fileName = argv[1];
  unsigned int roiSize = atoi( argv[2] );
  
  ReaderType::Pointer reader = ReaderType::New( );
  reader->SetFileName( fileName );
  reader->Update( );
  InternalImageType::Pointer image = reader->GetOutput( );
  
  NeighborhoodType neighborhood;
  neighborhood.SetRadius( 1 );
  unsigned int centerIndex = neighborhood.GetCenterNeighborhoodIndex( );
  
  OffsetType offset;
  
  for ( unsigned int d = 0; d < centerIndex; d++ )
  {
    offset = neighborhood.GetOffset( d );

    std::cout << "\nFor orientation " << d << ":\n";

    calcTextureFeatureROI( offset, image, roiSize );

  }

  return EXIT_SUCCESS;

}
