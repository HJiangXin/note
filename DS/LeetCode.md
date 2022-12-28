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

## 2.3 trim(去除前导零)

```c++
string trim(string &s)
    {
        int i = 0;
        while(i < s.size() - 1 && s[i] == '0')
        {
            i++;
        }
        return s.substr(i);
    }
```

## 2.3 substring

```c++
s.substring(left+1,right-left-1);//左闭右开区间,第一个参数为剪切的起始点，第二个参数为剪切长度
```



# 3.排序

## 3.1 按照频率将数组升序排序  (sort排序)

- [ ] LeetCode 1636

```c++
class Solution {
public:
    vector<int> frequencySort(vector<int>& nums) {
    unordered_map<int,int> m_map;
    for(int i = 0;i < nums.size();i++)
    {
        m_map[nums[i]]++;
    }
    sort(nums.begin(),nums.end(),[&](int a, int b){
        if(m_map[a] == m_map[b])
        {
            return a>b;
        }
    return m_map[a] < m_map[b];
    });

    return nums;
    }
};
```





