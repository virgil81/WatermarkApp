#include "EngineProcessor.h"



dv::EngineProcessor::EngineProcessor()
{
}


dv::EngineProcessor::~EngineProcessor()
{
}

cv::Mat dv::EngineProcessor::Process(const std::string & imagePath, const std::string& imagePathW)
{
	Watermark_Processor wmprocessor(imagePath, imagePathW);
	return wmprocessor.Watermark_start();
}
