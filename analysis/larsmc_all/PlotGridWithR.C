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
#include "TGraphErrors.h"

///// Globals /////

int n = 14; // Number of HLAr values
int o = 7; // Number of wavelengths

std::string infile_name = "/Users/autobreaux/LArSMC/analysis/larsmc_all/TrackOutfile.root";
std::string HLAr_names[14] = {"h2d22cm", "h5d23cm", "h10d31cm", "h17d93cm", "h25d34cm", "h28d09cm", "h38d25cm", "h40d79cm", "h50d97cm", "h63d65cm", "h76d33cm", "h89d05cm", "h101d83cm", "h127d22cm"};
std::string wavelength_names[7] = {"115nm", "125nm", "128nm", "135nm", "140nm", "150nm", "155nm"};
std::vector<std::string> r_range_names = {"0to3mm", "3to6mm", "6to9mm", "9to12mm", "12to15mm", "15to18mm", "18to21mm", "21to24mm", "24to27mm", "27to30mm", "30to33mm", "33to36mm", "36to39mm", "39to42mm", "42to45mm", "45to48mm", "48to51mm", "51to54mm", "54to57mm", "57to60mm", "60to63mm", "63to66mm", "66to69mm", "69to72mm", "72to75mm", "75to78mm", "78to81mm", "81to84mm", "84to87mm", "87to90mm", "90to93mm", "93to96mm", "96to99mm"};

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

void PlotGridWithR()
{
    std::string file_path12 = "/Users/autobreaux/LArSMC_Downloads/larsmc_all/PCvsR2wRealData_";
    std::string file_path34 = "/Users/autobreaux/LArSMC_Downloads/larsmc_all/GridPCvsHLAr_";
    
    for (int i = 0; i < o; i++)
    {
        std::string file1 = file_path12 + wavelength_names[i] + "12to15mm.root";
        std::string file2 = file_path12 + wavelength_names[i] + "15to18mm.root";
        std::string file3 = file_path34 + wavelength_names[i] + "_0deg.root";
        std::string file4 = file_path34 + wavelength_names[i] + "_45deg.root";

        TFile *datafile1 = TFile::Open(file1.c_str());
        TCanvas *ctemp1 = (TCanvas*)datafile1->Get("canvas");
        TGraphErrors *greal1 = (TGraphErrors*)ctemp1->GetPrimitive("greal");
        TGraph *gsim1 = (TGraph*)ctemp1->GetPrimitive("gsim");
        datafile1->Close();

        TFile *datafile2 = TFile::Open(file2.c_str());
        TCanvas *ctemp2 = (TCanvas*)datafile2->Get("canvas");
        TGraph *gsim2 = (TGraph*)ctemp2->GetPrimitive("gsim");
        datafile2->Close();

        TFile *datafile3 = TFile::Open(file3.c_str());
        TCanvas *ctemp3 = (TCanvas*)datafile3->Get("canvas"); 
        TGraph *gsquare0deg = (TGraph*)ctemp3->GetPrimitive("g");
        datafile3->Close();

        TFile *datafile4 = TFile::Open(file4.c_str());
        TCanvas *ctemp4 = (TCanvas*)datafile4->Get("canvas");
        TGraph *gsquare45deg = (TGraph*)ctemp4->GetPrimitive("g");
        datafile4->Close();

        gsim2->SetLineColor(kGreen);

        // Scale the grid data graph;
        double PC_square0deg[14];
        double PC_square45deg[14];
        if (wavelength_names[i] == "115nm" || wavelength_names[i] == "125nm" || wavelength_names[i] == "128nm")
        {
            for(int j = 0; j < n; j++) { PC_square0deg[j] = (gsquare0deg->GetPointY(j) / 150.0); }
            for(int j = 0; j < n; j++) { PC_square45deg[j] = (gsquare45deg->GetPointY(j) / 150.0); }
        }
        else 
        {
            for(int j = 0; j < n; j++) { PC_square0deg[j] = (gsquare0deg->GetPointY(j) / 100.0); }
            for(int j = 0; j < n; j++) { PC_square45deg[j] = (gsquare45deg->GetPointY(j) / 100.0); }
        }

        TCanvas *canvas = new TCanvas("canvas", "c", 800, 600);
        TLegend *legend = new TLegend(0.532581, 0.666667, 0.885965, 0.881944, "h", "brNDC");
        legend->SetHeader("Legend", "C");

        TGraph *gsquare0deg_weighted = new TGraph(14, HLAr_sim, PC_square0deg);
        std::string gname = ";HLAr (cm);Scaled Photon Count";
        gsquare0deg_weighted->SetTitle(gname.c_str());
        gsquare0deg_weighted->GetYaxis()->SetRangeUser(0, 200);
        gsquare0deg_weighted->SetLineColor(kViolet+2);
        gsquare0deg_weighted->SetLineStyle(2);
        gsquare0deg_weighted->SetLineWidth(2);
        gsquare0deg_weighted->Draw("AL");
        legend->AddEntry(gsquare0deg_weighted, "Square Detector Data - 0 degrees", "l");

        TGraph *gsquare45deg_weighted = new TGraph(14, HLAr_sim, PC_square45deg);
        gsquare45deg_weighted->SetLineColor(kPink+10);
        gsquare45deg_weighted->SetLineStyle(2);
        gsquare45deg_weighted->SetLineWidth(2);
        gsquare45deg_weighted->Draw("L");
        legend->AddEntry(gsquare45deg_weighted, "Square Detector Data - 45 degrees", "l");

        greal1->SetMarkerSize(2);
        greal1->Draw("P");
        gsim1->Draw("L");
        gsim2->Draw("L");

        legend->AddEntry(greal1, "Experimental Data", "p");
        legend->AddEntry(gsim1, "Ring Detector Data - 12 to 15 mm", "l");
        legend->AddEntry(gsim2, "Ring Detector Data - 15 to 18 mm", "l");

        // if (wavelength_names[i] == "115nm" || wavelength_names[i] == "125nm" || wavelength_names[i] == "128nm") { legend->AddEntry((TObject*)0, "Square Detector Data reduced by a factor of 150 ", ""); }
        // else { legend->AddEntry((TObject*)0, "Square Detector Data reduced by a factor of 100 ", ""); }

        legend->Draw();
        canvas->Update();
        std::string outfile = "/Users/autobreaux/LArSMC_Downloads/larsmc_all/PCvsHLAr_SRE_" + wavelength_names[i] + ".root";
        canvas->Print(outfile.c_str());
    }
}