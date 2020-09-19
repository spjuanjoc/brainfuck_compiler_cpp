//
// Created by juan.castellanos on 17/09/20.
//

#include <cstdlib>

void link()
{
  std::system("ld -lc tmp.o -o hello -I /lib64/ld-linux-x86-64.so.2");
}