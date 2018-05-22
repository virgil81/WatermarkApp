#pragma once
#include "API.h"
#include "Watermark_Processor.h"
#include <opencv2/core/mat.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>


namespace dv
{
	class DLLEXP EngineProcessor
	{
	public:
		EngineProcessor();
		~EngineProcessor();

		cv::Mat Process(const std::string& imagePath, const std::string& imagePathW, bool ischecked);
		
		//cv::Mat Process(std::string file);
	};

}