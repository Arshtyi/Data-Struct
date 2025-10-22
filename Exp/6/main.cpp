#include <bits/stdc++.h>
using namespace std;
template <class T>
class arrayStack
{
private:
    int stackTop, arrayLength;
    T *stack;

public:
    arrayStack(int initialCapacity = 10)
    {
        if (initialCapacity < 1)
            throw invalid_argument("Initial capacity must be > 0");
        arrayLength = initialCapacity;
        stack = new T[arrayLength];
        stackTop = -1;
    }
    ~arrayStack() { delete[] stack; }
    bool empty() const { return stackTop == -1; }
    int size() const { return stackTop + 1; }
    T &top()
    {
        if (stackTop == -1)
            throw out_of_range("Stack is empty");
        return stack[stackTop];
    }
    void pop()
    {
        if (stackTop == -1)
            exit(0);
        stack[stackTop--].~T();
    }
    void push(const T &theElement)
    {
        if (stackTop == arrayLength - 1)
        {
            arrayLength *= 2;
            T *newStack = new T[arrayLength];
            for (int i = 0; i <= stackTop; i++)
                newStack[i] = stack[i];
            delete[] stack;
            stack = newStack;
        }
        stack[++stackTop] = theElement;
    }
};
bool Priority(char a) { return a == '*' || a == '/'; }
void Suffix_Exp(const char *exp, arrayStack<char> &exp_stack)
{
    arrayStack<char> symbol_stack;
    while (*exp != '\0')
    {
        if (*exp >= '0' && *exp <= '9')
            exp_stack.push(*exp);
        else if (*exp == '(')
            symbol_stack.push(*exp);
        else if (*exp == ')')
        {
            while (symbol_stack.top() != '(')
            {
                exp_stack.push(symbol_stack.top());
                symbol_stack.pop();
            }
            symbol_stack.pop();
        }
        else
        {
            if (symbol_stack.size() == 0)
                symbol_stack.push(*exp);
            else if (Priority(*exp) > Priority(symbol_stack.top()))
                symbol_stack.push(*exp);
            else
            {
                while (Priority(symbol_stack.top()) >= Priority(*exp) && symbol_stack.top() != '(')
                {
                    exp_stack.push(symbol_stack.top());
                    symbol_stack.pop();
                    if (symbol_stack.size() == 0)
                        break;
                }
                symbol_stack.push(*exp);
            }
        }
        exp++;
    }
    if (symbol_stack.size() != 0)
    {
        int size = symbol_stack.size();
        for (int i = 0; i < size; i++)
        {
            exp_stack.push(symbol_stack.top());
            symbol_stack.pop();
        }
    }
}
double Calculate_Exp(arrayStack<char> &exp_stack)
{
    arrayStack<char> new_exp;
    while (!exp_stack.empty())
    {
        new_exp.push(exp_stack.top());
        exp_stack.pop();
    }
    arrayStack<double> num_stack;
    int size = new_exp.size();
    for (int i = 1; i <= size; ++i)
    {
        if (new_exp.top() >= '0' && new_exp.top() <= '9')
            num_stack.push(new_exp.top() - '0');
        else
        {
            double b = num_stack.top();
            num_stack.pop();
            double a = num_stack.top();
            num_stack.pop();
            switch (new_exp.top())
            {
            case '+':
                num_stack.push(a + b);
                break;
            case '-':
                num_stack.push(a - b);
                break;
            case '*':
                num_stack.push(a * b);
                break;
            case '/':
                num_stack.push(a / b);
                break;
            }
        }
        new_exp.pop();
    }
    return num_stack.top();
}
const int N = 102, M = 2005;
int n;
char ex[M];
signed main()
{
    cin >> n;
    for (int i = 1; i <= n; ++i)
    {
        arrayStack<char> exp_stack;
        cin >> ex;
        Suffix_Exp(ex, exp_stack);
        cout << fixed << setprecision(2) << Calculate_Exp(exp_stack) << endl;
    }
    return 0;
}
