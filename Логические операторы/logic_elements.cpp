#include "logic_elements.h"
#include <stdexcept>

namespace Logic
{


Input::operator bool() const
{
    return inverted ? !(*elem) : *elem;
}

void Element::calculate()
{
    switch (type)
    {
        case Type::Source:
            break;
        case Type::OperationAnd:
        {
            bool flag{ true };
            for (const auto& input : inputs)
            {
                if (!input)
                {
                    flag = false;
                    break;
                }
            }
            set(flag);
            break;
        }
        case Type::OperationOr:
        {
            bool flag{ false };
            for (const auto& input : inputs)
            {
                if (input)
                {
                    flag = true;
                    break;
                }
            }
            set(flag);
            break;
        }
    }
}

void Element::set(bool value)
{
    if (state != value)
    {
        state = value;
        for(auto output : outputs)
            output->calculate();
    }
}

bool CheckLoop(const Element& myself, const Element& where) {
    if (&where == &myself) {
        return true;
    }
    bool result = false;
    for (const Element* to_check : where.outputs){
        if (CheckLoop(myself, *to_check)) {
            return true;
        }
    }
    return false;
}

Element& operator >> (Element& left, Input right)
{   
    if (CheckLoop(left, *right.elem)) {
        throw std::runtime_error("loop detected");
    }

    bool input_connected{false};
    for(const auto input : right.elem->inputs)
    {
        if (input.elem == &left)
            input_connected = true;
    }
    if (!input_connected)
        right.elem->inputs.push_back(Input{ &left, right.inverted });

    bool output_connected = false;
    for(const auto output : left.outputs)
    {
        if (output == right.elem)
            output_connected = true;
    }
    if (!output_connected)
        left.outputs.push_back(right.elem);

    if (!input_connected || ! output_connected)
        right.elem->calculate();

    return *right.elem;
}

Element& operator >> (Element& left, Element& right)
{
    left >> Input{&right, false};
    return right;
}


    
}