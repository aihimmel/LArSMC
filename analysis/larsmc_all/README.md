# Broad Analysis Directory Preview
There are three main analysis pipelines that are located in this directory. The first is the fitting pipeline, the second is the chi squared analysis pipeline, and the third is the grid-based analysis pipeline.

**Note:** `MakePDFs.C` is a flexible macro that can be run for any of these pipelines, just edit it to output the PDFs you want.

**Fitting pipeline order of operations:**

`GraphScatLensVsAttLens.C` -> `FitScatLensVsAttLens.C` -> `CorrectScatLensVsAttLens.C`

**Chi Squared pipeline order of operations:**

`GraphPhotonCountVsHLAr_all.C` -> `ChiSquaredAnalysis.C` / `GraphChiSquaredRCurves.C`

**Grid-based pipeline order of operations:**

`GridMaker.C` -> `ExtractGridSquareData.C` -> `PlotGridWithR.C`

## Fitting Pipeline Macro Descriptions
### GraphScatLensVsAttLens.C
This macro relies on the output of each individual wavelength directory. More specifically, it relies on the output of each wavelength 
directories' `FitPhotonsVsHLAr_*.C` macro. It takes these fits and plots the extracted attenuation lengths from the r ranges selected in 
`FitPhotonsVsHLAr_*.C` at each scattering length in the analysis.

### FitScatLensVsAttLens.C
This macro performs fits to the graphs outputted in `GraphScatLensVsAttLens.C`. It needs reworking since we now know the 
previously outputted plots are not linear!

### CorrectScatLensVsAttLens.C
This macro corrects the fits outputted in `FitScatLensVsAttLens.C` to match the specified scattering lengths. Once again, this needs reworking since the corrections are no longer as simple as a linear transformation! 

## Chi Squared Pipeline Macro Descriptions
### GraphPhotonCountVsHLAr_all.C
This macro relies on the output of each individual wavelength directory. More specifically, it relies on the output of each wavelength 
directories' `GraphPhotonsVsHLAr_*.C` macro. It takes these plots and outputs a plot with every wavelength directory's curve at that specific
r range. So, each outputted plot has a curve for each wavelength, and one plot for each r range is plotted. This is simply a transposing macro.

### ChiSquaredAnalysis.C
This is the entirity of the likelihood ratio test. It takes each of the plots outputted in `GraphPhotonCountVsHLAr_all.C` and calculates the
chi squared value for each curve. It then outputs the 3D map of the delta chi squared versus the scattering length and r range. There is
also a portion that outputs the delta chi squared versus the r range, so there is one 2D plot for each scattering length outputted.

### GraphChiSquaredRCurves.C
This macro graphs each chi squared curve with the real data. In the previous macro, each curve is evaluated at the liquid argon heights that the experimental data has points at. This simply visualizes that process, and is reliant on the output of `GraphPhotonCountVsHLAr_all.C`.

## Grid-based Pipeline Macro Descriptions
### Track.C and Track.h
Class and header file that allows us to input a root file that was outputted by Geant4 and loop through all of its entries. This outputs a TH2D object.

### GridMaker.C
This initializes a track object for each wavelength at each height, runs the loop function, and writes all the outputted TH2Ds into a single TFile.

### ExtractGridSquareData.C
This macro reconstructs the SiPMs from the TH2D grids at a certain azimuthal angle from the x axis and at a certain distance from the SiPM's intended location. It could be better suited to handle reconstructions at 45, 135, 225, and 315 degrees, as it does not rotate the reconstruction as of now.








