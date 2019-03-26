#include "/afs/cern.ch/work/p/pmeiring/private/ATLAS/My_xAOD_Analysis_01/source/MyAnalysis/MyAnalysis/MiniEvent.h"
#include "/afs/cern.ch/work/p/pmeiring/private/ATLAS/My_FlatTuple_Analysis_01/Headers/Hists.h"
#include "/afs/cern.ch/work/p/pmeiring/private/ATLAS/My_FlatTuple_Analysis_01/Headers/Logger.h"
#include "/afs/cern.ch/work/p/pmeiring/private/ATLAS/My_FlatTuple_Analysis_01/Headers/ProcessHandler.h"
#include <iostream>
#include <string>
#include <algorithm>
#include <fstream>
#include <vector>



void Merge_FlatTuples(){
	
    bool debug = 0;
    bool Write=1;
    int  nentries=750;

    // Directory containing a samples from the GRID. It should contain a subdirectory for each analyzed process, ending with "ANALYSIS.root"
    const char *dirname = "/afs/cern.ch/work/p/pmeiring/private/ATLAS/NTuples/DxAOD/GRIDdownload0324_llbb/";    
	const char *ext="ANALYSIS.root";
	gSystem->pwd();
	TSystemDirectory dir(dirname, dirname);
	gSystem->pwd();

	// Get all files (actually they are directories) in the TSystemDirectory, abort if it's empty
	TList *files = dir.GetListOfFiles();
	if (!files) abort();

	// Loop over all files (directories) obtained in the previous step
	TSystemFile *file;
	TString fname;
	TIter next(files);
	while ((file=(TSystemFile*)next())) {

		// Get the name of the file (directory) and convert to a string
		fname = file->GetName();
		string fileName = fname.Data();

		// Determine if it is a directory obtained by downloading samples from the GRID, i.e. if it ends with "ANALYSIS.root"
		bool isGridDir = (fname.EndsWith(ext));
		cout<<fname<<endl;
		if (isGridDir) {

			// Construct the path of subdirectory (it ends with ANALYSIS.root)
			string subdirname = (string)dirname + fileName;

			// Make a new directory name with the same path, but the extension ".root" removed. This new subdirectory will contain the merged samples
			string subdirname_new = subdirname;
			string toErase = ".root";
			size_t pos = subdirname_new.find(toErase);
			if (pos != std::string::npos){
				subdirname_new.erase(pos, toErase.length());
			}

			// Rename the directory so that the ".root" extension is removed. If this is not done, we cannot treat it using the Root TSystemDirectory function
			string command = "mv " + subdirname + " " + subdirname_new;
		    cout<<command<<endl;
		    const char *C = command.c_str();
		    gSystem->Exec(C);
		    

		    // Mount the TSystemDirectory we just renamed 
			const char *Subdirname = subdirname_new.c_str();
			cout<<"checking "<<Subdirname<<endl;
			TSystemDirectory subdir(Subdirname, Subdirname);

			// List the files inside the directory; Continue if it's empty
			TList *subfiles = subdir.GetListOfFiles();	
			if (!subfiles) continue;

			// Construct the name of the file that will contain the samples inside the directory merged
			string mergedfilepath = subdirname_new + ".root";

			// This TChain will be the Root object containing the merged samples
			TChain ch("analysis");

			// Loop over all samples inside the directory
			TSystemFile *subfile;
			TString subfname;
			TIter subnext(subfiles);
			while ((subfile=(TSystemFile*)subnext())) {
				
				// Get the name of the sample file and convert it to a string
				subfname = subfile->GetName();
				string subfileName = subfname.Data();

				// If the sample is not a directory and it ends with ".root", it is considered a good sample file
				bool GoodFile = (!subfile->IsDirectory() && subfname.EndsWith(".root"));
				if (!GoodFile) continue;

				// Construct the path to the sample ntuple tree to add to the TChain object. Add it
				string filetoadd = subdirname_new + "/" + subfileName + "/analysis";
				ch.Add(filetoadd.c_str());

			}

			// After all trees are add to the TChain, merge them into a single file
			ch.Merge(mergedfilepath.c_str());

			// Delete the TSystemFile (directory) and subdirectory from memory and delete all subsamples
		    file->Delete();
		    subdir.Delete();
		    gSystem->Exec(TString::Format("rm -rf %s", subdirname_new.c_str()));

		}

		else {cout<<"not a griddir"<<endl;}
	}
}
