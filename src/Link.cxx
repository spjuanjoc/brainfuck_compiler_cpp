//
// Created by juan.castellanos on 17/09/20.
//
#include <fmt/format.h>
#include <cstdlib>

void link()
{
  const auto linker = std::getenv("LINK64");
  const auto ucrt = std::getenv("UCRT64");
  auto cmd = fmt::format(R"(""{})");
}