#include <bits/stdc++.h>
using namespace std;

#define PSS pair<string, string>

int precedence(string op);
bool isNumber(const string& str);
int operate(int a, int b, char op);
void output1(string &s, int &counter, map<string, string> &exp, vector<PSS> &expression);
void output2(map<string, string> &exp, vector<PSS> &expression);

int main()
{
    string s;
    vector<PSS> expression;
    map<string, string> exp;
    int counter = 1;

    cout << "Output I:\n\n";
    while (getline(cin, s))
    {
        output1(s, counter, exp, expression);
    }

    for (auto &x : expression)
    {
        if (x.first == "print")
        {
            cout << x.first << " " << x.second << "\n";
        }
        else
        {
            cout << x.first << " = " << x.second << "\n";
        }
    }

    cout << "\nOutput II:\n\n";
    output2(exp, expression);
}

void output1(string &s, int &counter, map<string, string> &exp, vector<PSS> &expression)
{
    stringstream ss(s);
    string word;
    stack<string> operand, operators;

    while (ss >> word)
    {
        if (word == "print")
        {
            ss >> word;
            expression.push_back({"print", word});
        }
        else if (word == "+" || word == "-" || word == "*" || word == "/" || word == "=")
        {
            if (operators.empty())
            {
                operators.push(word);
            }
            else
            {
                if (precedence(operators.top()) > precedence(word))
                {
                    while (!operators.empty() && precedence(operators.top()) > precedence(word))
                    {
                        string a = operand.top();
                        operand.pop();
                        string b = operand.top() + " " + operators.top() + " " + a;
                        string name = "t" + to_string(counter);
                        counter++;
                        exp[name] = b;
                        expression.push_back({name, b});
                        operand.top() = name;
                        operators.pop();
                    }
                    operators.push(word);
                }
                else
                {
                    operators.push(word);
                }
            }
        }
        else
        {
            operand.push(word);
        }
    }

    while (!operators.empty() && !operand.empty())
    {
        if (operators.top() == "=")
        {
            string var1 = operand.top();
            operand.pop();
            expression.push_back({operand.top(), var1});
            exp[operand.top()] = var1;
            operand.pop();
            operators.pop();
        }
        else
        {
            string a = operand.top();
            operand.pop();
            string b = operand.top() + " " + operators.top() + " " + a;
            string name = "t" + to_string(counter);
            counter++;
            exp[name] = b;
            expression.push_back({name, b});
            operand.top() = name;
            operators.pop();
        }
    }
}

void output2(map<string, string> &exp, vector<PSS> &expression)
{
    set<string> constants;

    for (auto &x : expression)
    {
        if (x.first == "print")
        {
            if (isNumber(exp[x.second]))
            {
                x.second = exp[x.second];
            }
            continue;
        }

        stringstream ss(x.second);
        string word1, word2, word3;
        ss >> word1 >> word2 >> word3;

        if (word2 == "")
        {
            if (isNumber(word1))
            {
                constants.insert(x.first);
            }
            else
            {
                exp[x.first] = exp[x.second];
                if (isNumber(exp[x.first]))
                {
                    constants.insert(x.first);
                }
                exp.erase(x.second);
                x.second = exp[x.first];
            }
        }
        else
        {
            if (isNumber(word1) && isNumber(word3))
            {
                x.second = to_string(operate(stoi(word1), stoi(word3), word2[0]));
                exp[x.first] = x.second;
                constants.insert(x.first);
            }
            else
            {
                if (exp.find(word1) != exp.end() && isNumber(exp[word1]))
                {
                    word1 = exp[word1];
                }
                if (exp.find(word3) != exp.end() && isNumber(exp[word3]))
                {
                    word3 = exp[word3];
                }
                if (isNumber(word1) && isNumber(word3))
                {
                    x.second = to_string(operate(stoi(word1), stoi(word3), word2[0]));
                    exp[x.first] = x.second;
                    constants.insert(x.first);
                }
                else
                {
                    x.second = word1 + " " + word2 + " " + word3;
                    exp[x.first] = x.second;
                }
            }
        }
    }

    for (auto &x : expression)
    {
        if (x.first == "print")
        {
            if (isNumber(x.second))
            {
                cout << x.second << "\n";
            }
            else
            {
                cout << x.first << " " << x.second << "\n";
            }
        }
        if (exp.find(x.first) != exp.end() && constants.find(x.first) == constants.end())
        {
            cout << x.first << " = " << x.second << "\n";
        }
    }
}

int precedence(string op)
{
    if (op == "/")
    {
        return 3;
    }
    else if (op == "*")
    {
        return 2;
    }
    else if (op == "+" || op == "-")
    {
        return 1;
    }
    return 0;
}

bool isNumber(const string& str)
{
    if (str.length() == 0)
    {
        return false;
    }
    for (char c : str)
    {
        if (!isdigit(c))
        {
            return false;
        }
    }
    return true;
}

int operate(int a, int b, char op)
{
    if (op == '+')
    {
        return a + b;
    }
    else if (op == '-')
    {
        return a - b;
    }
    else if (op == '*')
    {
        return a * b;
    }
    else if (op == '/')
    {
        return a / b;
    }
    return 0;
}