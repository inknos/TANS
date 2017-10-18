#include <TH1F.h>
#include <TF1.h>
#include <TMath.h>
#include <TRandom3.h>
#include <TStyle.h>

const float a (0.5);

TF1 * probaProva(){
  TF1 * f =new TF1("f", "x", 0., 2*TMath::Pi());
  return f;
}

TF1 * probaVera(bool norm = false){
  TF1 * f =new TF1("f", "1./(TMath::Sin(x)*TMath::Sin(x) + [0] * TMath::Cos(x)*TMath::Cos(x))", 0., 2*TMath::Pi());
  f->SetParameter(0, a);
  return f;
}

class NReiezione{
  
private:
  TF1 * _f;
public:
  NReiezione(){
    _f = new TF1("_f", "1", 0., 1.);
  }
  NReiezione( TF1 * f ){
  _f = new TF1(* f);
  }
  // NReiezione(const NReiezione & r );
  ~NReiezione(){
    if( _f ) delete _f;
  }

  float GetRndm();

void Draw();

};


float NReiezione::GetRndm(){
  float xT, yT;
  float xMax = this->_f->GetXmax();
  float xMin = this->_f->GetXmin();
  float fMax = this->_f->GetMaximum();
  //cout << xMax << " " << xMin << " " << fMax << endl;
  while (true){
    xT = xMin + (xMax - xMin) * gRandom->Rndm();
    yT = fMax * gRandom->Rndm();
    if (_f->Eval(xT) > yT )
      return xT;
  }
}

void NReiezione::Draw(){
  _f->Draw();
}


void reiezione(){
  TF1 * ff = probaVera();
  //ff->Draw();
  NReiezione rr(ff);
  TH1F * hh = new TH1F("hh", "histo", 100, 0., 2 * TMath::Pi());
  rr.GetRndm();
  for(int i = 0 ; i < 10000 ; i++ ) hh->Fill(rr.GetRndm());
  //hh->Fit("f","","",0., 2*TMath::Pi());
  hh->Draw();    
}
