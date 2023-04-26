#include "../headers/Object.h"

Object::Object(Type aType) : mType(aType) {}

Object::Type Object::GetType() {
    return mType;
}