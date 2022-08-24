## Static关键字

static关键字修饰的变量为类层级全局变量，可以直接用域操作符进行访问(::)



## virtual关键字

在多继承中，每个虚基类有一个虚指针，但是只有一个虚表。



## STL容器

- STL容器主要包括三大类deque、RB-Tree、hashtable

1. deque:双端队列，首位端都可添加或删除元素。基于deque衍生出 stack(栈)尾端入栈或出栈、以及queue(队列)尾端入队列，首端出队列。
2. RB-Tree：红黑树，是关联型容器，衍生出set、multi_set、map、multi_map。
3. hashtable：哈希表又称散列表，其容量大小一般选取质数，扩容时选取原容量*2后附近的质数，衍生出unordered_map、unordered_set。