#ifndef NODOA_H
#define NODOA_H


template <class T>class NodoA
{
    public:

        T peso;
        NodoA *ady;
        NodoV *vert;

        NodoA();
        virtual ~NodoA();

    protected:

    private:
};

#endif // NODOA_H
