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
void FitDataEB_MHT1(){


   double rangeMax=0.02;
   double rangeMin=0.005;
   int nBins=40;

   TH1F *hpromptSRreal=new TH1F("hpromptSRreal","hpromptSRreal",nBins,rangeMin,rangeMax);
   hpromptSRreal->SetLineWidth(1);

   TH1F *htotalSRreal=new TH1F("htotalSRreal","htotalSRreal",nBins,rangeMin,rangeMax);
   htotalSRreal->SetLineWidth(1);
   

   TH1F *hpromptSR=new TH1F("hpromptSR","hpromptSR",nBins,rangeMin,rangeMax);
   hpromptSR->SetLineWidth(1);

   

   TH1F *hnonpromptSR=new TH1F("hnonpromptSR","hnonpromptSR",nBins,rangeMin,rangeMax);
   hnonpromptSR->SetLineWidth(1);

   TH1F *hnonpromptSB=new TH1F("hnonpromptSB","hnonpromptSB",nBins,rangeMin,rangeMax);
   hnonpromptSB->SetLineWidth(1);

   TH1F *htotalSR=new TH1F("htotalSR","htotalSR",nBins,rangeMin,rangeMax);
   htotalSR->SetLineWidth(1);
   



   TChain* t1 = new TChain("SimpleTree");
    t1->Add("GJetsFullHT.root");//GJets100HTInf.root");//SignalGJets3.root");
    ReadTree read1(t1);


    TChain* t2 = new TChain("SimpleTree");
    t2->Add("QCDFullHT.root");//QCD100HTInf.root");//QCD80toInf.root");
    ReadTree read2(t2);


   TChain* t3 = new TChain("SimpleTree");
    t3->Add("SinglePhoton1p3ifb.root");//DataSinglePhotonCD.root");//Single Photon Data
    ReadTreeData read3(t3);
   




   int maxEvents1=t1->GetEntries();
    cout<<"maxEventsGJets: "<<maxEvents1<<endl;
    for(int i1=0;i1<maxEvents1;i1++){//GJets loop
    t1->GetEntry(i1);
    if(i1 % 1000000==0){cout<<"Event no GJets : "<<i1<<endl;}

   if(read1.isBarrel==1 && read1.nonPrompt !=1 && read1.MHTlow()==true && read1.evWeight<3. && read1.IchSR==1 ){//prompt 
 
   
   hpromptSR->Fill(read1.SigmaIetaIeta,read1.evWeight);
   if(read1.SigmaIetaIeta < 0.02){
    //htotalSR->Fill(read1.SigmaIetaIeta,read1.evWeight);  
       }

   if(read1.SigmaIetaIeta < 0.0107){
      hpromptSRreal->Fill(read1.SigmaIetaIeta,read1.evWeight);
      htotalSRreal->Fill(read1.SigmaIetaIeta,read1.evWeight);

       }



   }//prompt


   }//GJets loop





   int maxEvents2=t2->GetEntries();
    cout<<"maxEventsQCD: "<<maxEvents2<<endl;
    for(int i2=0;i2<maxEvents2;i2++){//QCD loop
    t2->GetEntry(i2);
    if(i2 % 1000000==0){cout<<"Event no QCD : "<<i2<<endl;}

    if(read2.nonPrompt ==1 && read2.MHTlow()==true  && read2.isBarrel==1 ){//non prompt 
   
   if(read2.IchSR==1 &&  read2.SigmaIetaIeta < 0.02 ){//2
   hnonpromptSR->Fill(read2.SigmaIetaIeta,read2.evWeight);
   
   
   //htotalSR->Fill(read2.SigmaIetaIeta,read2.evWeight);///
   if(read2.SigmaIetaIeta < 0.0107){//1
      
      htotalSRreal->Fill(read2.SigmaIetaIeta,read2.evWeight);

       }//1


      }//2
       
       

   if(read2.IchSB==1 && read2.SigmaIetaIeta < 0.02){//3
   hnonpromptSB->Fill(read2.SigmaIetaIeta,read2.evWeight);
   
       }//3
    
   


   }//non prompt





   }//QCD loop



   ///Data

   int maxEvents3=t3->GetEntries();
    cout<<"maxEvents in Single Photon Data: "<<maxEvents3<<endl;
    for(int i3=0;i3<maxEvents3;i3++){//Data
    t3->GetEntry(i3);
    if(i3 % 1000000==0){cout<<"Event no Data : "<<i3<<endl;}

      bool PassTrigger=false;
          
         for(int itr=0;itr<read3.TriggerNames->size();itr++){
             //cout<<"trigger size: "<<Data.TriggerNames->at(itr)<<endl;
             if(read3.TriggerNames->at(itr)=="HLT_Photon90_CaloIdL_PFHT500_v3" && read3.TriggerPass->at(itr)==1){
                PassTrigger=true;


               }

              }


   if( PassTrigger==true && read3.isBarrel==1 && read3.MHTlow()==true  && read3.IchSR==1 && read3.BJets==0){//photon SR


     




    

   if(read3.SigmaIetaIeta < 0.02){
    htotalSR->Fill(read3.SigmaIetaIeta);  
       }



    }//Photon SR

   }//Data

   



   TCanvas *cdata=new TCanvas("cdata","cdata");
   cdata->cd();
   htotalSR->Draw();







  //hnonpromptSR->Draw();
   
  


  TCanvas *cRoo=new TCanvas("cRoo","cRoo",850,850);
  cRoo->Divide(2,2);

  RooRealVar SIeta("SIeta","#sigma_{i#etai#eta}",rangeMin,rangeMax);

  RooDataHist dataSR("dataSR","dataSR",SIeta,Import(*htotalSR));

 

  RooDataHist pdfdata1("pdfdata1","pdfdata1",SIeta,Import(*hpromptSR));
  RooDataHist pdfdata2("pdfdata2","pdfdata2",SIeta,Import(*hnonpromptSB));


  RooHistPdf histpdf1("histpdf1","histpdf1",SIeta,pdfdata1,0);
  RooHistPdf histpdf2("histpdf2","histpdf2",SIeta,pdfdata2,0);


  RooRealVar Fitfrac("Fitfrac","Fitfrac",0.7,0.,1.5);

  RooAddPdf pdf("pdf","PSR-NPSB-PDF", RooArgList(histpdf1,histpdf2),Fitfrac);


  RooPlot* frame1 = SIeta.frame(Title("pdf from SR,Prompt(MC)"));
  pdfdata1.plotOn(frame1);
  histpdf1.plotOn(frame1);
  cRoo->cd(1);
  frame1->Draw(); 

  RooPlot* frame2 = SIeta.frame(Title("pdf from SB,nonPrompt(MC)"));
  pdfdata2.plotOn(frame2);
  histpdf2.plotOn(frame2);
  cRoo->cd(2);
  frame2->Draw();


  RooPlot* frame3 = SIeta.frame(Title("pdf from SR-Prompt+SB-nonPrompt(MC)"));
  
  cRoo->cd(3);
  pdf.plotOn(frame3,Components(RooArgList(histpdf1)), LineColor(kRed),LineStyle(2), LineWidth(3));
  pdf.plotOn(frame3,Components(RooArgList(histpdf2)), LineColor(kGreen),LineStyle(2), LineWidth(3));
  pdf.plotOn(frame3,Components(RooArgList(pdf)), LineColor(kBlue),LineStyle(1), LineWidth(2));
  frame3->Draw();

  TPaveText *tpav_txt = new TPaveText(0.43043478,0.6548342,0.7652174,0.8510471,"brNDC");

  tpav_txt->SetBorderSize(0);
  tpav_txt->SetFillStyle(0);
  tpav_txt->SetTextAlign(11);
  tpav_txt->SetTextFont(42);
  tpav_txt->SetTextSize(0.03);
  double RealFrac=hpromptSRreal->Integral()/htotalSRreal->Integral();
  int Percent = (int)round(1000*hpromptSRreal->Integral()/htotalSRreal->Integral());

  char Rfrac[100];
  sprintf(Rfrac,"Purity(MC, EB): 0.%i ",Percent); 
  tpav_txt->AddText(Rfrac);

  cRoo->cd(4);
  gPad->cd();
  gPad->SetLogy();
  RooPlot* frame4 = SIeta.frame(Title("CMS #it{Preliminary}                        1.3 fb^{-1}, 13 TeV"));

  dataSR.plotOn(frame4,Name("dataSR1"));  
  pdf.fitTo(dataSR);
  pdf.plotOn(frame4);
  //pdf.paramOn(frame4);

  
  pdf.plotOn(frame4,Name("histpdf1"),Components(RooArgList(histpdf1)), LineColor(kRed),LineStyle(2), LineWidth(2));
  pdf.plotOn(frame4,Name("histpdf2"),Components(RooArgList(histpdf2)), LineColor(kGreen),LineStyle(2), LineWidth(3));
  pdf.plotOn(frame4,Name("pdf"),Components(RooArgList(pdf)), LineColor(kBlue),LineStyle(1), LineWidth(2));
  


  TLegend *leg=new TLegend(00.5402358,0.4731495,0.7441038,0.6734398,NULL,"brNDC");
  leg->SetTextFont(62);
  leg->SetLineColor(1);
  leg->SetLineStyle(1);
  leg->SetLineWidth(3);
  leg->SetFillColor(0);
  leg->SetFillStyle(1001);
  leg->SetShadowColor(0);
  leg->SetDrawOption(0);
  leg->SetBorderSize(0);
  leg->SetTextSize(0.02);

  
  leg->AddEntry(frame4->findObject("histpdf1"),"Prompt PDF(from MC),EB","l");
  leg->AddEntry(frame4->findObject("histpdf2"),"NonPrompt PDF(from MC),EB","l");
  leg->AddEntry(frame4->findObject("pdf"),"P+NP PDF(from MC),EB","l");
  leg->AddEntry(frame4->findObject("dataSR1"),"Data,EB","P");

  
  
  


  SIeta.setRange("SR",0.005,0.0107);
  RooAbsReal* fracP = histpdf1.createIntegral(SIeta,NormSet(SIeta),Range("SR"));
  RooAbsReal* Ip=histpdf1.createIntegral(SIeta);
  RooAbsReal* fracNP = histpdf2.createIntegral(SIeta,NormSet(SIeta),Range("SR"));
  RooAbsReal* Inp=histpdf2.createIntegral(SIeta);

  double f=Fitfrac.getVal();
  double fError=Fitfrac.getError();
  double dataAreaFull=htotalSR->Integral();
  double promptIntFull=f*dataAreaFull;
  double nonpromptIntFull=(1-f)*dataAreaFull;

  double fracP_val=fracP->getVal();
  
  double fracNP_val=fracNP->getVal();
  
  double promptIntS=fracP_val*f;
  double nonpromptIntS=fracNP_val*(1-f);
  double PurityFromFit=promptIntS/(promptIntS+nonpromptIntS);
  
  float SigmaErr=(fError/f)*PurityFromFit;

  cout<<"Beta error: "<<SigmaErr<<endl;

  cout<<"fracP:  "<<fracP_val<<endl;
  cout<<"fracNP:  "<<fracNP_val<<endl;
  cout<<"Purity From Fit: "<<PurityFromFit<<endl;

  int PercentFit = (int)(1000*PurityFromFit);
  int PercentFitErr = (int)round(1000*SigmaErr);


  char RfracFit[100];
  sprintf(RfracFit,"P(Fit to EB Data): 0.%i +- %4.3f ",PercentFit,SigmaErr); 
  tpav_txt->AddText(RfracFit);

  

  
  frame4->Draw();
  tpav_txt->Draw();
    float chosenEff = 0.0107;
    TLine *line =new TLine(chosenEff,0,chosenEff,100);
    line->SetLineColor(kOrange+8);
    line->SetLineWidth(2);
    line->Draw();
   


  cout<<"real fraction: "<<hpromptSRreal->Integral()/htotalSRreal->Integral()<<endl;

  std::cout<<"Chisquare/ndof ="<<frame4->chiSquare()<<std::endl;


  //cRoo->SaveAs("dPhiFitresultSinglePhotonEB.png");
  //cRoo->SaveAs("dPhiFitresultSinglePhotonEB.gif");
  //cRoo->SaveAs("dPhiFitresultSinglePhotonEB.pdf");






  TCanvas *cFit=new TCanvas("cFit","cFit",850,850);
   
   cFit->cd();
   gPad->Update();
   gPad->SetLogy();
   cFit->Range(0.01,0.01,0.02,1000);
   //gPad->SetLogy();
   frame4->Draw();
   tpav_txt->Draw();
   line->Draw();
   leg->Draw();
   //cFit->SaveAs("OnlyFitEB.png");
   cFit->SaveAs("OnlyFitEBMHTlow.pdf");
   cFit->SaveAs("OnlyFitEBMHTlow.gif");
  

}
