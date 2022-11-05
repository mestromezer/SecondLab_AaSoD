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
    Coefficients<T> *GetHead() const
    {
        return Head;
    }

    long long GetOrderOfPolynominal() const
    {
        return OrderOfPolynominal;
    }

    Polynominal(long long Order)
    {
        if (Order >= 0)
        {
            OrderOfPolynominal = Order;
            Head = nullptr;
        }
        else
        {
            delete this;
            throw RangeError("Incorrect \"Order\" for polynomianl");
        }
    }

    ~Polynominal()
    {
        while (Head != NULL)
        {
            Coefficients<T> *tmp = Head;
            Head = Head->Next;
            delete tmp;
        }
    }

    void Set(long long Order, T Coef)
    {
        if (Coef == T(0))
        {
            std::cout << "\n!!!Only non-zero coefs will be saved!!!" << std::endl;
            if (Order == GetOrderOfPolynominal())
            {
                OrderOfPolynominal -= 1;
                std::cout << "Order -= 1" << std::endl;
            }
            return;
        }
        if (Order < 0 || Order > GetOrderOfPolynominal())
        {
            throw RangeError("Incorrect \"Order\", value can't be initialized\n");
        }
        if (Head == nullptr)
        {
            Coefficients<T> *newbie = new Coefficients<T>;
            newbie->MyOrder = Order;
            newbie->Value = Coef;
            newbie->Next = nullptr;
            Head = newbie;
            return;
        }

        Coefficients<T> *PointerA = GetHead();
        Coefficients<T> *PointerB = PointerA;
        for (long long i = 0; i < GetOrderOfPolynominal() + 1 && PointerA; i++)
        {
            if (PointerA->Next == nullptr && Order < PointerA->MyOrder) //последний эдемент
            {
                Coefficients<T> *newbie = new Coefficients<T>;
                newbie->MyOrder = Order;
                newbie->Value = Coef;
                newbie->Next = nullptr;

                PointerA->Next = newbie;
                return;
            }
            else if (PointerA->MyOrder == Order) // просто изменить значение
            {
                PointerA->Value = Coef;
                return;
            }
            else if (PointerA->MyOrder < Order) // добавить между
            {
                Coefficients<T> *newbie = new Coefficients<T>;
                newbie->MyOrder = Order;
                newbie->Value = Coef;

                newbie->Next = PointerA;
                PointerB->Next = newbie;
                return;
            }
            PointerB = PointerA;
            PointerA = PointerA->Next;
        }
    }

    T operator[](long long Order) const
    {
        Coefficients<T> *Pointer = GetHead();

        while (Pointer)
        {
            if (Pointer->MyOrder == Order)
                return Pointer->Value;
            Pointer = Pointer->Next;
        }
        return 0;
    }

    Polynominal operator+(const Polynominal &Other) const
    {
        long long Maximum = 0;

        this->GetOrderOfPolynominal() < Other.GetOrderOfPolynominal() ? Maximum = Other.GetOrderOfPolynominal() : Maximum = this->GetOrderOfPolynominal();

        Polynominal Result(Maximum);

        long long CurrentOrder = Maximum;

        while (CurrentOrder > -1)
        {
            Result.Set(CurrentOrder, ((*this)[CurrentOrder]) + (Other[CurrentOrder]));
            CurrentOrder--;
        }

        return Result;
    }

    Polynominal operator-(const Polynominal &Other) const
    {
        long long Maximum = 0;

        this->GetOrderOfPolynominal() < Other.GetOrderOfPolynominal() ? Maximum = Other.GetOrderOfPolynominal() : Maximum = this->GetOrderOfPolynominal();

        Polynominal Result(Maximum);

        long long CurrentOrder = Maximum;

        while (CurrentOrder > -1)
        {
            Result.Set(CurrentOrder, ((*this)[CurrentOrder]) - (Other[CurrentOrder]));
            CurrentOrder--;
        }

        return Result;
    }

    Polynominal operator*(T Val) const
    {
        Coefficients<T> *Pointer = GetHead();
        Polynominal Result(Pointer->MyOrder);

        for (long long i = 0; i <= GetOrderOfPolynominal(); i++)
        {
            Result.Set(Pointer->MyOrder, Pointer->Value * Val);
            Pointer = Pointer->Next;
        }
        return Result;
    }

    Polynominal Primitive() const
    {
        Polynominal Result((OrderOfPolynominal + 1));
        Coefficients<T> *Pointer = GetHead();
        for (int i = 0; Pointer != NULL; i++)
        {
            T Coef = Pointer->Value * (T(1) / T(Pointer->MyOrder + 1));
            Result.Set(((Pointer->MyOrder) + 1), Coef);
            Pointer = Pointer->Next;
        }
        return Result;
    }


    T CountValue(T x)
    {
        Coefficients<T> *Pointer = GetHead();
        T Ans = 0;
        for (int i = 0; i < GetOrderOfPolynominal() + 1 && Pointer; i++)
        {
            Ans += Pointer->Value * T(pow(x, Pointer->MyOrder));
            Pointer = Pointer->Next;
        }
        return Ans;
    }

    friend ostream &operator<<(ostream &os, const Polynominal<T> &Obj)
    {
        if (Obj.GetOrderOfPolynominal() == -1)
        {
            std::cout << "Polynominal has no coefs" << endl;
        }
        Coefficients<T> *Pointer = Obj.GetHead();
        for (int i = 0; i < Obj.GetOrderOfPolynominal() + 1 && Pointer; i++)
        {
            os << Pointer->Value << "*x^" << Pointer->MyOrder;
            if (Pointer->Next)
                os << " + ";
            Pointer = Pointer->Next;
        }
        return os;
    }   
};
