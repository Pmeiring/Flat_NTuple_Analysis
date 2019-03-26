#include "/afs/cern.ch/work/p/pmeiring/private/ATLAS/My_xAOD_Analysis_01/source/MyAnalysis/MyAnalysis/MiniEvent.h"
#include "/afs/cern.ch/work/p/pmeiring/private/ATLAS/My_FlatTuple_Analysis_01/Headers/Hists.h"
#include "/afs/cern.ch/work/p/pmeiring/private/ATLAS/My_FlatTuple_Analysis_01/Headers/Logger.h"
#include "/afs/cern.ch/work/p/pmeiring/private/ATLAS/My_FlatTuple_Analysis_01/Headers/ProcessHandler.h"
#include <iostream>
#include <string>
#include <algorithm>
#include <fstream>
#include <vector>



// MAKE SURE YOU HAVE SET THE CORRECT:
//			--> dirname (at the start)
//			--> histfile (path at the end)
//			--> ReadProcess/ReadGridProcess

// TAKE NOTE OF THE SETTINGS:
//			--> debug	(if 0: analyze all events, if 1: analyze only the first nentries events)
//			--> nentries
//			--> Write 	(if 0: do not write, just to test. if 1: Write to output)





void Analyze_FlatTuples(){
	
    bool debug = 0;
    int  nentries=750;
    bool Write=1;

    //const char *dirname = "/afs/cern.ch/work/p/pmeiring/private/ATLAS/My_xAOD_Analysis_01/run/test2/data-ANALYSIS/";
    const char *dirname = "/afs/cern.ch/work/p/pmeiring/private/ATLAS/NTuples/DxAOD/GRIDdownload0324_llbb/";    
	const char *ext=".root";
	TSystemDirectory dir(dirname, dirname);
	TList *files = dir.GetListOfFiles();

	if (!files) abort();
	TSystemFile *file;
	TString fname;
	TIter next(files);
	while ((file=(TSystemFile*)next())) {

		// If it is not a root file, go to next iteration
		fname = file->GetName();
		// Name of the data file
		string fileName = fname.Data();
		cout<<"\nComputing histograms for:\n"<<fileName<<endl;

		// Determine what kind of process were dealing with based on the file name
		//bool isTTbar(fileName.find("ttbar") != std::string::npos);
		//bool isHH(fileName.find("hh_WWbb") != std::string::npos);

		// If the is a root file, do the analysis; Else continue
		bool GoodFile = (!file->IsDirectory() && fname.EndsWith(ext));
		if (!GoodFile) {cout<<"Not a good file"<<endl; continue;}

		// Create a log file
		std::ofstream log = CreateLogger(fileName);

		// Determine the process specific parameters based on the fileName
		Process process;
		bool ProcessKnown = ReadGridProcess(process,fileName);
		if (!ProcessKnown) continue;

		// Compute path of the data file
		string basePath = dirname;
	    string filePath = basePath.append(fileName.c_str());
		const char *FilePath = filePath.c_str();

		// Open data file and get the tree
	    auto treeName = "analysis";
	    TFile *f= TFile::Open(FilePath);
		TTree *tree=(TTree*)f->Get(treeName);

		// Create struct MiniEvent_t and attach the struct to the branches in the tree
	    MiniEvent_t ev;
	    attachToMiniEventTree(tree,ev);

		// Create a container with all empty histograms.
		HistogramContainer hc;

		
		// Determine the amount of events to analyse
	    if (!debug){nentries = tree->GetEntries();}

		//std::cout<<"Loaded "<<fileName<<std::endl;
	    std::cout <<"Processing "<<nentries<<" events..."<<std::endl;
	    std::cout << std::setprecision(3);


	    int GoodRecoEvents=0;

		// Event loop
	    for (int iev = 0; iev < nentries; iev++) {
			//if (GoodEvents>10000) continue;

			tree->GetEntry(iev);
			//log <<"\nEvent "<<iev<<" has "<<ev.TruthParticle_id->size()<<" particles"<<endl;
			//log <<"Run nr.: "<<ev.m_runNumber<<"\tEvent nr.: "<<ev.m_eventNumber<<endl;


			// ================================================================ ev.TRUTH LEVEL COMPUTATIONS ======================================================== //
			// Convention: h1 > bb, h2 >wmwp, wp > il1 ilv1, wm > il2 ilv2
			TLorentzVector T, Tbar;
			TLorentzVector B, Bbar;
			TLorentzVector Wp, Wm;
			TLorentzVector L1, Lv1;
			TLorentzVector L2, Lv2;
			int TruthParticlesFound=0;

			for (int ip=0; ip<(ev.TruthParticle_id->size()); ip++){

				//log <<"Particle "<<ip<<"\tip "<<ev.TruthParticle_id->at(ip)<<"\tstatus "<<ev.TruthParticle_status->at(ip)<<endl;
				//cout<<"Status = "<<ev.TruthParticle_status.at(ip)<<endl;

				switch(ev.TruthParticle_id->at(ip)){
			      case 6:{
			      	T.SetPtEtaPhiM(ev.TruthParticle_pt->at(ip),ev.TruthParticle_eta->at(ip),ev.TruthParticle_phi->at(ip),ev.TruthParticle_m->at(ip)); TruthParticlesFound++;
			      } break;
			      case -6:{
			      	Tbar.SetPtEtaPhiM(ev.TruthParticle_pt->at(ip),ev.TruthParticle_eta->at(ip),ev.TruthParticle_phi->at(ip),ev.TruthParticle_m->at(ip)); TruthParticlesFound++;
			      } break;
			      case 24:{
			      	Wp.SetPtEtaPhiM(ev.TruthParticle_pt->at(ip),ev.TruthParticle_eta->at(ip),ev.TruthParticle_phi->at(ip),ev.TruthParticle_m->at(ip)); TruthParticlesFound++;
			      } break;
			      case -24:{
			      	Wm.SetPtEtaPhiM(ev.TruthParticle_pt->at(ip),ev.TruthParticle_eta->at(ip),ev.TruthParticle_phi->at(ip),ev.TruthParticle_m->at(ip)); TruthParticlesFound++;
			      } break;
			      case 5:{
			      	B.SetPtEtaPhiM(ev.TruthParticle_pt->at(ip),ev.TruthParticle_eta->at(ip),ev.TruthParticle_phi->at(ip),ev.TruthParticle_m->at(ip)); TruthParticlesFound++;
			      } break;
			      case -5:{
			      	Bbar.SetPtEtaPhiM(ev.TruthParticle_pt->at(ip),ev.TruthParticle_eta->at(ip),ev.TruthParticle_phi->at(ip),ev.TruthParticle_m->at(ip)); TruthParticlesFound++;
			      } break;		      
			      case 11:{
			      	L2.SetPtEtaPhiM(ev.TruthParticle_pt->at(ip),ev.TruthParticle_eta->at(ip),ev.TruthParticle_phi->at(ip),ev.TruthParticle_m->at(ip)); TruthParticlesFound++;
			      } break;
			      case -11:{
			      	L1.SetPtEtaPhiM(ev.TruthParticle_pt->at(ip),ev.TruthParticle_eta->at(ip),ev.TruthParticle_phi->at(ip),ev.TruthParticle_m->at(ip)); TruthParticlesFound++;
			      } break;		      
			      case 12:{
			      	Lv2.SetPtEtaPhiM(ev.TruthParticle_pt->at(ip),ev.TruthParticle_eta->at(ip),ev.TruthParticle_phi->at(ip),ev.TruthParticle_m->at(ip)); TruthParticlesFound++;
			      } break;
			      case -12:{
			      	Lv1.SetPtEtaPhiM(ev.TruthParticle_pt->at(ip),ev.TruthParticle_eta->at(ip),ev.TruthParticle_phi->at(ip),ev.TruthParticle_m->at(ip)); TruthParticlesFound++;
			      } break;		      
			      case 13:{
			      	L2.SetPtEtaPhiM(ev.TruthParticle_pt->at(ip),ev.TruthParticle_eta->at(ip),ev.TruthParticle_phi->at(ip),ev.TruthParticle_m->at(ip)); TruthParticlesFound++;
			      } break;
			      case -13:{
			      	L1.SetPtEtaPhiM(ev.TruthParticle_pt->at(ip),ev.TruthParticle_eta->at(ip),ev.TruthParticle_phi->at(ip),ev.TruthParticle_m->at(ip)); TruthParticlesFound++;
			      } break;
			      case 14:{
			      	Lv2.SetPtEtaPhiM(ev.TruthParticle_pt->at(ip),ev.TruthParticle_eta->at(ip),ev.TruthParticle_phi->at(ip),ev.TruthParticle_m->at(ip)); TruthParticlesFound++;
			      } break;
			      case -14:{
			      	Lv1.SetPtEtaPhiM(ev.TruthParticle_pt->at(ip),ev.TruthParticle_eta->at(ip),ev.TruthParticle_phi->at(ip),ev.TruthParticle_m->at(ip)); TruthParticlesFound++;
			      } break;		      
			      default: continue;
			    }
			    
			}

			//log << "TruthParticlesFound = "<<TruthParticlesFound<<endl;
			// ================================================================ TRUTH LEVEL COMPUTATIONS ======================================================== //
			// ================================================================ RECO  LEVEL LEPTON COMPUTATIONS ======================================================== //
			int LeptonsinAcceptance=0;
			int i_Reco_LeadingLepton=-1;
			int i_Reco_SubleadingLepton=-1;
			float LeadingLeptonPt=0;
			float SubleadingLeptonPt=0;

			// Apply cuts on leptons based on detector acceptance
			for (int ip=0; ip<ev.Lepton_id->size(); ip++){
				//log << "Lepton "<<ip<<" has PID "<<ev.Lepton_id->at(ip)<<" and Pt "<<ev.Lepton_pt->at(ip) /1000<<" and Eta "<<ev.Lepton_eta->at(ip)<<" and Phi "<<ev.Lepton_phi->at(ip)<<endl;
				if (ev.Lepton_pt->at(ip) < 10) continue;

				// Good electron condition
				if (ev.Lepton_id->at(ip)==11 && (abs(ev.Lepton_eta->at(ip))>2.47 || (abs(ev.Lepton_eta->at(ip))>1.37 && abs(ev.Lepton_eta->at(ip))<1.52) )) continue;

				// Good muon condition
				if (ev.Lepton_id->at(ip)==13 && abs(ev.Lepton_eta->at(ip))>2.4) continue;

				LeptonsinAcceptance++;

				if (ev.Lepton_pt->at(ip) > LeadingLeptonPt){
					i_Reco_SubleadingLepton = i_Reco_LeadingLepton;
					i_Reco_LeadingLepton = ip;
					SubleadingLeptonPt = LeadingLeptonPt;
					LeadingLeptonPt = ev.Lepton_pt->at(ip);
				}
				else if (ev.Lepton_pt->at(ip) > SubleadingLeptonPt){
					i_Reco_SubleadingLepton = ip;
					SubleadingLeptonPt = ev.Lepton_pt->at(ip);
				}
				else continue;
			}

			TLorentzVector Reco_LeadingLepton;
			TLorentzVector Reco_SubleadingLepton;
			if (LeptonsinAcceptance <= 1) continue;

			Reco_LeadingLepton.SetPtEtaPhiM(
				ev.Lepton_pt->at(i_Reco_LeadingLepton),
				ev.Lepton_eta->at(i_Reco_LeadingLepton),
				ev.Lepton_phi->at(i_Reco_LeadingLepton),
				ev.Lepton_m->at(i_Reco_LeadingLepton));								
			Reco_SubleadingLepton.SetPtEtaPhiM(
				ev.Lepton_pt->at(i_Reco_SubleadingLepton),
				ev.Lepton_eta->at(i_Reco_SubleadingLepton),
				ev.Lepton_phi->at(i_Reco_SubleadingLepton),
				ev.Lepton_m->at(i_Reco_SubleadingLepton));

				
			// ================================================================ RECO  LEVEL LEPTON COMPUTATIONS ======================================================== //
			// ================================================================ RECO  LEVEL BJET COMPUTATIONS ======================================================== //
			int BJetsinAcceptance=0;
			int i_Reco_LeadingBJet=-1;
			int i_Reco_SubleadingBJet=-1;
			float LeadingBJetPt=0;
			float SubleadingBJetPt=0;
			// Apply cuts on BJets based on detector acceptance
			for (int ip=0; ip<ev.nBJets; ip++){

				// Good BJet condition
				if (abs(ev.BJet_eta->at(ip))>2.5) continue;
				if (abs(ev.BJet_pt->at(ip))<20) continue;

				BJetsinAcceptance++;

				if (ev.BJet_pt->at(ip) > LeadingBJetPt){
					i_Reco_SubleadingBJet = i_Reco_LeadingBJet;
					i_Reco_LeadingBJet = ip;
					SubleadingBJetPt = LeadingBJetPt;
					LeadingBJetPt = ev.BJet_pt->at(ip);
				}
				else if (ev.BJet_pt->at(ip) > SubleadingBJetPt){
					i_Reco_SubleadingBJet = ip;
					SubleadingBJetPt = ev.BJet_pt->at(ip);
				}
				else continue;
			}

			if (BJetsinAcceptance <= 1) continue;


			TLorentzVector Reco_LeadingBJet;
			TLorentzVector Reco_SubleadingBJet;
			Reco_LeadingBJet.SetPtEtaPhiM(
				ev.BJet_pt->at(i_Reco_LeadingBJet),
				ev.BJet_eta->at(i_Reco_LeadingBJet),
				ev.BJet_phi->at(i_Reco_LeadingBJet),
				ev.BJet_m->at(i_Reco_LeadingBJet));								
			Reco_SubleadingBJet.SetPtEtaPhiM(
				ev.BJet_pt->at(i_Reco_SubleadingBJet),
				ev.BJet_eta->at(i_Reco_SubleadingBJet),
				ev.BJet_phi->at(i_Reco_SubleadingBJet),
				ev.BJet_m->at(i_Reco_SubleadingBJet));

			TLorentzVector Reco_TwoLeadingBJets = Reco_LeadingBJet + Reco_SubleadingBJet;
			if (Reco_TwoLeadingBJets.M()<100 || Reco_TwoLeadingBJets.M()>140) continue;
			// ================================================================ RECO  LEVEL BJET COMPUTATIONS ======================================================== //


			// ================================================================ TRUTH LEVEL FILLS ======================================================== //
			bool AllTruthPartFound = (TruthParticlesFound==10); 
			//bool GoodLeptonsFound = (Reco_LeadingLepton.Pt()>22 && Reco_SubleadingLepton.Pt()>15);
			//bool GoodEvent = (AllTruthPartFound && GoodLeptonsFound);
			if (AllTruthPartFound) {
				//log<<"Good thruth-level event"<<endl;

				TLorentzVector  BBbar;
				BBbar = B + Bbar;

		  		hc.H_Mass_bb->Fill(BBbar.M());
				hc.H_dEta_bb->Fill(B.Eta()-Bbar.Eta());
				hc.H_dPhi_bb->Fill(abs(B.DeltaPhi(Bbar)));

		  		hc.H_Pt_b->Fill(B.Pt());
		  		hc.H_Pt_bbar->Fill(Bbar.Pt());
				hc.H_Eta_b->Fill(B.Eta());
				hc.H_Eta_bbar->Fill(Bbar.Eta());
				hc.H_Phi_b->Fill(B.Phi());
				hc.H_Phi_bbar->Fill(Bbar.Phi());
				//log<<"b_phi = "<<B.Phi()<<"\tbbar_phi = "<<Bbar.Phi()<<"\tB.DeltaPhi(Bbar) = "<<B.DeltaPhi(Bbar)<<endl;

				hc.H_Mass_ll->Fill((L1+L2).M());
				hc.H_dEta_ll->Fill(L1.Eta()-L2.Eta());
				hc.H_dPhi_ll->Fill(abs(L1.DeltaPhi(L2)));
				hc.H_Truth_DeltaR_ll->Fill(L1.DeltaR(L2));

				hc.H_Pt_l1->Fill(L1.Pt());
				hc.H_Pt_lv1->Fill(Lv1.Pt());
				hc.H_Pt_l2->Fill(L2.Pt());
				hc.H_Pt_lv2->Fill(Lv2.Pt());
				hc.H_Eta_l1->Fill(L1.Eta());
				hc.H_Eta_l2->Fill(L2.Eta());
				hc.H_Phi_l1->Fill(L1.Phi());
				hc.H_Phi_l2->Fill(L2.Phi());

				if (L1.Pt() > L2.Pt()){
		    		hc.H_Truth_LeadingLepton_Pt->Fill(L1.Pt());
		    		hc.H_Truth_LeadingLepton_Eta->Fill(L1.Eta());
		    		hc.H_Truth_LeadingLepton_Phi->Fill(L1.Phi());
		    		hc.H_Truth_LeadingLepton_Mass->Fill(L1.M());
		    		hc.H_Truth_SubleadingLepton_Pt->Fill(L2.Pt());
		   			hc.H_Truth_SubleadingLepton_Eta->Fill(L2.Eta());
		    		hc.H_Truth_SubleadingLepton_Phi->Fill(L2.Phi());
		    		hc.H_Truth_SubleadingLepton_Mass->Fill(L2.M());
				}
				else{
		    		hc.H_Truth_LeadingLepton_Pt->Fill(L2.Pt());
		    		hc.H_Truth_LeadingLepton_Eta->Fill(L2.Eta());
		    		hc.H_Truth_LeadingLepton_Phi->Fill(L2.Phi());
		    		hc.H_Truth_LeadingLepton_Mass->Fill(L2.M());
		    		hc.H_Truth_SubleadingLepton_Pt->Fill(L1.Pt());
		   			hc.H_Truth_SubleadingLepton_Eta->Fill(L1.Eta());
		    		hc.H_Truth_SubleadingLepton_Phi->Fill(L1.Phi());
		    		hc.H_Truth_SubleadingLepton_Mass->Fill(L1.M());			
				}
			}
			else {	/*log <<"Not a good thruth-level event"<<endl;*/ }

			// ================================================================ TRUTH LEVEL FILLS ======================================================== //

			// ================================================================ RECO  LEVEL LEPTON FILLS ======================================================== //
			hc.H_Reco_nLeptons->Fill(ev.Lepton_id->size());
			bool GoodLeptonsFound = 1/*(Reco_LeadingLepton.Pt()>22 && Reco_SubleadingLepton.Pt()>15)*/;
			if (GoodLeptonsFound){
				GoodRecoEvents++;
				//log<<"Good reco-level event"<<endl;
				//log<<"LeadingPt = "<<LeadingPt/1000<<" at "<<i_Reco_LeadingLepton<<"\tSubleadingPt = "<<SubleadingPt/1000<<" at "<<i_Reco_SubleadingLepton<<endl;
				hc.H_Reco_LeadingLepton_Pt->Fill(Reco_LeadingLepton.Pt());
				hc.H_Reco_LeadingLepton_Eta->Fill(Reco_LeadingLepton.Eta());
				hc.H_Reco_LeadingLepton_Phi->Fill(Reco_LeadingLepton.Phi());
				hc.H_Reco_LeadingLepton_Mass->Fill(Reco_LeadingLepton.M());
				hc.H_Reco_SubleadingLepton_Pt->Fill(Reco_SubleadingLepton.Pt());
				hc.H_Reco_SubleadingLepton_Eta->Fill(Reco_SubleadingLepton.Eta());
				hc.H_Reco_SubleadingLepton_Phi->Fill(Reco_SubleadingLepton.Phi());
				hc.H_Reco_SubleadingLepton_Mass->Fill(Reco_SubleadingLepton.M());	

				if (Reco_LeadingLepton.DeltaR(Reco_SubleadingLepton) < 0.1){ /*log<<"ERROR\n\n"<<endl; */}
				//cout<<"Filling Reco mass: "<<(Reco_LeadingLepton+Reco_SubleadingLepton).M()<<endl;
				hc.H_Reco_DeltaR_ll->Fill(Reco_LeadingLepton.DeltaR(Reco_SubleadingLepton));
				hc.H_Reco_Mass_ll->Fill((Reco_LeadingLepton+Reco_SubleadingLepton).M());
			}
			else {/*log<<"Not a good reco-level event"<<endl;*/}
			// ================================================================ RECO  LEVEL LEPTON FILLS ======================================================== //




			// ================================================================ RECO  LEVEL BJET FILLS ======================================================== //
			hc.H_Reco_nBJets->Fill(ev.nBJets);
			bool GoodBJetsFound = 1/*(Reco_LeadingLepton.Pt()>22 && Reco_SubleadingLepton.Pt()>15)*/;
			if (GoodBJetsFound){
				GoodRecoEvents++;
				//log<<"Good reco-level event"<<endl;
				//log<<"LeadingPt = "<<LeadingPt/1000<<" at "<<i_Reco_LeadingLepton<<"\tSubleadingPt = "<<SubleadingPt/1000<<" at "<<i_Reco_SubleadingLepton<<endl;
				hc.H_Reco_LeadingBJet_Pt->Fill(Reco_LeadingBJet.Pt());
				hc.H_Reco_LeadingBJet_Eta->Fill(Reco_LeadingBJet.Eta());
				hc.H_Reco_LeadingBJet_Phi->Fill(Reco_LeadingBJet.Phi());
				hc.H_Reco_LeadingBJet_Mass->Fill(Reco_LeadingBJet.M());
				hc.H_Reco_SubleadingBJet_Pt->Fill(Reco_SubleadingBJet.Pt());
				hc.H_Reco_SubleadingBJet_Eta->Fill(Reco_SubleadingBJet.Eta());
				hc.H_Reco_SubleadingBJet_Phi->Fill(Reco_SubleadingBJet.Phi());
				hc.H_Reco_SubleadingBJet_Mass->Fill(Reco_SubleadingBJet.M());	
				hc.H_Reco_BJets_DeltaPhi->Fill(abs(Reco_LeadingBJet.DeltaPhi(Reco_SubleadingBJet)));
				if (Reco_LeadingBJet.DeltaR(Reco_SubleadingBJet) < 0.1){/* log<<"ERROR\n\n"<<endl; */}
				//cout<<"Filling Reco mass: "<<(Reco_LeadingLepton+Reco_SubleadingLepton).M()<<endl;
				hc.H_Reco_DeltaR_bb->Fill(Reco_LeadingBJet.DeltaR(Reco_SubleadingBJet));
				hc.H_Reco_Mass_bb->Fill((Reco_LeadingBJet+Reco_SubleadingBJet).M());
			}
			else {/*log<<"Not a good reco-level event"<<endl;*/}
		// ================================================================ RECO  LEVEL BJET FILLS ======================================================== //

		}	// End of Event loop



		if (Write){
			std::cout<<GoodRecoEvents<<" good reco events"<<std::endl;

			// Create the corresponding Histogram File and and copy the histograms in the container to the file.
			string histfile = "HistogramFiles/0324_llbb/Histograms_" + (string)fname.Data();
			const char *HistFile = histfile.c_str();

			// Fill the hist file with empty histograms
		    TFile *hf= TFile::Open(HistFile,"RECREATE");

		    for (int ih=0; ih < (hc.List).size(); ih++){		    	
		    	// Declare an empty TH1F with same properties as the one in the container
		    	const char *name = hc.List[ih]->GetName();
		    	const char *title = hc.List[ih]->GetTitle();
		    	int nbins = hc.List[ih]->GetSize();
		    	double xmin = hc.List[ih]->GetXaxis()->GetXmin();
		    	double xmax = hc.List[ih]->GetXaxis()->GetXmax();
		    	TH1F* h = new TH1F(name,title,nbins-2,xmin,xmax);
		    	//std::cout<<nbins<<"\t"<<xmin<<"\t"<<xmax<<"\t"<<name<<std::endl;
		    	// Add the filled histogram from the container to the empty one in the file
		       	h->Add(hc.List[ih]);

		    }

		    // Write the file so all histograms are saved
		    hf->Write();

		} // End of if (Write)
	} // End of file loop
	gApplication->Terminate();
}


