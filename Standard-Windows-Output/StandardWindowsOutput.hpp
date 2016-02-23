#pragma once

#include <iostream>
#include <streambuf>
#include <string>

/// <summary>
/// <para>
/// Visual Studio, for some reason, doesn't use std::cout for Win32 projects.
/// This class works around that limitation; just create an instance of it in main
/// and use std::cout, std::cerr, and std::clog as normal. That's it.  You don't
/// need to initialize anything or pass in any constructors.  As long as an
/// instance of this class exists, all std::cout/cerr/clog output will be directed
/// to the Visual Studio debug console (but ONLY when running with the debugger).
/// </para>
/// <para>
/// It's probably safe to create more than one instance of this class; but just
/// in case, don't do it.
/// </para>
/// <para>
/// When not compiling on Windows, this class does nothing.
/// </para>
/// <remarks>
/// Based on code from http://stackoverflow.com/a/23418611
/// </remarks>
/// </summary>
class StandardWindowsOutput : public std::streambuf {
public:
  StandardWindowsOutput();
  StandardWindowsOutput(const StandardWindowsOutput&) = delete;
  StandardWindowsOutput& operator=(const StandardWindowsOutput&) = delete;

  ~StandardWindowsOutput() override;

  int_type overflow(int_type c) override;

private:
#ifdef _WIN32
  std::string currentLine;
  std::streambuf *backupOut;
  std::streambuf *backupErr;
  std::streambuf *backupLog;
  static int count;
#endif
};