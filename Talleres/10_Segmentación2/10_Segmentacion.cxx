#include "itkImage.h"
#include "itkImageFileReader.h"
#include "itkImageFileWriter.h"
#include "itkScalarToRGBPixelFunctor.h"
#include "itkUnaryFunctorImageFilter.h"
#include "itkVectorGradientAnisotropicDiffusionImageFilter.h"
#include "itkWatershedImageFilter.h"
#include "itkRescaleIntensityImageFilter.h"
#include "itkScalarToRGBColormapImageFilter.h"
#include "itkGradientMagnitudeImageFilter.h"
#include "itkMorphologicalWatershedImageFilter.h"
#include "itkConfidenceConnectedImageFilter.h"

using UnsignedCharImageType = itk::Image<unsigned char, 2>;
using FloatImageType = itk::Image<float, 2>;
using RGBPixelType = itk::RGBPixel<unsigned char>;
using RGBImageType = itk::Image<RGBPixelType, 2>;
using LabeledImageType = itk::Image<unsigned long, 2>;
using ImageType = itk::Image<unsigned char, 2>;

static void
PerformSegmentation(FloatImageType::Pointer image, const float threshold, const float level);


int
main(int argc, char * argv[])
{
  if (argc < 2)
  {
    std::cerr << "Missing parameters." << std::endl;
    std::cerr << "Usage: " << argv[0] << " inputImageFile outputImageFile" << std::endl;
    return EXIT_FAILURE;
  }

  //Parámetros
  constexpr unsigned int Dimension = 2;
  //Segmentado
  //Los datos son de ejemplo, se pueden cambiar
  //Que el segmentado sea 1/100 del nivel
  float threshold = 0.005;

  //Nivel
  float level = 0.15;


  //Morphological Watershed Segmentation----------------------------------------------------------------------------------------------

  

  using InputImageType = itk::Image<unsigned char, Dimension>;
  using FloatImageType = itk::Image<float, Dimension>;
  using RGBPixelType = itk::RGBPixel<unsigned char>;
  using RGBImageType = itk::Image<RGBPixelType, Dimension>;
  using LabeledImageType = itk::Image<itk::IdentifierType, Dimension>;

  using FileReaderType = itk::ImageFileReader<InputImageType>;
  FileReaderType::Pointer reader = FileReaderType::New();
  reader->SetFileName(argv[1]);;


  using GradientMagnitudeImageFilterType = itk::GradientMagnitudeImageFilter<InputImageType, FloatImageType>;
  GradientMagnitudeImageFilterType::Pointer gradientMagnitudeImageFilter = GradientMagnitudeImageFilterType::New();

  gradientMagnitudeImageFilter->SetInput(reader->GetOutput());
  gradientMagnitudeImageFilter->Update();


  using WatershedFilterType = itk::WatershedImageFilter<FloatImageType>;
  WatershedFilterType::Pointer watershed = WatershedFilterType::New();

  watershed->SetThreshold(threshold);
  watershed->SetLevel(level);

  watershed->SetInput(gradientMagnitudeImageFilter->GetOutput());
  watershed->Update();

  using RGBFilterType = itk::ScalarToRGBColormapImageFilter<LabeledImageType, RGBImageType>;
  RGBFilterType::Pointer colormapImageFilter = RGBFilterType::New();
  colormapImageFilter->SetColormap(itk::ScalarToRGBColormapImageFilterEnums::RGBColormapFilter::Jet);
  colormapImageFilter->SetInput(watershed->GetOutput());
  colormapImageFilter->Update();

  using FileWriterType = itk::ImageFileWriter<RGBImageType>;
  FileWriterType::Pointer writer = FileWriterType::New();
  writer->SetFileName( "watershed_" +  reader->GetFileName() );
  writer->SetInput(colormapImageFilter->GetOutput());
  writer->Update();

  using ConfidenceConnectedFilterType = itk::ConfidenceConnectedImageFilter<ImageType, ImageType>;
  ConfidenceConnectedFilterType::Pointer confidenceConnectedFilter = ConfidenceConnectedFilterType::New();
  confidenceConnectedFilter->SetInitialNeighborhoodRadius(5);
  confidenceConnectedFilter->SetMultiplier(3);
  confidenceConnectedFilter->SetNumberOfIterations(25);
  confidenceConnectedFilter->SetReplaceValue(255);

  //Funcion Con Seed, la seed se encuentra en el centro para nuestro ejemplo

  using NewFileWriterType = itk::ImageFileWriter<ImageType>;
  ImageType::IndexType seed;
  seed[0] = std::stoi("400");
  seed[1] = std::stoi("245");
  confidenceConnectedFilter->SetSeed(seed);
  confidenceConnectedFilter->SetInput(reader->GetOutput());

  NewFileWriterType::Pointer newWriter = NewFileWriterType::New();
  newWriter->SetFileName( "seed_Segmentation_" +  reader->GetFileName() );
  newWriter->SetInput(confidenceConnectedFilter->GetOutput());
  newWriter->Update();

  //Watershed Image Filter----------------------------------------------------------------------------------------------


  // Se llama a la función que hace la segmentación
  PerformSegmentation(gradientMagnitudeImageFilter->GetOutput(), threshold, level);

  //Funcion Con Seed, la seed se encuentra en el centro para nuestro ejemplo


  

  return EXIT_SUCCESS;
}

void
PerformSegmentation(FloatImageType::Pointer image, const float threshold, const float level)
{

  using MorphologicalWatershedFilterType = itk::MorphologicalWatershedImageFilter<FloatImageType, LabeledImageType>;
  MorphologicalWatershedFilterType::Pointer watershedFilter = MorphologicalWatershedFilterType::New();
  watershedFilter->SetLevel(level);
  watershedFilter->SetInput(image);
  watershedFilter->Update();

  using RGBFilterType = itk::ScalarToRGBColormapImageFilter<LabeledImageType, RGBImageType>;
  RGBFilterType::Pointer colormapImageFilter = RGBFilterType::New();
  colormapImageFilter->SetInput(watershedFilter->GetOutput());
  colormapImageFilter->SetColormap(itk::ScalarToRGBColormapImageFilterEnums::RGBColormapFilter::Jet);
  colormapImageFilter->Update();


  using FileWriterType = itk::ImageFileWriter<RGBImageType>;
  FileWriterType::Pointer writer = FileWriterType::New();
  writer->SetFileName( "watershed_image_filter.png" );
  writer->SetInput(colormapImageFilter->GetOutput());
  writer->Update();

}