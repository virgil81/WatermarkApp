#include "EngineProcessor.h"



dv::EngineProcessor::EngineProcessor()
{
}


dv::EngineProcessor::~EngineProcessor()
{
}

cv::Mat dv::EngineProcessor::Process(const std::string & imagePath, const std::string& imagePathW, bool ischecked)
{	
		Watermark_Processor wmprocessor(imagePath, imagePathW,ischecked);
		return wmprocessor.Watermark_start(ischecked);
	
}
