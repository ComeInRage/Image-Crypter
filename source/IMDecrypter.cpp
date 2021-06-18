#include "IMDecrypter.h"

// PRIVATE

auto IMDecrypter::copy_uchar(UC_CHAR* const source, int source_size, U_CHAR* const dest, int dest_size) -> void {

	int MAX_SIZE = 0;

	if (dest_size <= source_size) {
		MAX_SIZE = dest_size;
	}
	else {
		MAX_SIZE = source_size;
	}

	for (int i = 0; i < MAX_SIZE; i++) {

		dest[i] = source[i];

	}

}

// PUBLIC

template <>
auto IMDecrypter::decrypt_image() -> U_CHAR* {
	
	int char_num = 0;
	int length = this->image.cols * this->image.rows * this->image.channels(); // length of image.data

	U_CHAR* result;
	U_CHAR* buff = new U_CHAR[length / 8]; // 8 is amount of bites in char type

	for (int bit_in_data = 0; bit_in_data < length; bit_in_data += 8, char_num++) {

		U_CHAR symbol = 0;

		for (int bit_in_char = 0; bit_in_char < 8; bit_in_char++) {

			int current_bit = ((this->image.data[bit_in_data + bit_in_char] > 127) ? 0 : 0b10000000);
			symbol ^= (current_bit >> bit_in_char);

		}

		buff[char_num] = symbol;

		if (symbol == 0) {
			char_num++;
			break;
		}

	}

	result = new U_CHAR[char_num];
	this->copy_uchar(buff, length / 8, result, char_num);

	delete[] buff;

	return result;

}

template <>
auto IMDecrypter::decrypt_image() -> string* {

	int char_num = 0;
	int length = this->image.cols * this->image.rows * this->image.channels(); // length of image.data[] (amount of pixels if image has only one channel)

	string* result = new string();

	for (int bit_in_data = 0; bit_in_data < length; bit_in_data += 8, char_num++) {

		U_CHAR symbol = 0;

		for (int bit_in_char = 0; bit_in_char < 8; bit_in_char++) {

			int current_bit = ((this->image.data[bit_in_data + bit_in_char] > 127) ? 0 : 0b10000000);
			symbol ^= (current_bit >> bit_in_char);

		}

		result->push_back(symbol);

		if (!symbol) {
			break;
		}

	}

	return result;

}

auto IMDecrypter::set_image(const char path[]) -> bool {

	if (!this->image.empty()) { 
		return false; 
	}

	this->image = cv::imread(path, cv::IMREAD_GRAYSCALE);

	return true;

}

auto IMDecrypter::set_image(const string &path) -> bool {

	if (!this->image.empty()) {
		return false;
	}

	this->image = cv::imread(path, cv::IMREAD_GRAYSCALE);

	return true;

}

auto IMDecrypter::set_image(const Mat &img) -> bool {

	if (!this->image.empty() || img.channels() > 1) {
		return false;
	}

	this->image = img.clone();

	return true;

}