#ifndef TEST_H
#define TEST_H


class test
{
private:
    int i;
    char c;

public:
    test();
    ~test();
    void func();
};
class child:public test
{
public:
    void func();
};

#endif // TEST_H
