#include "StandardWindowsOutput.hpp"

#ifdef _WIN32
#include <windows.h>

#include <iostream>
#include <streambuf>

int StandardWindowsOutput::count = 0;

StandardWindowsOutput::StandardWindowsOutput() {
	if (count == 0) {
		setp(0, 0);

		// set std::cout to use the custom streambuf
		backupOut = std::cout.rdbuf(this);
		backupErr = std::cerr.rdbuf(this);
		backupLog = std::clog.rdbuf(this);
	}

	++count;
}


StandardWindowsOutput::~StandardWindowsOutput() {
	if (count == 0) {
		// make sure to restore the original so we don't get a crash on close!
		std::cout.rdbuf(backupOut);
		std::cerr.rdbuf(backupErr);
		std::clog.rdbuf(backupLog);
	}

	--count;
}

std::streambuf::int_type StandardWindowsOutput::overflow(int_type c = traits_type::eof()) {
	currentLine.push_back(c);
	int value = fputc(c, stdout);

	if (value == traits_type::eof() || value == '\n') {
		OutputDebugStringA(currentLine.c_str());
		currentLine.clear();
	}
	return c;
}
#else
StandardWindowsOutput::StandardWindowsOutput() {}

StandardWindowsOutput::~StandardWindowsOutput() {}

std::streambuf::int_type StandardWindowsOutput::overflow(int_type c = traits_type::eof()) {
	return c;
}
#endif