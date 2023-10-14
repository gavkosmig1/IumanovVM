#ifndef LOGIC_ELEMENTS_H
#define LOGIC_ELEMENTS_H

#include <vector>

namespace Logic
{

// Type - type of logic element
// Type defines element behavior
enum class Type
{
    Source,
    OperationAnd,
    OperationOr,
    OperationNot,
    OperationNotOr,
    // TODO: add new types here
    // ...
};

class Element;

struct Input
{
    Input(Element* ptr, bool inv) :
        elem     { ptr },
        inverted { inv }
    {}

    Element*  elem    { nullptr };
    bool      inverted{ false };

    operator bool() const;
};

using InputContainer = std::vector<Input>;
using OutputContainer = std::vector<Element*>;

class Element
{
public:
    Element(Type t)
     : type{t}
    {}

    // simply returns state of element
    operator bool() const { return state; }

    // calculates state depending on inputs
    void calculate();

    // TODO: move to "protected" section
    void set(bool value);

    Input operator ~() { return Input{this, true}; }

private:
    bool state{ false };
    Type type;

    InputContainer inputs;
    OutputContainer outputs;

    friend bool CheckLoop(const Element& myself, const Element& where);
    friend Element& operator >> (Element& left, Element& right);
    friend Element& operator >> (Element& left, Input right);

};

Element& operator >> (Element& left, Element& right);
Element& operator >> (Element& left, Input right);

}   // eof namespace Logic

#endif  // LOGIC_ELEMENTS_H