#include <iostream>
#include <cassert>
#include <algorithm>
#include <string>     // std::char_traits
using namespace std;

class String{
    public:
        String():_length(0), _capacity(DEFAULT_CAPACITY), _ptrData(nullptr){}
        String(const char *str){
            _length = char_traits<char>::length(str);
            _init(_length);
            for(size_t i=0; i<_length; i++){
                _ptrData[i] = str[i];
            }
        }

        
        friend ostream& operator<<(ostream& out, const String& str){
            if(str._length==0){
                return cout;
            }
            return out << str._ptrData;
        }

        int find_in(const char *sub){
            size_t n_sub = char_traits<char>::length(sub);
            for(size_t i = 0; i < _length-n_sub; i++){
                size_t count = 0;
                for(size_t j = 0; j < n_sub; j++){
                    if(_ptrData[i+j] != sub[j]){
                        break;
                    }
                    count++;
                }
                if (count == n_sub){
                    return i;
                }
            }
            return -1;
        }
        String sub(size_t start, size_t len){
            size_t end = start + len;
            if(end > _length){
                end = _length;
            }
            if(start >= end){
                return String();
            }
            String s;
            s._init(end - start);
            for(size_t i = 0; i < (end - start); i++){
                s._ptrData[i] = _ptrData[start+i];
            }
            return s;
        }
        bool operator==(const String& str) const{
            if(_length != str._length){
                return false;
            }

            for(size_t i = 0; i < _length; i++){
                if(_ptrData[i] != str._ptrData[i]){
                    return false;
                }
            }
            return true;
        }

        String operator+(const String& str) const{
            String s;
            s._init(_length + str._length);
            for(size_t i=0; i<_length; i++){
                s._ptrData[i] = _ptrData[i];
            }
            for(size_t i=0; i<str._length; i++){
                s._ptrData[_length+i] = str._ptrData[i];
            }
            return s;
        }
    private:
        size_t _length;
        size_t _capacity;
        char *_ptrData;
        void _init(size_t length){
            if(_capacity < length){
                _capacity = length + 1;
            }else{
                _capacity = DEFAULT_CAPACITY;
            }
            _ptrData = new char[_capacity];
            _length = length;
        }

        static const size_t DEFAULT_CAPACITY = 10;


};


int main(){
    String s;
    cout << s << endl;
    String s1("hola mundou, ");
    cout << s1 << endl;
    String s2("enfermera!!!");
    String s3 = s1 + s2;
    cout << "after concat" << endl;
    cout << s3 << endl;
    String s4("enfermera!!!");
    cout << s2 << " == " << s4 << "? " << (s2 == s4) << endl;

    const char* sub = "fr";
    cout << "find " << sub << " in " << s4.find_in(sub) << endl;

    cout << s4.sub(3, 4) << endl;

    return 0;
}
