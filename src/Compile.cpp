//
// Created by juan.castellanos on 17/09/20.
//

#include "Compile.h"
#include <fstream>
#include <iterator>
#include <stack>

using std::string;
using std::stringstream;
using std::ifstream;
using std::ofstream;

void compile(std::string_view source = "../example")
{
  string brainfuckfile{source};
  string assemblyFile{source};
  brainfuckfile.append(".bf");
  assemblyFile.append(".asm");

  ifstream ifs{brainfuckfile};
  ofstream ofs{assemblyFile};

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
        case '.': ofs
          << "  mov cl, [r12]\n" // cl = r12 content
          << "  call putchar\n"; // write to byte with function putchar
          break;

        // ..++-[--,,,,]..
        //      ^           begin of the loop: use assembly labels
        // The loops may be nested
        case '[': ofs
          << "label" << current_label << "start:\n" // assign a label: label0start:
          << "  cmp byte [r12], 0\n" // if [ = 0 skip the whole loop
          << "  jz label" << current_label << "end\n"; // label0end
          labels.push(current_label);
          current_label++;
          break;

        case ']': ofs
          << "  jump label" << labels.top() << "start\n" // go to [
          << "label" << labels.top() << "end:\n";
          labels.pop();
          break;
        default: break;
      }
    }
  }
}
