#include <iostream>

class Complex {
public:
    // default constructor
    // Complex(); // 无参数构造函数 = 默认构造函数
    Complex(double re=0.0, double im=0.0); // 全默认参数构造函数 = 默认构造函数

    // constructor
    Complex(int re, int im); // 普通构造函数

    // copy constructor
    Complex(const Complex& c) = default; // 对于只包含普通数据的类，可以不实现

    // destructor
    ~Complex() = default; // 对于只包含普通数据结构的类，可以不实现

    // copy assignment
    Complex& operator=(const Complex& c) = default; // 对于只包含普通数据结构的类，可以不实现

public:
    void print_self();

private:
    double m_re;
    double m_im;
};

Complex::Complex(double re, double im): m_re(re), m_im(im)
{

}

Complex::Complex(int re, int im)
{
    m_re = static_cast<double>(re);
    m_im = static_cast<double>(im);
}

void Complex::print_self()
{
    std::cout << "complex = " << m_re << " + " << m_im << "i;" << std::endl;
}

class String {

public:
    // default constructor
    // String(); // 无参数构造函数 = 默认构造函数
    String(const char* data=nullptr); //

    // copy constructor
    // 对于有指针的class, 必须要实现拷贝构造函数
    String(const String& str);

    // destructor
    ~String();

    // copt assignment
    // 对于有指针的class, 必须要实现拷贝赋值函数
    String& operator=(const String& str);

public:
    void print_self();

private:
    char* m_data;
};

String::String(const char* data)
{

}

String::String(const String& str)
{

}

String::~String()
{

}

String& String::operator=(const String& str)
{
    return *this;
}

void String::print_self()
{

}

int main()
{
    Complex complex1(1.1, 1.1);
    Complex complex2(2, 2);
    Complex complex3(complex1);
    Complex complex4 = complex2;

    complex1.print_self();
    complex2.print_self();
    complex3.print_self();
    complex4.print_self();

    return 0;
}