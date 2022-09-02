#include <array>
#include <vector>
#include "utils/EyePatterns.h"
#include "utils/Image.h"
#include <iostream>


class EyePatternConverter
{
private:
  const std::array<EyePattern, EYE_PATTERNS_COUNT>& patterns = EYE_PATTERNS;
  std::vector<std::array<bool,EYEPATTERNDOUBLE>> eyePatterns;
  int minimalEye;
  int remove;
  char whitespace;  
  int _image_width=0,_image_height=0;
  
  bool IsRed([[maybe_unused]]PackedImage *images,int X,int Y) const;
  bool IsRed([[maybe_unused]]StrideImage *images,int X,int Y) const;

  template <typename Image>
  bool checkSquare(Image *images,int patternId, int X, int Y);
  
  void changePixel(std::vector<PackedImage> *images,int imageIndex, int X, int Y) const;
  void changePixel(std::vector<StrideImage> *images,int imageIndex, int X, int Y) const;

  template <typename Image>
  void changeSquare(std::vector<Image> *images,int imageIndex,int patternId, int X, int Y);

  template <typename Image>
  void setResolution(Image *images);

  template <typename Image>
  void removeRedEyeAtIndex([[maybe_unused]]std::vector<Image> *images,size_t image_index);
public:

  void fixBatch(std::vector<PackedImage>* images);
  void fixBatch(std::vector<StrideImage>* images);
  explicit EyePatternConverter(int minimalEye=200,int remove=150,char whitespace=' ');
  static void printPattern(std::array<int,EYEPATTERNDOUBLE> patt);
  ~EyePatternConverter()= default;
};

