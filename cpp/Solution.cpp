#include "Solution.h"
#include "utils/EyePatterns.h"




void Solution::compute([[maybe_unused]]std::vector<StrideImage> &images) {
    FunctionTracer<std::chrono::milliseconds> tracer("compute", "ms");
    for (size_t image_index = 0; image_index < images.size(); image_index++)
    {
      auto image = images[image_index];
      for (size_t i = 0; i < image.resolution.height-5; i++)
      {
        for (size_t j = 0; j < image.resolution.width-5; j++)
        {
          std::array<int,EYEPATTERNDOUBLE> PotentialEye;
          for (size_t widti = 0; widti < 5; widti++)
          {
            for (size_t heighti = 0; heighti < 5; heighti++)
            {
              PotentialEye[widti*EYE_PATTERN_COL_SIZE+heighti] = image.redPixels[(i+widti)*image.resolution.width+j+heighti];
            }
          }
          
          auto result = eye.isRedEye(PotentialEye);
          if(result.first == true)[[unlikely]]{
            for (size_t widti = 0; widti < 5; widti++)
            {
              for (size_t heighti = 0; heighti < 5; heighti++)
              {
                images[image_index].redPixels[(i+widti)*image.resolution.width+j+heighti] = result.second[widti*EYE_PATTERN_COL_SIZE+heighti];
              }
            }
          }
          
        }
        
      
      
    }
    }
    
      

    
  }