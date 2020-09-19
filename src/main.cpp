#include "Assemble.h"
#include "Compile.h"
#include "Link.h"
#include "Run.h"
#include <fmt/core.h>

int main()
{
  fmt::print("Hello Brainfuck\n");

  std::string_view filename{"../hello"};

  // Stage 1
  // source -> assembly
  compile(filename);

  // Stage 2
  // assembly -> object file
  assemble();

  // Stage 3
  // object file -> executable
  link();

  // Stage 4
  // run and capture the stdout
  run();

  fmt::print("Bye Brainfuck\n");
  return 0;
}
