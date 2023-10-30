#include <iostream>
#include <sstream>
#include <stdexcept>

#include <Graph_lib/Graph.h>
#include <Graph_lib/Simple_window.h>
#include <Graph_lib/GraphShape.h>

using namespace Graph_lib;

int main()
{

    Simple_window win({100, 100}, 800, 800, "LOLZ");

    win.wait_for_button();
    Graph_lib::Arc2 arc{Point{300, 300}, 200, 200, 45.0, 135.0};
    win.attach(arc);

    Graph_lib::Arc2 arc1{Point{400, 400}, 300, 300, 225, 315};
    win.attach(arc1);

    Graph_lib::Mark{Point{200, 200}, 'm'};

    win.wait_for_button();
    return 0;
}
