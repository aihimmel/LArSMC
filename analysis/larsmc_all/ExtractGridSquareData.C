#include <iostream>
#include <vector>
#include <string>
#include <cmath>

#include "TStyle.h"
#include "TROOT.h"
#include "TFile.h"
#include "TCanvas.h"
#include "TGraph.h"
#include "TLegend.h"
#include "TH2D.h"

///// Globals /////

int n = 14; // Number of HLAr values
int o = 7; // Number of wavelengths

std::string infile_name = "/Users/autobreaux/LArSMC/analysis/larsmc_all/TrackOutfile.root";
std::string HLAr_names[14] = {"h2d22cm", "h5d23cm", "h10d31cm", "h17d93cm", "h25d34cm", "h28d09cm", "h38d25cm", "h40d79cm", "h50d97cm", "h63d65cm", "h76d33cm", "h89d05cm", "h101d83cm", "h127d22cm"};
std::string wavelength_names[7] = {"115nm", "125nm", "128nm", "135nm", "140nm", "150nm", "155nm"};

double HLAr_sim[14] = {2.22, 5.23, 10.31, 17.93, 25.34, 28.09, 38.25, 40.79, 50.97, 63.65, 76.33, 89.05, 101.83, 127.22}; 

// Extracted grid squared for cardinal directions
double x_cardinal[6] = {85.0, 86.0, 87.0, 88.0, 89.0, 90.0};
double y_cardinal[6] = {-2.5, -1.5, -0.5, 0.5, 1.5, 2.5};

// Extracted grid squares for intercardinal directions
// double x_intercardinal[7] = {84.5, 85.5, 86.5, 87.5, 88.5, 89.5, 90.5};
// double y_intercardinal[7] = {-3.0, -2.0, -1.0, 0.0, 1.0, 2.0, 3.0};

double r = 15.0; // Distance in mm from directly under photon source (87.5 mm, 0 mm)
double theta[8] = {0, M_PI_4, M_PI_2, M_PI_2 + M_PI_4, M_PI, -1.0 * M_PI + M_PI_4, -1.0 * M_PI + M_PI_2, -1.0 * M_PI + M_PI_2 + M_PI_4}; // Angles of shapes from x axis

///////////////////

void GraphGridVisuals(std::string wavelength_name, std::vector<double> opdet0, std::vector<double> opdet1, std::vector<double> opdet2, std::vector<double> opdet3, std::vector<double> opdet4, std::vector<double> opdet5, std::vector<double> opdet6, std::vector<double> opdet7)
{
    double PC_0[14]; // n = 14
    double PC_45[14]; // n = 14
    double PC_90[14]; // n = 14
    double PC_135[14]; // n = 14
    double PC_180[14]; // n = 14
    double PC_225[14]; // n = 14
    double PC_270[14]; // n = 14
    double PC_315[14]; // n = 14

    for (int i = 0; i < 8; i++) // Loop through selected grid areas
    {
        std::vector<double> opdet;
        std::string opdet_ang;

        if (i == 0) 
        { 
            opdet = opdet0; 
            opdet_ang = "0deg"; 
            for (int j = 0; j < n; j++)
            {
                PC_0[j] = opdet[j];
            }
        }

        if (i == 1) 
        { 
            opdet = opdet1; 
            opdet_ang = "45deg"; 
            for (int j = 0; j < n; j++)
            {
                PC_45[j] = opdet[j];
            }
        }

        if (i == 2) 
        { 
            opdet = opdet2; 
            opdet_ang = "90deg"; 
            for (int j = 0; j < n; j++)
            {
                PC_90[j] = opdet[j];
            }
        }

        if (i == 3) 
        { 
            opdet = opdet3; 
            opdet_ang = "135deg"; 
            for (int j = 0; j < n; j++)
            {
                PC_135[j] = opdet[j];
            }
        }

        if (i == 4) 
        { 
            opdet = opdet4; 
            opdet_ang = "180deg"; 
            for (int j = 0; j < n; j++)
            {
                PC_180[j] = opdet[j];
            }
        }

        if (i == 5) 
        { 
            opdet = opdet5; 
            opdet_ang = "225deg"; 
            for (int j = 0; j < n; j++)
            {
                PC_225[j] = opdet[j];
            }
        }

        if (i == 6) 
        { 
            opdet = opdet6; 
            opdet_ang = "270deg"; 
            for (int j = 0; j < n; j++)
            {
                PC_270[j] = opdet[j];
            }
        }

        if (i == 7) 
        { 
            opdet = opdet7; 
            opdet_ang = "315deg"; 
            for (int j = 0; j < n; j++)
            {
                PC_315[j] = opdet[j];
            }
        }
    }

    TCanvas *c = new TCanvas("canvas", "c", 800, 600);
    TLegend *l = new TLegend(0.585213, 0.730903, 0.885965, 0.881944, "h", "brNDC");
    l->SetHeader("Azimuthal Angle (degrees)", "C");
    l->SetNColumns(2);

    // gStyle->SetPalette(kRainbow);
    // gStyle->SetNumberContours(8);

    TGraph *g1 = new TGraph(n, HLAr_sim, PC_0);
    g1->SetNameTitle("g1", ";LAr Height (cm);Photon Count");
    g1->SetMarkerStyle(20);
    g1->SetMarkerColor(kPink+10);
    g1->SetLineColor(kRed+4);
    g1->SetLineWidth(2);
    g1->Draw("AML");
    l->AddEntry(g1, "0", "l");

    TGraph *g2 = new TGraph(n, HLAr_sim, PC_45);
    g2->SetName("g2");
    g2->SetMarkerStyle(20);
    g2->SetMarkerColor(kRed);
    g2->SetLineColor(kRed);
    g2->SetLineWidth(2);
    g2->Draw("SAME ML");
    l->AddEntry(g2, "45", "l");

    TGraph *g3 = new TGraph(n, HLAr_sim, PC_90);
    g3->SetName("g3");
    g3->SetMarkerStyle(20);
    g3->SetMarkerColor(kOrange+10);
    g3->SetLineColor(kOrange+10);
    g3->SetLineWidth(2);
    g3->Draw("SAME ML");
    l->AddEntry(g3, "90", "l");

    TGraph *g4 = new TGraph(n, HLAr_sim, PC_135);
    g4->SetName("g4");
    g4->SetMarkerStyle(20);
    g4->SetMarkerColor(kYellow);
    g4->SetLineColor(kYellow);
    g4->SetLineWidth(2);
    g4->Draw("SAME ML");
    l->AddEntry(g4, "135", "l");

    TGraph *g5 = new TGraph(n, HLAr_sim, PC_180);
    g5->SetName("g5");
    g5->SetMarkerStyle(20);
    g5->SetMarkerColor(kGreen+1);
    g5->SetLineColor(kGreen+1);
    g5->SetLineWidth(2);
    g5->Draw("SAME ML");
    l->AddEntry(g5, "180", "l");

    TGraph *g6 = new TGraph(n, HLAr_sim, PC_225);
    g6->SetName("g6");
    g6->SetMarkerStyle(20);
    g6->SetMarkerColor(kAzure);
    g6->SetLineColor(kAzure);
    g6->SetLineWidth(2);
    g6->Draw("SAME ML");
    l->AddEntry(g6, "225", "l");

    TGraph *g7 = new TGraph(n, HLAr_sim, PC_270);
    g7->SetName("g7");
    g7->SetMarkerStyle(20);
    g7->SetMarkerColor(kMagenta);
    g7->SetLineColor(kMagenta);
    g7->SetLineWidth(2);
    g7->Draw("SAME ML");
    l->AddEntry(g7, "270", "l");

    TGraph *g8 = new TGraph(n, HLAr_sim, PC_315);
    g8->SetName("g8");
    g8->SetMarkerStyle(20);
    g8->SetMarkerColor(kTeal);
    g8->SetLineColor(kTeal);
    g8->SetLineWidth(2);
    g8->Draw("SAME ML");
    l->AddEntry(g8, "315", "l");

    l->Draw();
    std::string outfile_name = "/Users/autobreaux/LArSMC_Downloads/larsmc_all/GridPCvsHLAr_Overlay_" + wavelength_name + ".root";
    c->Update();
    c->Print(outfile_name.c_str());
    delete c;
}

void GraphPCvsHLAr(std::string wavelength_name, std::vector<double> opdet0, std::vector<double> opdet1, std::vector<double> opdet2, std::vector<double> opdet3, std::vector<double> opdet4, std::vector<double> opdet5, std::vector<double> opdet6, std::vector<double> opdet7)
{
    for (int i = 0; i < 8; i++) // Loop through selected grid areas
    {
        std::vector<double> opdet;
        std::string opdet_ang;
        if (i == 0) { opdet = opdet0; opdet_ang = "0deg"; }
        if (i == 1) { opdet = opdet1; opdet_ang = "45deg"; }
        if (i == 2) { opdet = opdet2; opdet_ang = "90deg"; }
        if (i == 3) { opdet = opdet3; opdet_ang = "135deg"; }
        if (i == 4) { opdet = opdet4; opdet_ang = "180deg"; }
        if (i == 5) { opdet = opdet5; opdet_ang = "225deg"; }
        if (i == 6) { opdet = opdet6; opdet_ang = "270deg"; }
        if (i == 7) { opdet = opdet7; opdet_ang = "315deg"; }

        double PC[14]; // n = 14
        for (int j = 0; j < n; j++)
        {
            PC[j] = opdet[j];
        }

        TCanvas *c = new TCanvas("canvas", "c", 800, 600);
        // TLegend *l = new TLegend(0.585213, 0.730903, 0.885965, 0.881944, "h", "brNDC");
        // l->SetHeader("Scattering Length (cm)", "C");

        TGraph *g = new TGraph(n, HLAr_sim, PC);
        g->SetNameTitle("g", ";LAr Height (cm);Photon Count");
        g->SetMarkerColor(kRed+4);
        g->SetMarkerStyle(20);
        g->SetLineColor(kRed+4);
        g->SetLineWidth(2);
        g->Draw("ALP");

        std::string outfile_name = "/Users/autobreaux/LArSMC_Downloads/larsmc_all/GridPCvsHLAr_" + wavelength_name + "_" + opdet_ang + ".root";
        c->Update();
        c->Print(outfile_name.c_str());
        delete c;
    }
}

void ExtractGridSquareData()
{
    TFile *mainfile = TFile::Open(infile_name.c_str());

    for (int i = 0; i < o; i++) // Loop through wavelengths
    {
        std::vector<double> opdet0;
        std::vector<double> opdet1;
        std::vector<double> opdet2;
        std::vector<double> opdet3;
        std::vector<double> opdet4;
        std::vector<double> opdet5;
        std::vector<double> opdet6;
        std::vector<double> opdet7;

        for (int j = 0; j < n; j++) // Loop through heights
        {
            std::string histogram_name = "h" + HLAr_names [j] + "_" + wavelength_names[i];
            TH2D *histogram = (TH2D*)mainfile->Get(histogram_name.c_str());

            for (int k = 0; k < 8; k++) // Loop radially for different grid extractions
            {
                double PC_opdet = 0.0;
                double delta_x = r * std::cos(theta[k]);
                double delta_y = r * std::sin(theta[k]);
                
                for (int l = 0; l < 6; l++) // Loop through x grid coordinates
                {
                    for (int m = 0; m < 6; m++) // Loop through y grid coordinates
                    {
                        double bin_x = x_cardinal[l] + delta_x;
                        double bin_y = y_cardinal[m] + delta_y;
                        int bin_num = histogram->FindBin(bin_x, bin_y);
                        PC_opdet += histogram->GetBinContent(bin_num);
                    }
                }

                if (k == 0) {opdet0.push_back(PC_opdet); }
                if (k == 1) {opdet1.push_back(PC_opdet); }
                if (k == 2) {opdet2.push_back(PC_opdet); }
                if (k == 3) {opdet3.push_back(PC_opdet); }
                if (k == 4) {opdet4.push_back(PC_opdet); }
                if (k == 5) {opdet5.push_back(PC_opdet); }
                if (k == 6) {opdet6.push_back(PC_opdet); }
                if (k == 7) {opdet7.push_back(PC_opdet); }
            }
        }   
    
        GraphPCvsHLAr(wavelength_names[i], opdet0, opdet1, opdet2, opdet3, opdet4, opdet5, opdet6, opdet7);
        GraphGridVisuals(wavelength_names[i], opdet0, opdet1, opdet2, opdet3, opdet4, opdet5, opdet6, opdet7);
    }
}

// IDEA FOR ROTATING SIPM AROUND CENTER
// if (k == 1 || k == 3 || k == 5 || k == 7)
//                 {
//                     for (int l = 0; l < 7; l++) // Loop through x-base grid coordinates
//                     {
//                         double bin_x = x_intercardinal[l] + delta_x;
//                         double bin_y = y_intercardinal[3] + delta_y;
//                         int bin_num = histogram->GetBin(bin_x, bin_y);
//                         PC_opdet += histogram->GetBinContent(bin_num);
//                     }

//                     for (int l = 0; l < 7; l++) // Loop through y-base grid coordinates
//                     {
//                         if (l != 3) // Skip the origin grid square to prevent repeating
//                         {
//                             double bin_x = x_intercardinal[3] + delta_x;
//                             double bin_y = y_intercardinal[l] + delta_y;
//                             int bin_num = histogram->GetBin(bin_x, bin_y);
//                             PC_opdet += histogram->GetBinContent(bin_num);
//                         }
//                     }

                    
//                 }