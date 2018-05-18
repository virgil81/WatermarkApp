// EngineWrapper.h

#pragma once


#include <vector>
#include <opencv2\core.hpp>
#include <opencv2\imgcodecs.hpp>
#include <opencv2\imgproc.hpp>
#include "../Engine/EngineProcessor.h"


using namespace System;
using namespace System::Windows::Media::Imaging;
using namespace System::Drawing;
using namespace System::Drawing::Imaging;
using namespace System::Windows;


[System::Runtime::InteropServices::DllImportAttribute("gdi32.dll")]
extern bool DeleteObject(IntPtr handle);



namespace dv {

	public ref class EngineWrapper
	{
	public:
		EngineWrapper();
		~EngineWrapper();
		!EngineWrapper();
		BitmapSource^ Process(System::String^ imagePath, System::String^ imagePathW);
	private:
		static BitmapSource^ ToBitmapSource(cv::Mat image);

		std::string MarshalString(System::String^ s) {
			using namespace System::Runtime::InteropServices;
			const char* chars =
				(const char*)(Marshal::StringToHGlobalAnsi(s)).ToPointer();
			std::string os = chars;
			Marshal::FreeHGlobal(System::IntPtr((void*)chars));
			return os;
		};

	private:
		dv::EngineProcessor* _engineprocessor;

	};
}

