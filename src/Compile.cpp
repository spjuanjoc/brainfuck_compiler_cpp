//
// Created by juan.castellanos on 17/09/20.
//

#include "Compile.h"
#include <fstream>
#include <iterator>
#include <stack>
#include <fmt/ostream.h>

using std::string;
using std::stringstream;
using std::ifstream;
using std::ofstream;

constexpr auto arg_reg = "dil"; // linux only

void compile(std::string_view source = "../example")
{
  string brainfuckfile{source};
  brainfuckfile.append(".bf");

  ifstream ifs{brainfuckfile};
  ofstream ofs{"tmp.asm"};

  auto prolog = R"(
  global _start
  extern getchar
  extern putchar
  extern exit
  section .text
_start:
  sub rsp, 4000
  mov eax, 0
  mov ecx, 4000
  mov rdi, rsp
  rep stosb
  mov r12, rsp
  sub rsp, 64
)";
  ofs << prolog;

  if (ifs)
  {
    std::stack<uint32_t> labels;
    auto current_label = 0;

    // Read the brainfuck
    // ...+++---,.,.,[++--,.]

    // Start memory
    // 00000000000000000000000
    //            ^            Start reg = r12

    char c;
    while (ifs >> c)
    {

      switch (c)
      {
        case '>': ofs << "  add r12, 1\n"; break; // move the pointer 1 reg to the right
        case '<': ofs << "  sub r12, 1\n"; break; // move the pointer 1 reg to the left
        case '+': ofs << "  add byte [r12], 1\n"; break; // increase the value of the reg pointed by 1
        case '-': ofs << "  sub byte [r12], 1\n"; break; // decrease the value of the reg pointed by 1
        case ',': ofs
            << "  call getchar\n" // read byte from function getchar
            << "  mov byte [r12], al\n"; // al = r12 content
          break;
        case '.': fmt::print(ofs,
          "  mov {0}, [r12]\n" // cl = r12 content
          "  call putchar\n", arg_reg); // write to byte with function putchar
          break;

        // ..++-[--,,,,]..
        //      ^           begin of the loop: use assembly labels
        // The loops may be nested
        case '[':
          fmt::print(ofs,
                     "label{0}start:\n"        // assign a label: label0start:
                     "  cmp byte [r12], 0\n"  // if [ = 0 skip the whole loop
                     "  jz label{0}end\n",
                     current_label);  // label0end
          labels.push(current_label);
          current_label++;
          break;

        case ']':
          fmt::print(ofs,
                     "  jmp label{0}start\n"  // go to [
                     "label{0}end:\n",
                     labels.top());
          labels.pop();
          break;
        default: break;
      }
    }
  }
  auto epilog = R"(
  add rsp, 4064
  mov eax, 0
  call exit
)";
  ofs << epilog;
}
