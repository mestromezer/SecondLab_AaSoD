#pragma once
#include <iostream>
#include <math.h>
#include <complex>
#include "PolynominalError.hpp"
using namespace std;

template<typename T>
struct Coefficients
{
    long long MyOrder;
    T Value;
    Coefficients *Next;
};

template<typename T>
class Polynominal
{
    Coefficients<T> *Head;

    long long OrderOfPolynominal;

public:

    Coefficients<T> *GetHead() const;

    long long GetOrderOfPolynominal() const;

    Polynominal(long long Order);

    ~Polynominal();

    void Set(long long Order, T Coef);

    T operator[](long long Order) const;

    Polynominal operator+(const Polynominal &Other) const;

    Polynominal operator-(const Polynominal &Other) const;

    Polynominal operator*(T Val) const;

    Polynominal Primitive() const;


    T CountValue(T x);

    //friend ostream &operator<<(ostream &os, const Polynominal<T> &Obj);
};
