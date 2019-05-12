#include <iostream>
#include <algorithm>
using namespace std;

class Fraction{
    public: 
        Fraction(){Fraction(0, 1);}
        Fraction(int numerator, int denominator): \
            _numerator(numerator), _denominator(denominator){
            if(_numerator < 0 && _denominator < 0){
                _numerator = -numerator;
                _denominator = -denominator;
            } 
        }

        void display() const{
            cout << _numerator << " / " << _denominator << endl;
        }
        Fraction reduce() const{
            if(_numerator == 0){
                return Fraction();
            }
            if(_denominator == 0){
                return Fraction(_numerator, 0);
            }

            int div = __gcd(_numerator, _denominator);
            return Fraction(_numerator/div, _denominator/div);
        }

        Fraction plus(Fraction rhs) const{
            int num = (_numerator * rhs.denominator()) + (rhs.numerator() * _denominator);
            int den = _denominator * rhs.denominator();

            return Fraction(num, den).reduce();
        }

        Fraction minus(Fraction rhs) const{
            int num = (_numerator * rhs.denominator()) - (rhs.numerator() * _denominator);
            int den = _denominator * rhs.denominator();
            
            return Fraction(num, den).reduce();
        }
        Fraction times(Fraction rhs) const{
            int num = _numerator * rhs.numerator();
            int den = _denominator * rhs.denominator();
            
            return Fraction(num, den).reduce();
        }

        Fraction divided(Fraction rhs) const{
            int num = _numerator * rhs.denominator();
            int den = _denominator * rhs.numerator();
            
            return Fraction(num, den).reduce();
        }


        int compare(Fraction rhs) const{
            if ( equal(rhs) ){
                return 0;
            } else if (greater(rhs)){
                return 1;
            } else { // less than
                return -1;
            }
        }

        int equal(Fraction rhs) const{
            if(_numerator == rhs.numerator() && _denominator == rhs.denominator()){
                return 1;
            }
            return 0;
        }
        int greater(Fraction rhs) const{
            if( (_numerator * rhs.denominator()) > (rhs.numerator() * _denominator) ){
                return 1;
            }            
            return 0;
        }
        int less(Fraction rhs) const{
            if( (_numerator * rhs.denominator()) < (rhs.numerator() * _denominator) ){
                return 1;
            }            
            return 0;
        }
        int numerator() const{
            return _numerator;
        }
        inline int GetNumerator()const{
            return _numerator;
        }

        int denominator() const{
            return _denominator;
        }
        inline int GetDenominator() const{
            return _denominator;
        }
        const static Fraction HALF;
        const static Fraction THIRD;
        const static Fraction FOURTH;
        const static Fraction FIFTH;

    private:
        int _numerator, _denominator;
};

const Fraction Fraction::HALF   = Fraction(1, 2);
const Fraction Fraction::THIRD  = Fraction(1, 3);
const Fraction Fraction::FOURTH = Fraction(1, 4);
const Fraction Fraction::FIFTH  = Fraction(1, 5);


int main(){
    cout << "First fraction" << endl;
    Fraction f0(2, 3);
    f0.display();
    cout << "Second fraction" << endl;
    Fraction f1(1, 3);
    f1.display();

    cout << endl << "Addition" << endl;
    Fraction f0p1 = f0.plus(f1);
    f0p1.display(); 

    cout << endl << "Subtraction" << endl;
    Fraction f0m1 = f0.minus(f1);
    f0m1.display(); 

    cout << endl << "Multiplication" << endl;
    Fraction f0t1 = f0.times(f1);
    f0t1.display(); 

    cout << endl << "Division" << endl;
    Fraction f0d1 = f0.divided(f1);
    f0d1.display(); 

    cout << endl << "What's a static half?" << endl;
    Fraction::HALF.display();

    return 0;
}
