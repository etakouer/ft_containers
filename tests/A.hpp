#include <iostream>

class A {
    public:
    std::string _name;
    A(){
        _name = "?";
        #ifdef DEBUG
        std::cout << "A()" << std::endl;
        #endif
    }

    A(std::string name) :  _name(name){
        #ifdef DEBUG
        std::cout << "A("<< _name <<")" << std::endl;
        #endif
    }

    A(int i) :  _name(std::to_string(i)){
        #ifdef DEBUG
        std::cout << "A("<< _name <<")" << std::endl;
        #endif
    }

    A(A const & a){
        #ifdef DEBUG
        std::cout << "A(A &a) a.name: " << a._name << std::endl;
        //_name = "copie constructeur de " + a._name;
        #endif
        _name = a._name;
    }

     A & operator=(A const & a){
        #ifdef DEBUG
        std::cout << "operator=(A &a) this.name : " << _name << " a.name : " << a._name << std::endl;
        //_name = "copie operateur= de " + a._name;
        #endif
        _name = a._name;
        return *this;
    }
   ~A(){
        #ifdef DEBUG
        std::cout << "~A() name : " << _name << std::endl;
        #endif
    }
     A operator+(A const & a) const {
        return A(_name + " + " + a._name);
     }
     A operator-(A const & a) const {
        return A(_name + " - " + a._name);
     }
     A operator+=(A const & a) {
        *this = *this + a;
        return *this;
     }
     A operator-=(A const & a) {
        *this = *this - a;
        return *this;
     }

     A operator*(A const & a) const{
        return A(_name + " * " + a._name);
     }
     A operator/(A const & a) const{
        return A(_name + " / " + a._name);
     }
     A operator++(void){
        _name += " ++ " + _name;
        return *this;
     }
     A operator++(int){
         A tmp(*this);
        _name += " ++ " + _name;
        return tmp;
     }
     A operator--(void){
        _name += " -- " + _name;
        return *this;
     }
     A operator--(int){
         A tmp(*this);
        _name += " -- " + _name;
        return tmp;
     }

};

bool operator==(const A & lhs, const A & rhs) {
       #ifdef DEBUG
      std::cout << lhs._name <<  " == " << rhs._name << std::endl;
       #endif
      return lhs._name == rhs._name;
}
bool operator!= (const A & lhs, const A & rhs){
       #ifdef DEBUG
      std::cout << lhs._name <<  " != " << rhs._name << std::endl;
       #endif
      return !(lhs == rhs);
}

  bool operator<  (const A & lhs, const A & rhs){
       #ifdef DEBUG
      std::cout << lhs._name <<  " <  " << rhs._name << std::endl;
       #endif
      return lhs._name < rhs._name;
}

  bool operator<= (const A & lhs, const A & rhs){
       #ifdef DEBUG
      std::cout << lhs._name <<  " <=  " << rhs._name << std::endl;
       #endif
      return !(rhs < lhs);
}

  bool operator>  (const A & lhs, const A & rhs){
       #ifdef DEBUG
      std::cout << lhs._name <<  " > " << rhs._name << std::endl;
       #endif
      return rhs < lhs;
}

  bool operator>= (const A & lhs, const A & rhs){
       #ifdef DEBUG
      std::cout << lhs._name <<  " >= " << rhs._name << std::endl;
       #endif
      return !(lhs < rhs);
}

std::ostream & operator<<(std::ostream & o, A const & a) {
    o << a._name;
    return o;
}
