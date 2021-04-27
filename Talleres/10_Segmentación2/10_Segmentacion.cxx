// #include "itkImageFileReader.h"
// #include "itkImageFileWriter.h"
// #include "itkScalarToRGBPixelFunctor.h"
// #include "itkUnaryFunctorImageFilter.h"
// #include "itkVectorGradientAnisotropicDiffusionImageFilter.h"
// #include "itkWatershedImageFilter.h"
// #include "itkRescaleIntensityImageFilter.h"
// #include "itkScalarToRGBColormapImageFilter.h"
// #include "itkGradientMagnitudeImageFilter.h"

// // Run with:
// // ./SegmentWithWatershedImageFilter inputImageFile outputImageFile threshold level
// // e.g.
// // ./SegmentWithWatershedImageFilter BrainProtonDensitySlice.png OutBrainWatershed.png 0.005 .5
// // (A rule of thumb is to set the Threshold to be about 1 / 100 of the Level.)

// int
// main(int argc, char * argv[])
// {
//   if (argc < 5)
//   {
//     std::cerr << "Missing parameters." << std::endl;
//     std::cerr << "Usage: " << argv[0] << " inputImageFile outputImageFile threshold level" << std::endl;
//     return EXIT_FAILURE;
//   }

//   constexpr unsigned int Dimension = 2;

//   using InputImageType = itk::Image<unsigned char, Dimension>;
//   using FloatImageType = itk::Image<float, Dimension>;
//   using RGBPixelType = itk::RGBPixel<unsigned char>;
//   using RGBImageType = itk::Image<RGBPixelType, Dimension>;
//   using LabeledImageType = itk::Image<itk::IdentifierType, Dimension>;

//   using FileReaderType = itk::ImageFileReader<InputImageType>;
//   FileReaderType::Pointer reader = FileReaderType::New();
//   reader->SetFileName(argv[1]);

//   using GradientMagnitudeImageFilterType = itk::GradientMagnitudeImageFilter<InputImageType, FloatImageType>;
//   GradientMagnitudeImageFilterType::Pointer gradientMagnitudeImageFilter = GradientMagnitudeImageFilterType::New();

//   gradientMagnitudeImageFilter->SetInput(reader->GetOutput());
//   gradientMagnitudeImageFilter->Update();

//   using WatershedFilterType = itk::WatershedImageFilter<FloatImageType>;
//   WatershedFilterType::Pointer watershed = WatershedFilterType::New();

//   float threshold = std::stod(argv[3]);
//   float level = std::stod(argv[4]);

//   watershed->SetThreshold(threshold);
//   watershed->SetLevel(level);

//   watershed->SetInput(gradientMagnitudeImageFilter->GetOutput());
//   watershed->Update();

//   using RGBFilterType = itk::ScalarToRGBColormapImageFilter<LabeledImageType, RGBImageType>;
//   RGBFilterType::Pointer colormapImageFilter = RGBFilterType::New();
//   colormapImageFilter->SetColormap(itk::ScalarToRGBColormapImageFilterEnums::RGBColormapFilter::Jet);
//   colormapImageFilter->SetInput(watershed->GetOutput());
//   colormapImageFilter->Update();

//   using FileWriterType = itk::ImageFileWriter<RGBImageType>;
//   FileWriterType::Pointer writer = FileWriterType::New();
//   writer->SetFileName(argv[2]);
//   writer->SetInput(colormapImageFilter->GetOutput());
//   writer->Update();

//   return EXIT_SUCCESS;
// }

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------

// #include <iostream>

// #include "itkImageFileReader.h"
// #include "itkImageFileWriter.h"
// #include "itkScalarToRGBPixelFunctor.h"
// #include "itkUnaryFunctorImageFilter.h"
// #include "itkVectorGradientAnisotropicDiffusionImageFilter.h"
// #include "itkVectorMagnitudeImageFilter.h"
// #include "itkMorphologicalWatershedImageFilter.h"
// #include "itkRescaleIntensityImageFilter.h"
// #include "itkScalarToRGBColormapImageFilter.h"
// #include "itkGradientMagnitudeImageFilter.h"

// // Run with:
// // ./WatershedImageFilter threshold level
// // e.g.
// // ./WatershedImageFilter 0.005 .5
// // (A rule of thumb is to set the Threshold to be about 1 / 100 of the Level.)

// using UnsignedCharImageType = itk::Image<unsigned char, 2>;
// using FloatImageType = itk::Image<float, 2>;
// using RGBPixelType = itk::RGBPixel<unsigned char>;
// using RGBImageType = itk::Image<RGBPixelType, 2>;
// using LabeledImageType = itk::Image<unsigned long, 2>;

// static void
// CreateImage(UnsignedCharImageType::Pointer image);
// static void
// PerformSegmentation(FloatImageType::Pointer image, const float threshold, const float level);

// int
// main(int argc, char * argv[])
// {
//   // Verify arguments
//   if (argc < 3)
//   {
//     std::cerr << "Parameters " << std::endl;
//     std::cerr << " threshold level" << std::endl;
//     return 1;
//   }

//   // Parse arguments
//   std::string       strThreshold = argv[1];
//   float             threshold = 0.0;
//   std::stringstream ssThreshold;
//   ssThreshold << strThreshold;
//   ssThreshold >> threshold;

//   std::string       strLevel = argv[2];
//   float             level = 0.0;
//   std::stringstream ssLevel;
//   ssLevel << strLevel;
//   ssLevel >> level;

//   // Output arguments
//   std::cout << "Running with:" << std::endl
//             << "Threshold: " << threshold << std::endl
//             << "Level: " << level << std::endl;

//   UnsignedCharImageType::Pointer image = UnsignedCharImageType::New();
//   CreateImage(image);

//   using GradientMagnitudeImageFilterType = itk::GradientMagnitudeImageFilter<UnsignedCharImageType, FloatImageType>;
//   GradientMagnitudeImageFilterType::Pointer gradientMagnitudeImageFilter = GradientMagnitudeImageFilterType::New();
//   gradientMagnitudeImageFilter->SetInput(image);
//   gradientMagnitudeImageFilter->Update();

//   // Custom parameters
//   PerformSegmentation(gradientMagnitudeImageFilter->GetOutput(), threshold, level);

//   return EXIT_SUCCESS;
// }

// void
// CreateImage(UnsignedCharImageType::Pointer image)
// {
//   // Create a white image with 3 dark regions of different values

//   itk::Index<2> start;
//   start.Fill(0);

//   itk::Size<2> size;
//   size.Fill(200);

//   itk::ImageRegion<2> region(start, size);
//   image->SetRegions(region);
//   image->Allocate();
//   image->FillBuffer(255);

//   itk::ImageRegionIterator<UnsignedCharImageType> imageIterator(image, region);

//   while (!imageIterator.IsAtEnd())
//   {
//     if (imageIterator.GetIndex()[0] > 20 && imageIterator.GetIndex()[0] < 50 && imageIterator.GetIndex()[1] > 20 &&
//         imageIterator.GetIndex()[1] < 50)
//       imageIterator.Set(50);

//     ++imageIterator;
//   }

//   imageIterator.GoToBegin();

//   while (!imageIterator.IsAtEnd())
//   {
//     if (imageIterator.GetIndex()[0] > 60 && imageIterator.GetIndex()[0] < 80 && imageIterator.GetIndex()[1] > 60 &&
//         imageIterator.GetIndex()[1] < 80)
//       imageIterator.Set(100);

//     ++imageIterator;
//   }

//   imageIterator.GoToBegin();

//   while (!imageIterator.IsAtEnd())
//   {
//     if (imageIterator.GetIndex()[0] > 100 && imageIterator.GetIndex()[0] < 130 && imageIterator.GetIndex()[1] > 100 &&
//         imageIterator.GetIndex()[1] < 130)
//       imageIterator.Set(150);

//     ++imageIterator;
//   }

//   using FileWriterType = itk::ImageFileWriter<UnsignedCharImageType>;
//   FileWriterType::Pointer writer = FileWriterType::New();
//   writer->SetFileName("input.png");
//   writer->SetInput(image);
//   writer->Update();
// }

// void
// PerformSegmentation(FloatImageType::Pointer image, const float threshold, const float level)
// {
//   using MorphologicalWatershedFilterType = itk::MorphologicalWatershedImageFilter<FloatImageType, LabeledImageType>;
//   MorphologicalWatershedFilterType::Pointer watershedFilter = MorphologicalWatershedFilterType::New();
//   watershedFilter->SetLevel(level);
//   watershedFilter->SetInput(image);
//   watershedFilter->Update();

//   using RGBFilterType = itk::ScalarToRGBColormapImageFilter<LabeledImageType, RGBImageType>;
//   RGBFilterType::Pointer colormapImageFilter = RGBFilterType::New();
//   colormapImageFilter->SetInput(watershedFilter->GetOutput());
//   colormapImageFilter->SetColormap(itk::ScalarToRGBColormapImageFilterEnums::RGBColormapFilter::Jet);
//   colormapImageFilter->Update();

//   std::stringstream ss;
//   ss << "output_" << threshold << "_" << level << ".png";

//   using FileWriterType = itk::ImageFileWriter<RGBImageType>;
//   FileWriterType::Pointer writer = FileWriterType::New();
//   writer->SetFileName(ss.str());
//   writer->SetInput(colormapImageFilter->GetOutput());
//   writer->Update();
// }

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------

// #include "itkImage.h"
// #include "itkImageFileReader.h"
// #include "itkImageFileWriter.h"
// #include "itkConfidenceConnectedImageFilter.h"

// #include "itksys/SystemTools.hxx"
// #include <sstream>

// using namespace itk;

// typedef itk::Image<unsigned char, 2> ImageType;
// typedef itk::ImageFileWriter<ImageType> FileWriterType;

// int main(int argc, char *argv[])
// {
//   if (argc < 5)
//   {
//     std::cerr << "Required: filename.png seedX seedY output.png" << std::endl;

//     return EXIT_FAILURE;
//   }
//   std::string inputFileName = argv[1];

//   using ReaderType = itk::ImageFileReader<ImageType>;
//   ReaderType::Pointer reader = ReaderType::New();
//   reader->SetFileName(inputFileName.c_str());
//   reader->Update();

//   using ConfidenceConnectedFilterType = itk::ConfidenceConnectedImageFilter<ImageType, ImageType>;
//   ConfidenceConnectedFilterType::Pointer confidenceConnectedFilter = ConfidenceConnectedFilterType::New();
//   confidenceConnectedFilter->SetInitialNeighborhoodRadius(3);
//   confidenceConnectedFilter->SetMultiplier(3);
//   confidenceConnectedFilter->SetNumberOfIterations(25);
//   confidenceConnectedFilter->SetReplaceValue(255);

//   // Set seed
//   ImageType::IndexType seed;
//   seed[0] = std::stoi(argv[2]);
//   seed[1] = std::stoi(argv[3]);
//   confidenceConnectedFilter->SetSeed(seed);
//   confidenceConnectedFilter->SetInput(reader->GetOutput());

//   FileWriterType::Pointer writer = FileWriterType::New();
//   writer->SetFileName(argv[4]);
//   writer->SetInput(reader->GetOutput());
//   writer->Update();
  
//   return EXIT_SUCCESS;
// }