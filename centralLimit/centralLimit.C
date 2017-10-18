#if !defined(__CINT__) || defined(__MAKECINT__)

#include <Riostream.h>
#include <TH1D.h>
#include <TCanvas.h>
#include <TRandom3.h>

#endif

#define BINS    100
#define ENTRIES 200000

typedef Double_t NType;

class NCumulativeHisto {
 private:
  TH1D _histo;
  NType  _counter;
  
  NType Distribution() const {
    NType r = gRandom->Rndm();
    r < 0.5 ? r = r * 0.4 : r = 0.6 + r * 0.4 ;
    return r;
  }

 
 public:
  NCumulativeHisto() : _counter(0.), _histo() {
    clog << "def " << this << endl;
  }
  
  NCumulativeHisto(const char* name, const char* title, Int_t n = BINS, NType min = 0., NType max = 1.) :
    _counter(1.),
    _histo(name, title, n, min, max) {
    clog << "par " << this << endl;;
    for ( int i = 0 ; i < ENTRIES ; i++ )
      _histo.Fill(Distribution());
  }

  NCumulativeHisto(NType n) :
    _counter(n) {
    NCumulativeHisto();
  }

  NCumulativeHisto& operator=(const NCumulativeHisto& obj){
    if( this == &obj ) return *this;
    clog << "op. = 2 " << this << endl;
    _histo = obj._histo;
    return *this;
  }

  NCumulativeHisto& operator++(){
    clog<<"pre ++\n";
    _counter++;
    TH1D tmp("tmp", "tmp", BINS, 0., _counter);
    for( int i = 0 ; i < ENTRIES ; i++ ) {
      tmp.Fill(_histo.GetRandom() + _histo.GetRandom());
    }
    _histo = (tmp);
    return *this;
  }
  
  NCumulativeHisto  operator++(int){
    clog << "post ++\n";
    NCumulativeHisto tmp(*this);
    operator++();
    return tmp;
  }

  void Draw(){
    new TCanvas();
    _histo.DrawCopy();
  }
  
};
