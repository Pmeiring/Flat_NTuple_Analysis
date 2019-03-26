#include "/afs/cern.ch/work/p/pmeiring/private/ATLAS/My_xAOD_Analysis_01/source/MyAnalysis/MyAnalysis/MiniEvent.h"
#include "/afs/cern.ch/work/p/pmeiring/private/ATLAS/My_FlatTuple_Analysis_01/Headers/Hists.h"
#include "/afs/cern.ch/work/p/pmeiring/private/ATLAS/My_FlatTuple_Analysis_01/Headers/Logger.h"
#include "/afs/cern.ch/work/p/pmeiring/private/ATLAS/My_FlatTuple_Analysis_01/Headers/ProcessHandler.h"
#include <iostream>
#include <sstream>
#include <string>
#include <algorithm>
#include <fstream>
#include <vector>


float DetermineScaleFactor(int DSID){

	float ScaleFactor = -1;

	std::string SampleName;
	std::ifstream SampleFile;
	SampleFile.open("/afs/cern.ch/work/p/pmeiring/private/ATLAS/My_xAOD_Analysis_01/source/MyAnalysis/share/All_mc16a_samples.txt");

	// Iterate over all processes in SampleFile used to launch GRID jobs
	if (SampleFile){
		while (SampleFile >> SampleName){

			std::string dsid = std::to_string(DSID);
			if (!(SampleName.find(dsid) != std::string::npos)) continue;


			std::cout<<"LogicalDatasetName: "<<SampleName<<std::endl;

			double SampleXSEC;
			int nSampleEvents;
			double TargetLuminosity = 140;


			// Open PMGxsec file and determine xsec corresponding to SampleName
			std::ifstream PMGxsecFile;
			PMGxsecFile.open("/afs/cern.ch/work/p/pmeiring/private/ATLAS/My_FlatTuple_Analysis_01/Data/PMGxsecDB_mc16.txt");
			if (PMGxsecFile){
				std::string line;

				int dataset_number;
				std::string physics_short;
				double crossSection;
				double genFiltEff;
				double kFactor;
				double relUncertUP;
				double relUncertDOWN;
				std::string generator_name;

				std::cout<<"... Reading PMGxsec info ..."<<std::endl;
				// Loop over all lines in PMGxsecFile
				while(!PMGxsecFile.eof()){
					getline(PMGxsecFile,line);
			
					if (line[0] == 'd') continue;
					PMGxsecFile >> dataset_number >> physics_short >> crossSection >> genFiltEff >> kFactor >> relUncertUP >> relUncertDOWN >> generator_name;

					// If the SampleName contains physics_short, we found the process
					bool FoundProcess(SampleName.find(physics_short+".") != std::string::npos);
					if (FoundProcess){
						std::cout<<"Found corresponding crossSection: "<<crossSection<<" pb"<<std::endl;
						SampleXSEC = crossSection;
					}
				}
			}

			// Call on AMI to determine samplesize
			std::cout<<"... Reading ami info ..."<<std::endl;
			remove("AMIDatasetInfo.txt");
			std::string AMIcommand = "ami show dataset info "+SampleName+" >> AMIDatasetInfo.txt";
			system(AMIcommand.c_str());

			std::ifstream AMIDatasetInfo;
			AMIDatasetInfo.open("/afs/cern.ch/work/p/pmeiring/private/ATLAS/My_FlatTuple_Analysis_01/AMIDatasetInfo.txt");
			if (AMIDatasetInfo){
				std::string line;

				std::string variable;
				std::string colon;

				bool TargetFound=0;
				while(!AMIDatasetInfo.eof() && TargetFound==0){
					getline(AMIDatasetInfo,line);

					if (line[0]!='t' || line[1]!='o' || line[5]!='E') continue;

					std::istringstream stream(line);
					stream >> variable >>colon >> nSampleEvents;
					TargetFound=1;
					std::cout<<"Found number of events in Sample: "<<nSampleEvents<<std::endl;
				}
			}

			double Luminosity = nSampleEvents/(SampleXSEC * 1e3); // fb-1
			std::cout<<"Luminosity : "<<Luminosity<<" fb-1"<<std::endl;
			ScaleFactor = TargetLuminosity/Luminosity;
			std::cout<<"ScaleFactor : "<<ScaleFactor<<std::endl;
			remove("AMIDatasetInfo.txt");

		}
	}
	else {std::cout<<"Could not open SampleFile"<<std::endl; abort();}
	return ScaleFactor;

}