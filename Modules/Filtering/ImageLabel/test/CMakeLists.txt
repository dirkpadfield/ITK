itk_module_test()
set(ITKImageLabelTests
itkChangeLabelImageFilterTest.cxx
itkLabelContourImageFilterTest.cxx
itkBinaryContourImageFilterTest.cxx
)

CreateTestDriver(ITKImageLabel  "${ITKImageLabel-Test_LIBRARIES}" "${ITKImageLabelTests}")

itk_add_test(NAME itkChangeLabelImageFilterTest
      COMMAND ITKImageLabelTestDriver itkChangeLabelImageFilterTest)
itk_add_test(NAME itkLabelContourImageFilterTest0
      COMMAND ITKImageLabelTestDriver
      --compare ${ITK_DATA_ROOT}/Baseline/Review/itkLabelContourImageFilterTest0.png
      ${ITK_TEST_OUTPUT_DIR}/itkLabelContourImageFilterTest0.png
      itkLabelContourImageFilterTest
      ${ITK_DATA_ROOT}/Input/2th_cthead1.png
      ${ITK_TEST_OUTPUT_DIR}/itkLabelContourImageFilterTest0.png
      0 0)
itk_add_test(NAME itkLabelContourImageFilterTest1
      COMMAND ITKImageLabelTestDriver
      --compare ${ITK_DATA_ROOT}/Baseline/Review/itkLabelContourImageFilterTest1.png
      ${ITK_TEST_OUTPUT_DIR}/itkLabelContourImageFilterTest1.png
      itkLabelContourImageFilterTest
      ${ITK_DATA_ROOT}/Input/2th_cthead1.png
      ${ITK_TEST_OUTPUT_DIR}/itkLabelContourImageFilterTest1.png
      1 0)
itk_add_test(NAME itkBinaryContourImageFilterTest0
      COMMAND ITKImageLabelTestDriver
    --compare ${ITK_DATA_ROOT}/Baseline/Review/itkBinaryContourImageFilterTest0.png
              ${ITK_TEST_OUTPUT_DIR}/itkBinaryContourImageFilterTest0.png
    itkBinaryContourImageFilterTest ${ITK_DATA_ROOT}/Input/2th_cthead1.png ${ITK_TEST_OUTPUT_DIR}/itkBinaryContourImageFilterTest0.png 0 200 0)
itk_add_test(NAME itkBinaryContourImageFilterTest1
      COMMAND ITKImageLabelTestDriver
    --compare ${ITK_DATA_ROOT}/Baseline/Review/itkBinaryContourImageFilterTest1.png
              ${ITK_TEST_OUTPUT_DIR}/itkBinaryContourImageFilterTest1.png
    itkBinaryContourImageFilterTest ${ITK_DATA_ROOT}/Input/2th_cthead1.png ${ITK_TEST_OUTPUT_DIR}/itkBinaryContourImageFilterTest1.png 1 200 0)
