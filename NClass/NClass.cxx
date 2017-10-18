#include <Riostream.h>
#include "NClass.h"
#include "TString.h"

ClassImp(NClass)

NClass::NClass() : TObject(),
  _height(0.),
  _weight(0.),
  _age(0),
  _size(0),
  _info(NULL),
  _male(false) { clog << "def constr. " << this << endl; }

NClass::NClass(Double_t _h, Double_t _w, Int_t _a, Bool_t _m) :
  TObject(),
  _height(_h),
  _weight(_w),
  _age(_a),
  _size(0),
  _info(NULL),
  _male(_m) { clog << "par constr. " << this << endl; }

NClass::NClass(const NClass& obj) :
  TObject(),
  _height(obj._height),
  _weight(obj._weight),
  _age(obj._age),
  _size(obj._size),
  _male(obj._male) {
  clog << "cop constr. " << this << endl; 
  if( _size > 0 ) {
    _info = new Int_t[_size];
    for( int i = 0 ; i < _size ; i++ )
      _info[i] = obj._info[i];
  }
  else _info = NULL;
}

NClass::~NClass() {
  clog << "destructor " << this << endl; 
  if( _size > 0 ) delete []_info;
}

/* classic assignment op.
NClass& NClass::operator=(const NClass& obj) {
  clog << "op. = 1 " << this << endl; 
  if( this != &obj ) {
    if( _size > 0 ) delete []_info;
    TObject::operator=(obj);
    _height = obj._height;
    _weight = obj._weight;
    _age    = obj._age;
    _size   = obj._size;
    _male   = obj. male;
    if( _size > 0 ) {
      _info = new Int_t[_size];
      for(int i = 0 ; i < _size ; i++ )
	_info[i] = obj._info[i];
    }
    else _info = NULL;
  }
  return *this;
}
*/

/* cool assignment operator*/
NClass& NClass::operator=(const NClass& obj) {
  if( this == &obj ) return *this;
  clog << "op. = 2 " << this << endl;
  this->~NClass();
  new(this) NClass(obj);
  return *this;
}

void NClass::PrintStatus() const {
  clog << "print status" << endl;
  TString sex = "F";
  if ( this->_male ) sex = "M";
  cout << "age:    " << '\t' << _age << '\t'
       << "sex:    " << '\t'<< sex.Data() << '\n'
       << "height: " << '\t'<< _height << '\t'
       << "weight: " << '\t'<< _weight << '\n';
  if( _size > 0 ) {
    cout << "info aggiuntive:\n";
    for( int i = 1 ; i < _size + 1 ; i++ ) {
      cout << _info[i - 1] << '\t';
      if( i%6 == 0 ) cout << endl;
    }
  }
  cout << endl;
}

void NClass::SetArray(Int_t * arr, Int_t siz) {
  if ( _size > 0 ) delete []_info;
  _info = new Int_t[siz];
  _size = siz;
  for( int i = 0 ; i < _size ; i++ ) _info[i] = arr[i];
}
