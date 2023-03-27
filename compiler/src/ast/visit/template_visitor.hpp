#pragma once

#include "node.hpp"
#include "visitor.hpp"

namespace ast::visit
{

template<typename T>
class TemplateVisitor : public IVisitor {
 public:
    T Accept(INode* node);
    void SetValue(T value);
 protected:
    T tos_value_;
};

template<typename T>
T TemplateVisitor<T>::Accept(INode* node) {
    node->Visit(*this);
    return tos_value_;
}

template<typename T>
void TemplateVisitor<T>::SetValue(T value) {
    tos_value_ = value;
}

}