#include <TH1F.h>
#include <TF1.h>
#include <TMath.h>
#include <TRandom3.h>
#include <TStyle.h>

typedef Double_t NType;
typedef TH1D     NHIST;

TF1 * fu();

TF1 * fa();

NHIST * rejection(TF1 * func,
		  const char * name, const char * title,
		  Int_t bin, NType min, NType max);



void ma(){
  NHIST * hh = rejection(fa(), "hh", "histo", 100, -10., 10.);
  hh->Draw();
}




TF1 * fu(){
  TF1 * f =new TF1("f", "1./(TMath::Sin(x)*TMath::Sin(x) + [0] * TMath::Cos(x)*TMath::Cos(x))", 0., 2*TMath::Pi());
  f->SetParameter(0, 0.5);
  return f;
}

TF1 * fa(){
  TF1 * f = new TF1("f", "TMath::Sin(x)*TMath::Sin(x)/(x*x)", -10.,10.);
  return f;
}

NHIST * rejection(TF1 * func,
		  const char * name, const char * title,
		  Int_t bin, NType min, NType max,
		  Int_t sample = 100000, NHIST* hist = NULL){
  cout << "1" << endl;
  func->SetParameter(0,0.5);
  cout << "1.2" << endl;
  NType xT(0.), yT(0.);
  cout << "1.2.1" << endl;
  NType xMax = func->GetXmax();
  cout << "1.2.1" << endl;
  NType xMin = func->GetXmin();
  cout << "1.2.1" << endl;
  NType fMax = func->GetMaximum();
  cout << "1.3"<<endl;
  NHIST * h = new NHIST(name, title, bin, min, max);
  cout<<"2"<<endl<<flush;
  for( int i = 0; i < sample; i++ ){
    while (true){
      xT = xMin + (xMax - xMin) * gRandom->Rndm();
      yT = hist->GetBinContent(xT);
      if (func->Eval(xT) > yT )
	break;
    }
    h->Fill(xT);
  }
  return h;
}
