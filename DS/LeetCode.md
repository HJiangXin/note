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

## 2.2 string找子串

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

## 2.3 istringstream

```c++
class Solution {
public:
    string solveEquation(string equation) {
        istringstream ss(equation);
        int x_index = -1,n_index = 1, xNum = 0, Num = 0, tmpNume = 0;
        for(char ch; ss >> ch;)
        {
            if(ch == '+')
            {
                n_index = 1;
                
            }
            else if(ch == '-')
            {
                n_index = -1;
            }
            else if(ch == '=')
            {
                
                n_index = 1;
                x_index = 1;
            }
            else if(ch == 'x')
            {
                xNum -= x_index*n_index;
            }
            else
            {
                ss.unget();//往回退一步
                ss >> tmpNume;
                if(ss.peek() == 'x')//查看ss流的下一个
                {
                    ss.get();//获取下一个字符
                    xNum -= x_index*n_index*tmpNume;
                }
                else
                {
                    Num += x_index*n_index*tmpNume;
                }
            }
        }
        
        return xNum ? "x=" + to_string(Num/xNum) : Num ? "No solution":"Infinite solutions";
    }
};
```





