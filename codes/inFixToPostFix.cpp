#include "farhad.h"
using namespace std;
bool isOperand(char x) {
    return !(x == '+' || x == '-' || x == '*' || x == '/' || x == '^' || x == '(' || x == ')');
}

int outPrecedence(char x) {
    if (x == '+' || x == '-') return 1;
    if (x == '*' || x == '/') return 3;
    if (x == '^') return 6;
    if (x == '(') return 7;
    if (x == ')') return 0;
    return -1;
}

int inPrecedence(char x) {
    if (x == '+' || x == '-') return 2;
    if (x == '*' || x == '/') return 4;
    if (x == '^') return 5;
    if (x == '(') return 0;
    return -1;
}

char* convert(const char* infix) {
    char* postfix = new char[strlen(infix) + 1];
    Array<char> stk;

    int i = 0;
    int j = 0;

    while (infix[i] != '\0') {
        if (isOperand(infix[i])) {
            postfix[j++] = infix[i++];
        } else {
            if (infix[i] == ')') {
                while (!stk.getLength()==0 && stk[LAST] != '(') {
                    postfix[j++] = stk[LAST];
                    stk.remove();
                }
                stk.remove(); 
                i++;
            } else {
                while (!stk.getLength()==0 && outPrecedence(infix[i]) <= inPrecedence(stk[LAST])) {
                    postfix[j++] = stk[LAST];
                    stk.remove();
                }
                stk.insert(infix[i++]);
            }
        }
    }

    while (!stk.getLength()==0) {
        postfix[j++] = stk[LAST];
        stk.remove();
    }

    postfix[j] = '\0';
    return postfix;
}

int main(){

    char infix[]="(A+B)*(C+D)";
    char* postfix=convert(infix);
    cout<<postfix<<endl;//'A B + C D + *'

    char infix2[]="a+b*(c^d-e)^(f+g*h)-i";
    postfix=convert(infix2);
    cout<<postfix<<endl;//'a b c d ^ e - f g h * + ^ * + i -'


}