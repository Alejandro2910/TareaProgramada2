#ifndef NODOL_H
#define NODOL_H
#include <utility>

using namespace std;

template<class A, class B>
class NodoL
{
    public:
        std::pair <A, B> elem;
        NodoL *ptrSig;

        NodoL(){

        }

        NodoL(A dat1, B dat2){
            elem = make_pair(dat1, dat2);
            ptrSig=nullptr;
        }

        virtual ~NodoL(){

        }



    protected:

    private:
};

#endif // NODOL_H
