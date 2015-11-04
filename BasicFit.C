#ifndef __CINT__
#include "RooGlobalFunc.h"
#endif
#include "RooRealVar.h"
#include "RooDataSet.h"
#include "RooDataHist.h"
#include "RooGaussian.h"
#include "RooPlot.h"
#include "TTree.h"
#include "TH1D.h"
#include "TRandom.h"
#include<iostream>
#include "TCanvas.h"
#include "RooPlot.h"
#include "TAxis.h"
#include<vector>
#include "TH1.h"
#include "TH2.h"
#include "TGraph.h"
#include "TFile.h"
#include "TCanvas.h"
#include "TString.h"
#include "TDirectory.h"
#include "ReadTree.cc"
#include "ReadTreeData.cc"
//#include "PlotHisto.C"
#include "SetStyle.C"


using namespace std;
using namespace RooFit ;
void BasicFitfun(){



   double rangeMax=0.02;
   double rangeMin=0.005;
   int nBins=80;

  

   TH1F *hpromptSR=new TH1F("hpromptSR","hpromptSR",nBins,rangeMin,rangeMax);
   hpromptSR->SetLineWidth(1);

   

    TChain* t1 = new TChain("SimpleTree");
    t1->Add("GJetsFullHT.root");//GJets100HTInf.root");//SignalGJets3.root");
    ReadTree read1(t1);


    int maxEvents1=t1->GetEntries();
    cout<<"maxEventsGJets: "<<maxEvents1<<endl;
    for(int i1=0;i1<maxEvents1;i1++){//GJets loop
    t1->GetEntry(i1);
    if(i1 % 1000000==0){cout<<"Event no GJets : "<<i1<<endl;}

   if(read1.isBarrel==1 && read1.nonPrompt !=1 && read1.BaseLine()==true && read1.evWeight<3. && read1.IchSR==1 ){//prompt 
 
   
   hpromptSR->Fill(read1.SigmaIetaIeta,read1.evWeight);
   if(read1.SigmaIetaIeta < 0.02){
    //htotalSR->Fill(read1.SigmaIetaIeta,read1.evWeight);  
       }

   



   }//prompt


   }//GJets loop




   TCanvas* c = new TCanvas("c","test",570,400);

  RooRealVar mtop("mtop","M (GeV/c^{2})",0.00,0.022) ;
  RooDataHist ds("ds","ds",mtop,Import(*hpromptSR)) ;
  ds.Print();


  RooPlot* frame = mtop.frame(Title("Prompt Photons(#gamma +Jets)"));

  ds.plotOn(frame) ;

  RooRealVar mean("mean","mean",0.009118,0.006,0.012);
  RooRealVar sigma("sigma","sigma",0.0005264,0.0000023,0.00055200);
  RooGaussian gtop("gtop","gtop",mtop,mean,sigma);
  
  RooRealVar sigma1("sigma1","sigma1",0.00023,0.00005,0.0005);
  RooRealVar sigma2("sigma2","sigma2",0.0004264,0.0000023,0.001200);
  RooBifurGauss bgtop("bgtop","bgtop",mtop,mean,sigma1,sigma2);

  RooGaussian gtop2("gtop2","gtop2",mtop,mean,sigma1);  



  RooRealVar frac0("frac0","frac0",0.25,0.1,0.6);

  RooRealVar  frac1("frac1","frac1",0.15,0.1,0.90);

  RooAddPdf pdfg("pdfg","double gaussian Pdf", RooArgList(bgtop,gtop),RooArgList(frac0));

  RooAddPdf pdfgg2("pdfgg2","double gaussian Pdfg2", RooArgList(gtop2,gtop),RooArgList(frac1));


  RooRealVar slope("slope","slope",1.0,0.9,1.3);
  RooChebychev cheb("cheb","cheb",mtop,slope);
  RooRealVar frac("frac","frac",0.5,0.001,1.00);



  RooAddPdf pdf("pdf","total Pdf", RooArgList(pdfgg2,cheb),RooArgList(frac));



  pdf.fitTo(ds);
  pdf.plotOn(frame);
  pdf.paramOn(frame);
  std::cout<<"Chi Square ="<<frame->chiSquare()<<std::endl;




  RooPlot* z1frame = mtop.frame(Title("SigmaIetaIeta"));
  RooHist* hpull1 = frame->pullHist();
  z1frame->addPlotable(hpull1,"P");

  RooPlot* z2frame = mtop.frame(Title("SigmaIetaIeta"));
  RooHist* hresid = frame->residHist();
  z2frame->addPlotable(hresid,"P") ;

  TCanvas* c2 = new TCanvas("pull1","pull1",1200,800) ;
 // c2->Divide(2,1) ; // column, row
  double xmin = 0.000; double xmax = 0.03;
  TLine *line = new TLine(xmin,0.0,xmax,0.0);
 
 // c2->cd(2); line->SetLineColor(kRed); line->SetLineWidth(2); gPad->SetLeftMargin(0.15); z1frame->GetYaxis()->SetTitleOffset(1.6); z1frame->GetYaxis()->SetRangeUser(-50.0, 50.0); z1frame->Draw(); line->Draw("SAME");
  //  c2->cd(1); gPad->SetLeftMargin(0.15); z2frame->GetYaxis()->SetTitleOffset(1.6); z2frame->Draw(); line->Draw("SAME");
  c2->cd(); gPad->SetLeftMargin(0.15); frame->GetYaxis()->SetTitleOffset(1.6); frame->Draw();
  
 pdf.plotOn(frame,Components(RooArgList(gtop)), LineColor(kRed),LineStyle(2), LineWidth(4));
 pdf.plotOn(frame,Components(RooArgList(gtop2)), LineColor(kRed+2),LineStyle(2), LineWidth(4));
 pdf.plotOn(frame,Components(RooArgList(cheb)), LineColor(kBlue),LineStyle(2), LineWidth(4));
 //pdf.plotOn(frame,Components(RooArgList(bgtop)), LineColor(kGreen),LineStyle(2), LineWidth(4));
  
  
 frame->Draw();

//promptHisto->Draw("E1");



TCanvas *c_h=new TCanvas("C_histos","C_histos");
c_h->cd();
//promptHisto->GetXaxis()->SetRangeUser(0,0.025);
//PromptHisto->Draw("E1");


std::cout<<"Chi Square ="<<frame->chiSquare()<<std::endl;



















}
