#pragma once

#include "type_info.hpp"

#include <stdexcept>
#include <string>
#include <variant>

namespace runtime
{

class Object {
 public:
    Object() : info_(TypeInfo("")), data_(std::monostate()) {}
    explicit Object(TypeInfo&& typeInfo) : info_(typeInfo), data_(std::monostate()) {
        if (info_.IsInt()) {
            data_.emplace<0>(0);
            return;
        }
        if (info_.IsBool()) {
            data_.emplace<1>(false);
            return;
        }
    }

    explicit Object(int value) : info_(TypeInfo("int")), data_(value) {}
    explicit Object(bool value) : info_(TypeInfo("bool")), data_(value) {}

    const TypeInfo& GetType() const {
        return info_;
    }

    int Int() const {
        if (data_.index() != 0) {
            throw std::runtime_error("cannot convert to int");
        }
        return get<0>(data_);
    }

    bool Bool() const {
        if (data_.index() != 1) {
            throw std::runtime_error("cannot convert to bool");
        }
        return get<1>(data_);
    }

    std::string Show() const {
        if (info_.IsInt()) {
            return std::to_string(Int());
        }
        if (info_.IsBool()) {
            return Bool()? "true" : "false";
        }
        return "unsupported type";
    }

 private:
    using storage = std::variant<int, bool, std::monostate>;

 private:
    TypeInfo info_;
    storage data_;
};

}