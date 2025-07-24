#include <iostream>
#include <vector>
#include <string>

#include "TROOT.h"
#include "TFile.h"
#include "TTree.h"
#include "TH1D.h"
#include "TCanvas.h"
#include "TGraph.h"
#include "TLegend.h"

void GraphTogether(std::vector<double> integrals_2d22, std::vector<double> integrals_5d23, std::vector<double> integrals_10d31, std::vector<double> integrals_17d93, std::vector<double> integrals_25d34, std::vector<double> integrals_28d09, std::vector<double> integrals_38d25, std::vector<double> integrals_40d79, std::vector<double> integrals_50d97, std::vector<double> integrals_63d65, std::vector<double> integrals_76d33, std::vector<double> integrals_89d05, std::vector<double> integrals_101d83, std::vector<double> integrals_127d22)
{
    std::string goutput_name = "/nashome/a/abreaux/Downloads/larsmc_129nm/gPhotonCount_vs_r2_129nm.root";

    TCanvas *cmain = new TCanvas("canvas", "Photons vs. r^2", 800, 600);

    TLegend *legend = new TLegend(0.487469, 0.611111 , 0.885965, 0.881944, "h", "brNDC");
    legend->SetHeader("r Ranges (mm)", "C");
    legend->SetNColumns(4);

    double HLAr[14] = {2.22, 5.23, 10.31, 17.93, 25.34, 28.09, 38.25, 40.79, 50.97, 63.65, 76.33, 89.05, 101.83, 127.22};
    int line_colors[33] = {632, 633, 635, 800, 801, 810, 401, 403, 830, 820, 813, 417, 420, 843, 834, 840, 434, 436, 861, 863, 867, 600, 602, 604, 878, 880, 890, 616, 618, 620, 906, 908, 910};
    std::string r_ranges[33] = {"[0,3]", "(3,6]", "(6,9]", "(9,12]", "(12,15]", "(15,18]", "(18,21]", "(21,24]", "(24,27]", "(27,30]", "(30,33]", "(33,36]", "(36,39]", "(39,42]", "(42,45]", "(45,48]", "(48,51]", "(51,54]", "(54,57]", "(57,60]", "(60,63]", "(63,66]", "(66,69]", "(69,72]", "(72,75]", "(75,78]", "(78,81]", "(81,84]", "(84,87]", "(87,90]", "(90,93]", "(93,96]", "(96,99]"};

    for(int i = 0; i < integrals_2d22.size(); i++)
    {
        double PhotonCount[14] = {integrals_2d22[i], integrals_5d23[i], integrals_10d31[i], integrals_17d93[i], integrals_25d34[i], integrals_28d09[i], integrals_38d25[i], integrals_40d79[i], integrals_50d97[i], integrals_63d65[i], integrals_76d33[i], integrals_89d05[i], integrals_101d83[i], integrals_127d22[i]};

        // Added for pretty plots
        if (i == 0) { for (int i = 0; i < 14; i ++) { PhotonCount[i] = PhotonCount[i] / 300.0; }}
        if (i == 1) { for (int i = 0; i < 14; i ++) { PhotonCount[i] = PhotonCount[i] / 5.0; }}

        cmain->cd();

        TGraph *gtemp = new TGraph(14, HLAr, PhotonCount);
        gtemp->SetMarkerColor(line_colors[i]);
        gtemp->SetMarkerStyle(6);
        gtemp->SetLineColor(line_colors[i]);
        gtemp->SetLineStyle(1);
        gtemp->SetLineWidth(2);

        if (i == 0)
        {
            gtemp->SetNameTitle("g1", ";LAr Height (cm);Photon Count"); 
            gtemp->GetYaxis()->SetRangeUser(0.0, 300000);
            gtemp->GetXaxis()->SetLimits(0.0, 130.0);
            gtemp->Draw();
        }
        else
        {
            gtemp->Draw("SAME");
        }

        legend->AddEntry(gtemp, r_ranges[i].c_str(), "l");
    }

    cmain->cd();
    legend->Draw();
    cmain->Update();
    cmain->Print(goutput_name.c_str());
    return;
}

void GraphIndividually(std::vector<double> integrals_2d22, std::vector<double> integrals_5d23, std::vector<double> integrals_10d31, std::vector<double> integrals_17d93, std::vector<double> integrals_25d34, std::vector<double> integrals_28d09, std::vector<double> integrals_38d25, std::vector<double> integrals_40d79, std::vector<double> integrals_50d97, std::vector<double> integrals_63d65, std::vector<double> integrals_76d33, std::vector<double> integrals_89d05, std::vector<double> integrals_101d83, std::vector<double> integrals_127d22)
{
    double HLAr[14] = {2.22, 5.23, 10.31, 17.93, 25.34, 28.09, 38.25, 40.79, 50.97, 63.65, 76.33, 89.05, 101.83, 127.22};
    std::string r_ranges[33] = {"[0,3]", "(3,6]", "(6,9]", "(9,12]", "(12,15]", "(15,18]", "(18,21]", "(21,24]", "(24,27]", "(27,30]", "(30,33]", "(33,36]", "(36,39]", "(39,42]", "(42,45]", "(45,48]", "(51,54]", "(54,57]", "(57,60]", "(60,63]", "(63,66]", "(66,69]", "(69,72]", "(72,75]", "(75,78]", "(78,81]", "(81,84]", "(84,87]", "(87,90]", "(90,93]", "(93,96]", "(96,99]"};
    std::string r_range_names[33] = {"0to3mm", "3to6mm", "6to9mm", "9to12mm", "12to15mm", "15to18mm", "18to21mm", "21to24mm", "24to27mm", "27to30mm", "30to33mm", "33to36mm", "36to39mm", "39to42mm", "42to45mm", "45to48mm", "48to51mm", "51to54mm", "54to57mm", "57to60mm", "60to63mm", "63to66mm", "66to69mm", "69to72mm", "72to75mm", "75to78mm", "78to81mm", "81to84mm", "84to87mm", "87to90mm", "90to93mm", "93to96mm", "96to99mm"};
    int line_colors[33] = {632, 633, 635, 800, 801, 810, 401, 403, 830, 820, 813, 417, 420, 843, 834, 840, 434, 436, 861, 863, 867, 600, 602, 604, 878, 880, 890, 616, 618, 620, 906, 908, 910};

    for(int i = 0; i < integrals_2d22.size(); i++)
    {
        std::string goutput_name = "/nashome/a/abreaux/Downloads/larsmc_129nm/gPhotonCount_vs_r2_" + r_range_names[i] + "_129nm.root";
        double PhotonCount[14] = {integrals_2d22[i], integrals_5d23[i], integrals_10d31[i], integrals_17d93[i], integrals_25d34[i], integrals_28d09[i], integrals_38d25[i], integrals_40d79[i], integrals_50d97[i], integrals_63d65[i], integrals_76d33[i], integrals_89d05[i], integrals_101d83[i], integrals_127d22[i]};

        TCanvas *ctemp = new TCanvas("canvas", "Photons vs. r^2", 800, 600);
        TLegend *legendtemp = new TLegend(0.585213, 0.730903, 0.885965, 0.881944, "h", "brNDC");
        legendtemp->SetHeader("r Range (mm)", "C");

        ctemp->cd();
        TGraph *gtemp = new TGraph(14, HLAr, PhotonCount);
        gtemp->SetMarkerColor(line_colors[i]);
        gtemp->SetMarkerStyle(6);
        gtemp->SetLineColor(line_colors[i]);
        gtemp->SetLineStyle(1);
        gtemp->SetLineWidth(2);
        gtemp->SetNameTitle("g1", ";LAr Height (cm);Photon Count"); 
        gtemp->Draw();

        ctemp->cd();
        legendtemp->AddEntry(gtemp, r_ranges[i].c_str(), "l");
        legendtemp->Draw();
        ctemp->Update();
        ctemp->SaveAs(goutput_name.c_str());
        delete ctemp;
    }
    return;
}

void GraphPhotonsVsHLAr_129nm()
{
    std::vector<std::string> file_names = {"PhotonCount_vs_r2_2d22_129nm.root", "PhotonCount_vs_r2_5d23_129nm.root", "PhotonCount_vs_r2_10d31_129nm.root", "PhotonCount_vs_r2_17d93_129nm.root", "PhotonCount_vs_r2_25d34_129nm.root", "PhotonCount_vs_r2_28d09_129nm.root", "PhotonCount_vs_r2_38d25_129nm.root", "PhotonCount_vs_r2_40d79_129nm.root", "PhotonCount_vs_r2_50d97_129nm.root", "PhotonCount_vs_r2_63d65_129nm.root", "PhotonCount_vs_r2_76d33_129nm.root", "PhotonCount_vs_r2_89d05_129nm.root", "PhotonCount_vs_r2_101d83_129nm.root", "PhotonCount_vs_r2_127d22_129nm.root"};
    std::string file_path = "/nashome/a/abreaux/Downloads/larsmc_129nm/";

    std::vector<double> integrals_2d22;
    std::vector<double> integrals_5d23;
    std::vector<double> integrals_10d31;
    std::vector<double> integrals_17d93;
    std::vector<double> integrals_25d34;
    std::vector<double> integrals_28d09;
    std::vector<double> integrals_38d25;
    std::vector<double> integrals_40d79;
    std::vector<double> integrals_50d97;
    std::vector<double> integrals_63d65;
    std::vector<double> integrals_76d33;
    std::vector<double> integrals_89d05;
    std::vector<double> integrals_101d83;
    std::vector<double> integrals_127d22;

    for (int i = 0; i < 14; i++)
    {
        std::string file_name = file_path + file_names[i];

        TFile *file = TFile::Open(file_name.c_str());
        TCanvas *canvas = (TCanvas*)file->Get("canvas");
        TH1D *histogram = (TH1D*)canvas->GetPrimitive("h1");

        std::vector <double> integrals;

        // Loop to extract integral range values in histograms
        for(int j = 0; j <= 97; j += 3)
        {
            int k = j * j + 1;
            int l = (j + 3) * (j + 3);

            double integral = histogram->Integral(k, l, "");

            integrals.push_back(integral);
        }

        // If statements to assign to vectors
        if (i == 0) { integrals_2d22 = integrals; }
        else if(i == 1) { integrals_5d23 = integrals; }
        else if(i == 2) { integrals_10d31 = integrals; }
        else if(i == 3) { integrals_17d93 = integrals; }
        else if(i == 4) { integrals_25d34 = integrals; }
        else if(i == 5) { integrals_28d09 = integrals; }
        else if(i == 6) { integrals_38d25 = integrals; }
        else if(i == 7) { integrals_40d79 = integrals; }
        else if(i == 8) { integrals_50d97 = integrals; }
        else if(i == 9) { integrals_63d65 = integrals; }
        else if(i == 10) { integrals_76d33 = integrals; }
        else if(i == 11) { integrals_89d05 = integrals; }
        else if(i == 12) { integrals_101d83 = integrals; }
        else if(i == 13) { integrals_127d22 = integrals; }

        delete canvas;
        file->Close();
        delete file;
    }

    GraphTogether(integrals_2d22, integrals_5d23, integrals_10d31, integrals_17d93, integrals_25d34, integrals_28d09, integrals_38d25, integrals_40d79, integrals_50d97, integrals_63d65, integrals_76d33, integrals_89d05, integrals_101d83, integrals_127d22);
    // GraphIndividually(integrals_2d22, integrals_5d23, integrals_10d31, integrals_17d93, integrals_25d34, integrals_28d09, integrals_38d25, integrals_40d79, integrals_50d97, integrals_63d65, integrals_76d33, integrals_89d05, integrals_101d83, integrals_127d22);

    return;
}