#include <iostream>
#include <vector>
#include <array>
#include <string>

#include "TROOT.h"
#include "TFile.h"
#include "TTree.h"
#include "TH2D.h"
#include "TCanvas.h"
#include "TGraph.h"
#include "TLegend.h"

#include "Track.h"

void GridMaker()
{
    // gROOT->ProcessLine(".L Track.C+");

    std::string filepath = "/exp/dune/data/users/abreaux/larsmc_";
    std::string HLAr_names[14] = {"h2d22cm", "h5d23cm", "h10d31cm", "h17d93cm", "h25d34cm", "h28d09cm", "h38d25cm", "h40d79cm", "h50d97cm", "h63d65cm", "h76d33cm", "h89d05cm", "h101d83cm", "h127d22cm"};
    std::string wavelength_names[7] = {"115nm", "125nm", "128nm", "135nm", "140nm", "150nm", "155nm"};

    TFile *fout = new TFile("TrackOutfile.root", "RECREATE");

    for (int i = 0; i < 14; i++) // Loop through heights
    {
        std::cout << "Looping through wavelengths at HLAr = " << HLAr_names[i] << std::endl; 
        for (int j = 0; j < 7; j++) // Loop through wavelengths
        {   
            std::cout << "Wavelength = " <<  wavelength_names[j] << std::endl;
            std::string filename = filepath + HLAr_names[i] + "_" + wavelength_names[j] + ".root";
            std::string histname = "h" + HLAr_names[i] + "_" + wavelength_names[j];

            Track t(filename);
            TH2D *grid = t.Loop();

            fout->cd();
            grid->Write(histname.c_str());
        }
    }

    fout->Close();
}

