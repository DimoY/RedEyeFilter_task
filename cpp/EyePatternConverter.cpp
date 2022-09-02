#include "EyePatternConverter.h"

/**
 * @brief Construct a new Eye Pattern Converter:: Eye Pattern Converter object from the available patterns
 *
 */
EyePatternConverter::EyePatternConverter(int minimalEye,int remove,char whitespace):minimalEye(minimalEye),remove(remove),whitespace(whitespace)
{
	for (auto pattern : this->patterns)
	{

		std::array<bool, EYEPATTERNDOUBLE> intPattern{};
		for (size_t z = 0; z < EYE_PATTERN_COL_SIZE; z++)
		{
			for (size_t j = 0; j < EYE_PATTERN_COL_SIZE; j++)
			{
				intPattern[z * EYE_PATTERN_COL_SIZE + j] = pattern[z][j] - this->whitespace != 0;
			}
		}
		this->eyePatterns.push_back(intPattern);
	}
}

/**
 * @brief check if a pixel is above the red treshhold
 * 
 * @param images the image
 * @param X the x coordinate
 * @param Y the y coordinate
 * @return true yes it is
 * @return false no it is not
 */
inline bool EyePatternConverter::IsRed([[maybe_unused]] PackedImage *images, int X, int Y) const
{
	return images->pixels[Y * this->_image_width + X].red < this->minimalEye;
}
/**
 * @brief check if a pixel is above the red treshhold
 * 
 * @param images the image
 * @param X the x coordinate
 * @param Y the y coordinate
 * @return true yes it is
 * @return false no it is not
 */
inline bool EyePatternConverter::IsRed([[maybe_unused]] StrideImage *images, int X, int Y) const
{
	return images->redPixels[Y * this->_image_width + X] < this->minimalEye;
}

/**
 * @brief Check if a pattern is completed in the space
 * 
 * @tparam Image either PackedImage or StrideImage
 * @param images the image to be checked
 * @param patternId the pattern to be checked
 * @param X the x coordinate
 * @param Y the y coordinate
 * @return true yes there is an occurrence of this pattern that exists here
 * @return false no there is not an occurrence of this pattern that exists here
 */
template <typename Image>
bool EyePatternConverter::checkSquare(Image *images, int patternId, int X, int Y)
{
	for (int i = 0; i < EYE_PATTERN_COL_SIZE; i++)
	{
		for (int j = 0; j < EYE_PATTERN_COL_SIZE; j++)
		{
			if (this->eyePatterns[patternId][i * EYE_PATTERN_COL_SIZE + j] != 0 &&
				this->IsRed(images, (X + j), (Y + i)))
			{

				return false;
			}
		}
	}
	return true;
}

/**
 * @brief Remove value from a specific pixel
 * 
 * @param images the pointer to the list of images ( did it like this because i was not sure if it ok to change a lot of things about the skeleton)
 * @param imageIndex the index of the image
 * @param X the x coordinate
 * @param Y the y coordinate
 */
void EyePatternConverter::changePixel(std::vector<PackedImage> *images, int imageIndex, int X, int Y) const
{
	(*images)[imageIndex].pixels[Y * this->_image_width + X].red -= this->remove;
}
/**
 * @brief Remove value from a specific pixel
 * 
 * @param images the pointer to the list of images ( did it like this because i was not sure if it ok to change a lot of things about the skeleton)
 * @param imageIndex the index of the image
 * @param X the x coordinate
 * @param Y the y coordinate
 */
void EyePatternConverter::changePixel(std::vector<StrideImage> *images, int imageIndex, int X, int Y) const
{
	(*images)[imageIndex].redPixels[Y * _image_width + X] -= this->remove;
}

/**
 * @brief Remove the values of pixels in a specific pattern 
 * 
 * @tparam Image either Packed image or Stride Image 
 * @param images the list of images ( did it like this because i was not sure if it ok to change a lot of things about the skeleton)
 * @param imageIndex the specific index
 * @param patternId the pattern that should be used
 * @param X the x coordinate
 * @param Y the Y coordinate
 */
template <typename Image>
void EyePatternConverter::changeSquare(std::vector<Image> *images, int imageIndex, int patternId, int X, int Y)
{
	for (int i = 0; i < EYE_PATTERN_COL_SIZE; i++)
	{
		for (int j = 0; j < EYE_PATTERN_COL_SIZE; j++)
		{
			if (this->eyePatterns[patternId][i * EYE_PATTERN_COL_SIZE + j] != 0)
				this->changePixel(images, imageIndex, (X + j),(Y + i));
		}
	}
}

/**
 * @brief  set the values of the resolution variables based on the image
 * 
 * @tparam Image either Packed image or Stride Image 
 * @param images 
 */
template <typename Image>
void EyePatternConverter::setResolution(Image *images)
{
	this->_image_width = images->resolution.width;
	this->_image_height = images->resolution.height;
}

/**
 * @brief Remove the red eyes in an image at a specific index
 * 
 * @tparam Image either Packed image or Stride Image 
 * @param images the list of images ( did it like this because i was not sure if it ok to change a lot of things about the skeleton)
 * @param image_index the specific image index to be used
 */
template <typename Image>
void EyePatternConverter::removeRedEyeAtIndex(std::vector<Image> *images, size_t image_index)
{
	this->setResolution(&images[0][image_index]);
	for (int Yindex = 0; Yindex < _image_height; Yindex++)
	{
		for (int Xindex = 0; Xindex < _image_width; Xindex++)
		{
			bool eye;
			for (int pattern = 0; pattern < this->eyePatterns.size(); pattern++)
			{
				eye = this->checkSquare(&(images[0][image_index]), pattern, Xindex, Yindex);

				if (eye)
				{
					this->changeSquare(images, image_index, pattern, Xindex, Yindex);
				}
			}
		}
	}
}

/**
 * @brief Fix a whole list of images
 * @param images list of images
 */
void EyePatternConverter::fixBatch(std::vector<PackedImage> *images)
{
	for (size_t image_index = 0; image_index < images->size(); image_index++)
	{
		this->removeRedEyeAtIndex(images, image_index);
	}
}
/**
 * @brief Fix a whole list of images
 * @param images list of images
 */
void EyePatternConverter::fixBatch(std::vector<StrideImage> *images)
{
	for (size_t image_index = 0; image_index < images->size(); image_index++)
	{
		this->removeRedEyeAtIndex(images, image_index);
	}
}