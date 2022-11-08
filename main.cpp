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
ostream& operator<<(ostream &os, const Polynominal<T> &Obj)
{
    if (Obj.GetOrderOfPolynominal() == -1)
    {
        cout << "Polynominal has no coefs" << endl;
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

template<typename T>
void MenuInputComplex()
{
    system("clear");

    cout << "Create poilynominal menu\n\n"
         << endl;

    cout << "Order of Polynominal: " << endl;
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

    double R = 0;
    double I = 0;

    for (int i = OrderOfPolynominal; i >= 0; i--)
    {
        cout << "Coef by (input like : *real *img)" << i << ":\n";
        string str;
        cin>>str;

        R = stoi(str);

        cin>>str;
        I = stoi(str);

        Newbie->Set(i,T(R,I));
    }

    cout << "Created polynominal: " << *Newbie << endl;
    cout << "Press any key" << endl;
    getch();

    Menu2(Newbie);
}

template<typename T>
void Menu1()
{
    cout << "Create poilynominal menu\n\n"
         << endl;

    cout << "Order of Polynominal: " << endl;
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

    for (int i = OrderOfPolynominal; i >= 0; i--)
    {
        cout << "Coef by " << i << ":\n";
        T Coefficient;
        cin >> Coefficient;
        Newbie->Set(i, Coefficient);
    }

    cout << "Created polynominal: " << *Newbie << endl;
    cout << "Press any key" << endl;
    getch();

    Menu2(Newbie);
}

template<typename T>
Polynominal<T> * MenuInputArg()
{
    cout << "Create poilynominal menu\n\n"
         << endl;

    cout << "Order of Polynominal: " << endl;
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

    for (int i = OrderOfPolynominal; i >= 0; i--)
    {
        cout << "Coef by " << i << ":\n";
        T Coefficient;
        cin >> Coefficient;
        Newbie->Set(i, Coefficient);
    }

    cout << "Created polynominal: " << *Newbie << endl;
    cout << "Press any key" << endl;
    getch();

    return Newbie;
}

template<typename T>
ostream &operator<<(ostream &os, const Polynominal<T> &Obj);
/*{
    if (Obj.GetOrderOfPolynominal() == -1)
    {
        cout << "Polynominal has no coefs" << endl;
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
    cout << "Give a value: " << endl;;
    double X = 0;
    cin >> X;
    return X;
}

template<typename T>
void GiveAnX(const Polynominal<T> *Object)
{
    T X = InputValue<T>();

    T Y = Object->CountValue(X);

    cout << "Value for polynom (x = " << X << "): " << Y << endl;
}

template<typename T>
void Sum(const Polynominal<T> *Object)
{
    system("clear");

    cout << "Firstly input another polynom" << endl;;
    cout << "Any key to input another polynom" << endl;;

    getch();

    system("clear");

    const Polynominal<T> *Another = MenuInputArg<T>();

    system("clear");

    cout << "Sum of two polynominals:" << endl;;
    cout << "\n\nFirst: " << (*Object) << endl;;
    cout << "\nSecond: " << (*Another) << endl;;
    cout << "\nTheir sum: " << ((*Object) + (*Another)) << endl;;

    delete Another;
}

template <typename T>
void Substract(const Polynominal<T> *Object)
{
    system("clear");

    cout << "Substract menu\n"
         << endl;

    cout << "Firstly input another polynom" << endl;
    cout << "Any key to input another polynom" << endl;

    getch();

    system("clear");

    const Polynominal<T> *Another = MenuInputArg<T>();

    system("clear");

    cout << "Substract menu\n"
         << endl;

    cout << "Sum of two polynominals:" << endl;
    cout << "First: " << (*Object) << endl;
    cout << "Second: " << (*Another) << endl;
    cout << "Their substruction result: " << ((*Object) - (*Another)) << endl;

    delete Another;
}

template <typename T>
void MultiplyByArg(const Polynominal<T> *Object)
{
    cout << "Multiply by arg menu\n"
         << endl;
    T Arg = InputValue<T>();

    system("clear");

    cout << "Multiply by arg menu\n"
         << endl;

    cout << "(" << (*Object) << ")"
         << " * " << Arg << " :" << endl;
    cout << (*Object) * Arg << endl;
}

template <typename T>
void GetCoefByIndex(const Polynominal<T> *Object)
{
    system("clear");

    cout << "Get coefficient by index menu\n"
         << endl;
    cout << (*Object) << endl;
    cout << "Input index: ";
    int Index = 0;
    cin >> Index;
    cout << "Value: " << (*Object)[Index] << endl;
}

template <typename T>
void GetPremitiveFucntion(const Polynominal<T> *Object)
{
    system("clear");

    cout << "Get Premitive funtion menu\n"
         << endl;
    cout << "For : " << (*Object) << endl;
    cout << "Primitive function equals: " << (*Object).Primitive() << endl;
}

int MenuChoice()
{
    cout << "\n\t[1] - Give an X" << endl;
    cout << "\n\t[2] - Sum" << endl;
    cout << "\n\t[3] - Substract" << endl;
    cout << "\n\t[4] - Multiply by arg" << endl;
    cout << "\n\t[5] - Get coefficinent by index" << endl;
    cout << "\n\t[6] - Get premitive fucntion" << endl;
    cout << "\n\t[BACKSPACE] - Set new polynoms" << endl;
    cout << "\n\n\tEsc - Exit" << endl;
    while (true)
    {
        int key = getch();
        if ((key == 49) || (key == 50) || (key == 51) || (key == 52) || (key == 53) || (key == 54) || (key == 127) || (key == 27))
        {
            return key;
        }
    }
}

template <typename T> void Menu2(Polynominal<T> *Object)
{
    while (true)
    {
        system("clear");

        while (Object)
        {
            system("clear");

            cout << "Your polymon: ";
            cout<<*Object << endl;;

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
                cout << "Work is done" << endl;
                return;
                break;
            default:
                break;
            }

            cout << "Press any key" << endl;
            getch();
        }
        return;
    }
}

int main()
{
    while(true){
        system("clear");
        cout<<"Choose type:"<<endl;;
        cout<<"[1] - int"<<endl;;
        cout<<"[2] - float"<<endl;;
        cout<<"[3] - double"<<endl;;
        cout<<"[4] - complex (float)"<<endl;;
        cout<<"[5] - complex (double)"<<endl;;
        cout<<"[ESC] - Exit"<<endl;;

        int Choice = getch();

        switch (Choice)
        {
        case 49:
            Menu1<int>();
            break;
        case 50:
            Menu1<float>();
            break;
        case 51:
            Menu1<double>();
            break;
        case 52:
            MenuInputComplex<std::complex<float>>();
            break;
        case 53:
            MenuInputComplex<complex<double>>();
            break;
        case 27:
            return EXIT_SUCCESS;
        default:
            system("clear");
            break;
        }
    }
}