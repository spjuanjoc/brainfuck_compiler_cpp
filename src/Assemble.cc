//
// Created by juan.castellanos on 17/09/20.
//

#include <cstdlib>

void assemble()
{
  std::system("nasm -felf64 tmp.asm -o tmp.o");
}
