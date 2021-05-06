#ifndef __analyze_cxx__
#define __analyze_cxx__

#include <TFile.h>
#include <TTree.h>
#include <TH1D.h>
#include <TH2D.h>
#include <TF1.h>
#include <TLine.h>
#include <TProfile.h>
#include <TLorentzVector.h>

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

#include <math.h>

#include <AtlasUtils.h>

#include <GlobalParams.h>
#include <Utilities.h>

#include "header.h"

using namespace PythiaBoostStudy;



void ScaleHist (TH1D* h, const double sf, const bool doWidth) {
  const int nb = h->GetNbinsX ();
  for (int iX = 1; iX <= nb; iX++) {
    h->SetBinContent (iX, h->GetBinContent (iX) * sf / (doWidth ? h->GetBinWidth (iX) : 1.));
    h->SetBinError (iX, h->GetBinError (iX) * sf / (doWidth ? h->GetBinWidth (iX) : 1.));
  }
  return;
}



void ScaleHist (TH2D* h, const double sf, const bool doWidth) {
  const int nbx = h->GetNbinsX (); const int nby = h->GetNbinsY ();
  for (int iX = 1; iX <= nbx; iX++) {
    for (int iY = 1; iY <= nby; iY++) {
      h->SetBinContent (iX, iY, h->GetBinContent (iX, iY) * sf / (doWidth ? h->GetXaxis ()->GetBinWidth (iX) * h->GetYaxis ()->GetBinWidth (iY) : 1.));
      h->SetBinError (iX, iY, h->GetBinError (iX, iY) * sf / (doWidth ? h->GetXaxis ()->GetBinWidth (iX) * h->GetYaxis ()->GetBinWidth (iY) : 1.));
    }
  }
  return;
}



double GetMaxRapidity (const double mass, const double pT) {
  // Strategy:
  // for a particular mass of particle, get its rapidity at the edge of the
  // ATLAS tracker (eta = +2.5).
  // That value is the maximum rapidity of that particle you can observe, y_max,
  // across all system boosts.
  // Since the p+Pb center of mass boost is +0.465, you restrict to just 
  // particles with |rapidity - y_system| < y_max - 0.465.

  const double en = std::sqrt (std::pow (mass, 2) + std::pow (pT * std::cosh ((double)2.5), 2));
  const double pz = pT * std::sinh ((double)2.5);

  return 0.5 * std::log ((en + pz) / (en - pz));
}




int main (int argc, char** argv) {

  if (argc < 4) {
    std::cout << " usage: analyze NAME INFILENAME OUTFILENAME" << std::endl;
    return 0;
  }

  const string name = std::string (argv[1]);
  const string inFileName = std::string (argv[2]);
  const string outFileName = std::string (argv[3]);

  const bool DoNoCut = (name.find ("NoCut") != std::string::npos);
  const bool DoM0Cut = (name.find ("M0_Cut") != std::string::npos);
  const bool DoMPiCut = (name.find ("MPi_Cut") != std::string::npos);
  const bool DoMProCut = (name.find ("MPro_Cut") != std::string::npos);
  const float boost = (name.find ("boost") != std::string::npos ? 0.465 : 0);

  std::cout << "boost = " << boost << std::endl;

  TFile* inFile = nullptr;
  TTree* inTree = nullptr;

  int code = 0;

  int akt2_jet_n = 0;
  float akt2_jet_pt[100];
  float akt2_jet_eta[100];
  float akt2_jet_phi[100];
  float akt2_jet_e[100];
  float akt2_jet_m[100];

  int akt4_jet_n = 0;
  float akt4_jet_pt[100];
  float akt4_jet_eta[100];
  float akt4_jet_phi[100];
  float akt4_jet_e[100];
  float akt4_jet_m[100];

  int part_n = 0;
  float part_pt[10000];
  float part_eta[10000];
  float part_y[10000];
  float part_phi[10000];
  float part_e[10000];
  float part_m[10000];

  inFile = new TFile (inFileName.c_str (), "read");
  inTree = (TTree*) inFile->Get ("tree");

  const int nEvents = inTree->GetEntries ();
  double sumWgtsEvents = 0, sumWgtsSqEvents = 0;
  int nJetEvents = 0;
  double sumWgtsJetEvents = 0, sumWgtsSqJetEvents = 0;

  inTree->SetBranchAddress ("code",       &code);
  //inTree->SetBranchAddress ("id1",        &id1);
  //inTree->SetBranchAddress ("id2",        &id2);
  //inTree->SetBranchAddress ("x1pdf",      &x1pdf);
  //inTree->SetBranchAddress ("x2pdf",      &x2pdf);
  //inTree->SetBranchAddress ("Q",          &Q);
  //inTree->SetBranchAddress ("isValence1", &isValence1);
  //inTree->SetBranchAddress ("isValence2", &isValence2);

  inTree->SetBranchAddress ("akt2_jet_n",   &akt2_jet_n);
  inTree->SetBranchAddress ("akt2_jet_pt",  &akt2_jet_pt);
  inTree->SetBranchAddress ("akt2_jet_eta", &akt2_jet_eta);
  inTree->SetBranchAddress ("akt2_jet_phi", &akt2_jet_phi);
  inTree->SetBranchAddress ("akt2_jet_e",   &akt2_jet_e);
  inTree->SetBranchAddress ("akt2_jet_m",   &akt2_jet_m);

  inTree->SetBranchAddress ("akt4_jet_n",   &akt4_jet_n);
  inTree->SetBranchAddress ("akt4_jet_pt",  &akt4_jet_pt);
  inTree->SetBranchAddress ("akt4_jet_eta", &akt4_jet_eta);
  inTree->SetBranchAddress ("akt4_jet_phi", &akt4_jet_phi);
  inTree->SetBranchAddress ("akt4_jet_e",   &akt4_jet_e);
  inTree->SetBranchAddress ("akt4_jet_m",   &akt4_jet_m);

  inTree->SetBranchAddress ("part_n",     &part_n);
  inTree->SetBranchAddress ("part_pt",    &part_pt);
  inTree->SetBranchAddress ("part_eta",   &part_eta);
  inTree->SetBranchAddress ("part_y",     &part_y);
  inTree->SetBranchAddress ("part_phi",   &part_phi);
  inTree->SetBranchAddress ("part_e",     &part_e);
  inTree->SetBranchAddress ("part_m",     &part_m);


  TH1D* h_trk_pt_ns_yield;
  TH2D* h2_trk_pt_ns_cov;
  TH1D* h_trk_pt_as_yield;
  TH2D* h2_trk_pt_as_cov;

  TH1D* h_trk_dphi_pt_gt2_yield;
  TH2D* h2_trk_dphi_pt_gt2_cov;
  TH1D* h_trk_dphi_pt_lt2_yield;
  TH2D* h2_trk_dphi_pt_lt2_cov;

  TH1D* h_jet_pt_yield;
  TH2D* h2_jet_pt_cov;

  TH1D* h_jet_yield;

  const double pthBins[] = {0.5, 0.55, 0.6, 0.65, 0.7, 0.75, 0.8, 0.85, 0.9, 0.95, 1, 1.1, 1.2, 1.3, 1.4, 1.5, 1.6, 1.7, 1.8, 1.9, 2, 2.25, 2.5, 2.75, 3, 3.25, 3.5, 3.75, 4, 4.5, 5, 5.5, 6, 7, 8, 9, 10, 11, 12, 14, 16, 18, 20, 25, 30, 35, 40, 45, 50, 55, 60};
  const short nPthBins = sizeof (pthBins) / sizeof (pthBins[0]) - 1;
  const short nDPhiBins = 24;
  const double* dPhiBins = linspace (0, pi, nDPhiBins);
  const int nPtJBins = 30;
  const double* pTJBins = logspace (8, 140, nPtJBins);

  int trk_pt_ns_counts[nPthBins] = {};
  int trk_pt_as_counts[nPthBins] = {};
  int trk_dphi_pt_gt2_counts[nDPhiBins] = {};
  int trk_dphi_pt_lt2_counts[nDPhiBins] = {};
  int jet_ptj_counts[nPtJBins] = {};


  TFile* outFile = new TFile (outFileName.c_str (), "recreate");

  h_trk_pt_ns_yield = new TH1D (Form ("h_trk_pt_ns_yield_%s", name.c_str ()), ";#it{p}_{T}^{ch} [GeV]", nPthBins, pthBins);
  h2_trk_pt_ns_cov = new TH2D (Form ("h2_trk_pt_ns_cov_%s", name.c_str ()), ";#it{p}_{T}^{ch} [GeV];#it{p}_{T}^{ch} [GeV]", nPthBins, pthBins, nPthBins, pthBins);
  h_trk_pt_as_yield = new TH1D (Form ("h_trk_pt_as_yield_%s", name.c_str ()), ";#it{p}_{T}^{ch} [GeV]", nPthBins, pthBins);
  h2_trk_pt_as_cov = new TH2D (Form ("h2_trk_pt_as_cov_%s", name.c_str ()), ";#it{p}_{T}^{ch} [GeV];#it{p}_{T}^{ch} [GeV]", nPthBins, pthBins, nPthBins, pthBins);

  h_trk_dphi_pt_gt2_yield = new TH1D (Form ("h_trk_dphi_pt_gt2_yield_%s", name.c_str ()), ";#Delta#phi_{ch,#gamma}", nDPhiBins, dPhiBins);
  h2_trk_dphi_pt_gt2_cov = new TH2D (Form ("h2_trk_dphi_pt_gt2_cov_%s", name.c_str ()), ";#Delta#phi_{ch,#gamma}", nDPhiBins, dPhiBins, nDPhiBins, dPhiBins);
  h_trk_dphi_pt_lt2_yield = new TH1D (Form ("h_trk_dphi_pt_lt2_yield_%s", name.c_str ()), ";#Delta#phi_{ch,#gamma}", nDPhiBins, dPhiBins);
  h2_trk_dphi_pt_lt2_cov = new TH2D (Form ("h2_trk_dphi_pt_lt2_cov_%s", name.c_str ()), ";#Delta#phi_{ch,#gamma}", nDPhiBins, dPhiBins, nDPhiBins, dPhiBins);

  h_jet_pt_yield = new TH1D (Form ("h_jet_pt_yield_%s", name.c_str ()), ";#it{p}_{T}^{jet} [GeV]", nPtJBins, pTJBins);
  h2_jet_pt_cov = new TH2D (Form ("h2_jet_pt_cov_%s", name.c_str ()), ";#it{p}_{T}^{jet} [GeV];#it{p}_{T}^{jet} [GeV]", nPtJBins, pTJBins, nPtJBins, pTJBins);

  h_jet_yield = new TH1D (Form ("h_jet_yield_%s", name.c_str ()), "", 9, -0.5, 8.5);
  h_jet_yield->Sumw2 ();

  //bool firstPart = true;

  for (int iEvent = 0; iEvent < nEvents; iEvent++) {
    inTree->GetEntry (iEvent);

    const double evtWgt = 1; // no weights 
    sumWgtsEvents += evtWgt;
    sumWgtsSqEvents += evtWgt*evtWgt;

    // all-particle jets
    int jetCount = 0;
    for (int iJ = 0; iJ < akt4_jet_n; iJ++) {
      const float jpt = akt4_jet_pt[iJ];
      const float jeta = akt4_jet_eta[iJ];
      const float jphi = akt4_jet_phi[iJ];

      if (fabs (jeta) > 2.8)
        continue;

      for (short i = 0; i < nPtJBins; i++) {
        if (pTJBins[i] <= jpt && jpt < pTJBins[i+1]) {
          jet_ptj_counts[i]++;
          break;
        }
      }

      if (jpt < 60)
        continue;

      nJetEvents += 1;
      sumWgtsJetEvents += evtWgt;
      sumWgtsSqJetEvents += evtWgt*evtWgt;

      // now loop over the particles in the recorded event
      for (int iPart = 0; iPart < part_n; iPart++) {

        const float trk_pt = part_pt[iPart];
        const float trk_eta = part_eta[iPart];
        const float dphi = DeltaPhi (part_phi[iPart], jphi);

        if (fabs (part_eta[iPart]) > 2.5)
          continue;

        else if (!DoNoCut) {
          double trk_m = -1;
          if (DoM0Cut) trk_m = 0; // assume everyone is massless
          if (DoMPiCut) trk_m = pion_mass; // assume everyone is a charged pion
          if (DoMProCut) trk_m = proton_mass; // assume everyone is a charged pion
          if (trk_m < 0) continue;
          const double trk_e = std::sqrt (std::pow (trk_m, 2) + pow (trk_pt * std::cosh ((double)(trk_eta)), 2));
          const double trk_pz = ((double)trk_pt) * std::sinh ((double)trk_eta);
          const double trk_y = (trk_e > trk_pz ? 0.5 * std::log ((trk_e + trk_pz)/(trk_e - trk_pz)) : 0.);

          //if (firstPart) {
          //  const double trk_y_truth = part_y[iPart];
          //  const double trk_e_truth = part_e[iPart];
          //  std::cout << "first particle (pT, eta, y, yhat, yerr, E, Ehat, Eerr) = (" << trk_pt << ", " << trk_eta << ", " << trk_y_truth << ", " << trk_y << ", " << trk_y - trk_y_truth << ", " << trk_e_truth << ", " << trk_e << ", " << trk_e - trk_e_truth << ")" << std::endl;
          //  firstPart = false;
          //}
  
          if (fabs (trk_y - boost) > GetMaxRapidity (trk_m, trk_pt)-0.465) // TODO justify me!
            continue;
        }

        for (short i = 0; i < nDPhiBins; i++) {
          if (dPhiBins[i] <= dphi && dphi < dPhiBins[i+1]) {
            if (trk_pt > 2)
              trk_dphi_pt_gt2_counts[i]++;
            else if (trk_pt > 0.5)
              trk_dphi_pt_lt2_counts[i]++;
            break;
          }
        }


        for (short i = 0; i < nPthBins; i++) {
          if (pthBins[i] <= trk_pt && trk_pt < pthBins[i+1]) {
            if (dphi >= 7.*pi/8.)
              trk_pt_ns_counts[i]++;
            else if (dphi < pi/8.)
              trk_pt_as_counts[i]++;
            break;
          }
        }
      } // end loop over iPart

      nJetEvents += 1;
      sumWgtsJetEvents += evtWgt;
      sumWgtsSqJetEvents += evtWgt*evtWgt;
    }
    h_jet_yield->Fill (jetCount);


    for (short iX = 0; iX < nPthBins; iX++) {
      h_trk_pt_ns_yield->SetBinContent (iX+1, h_trk_pt_ns_yield->GetBinContent (iX+1) + evtWgt * trk_pt_ns_counts[iX]);
      for (short iY = 0; iY < nPthBins; iY++)
        h2_trk_pt_ns_cov->SetBinContent (iX+1, iY+1, h2_trk_pt_ns_cov->GetBinContent (iX+1, iY+1) + evtWgt * (trk_pt_ns_counts[iX])*(trk_pt_ns_counts[iY]));
    }
    for (short iX = 0; iX < nPthBins; iX++) {
      h_trk_pt_as_yield->SetBinContent (iX+1, h_trk_pt_as_yield->GetBinContent (iX+1) + evtWgt * trk_pt_as_counts[iX]);
      for (short iY = 0; iY < nPthBins; iY++)
        h2_trk_pt_as_cov->SetBinContent (iX+1, iY+1, h2_trk_pt_as_cov->GetBinContent (iX+1, iY+1) + evtWgt * (trk_pt_as_counts[iX])*(trk_pt_as_counts[iY]));
    }
    for (short iX = 0; iX < nDPhiBins; iX++) {
      h_trk_dphi_pt_gt2_yield->SetBinContent (iX+1, h_trk_dphi_pt_gt2_yield->GetBinContent (iX+1) + evtWgt * trk_dphi_pt_gt2_counts[iX]);
      for (short iY = 0; iY < nDPhiBins; iY++)
        h2_trk_dphi_pt_gt2_cov->SetBinContent (iX+1, iY+1, h2_trk_dphi_pt_gt2_cov->GetBinContent (iX+1, iY+1) +evtWgt *  (trk_dphi_pt_gt2_counts[iX])*(trk_dphi_pt_gt2_counts[iY]));
    }
    for (short iX = 0; iX < nDPhiBins; iX++) {
      h_trk_dphi_pt_lt2_yield->SetBinContent (iX+1, h_trk_dphi_pt_lt2_yield->GetBinContent (iX+1) + evtWgt * trk_dphi_pt_lt2_counts[iX]);
      for (short iY = 0; iY < nDPhiBins; iY++)
        h2_trk_dphi_pt_lt2_cov->SetBinContent (iX+1, iY+1, h2_trk_dphi_pt_lt2_cov->GetBinContent (iX+1, iY+1) + evtWgt * (trk_dphi_pt_lt2_counts[iX])*(trk_dphi_pt_lt2_counts[iY]));
    }

    for (short iX = 0; iX < nPtJBins; iX++) {
      h_jet_pt_yield->SetBinContent (iX+1, h_jet_pt_yield->GetBinContent (iX+1) + evtWgt * jet_ptj_counts[iX]);
      for (short iY = 0; iY < nPtJBins; iY++)
        h2_jet_pt_cov->SetBinContent (iX+1, iY+1, h2_jet_pt_cov->GetBinContent (iX+1, iY+1) + evtWgt * (jet_ptj_counts[iX])*(jet_ptj_counts[iY]));
    }

    for (int i = 0; i < nPthBins; i++) {
      trk_pt_ns_counts[i] = 0;
      trk_pt_as_counts[i] = 0;
    }
    for (int i = 0; i < nDPhiBins; i++) {
      trk_dphi_pt_gt2_counts[i] = 0;
      trk_dphi_pt_lt2_counts[i] = 0;
    }
    for (int i = 0; i < nPtJBins; i++) {
      jet_ptj_counts[i] = 0;
    }
  } // end loop over iEvent

  inFile->Close ();
  SaferDelete (&inFile);


  // convert all counts to doubles (to avoid integer division issues... yay)
  const double fnEvents = (double) nEvents;
  const double fnJetEvents = (double) nJetEvents;

  {
    TH2D* h2 = nullptr;
    TH1D* h = nullptr;

    h2 = h2_trk_pt_ns_cov;
    h = h_trk_pt_ns_yield;
    for (int iX = 1; iX <= h2->GetNbinsX (); iX++)
      for (int iY = 1; iY <= h2->GetNbinsY (); iY++)
        h2->SetBinContent (iX, iY, ((double)(h2->GetBinContent (iX, iY))) - ((double)(h->GetBinContent (iX)))*((double)(h->GetBinContent (iY)))/((double)sumWgtsJetEvents));
    ScaleHist (h, pow (sumWgtsJetEvents * pi/4., -1), true);
    ScaleHist (h2, pow (nJetEvents * (sumWgtsJetEvents*sumWgtsJetEvents - sumWgtsSqJetEvents) * pow(pi/4., 2) / sumWgtsJetEvents, -1), true);
    SetVariances (h, h2);


    h2 = h2_trk_pt_as_cov;
    h = h_trk_pt_as_yield;
    for (int iX = 1; iX <= h2->GetNbinsX (); iX++)
      for (int iY = 1; iY <= h2->GetNbinsY (); iY++)
        h2->SetBinContent (iX, iY, ((double)(h2->GetBinContent (iX, iY))) - ((double)(h->GetBinContent (iX)))*((double)(h->GetBinContent (iY)))/((double)sumWgtsJetEvents));
    ScaleHist (h, pow (sumWgtsJetEvents * pi/4., -1), true);
    ScaleHist (h2, pow (nJetEvents * (sumWgtsJetEvents*sumWgtsJetEvents - sumWgtsSqJetEvents) * pow(pi/4., 2) / sumWgtsJetEvents, -1), true);
    SetVariances (h, h2);


    h2 = h2_trk_dphi_pt_gt2_cov;
    h = h_trk_dphi_pt_gt2_yield;
    for (int iX = 1; iX <= h2->GetNbinsX (); iX++)
      for (int iY = 1; iY <= h2->GetNbinsY (); iY++)
        h2->SetBinContent (iX, iY, ((double)(h2->GetBinContent (iX, iY))) - ((double)(h->GetBinContent (iX)))*((double)(h->GetBinContent (iY)))/((double)sumWgtsJetEvents));
    ScaleHist (h, pow (sumWgtsJetEvents, -1), true);
    ScaleHist (h2, pow (nJetEvents * (sumWgtsJetEvents*sumWgtsJetEvents - sumWgtsSqJetEvents) / sumWgtsJetEvents, -1), true);
    SetVariances (h, h2);


    h2 = h2_trk_dphi_pt_lt2_cov;
    h = h_trk_dphi_pt_lt2_yield;
    for (int iX = 1; iX <= h2->GetNbinsX (); iX++)
      for (int iY = 1; iY <= h2->GetNbinsY (); iY++)
        h2->SetBinContent (iX, iY, ((double)(h2->GetBinContent (iX, iY))) - ((double)(h->GetBinContent (iX)))*((double)(h->GetBinContent (iY)))/((double)sumWgtsJetEvents));
    ScaleHist (h, pow (sumWgtsJetEvents, -1), true);
    ScaleHist (h2, pow (nJetEvents * (sumWgtsJetEvents*sumWgtsJetEvents - sumWgtsSqJetEvents) / sumWgtsJetEvents, -1), true);
    SetVariances (h, h2);


    h2 = h2_jet_pt_cov;
    h = h_jet_pt_yield;
    for (int iX = 1; iX <= h2->GetNbinsX (); iX++)
      for (int iY = 1; iY <= h2->GetNbinsY (); iY++)
        h2->SetBinContent (iX, iY, ((double)(h2->GetBinContent (iX, iY))) - ((double)(h->GetBinContent (iX)))*((double)(h->GetBinContent (iY)))/((double)sumWgtsJetEvents));
    ScaleHist (h, pow (sumWgtsJetEvents, -1), true);
    ScaleHist (h2, pow (sumWgtsJetEvents * (sumWgtsJetEvents-1), -1), true);
    SetVariances (h, h2);

  }


  // now save histograms to a rootfile
  h_trk_pt_ns_yield->Write ();
  h2_trk_pt_ns_cov->Write ();
  h_trk_pt_as_yield->Write ();
  h2_trk_pt_as_cov->Write ();
  h_trk_dphi_pt_gt2_yield->Write ();
  h2_trk_dphi_pt_gt2_cov->Write ();
  h_trk_dphi_pt_lt2_yield->Write ();
  h2_trk_dphi_pt_lt2_cov->Write ();
  h_jet_pt_yield->Write ();
  h2_jet_pt_cov->Write ();
  h_jet_yield->Write (); 
  
  outFile->Close ();

  return 0;
}

#endif
