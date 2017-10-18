#include <TH1F.h>
#include <TH1D.h>
#include <TF1.h>
#include <TMath.h>
#include <TRandom3.h>
#include <TStyle.h>

typedef Double_t NType;
typedef TH1D     NHIST;

//------------------------------------------------------------

TF1 * fu();

TF1 * fa();

//------------------------------------------------------------

NType f(NType * x, NType * xx);

NType fc(NType(*pf)(NType*, NType*)); 

NType fi(NType * x, NType * xx);

//------------------------------------------------------------


NHIST * rejection(TF1 * func,
		  const char * name, const char * title,
		  Int_t bin, NType min, NType max,
		  Int_t sample = 100000, NHIST* hist = NULL){
  func->SetParameter(0,0.5);
  NType xT(0.), yT(0.);
  NType xMax = func->GetXmax();
  NType xMin = func->GetXmin();
  NType fMax = func->GetMaximum();
  NHIST * h = new NHIST(name, title, bin, min, max);
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

NHIST * inversion(NType(*pf)(NType*, NType *),
		  const char* name,
		  const char* title,
		  Int_t bin,
		  NType min,
		  NType max,
		  Int_t sample = 10000000, NType scale = 1.) {
  NHIST * histo = new NHIST("histo", "histo", bin, min, max);
  NType * temp = new NType[1];
  for (int i = 0; i < sample; i++){
    temp[0] = scale*gRandom->Rndm();
    histo->Fill(pf(temp, NULL));
  }
  delete [] temp;
  return histo;
}

//------------------------------------------------------------



void ma(){
   NHIST * hi = inversion(fi, "hi", "histo",
			 100, -10., 10., 10000000, 5.94);
   hi->Draw();
   NHIST * hr = rejection(fa(), "hr", "histo", 100, -10., 10.);
   hr->Draw("histsame");
}


//------------------------------------------------------------


TF1 * fu(){
  TF1 * f =new TF1("f", "1./(TMath::Sin(x)*TMath::Sin(x) + [0] * TMath::Cos(x)*TMath::Cos(x))", 0., 2*TMath::Pi());
  f->SetParameter(0, 0.5);
  return f;
}

TF1 * fa(){
  TF1 * f = new TF1("f", "TMath::Sin(x)*TMath::Sin(x)/(x*x)", -10.,10.);
  return f;
}





NType f(NType * x , NType * xx){
  // pdf
  if (x[0] < -2.6 || x[0] > 2.6) return 0.05;
  else return 1;
}

NType fc(NType * x , NType * xx){
  // cumulative function
  if (x[0] < -2.6) return 0.05 * x[0] + 0.5;
  if (x[0] >  2.6) return 0.05 * x[0] + 5.44;
  else             return        x[0] + 2.97;
}

NType fi(NType * x, NType * xx){
  // inverse cumulative function
  if (x[0] > 0    && x[0] < 0.37) return 20 * x[0] - 10;
  if (x[0] > 5.57 && x[0] < 5.94) return 20 * x[0] - 108.8;
  else                            return      x[0] - 2.97;
}



