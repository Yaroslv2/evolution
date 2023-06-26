#ifndef Object__h
#define Object__h

class Object
{
public:
    enum class Type
    {
        NUN,
        BOT,
        POISON,
        EAT,
        WALL,
        EMPTY
    };

    Object(Type aType);
    Type GetType();

private:
    Type mType;
};

#endif