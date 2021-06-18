#include "IMCrypter.h"

// PRIVATE

auto IMCrypter::init_image(int text_size) -> void { // sets optimal image size using text size

	const int bitstream_size = text_size * 8;

	int y = static_cast<int> (sqrt(bitstream_size));
	int x = y;

	while (y * x < bitstream_size) {
		x++;
	}

	this->image = Mat(y, x, CV_8UC1);

}

// PUBLIC

auto IMCrypter::crypt_text(const unsigned char text[], int text_size) -> void {

	this->init_image(text_size);

	int bit_num = 0;
	for (int char_num = 0; char_num < text_size; char_num++) {

		for (int shift = 7, separator = 0b10000000; shift >= 0; shift--, separator >>= 1, bit_num++) { // (text[char_num] & separator) >> shift
			int x = bit_num % this->image.cols;
			int y = bit_num / this->image.cols;
			this->image.at<uchar>(y, x) = (((text[char_num] & separator) >> shift) == 1 ? 0 : 255);
		}

	}

}

auto IMCrypter::crypt_text(const string &text) -> void {

	this->init_image(static_cast<int>(text.length()));

	int bit_num = 0;
	for (auto symbol = text.begin(); symbol != text.end(); symbol++) {

		for (int shift = 7, separator = 0b10000000; shift >= 0; shift--, separator >>= 1) { // (text[char_num] & separator) >> shift
			int x = bit_num % this->image.cols;
			int y = bit_num / this->image.cols;
			this->image.at<uchar>(y, x) = (((*symbol & separator) >> shift) == 1 ? 0 : 255);
			bit_num++;
		}

	}

}