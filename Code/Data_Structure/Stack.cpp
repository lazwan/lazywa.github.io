#include <bits/stdc++.h>
using namespace std;

// 优先级
int fl (char str) {
    int tmp;
    switch (str) {
        // case '(': tmp = 0; break;
        case '+': tmp = 1; break;
        case '-': tmp = 1; break;
        case '*': tmp = 2; break;
        case '/': tmp = 2; break;
    }
    return tmp;
}

int main()
{
    stack<char> s;
    string str; // = "2*(9+6/3-5)+4";
    cin >> str;
    for (int i = 0; i < str.length(); i++) {
        if ((str[i] >= '0' && str[i] <= '9') || (str[i] >= 'a' && str[i] <= 'z')) {
            cout << str[i] << ' ';
        } else if (str[i] == '+' || str[i]== '-' || str[i] == '*' || str[i] == '/') {
            while (true) {
                if (s.empty() || s.top() == '(') {
                    s.push(str[i]);
                    break;
                } else if (fl(str[i]) > fl(s.top())) {
                    s.push(str[i]);
                    break;
                } 
                else {
                    // while (fl(str[i]) <= fl(s.top())) {
                    //     cout << s.top() << ' ';
                    //     s.pop();
                    // }
                    cout << s.top() << ' ';
                    s.pop();
                    // s.push(str[i]);
                }
            }

        } else if (str[i] == '(') {
            s.push(str[i]);
        } else if (str[i] == ')') {
            while (s.top() != '(') {
                cout << s.top() << ' ';
                s.pop();
            }
            s.pop();
        }
    }
    while (!s.empty()) {
        cout << s.top() << ' ';
        s.pop();
    }
    cout << endl;
    return 0;
}