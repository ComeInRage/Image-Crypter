//#include <vld.h> // Checking Memory Leaks
#include "windows.h"
#include "IMCrypter.h"
#include "IMDecrypter.h"

enum class InputOptions {
	ENCRYPT = 1,
	DECRYPT
};

int get_int() {

	int num = 0;
	std::cin >> num;

	if (std::cin.fail()) {
		std::cin.clear();
		std::cin.ignore(32767, '\n');
		return 0;
	}

	std::cin.ignore(32767, '\n');
	return num;

}

int main(int argc, char** argv)
{

	setlocale(LC_ALL, "Russian");
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	system("color A");

	std::cout << "You started ImageCrypter by SemGV. Here you can encrypt any text into the image and decrypt images into the text." 
			  << "Choose your option:\n1. Encrypt text into image and save.\n2. Decrypt text from image and show.\n";
	int option = get_int();

	switch (option) {
		
		case static_cast<int> (InputOptions::ENCRYPT):
		{

			string text = ""; // strongly recommended to use std::sting or cv::String instead of unsigned char[]
			std::cout << "Enter the text you want to encrypt:\n";
			std::getline(std::cin, text);

			IMCrypter crypter = IMCrypter();
			crypter.crypt_text(text);
			crypter.save_image("SAVED_IMG.jpg");

			std::cout << "Encrypted image saved as SAVED_IMG.jpg in this directory\n";

			break;

		}

		case static_cast<int> (InputOptions::DECRYPT):
		{

			string path = "";
			std::cout << "Enter the path to encrypted image: ";
			std::getline(std::cin, path);

			IMDecrypter decrypter = IMDecrypter();
			if (!decrypter.set_image(path)) {
				std::cout << "Unable to set image by path: " << path << "\n";
				break;
			}
			string *text = decrypter.decrypt_image<string>();

			std::cout << "Decrypted text from image:\n" << *text << "\n";

			break;
		
		}

		default:
		{
			std::cout << "Input error. Closing the program...\n";
			break;
		}

	}

	system("pause");
	return 0;

}
