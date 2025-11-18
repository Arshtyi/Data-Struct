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
            throw out_of_range("Stack is empty");
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
void run_expression()
{
    cin >> n;
    for (int i = 1; i <= n; ++i)
    {
        arrayStack<char> exp_stack;
        cin >> ex;
        Suffix_Exp(ex, exp_stack);
        cout << fixed << setprecision(2) << Calculate_Exp(exp_stack) << endl;
    }
}
struct NodePos
{
    int r, c, dir;
};
const int MAXMZ = 256, dr[] = {0, 1, 0, -1}, dc[] = {1, 0, -1, 0};
int r, c, maze[MAXMZ][MAXMZ], pathMark[MAXMZ][MAXMZ], vis[MAXMZ][MAXMZ], pr[MAXMZ * MAXMZ], pc[MAXMZ * MAXMZ], vis2[MAXMZ][MAXMZ];
bool load_maze()
{
    freopen("maze.txt", "r", stdin);
    cin >> r >> c;
    for (int i = 0; i < r; ++i)
        for (int j = 0; j < c; ++j)
            cin >> maze[i][j];
    return r > 0 && c > 0;
}
bool solve_maze()
{
    if (maze[0][0] || maze[r - 1][c - 1])
        return false;
    arrayStack<NodePos> st(r * c + 10);
    NodePos start{0, 0, 0};
    st.push(start);
    vis[0][0] = 1;
    bool found = false;
    while (!st.empty())
    {
        NodePos &cur = st.top();
        if (cur.r == r - 1 && cur.c == c - 1)
        {
            found = true;
            break;
        }
        if (cur.dir >= 4)
        {
            st.pop();
            continue;
        }
        int dir = cur.dir;
        cur.dir++;
        int nr = cur.r + dr[dir], nc = cur.c + dc[dir];
        if (nr >= 0 && nr < r && nc >= 0 && nc < c && !vis[nr][nc] && !maze[nr][nc])
        {
            vis[nr][nc] = 1;
            NodePos nxt{nr, nc, 0};
            st.push(nxt);
        }
    }
    if (!found)
        return false;
    arrayStack<NodePos> tmp;
    while (!st.empty())
    {
        tmp.push(st.top());
        st.pop();
    }
    while (!tmp.empty())
    {
        NodePos p = tmp.top();
        tmp.pop();
        pathMark[p.r][p.c] = 1;
        st.push(p);
    }
    return true;
}
void print_path()
{
    int maxLen = r * c, len = 0, x = 0, y = 0;
    pr[len] = x, pc[len] = y;
    len++;
    vis2[x][y] = 1;
    while (!(x == r - 1 && y == c - 1) && len < maxLen)
    {
        bool adv = false;
        for (int k = 0; k < 4; ++k)
        {
            int nr = x + dr[k];
            int nc = y + dc[k];
            if (nr >= 0 && nr < r && nc >= 0 && nc < c && pathMark[nr][nc] && !vis2[nr][nc])
            {
                x = nr, y = nc;
                vis2[x][y] = 1;
                pr[len] = x, pc[len] = y;
                len++;
                adv = true;
                break;
            }
        }
    }
    printf("Path length: %d\n", len);
    printf("Path: ");
    for (int i = 0; i < len; ++i)
    {
        printf("(%d,%d)%s", pr[i] + 1, pc[i] + 1, (i + 1 < len ? "->" : "\n"));
    }
    printf("\nMap with path (*):\n");
    for (int i = 0; i < r; ++i)
    {
        for (int j = 0; j < c; ++j)
        {
            char ch;
            if (maze[i][j] == 1)
                ch = '#';
            else if (pathMark[i][j])
                ch = '*';
            else
                ch = '.';
            putchar(ch);
            if (j + 1 < c)
                putchar(' ');
        }
        putchar('\n');
    }
}
void run_maze()
{
    if (!load_maze())
    {
        return;
    }
    if (!solve_maze())
    {
        printf("No path from (1,1) to (%d,%d).\n", r, c);
        printf("\nMap:\n");
        for (int i = 0; i < r; ++i)
        {
            for (int j = 0; j < c; ++j)
            {
                putchar(maze[i][j] ? '#' : '.');
                if (j + 1 < c)
                    putchar(' ');
            }
            putchar('\n');
        }
        return;
    }
    else
        print_path();
}
signed main()
{
    // run_maze();
    run_expression();
    return 0;
}
