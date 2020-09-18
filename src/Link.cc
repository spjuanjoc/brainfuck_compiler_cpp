//
// Created by juan.castellanos on 17/09/20.
//

#include <fmt/format.h>
#include <cstdlib>

void link()
{
  std::system("ld tmp.o -o hello");
//  std::system("ld -c tmp.o -o hello -I /lib64/ld-linux-x86-64.so.2");
}