/*=========================================================================
  
  Program:   Insight Segmentation & Registration Toolkit
  Module:    itkNrrdImageIOTest.h
  Language:  C++
  Date:      $Date$
  Version:   $Revision$

  Copyright (c) Insight Software Consortium. All rights reserved.
  See ITKCopyright.txt or http://www.itk.org/HTML/Copyright.htm for details.

     This software is distributed WITHOUT ANY WARRANTY; without even 
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR 
     PURPOSE.  See the above copyright notices for more information.

=========================================================================*/
#ifndef __itkNrrdImageIOTest_h_
#define __itkNrrdImageIOTest_h_

#include <fstream>
#include "itkImageRegionIterator.h"
#include "itkImageIOBase.h"
#include "itkImageFileReader.h"
#include "itkImageFileWriter.h"
#include "itkImage.h"
#include "itkRandomImageSource.h"

template <class TPixelType, unsigned int VImageDimension>
typename itk::Image<TPixelType, VImageDimension>::Pointer
itkNrrdImageIOTestGenerateRandomImage(unsigned int size)
{
  typedef itk::Image<TPixelType, VImageDimension> ImageType;

  typename itk::RandomImageSource<ImageType>::Pointer source
    = itk::RandomImageSource<ImageType>::New();

  unsigned long sz[VImageDimension];
  float spacing[VImageDimension];
  float origin[VImageDimension];
  for (unsigned int i = 0; i < VImageDimension; i++)
    {
    sz[i]      = size;
    spacing[i] = static_cast<float>(i+1);
    origin[i]  = static_cast<float>(i);
    }
  
  source->SetSize(sz);
  source->SetOrigin(origin);
  source->SetSpacing(spacing);

  source->Update();
  return (source->GetOutput());  
}

template<class TPixelType, unsigned int VImageDimension>
int itkNrrdImageIOTestReadWriteTest(std::string fn, unsigned int size,
                                    std::string inputFile, bool compression=false)
{
  typedef itk::Image<TPixelType, VImageDimension> ImageType;

  typename itk::ImageFileReader<ImageType>::Pointer reader 
    = itk::ImageFileReader<ImageType>::New();
  typename itk::ImageFileWriter<ImageType>::Pointer writer
    = itk::ImageFileWriter<ImageType>::New();

  typename ImageType::Pointer image;

  if (inputFile != "null")
    {
    typename itk::ImageFileReader<ImageType>::Pointer tmpReader
      = itk::ImageFileReader<ImageType>::New();
    tmpReader->SetFileName(inputFile.c_str());
    try
      {
      tmpReader->Update();
      std::cout << "DONE READING INPUT IMAGE" << std::endl;
      }
    catch(itk::ExceptionObject &e)
      {
      std::cerr << e << std::endl;
      return EXIT_FAILURE;
      }
    
    image = tmpReader->GetOutput();
    }
  else
    {
    // Generate a random image.
    image = itkNrrdImageIOTestGenerateRandomImage<TPixelType, VImageDimension>(size);
    }
    
  // Write, then read the image.
  try
    {
    writer->SetFileName(fn.c_str());
    if (compression==true)
      { writer->UseCompressionOn(); }
    else
      { writer->UseCompressionOff();}
    reader->SetFileName(fn.c_str());
    //writer->SetFileName("testDebug.mhd");
    //reader->SetFileName("testDebug.mhd");
    
    }
  catch(itk::ExceptionObject &e)
    {
    std::cerr << e << std::endl;
    return EXIT_FAILURE;
    }
  
    writer->SetInput(image);
    
    image->Print(std::cout);
    std::cout << "----------" << std::endl;
    
  try
    {
    writer->Update();
    std::cout << "DONE WRITING TEST IMAGE" << std::endl;
    reader->Update();
    std::cout << "DONE READING TEST IMAGE" << std::endl;
    }
  catch (itk::ExceptionObject & e)
    {
    std::cerr << "Exception in file reader or writer " << std::endl;
    std::cerr << e.GetDescription() << std::endl;
    std::cerr << e.GetLocation() << std::endl;
    return EXIT_FAILURE;
    }

  // Print the image information.

  reader->GetOutput()->Print(std::cout);
  std::cout << std::endl;
  
  // Compare input and output images.
  itk::ImageRegionIterator<ImageType> a(image, image->GetRequestedRegion());
  itk::ImageRegionIterator<ImageType> b(reader->GetOutput(),
                                        reader->GetOutput()->GetRequestedRegion());
  for (a.GoToBegin(), b.GoToBegin(); ! a.IsAtEnd(); ++a, ++b)
    {
    if ( b.Get() != a.Get() )
      {
      std::cerr << "At index " << b.GetIndex() << " value " << b.Get() << " should be " << a.Get() << std::endl;
      return EXIT_FAILURE;
      }
    }
  return EXIT_SUCCESS;
}

#endif // __itkNrrdImageIOTest_h_
