// Test.cpp : Defines the entry point for the console application.
//

#include <iostream>

#include "StandardWindowsOutput.hpp"

using std::cout;
using std::cerr;
using std::clog;
using std::endl;

int main()
{
	StandardWindowsOutput out;

#ifndef _WIN32
	cerr << "NOTE: It doesn't look like you're building a Win32 application." << endl;
#endif

	cout << "cout works!" << endl;
	clog << "clog works!" << endl;
	cerr << "cerr works!" << endl;
}

