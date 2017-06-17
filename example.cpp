#if !defined(BOOST_SPIRIT_X3_CALC9_STATEMENT_DEF_HPP)
#define BOOST_SPIRIT_X3_CALC9_STATEMENT_DEF_HPP

#include <boost/spirit/home/x3.hpp>
#include <boost/spirit/home/x3/support/utility/annotate_on_success.hpp>

df + df;
dfd + df;

const long int main();

{
	dfd;
	34 + fd;
	dfdf(3,34);
}

if(int i = 2 == 2)
	{
		cout<<"i = "<<i<<endl;
	}
    
if(switchs_case *item = boost::get<switchs_case>(i))
{
    cout<<"case ";
    (*this)(item->condition);
    cout<<":\n";
    (*this)(item->action);
}
	
try {
    f();
} catch (const std::overflow_error& e) {
} catch (const std::runtime_error& e) {
} catch (const std::exception& e) {
} catch (...) {
}

int main(int argc,char *argv)
{
    cout<<"Hello World!"<<std::endl;
}

class Person
{
    Person(int age){
        
    }
    int Person(int fd);
    static const int d=d;
    
    Person operator+ (Person anotherPerson){
        
    }
};


struct dfd{
    int f;
    int start;
    int end;
}*dfd;

class Person;
class Person *me;

34 + e;

class S {
    int d1; // non-static data member
    int a[10] = {1,2}; // non-static data member with initializer (C++11)
    static const int d2 = 1; // static data member with initializer
    virtual void f1(int) = 0; // pure virtual member function
    std::string d3, *d4, f2(int); // two data members and a member function
    enum {NORTH, SOUTH, EAST, WEST};
    struct NestedS {
        std::string s;
    } d5, *d6;
    typedef NestedS value_type, *pointer_type;
};

switch(number){
case 4:
    34 + df;
default:
    34 + df;
}

for(int i = 1,w=2;i<24;i++){
    
}

while (--x >= 0)
    int i;

do{
    int a = 34 + 34;
}while(true);

#define hello "dfdf by some\
    dfdfd dfdfdfdf
    
    
namespace {
    int g = 0;
}

namespace space {
    int g = "hello";
}

namespace area = space;

using error_handler = x3::error_handler<Iterator>;
using std::cout;
using namespace std;

namespace Q {
  namespace V { // original-namespace-definition for V
    void f(); // declaration of Q::V::f
  }
  void V::f() {} // OK
  void V::g() {} // Error: g() is not yet a member of V
  namespace V { // extension-namespace-definition for V
    void g(); // declaration of Q::V::g
  }
}
namespace R { // not a enclosing namespace for Q
   void Q::V::g() {} // Error: cannot define Q::V::g inside R
}
void Q::V::g() {} // OK: global namespace encloses Q

template <typename Iterator>
using error_handler = x3::error_handler<Iterator>;
