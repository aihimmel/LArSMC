## Wavelength-Specific Directory Preview
Here is the typical order of operations:
`MakeClassFiles_*.C` -> `HistoPhotonsVsR2_*.C ` -> `GraphPhotonsVsHLAr_*.C` -> `FitPhotonsVsHLAr_*.C`

### MakeClassFiles_*.C
**This is a dangerous script.** It writes a class and header file within each wavelength directory for every liquid argon height specified
during simulations. I would not run this script. Instead, edit the class files that are already present in the directory so the edited nested
loop contents are not lost.

### HistoPhotonsVsR2_*.C
This calls and runs all of the class files written in `MakeClassFiles_*.C`. Within these class files, there is a for loop that retrieves values
of r^2 up to 100^2. The output is a root file containing all of the histograms drawn on top of each other, as well as each of the liquid argon heights'
individual histograms. Only the individual histograms are used in later analysis.

### GraphPhotonsVsHLAr_*.C
This retrieves the contents of the aforementioned height-specific histogram files. It takes each of these and gets the photon count within
r^2 ranges. Specifically, the first integral range is 0 to 9 mm^2 because that tranforms to 0 to 3 mm, then it is 9 to 36 mm^2, and so on.
With these integrals, a total photon count at the different ranges of r are generated, which are simultaneously at liquid argon height dependent.
From here, we transpose the data to have each 0 to 3 mm photon count for all the heights on one graph. This is done for each r range. A plot of all
of the r ranges on top of each other is drawn, as well as individual r range plots which are used in future analysis.

### FitPhotonsVsHLAr_*.C
This is a largely irrelevant script now since we perform a likelihood ratio test. It retrieves the tail end of selected r interval curves produced
in the previous script, then it performs an exponential fit and extracts the attenuation length. These attenuation length values are graphed against
the specified scattering length values. The output is used in future analysis *if* this route of analysis is taken. They are useless to the likelihood
ratio test.
