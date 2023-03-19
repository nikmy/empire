#pragma once

namespace runtime
{

enum TypeKind {
    KindInt,
    KindBool
};

class TypeInfo {
 public:
    explicit TypeInfo(const std::string& typeName) {
        if (typeName == "int") {
            kind_ = KindInt;
            return;
        }

        if (typeName == "bool") {
            kind_ = KindBool;
        }
    }

    bool IsInt() const {
        return kind_ == KindInt;
    }

    bool IsBool() const {
        return kind_ == KindBool;
    }

    bool IsBasicType() {
        return kind_ == KindInt || kind_ == KindBool;
    }

    bool operator==(const TypeInfo& other) const {
        return kind_ == other.kind_;
    }

    bool operator!=(const TypeInfo& other) const {
        return kind_ != other.kind_;
    }

 private:
    TypeKind kind_;
};

}