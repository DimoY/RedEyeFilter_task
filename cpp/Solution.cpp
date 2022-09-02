#include "Solution.h"
void Solution::compute([[maybe_unused]]std::vector<PackedImage> *images){
  FunctionTracer<std::chrono::milliseconds> tracer("compute", "ms");
  this->eye.fixBatch(images);
}

void Solution::compute([[maybe_unused]]std::vector<StrideImage> *images){
  FunctionTracer<std::chrono::milliseconds> tracer("compute", "ms");
  this->eye.fixBatch(images);

}

