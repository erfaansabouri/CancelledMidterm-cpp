#include <iostream>
#include <list>
using  namespace std;

int max(int x, int y){
    if(x>=y)
        return x;
    return y;
}


/** 2 - Design the abstract class of Poly as the parent of Polynomial **/
template <class Type , int deg>
class Poly{
protected:
    virtual void print() = 0;


    static list<Type> polys;
};

template <class Type , int deg>
list<Type> Poly<Type,deg>::polys;

template <class Type , int deg>
class Polynomial;
class Iterator{
private:
    int index;

public:
    int get(){
        return index;
    }
};
/** g - Type of its coefficients should be defined by a template **/
/** h - Degree of the coefficient is given in the template **/
template <class Type , int deg>
class Polynomial : public Poly<Type , deg>{


    /** 1 - a : Initialize with an array [a0 , a1 , ... an ] **/
    Type * coefficients;
    int degree = deg;


    /** 1 - a - i : The same action with operator = **/
public:
    void operator=(const int * coefficients){
        //this->coefficients = coefficients;
        this->coefficients = new int[degree];
        for(int i=0 ; i<degree ; i++)
            this->coefficients[i] = coefficients[i];
    }


public:
    /** b - Constructor **/
    Polynomial(const int *coefficients , int degree) : degree(degree){
        this->coefficients = new int[degree];
        for(int i=0 ; i<degree ; i++)
            this->coefficients[i] = coefficients[i];
    }

    Polynomial(const int *coefficients){
        this->coefficients = new int[degree];
        for(int i=0 ; i<degree ; i++)
            this->coefficients[i] = coefficients[i];
    }


public:
    /** c - Set or get of coefficient of any power **/
    Type& getCoeff(int power) const {
        return coefficients[power];
    }

    void setCoeff(Type & coeff , int power) {
        coefficients[power] = coeff;
    }


public:
    /** c - i - Both of them with operator [] **/
    Type& operator[](int power) const {
        return coefficients[power];
    }

    Type getCoeff_v2(int power){
        return operator[](power);
    }

    void setCoeff_v2(Type coeff , int power){
        operator[](power) = coeff;
    }


public:
    /** d - Add with a polynomial and returning the result. **/

    Polynomial& add(Polynomial & rhs){
        int max_of_degrees = max(degree,rhs.degree);
        this->degree = max_of_degrees;
        for(int i=0 ; i<max_of_degrees ; i++)
            coefficients[i] += rhs.coefficients[i];
        return *this;
    }

    Polynomial& operator+(Polynomial &rhs) {
        return add(rhs);
    }


public:
    /** e - Negating with unary operator – **/
    Polynomial& operator-(){
        for(int i=0 ; i<degree ; i++)
            coefficients[i] *= (-1);
        return *this;
    }

public:
    /** f. Implement iterator for it. **/

    int& getCoeff_v3(Iterator & iter){
        return coefficients[iter.get()];
    }

    void setCoeff_v3(Iterator & iter, Type value ){
        coefficients[iter.get()] = value;
    }


public:
    /** i - i Store coefficients in a dynamic array  With copy constructor **/
    Polynomial(const Polynomial & rhs){
        this->coefficients = new int[degree];
        for(int i=0 ; i<degree ; i++)
            this->coefficients[i] = rhs.coefficients[i];
    }
    /** i - ii Store coefficients in a dynamic array  With move constructor**/
    /*
    Polynomial(const Polynomial && rhs) noexcept{
        this->coefficients = new int[degree];
        for(int i=0 ; i<degree ; i++)
            this->coefficients[i] = rhs.coefficients[i];
    }*/

public:
    Polynomial() = default;




/** j. Implement printing of the polynomial with cout **/
public:
    void print(){
        cout<<"Poly = [ ";
        for(int i = 0; i<degree ; i++)
            cout << coefficients[i] << ", ";
        cout<< "\b\b ]" <<endl;
    }
};





/** 3- Design a new Polynomial which stores pairs of coefficient-power. **/

template <class Type>
        class Pair{
        public:
            Type coeff;
            int power;

            Pair(int coeff , int power):coeff(coeff) , power(power){}
        };


template <class Type , int deg>
class NewPolynomial : public Polynomial<Type, deg>{
public:
    list <Pair<Type>> storage_list;

    NewPolynomial(const int * coefficients){
        for(int i=0 ; i<deg ; i++){
            Pair<Type> new_pair(coefficients[i] , i);
            storage_list.push_back(new_pair);
        }
    }
};

int main() {
    int coeff_array[5] = {19,48,6,8,9};
    int coeff_array2[5] = {44,45,45,46,80};
    int coeff_array_second[6] = {2,20,30,40,50,90};

    Polynomial<int,6> p(coeff_array);
    p = coeff_array2;
    p.print();
    Polynomial<int,6> q(coeff_array_second);
    q.print();
    Polynomial<int,6> r = p+q;
    r = -r;
    r.print();

    Polynomial<int,6> s(coeff_array);
    Polynomial<int,6> t(coeff_array2);
    Polynomial<int,6> u = s;
    u.print();


    return 0;
}
