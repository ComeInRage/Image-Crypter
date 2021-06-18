#pragma once

#include "IMAbstractCrypter.h"

class IMCrypter : public IMAbstractCrypter
{

private:

	auto init_image(int text_size)								-> void; // sets optimal image size using text size

public:

	auto crypt_text(const unsigned char text[], int text_size)	-> void;
	auto crypt_text(const string &text)							-> void;

};