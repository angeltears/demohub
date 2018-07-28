#ifndef MUDUO_BASE_COPYABLE_H
#define MUDUO_BASE_COPYABLE_H



namespace jmuduo
{

    // A tag class emphasises the objects are copyable. 标记类
    // The empty base class optimization applies.　　空基类
    // Any derived class of copyable should be a value type.　　派生类为值类型　只有值类型才可以拷贝
    class copyable
    {

    };
};

#endif