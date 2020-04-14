// C++
#include <iostream>
#include <fstream>
#include <string>

// ROOT
#include "TApplication.h"
#include <TROOT.h>
#include "TFile.h"
#include "TString.h"
#include "TStyle.h"

// My own files
#include <ZZXAnalysis/AnalysisStep/test/ZpXEstimation/include/SSmethod.h>
#include <ZZXAnalysis/AnalysisStep/test/ZpXEstimation/src/setTDRStyle.cpp>

using namespace std;

int main( int argc, char *argv[] )
{
   setTDRStyle();
   
   TString path = "/eos/user/a/acappati/samples_HH4lbb/samples_2018/";
   TString file_name = "/ZZXAnalysis.root";
	
   TString Data    = path + "AllData"        + file_name;
   TString WZ      = path + "WZTo3LNuext1"   + file_name;
   TString ZZ      = path + "ZZTo4lext1"     + file_name;
   TString ttbar   = path + "TTTo2L2Nu"      + file_name;
   TString DY      = path + "DYJetsToLL_M50" + file_name;
	
   bool SubtractWZ = true;
   bool Remove_NegBins_FR = true;
   bool SubtractMCContribution = true;
	
   float pT_bins[] = {5, 7, 10, 20, 30, 40, 50, 80};

   SSmethod *ss = new SSmethod();
   ss->SetLumi(59.7);

   ///////////////////////////////////
   // Fill control histos           //
   ///////////////////////////////////
   ss->FillDataMCPlots(Data);
   ss->FillDataMCPlots(WZ);
   ss->FillDataMCPlots(ZZ);
   ss->FillDataMCPlots(ttbar);
   ss->FillDataMCPlots(DY);
   ss->SaveDataMCHistos("DataMC_SS_samples2018.root");

   ///////////////////////////////////
   // Fill passing/failling histos  //
   ///////////////////////////////////
   ss->FillFRHistos(Data);
   ss->FillFRHistos(WZ);
   ss->SaveFRHistos("Histos_SS_samples2018.root", SubtractWZ, Remove_NegBins_FR);

   ///////////////////////////////////
   // Calculate fake rates          //
   ///////////////////////////////////
   ss->GetFRHistos("Histos_SS_samples2018.root");
   ss->Set_pT_binning(8, pT_bins);
   ss->ProduceFakeRates("FakeRates_SS_samples2018.root", Data);

   ///////////////////////////////////
   // Calculate OS/SS ratios        //
   ///////////////////////////////////
   ss->Calculate_SSOS_Ratio( Data, ZZ, SubtractMCContribution);

   ///////////////////////////////////
   // Fill ZX contributions histos  //
   ///////////////////////////////////
   ss->MakeHistogramsZX(Data, "FakeRates_SS_samples2018.root");
   ss->SaveZXHistos("ZXHistos_SS_samples2018.root");

   ///////////////////////////////////
   // Plot control plots            //
   ///////////////////////////////////
   ss->GetDataMCHistos("DataMC_SS_samples2018.root");
   ss->PlotDataMC( "M4l", "Plots" );

   ///////////////////////////////////
   // Plot and fit Z+X              //
   ///////////////////////////////////
   ss->GetZXHistos("ZXHistos_SS_samples2018.root");
   ss->PlotZX("M4l", "Plots");
   ss->FitZX("M4l", "Plots");
	
   delete ss;
}
