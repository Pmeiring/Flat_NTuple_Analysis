#ifndef _process_
#define _process_


#include <fstream>

struct Process{

	Process(){};

	int DSID;
	std::string Dataset;
	float xsec;
	std::string ProcessAbrev;
	std::string Details;

};
	
bool ReadProcess(Process &p, std::string filename){
	std::ifstream XSECfile;
	XSECfile.open("/afs/cern.ch/work/p/pmeiring/private/ATLAS/My_FlatTuple_Analysis_01/Data/Cross_sections.txt");
	bool ProcessKnown=0;

	int dsid;
	std::string ds;
	float x;
	std::string processabrev;
	if (XSECfile){
		while (XSECfile >> dsid >> x >> processabrev >> ds){
			//std::cout<<"\n"<<filename<<std::endl;
			//std::cout<<"Histograms_"+ds+".root"<<std::endl;
			ProcessKnown = ("Histograms_"+ds+".root"==filename) || (ds.append(".root")==filename);
			if (ProcessKnown){
				//std::cout<<"HERE"<<std::endl;
				std::cout<<"Process = "<<processabrev<<std::endl;				
				std::cout<<"Cross-section (AMI) = "<<x<<" nb"<<std::endl;
				p.DSID = dsid;
				p.xsec = x;
				p.Dataset = ds;
				p.ProcessAbrev = processabrev;
				break;
			}
		}
	}

	return ProcessKnown;
}

bool ReadGridProcess(Process &p, std::string filename){
	std::ifstream XSECfile;
	XSECfile.open("/afs/cern.ch/work/p/pmeiring/private/ATLAS/My_FlatTuple_Analysis_01/Data/GridProcesses.txt");
	bool ProcessKnown=0;

	int dsid_min;
	int dsid_max;
	std::string ds;
	float x;
	std::string processabrev;
	std::string details;

	if (XSECfile){

		int pos = filename.find("_ANALYSIS");
		string dsidstring = filename.substr(pos-6,pos);
		p.DSID = std::atoi(dsidstring.c_str());
		//std::cout<<"DSID = "<<p.DSID<<std::endl;

		while (XSECfile >> dsid_min >> dsid_max >> x >> processabrev >> details){
			//std::cout<<"\n"<<filename<<std::endl;
			//std::cout<<"Histograms_"+ds+".root"<<std::endl;

			ProcessKnown = (p.DSID <= dsid_max && p.DSID >= dsid_min);
			//ProcessKnown = ("Histograms_"+ds+".root"==filename) || (ds.append(".root")==filename);
			if (ProcessKnown){
				//std::cout<<"HERE"<<std::endl;
				std::cout<<"Process : "<<processabrev<<std::endl;				
				std::cout<<"ProcessDetails : "<<details<<std::endl;
				//std::cout<<"Cross-section = "<<x<<" nb"<<std::endl;

				p.xsec = x;
				p.ProcessAbrev = processabrev;
				p.Details = details;
				break;
			}
		}
	}	

	return ProcessKnown;
}




#endif
