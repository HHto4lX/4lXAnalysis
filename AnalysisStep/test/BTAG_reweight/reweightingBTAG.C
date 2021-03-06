// ******************************************
// use: root -l -b -q reweightingBTAG.C++
// ******************************************

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <math.h>
#include "TCanvas.h"
#include "TColor.h"
#include "TFile.h"
#include "TFrame.h"
#include "TF1.h"
#include "TGraph.h"
#include "TGraphErrors.h"
#include "TGraphAsymmErrors.h"
#include "TH1.h"
#include "TH2.h"
#include "TLegend.h"
#include "TLegendEntry.h"
#include "TLine.h"
#include "TMath.h"
#include "TPaletteAxis.h"
#include "TROOT.h"
#include "TSpline.h"
#include "TStyle.h"
#include "TSystem.h"
#include "TTree.h"
#include <vector>
#include "TLorentzVector.h"

// includes for btag SF
#include "BTagCalibrationStandalone.h"
#include "BTagCalibrationStandalone.cpp"
#include "evalEventSF.C"


using namespace std;


//TString syear = "2016";
//TString syear = "2017";
TString syear = "2018";




void reweightingBTAG(){

  ///////////// SET UP B-TAG CALIBRATION ///////////////
    
  // set up calibration + reader
  cout << "Loading the .csv file..." << endl;
    
  std::string inputCSVfile = "";
  if(syear=="2016")      { inputCSVfile = "../../data/BTagging/DeepCSV_2016LegacySF_V1.csv";} //2016
  else if(syear=="2017") { inputCSVfile = "../../data/BTagging/DeepCSV_94XSF_V5_B_F.csv";}    //2017
  else if(syear=="2018") { inputCSVfile = "../../data/BTagging/DeepCSV_102XSF_V1.csv";}       //2018
  std::string measType            = "iterativefit";
  std::string sysType             = "central";
  std::string sysTypeJESUp        = "up_jes";
  std::string sysTypeJESDown      = "down_jes";
  std::string sysTypeHFUp         = "up_hf";
  std::string sysTypeHFDown       = "down_hf";
  std::string sysTypeLFUp         = "up_lf";
  std::string sysTypeLFDown       = "down_lf";
  std::string sysTypehfstats1Up   = "up_hfstats1";
  std::string sysTypehfstats1Down = "down_hfstats1";
  std::string sysTypehfstats2Up   = "up_hfstats2";
  std::string sysTypehfstats2Down = "down_hfstats2";
  std::string sysTypelfstats1Up   = "up_lfstats1";
  std::string sysTypelfstats1Down = "down_lfstats1";
  std::string sysTypelfstats2Up   = "up_lfstats2";
  std::string sysTypelfstats2Down = "down_lfstats2";
  std::string sysTypecfErr1Up     = "up_cferr1";
  std::string sysTypecfErr1Down   = "down_cferr1";
  std::string sysTypecfErr2Up     = "up_cferr2";
  std::string sysTypecfErr2Down   = "down_cferr2";
    
  BTagCalibration calib("csvv2", inputCSVfile);
  //nominal
  BTagCalibrationReader CSVreader(BTagEntry::OP_RESHAPING, sysType);       
  CSVreader.load(calib, BTagEntry::FLAV_B, measType);
  CSVreader.load(calib, BTagEntry::FLAV_C, measType);
  CSVreader.load(calib, BTagEntry::FLAV_UDSG, measType);
  //up_jes shift
  BTagCalibrationReader CSVreaderJESUp(BTagEntry::OP_RESHAPING, sysTypeJESUp);       
  CSVreaderJESUp.load(calib, BTagEntry::FLAV_B, measType);
  CSVreaderJESUp.load(calib, BTagEntry::FLAV_C, measType);
  CSVreaderJESUp.load(calib, BTagEntry::FLAV_UDSG, measType);
  //down_jes shift
  BTagCalibrationReader CSVreaderJESDown(BTagEntry::OP_RESHAPING, sysTypeJESDown);       
  CSVreaderJESDown.load(calib, BTagEntry::FLAV_B, measType);
  CSVreaderJESDown.load(calib, BTagEntry::FLAV_C, measType);
  CSVreaderJESDown.load(calib, BTagEntry::FLAV_UDSG, measType);
  //up_hf shift
  BTagCalibrationReader CSVreaderHFUp(BTagEntry::OP_RESHAPING, sysTypeHFUp);       
  CSVreaderHFUp.load(calib, BTagEntry::FLAV_B, measType);
  CSVreaderHFUp.load(calib, BTagEntry::FLAV_C, measType);
  CSVreaderHFUp.load(calib, BTagEntry::FLAV_UDSG, measType);
  //down_hf shift
  BTagCalibrationReader CSVreaderHFDown(BTagEntry::OP_RESHAPING, sysTypeHFDown);       
  CSVreaderHFDown.load(calib, BTagEntry::FLAV_B, measType);
  CSVreaderHFDown.load(calib, BTagEntry::FLAV_C, measType);
  CSVreaderHFDown.load(calib, BTagEntry::FLAV_UDSG, measType);
  //up_lf shift
  BTagCalibrationReader CSVreaderLFUp(BTagEntry::OP_RESHAPING, sysTypeLFUp);       
  CSVreaderLFUp.load(calib, BTagEntry::FLAV_B, measType);
  CSVreaderLFUp.load(calib, BTagEntry::FLAV_C, measType);
  CSVreaderLFUp.load(calib, BTagEntry::FLAV_UDSG, measType);
  //down_lf shift
  BTagCalibrationReader CSVreaderLFDown(BTagEntry::OP_RESHAPING, sysTypeLFDown);       
  CSVreaderLFDown.load(calib, BTagEntry::FLAV_B, measType);
  CSVreaderLFDown.load(calib, BTagEntry::FLAV_C, measType);
  CSVreaderLFDown.load(calib, BTagEntry::FLAV_UDSG, measType);
  //up_hfstats1 shift
  BTagCalibrationReader CSVreaderhfstats1Up(BTagEntry::OP_RESHAPING, sysTypehfstats1Up);       
  CSVreaderhfstats1Up.load(calib, BTagEntry::FLAV_B, measType);
  CSVreaderhfstats1Up.load(calib, BTagEntry::FLAV_C, measType);
  CSVreaderhfstats1Up.load(calib, BTagEntry::FLAV_UDSG, measType);
  //down_hfstats1 shift
  BTagCalibrationReader CSVreaderhfstats1Down(BTagEntry::OP_RESHAPING, sysTypehfstats1Down);       
  CSVreaderhfstats1Down.load(calib, BTagEntry::FLAV_B, measType);
  CSVreaderhfstats1Down.load(calib, BTagEntry::FLAV_C, measType);
  CSVreaderhfstats1Down.load(calib, BTagEntry::FLAV_UDSG, measType);
  //up_lfstats2 shift
  BTagCalibrationReader CSVreaderhfstats2Up(BTagEntry::OP_RESHAPING, sysTypehfstats2Up);       
  CSVreaderhfstats2Up.load(calib, BTagEntry::FLAV_B, measType);
  CSVreaderhfstats2Up.load(calib, BTagEntry::FLAV_C, measType);
  CSVreaderhfstats2Up.load(calib, BTagEntry::FLAV_UDSG, measType);
  //down_lfstats2 shift
  BTagCalibrationReader CSVreaderhfstats2Down(BTagEntry::OP_RESHAPING, sysTypehfstats2Down);       
  CSVreaderhfstats2Down.load(calib, BTagEntry::FLAV_B, measType);
  CSVreaderhfstats2Down.load(calib, BTagEntry::FLAV_C, measType);
  CSVreaderhfstats2Down.load(calib, BTagEntry::FLAV_UDSG, measType);
  //up_lfstats1 shift
  BTagCalibrationReader CSVreaderlfstats1Up(BTagEntry::OP_RESHAPING, sysTypelfstats1Up);       
  CSVreaderlfstats1Up.load(calib, BTagEntry::FLAV_B, measType);
  CSVreaderlfstats1Up.load(calib, BTagEntry::FLAV_C, measType);
  CSVreaderlfstats1Up.load(calib, BTagEntry::FLAV_UDSG, measType);
  //down_lfstats1 shift
  BTagCalibrationReader CSVreaderlfstats1Down(BTagEntry::OP_RESHAPING, sysTypelfstats1Down);       
  CSVreaderlfstats1Down.load(calib, BTagEntry::FLAV_B, measType);
  CSVreaderlfstats1Down.load(calib, BTagEntry::FLAV_C, measType);
  CSVreaderlfstats1Down.load(calib, BTagEntry::FLAV_UDSG, measType);
  //up_lfstats2 shift
  BTagCalibrationReader CSVreaderlfstats2Up(BTagEntry::OP_RESHAPING, sysTypelfstats2Up);       
  CSVreaderlfstats2Up.load(calib, BTagEntry::FLAV_B, measType);
  CSVreaderlfstats2Up.load(calib, BTagEntry::FLAV_C, measType);
  CSVreaderlfstats2Up.load(calib, BTagEntry::FLAV_UDSG, measType);
  //down_lfstats2 shift
  BTagCalibrationReader CSVreaderlfstats2Down(BTagEntry::OP_RESHAPING, sysTypelfstats2Down);       
  CSVreaderlfstats2Down.load(calib, BTagEntry::FLAV_B, measType);
  CSVreaderlfstats2Down.load(calib, BTagEntry::FLAV_C, measType);
  CSVreaderlfstats2Down.load(calib, BTagEntry::FLAV_UDSG, measType);
  //up_cferr1 shift
  BTagCalibrationReader CSVreadercfErr1Up(BTagEntry::OP_RESHAPING, sysTypecfErr1Up);       
  CSVreadercfErr1Up.load(calib, BTagEntry::FLAV_B, measType);
  CSVreadercfErr1Up.load(calib, BTagEntry::FLAV_C, measType);
  CSVreadercfErr1Up.load(calib, BTagEntry::FLAV_UDSG, measType);
  //down_cferr1 shift
  BTagCalibrationReader CSVreadercfErr1Down(BTagEntry::OP_RESHAPING, sysTypecfErr1Down);       
  CSVreadercfErr1Down.load(calib, BTagEntry::FLAV_B, measType);
  CSVreadercfErr1Down.load(calib, BTagEntry::FLAV_C, measType);
  CSVreadercfErr1Down.load(calib, BTagEntry::FLAV_UDSG, measType);
  //up_cferr2 shift
  BTagCalibrationReader CSVreadercfErr2Up(BTagEntry::OP_RESHAPING, sysTypecfErr2Up);       
  CSVreadercfErr2Up.load(calib, BTagEntry::FLAV_B, measType);
  CSVreadercfErr2Up.load(calib, BTagEntry::FLAV_C, measType);
  CSVreadercfErr2Up.load(calib, BTagEntry::FLAV_UDSG, measType);
  //down_cferr2 shift
  BTagCalibrationReader CSVreadercfErr2Down(BTagEntry::OP_RESHAPING, sysTypecfErr2Down);       
  CSVreadercfErr2Down.load(calib, BTagEntry::FLAV_B, measType);
  CSVreadercfErr2Down.load(calib, BTagEntry::FLAV_C, measType);
  CSVreadercfErr2Down.load(calib, BTagEntry::FLAV_UDSG, measType);
    
    
    
  cout << "Input CSV weight file = " << inputCSVfile << "; measurementType = " << measType << ";" << endl;




  // variables for tree 
  float lumi;
  if(syear=="2016") {lumi = 35.8;} //2016
  else if(syear=="2017") {lumi = 41.5;} //2017
  else if(syear=="2017") {lumi = 59.7;} //2017

  TFile* inputFile;
  TTree* inputTree;
  TH1F* hCounters;
  int NGenEvt;
  Float_t gen_sumWeights;
  Float_t partialSampleWeight;

  Float_t genBR;
  Int_t nRun;
  Long64_t nEvent;
  Int_t nLumi;
  Float_t overallEventWeight;
  //  Float_t xsec = 0.0000447896; //pb
  Float_t xsec; 

  Short_t ZZsel;
  vector<Float_t> *LepPt = 0;
  vector<Float_t> *LepEta = 0;
  Float_t ZZMass;

  vector<Float_t> *JetPt     = 0;
  vector<Float_t> *JetEta    = 0;
  vector<Float_t> *JetPhi    = 0;
  vector<Float_t> *JetMass   = 0;
  vector<Float_t> *JetBTagger = 0;
  vector<Float_t> *JetHadronFlavour = 0;

  float deepCSV_jet1;
  float deepCSV_jet2;


  TH1F* h_BtagSF = new TH1F("h_BtagSF",";BtagSF;events", 10, 0.,2.);
  TH1F* h_BtagSF_norm = new TH1F("h_BtagSF_norm",";BtagSF normalized;events", 10, 0.,2.);
  TH1F* h_Btagger_jet1_preSF  = new TH1F("h_Btagger_jet1_preSF" ,";deepCSV jet1;events", 10, 0., 1.);
  TH1F* h_Btagger_jet1_postSF = new TH1F("h_Btagger_jet1_postSF",";deepCSV jet1;events", 10, 0., 1.);
  TH1F* h_Btagger_jet2_preSF  = new TH1F("h_Btagger_jet2_preSF" ,";deepCSV jet2;events", 10, 0., 1.);
  TH1F* h_Btagger_jet2_postSF = new TH1F("h_Btagger_jet2_postSF",";deepCSV jet2;events", 10, 0., 1.);

  // arrays for BTagSF norm
  float sum_events = 0.;            
  float sum_BTagSF = 0.; 

  TString inFile;
  //  TString inFile = "/eos/user/a/acappati/samples_4lX/allsamples/HH4lbb/ZZXAnalysis.root";
  if(syear=="2016")      inFile = "/eos/user/a/acappati/samples_HH4lbb/samples_2016/HH4lbb_Ilirjan/ZZXAnalysis.root";
  else if(syear=="2017") inFile = "/eos/user/a/acappati/samples_HH4lbb/samples_2017/HH4lbb_Angela/ZZXAnalysis.root";
  else if(syear=="2018") inFile = "/eos/user/a/acappati/samples_HH4lbb/samples_2018/HH4lbb_Angela/ZZXAnalysis.root";
  inputFile =  TFile::Open( inFile );


  hCounters = (TH1F*)inputFile->Get("ZZTree/Counters");
  NGenEvt = (Float_t)hCounters->GetBinContent(1);
  gen_sumWeights = (Float_t)hCounters->GetBinContent(40);
  partialSampleWeight = lumi * 1000 / gen_sumWeights;
  inputTree = (TTree*)inputFile->Get("ZZTree/candTree");


  inputTree->SetBranchAddress("RunNumber", &nRun);
  inputTree->SetBranchAddress("EventNumber", &nEvent);
  inputTree->SetBranchAddress("LumiNumber", &nLumi);
  inputTree->SetBranchAddress("overallEventWeight", &overallEventWeight);
  inputTree->SetBranchAddress("xsec", &xsec);
  //  xsec = 0.00001017; //pb Angela

  inputTree->SetBranchAddress("ZZsel", &ZZsel);
  inputTree->SetBranchAddress("LepPt", &LepPt);
  inputTree->SetBranchAddress("LepEta", &LepEta);
  inputTree->SetBranchAddress("ZZMass", &ZZMass); 
  
  inputTree->SetBranchAddress("JetPt", &JetPt);
  inputTree->SetBranchAddress("JetEta", &JetEta);
  inputTree->SetBranchAddress("JetMass", &JetMass);
  inputTree->SetBranchAddress("JetPhi",  &JetPhi);
  inputTree->SetBranchAddress("JetBTagger",  &JetBTagger);
  inputTree->SetBranchAddress("JetHadronFlavour",  &JetHadronFlavour);


  // --------------------------------------------------------------
  //first loop for normalization
  // --- first loop over input tree to get norm for BtagSF
  Long64_t entries1 = inputTree->GetEntries();
  std::cout<<"Processing file: "<< inFile << "\nNumber of entries: " << entries1 << endl;
  for (Long64_t entry = 0; entry < entries1; entry++)
  {  

    inputTree->GetEntry(entry);

    // trigger check
    if( !(ZZsel >= 0) ) continue;


    // check if only 4 lepton
    if(LepEta->size() != 4){
	cerr << "error in event " << nRun << ":" << nLumi << ":" << nEvent << "; stored leptons: "<< LepEta->size() << endl;
	continue;
    }

    // compute SF
    double * scaleFactors;
    scaleFactors = evalEventSF( int(JetPt->size()), JetHadronFlavour, JetEta, JetPt, JetBTagger, CSVreader, CSVreaderJESUp, CSVreaderJESDown, CSVreaderHFUp, CSVreaderHFDown, CSVreaderLFUp, CSVreaderLFDown, CSVreaderhfstats1Up, CSVreaderhfstats1Down, CSVreaderhfstats2Up, CSVreaderhfstats2Down, CSVreaderlfstats1Up, CSVreaderlfstats1Down, CSVreaderlfstats2Up, CSVreaderlfstats2Down, CSVreadercfErr1Up, CSVreadercfErr1Down, CSVreadercfErr2Up, CSVreadercfErr2Down );

    // total counters for BTagSF norm 
    sum_events += 1.; 
    sum_BTagSF += scaleFactors[0]; 


  }//end first loop over entries

  cout<<inFile<<" "<<sum_events<<" "<<sum_BTagSF<<endl;

  // --- control for norm
  if( sum_events == 0. || std::isnan(sum_events) ){ sum_events = 1.; }
  if( sum_BTagSF == 0. || std::isnan(sum_BTagSF) ){ sum_BTagSF = 1.; }

  cout<<inFile<<" "<<sum_events<<" "<<sum_BTagSF<<endl;
  // ----------------------------------------------------------------------



  // ----------------------------------------------------------------------
  // second loop 
  Long64_t entries2 = inputTree->GetEntries();
  std::cout<<"Processing file: "<< inFile << "\nNumber of entries: " << entries2 << endl;
  for (Long64_t entry = 0; entry < entries2; entry++)
  {  

    inputTree->GetEntry(entry);

    // trigger check
    if( !(ZZsel >= 0) ) continue;


    // check if only 4 lepton
    if(LepEta->size() != 4){
	cerr << "error in event " << nRun << ":" << nLumi << ":" << nEvent << "; stored leptons: "<< LepEta->size() << endl;
	continue;
    }


    // mass cut: signal region
    if(ZZMass < 115 || ZZMass > 135) continue; // 115 < ZZMass < 135 GeV


 

    // at least 2 jets in the acceptance
    if (JetPt->size() < 2) continue;


    // compute SF
    double * scaleFactors;
    scaleFactors = evalEventSF( int(JetPt->size()), JetHadronFlavour, JetEta, JetPt, JetBTagger, CSVreader, CSVreaderJESUp, CSVreaderJESDown, CSVreaderHFUp, CSVreaderHFDown, CSVreaderLFUp, CSVreaderLFDown, CSVreaderhfstats1Up, CSVreaderhfstats1Down, CSVreaderhfstats2Up, CSVreaderhfstats2Down, CSVreaderlfstats1Up, CSVreaderlfstats1Down, CSVreaderlfstats2Up, CSVreaderlfstats2Down, CSVreadercfErr1Up, CSVreadercfErr1Down, CSVreadercfErr2Up, CSVreadercfErr2Down );

    // print SF
    //cout<<"SF "<<scaleFactors[0]<<endl;



    // fill eventweight
    Double_t eventWeight = partialSampleWeight * xsec * overallEventWeight ;  //kfactor e l1prefiring non ci sono, tanto uso solo HH sample



    // --- choose 2 jets

    // get and save vector with max btagger value
    deepCSV_jet1 = *max_element(JetBTagger->begin(), JetBTagger->end());

    // get and save btagger value of the second jet (the one with second max btag)
    int d1_maxbtag = distance( JetBTagger->begin(), max_element(JetBTagger->begin(), JetBTagger->end()));

    float maxJetBtag = -9999.;
    int d2_maxbtag = -9999;
    for(UInt_t i=0; i<JetBTagger->size(); i++){

      if(i == d1_maxbtag) continue;
      float temp = JetBTagger->at(i);
      if (temp > maxJetBtag){
        maxJetBtag = temp;
        d2_maxbtag = i;
      }
    }
    // save btagger value of the second jet (the one with second max btag)
    deepCSV_jet2 = JetBTagger->at(d2_maxbtag);



    // fill histos
    h_BtagSF->Fill(scaleFactors[0]);
    h_BtagSF_norm->Fill(scaleFactors[0] * sum_events/sum_BTagSF);
    h_Btagger_jet1_preSF ->Fill(deepCSV_jet1, eventWeight);
    h_Btagger_jet1_postSF->Fill(deepCSV_jet1, eventWeight*scaleFactors[0] * sum_events/sum_BTagSF);
    h_Btagger_jet2_preSF ->Fill(deepCSV_jet2, eventWeight);
    h_Btagger_jet2_postSF->Fill(deepCSV_jet2, eventWeight*scaleFactors[0] * sum_events/sum_BTagSF); 



  }// end loop over tree entries

  
  


  // Draw histos
  gStyle->SetOptStat(0);

  TCanvas *c_btagSF = new TCanvas();
  c_btagSF->cd();
  h_BtagSF->SetLineColor(kBlue);
  h_BtagSF->Draw("hist");
  c_btagSF->SaveAs("btagSF_"+ syear + ".png");

  TCanvas *c_btagSF_norm = new TCanvas();
  c_btagSF_norm->cd();
  h_BtagSF_norm->SetLineColor(kBlue);
  h_BtagSF_norm->Draw("hist");
  c_btagSF_norm->SaveAs("btagSF_norm_"+ syear + ".png");

  TCanvas *c_btagger_jet1 = new TCanvas();
  c_btagger_jet1->cd();
  h_Btagger_jet1_preSF->SetLineColor(kBlue);
  h_Btagger_jet1_preSF->Draw("hist");
  h_Btagger_jet1_postSF->SetLineColor(kRed);
  h_Btagger_jet1_postSF->Draw("hist same");

  TLegend* leg_j1 = new TLegend(0.45,0.75,0.6,0.89);
  leg_j1->AddEntry(h_Btagger_jet1_preSF , "no SF", "l");
  leg_j1->AddEntry(h_Btagger_jet1_postSF, "with SF", "l");
  leg_j1->SetFillColor(kWhite);
  leg_j1->SetLineColor(kBlack);
  leg_j1->SetTextFont(43);
  leg_j1->SetTextSize(20);
  leg_j1->Draw();

  c_btagger_jet1->SaveAs("btagger_jet1_SF_"+ syear + ".png");


  TCanvas *c_btagger_jet2 = new TCanvas();
  c_btagger_jet2->cd();
  h_Btagger_jet2_postSF->SetLineColor(kRed);
  h_Btagger_jet2_postSF->Draw("hist");
  h_Btagger_jet2_preSF->SetLineColor(kBlue);
  h_Btagger_jet2_preSF->Draw("hist same");

  TLegend* leg_j2 = new TLegend(0.45,0.75,0.6,0.89);
  leg_j2->AddEntry(h_Btagger_jet2_preSF , "no SF", "l");
  leg_j2->AddEntry(h_Btagger_jet2_postSF, "with SF", "l");
  leg_j2->SetFillColor(kWhite);
  leg_j2->SetLineColor(kBlack);
  leg_j2->SetTextFont(43);
  leg_j2->SetTextSize(20);
  leg_j2->Draw();

  c_btagger_jet2->SaveAs("btagger_jet2_SF_"+ syear + ".png");



}
