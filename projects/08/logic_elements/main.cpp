#include <iostream>
#include "logic_elements.h"

using namespace std;


int main()
try
{
    using namespace Logic;

    Element src1    { Type::Source };
    Element and1    { Type::OperationAnd };
    Element or1     { Type::OperationOr };

    src1 >> ~and1 >> or1;
    

    if (and1)
        cout << "and1: true" << endl;
    else
        cout << "and1: false" << endl;


    return 0;
}
catch (std::exception& e)
{
    std::cerr << e.what() << std::endl;
    return 1;
}
catch (...)
{
    std::cerr << "Something went wrong..." << std::endl;
    return 2;
}