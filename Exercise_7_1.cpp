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

        String(const String &rhs){
            _init(rhs._length);
            for(size_t i=0; i<_length; i++){
                _ptrData[i] = rhs._ptrData[i];
            }
        }

        ~String(){
            _length = 0;
            _capacity = 0;
            if(_ptrData != nullptr){
                delete [] _ptrData;
                _ptrData = nullptr;
            }
        }

        friend ostream& operator<<(ostream& out, const String& str){
            if(str._length==0){
                return cout;
            }
            return out << str._ptrData << " [" << str._length << "/" \
                    << str._capacity << "]";
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
                String s;
                return s;
            }
            String s;
            size_t slen = end - start;
            s._init(slen);
            for(size_t i = 0; i < slen; i++){
                s._ptrData[i] = _ptrData[start+i];
            }
            return s;
        }

        String& operator=(const String& rhs){
            if((*this) == rhs){
                return (*this);
            }

            if(_length == 0 || _ptrData == nullptr){
                _init(rhs._length);
            }else{
                _reset(rhs._capacity);
            }

            _length = rhs._length;
            for(size_t i=0; i<_length; i++){
                _ptrData[i] = rhs._ptrData[i];
            }

            return (*this);
        }

        String& operator=(const char* rhs){
            size_t len = char_traits<char>::length(rhs);
            if(_length == 0 || _ptrData == nullptr){
                _init(len);
            }else{
                
                size_t cap = String::DEFAULT_CAPACITY;
                if(cap < len){
                    cap = len + 1;
                }
                _reset(cap);
                _length = len;
            }

            
            for(size_t i=0; i<_length; i++){
                _ptrData[i] = rhs[i];
            }

            return (*this);
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

        String& operator+=(const String& str){
            if(_length == 0 || _ptrData == nullptr){
                _init(str._length);
                for(size_t i=0; i<_length; i++){
                    _ptrData[i] = str._ptrData[i];
                }
                return (*this);
            }else{
                char *orig = _ptrData;
                size_t len = _length;
                _reset(_length + str._length + 1, false);
                for(size_t i=0; i < len; i++){
                    _ptrData[i] = orig[i];
                }
                for(size_t i=0; i < str._length; i++){
                    _ptrData[len+i] = str._ptrData[i];
                }
                delete [] orig;
                _length = len + str._length;
                return (*this);
            }
        }

        String& operator+=(const char c){
            if(_length == 0 || _ptrData == nullptr){
                _init(1);
                _ptrData[0] = c;
                return (*this);
            }else{
                char *orig = _ptrData;
                size_t len = _length;
                _reset(_length + 2, false);
                for(size_t i=0; i < len; i++){
                    _ptrData[i] = orig[i];
                }
                _ptrData[len] = c;
                _length = len + 1;
                if(orig != _ptrData){
                    delete [] orig;
                }
                return (*this);
            }
        }
        
        char operator[](const size_t index) const{
            assert(index < _length && "index not assigned!");
            if (index < _length){
                return _ptrData[index];
            }
            return 0;
        }
        // char& operator[](const size_t index){
        //     assert(index < _length && "index not assigned!");
        //     if (index < _length){
        //         return _ptrData[index];
        //     }
        //     return ;
        // }

        const char* to_literal(){
            char *str = new char[_length];
            for(size_t i=0; i<_length; i++){
                str[i] = _ptrData[i];
            }
            return (const char*)str;
        }

        inline size_t length() const{return _length;}
        
    private:
        size_t _length;
        size_t _capacity;
        char *_ptrData;
        void _init(size_t length){
            if(_capacity < length){
                _capacity = length * 2;
            }else{
                _capacity = DEFAULT_CAPACITY;
            }
            _ptrData = new char[_capacity];
            _length = length;
        }
        void _reset(size_t capacity, bool del=true){
            _length = 0;
            if(capacity < _capacity){
                return;
            }

            _capacity = capacity;
            if(_ptrData != nullptr && del == true){
                delete [] _ptrData;
                _ptrData = nullptr;
            }

            _ptrData = new char[capacity];
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

    cout << s4[1] << endl;

    String s5 = s4;
    cout << "copied?" << endl;
    cout << s5 << " " << (s4 == s5) << endl;

    String s6 = "doritos nachos";
    cout << s6 << endl;
    String s7("yellow ");
    cout << s7 << endl;
    s7 += String("there");
    cout << s7 << endl;
    s7 += '!';
    cout << s7 << endl;

    cout << "to literal" << endl;
    cout << s7.to_literal() << endl;
    

    return 0;
}
