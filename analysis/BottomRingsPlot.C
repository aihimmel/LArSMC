#include <iostream>
#include <vector>
#include <string>

#include "TROOT.h"
#include "TFile.h"
#include "TCanvas.h"
#include "TLegend.h"
#include "TEllipse.h"

void BottomRingsPlot()
{
    int line_colors[33] = {632, 633, 635, 800, 801, 810, 401, 403, 830, 820, 813, 417, 420, 843, 834, 840, 434, 436, 861, 863, 867, 600, 602, 604, 878, 880, 890, 616, 618, 620, 906, 908, 910};
    std::string r_ranges[33] = {"[0,3]", "(3,6]", "(6,9]", "(9,12]", "(12,15]", "(15,18]", "(18,21]", "(21,24]", "(24,27]", "(27,30]", "(30,33]", "(33,36]", "(36,39]", "(39,42]", "(42,45]", "(45,48]", "(48,51]", "(51,54]", "(54,57]", "(57,60]", "(60,63]", "(63,66]", "(66,69]", "(69,72]", "(72,75]", "(75,78]", "(78,81]", "(81,84]", "(84,87]", "(87,90]", "(90,93]", "(93,96]", "(96,99]"};
    std::vector<int> r_range_values;
    for (int i = 3; i <= 99; i+=3) { r_range_values.push_back(i); }

    TCanvas *canvas = new TCanvas("canvas", "Photons vs. r^2", 600, 600);

    TEllipse *circle = new TEllipse(0.5, 0.5, 0.4, 0.4); 
    circle->SetFillColor(kGray+1); 
    circle->SetLineColor(kGray+1);
    circle->Draw();

    double x = 0.5 + ((87.5 * 0.5) / 300.0);

    for(int i = 32; i >= 0; i--)
    {
        double circ_r = (r_range_values[i] / 300.0) * 0.4;
        TEllipse *circle = new TEllipse(x, 0.5, circ_r, circ_r); 
        circle->SetFillColor(line_colors[i]); 
        circle->SetLineColor(line_colors[i]);
        circle->Draw("SAME");
    }

    double dev = (3 / 300.0) * 0.8;

    TBox *square = new TBox(x - dev, 0.5 - (2 * dev), x + dev, 0.5 + (2 * dev));
    square->SetFillColor(kBlack);
    square->SetLineColor(kBlack); 
    square->Draw("SAME");

    canvas->Update();
    canvas->Print("~/Downloads/BottomRingsPlot.root");
    canvas->SaveAs("~/Downloads/BottomRingsPlot.pdf");

}