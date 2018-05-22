#include "Watermark_Processor.h"



Watermark_Processor::Watermark_Processor()
{
}


Watermark_Processor::~Watermark_Processor()
{
}

Watermark_Processor::Watermark_Processor(std::string path, std::string new_file, bool ischecked)
{
	_image1 = cv::imread(path);
	_hideimage1 = cv::imread(new_file);
	if (ischecked)
	{
		cv::resize(_hideimage1, _hideimage1, _image1.size() / 3);
		cv::GaussianBlur(_hideimage1, _hideimage1, cv::Size(3, 3), 2);
	}
	else
	{
		cv::resize(_hideimage1, _hideimage1, _image1.size());
	}
}

cv::Mat Watermark_Processor::Watermark_start(bool ischecked) {
	cv::Mat _result1 = _image1.clone();
	cv::Mat hiddenimage = _hideimage1.clone();

	if (ischecked)
	{
		cv::Mat roi = _result1(cv::Rect(_result1.cols - _hideimage1.cols,
			_result1.rows - _hideimage1.rows, _hideimage1.cols, _hideimage1.rows));

		//cv::addWeighted(roi,0.8, _hideimage1,0.2,0, roi);

		//for si modificam roi
		for (size_t i = 0; i < hiddenimage.cols; i++) {
			for (size_t j = 0; j < hiddenimage.rows; j++) {
				uchar pixel1 = hiddenimage.at<cv::Vec<uchar, 3>>(j, i).val[0];
				uchar pixel2 = hiddenimage.at<cv::Vec<uchar, 3>>(j, i).val[1];
				uchar pixel3 = hiddenimage.at<cv::Vec<uchar, 3 >>(j, i).val[2];

				if (pixel1 > 170 && pixel2 > 170 && pixel3 > 170) {
					roi.at<cv::Vec<uchar, 3>>(j, i).val[0] = cv::min(255.0,
						192 + 0.5 * roi.at<cv::Vec<uchar, 3>>(j, i).val[0]);
					roi.at<cv::Vec<uchar, 3>>(j, i).val[1] = cv::min(255.0,
						192 + 0.5 * roi.at<cv::Vec<uchar, 3>>(j, i).val[1]);
					roi.at<cv::Vec<uchar, 3>>(j, i).val[2] = cv::min(255.0,
						192 + 0.5 * roi.at<cv::Vec<uchar, 3>>(j, i).val[2]);
				}


			}
		}

		
	}
	else
	{
		
		cv::Mat hiddenimage = _hideimage1.clone();
		int _nobits = 4;

		for (size_t i = 0; i < _image1.cols; i++)
		{
			for (size_t j = 0; j < _image1.rows; j++)
			{
				//uchar val = _image.at<uchar>(j, i);
				//if (val != 0)
				_result1.at<cv::Vec<uchar, 3> >(j, i).val[0] = _image1.at<cv::Vec<uchar, 3> >(j, i).val[0] >> _nobits;
				_result1.at<cv::Vec<uchar, 3> >(j, i).val[1] = _image1.at<cv::Vec<uchar, 3> >(j, i).val[1] >> _nobits;
				_result1.at<cv::Vec<uchar, 3> >(j, i).val[2] = _image1.at<cv::Vec<uchar, 3> >(j, i).val[2] >> _nobits;

				_result1.at<cv::Vec<uchar, 3> >(j, i).val[0] = _result1.at<cv::Vec<uchar, 3> >(j, i).val[0] << _nobits;
				_result1.at<cv::Vec<uchar, 3> >(j, i).val[1] = _result1.at<cv::Vec<uchar, 3> >(j, i).val[1] << _nobits;
				_result1.at<cv::Vec<uchar, 3> >(j, i).val[2] = _result1.at<cv::Vec<uchar, 3> >(j, i).val[2] << _nobits;

				hiddenimage.at<cv::Vec<uchar, 3> >(j, i).val[0] = _hideimage1.at<cv::Vec<uchar, 3> >(j, i).val[0] >> 8 - _nobits;
				hiddenimage.at<cv::Vec<uchar, 3> >(j, i).val[1] = _hideimage1.at<cv::Vec<uchar, 3> >(j, i).val[1] >> 8 - _nobits;
				hiddenimage.at<cv::Vec<uchar, 3> >(j, i).val[2] = _hideimage1.at<cv::Vec<uchar, 3> >(j, i).val[2] >> 8 - _nobits;



				_result1.at<cv::Vec<uchar, 3> >(j, i).val[0] = _result1.at<cv::Vec<uchar, 3> >(j, i).val[0] | hiddenimage.at<cv::Vec<uchar, 3> >(j, i).val[0];
				_result1.at<cv::Vec<uchar, 3> >(j, i).val[1] = _result1.at<cv::Vec<uchar, 3> >(j, i).val[1] | hiddenimage.at<cv::Vec<uchar, 3> >(j, i).val[1];
				_result1.at<cv::Vec<uchar, 3> >(j, i).val[2] = _result1.at<cv::Vec<uchar, 3> >(j, i).val[2] | hiddenimage.at<cv::Vec<uchar, 3> >(j, i).val[2];
			}
		}
	}
	return _result1;
}
