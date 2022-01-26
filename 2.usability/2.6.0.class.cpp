#include <iostream>
#include <cstring>

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
    std::cout << "Complex default constructor!" << std::endl;
}

Complex::Complex(int re, int im)
{
    std::cout << "Complex common constructor!" << std::endl;
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
    String(const char* data = nullptr); //

    // copy constructor
    // 对于有指针的class, 必须要实现拷贝构造函数
    String(const String& str);

    // TODO: move constructor

    // destructor
    // 对于有指针的class, 必须要实现析构函数
    ~String();

    // copty assignment
    // 对于有指针的class, 必须要实现拷贝赋值函数
    String& operator=(const String& str);

    // TODO: move assignment

public:
    void print_self();
    char* get_data();

private:
    char* m_data;
};

String::String(const char* data)
{
    std::cout << "String default constructor!" << std::endl;
    if (data)
    {
        m_data = new char[strlen(data) + 1];
        strcpy(m_data, data);
    }
    else
    {
        m_data = new char[1];
        m_data[0] = '\0';
    }
}

String::String(const String& str)
{
    std::cout << "String copy constructor!" << std::endl;
    m_data = new char[strlen(str.m_data) + 1];
    strcpy(m_data, str.m_data);
}

String::~String()
{
    std::cout << "String destructor!" << std::endl;
    delete[] m_data;
}

String& String::operator=(const String& str)
{
    // 判断是否是同一个对象
    // 1.效率
    // 2.防止删除*this后形成野指针，再调用时内存错误
    if (this == &str)
        return *this;

    delete[] m_data;

    m_data = new char[strlen(str.m_data) + 1];
    strcpy(m_data, str.m_data);

    return *this;
}

void String::print_self()
{
    std::cout << m_data << std::endl;
}

char* String::get_data()
{
    return m_data;
}

int main()
{
    // *********************
    Complex complex1(1.1, 1.1);
    Complex complex2(2, 2);
    Complex complex3(complex1);
    Complex complex4 = complex2;

    complex1.print_self();
    complex2.print_self();
    complex3.print_self();
    complex4.print_self();

    // *********************
    String str1("abc");
    String str2(str1);

    str1.print_self();
    std::cout << str2.get_data() << std::endl;

    return 0;
}