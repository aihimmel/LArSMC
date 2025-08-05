#include <iostream>
#include <vector>
#include <string>

#include "TROOT.h"
#include "TFile.h"
#include "TTree.h"
#include "TH1D.h"
#include "TCanvas.h"
#include "TSystem.h"

#include "Track_h2d22cm_128nm.h"
#include "Track_h5d23cm_128nm.h"
#include "Track_h10d31cm_128nm.h"
#include "Track_h17d93cm_128nm.h"
#include "Track_h25d34cm_128nm.h"
#include "Track_h28d09cm_128nm.h"
#include "Track_h38d25cm_128nm.h"
#include "Track_h40d79cm_128nm.h"
#include "Track_h50d97cm_128nm.h"
#include "Track_h63d65cm_128nm.h"
#include "Track_h76d33cm_128nm.h"
#include "Track_h89d05cm_128nm.h"
#include "Track_h101d83cm_128nm.h"
#include "Track_h127d22cm_128nm.h"

void HistoPhotonsVsR2_128nm()
{
    gROOT->ProcessLine(".L Track_h2d22cm_128nm.C"); gROOT->ProcessLine("Track_h2d22cm_128nm h2d22"); gROOT->ProcessLine("h2d22.Loop()");
    gROOT->ProcessLine(".L Track_h5d23cm_128nm.C"); gROOT->ProcessLine("Track_h5d23cm_128nm h5d23"); gROOT->ProcessLine("h5d23.Loop()");
    gROOT->ProcessLine(".L Track_h10d31cm_128nm.C"); gROOT->ProcessLine("Track_h10d31cm_128nm h10d31"); gROOT->ProcessLine("h10d31.Loop()");
    gROOT->ProcessLine(".L Track_h17d93cm_128nm.C"); gROOT->ProcessLine("Track_h17d93cm_128nm h17d93"); gROOT->ProcessLine("h17d93.Loop()");
    gROOT->ProcessLine(".L Track_h25d34cm_128nm.C"); gROOT->ProcessLine("Track_h25d34cm_128nm h25d34"); gROOT->ProcessLine("h25d34.Loop()");
    gROOT->ProcessLine(".L Track_h28d09cm_128nm.C"); gROOT->ProcessLine("Track_h28d09cm_128nm h28d09"); gROOT->ProcessLine("h28d09.Loop()");
    gROOT->ProcessLine(".L Track_h38d25cm_128nm.C"); gROOT->ProcessLine("Track_h38d25cm_128nm h38d25"); gROOT->ProcessLine("h38d25.Loop()");
    gROOT->ProcessLine(".L Track_h40d79cm_128nm.C"); gROOT->ProcessLine("Track_h40d79cm_128nm h40d79"); gROOT->ProcessLine("h40d79.Loop()");
    gROOT->ProcessLine(".L Track_h50d97cm_128nm.C"); gROOT->ProcessLine("Track_h50d97cm_128nm h50d97"); gROOT->ProcessLine("h50d97.Loop()");
    gROOT->ProcessLine(".L Track_h63d65cm_128nm.C"); gROOT->ProcessLine("Track_h63d65cm_128nm h63d65"); gROOT->ProcessLine("h63d65.Loop()");
    gROOT->ProcessLine(".L Track_h76d33cm_128nm.C"); gROOT->ProcessLine("Track_h76d33cm_128nm h76d33"); gROOT->ProcessLine("h76d33.Loop()");
    gROOT->ProcessLine(".L Track_h89d05cm_128nm.C"); gROOT->ProcessLine("Track_h89d05cm_128nm h89d05"); gROOT->ProcessLine("h89d05.Loop()");
    gROOT->ProcessLine(".L Track_h101d83cm_128nm.C"); gROOT->ProcessLine("Track_h101d83cm_128nm h101d83"); gROOT->ProcessLine("h101d83.Loop()");
    gROOT->ProcessLine(".L Track_h127d22cm_128nm.C"); gROOT->ProcessLine("Track_h127d22cm_128nm h127d22"); gROOT->ProcessLine("h127d22.Loop()");

    std::vector<std::string> file_names = {"PhotonCount_vs_r2_2d22_128nm.root", "PhotonCount_vs_r2_5d23_128nm.root", "PhotonCount_vs_r2_10d31_128nm.root", "PhotonCount_vs_r2_17d93_128nm.root", "PhotonCount_vs_r2_25d34_128nm.root", "PhotonCount_vs_r2_28d09_128nm.root", "PhotonCount_vs_r2_38d25_128nm.root", "PhotonCount_vs_r2_40d79_128nm.root", "PhotonCount_vs_r2_50d97_128nm.root", "PhotonCount_vs_r2_63d65_128nm.root", "PhotonCount_vs_r2_76d33_128nm.root", "PhotonCount_vs_r2_89d05_128nm.root", "PhotonCount_vs_r2_101d83_128nm.root", "PhotonCount_vs_r2_127d22_128nm.root"};

    TCanvas *main = new TCanvas("canvas", "Photons vs. r^2", 800, 600);

    for (int i = 0; i < 14; i++)
    {
        std::string file_path = "/nashome/a/abreaux/Downloads/larsmc_128nm/";
        std::string filee = file_path + file_names[i];

        TFile *file = TFile::Open(filee.c_str());
        TCanvas *canvas = (TCanvas*)file->Get("canvas");
        TH1D *histogram = (TH1D*)canvas->GetPrimitive("h1");

        main->cd();
        histogram->SetLineColor(i + 2);
        if (file_names[i] == "PhotonCount_vs_r2_2d22_128nm.root")
        {
            histogram->Draw();
        }
        else
        {
            histogram->Draw("SAME");
        }

        file->Close();
    }

    main->Update();
    std::string plot_name = "/nashome/a/abreaux/Downloads/larsmc_128nm/PhotonCount_vs_r2_128nm.root";
    main->SaveAs(plot_name.c_str());
    delete main;

    return;
} 