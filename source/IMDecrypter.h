#pragma once

#include "IMAbstractCrypter.h"

typedef const unsigned char UC_CHAR;
typedef unsigned char U_CHAR;

class IMDecrypter : public IMAbstractCrypter
{

private:

	auto copy_uchar(UC_CHAR* const source, int source_size, U_CHAR* const dest, int dest_size) -> void;

public:

	template <typename T>
	auto decrypt_image()					-> T*;

	auto set_image(const char path[])		-> bool;
	auto set_image(const Mat &img)			-> bool;
	auto set_image(const string &path)		-> bool;

};

