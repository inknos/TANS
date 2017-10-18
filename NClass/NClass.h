#ifndef NCLASS_H
#define NCLASS_H

#include "TObject.h"

class NClass : public TObject {

 private:
  Double_t _height; // height
  Double_t _weight; // weight
  Int_t    _age;    // age
  Int_t    _size;   // size of _info
  Int_t *  _info;   // [_size] numerical info
  Bool_t   _male;   // true if male

 public:

  // constructors
  NClass();
  NClass(Double_t, Double_t, Int_t, Bool_t);
  NClass(const NClass& obj);
  virtual ~NClass(); // must be virtual

  // operators
  NClass& operator=(const NClass&);
  
  // methods
  Double_t GetHeight() const { return _height; }
  Double_t GetWeight() const { return _weight; }
  Int_t    GetAge()    const { return _age; }
  Bool_t   IsMale()    const { return _male; }
  Int_t    GetArray(int i) const {
    return ( i > 0 && i < _size ) ? _info[i] : -1;
  } 
  void PrintStatus() const;
  void SetArray(Int_t *, Int_t);

  ClassDef(NClass, 1)
};


#endif
