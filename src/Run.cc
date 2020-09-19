//
// Created by juan.castellanos on 18/09/20.
//

#include "Run.h"
#include "Exec.h"
#include <iostream>
#include <string>

void run()
{
  std::string s{"./hello"};
  auto result = execute(s);
  std::cout << "The result of the execution of hello.bf is: " << result << '\n';
}
