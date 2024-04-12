// RTTIDumper.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <cstdio>
#include <filesystem>
#include <fstream>
#include "kaitai/kaitaistream.h"
#include "parsers/mach_o/mach_o.h"

void check_binary(char* binary_path)
{
	std::ifstream input(binary_path, std::ios::binary);

	kaitai::kstream ks(&input);

	mach_o_t data(&ks);
	printf("ass %i\n", (int)data.magic());
};

int main(int argc, char* argv[])
{
	//Print help information if no arguments are supplied.
	if (argc == 1)
	{
		printf("This program attempts to dump RTTI info from binary files made using either MSVC or GCC and attempt to make header files from them.\n");
		printf("Microsoft PE: mspe Mach object file format: macho - More types will be added soon.\n");
		printf("Usage: RTTIDumper.exe \"path/to/binary\" macho/mspe\n");
	}

	if (argc == 3) {
		printf("Attempting to dump \"%s\" with file type \"%s\"\n", argv[1], argv[2]);

		char* file_type = argv[2];

		if (strcmp(file_type, "macho") != 0 && strcmp(file_type, "mspe") != 0)
		{
			printf("Error: Invalid file type.\n");
			return 0;
		}

		char* binary_path = argv[1];
		if (std::filesystem::exists(binary_path))
			check_binary(binary_path);
	}
	else if (argc > 3)
		printf("Error: Invalid number of arguments. Exiting.\n");

	return 0;
}