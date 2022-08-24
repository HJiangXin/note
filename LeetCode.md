# 1.二叉树

## 1.1Morris遍历

```c++
class Solution {
public:
    int n = 0;
    int countNodes(TreeNode* root) {
        morrisMiddle(root);
        return n;
    }
    void morrisMiddle(TreeNode* root)
    {
        TreeNode* cur = root;
        TreeNode* mostRight;
        while(cur != nullptr)
        {
            mostRight = cur->left;
            if(mostRight != nullptr)
            {
                while(mostRight->right != nullptr && mostRight->right != cur)
                {
                    mostRight = mostRight->right;
                }
                    if(mostRight->right == nullptr)
                    {
                        mostRight->right = cur;
                        cur = cur->left;
                        continue;
                    }
                    else
                    {
                        mostRight->right = nullptr;
                    }
                
            }
            n++;
            cur = cur->right;
        }
        
    }
};
```

# 2.String类技巧

## 2.1 string中的split函数

```c++
vector<string_view> split(string &str, char ch) {
        int pos = 0;
        int start = 0;
        string_view s(str);
        vector<string_view> ret;
        while (pos < s.size()) {
            while (pos < s.size() && s[pos] == ch) {
                pos++;
            }
            start = pos;
            while (pos < s.size() && s[pos] != ch) {
                pos++;
            }
            if (start < s.size()) {
                ret.emplace_back(s.substr(start, pos - start));
            }
        }
```

## 2.2string找子串

```c++
//1408. 数组中的字符串匹配
class Solution {
public:
    vector<string> stringMatching(vector<string>& words) {
        vector<string> rarr;
        for(int i = 0; i < words.size(); i++)
        {
            for(int j = 0;j < words.size(); j++)
            {
                if(i != j  )
                {
                    if(words[j].find(words[i])!=string::npos)//npos可以表示string的结束位子，是string::type_size 类型的，也就是find（）返回的类型。find函数在找不到指定值得情况下会返回string::npos。
                    {
                        rarr.emplace_back(words[i]);    
                        break;
                    }
                    
                }
            }
        }
        return rarr;
    }
};
```



# 3.C++继承问题

## 3.1三目运算符

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

