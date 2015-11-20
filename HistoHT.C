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
void HistosHT(){
 //barrel
 // double rangeMax=0.01;
 // double rangeMin=0.005;

   //endcap
   double rangeMax=0.05;
   double rangeMin=0.01;



   int nBins=120;

   
   TFile *f=new TFile("HistosHTEndcap.root","RECREATE");

   TH1F *hpromptSR=new TH1F("hpromptSR","hpromptSR",nBins,rangeMin,rangeMax);
   hpromptSR->SetLineWidth(1);

   TH1F *hnonpromptSR=new TH1F("hnonpromptSR","hnonpromptSR",nBins,rangeMin,rangeMax);
   hnonpromptSR->SetLineWidth(1);

   TH1F *hnonpromptSB=new TH1F("hnonpromptSB","hnonpromptSB",nBins,rangeMin,rangeMax);
   hnonpromptSB->SetLineWidth(1);

   TH1F *hSRData=new TH1F("hSRData","hSRData",nBins,rangeMin,rangeMax);
   hSRData->SetLineWidth(1);



   TH1F *hpromptSRHTlow=new TH1F("hpromptSRHTlow","hpromptSRHTlow",nBins,rangeMin,rangeMax);
   

   TH1F *hnonpromptSRHTlow=new TH1F("hnonpromptSRHTlow","hnonpromptSRHTlow",nBins,rangeMin,rangeMax);
   

   TH1F *hnonpromptSBHTlow=new TH1F("hnonpromptSBHTlow","hnonpromptSBHTlow",nBins,rangeMin,rangeMax);
   

   TH1F *hSRDataHTlow=new TH1F("hSRDataHTlow","hSRDataHTlow",nBins,rangeMin,rangeMax);
   



   TH1F *hpromptSRHTmed=new TH1F("hpromptSRHTmed","hpromptSRHTmed",nBins,rangeMin,rangeMax);
   

   TH1F *hnonpromptSRHTmed=new TH1F("hnonpromptSRHTmed","hnonpromptSRHTmed",nBins,rangeMin,rangeMax);
   

   TH1F *hnonpromptSBHTmed=new TH1F("hnonpromptSBHTmed","hnonpromptSBHTmed",nBins,rangeMin,rangeMax);
   

   TH1F *hSRDataHTmed=new TH1F("hSRDataHTmed","hSRDataHTmed",nBins,rangeMin,rangeMax);



   TH1F *hpromptSRHThigh=new TH1F("hpromptSRHThigh","hpromptSRHThigh",nBins,rangeMin,rangeMax);
   

   TH1F *hnonpromptSRHThigh=new TH1F("hnonpromptSRHThigh","hnonpromptSRHThigh",nBins,rangeMin,rangeMax);
   

   TH1F *hnonpromptSBHThigh=new TH1F("hnonpromptSBHThigh","hnonpromptSBHThigh",nBins,rangeMin,rangeMax);
   

   TH1F *hSRDataHThigh=new TH1F("hSRDataHThigh","hSRDataHThigh",nBins,rangeMin,rangeMax);






   

    TChain* t1 = new TChain("SimpleTree");
    t1->Add("GJetsFullHT.root");//GJets100HTInf.root");//SignalGJets3.root");
    ReadTree read1(t1);


    TChain* t2 = new TChain("SimpleTree");
    t2->Add("QCDFullHT.root");//QCD100HTInf.root");//QCD80toInf.root");
    ReadTree read2(t2);


    TChain* t3 = new TChain("SimpleTree");
    t3->Add("SinglePhoton1p3ifb.root");//DataSinglePhotonCD.root");//Single Photon Data
    ReadTree read3(t3);



    int maxEvents1=t1->GetEntries();
    cout<<"maxEventsGJets: "<<maxEvents1<<endl;
    for(int i1=0;i1<maxEvents1;i1++){//GJets loop
    t1->GetEntry(i1);

    cout<<"Weight: "<<read1.evWeight<<endl;
    if(i1 % 1000000==0){cout<<"Event no GJets : "<<i1<<endl;}

   if(read1.isEndcap==1 && read1.nonPrompt !=1 && read1.BaseLine()==true && read1.evWeight<3. && read1.IchSR==1 && read1.BJets==0){//prompt 
 
   
   hpromptSR->Fill(read1.SigmaIetaIeta,read1.evWeight);
   if(read1.HTlow()==true){hpromptSRHTlow->Fill(read1.SigmaIetaIeta,read1.evWeight);}   
   if(read1.HTmed()==true){hpromptSRHTmed->Fill(read1.SigmaIetaIeta,read1.evWeight);} 
   if(read1.HThigh()==true){hpromptSRHThigh->Fill(read1.SigmaIetaIeta,read1.evWeight);} 



   }//prompt


   }//GJets loop





   int maxEvents2=t2->GetEntries();
    cout<<"maxEventsQCD: "<<maxEvents2<<endl;
    for(int i2=0;i2<maxEvents2;i2++){//QCD loop
    t2->GetEntry(i2);
    if(i2 % 1000000==0){cout<<"Event no QCD : "<<i2<<endl;}

    if(read2.nonPrompt ==1 && read2.BaseLine()==true  && read2.isEndcap==1 && read2.BJets==0){//non prompt 
   
   if(read2.IchSR==1  ){//2
   hnonpromptSR->Fill(read2.SigmaIetaIeta,read2.evWeight);
   if(read2.HTlow()==true){hnonpromptSRHTlow->Fill(read2.SigmaIetaIeta,read2.evWeight);}   
   if(read2.HTmed()==true){hnonpromptSRHTmed->Fill(read2.SigmaIetaIeta,read2.evWeight);} 
   if(read2.HThigh()==true){hnonpromptSRHThigh->Fill(read2.SigmaIetaIeta,read2.evWeight);} 

   
   


      }//2
       
       

   if(read2.IchSB==1 ){//3
   hnonpromptSB->Fill(read2.SigmaIetaIeta,read2.evWeight);
   if(read2.HTlow()==true){hnonpromptSBHTlow->Fill(read2.SigmaIetaIeta,read2.evWeight);}   
   if(read2.HTmed()==true){hnonpromptSBHTmed->Fill(read2.SigmaIetaIeta,read2.evWeight);} 
   if(read2.HThigh()==true){hnonpromptSBHThigh->Fill(read2.SigmaIetaIeta,read2.evWeight);} 
   


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


   if( PassTrigger==true && read3.isEndcap==1 && read3.BaseLine()==true  && read3.IchSR==1 && read3.BJets==0){//photon SR


     




    

   
    hSRData->Fill(read3.SigmaIetaIeta); 
    if(read3.HTlow()==true){hSRDataHTlow->Fill(read3.SigmaIetaIeta);}   
    if(read3.HTmed()==true){hSRDataHTmed->Fill(read3.SigmaIetaIeta);} 
    if(read3.HThigh()==true){hSRDataHThigh->Fill(read3.SigmaIetaIeta);} 

 
      



    }//Photon SR

   }//Data

   



 f->Write();







}
