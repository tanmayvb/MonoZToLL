// example code to run 2016 NSSM MC X->Y+H samples
// .L xAna_nano_nssm.C++
// xAna_nano_nssm("test.root") or xAna_nano_nssm("input.txt")
// example root file is at /afs/cern.ch/work/s/syu/public/forTiKai/nssm_nano.root

#include <vector>
#include <iostream>
#include <fstream>
#include <algorithm>
#include <TH1D.h>
#include <TFile.h>
#include "untuplizer.h"
#include <TLorentzVector.h>

using namespace std;
void xAna_nano_nssm(std::string filename){

  std::vector<std::string> inputFiles;

  // check first if this is a root file
  if(filename.find(".root")!=string::npos)
    {
      cout << "This is a single input root file" << endl;
      inputFiles.push_back(filename);
    }
  else // assume this is a text file
    {
      cout << "This is a text file " << endl;
      ifstream fin;
      fin.open(filename.data());
      string temp;
      fin >> temp;
      while(!fin.eof())
	{
	  inputFiles.push_back(temp);
	  fin >> temp;
	}
      cout << "There are " << inputFiles.size() << " files" << endl;
      for(unsigned int ifile=0; ifile < inputFiles.size(); ifile++)
	cout << "Input file " << ifile << " is " << inputFiles[ifile] << endl;
    }
  
  //get TTree from file ...  
  TreeReader data(inputFiles,"Events");
  Long64_t nTotal=0;
  Long64_t nPass[20]={0};
  TH1F* heve=new TH1F("heve","",1,0.5,1.5);

  for(Long64_t jEntry=0; jEntry<data.GetEntriesFast() ;jEntry++){

    if (jEntry % 50000 == 0)
      fprintf(stderr, "Processing event %lli of %lli\n", jEntry + 1, data.GetEntriesFast());

    data.GetEntry(jEntry);
    nTotal++;
    heve->Fill(1.);
    //1. trigger 

    Bool_t passTrigger=false;
    const unsigned int nTrigs=7;
    Bool_t passTrig[nTrigs] = {data.GetBool("HLT_PFHT800"),
			 data.GetBool("HLT_PFHT900"),
			 data.GetBool("HLT_PFHT650_WideJetMJJ900DEtaJJ1p5"),
			 data.GetBool("HLT_AK8PFJet360_TrimMass30"),
			 data.GetBool("HLT_AK8DiPFJet280_200_TrimMass30_BTagCSV_p20"),
			 data.GetBool("HLT_AK8PFHT650_TrimR0p1PT0p03Mass50"),
			 data.GetBool("HLT_AK8PFHT700_TrimR0p1PT0p03Mass50")
    };

    for(unsigned int itrig=0; itrig< nTrigs; itrig++)
      {
	if(passTrig[itrig]==true)
	  {
	    passTrigger=true;
	    break;
	  }
      } // end of loop over required trigger paths

    if(!passTrigger)continue;
    nPass[0]++;

    // loop over fatjets
    Float_t*  FatJet_pt = data.GetPtrFloat("FatJet_pt");
    Float_t*  FatJet_eta = data.GetPtrFloat("FatJet_eta");
    Float_t*  FatJet_tau1 = data.GetPtrFloat("FatJet_tau1");
    Float_t*  FatJet_tau2 = data.GetPtrFloat("FatJet_tau2");
    
    UInt_t nFatJet = data.GetInt("nFatJet");
    UInt_t nGoodPair = 0;

    for(UInt_t ij=0; ij < nFatJet; ij++){

      if(FatJet_pt[ij] < 300)continue;
      if(fabs(FatJet_eta[ij]) > 2.4)continue;
      Float_t tau21_i = FatJet_tau2[ij]/FatJet_tau1[ij];
      if(tau21_i > 0.55)continue;

      for(UInt_t jj=0; jj < ij; jj++){

	if(FatJet_pt[jj] < 300)continue;
	if(fabs(FatJet_eta[jj]) > 2.4)continue;
	Float_t tau21_j = FatJet_tau2[jj]/FatJet_tau1[jj];
	if(tau21_j > 0.55)continue;

	// eta difference
	if(fabs(FatJet_eta[ij]-FatJet_eta[jj]) > 1.3)continue;
	
	
	nGoodPair++;

	
      } // end of inner jet loop

      
    } // end of outer jet loop


    if(nGoodPair<1)continue;
    nPass[1]++;
    

  } // end of loop over events

  cout << "Number of total events = " << nTotal << endl;

  for(int i=0;i<20;i++)
    if(nPass[i]>0)cout << "nPass["<<i<<"]= " << nPass[i] << endl;

  // writing example output file
  TFile* outFile = new TFile("histo.root","recreate");
  heve->Write();
  outFile->Close();
  
  
} // end of macro
