#include "EyePatternConverter.h"
/**
 * @brief Construct a new Eye Pattern Converter:: Eye Pattern Converter object from the available patterns
 * 
 */
EyePatternConverter::EyePatternConverter(){
    for (auto pattern : this->patterns)
    {

        std::array<bool,EYEPATTERNDOUBLE> intPattern;
        for (size_t z = 0; z < EYE_PATTERN_COL_SIZE; z++)
        {
            for (size_t j = 0; j < EYE_PATTERN_COL_SIZE; j++)
            {
                intPattern[z*EYE_PATTERN_COL_SIZE+j] = pattern[z][j]-this->whitespace!=0;

            }
        }
        this->eyePatterns.push_back(intPattern);
    }

}
/**
 * @brief a check if the 5 by 5 box contains an eye
 * 
 * @param unfiltered an one dim array that contains by 5x5 grid
 * @return std::pair<bool,std::array<int,EYEPATTERNDOUBLE> &>  first parrameter is a indicatior if there is an eye the seccond is the new matrix if there is an eye
 */
std::pair<bool,std::array<int,EYEPATTERNDOUBLE> &> EyePatternConverter::isRedEye(std::array<int,EYEPATTERNDOUBLE> &unfiltered){
    bool eye;
    for (auto pattern : this->eyePatterns)
    {
        eye=true;
        for (size_t i = 0; i < EYEPATTERNDOUBLE; i++)
        {
            if(pattern[i]==1 && unfiltered[i]<this->minimalEye){
                eye=false;
                break;
            }
        }

        //array order !!
        if(eye==true)[[unlikely]]{
            for (size_t i = 0; i < EYEPATTERNDOUBLE; i++)
            {
                if(pattern[i]==1) unfiltered[i]-=this->remove;
            }
            //return true;
            return std::pair<bool,std::array<int,EYEPATTERNDOUBLE>&>(true,unfiltered);
        }
    }

    //return std::pair<bool,std::array<int,EYEPATTERNDOUBLE>>(true,unfiltered);
    //return false;
    return std::pair<bool,std::array<int,EYEPATTERNDOUBLE>&>(false,unfiltered);
}
/**
 * @brief print the 5 by 5 pattern
 * 
 * @param patt the pattern as a one dim. array
 */
void EyePatternConverter::printPattern(std::array<int,EYEPATTERNDOUBLE> patt){
    for (size_t i = 0; i < EYE_PATTERN_COL_SIZE; i++)
    {
      for (size_t j = 0; j < EYE_PATTERN_COL_SIZE; j++)
      {
        std::cout<<patt[i*EYE_PATTERN_COL_SIZE+j]<<" ";
      }
      std::cout<<std::endl;
    }
    std::cout<<std::endl;
    
  }