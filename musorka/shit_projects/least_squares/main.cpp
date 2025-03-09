#include <cmath>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <stdexcept>

#include <Graph_lib/Graph.h>
#include <Graph_lib/Simple_window.h>

#include "least_squares.h"

using namespace Graph_lib;

int main ()
try
{
  constexpr int xmax = 600;  // window size
  constexpr int ymax = 450;

  // ... (constants)

  Point lt{100, 100};  // left top window corner
  Simple_window win{lt, xmax, ymax, "Least Squares"};
  win.color(Color::white);
  win.wait_for_button();

  // ... (draw axes)

  // ... (draw plot)
}
catch (std::exception& e)
{
  std::cerr << "error: " << e.what() << std::endl;
  return 1;
}
