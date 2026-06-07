#include "farhad.h"
using namespace std;
bool isOperand(char x) {
    return !(x == '+' || x == '-' || x == '*' || x == '/' || x == '^' || x == '(' || x == ')');
}
double operation(char op, double x,   double y){
    if (op == '+'){
        return x + y;
    } else if (op == '-'){
        return x - y;
    } else if (op == '*'){
        return x * y;
    } else if (op == '/'){
        return x / y;
    }
    return 0;
}
double Evaluate(char* postfix){
    Array<double> stk;
    double x;
    double y;
    double result;
    for (int i=0; postfix[i]!='\0'; i++){
        if (isOperand(postfix[i])){
            // int typecast would not work because of char so subtract '0'
            stk.insert(postfix[i]-'0');
        } else {
            y = stk[LAST];
            stk.remove();
            x = stk[LAST];
            stk.remove();
            result = operation(postfix[i], x, y);
            stk.insert(result);
        }
    }
    result = stk[LAST];
    stk.remove();
    return result;
}
int main(){
    char postfix[] = "231*+9-";
    cout << Evaluate(postfix) << endl; // -4
    char postfix2[] = "38+98/-";
    cout << Evaluate(postfix2) << endl; // 9.875
    return 0;
}