# Protein Knot Analyzer and Detector
This tool was created for a UC Davis ECS 129 course taught by Dr. Patrice Koehl for an assignment called "Protein structure geometry: knot, or not?" The assignment details are in the /share directory. 

The repository "protein-knot-analyzer" is the full graphical program used for PDB model processing and simulation, while the "protein-knot-detector" is the command line lite version with only the core algorithm and a reduced file importer.

# Demo
In Faísca's paper, it was shown that in protein CAB (PDB ID: 2cab) there is a superficial knot. The protein viewed as a ribbon in UCSF Chimera is shown below:
![2cab_ribbon](https://github.com/bradosia/protein-knot-analyzer/blob/master/share/report/2cab_ribbon.jpg?raw=true)

After decomposing the protein model into only a string of the alpha carbons:
![2cab_backbone-wire-iteration-0](https://github.com/bradosia/protein-knot-analyzer/blob/master/share/report/2cab_backbone-wire-iteration-0.jpg?raw=true)

After running Taylor's knot algorithm 50 iterations:
![2cab_backbone-wire-iteration-1](https://github.com/bradosia/protein-knot-analyzer/blob/master/share/report/2cab_backbone-wire-iteration-1.jpg?raw=true)

After running Taylor's knot algorithm 1000 iterations:
![2cab_backbone-wire-iteration-20](https://github.com/bradosia/protein-knot-analyzer/blob/master/share/report/2cab_backbone-wire-iteration-20.jpg?raw=true)

# Libraries Used:
* MMDB, a macromolecular coordinate library
* openCascade

# Acknowledgment:
Molecular graphics and analyses performed with UCSF Chimera, developed by the Resource for Biocomputing, Visualization, and Informatics at the University of California, San Francisco, with support from NIH P41-GM103311.

# References
1. P. F. N. Faísca, Knotted proteins: A tangled tale of Structural Biology.
Comput. Struct. Biotechnol. J. 13, 459–468 (2015)
2. UCSF Chimera--a visualization system for exploratory research and analysis. Pettersen EF, Goddard TD, Huang CC, Couch GS, Greenblatt DM, Meng EC, Ferrin TE. J Comput Chem. 2004 Oct;25(13):1605-12.
3. M. D. Winn et al. Acta. Cryst. D67, 235-242 (2011)
"Overview of the CCP4 suite and current developments"
[ doi:10.1107/S0907444910045749 ]
