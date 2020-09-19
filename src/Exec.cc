//
// Created by juan.castellanos on 18/09/20.
//

#include "Exec.h"
#include <array>
#include <fstream>
#include <iostream>
#include <memory>
#include <string>

// C style
std::string exec(const char* cmd)
{
  std::array<char, 128>                    buffer{};
  std::string                              result;
  std::unique_ptr<FILE, decltype(&pclose)> pipe(popen(cmd, "r"), pclose);

  if (!pipe)
  {
    throw std::runtime_error("popen() failed!");
  }
  while (fgets(buffer.data(), buffer.size(), pipe.get()) != nullptr)
  {
    result.append(buffer.data());
  }
  return result;
}

// c++ style
std::string execute(const std::string& command)
{
  std::system((command + " > temp.txt").c_str());

  std::ifstream ifs("temp.txt");
  std::string   ret{std::istreambuf_iterator<char>(ifs), std::istreambuf_iterator<char>()};
  ifs.close();  // must close the input stream so the file can be cleaned up

  if (std::remove("temp.txt") != 0)
  {
    std::cerr << "Error deleting temporary file\n";
  }

  return ret;
}