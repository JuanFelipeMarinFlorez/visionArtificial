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
typedef itk::ImageFileWriter<InternalImageType> WriterType;

//calculate features for one offset
void calcTextureFeatureImage ( OffsetType offset, unsigned int windowSize,
  InternalImageType::Pointer inputImage, InternalImageType::Pointer outInertia,
  InternalImageType::Pointer outCorrelation, InternalImageType::Pointer outEnergy,
  InternalImageType::Pointer outEntropy, InternalImageType::Pointer outHomogeneity )
{
  //allocate output images
  outInertia->CopyInformation( inputImage );
  outInertia->SetRegions( inputImage->GetLargestPossibleRegion( ) );
  outInertia->Allocate( );
  outInertia->FillBuffer( 0 );

  outCorrelation->CopyInformation( inputImage );
  outCorrelation->SetRegions( inputImage->GetLargestPossibleRegion( ) );
  outCorrelation->Allocate( );
  outCorrelation->FillBuffer( 0 );

  outEnergy->CopyInformation( inputImage );
  outEnergy->SetRegions( inputImage->GetLargestPossibleRegion( ) );
  outEnergy->Allocate( );
  outEnergy->FillBuffer( 0 );

  outEntropy->CopyInformation( inputImage );
  outEntropy->SetRegions( inputImage->GetLargestPossibleRegion( ) );
  outEntropy->Allocate( );
  outEntropy->FillBuffer( 0 );

  outHomogeneity->CopyInformation( inputImage );
  outHomogeneity->SetRegions( inputImage->GetLargestPossibleRegion( ) );
  outHomogeneity->Allocate( );
  outHomogeneity->FillBuffer( 0 );

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
  size.Fill( windowSize ); //window size=3x3
  window.SetSize( size );
  InternalImageType::IndexType pi; //pixel index
  unsigned int disp = windowSize / 2;
    
  //slide window over the entire image
  for ( unsigned int x = disp; x < inputImage->GetLargestPossibleRegion( ).GetSize( 0 ) - disp; x++)
  {
    pi.SetElement( 0, x );
    window.SetIndex( 0, x - disp );

    for (unsigned int y = disp; y < inputImage->GetLargestPossibleRegion( ).GetSize( 1 ) - disp; y++)
    {
      pi.SetElement( 1, y );
      window.SetIndex( 1, y - disp );
      roi->SetRegionOfInterest( window );
      roi->Update( );

      glcmGenerator->SetInput( roi->GetOutput( ) );
      glcmGenerator->Update( );
      
      featureCalc->SetInput( glcmGenerator->GetOutput( ) );
      featureCalc->Update( );
      
      outInertia->SetPixel( pi, featureCalc->GetInertia( ) );
      outCorrelation->SetPixel( pi, featureCalc->GetCorrelation( ) );
      outEnergy->SetPixel( pi, featureCalc->GetEnergy( ) );
      outEntropy->SetPixel( pi, featureCalc->GetEntropy( ) );
      outHomogeneity->SetPixel( pi, featureCalc->GetInverseDifferenceMoment( ) );
    }
  }
}

int main ( int argc, char* argv[] )
{
  if( argc < 3 )
  {
    std::cerr << "Usage: " << argv[0] << " <image_file> <window_size>" << std::endl;
    return EXIT_FAILURE;
  }
  
  std::string fileName = argv[1];
  unsigned int winSize = atoi( argv[2] );
  
  ReaderType::Pointer reader = ReaderType::New( );
  reader->SetFileName( fileName );
  reader->Update( );
  InternalImageType::Pointer image = reader->GetOutput( );
  
  NeighborhoodType neighborhood;
  neighborhood.SetRadius( 1 );
  unsigned int centerIndex = neighborhood.GetCenterNeighborhoodIndex( );
  
  OffsetType offset;
  WriterType::Pointer writer = WriterType::New( );
  
  for ( unsigned int d = 0; d < centerIndex; d++ )
  { 
    offset = neighborhood.GetOffset( d );
    
    InternalImageType::Pointer inertia = InternalImageType::New( );
    InternalImageType::Pointer correlation = InternalImageType::New( );
    InternalImageType::Pointer energy = InternalImageType::New( );
    InternalImageType::Pointer entropy = InternalImageType::New( );
    InternalImageType::Pointer homogeneity = InternalImageType::New( );
    calcTextureFeatureImage(offset, winSize, image, inertia, correlation, energy, entropy, homogeneity);

    RescaleFilterType::Pointer rescaleInertiaFilter = RescaleFilterType::New( );
    rescaleInertiaFilter->SetInput( inertia );
    rescaleInertiaFilter->SetOutputMinimum( 0 );
    rescaleInertiaFilter->SetOutputMaximum( 255 );

    RescaleFilterType::Pointer rescaleCorrelationFilter = RescaleFilterType::New( );
    rescaleCorrelationFilter->SetInput( correlation );
    rescaleCorrelationFilter->SetOutputMinimum( 0 );
    rescaleCorrelationFilter->SetOutputMaximum( 255 );

    RescaleFilterType::Pointer rescaleEnergyFilter = RescaleFilterType::New( );
    rescaleEnergyFilter->SetInput( energy );
    rescaleEnergyFilter->SetOutputMinimum( 0 );
    rescaleEnergyFilter->SetOutputMaximum( 255 );

    RescaleFilterType::Pointer rescaleEntropyFilter = RescaleFilterType::New( );
    rescaleEntropyFilter->SetInput( entropy );
    rescaleEntropyFilter->SetOutputMinimum( 0 );
    rescaleEntropyFilter->SetOutputMaximum( 255 );

    RescaleFilterType::Pointer rescaleHomogeneityFilter = RescaleFilterType::New( );
    rescaleHomogeneityFilter->SetInput( homogeneity );
    rescaleHomogeneityFilter->SetOutputMinimum( 0 );
    rescaleHomogeneityFilter->SetOutputMaximum( 255 );
      
    writer->SetInput( rescaleInertiaFilter->GetOutput( ) );
    std::stringstream ssInertia;
    ssInertia << "Inertia" << d << ".png";
    writer->SetFileName( ssInertia.str( ) );
    writer->Update( );

    writer->SetInput( rescaleCorrelationFilter->GetOutput( ) );
    std::stringstream ssCorrelation;
    ssCorrelation << "Correlation" << d << ".png";
    writer->SetFileName( ssCorrelation.str( ) );
    writer->Update( );
      
    writer->SetInput( rescaleEnergyFilter->GetOutput( ) );
    std::stringstream ssEnergy;
    ssEnergy << "Energy" << d << ".png";
    writer->SetFileName( ssEnergy.str( ) );
    writer->Update( );

    writer->SetInput( rescaleEntropyFilter->GetOutput( ) );
    std::stringstream ssEntropy;
    ssEntropy << "Entropy" << d << ".png";
    writer->SetFileName( ssEntropy.str( ) );
    writer->Update( );

    writer->SetInput( rescaleHomogeneityFilter->GetOutput( ) );
    std::stringstream ssHomogeneity;
    ssHomogeneity << "Homogeneity" << d << ".png";
    writer->SetFileName( ssHomogeneity.str( ) );
    writer->Update( );
      
    std::cout << "Finished orientation " << d << "\n";

  }
  
  return EXIT_SUCCESS;
}
