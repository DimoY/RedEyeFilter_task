#include <array>
#include <vector>
#include "utils/EyePatterns.h"
#include <iostream>


class EyePatternConverter
{
private:
  const std::array<EyePattern, EYE_PATTERNS_COUNT>& patterns = EYE_PATTERNS;
  std::vector<std::array<bool,EYEPATTERNDOUBLE>> eyePatterns;
  int minimalEye = 200;
  int remove = 150;
  char whitespace = ' ';
public:
  EyePatternConverter();
  std::pair<bool,std::array<int,EYEPATTERNDOUBLE> &> isRedEye(std::array<int,EYEPATTERNDOUBLE> &unfiltered);
 
  static void printPattern(std::array<int,EYEPATTERNDOUBLE> patt);
  ~EyePatternConverter(){};
};

