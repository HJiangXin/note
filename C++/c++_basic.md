## Static关键字

static关键字修饰的变量为类层级全局变量，可以直接用域操作符进行访问(::)



## virtual关键字

在多继承中，每个虚基类有一个虚指针，但是只有一个虚表。



## STL容器

- STL容器

1. deque:双端队列，双向，分段连续假连续，具备连续的特性(使用迭代器任意跳跃)，首位端都可添加或删除元素。基于deque衍生出 stack(栈)尾端入栈或出栈、以及queue(队列)尾端入队列，首端出队列，可以使用迭代器任意跳跃。
2. RB-Tree：红黑树，双向，是关联型容器，衍生出set、multi_set、map、multi_map。
3. hashtable：哈希表又称散列表，其容量大小一般选取质数，扩容时选取原容量*2后附近的质数，衍生出unordered_map、unordered_set。
4. list：双向，存储空间在物理上不连续，使用指针连接，不可使用迭代器任意跳跃
5. vector：连续空间，可使用迭代器任意跳跃

## C++继承问题

- 三目运算符左右值类型必须相等

```c++
class FSStateBase
{
public:
    FSStateBase(const FSStateBase & other)
    {
        cout << "base copy constructor called" << endl;
    }

    FSStateBase()
    {
        cout << "base constructor called" << endl;
    }
    ~FSStateBase()
    {

    }

private:

};
class FSState :public FSStateBase
{
public:
    FSState(const FSState& other)
    {
        cout << "derive copy constructor called" << endl;
    }
    FSState()
    {
        cout << "derive constructor called" << endl;
    }
    ~FSState()
    {

    }
};

void foo(const FSStateBase& stat)
{
    cout << &stat << endl;
}
int main()
{
   FSState* m_state = new FSState();
    cout << m_state << endl;
    foo(m_state != nullptr ? *m_state : FSStateBase());//错误,基类会进行拷贝构造，
  												  //三目运算符须保持分支类型一致，引用类型的转换不会进行拷贝构造
  	foo(m_state != nullptr ? *m_state : (const FSStateBase&)FSStateBase());//正确
    return 0;
}
```

