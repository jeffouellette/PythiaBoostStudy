#include <TFile.h>
#include <TH1D.h>
#include <TH2D.h>
#include <TF1.h>
#include <TGraphAsymmErrors.h>
#include <TLine.h>
#include <TCanvas.h>
#include <TProfile.h>
#include <TLatex.h>
#include <TF1.h>
#include <TBox.h>

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

#include <math.h>

#include <AtlasStyle.h>
#include <AtlasUtils.h>

#include <GlobalParams.h>
#include <Utilities.h>

#include "header.h"

using namespace PythiaBoostStudy;

typedef TGraphAsymmErrors TGAE;

TH1D* h_trk_pt_ns_yield[4];
TH1D* h_trk_pt_ns_yield_boost[4];
TH1D* h_trk_pt_ns_yield_ratio[4]; // ratio of track yield in a jet / all tracks
TH1D* h_trk_pt_as_yield[4];
TH1D* h_trk_pt_as_yield_boost[4];
TH1D* h_trk_pt_as_yield_ratio[4]; // ratio of track yield in a jet / all tracks

TH1D* h_trk_dphi_pt_gt2_yield[4];
TH1D* h_trk_dphi_pt_gt2_yield_boost[4];
TH1D* h_trk_dphi_pt_gt2_yield_ratio[4];
TH1D* h_trk_dphi_pt_lt2_yield[4];
TH1D* h_trk_dphi_pt_lt2_yield_boost[4];
TH1D* h_trk_dphi_pt_lt2_yield_ratio[4];

TH1D* h_jet_pt_yield[4];
TH1D* h_jet_pt_yield_boost[4];
TH1D* h_jet_pt_yield_ratio[4];

TH1D* h_jet_yield[4];
TH1D* h_jet_yield_boost[4];


void SetVariances (TH1D* h, TH2D* h2) {
  const int nb = h->GetNbinsX ();
  assert (nb == h2->GetNbinsX () && nb == h2->GetNbinsY ());

  for (int iX = 1; iX <= nb; iX++) {
    assert (h2->GetBinContent (iX, iX) >= 0);
    h->SetBinError (iX, sqrt (h2->GetBinContent (iX, iX)));
  }
}


TColor* tcolor = new TColor ();
const Color_t myBlue = (Color_t) tcolor->GetColor (45, 64, 245);
const Color_t myPurple = (Color_t) tcolor->GetColor (130,  10, 130);
const Color_t myRed = (Color_t) tcolor->GetColor (255,  12,  73);
const Color_t myGreen = (Color_t) tcolor->GetColor ( 54, 167,  80);
const Color_t myOrange = (Color_t) tcolor->GetColor (255,  68,   0);
const Color_t myYellow = kYellow;
const Color_t myLiteMagenta = kMagenta-10;
const Color_t myLiteGreen = kGreen-10;

Color_t colors[] = {myRed, myGreen, myBlue, myOrange, myPurple, myYellow, myLiteGreen, myLiteMagenta};


int main () {

  SetAtlasStyle(); 

  TFile* inFile = nullptr;


  inFile = new TFile ("rootFiles/NoBoost/hists_NoCut.root", "read");

  h_trk_pt_ns_yield[0] = (TH1D*) inFile->Get ("h_trk_pt_ns_yield_NoCut")->Clone ("h_trk_pt_ns_NoCut");
  h_trk_pt_as_yield[0] = (TH1D*) inFile->Get ("h_trk_pt_as_yield_NoCut")->Clone ("h_trk_pt_as_NoCut");

  h_trk_dphi_pt_gt2_yield[0] = (TH1D*) inFile->Get ("h_trk_dphi_pt_gt2_yield_NoCut")->Clone ("h_trk_dphi_pt_gt2_NoCut");
  h_trk_dphi_pt_lt2_yield[0] = (TH1D*) inFile->Get ("h_trk_dphi_pt_lt2_yield_NoCut")->Clone ("h_trk_dphi_pt_lt2_NoCut");

  h_jet_pt_yield[0] = (TH1D*) inFile->Get ("h_jet_pt_yield_NoCut")->Clone ("h_jet_pt_NoCut");

  h_jet_yield[0] = (TH1D*) inFile->Get ("h_jet_yield_NoCut")->Clone ("h_jet_NoCut");


  inFile = new TFile ("rootFiles/Boost_0p465/hists_NoCut.root", "read");

  h_trk_pt_ns_yield_boost[0] = (TH1D*) inFile->Get ("h_trk_pt_ns_yield_boost_NoCut")->Clone ("h_trk_pt_ns_boost_NoCut");
  h_trk_pt_as_yield_boost[0] = (TH1D*) inFile->Get ("h_trk_pt_as_yield_boost_NoCut")->Clone ("h_trk_pt_as_boost_NoCut");

  h_trk_dphi_pt_gt2_yield_boost[0] = (TH1D*) inFile->Get ("h_trk_dphi_pt_gt2_yield_boost_NoCut")->Clone ("h_trk_dphi_pt_gt2_boost_NoCut");
  h_trk_dphi_pt_lt2_yield_boost[0] = (TH1D*) inFile->Get ("h_trk_dphi_pt_lt2_yield_boost_NoCut")->Clone ("h_trk_dphi_pt_lt2_boost_NoCut");

  h_jet_pt_yield_boost[0] = (TH1D*) inFile->Get ("h_jet_pt_yield_boost_NoCut")->Clone ("h_jet_pt_boost_NoCut");

  h_jet_yield_boost[0] = (TH1D*) inFile->Get ("h_jet_yield_boost_NoCut")->Clone ("h_jet_boost_NoCut");

  h_trk_pt_ns_yield_ratio[0] = (TH1D*) h_trk_pt_ns_yield_boost[0]->Clone ("h_trk_pt_ns_ratio_NoCut");
  h_trk_pt_ns_yield_ratio[0]->Divide (h_trk_pt_ns_yield[0]);
  h_trk_pt_as_yield_ratio[0] = (TH1D*) h_trk_pt_as_yield_boost[0]->Clone ("h_trk_pt_as_ratio_NoCut");
  h_trk_pt_as_yield_ratio[0]->Divide (h_trk_pt_as_yield[0]);

  h_trk_dphi_pt_gt2_yield_ratio[0] = (TH1D*) h_trk_dphi_pt_gt2_yield_boost[0]->Clone ("h_trk_dphi_pt_gt2_ratio_NoCut");
  h_trk_dphi_pt_gt2_yield_ratio[0]->Divide (h_trk_dphi_pt_gt2_yield[0]);
  h_trk_dphi_pt_lt2_yield_ratio[0] = (TH1D*) h_trk_dphi_pt_lt2_yield_boost[0]->Clone ("h_trk_dphi_pt_lt2_ratio_NoCut");
  h_trk_dphi_pt_lt2_yield_ratio[0]->Divide (h_trk_dphi_pt_lt2_yield[0]);

  h_jet_pt_yield_ratio[0] = (TH1D*) h_jet_pt_yield_boost[0]->Clone ("h_jet_pt_ratio_NoCut");
  h_jet_pt_yield_ratio[0]->Divide (h_jet_pt_yield[0]);




  inFile = new TFile ("rootFiles/NoBoost/hists_M0_Cut.root", "read");

  h_trk_pt_ns_yield[1] = (TH1D*) inFile->Get ("h_trk_pt_ns_yield_M0_Cut")->Clone ("h_trk_pt_ns_M0_Cut");
  h_trk_pt_as_yield[1] = (TH1D*) inFile->Get ("h_trk_pt_as_yield_M0_Cut")->Clone ("h_trk_pt_as_M0_Cut");

  h_trk_dphi_pt_gt2_yield[1] = (TH1D*) inFile->Get ("h_trk_dphi_pt_gt2_yield_M0_Cut")->Clone ("h_trk_dphi_pt_gt2_M0_Cut");
  h_trk_dphi_pt_lt2_yield[1] = (TH1D*) inFile->Get ("h_trk_dphi_pt_lt2_yield_M0_Cut")->Clone ("h_trk_dphi_pt_lt2_M0_Cut");

  h_jet_pt_yield[1] = (TH1D*) inFile->Get ("h_jet_pt_yield_M0_Cut")->Clone ("h_jet_pt_M0_Cut");

  h_jet_yield[1] = (TH1D*) inFile->Get ("h_jet_yield_M0_Cut")->Clone ("h_jet_pt_M0_Cut");


  inFile = new TFile ("rootFiles/Boost_0p465/hists_M0_Cut.root", "read");

  h_trk_pt_ns_yield_boost[1] = (TH1D*) inFile->Get ("h_trk_pt_ns_yield_boost_M0_Cut")->Clone ("h_trk_pt_ns_boost_M0_Cut");
  h_trk_pt_as_yield_boost[1] = (TH1D*) inFile->Get ("h_trk_pt_as_yield_boost_M0_Cut")->Clone ("h_trk_pt_as_boost_M0_Cut");

  h_trk_dphi_pt_gt2_yield_boost[1] = (TH1D*) inFile->Get ("h_trk_dphi_pt_gt2_yield_boost_M0_Cut")->Clone ("h_trk_dphi_pt_gt2_boost_M0_Cut");
  h_trk_dphi_pt_lt2_yield_boost[1] = (TH1D*) inFile->Get ("h_trk_dphi_pt_lt2_yield_boost_M0_Cut")->Clone ("h_trk_dphi_pt_lt2_boost_M0_Cut");

  h_jet_pt_yield_boost[1] = (TH1D*) inFile->Get ("h_jet_pt_yield_boost_M0_Cut");

  h_jet_yield_boost[1] = (TH1D*) inFile->Get ("h_jet_yield_boost_M0_Cut")->Clone ("h_jet_boost_M0_Cut");

  h_trk_pt_ns_yield_ratio[1] = (TH1D*) h_trk_pt_ns_yield_boost[1]->Clone ("h_trk_pt_ns_ratio_M0_Cut");
  h_trk_pt_ns_yield_ratio[1]->Divide (h_trk_pt_ns_yield[1]);
  h_trk_pt_as_yield_ratio[1] = (TH1D*) h_trk_pt_as_yield_boost[1]->Clone ("h_trk_pt_as_ratio_M0_Cut");
  h_trk_pt_as_yield_ratio[1]->Divide (h_trk_pt_as_yield[1]);

  h_trk_dphi_pt_gt2_yield_ratio[1] = (TH1D*) h_trk_dphi_pt_gt2_yield_boost[1]->Clone ("h_trk_dphi_pt_gt2_ratio_M0_Cut");
  h_trk_dphi_pt_gt2_yield_ratio[1]->Divide (h_trk_dphi_pt_gt2_yield[1]);
  h_trk_dphi_pt_lt2_yield_ratio[1] = (TH1D*) h_trk_dphi_pt_lt2_yield_boost[1]->Clone ("h_trk_dphi_pt_lt2_ratio_M0_Cut");
  h_trk_dphi_pt_lt2_yield_ratio[1]->Divide (h_trk_dphi_pt_lt2_yield[1]);

  h_jet_pt_yield_ratio[1] = (TH1D*) h_jet_pt_yield_boost[1]->Clone ("h_jet_pt_ratio_M0_Cut");
  h_jet_pt_yield_ratio[1]->Divide (h_jet_pt_yield[1]);




  inFile = new TFile ("rootFiles/NoBoost/hists_MPi_Cut.root", "read");

  h_trk_pt_ns_yield[2] = (TH1D*) inFile->Get ("h_trk_pt_ns_yield_MPi_Cut")->Clone ("h_trk_pt_ns_MPi_Cut");
  h_trk_pt_as_yield[2] = (TH1D*) inFile->Get ("h_trk_pt_as_yield_MPi_Cut")->Clone ("h_trk_pt_as_MPi_Cut");

  h_trk_dphi_pt_gt2_yield[2] = (TH1D*) inFile->Get ("h_trk_dphi_pt_gt2_yield_MPi_Cut")->Clone ("h_trk_dphi_pt_gt2_MPi_Cut");
  h_trk_dphi_pt_lt2_yield[2] = (TH1D*) inFile->Get ("h_trk_dphi_pt_lt2_yield_MPi_Cut")->Clone ("h_trk_dphi_pt_lt2_MPi_Cut");

  h_jet_pt_yield[2] = (TH1D*) inFile->Get ("h_jet_pt_yield_MPi_Cut")->Clone ("h_jet_pt_MPi_Cut");

  h_jet_yield[2] = (TH1D*) inFile->Get ("h_jet_yield_MPi_Cut")->Clone ("h_jet_MPi_Cut");


  inFile = new TFile ("rootFiles/Boost_0p465/hists_MPi_Cut.root", "read");

  h_trk_pt_ns_yield_boost[2] = (TH1D*) inFile->Get ("h_trk_pt_ns_yield_boost_MPi_Cut")->Clone ("h_trk_pt_ns_boost_MPi_Cut");
  h_trk_pt_as_yield_boost[2] = (TH1D*) inFile->Get ("h_trk_pt_as_yield_boost_MPi_Cut")->Clone ("h_trk_pt_as_boost_MPi_Cut");

  h_trk_dphi_pt_gt2_yield_boost[2] = (TH1D*) inFile->Get ("h_trk_dphi_pt_gt2_yield_boost_MPi_Cut")->Clone ("h_trk_dphi_pt_gt2_boost_MPi_Cut");
  h_trk_dphi_pt_lt2_yield_boost[2] = (TH1D*) inFile->Get ("h_trk_dphi_pt_lt2_yield_boost_MPi_Cut")->Clone ("h_trk_dphi_pt_lt2_boost_MPi_Cut");

  h_jet_pt_yield_boost[2] = (TH1D*) inFile->Get ("h_jet_pt_yield_boost_MPi_Cut")->Clone ("h_jet_pt_yield_boost_MPi_Cut");

  h_jet_yield_boost[2] = (TH1D*) inFile->Get ("h_jet_yield_boost_MPi_Cut")->Clone ("h_jet_boost_MPi_Cut");

  h_trk_pt_ns_yield_ratio[2] = (TH1D*) h_trk_pt_ns_yield_boost[2]->Clone ("h_trk_pt_ns_ratio_MPi_Cut");
  h_trk_pt_ns_yield_ratio[2]->Divide (h_trk_pt_ns_yield[2]);
  h_trk_pt_as_yield_ratio[2] = (TH1D*) h_trk_pt_as_yield_boost[2]->Clone ("h_trk_pt_as_ratio_MPi_Cut");
  h_trk_pt_as_yield_ratio[2]->Divide (h_trk_pt_as_yield[2]);

  h_trk_dphi_pt_gt2_yield_ratio[2] = (TH1D*) h_trk_dphi_pt_gt2_yield_boost[2]->Clone ("h_trk_dphi_pt_gt2_ratio_MPi_Cut");
  h_trk_dphi_pt_gt2_yield_ratio[2]->Divide (h_trk_dphi_pt_gt2_yield[2]);
  h_trk_dphi_pt_lt2_yield_ratio[2] = (TH1D*) h_trk_dphi_pt_lt2_yield_boost[2]->Clone ("h_trk_dphi_pt_lt2_ratio_MPi_Cut");
  h_trk_dphi_pt_lt2_yield_ratio[2]->Divide (h_trk_dphi_pt_lt2_yield[2]);

  h_jet_pt_yield_ratio[2] = (TH1D*) h_jet_pt_yield_boost[2]->Clone ("h_jet_pt_ratio_MPi_Cut");
  h_jet_pt_yield_ratio[2]->Divide (h_jet_pt_yield[2]);




  inFile = new TFile ("rootFiles/NoBoost/hists_MPro_Cut.root", "read");

  h_trk_pt_ns_yield[3] = (TH1D*) inFile->Get ("h_trk_pt_ns_yield_MPro_Cut")->Clone ("h_trk_pt_ns_MPro_Cut");
  h_trk_pt_as_yield[3] = (TH1D*) inFile->Get ("h_trk_pt_as_yield_MPro_Cut")->Clone ("h_trk_pt_as_MPro_Cut");

  h_trk_dphi_pt_gt2_yield[3] = (TH1D*) inFile->Get ("h_trk_dphi_pt_gt2_yield_MPro_Cut")->Clone ("h_trk_dphi_pt_gt2_MPro_Cut");
  h_trk_dphi_pt_lt2_yield[3] = (TH1D*) inFile->Get ("h_trk_dphi_pt_lt2_yield_MPro_Cut")->Clone ("h_trk_dphi_pt_lt2_MPro_Cut");

  h_jet_pt_yield[3] = (TH1D*) inFile->Get ("h_jet_pt_yield_MPro_Cut")->Clone ("h_jet_pt_MPro_Cut");

  h_jet_yield[3] = (TH1D*) inFile->Get ("h_jet_yield_MPro_Cut")->Clone ("h_jet_MPro_Cut");


  inFile = new TFile ("rootFiles/Boost_0p465/hists_MPro_Cut.root", "read");

  h_trk_pt_ns_yield_boost[3] = (TH1D*) inFile->Get ("h_trk_pt_ns_yield_boost_MPro_Cut")->Clone ("h_trk_pt_ns_boost_MPro_Cut");
  h_trk_pt_as_yield_boost[3] = (TH1D*) inFile->Get ("h_trk_pt_as_yield_boost_MPro_Cut")->Clone ("h_trk_pt_as_boost_MPro_Cut");

  h_trk_dphi_pt_gt2_yield_boost[3] = (TH1D*) inFile->Get ("h_trk_dphi_pt_gt2_yield_boost_MPro_Cut")->Clone ("h_trk_dphi_pt_gt2_boost_MPro_Cut");
  h_trk_dphi_pt_lt2_yield_boost[3] = (TH1D*) inFile->Get ("h_trk_dphi_pt_lt2_yield_boost_MPro_Cut")->Clone ("h_trk_dphi_pt_lt2_boost_MPro_Cut");

  h_jet_pt_yield_boost[3] = (TH1D*) inFile->Get ("h_jet_pt_yield_boost_MPro_Cut")->Clone ("h_jet_pt_yield_boost_MPro_Cut");

  h_jet_yield_boost[3] = (TH1D*) inFile->Get ("h_jet_yield_boost_MPro_Cut")->Clone ("h_jet_boost_MPro_Cut");

  h_trk_pt_ns_yield_ratio[3] = (TH1D*) h_trk_pt_ns_yield_boost[3]->Clone ("h_trk_pt_ns_ratio_MPro_Cut");
  h_trk_pt_ns_yield_ratio[3]->Divide (h_trk_pt_ns_yield[3]);
  h_trk_pt_as_yield_ratio[3] = (TH1D*) h_trk_pt_as_yield_boost[3]->Clone ("h_trk_pt_as_ratio_MPro_Cut");
  h_trk_pt_as_yield_ratio[3]->Divide (h_trk_pt_as_yield[3]);

  h_trk_dphi_pt_gt2_yield_ratio[3] = (TH1D*) h_trk_dphi_pt_gt2_yield_boost[3]->Clone ("h_trk_dphi_pt_gt2_ratio_MPro_Cut");
  h_trk_dphi_pt_gt2_yield_ratio[3]->Divide (h_trk_dphi_pt_gt2_yield[3]);
  h_trk_dphi_pt_lt2_yield_ratio[3] = (TH1D*) h_trk_dphi_pt_lt2_yield_boost[3]->Clone ("h_trk_dphi_pt_lt2_ratio_MPro_Cut");
  h_trk_dphi_pt_lt2_yield_ratio[3]->Divide (h_trk_dphi_pt_lt2_yield[3]);

  h_jet_pt_yield_ratio[3] = (TH1D*) h_jet_pt_yield_boost[3]->Clone ("h_jet_pt_ratio_MPro_Cut");
  h_jet_pt_yield_ratio[3]->Divide (h_jet_pt_yield[3]);





  {
    const char* canvasName = "c_trk_pt_yield";
    TCanvas* c = new TCanvas (canvasName, "", 800, 800);
    TPad* uPad = new TPad (Form ("%s_uPad", canvasName), "", 0.0, 0.4, 1.0, 1.0);
    TPad* dPad = new TPad (Form ("%s_dPad", canvasName), "", 0.0, 0.0, 1.0, 0.4);

    uPad->SetBottomMargin (0);
    dPad->SetTopMargin (0);
    dPad->SetBottomMargin (0.25);
    uPad->Draw ();
    dPad->Draw ();

    TH1D* h = nullptr; 
    TGAE* g = nullptr;

    uPad->cd (); 
    uPad->SetLogx ();
    uPad->SetLogy ();

    float ymin = 2e-6;
    float ymax = 10;

    h = (TH1D*) h_trk_pt_ns_yield[0]->Clone ("h");
    h->Reset ();
    h->GetYaxis ()->SetRangeUser (ymin, ymax);
    h->GetXaxis ()->SetTitle ("#it{p}_{T}^{ch} [GeV]");
    h->GetXaxis ()->SetTitleSize (0.04/0.6);
    h->GetXaxis ()->SetLabelSize (0.04/0.6);
    h->GetXaxis ()->SetTitleOffset (1.5*0.6);
    h->GetYaxis ()->SetTitle ("d^{2}N_{ch} / d#it{p}_{T} #Delta#phi [GeV^{-1}]");
    h->GetYaxis ()->SetTitle ("(1/N_{jet}) (d^{2}N_{ch} / d#it{p}_{T}^{ch} d#Delta#phi_{ch,jet}) [GeV^{-1}]");
    h->GetYaxis ()->SetTitleSize (0.04/0.6);
    h->GetYaxis ()->SetLabelSize (0.04/0.6);
    h->GetYaxis ()->SetTitleOffset (1.5*0.6);

    h->SetLineWidth (0);
    h->DrawCopy ("hist ][");
    SaferDelete (&h);

    h = (TH1D*) h_trk_pt_ns_yield[0]->Clone ("h");
    h->SetLineColor (colors[0]);
    h->SetLineWidth (2);
    h->DrawCopy ("hist ][ same");
    g = make_graph (h);
    g->SetMarkerStyle (kFullCircle);
    g->SetMarkerSize (0.8);
    g->SetMarkerColor (colors[0]);
    g->SetLineColor (colors[0]);
    g->SetLineWidth (2);
    ((TGAE*) g->Clone ())->Draw ("p");
    g->SetMarkerStyle (kOpenCircle);
    g->SetMarkerColor (kBlack);
    g->SetLineWidth (0);
    ((TGAE*) g->Clone ())->Draw ("p");
    SaferDelete (&h);
    SaferDelete (&g);

    h = (TH1D*) h_trk_pt_ns_yield_boost[0]->Clone ("h");
    h->SetLineColor (colors[1]);
    h->SetLineWidth (2);
    h->DrawCopy ("hist ][ same");
    g = make_graph (h);
    g->SetMarkerStyle (kFullCircle);
    g->SetMarkerSize (0.8);
    g->SetMarkerColor (colors[1]);
    g->SetLineColor (colors[1]);
    g->SetLineWidth (2);
    ((TGAE*) g->Clone ())->Draw ("p");
    g->SetMarkerStyle (kOpenCircle);
    g->SetMarkerColor (kBlack);
    g->SetLineWidth (0);
    ((TGAE*) g->Clone ())->Draw ("p");
    SaferDelete (&h);
    SaferDelete (&g);


    h = (TH1D*) h_trk_pt_ns_yield[1]->Clone ("h");
    h->SetLineColor (colors[2]);
    h->SetLineWidth (2);
    h->DrawCopy ("hist ][ same");
    g = make_graph (h);
    g->SetMarkerStyle (kFullSquare);
    g->SetMarkerSize (0.8);
    g->SetMarkerColor (colors[2]);
    g->SetLineColor (colors[2]);
    g->SetLineWidth (2);
    ((TGAE*) g->Clone ())->Draw ("p");
    g->SetMarkerStyle (kOpenSquare);
    g->SetMarkerColor (kBlack);
    g->SetLineWidth (0);
    ((TGAE*) g->Clone ())->Draw ("p");
    SaferDelete (&h);
    SaferDelete (&g);

    h = (TH1D*) h_trk_pt_ns_yield_boost[1]->Clone ("h");
    h->SetLineColor (colors[3]);
    h->SetLineWidth (2);
    h->DrawCopy ("hist ][ same");
    g = make_graph (h);
    g->SetMarkerStyle (kFullSquare);
    g->SetMarkerSize (0.8);
    g->SetMarkerColor (colors[3]);
    g->SetLineColor (colors[3]);
    g->SetLineWidth (2);
    ((TGAE*) g->Clone ())->Draw ("p");
    g->SetMarkerStyle (kOpenSquare);
    g->SetMarkerColor (kBlack);
    g->SetLineWidth (0);
    ((TGAE*) g->Clone ())->Draw ("p");
    SaferDelete (&h);
    SaferDelete (&g);


    h = (TH1D*) h_trk_pt_ns_yield[2]->Clone ("h");
    h->SetLineColor (colors[4]);
    h->SetLineWidth (2);
    h->DrawCopy ("hist ][ same");
    g = make_graph (h);
    g->SetMarkerStyle (kFullDiamond);
    g->SetMarkerSize (0.8);
    g->SetMarkerColor (colors[4]);
    g->SetLineColor (colors[4]);
    g->SetLineWidth (2);
    ((TGAE*) g->Clone ())->Draw ("p");
    g->SetMarkerStyle (kOpenDiamond);
    g->SetMarkerColor (kBlack);
    g->SetLineWidth (0);
    ((TGAE*) g->Clone ())->Draw ("p");
    SaferDelete (&h);
    SaferDelete (&g);

    h = (TH1D*) h_trk_pt_ns_yield_boost[2]->Clone ("h");
    h->SetLineColor (colors[5]);
    h->SetLineWidth (2);
    h->DrawCopy ("hist ][ same");
    g = make_graph (h);
    g->SetMarkerStyle (kFullDiamond);
    g->SetMarkerSize (0.8);
    g->SetMarkerColor (colors[5]);
    g->SetLineColor (colors[5]);
    g->SetLineWidth (2);
    ((TGAE*) g->Clone ())->Draw ("p");
    g->SetMarkerStyle (kOpenDiamond);
    g->SetMarkerColor (kBlack);
    g->SetLineWidth (0);
    ((TGAE*) g->Clone ())->Draw ("p");
    SaferDelete (&h);
    SaferDelete (&g);


    h = (TH1D*) h_trk_pt_ns_yield[3]->Clone ("h");
    h->SetLineColor (colors[6]);
    h->SetLineWidth (2);
    h->DrawCopy ("hist ][ same");
    g = make_graph (h);
    g->SetMarkerStyle (kFullCross);
    g->SetMarkerSize (0.8);
    g->SetMarkerColor (colors[6]);
    g->SetLineColor (colors[6]);
    g->SetLineWidth (2);
    ((TGAE*) g->Clone ())->Draw ("p");
    g->SetMarkerStyle (kOpenCross);
    g->SetMarkerColor (kBlack);
    g->SetLineWidth (0);
    ((TGAE*) g->Clone ())->Draw ("p");
    SaferDelete (&h);
    SaferDelete (&g);

    h = (TH1D*) h_trk_pt_ns_yield_boost[3]->Clone ("h");
    h->SetLineColor (colors[7]);
    h->SetLineWidth (2);
    h->DrawCopy ("hist ][ same");
    g = make_graph (h);
    g->SetMarkerStyle (kFullCross);
    g->SetMarkerSize (0.8);
    g->SetMarkerColor (colors[7]);
    g->SetLineColor (colors[7]);
    g->SetLineWidth (2);
    ((TGAE*) g->Clone ())->Draw ("p");
    g->SetMarkerStyle (kOpenCross);
    g->SetMarkerColor (kBlack);
    g->SetLineWidth (0);
    ((TGAE*) g->Clone ())->Draw ("p");
    SaferDelete (&h);
    SaferDelete (&g);

    myText (0.20, 0.380, kBlack, "#bf{Pythia 8.303}, #it{pp}, #sqrt{s} = 5.02 TeV", 0.028/0.6);
    myText (0.20, 0.320, kBlack, "#it{p}_{T}^{jet} > 60 GeV, #Delta#phi_{ch,jet} > 7#pi/8", 0.028/0.6);
    myText (0.31, 0.260, kBlack, "#Deltay = 0", 0.024/0.6);
    myText (0.41, 0.260, kBlack, "#Deltay = +0.465", 0.024/0.6);
    myText (0.20, 0.205, kBlack, "No cut", 0.024/0.6);
    myText (0.20, 0.150, kBlack, "Massless", 0.024/0.6);
    myText (0.20, 0.095, kBlack, "m = m_{#pi}", 0.024/0.6);
    myText (0.20, 0.040, kBlack, "m = m_{p}", 0.024/0.6);
    myMarkerText (0.38, 0.205, colors[0], kFullCircle, "", 1.2, 0.028/0.6, true);
    myMarkerText (0.50, 0.205, colors[1], kFullCircle, "", 1.2, 0.028/0.6, true);
    myMarkerText (0.38, 0.150, colors[2], kFullSquare, "", 1.2, 0.028/0.6, true);
    myMarkerText (0.50, 0.150, colors[3], kFullSquare, "", 1.2, 0.028/0.6, true);
    myMarkerText (0.38, 0.095, colors[4], kFullDiamond, "", 1.2, 0.028/0.6, true);
    myMarkerText (0.50, 0.095, colors[5], kFullDiamond, "", 1.2, 0.028/0.6, true);
    myMarkerText (0.38, 0.040, colors[6], kFullCross, "", 1.2, 0.028/0.6, true);
    myMarkerText (0.50, 0.040, colors[7], kFullCross, "", 1.2, 0.028/0.6, true);


    dPad->cd (); 
    dPad->SetLogx ();

    ymin = 0.84;
    ymax = 1.16;

    h = (TH1D*) h_trk_pt_ns_yield_ratio[0]->Clone ("h");
    h->Reset ();
    for (int i = 1; i <= h->GetNbinsX (); i++) h->SetBinContent (i, 1);
    h->GetXaxis ()->SetMoreLogLabels ();
    h->GetYaxis ()->SetRangeUser (ymin, ymax);
    h->GetXaxis ()->SetTitle ("#it{p}_{T}^{ch} [GeV]");
    h->GetXaxis ()->SetTitleSize (0.04/0.4);
    h->GetXaxis ()->SetLabelSize (0.04/0.4);
    h->GetXaxis ()->SetTitleOffset (2.7*0.4);
    h->GetXaxis ()->SetLabelOffset (-0.04*0.4);
    h->GetYaxis ()->SetTitle ("Boost / No boost");
    h->GetYaxis ()->SetTitleSize (0.04/0.4);
    h->GetYaxis ()->SetLabelSize (0.04/0.4);
    h->GetYaxis ()->SetTitleOffset (1.5*0.4);
    h->GetYaxis ()->CenterTitle ();

    h->SetLineWidth (1);
    h->SetLineStyle (2);
    h->DrawCopy ("hist ][");
    SaferDelete (&h);

    h = (TH1D*) h_trk_pt_ns_yield_ratio[0];
    g = make_graph (h);
    g->SetLineColor (colors[1]);
    g->SetLineWidth (2);
    g->SetMarkerColor (colors[1]);
    g->SetMarkerStyle (kFullCircle);
    g->SetMarkerSize (0.8);
    ((TGAE*) g->Clone ())->Draw ("p");
    g->SetMarkerStyle (kOpenCircle);
    g->SetMarkerColor (kBlack);
    g->SetLineWidth (0);
    ((TGAE*) g->Clone ())->Draw ("p");
    SaferDelete (&g);

    h = (TH1D*) h_trk_pt_ns_yield_ratio[1];
    g = make_graph (h);
    g->SetLineColor (colors[3]);
    g->SetLineWidth (2);
    g->SetMarkerColor (colors[3]);
    g->SetMarkerStyle (kFullSquare);
    g->SetMarkerSize (0.8);
    ((TGAE*) g->Clone ())->Draw ("p");
    g->SetMarkerStyle (kOpenSquare);
    g->SetMarkerColor (kBlack);
    g->SetLineWidth (0);
    ((TGAE*) g->Clone ())->Draw ("p");
    SaferDelete (&g);

    h = (TH1D*) h_trk_pt_ns_yield_ratio[2];
    g = make_graph (h);
    g->SetLineColor (colors[5]);
    g->SetLineWidth (2);
    g->SetMarkerColor (colors[5]);
    g->SetMarkerStyle (kFullDiamond);
    g->SetMarkerSize (0.8);
    ((TGAE*) g->Clone ())->Draw ("p");
    g->SetMarkerStyle (kOpenDiamond);
    g->SetMarkerColor (kBlack);
    g->SetLineWidth (0);
    ((TGAE*) g->Clone ())->Draw ("p");
    SaferDelete (&g);

    h = (TH1D*) h_trk_pt_ns_yield_ratio[3];
    g = make_graph (h);
    g->SetLineColor (colors[7]);
    g->SetLineWidth (2);
    g->SetMarkerColor (colors[7]);
    g->SetMarkerStyle (kFullCross);
    g->SetMarkerSize (0.8);
    ((TGAE*) g->Clone ())->Draw ("p");
    g->SetMarkerStyle (kOpenCross);
    g->SetMarkerColor (kBlack);
    g->SetLineWidth (0);
    ((TGAE*) g->Clone ())->Draw ("p");
    SaferDelete (&g);

    c->SaveAs ("Plots/Ptch_yields_comparison.pdf"); 
  }




  return 0;
}


void plotter () {
  main ();
}
