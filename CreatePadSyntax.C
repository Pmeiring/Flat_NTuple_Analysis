#include "TROOT.h"
#include "TFile.h"
#include "TTree.h"
#include "TBrowser.h"
#include "TH2.h"
#include "TRandom.h"
#include "/afs/cern.ch/work/p/pmeiring/private/ATLAS/My_FlatTuple_Analysis_01/Headers/PadSyntax.h"

void CreatePadSyntax(){

	CreatePadSyntaxStack_hh(1,1,8);
	CreatePadSyntaxStack_hh(1,2,8);
	CreatePadSyntaxStack_hh(1,3,8);
	CreatePadSyntaxStack_hh(1,4,8);


	CreatePadSyntaxStack_hh(2,1,8);
	CreatePadSyntaxStack_hh(2,2,8);
	CreatePadSyntaxStack_hh(2,3,8);
	CreatePadSyntaxStack_hh(2,4,8);

	gApplication->Terminate();

}




