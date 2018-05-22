// This is the main DLL file.

#include "stdafx.h"

#include "EngineWrapper.h"

dv::EngineWrapper::EngineWrapper()
{
	_engineprocessor = new dv::EngineProcessor();
}

dv::EngineWrapper::~EngineWrapper()
{
	delete _engineprocessor;
}

dv::EngineWrapper::!EngineWrapper()
{
	delete _engineprocessor;
}

BitmapSource ^ dv::EngineWrapper::Process(System::String ^ imagePath, System::String ^ imagePathW, Boolean ischeked)
{
	try
	{
		cv::Mat result;
		result = _engineprocessor->Process(MarshalString(imagePath), MarshalString(imagePathW), ischeked);
		return ToBitmapSource(result);
	}
	catch (const std::exception& ex)
	{
		
		return nullptr;
	}
	
}

BitmapSource ^ dv::EngineWrapper::ToBitmapSource(cv::Mat image)
{
	if (image.channels() != 3)
	{
		cv::Mat auxImage = image.clone();
		image.create(image.rows, image.cols, CV_8UC3);
		cv::cvtColor(auxImage, image, CV_GRAY2BGR);
	}

	if (image.cols % 4 != 0)
	{
		cv::resize(image.clone(), image, cvSize(image.cols - image.cols % 4, image.rows));
	}

	if (image.rows % 4 != 0)
	{
		cv::resize(image.clone(), image, cvSize(image.cols, image.rows - image.rows % 4));
	}

	bool isContinuous = image.isContinuous();
	int cols = image.cols;
	int rows = image.rows;
	int stride = image.cols*image.channels();
	int stride00 = image.step.buf[0];
	uchar* data = image.data;

	IntPtr pointer = IntPtr(const_cast<uchar*>(data));

	Bitmap ^bitmap = gcnew Bitmap(
		cols,
		rows,
		stride,
		PixelFormat::Format24bppRgb,
		pointer);

	IntPtr ip = bitmap->GetHbitmap();

	BitmapSource ^bitmapSource = System::Windows::Interop::Imaging::CreateBitmapSourceFromHBitmap(
		ip,
		IntPtr::Zero,
		Int32Rect::Empty,
		BitmapSizeOptions::FromEmptyOptions());

	DeleteObject(ip);
	return bitmapSource;
}
