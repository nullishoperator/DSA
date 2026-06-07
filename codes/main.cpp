#include "farhad.h"
#include <type_traits>
using namespace std;
//******************************************************** */

//****************************************************** */
void multipleByTwo(ArrayInterface<int> *d){
    for(int i=0;i<d->getLength();i++)
        (*d)[i]*=2;
}
template <class T>
void sumOfAll (Data<T>* d) {
    T *val=new T;
    *val=d->sum();
    if constexpr (std::is_arithmetic<T>::value) {
        *val=d->sum();
        cout<<(*val);
        return;
    }else{
       sumOfAll(val);
    }
    delete val;
    return;
}
int main()
{

Set<int> s{1,2,3,4,5,6,7};


sumOfAll(&s);//28

return 0;
}
