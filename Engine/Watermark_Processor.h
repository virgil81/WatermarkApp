#pragma once
#include <opencv2/core/mat.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <string>

class Watermark_Processor
{
public:
	Watermark_Processor();
	~Watermark_Processor();
	Watermark_Processor(std::string path, std::string new_file, bool ischecked);
	cv::Mat Watermark_start(bool);

private:
	cv::Mat _image1;
	cv::Mat _hideimage1;
	

};

