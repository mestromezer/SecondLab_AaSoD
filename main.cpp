#include <iostream>
#include <termios.h>
#include <unistd.h>
#include <complex>
#include "Polynominal.hpp"
using namespace std;

char getch(void)
{
    char buf = 0;
    struct termios old = {0};
    fflush(stdout);
    if (tcgetattr(0, &old) < 0)
        perror("tcsetattr()");
    old.c_lflag &= ~ICANON;
    old.c_lflag &= ~ECHO;
    old.c_cc[VMIN] = 1;
    old.c_cc[VTIME] = 0;
    if (tcsetattr(0, TCSANOW, &old) < 0)
        perror("tcsetattr ICANON");
    if (read(0, &buf, 1) < 0)
        perror("read()");
    old.c_lflag |= ICANON;
    old.c_lflag |= ECHO;
    if (tcsetattr(0, TCSADRAIN, &old) < 0)
        perror("tcsetattr ~ICANON");
    return buf;
}

template<typename T>
Polynominal<T> *MenuInput()
{
    std::cout << "Create poilynominal menu\n\n"
         << endl;

    std::cout << "Order of Polynominal: " << endl;
    long long OrderOfPolynominal = 0;
    cin >> OrderOfPolynominal;

    Polynominal<T> *Newbie = NULL;
    try
    {
        Newbie = new Polynominal<T>(OrderOfPolynominal);
    }
    catch (exception e)
    {
        clog << "An exception occured" << endl;
    }

    for (long long i = OrderOfPolynominal; i >= 0; i--)
    {
        std::cout << "Coef by " << i << ":\n";
        double Coefficient = 0;
        cin >> Coefficient;
        Newbie->Set(i, Coefficient);
        cout << endl;
    }

    std::cout << "Created polynominal: " << *Newbie << endl;
    std::cout << "Press any key" << endl;
    getch();

    return Newbie;
}

template<typename T>
ostream &operator<<(ostream &os, const Polynominal<T> &Obj);
/*{
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
}*/

template<typename T>
T InputValue()
{
    std::cout << "Give a value: " << std::endl;
    double X = 0;
    cin >> X;
    return X;
}

template<typename T>
void GiveAnX(const Polynominal<T> *Object)
{
    T Y;
    T X = InputValue<T>();

    for (int i = Object->GetOrderOfPolynominal(); i >= 0; i--)
    {
        Y += (*Object)[i] * pow(X, i);
    }

    std::cout << "Value for polynom (x = " << X << "): " << Y << endl;
}

template<typename T>
void Sum(const Polynominal<T> *Object)
{
    system("clear");

    std::cout << "Firstly input another polynom" << std::endl;
    std::cout << "Any key to input another polynom" << std::endl;

    getch();

    system("clear");

    const Polynominal<T> *Another = MenuInput<T>();

    system("clear");

    std::cout << "Sum of two polynominals:" << std::endl;
    std::cout << "\n\nFirst: " << (*Object) << std::endl;
    std::cout << "\nSecond: " << (*Another) << std::endl;
    std::cout << "\nTheir sum: " << ((*Object) + (*Another)) << std::endl;

    delete Another;
}

template <typename T>
void Substract(const Polynominal<T> *Object)
{
    system("clear");

    std::cout << "Substract menu\n"
         << endl;

    std::cout << "Firstly input another polynom" << endl;
    std::cout << "Any key to input another polynom" << endl;

    getch();

    system("clear");

    const Polynominal<T> *Another = MenuInput<T>();

    system("clear");

    std::cout << "Substract menu\n"
         << endl;

    std::cout << "Sum of two polynominals:" << endl;
    std::cout << "First: " << (*Object) << endl;
    std::cout << "Second: " << (*Another) << endl;
    std::cout << "Their substruction result: " << ((*Object) - (*Another)) << endl;

    delete Another;
}

template <typename T>
void MultiplyByArg(const Polynominal<T> *Object)
{
    std::cout << "Multiply by arg menu\n"
         << endl;
    T Arg = InputValue<T>();

    system("clear");

    std::cout << "Multiply by arg menu\n"
         << endl;

    std::cout << "(" << (*Object) << ")"
         << " * " << Arg << " :" << endl;
    cout << (*Object) * Arg << endl;
}

template <typename T>
void GetCoefByIndex(const Polynominal<T> *Object)
{
    system("clear");

    std::cout << "Get coefficient by index menu\n"
         << endl;
    cout << (*Object) << endl;
    std::cout << "Input index: ";
    int Index = 0;
    cin >> Index;
    std::cout << "Value: " << (*Object)[Index] << endl;
}

template <typename T>
void GetPremitiveFucntion(const Polynominal<T> *Object)
{
    system("clear");

    std::cout << "Get Premitive funtion menu\n"
         << endl;
    std::cout << "For : " << (*Object) << endl;
    std::cout << "Primitive function equals: " << (*Object).Primitive() << endl;
}

int MenuChoice()
{
    std::cout << "\n\t[1] - Give an X" << endl;
    std::cout << "\n\t[2] - Sum" << endl;
    std::cout << "\n\t[3] - Substract" << endl;
    std::cout << "\n\t[4] - Multiply by arg" << endl;
    std::cout << "\n\t[5] - Get coefficinent by index" << endl;
    std::cout << "\n\t[6] - Get premitive fucntion" << endl;
    std::cout << "\n\t[BACKSPACE] - Set new polynoms" << endl;
    std::cout << "\n\n\tEsc - Exit" << endl;
    while (true)
    {
        int key = getch();
        if ((key == 49) || (key == 50) || (key == 51) || (key == 52) || (key == 53) || (key == 54) || (key == 127) || (key == 27))
        {
            return key;
        }
    }
}

template <typename T> void Menu()
{
    while (true)
    {

        std::cout << "Hellow, world!" << endl;
        system("clear");

        Polynominal<T> *Object = nullptr;

        Object = MenuInput<T>();

        while (Object)
        {
            system("clear");

            std::cout << "Your polymon: ";
            cout<<*Object << std::endl;

            int Choice = MenuChoice();

            switch (Choice)
            {
            case 49: // Give an X
                GiveAnX<T>(Object);
                break;
            case 50: // Sum
                Sum<T>(Object);
                break;
            case 51: // Substract
                Substract<T>(Object);
                break;
            case 52: // Multiply by arg
                MultiplyByArg<T>(Object);
                break;
            case 53: // Get doef by index
                GetCoefByIndex<T>(Object);
                break;
            case 54: // Get premitive fucntion
                GetPremitiveFucntion<T>(Object);
                break;
            case 127: // Set new polynoms
                delete Object;
                Object = nullptr;
                break;
            case 27: // Exit
                system("clear");
                std::cout << "Word is done" << endl;
                return;
                break;
            default:
                break;
            }

            std::cout << "Press any key" << endl;
            getch();
        }
    }
}

int main()
{
    cout<<"Choose type:"<<std::endl;
    cout<<"[1] - int"<<std::endl;
    cout<<"[2] - float"<<std::endl;
    cout<<"[3] - double"<<std::endl;
    cout<<"[4] - complex (float)"<<std::endl;
    cout<<"[5] - complex (double)"<<std::endl;

    int Choice = 0;

    cin>>Choice;

    switch (Choice)
    {
    case 1:
        Menu<int>();
        break;
    case 2:
        Menu<float>();
        break;
    case 3:
        Menu<double>();
        break;
    case 4:
        Menu<std::complex<float>>();
        break;
    case 5:
        Menu<complex<double>>();
        break;
    
    default:
        break;
    }
    return 0;
}