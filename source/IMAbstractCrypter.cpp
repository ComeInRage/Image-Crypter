#include "IMAbstractCrypter.h"

auto IMAbstractCrypter::get_image() -> const Mat& {
	return image;
}

auto IMAbstractCrypter::save_image(const char path[]) -> void {

	cv::imwrite(path, this->image);

}

auto IMAbstractCrypter::save_image(const string& path) -> void {

	cv::imwrite(path, this->image);

}

auto IMAbstractCrypter::show_image() -> void {

	const string win_name = "Debug";

	cv::namedWindow(win_name);
	cv::imshow(win_name, this->image);
	cv::waitKey(0);
	cv::destroyWindow(win_name);

}