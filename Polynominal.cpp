#include "Polynominal.hpp"

template<typename T>
Coefficients<T>* Polynominal<T>::GetHead() const
{
    return Head;
}

template<typename T>
long long Polynominal<T>::GetOrderOfPolynominal() const
{
    return OrderOfPolynominal;
}

template<typename T>
Polynominal<T>::Polynominal(long long Order)
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

template<typename T>
Polynominal<T>::Polynominal(const Polynominal& Other)
{
    this->OrderOfPolynominal = Other.GetOrderOfPolynominal();
    const Coefficients<T>* Data = Other.GetHead();

    while(Data!= nullptr)
    {
        Set(Data->MyOrder, Data->Value);
        Data = Data->Next;
    }
}

template<typename T>
Polynominal<T>::~Polynominal()
{
    while (Head != NULL)
    {
        Coefficients<T> *tmp = Head;
        Head = Head->Next;
        delete tmp;
    }
}

template<typename T>
void Polynominal<T>::Set(long long Order, T Coef)
{
    if (Coef == T(0))
    {
        //cout << "\n!!!Only non-zero coefs will be saved!!!" << endl;
        if (Order == GetOrderOfPolynominal())
        {
            OrderOfPolynominal -= 1;
            cout << "Order -= 1" << endl;
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

template<typename T>
T Polynominal<T>::operator[](long long Order) const
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

template<typename T>
Polynominal<T> Polynominal<T>::operator+(const Polynominal &Other) const
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

template<typename T>
Polynominal<T> Polynominal<T>::operator-(const Polynominal &Other) const
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

template<typename T>
Polynominal<T> Polynominal<T>::operator*(T Val) const
{
    Coefficients<T> *Pointer = GetHead();
    Polynominal Result(Pointer->MyOrder);

    while(Pointer != NULL)
    {
        Result.Set(Pointer->MyOrder, Pointer->Value * Val);
        Pointer = Pointer->Next;
    }
    return Result;
}

template<typename T>
Polynominal<T> Polynominal<T>::Primitive() const
{
    Polynominal Result((OrderOfPolynominal + 1));
    Coefficients<T> *Pointer = GetHead();
    while(Pointer)
    {
        T Coef = Pointer->Value * (T(1) / T(Pointer->MyOrder + 1));
        Result.Set(((Pointer->MyOrder) + 1), Coef);
        Pointer = Pointer->Next;
    }
    return Result;
}

template<typename T>
T Polynominal<T>::CountValue(T x) const
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

template class Polynominal<int>;
template class Polynominal<float>;
template class Polynominal<double>;
template class Polynominal<complex<float>>;
template class Polynominal<complex<double>>;