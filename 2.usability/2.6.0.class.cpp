class Complex {
public:
    // default constructor
    // Complex(); // 重载默认构造函数
    Complex(double re=0.0, double im=0.0); // 重载默认构造函数

    // constructor
    Complex(int re, int im);

    // copy constructor
    Complex(const Complex& c); // 对于只包含普通数据的类，可以不实现

    // destructor
    ~Complex();

    // copy assignment
    Complex& operator=(const Complex& c);

private:
    double m_re;
    double m_im;
};

Complex::Complex(double re, double im): m_re(re), m_im(im)
{

}

Complex::Complex(int re, int im): m_re(re), m_im(im)
{

}

Complex::Complex(const Complex& c)
{

}

int main()
{
    return 0;
}