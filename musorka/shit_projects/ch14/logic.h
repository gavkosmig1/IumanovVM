#ifndef LOGIC_H
#define LOGIC_H 1

#include <vector>
#include <string>
#include <iostream>
#include <function>

namespace logic {

class Output;
class Operation;

using Output = std::reference_wrapper<Element>;

enum class State {
    inverted = 0,
    direct
};


class Element
{
public:
    Element(const std::string& name, State out_state = State::direct); //...

    bool output () const;
    const std::string& name () const { return elem_name; }

    State output_state () const {return out_st; }

    Operation& operator>> (Operation& rsh);

protected:
    bool out{false};           // output signal

    virtual void calc () = 0;

private:
    std::string elem_name;
    std::vector<Output> elem_outs;
    State out_st;    // output signal state
};


std::ostream& operator<< (std::ostream& os, const Element& rhs)
{
    os << rhs.name() << ": " << rhs.output();
    return os;
}

enum class Signal
{
    off = 0,
    on
};


class Source : public Element
{
public:
    Source(Signal out = Signal::on, State out_state = State::direct);

    void set_output (Signal sig) { out = (sig == Signal::on); }

protected:
    void calc () override {}
};

class Input
{
public:
    Input (Element& op, State st = State::direct);

    bool output () const;
private:
    State in_st;
    std::reference_wrapper<Elemetn> elem;
};

class Operation : public Element
{
public:
    using Element::Element;

    void attach (Element& elem);

    void calculate();
private:
    std::vector<Input> elem_ins;
};

} // namespace logic

#endif