//
// Created by juan.castellanos on 17/09/20.
//

#include "Exec.h"
#include <iostream>

void link()
{
  std::string command{"ld -lc tmp.o -o hello -I /lib64/ld-linux-x86-64.so.2"};
  std::string result = execute(command);
  std::cout << result << '\n';
}