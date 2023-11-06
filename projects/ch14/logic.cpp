#include <logic.h>

namespace logic {

Element::Element(const std::string name, State out_state) : out_st{out_state} {} //...


Input::Input(Element& el, State st) //...

bool Element::output() const
{
    bool out = elem.get().output()
    return (in_st == State::direct) ? out : !out;
}

Source::Source(const std::string& name, Signal out, State out_state = State::direct)
    : Element {out_state};

Input(Element& el, State st = State::direct) : elem{el}
{
    //...
}


void Operation::calculate()
{
    for (auto& item : elem_ins)
    item.calculate();
}

} // namespace logic