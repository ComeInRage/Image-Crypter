#pragma once

#include <opencv2/opencv.hpp>
#include <cmath>

using std::string;
using cv::Mat;

class IMAbstractCrypter
{

protected:

	Mat image;

public:

	auto get_image()											-> const Mat&;
	auto save_image(const char path[])							-> void;
	auto save_image(const string &path)							-> void;
	auto show_image()											-> void;

};