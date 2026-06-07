#include "farhad.h"
using namespace std;
bool isBalanced(string exp)
{

    Array<char> stack(exp.length());

    for (int i = 0; i < exp.length(); i++)
    {
        if (exp[i] == '(')
            stack.insert(exp[i]);
        else if (exp[i] == ')')
            if (stack.getLength() == 0)
                return false;
            else
                stack.remove();
    }
    return stack.getLength() ? false : true;
}
int main(){
    string test{};
    test="(a+b)*c";
    cout<<isBalanced(test)<<endl;//1
    test="(a+b))*c";
    cout<<isBalanced(test)<<endl;//0
    test="a+b*(c+d))*(e+f)";
    cout<<isBalanced(test)<<endl;//0
}