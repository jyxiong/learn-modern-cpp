#include <iostream>

class HeavyObject
{
public:
    HeavyObject() { std::cout << "constructor!" << std::endl; }

    HeavyObject(const HeavyObject&) { std::cout << "copy constructor!" << std::endl; }
    HeavyObject(HeavyObject&&) { std::cout << "move constructor!" << std::endl; }

    ~HeavyObject() { std::cout << "destructor!" << std::endl; }

    HeavyObject operator=(const HeavyObject&) { std::cout << "copy assignment!" << std::endl; return *this; }
    HeavyObject operator=(HeavyObject&&) { std::cout << "move assignment!" << std::endl; return *this; }
};

HeavyObject func1()
{
    return HeavyObject();
}

HeavyObject func2()
{
    HeavyObject o;
    return o;
}

HeavyObject func3()
{
    return std::move(HeavyObject());
}

HeavyObject func4(const HeavyObject& o)
{
    std::cout << "" << std::endl;
    return o;
}


/*
================!
1 constructor!
================!
2 constructor!
================!
3 constructor!
move constructor!
destructor!
================!

4 copy constructor!
================!
1 destructor!
2 destructor!
3 destructor!
4 destructor!
*/
int main()
{
    std::cout << "================!" << std::endl;
    HeavyObject o1 = func1();

    std::cout << "================!" << std::endl;
    HeavyObject o2 = func2();

    std::cout << "================!" << std::endl;
    HeavyObject o3 = func3();

    std::cout << "================!" << std::endl;
    HeavyObject o4 = func4(o3);

    std::cout << "================!" << std::endl;

    return 0;
}