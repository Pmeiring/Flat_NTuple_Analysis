#ifndef _hists_
#define _hists_

#include "TTree.h"

struct HistogramContainer{
  	HistogramContainer(){
    	//g_nw=0; 
  	}
  	//int g_nw;
	TH1F *H_size = new TH1F("H_size","Amount of particles",10000,0,10000);						//1
    TH1F *H_PID = new TH1F("H_PID","Particle PID",100,0,100);

	TH1F *H_gx1 = new TH1F("H_gx1","gx1",100,0.0,1.0);											//3
	TH1F *H_gx2 = new TH1F("H_gx2","gx2",100,0.0,1.0);
	TH1F *H_gcm = new TH1F("H_gcm","Center of mass energy gluons",200,0.0,2000);
	TH1F *H_qx1 = new TH1F("H_qx1","qx1",100,0.0,1.0);
	TH1F *H_qx2 = new TH1F("H_qx2","qx2",100,0.0,1.0);
	TH1F *H_qcm = new TH1F("H_qcm","Center of mass energy quarks",200,0.0,2000);

    TH1F *H_Mass_hh = new TH1F("H_Mass_hh","Invariant mass Higgs-pair",100,0,1000);				//9
    TH1F *H_Pt_h1 = new TH1F("H_Pt_h1"," pt_{h1}",101,-10,1000);
    TH1F *H_Pt_h2 = new TH1F("H_Pt_h2"," pt_{h2}",101,-10,1000);

    TH1F *H_Mass_bb = new TH1F("H_Mass_bb","Invariant mass bb",50,0,500);						//12
	TH1F *H_dEta_bb = new TH1F("H_dEta_bb","#Delta #eta_{bb}",200,-10,10);
	TH1F *H_dPhi_bb = new TH1F("H_dPhi_bb","#Delta #phi_{b#bar{b}}",100,-8,8);
    TH1F *H_Pt_b = new TH1F("H_Pt_b"," pt_{b}",101,-10,1000);
    TH1F *H_Pt_bbar = new TH1F("H_Pt_bbar"," pt_{#bar{b}}",101,-10,1000);
    TH1F *H_Eta_b = new TH1F("H_Eta_b"," #eta_{b}",100,0,5);
    TH1F *H_Eta_bbar = new TH1F("H_Eta_bbar","#eta_{#bar{b}}",100,0,5);
	TH1F *H_Phi_b = new TH1F("H_Phi_b","#phi_{b}",100,-4,4);
	TH1F *H_Phi_bbar = new TH1F("H_Phi_bbar","#phi_{#bar{b}}",100,-4,4);						//20

    TH1F *H_Mass_ww = new TH1F("H_Mass_ww","Invariant mass W+W-",50,0,500);						//21
    TH1F *H_Pt_wm = new TH1F("H_Pt_wp"," pt_{W-}",101,-10,1000);
    TH1F *H_Pt_wp = new TH1F("H_Pt_wm"," pt_{w+}",101,-10,1000);
    TH1F *H_Mass_wp = new TH1F("H_Mass_wp","Invariant mass llv",50,0,500);
    TH1F *H_Mass_wm = new TH1F("H_Mass_wm","Invariant mass llv",50,0,500);						//25					

	TH1F *H_Mass_wp_found = new TH1F("H_Mass_wp_found","Invariant mass llv",50,0,300);
    TH1F *H_Mass_wp_missing = new TH1F("H_Mass_wp_missing","Invariant mass llv",50,0,300);
    TH1F *H_Mass_wm_found = new TH1F("H_Mass_wm_found","Invariant mass llv",50,0,300);
    TH1F *H_Mass_wm_missing = new TH1F("H_Mass_wm_missing","Invariant mass llv",50,0,300);		//29

	TH1F *H_Mass_ll = new TH1F("H_Mass_ll","Mass_{ll}",100,0,1000);								//30
	TH1F *H_dEta_ll = new TH1F("H_dEta_ll","#Delta #eta_{ll}",200,-10,10);
	TH1F *H_dTheta_ll = new TH1F("H_dTheta_ll","#Delta #theta_{ll}",100,-4,4);
	TH1F *H_dPhi_ll = new TH1F("H_dPhi_ll","#Delta #phi_{ll}",100,-8,8);
    TH1F *H_Pt_l1 = new TH1F("H_Pt_l1"," pt_{l}",101,-5,500);
    TH1F *H_Pt_lv1 = new TH1F("H_Pt_lv1"," pt_{lv}",101,-5,500);
    TH1F *H_Pt_l2 = new TH1F("H_Pt_l2"," pt_{l}",101,-5,500);
    TH1F *H_Pt_lv2 = new TH1F("H_Pt_lv2"," pt_{lv}",101,-5,500);
    TH1F *H_Eta_l1 = new TH1F("H_Eta_l1","#eta_{l+}",100,0,5);
    TH1F *H_Eta_l2 = new TH1F("H_Eta_l2","#eta_{l-}",100,0,5);
    TH1F *H_Phi_l1 = new TH1F("H_Phi_l1","#phi_{l+}",100,-4,4);
    TH1F *H_Phi_l2 = new TH1F("H_Phi_l2","#phi_{l-}",100,-4,4);									//41

    TH1F *H_nJets = new TH1F("H_nJets","Amount of jets",20,0,20);
    TH1F *H_nbJets = new TH1F("H_nbJets","Amount of b-jets",20,0,20);
    TH1F *H_JetPt = new TH1F("H_JetPt"," Jet Pt",100,0,500);
    TH1F *H_JetEta = new TH1F("H_JetEta"," Jet Eta",200,-10,10);
    TH1F *H_JetPhi = new TH1F("H_JetPhi"," Jet Phi",100,-4,4);
    TH1F *H_JetMass = new TH1F("H_JetMass"," Jet Mass",100,0,100);
    TH1F *H_JetDeltaEta = new TH1F("H_JetDeltaEta","Delta #eta_{jet}",200,-10,10);
    TH1F *H_JetDeltaPhi = new TH1F("H_JetDeltaPhi","Delta #phi_{jet}",100,-8,8);
    TH1F *H_DeltaPt_Jet_B = new TH1F("H_DeltaPt_Jet_B","Delta pt_{b}",200,-100,100);
    TH1F *H_DeltaEta_Jet_B = new TH1F("H_DeltaEta_Jet_B","Delta #eta_{b}",200,-10,10);
    TH1F *H_DeltaPhi_Jet_B = new TH1F("H_DeltaPhi_Jet_B","Delta #phi_{b}",100,-8,8);
    TH1F *H_bJetPt = new TH1F("H_bJetPt"," bJet Pt",100,0,500);
    TH1F *H_bJetEta = new TH1F("H_bJetEta"," bJet Eta",200,-10,10);
    TH1F *H_bJetPhi = new TH1F("H_bJetPhi"," bJet Phi",100,-4,4);
    TH1F *H_bJetMass = new TH1F("H_bJetMass"," bJet Mass",100,0,100);							//56

    TH1F *H_bJets_DeltaEta = new TH1F("H_bJets_DeltaEta","#Delta #eta_{bjets}",200,-10,10);
    TH1F *H_bJets_DeltaPhi = new TH1F("H_bJets_DeltaPhi","#Delta #phi_{bjets}",100,-8,8);
    TH1F *H_bJets_DeltaPhi_100 = new TH1F("H_bJets_DeltaPhi_100","#Delta #phi_{bjets}",100,-8,8);
    TH1F *H_bJets_DeltaPhi_200 = new TH1F("H_bJets_DeltaPhi_200","#Delta #phi_{bjets}",100,-8,8);
    TH1F *H_bJets_DeltaPhi_300 = new TH1F("H_bJets_DeltaPhi_300","#Delta #phi_{bjets}",100,-8,8);
    TH1F *H_bJets_DeltaPhi_400 = new TH1F("H_bJets_DeltaPhi_400","#Delta #phi_{bjets}",100,-8,8);
    TH1F *H_bJets_DeltaPhi_up = new TH1F("H_bJets_DeltaPhi_up","#Delta #phi_{bjets}",100,-8,8);		//63

    TH1F *H_bJets_DeltaR = new TH1F("H_bJets_DeltaR","#Delta R_{bjets}",100,0,10);
    TH1F *H_bJets_Mass = new TH1F("H_bJets_Mass"," Invariant mass of two leading b-jets",100,0,1000);		//65

    TH1F *H_Bfragmentation = new TH1F("H_Bfragmentation","|p_{jet}|/|p_{b}|",100,0,2);
    TH1F *H_Bbarfragmentation = new TH1F("H_Bbarfragmentation","|p_{jet}|/|p_{bbar}|",100,0,2);
    TH1F *H_BHadfragmentation = new TH1F("H_BHadfragmentation","|p_{had}|/|p_{b}|",100,0,2);
    TH1F *H_BbarHadfragmentation = new TH1F("H_BbarHadfragmentation","|p_{had}|/|p_{bbar}|",100,0,2);		//69

    TH1F *H_Truth_LeadingLepton_Pt =  new TH1F("H_Truth_LeadingLepton_Pt"," Leading lepton p_{T} [GeV]",101,-5,500);
    TH1F *H_Truth_LeadingLepton_Eta = new TH1F("H_Truth_LeadingLepton_Eta"," #eta_{l_a}",200,-10,10);
    TH1F *H_Truth_LeadingLepton_Phi = new TH1F("H_Truth_LeadingLepton_Phi"," #phi_{l_a}",100,-4,4);
    TH1F *H_Truth_LeadingLepton_Mass =new TH1F("H_Truth_LeadingLepton_Mass"," Mass_{l_a}",100,0,100);
    TH1F *H_Truth_SubleadingLepton_Pt =  new TH1F("H_Truth_SubleadingLepton_Pt"," pt_{l_b}",101,-5,500);
    TH1F *H_Truth_SubleadingLepton_Eta = new TH1F("H_Truth_SubleadingLepton_Eta"," #eta_{l_b}",200,-10,10);
    TH1F *H_Truth_SubleadingLepton_Phi = new TH1F("H_Truth_SubleadingLepton_Phi"," #phi_{l_b}",100,-4,4);
    TH1F *H_Truth_SubleadingLepton_Mass =new TH1F("H_Truth_SubleadingLepton_Mass"," Mass_{l_b}",100,0,100);	//77
    TH1F *H_Truth_DeltaR_ll = new TH1F("H_Truth_DeltaR_ll"," #Delta R_{ll}",100,0,10);

    TH1F *H_Reco_LeadingLepton_Pt =  new TH1F("H_Reco_LeadingLepton_Pt"," Leading lepton p_{T} [GeV]",10,0,600);
    TH1F *H_Reco_LeadingLepton_Eta = new TH1F("H_Reco_LeadingLepton_Eta"," #eta_{l_a}",200,-10,10);
    TH1F *H_Reco_LeadingLepton_Phi = new TH1F("H_Reco_LeadingLepton_Phi"," #phi_{l_a}",100,-4,4);
    TH1F *H_Reco_LeadingLepton_Mass =new TH1F("H_Reco_LeadingLepton_Mass"," Mass_{l_a}",100,0,100);
    TH1F *H_Reco_SubleadingLepton_Pt =  new TH1F("H_Reco_SubleadingLepton_Pt"," Sub-leading lepton p_{T} [GeV]",22,0,330);
    TH1F *H_Reco_SubleadingLepton_Eta = new TH1F("H_Reco_SubleadingLepton_Eta"," #eta_{l_b}",200,-10,10);
    TH1F *H_Reco_SubleadingLepton_Phi = new TH1F("H_Reco_SubleadingLepton_Phi"," #phi_{l_b}",100,-4,4);
    TH1F *H_Reco_SubleadingLepton_Mass =new TH1F("H_Reco_SubleadingLepton_Mass"," Mass_{l_b}",100,0,100);	//86
    TH1F *H_Reco_DeltaR_ll = new TH1F("H_Reco_DeltaR_ll"," #Delta R_{ll}",20,0,6);
    TH1F *H_Reco_Mass_ll = new TH1F("H_Reco_Mass_ll"," m_{ll} [GeV]",20,0,1200);
    TH1F *H_Reco_TransMass = new TH1F("H_Reco_TransMass"," m_T ",100,0,1000);
    TH1F *H_Reco_nLeptons = new TH1F("H_Reco_nLeptons","Number of leptons",20,0,20);

    TH1F *H_Reco_LeadingBJet_Pt =  new TH1F("H_Reco_LeadingBJet_Pt"," Leading b-jet p_{T} [GeV]",10,0,600);
    TH1F *H_Reco_LeadingBJet_Eta = new TH1F("H_Reco_LeadingBJet_Eta"," #eta_{b_a}",200,-10,10);
    TH1F *H_Reco_LeadingBJet_Phi = new TH1F("H_Reco_LeadingBJet_Phi"," #phi_{b_a}",100,-4,4);
    TH1F *H_Reco_LeadingBJet_Mass =new TH1F("H_Reco_LeadingBJet_Mass"," Mass_{b_a}",100,0,100);
    TH1F *H_Reco_SubleadingBJet_Pt =  new TH1F("H_Reco_SubleadingBJet_Pt"," Sub-leading b-jet p_{T} [GeV]",20,0,200);
    TH1F *H_Reco_SubleadingBJet_Eta = new TH1F("H_Reco_SubleadingBJet_Eta"," #eta_{b_b}",200,-10,10);
    TH1F *H_Reco_SubleadingBJet_Phi = new TH1F("H_Reco_SubleadingBJet_Phi"," #phi_{b_b}",100,-4,4);
    TH1F *H_Reco_SubleadingBJet_Mass =new TH1F("H_Reco_SubleadingBJet_Mass"," Mass_{b_b}",100,0,100);   //86
    TH1F *H_Reco_DeltaR_bb = new TH1F("H_Reco_DeltaR_bb"," #Delta R_{bb}",20,0,6);
    TH1F *H_Reco_Mass_bb = new TH1F("H_Reco_Mass_bb"," m_{bb} [GeV]",8,100,140);
    //TH1F *H_Reco_TransMass = new TH1F("H_Reco_TransMass"," m_T ",100,0,1000);
    TH1F *H_Reco_nBJets = new TH1F("H_Reco_nBJets","Number of b-jets",20,0,20);
    TH1F *H_Reco_BJets_DeltaPhi = new TH1F("H_Reco_BJets_DeltaPhi","|#Delta #phi_{bb}|",10,0,3.20);







    std::vector<TH1F*> List{
    	H_size,H_PID,H_gx1,H_gx2,H_gcm,H_qx1,H_qx2,H_qcm,
    	H_Mass_hh,H_Pt_h1,H_Pt_h2,
    	H_Mass_bb,H_dEta_bb,H_dPhi_bb,H_Pt_b,H_Pt_bbar,H_Eta_b,H_Eta_bbar,H_Phi_b,H_Phi_bbar,
    	H_Mass_ww,H_Pt_wm,H_Pt_wp,H_Mass_wp,H_Mass_wm,
    	H_Mass_wp_found,H_Mass_wp_missing,H_Mass_wm_found,H_Mass_wm_missing,
    	H_Mass_ll,H_dEta_ll,H_dTheta_ll,H_dPhi_ll,H_Pt_l1,H_Pt_lv1,H_Pt_l2,H_Pt_lv2,H_Eta_l1,H_Eta_l2,H_Phi_l1,H_Phi_l2,
    	H_nJets,H_nbJets,H_JetPt,H_JetEta,H_JetPhi,H_JetMass,H_JetDeltaEta,H_JetDeltaPhi,H_DeltaPt_Jet_B,H_DeltaEta_Jet_B,H_DeltaPhi_Jet_B,H_bJetPt,H_bJetEta,H_bJetPhi,H_bJetMass,
    	H_bJets_DeltaEta,H_bJets_DeltaPhi,H_bJets_DeltaPhi_100,H_bJets_DeltaPhi_200,H_bJets_DeltaPhi_300,H_bJets_DeltaPhi_400,H_bJets_DeltaPhi_up,
    	H_bJets_DeltaR,H_bJets_Mass,
    	H_Bfragmentation,H_Bbarfragmentation,H_BHadfragmentation,H_BbarHadfragmentation,
    	H_Truth_LeadingLepton_Pt,H_Truth_LeadingLepton_Eta,H_Truth_LeadingLepton_Phi,H_Truth_LeadingLepton_Mass,H_Truth_SubleadingLepton_Pt,H_Truth_SubleadingLepton_Eta,H_Truth_SubleadingLepton_Phi,H_Truth_SubleadingLepton_Mass,H_Truth_DeltaR_ll,
    	H_Reco_LeadingLepton_Pt,H_Reco_LeadingLepton_Eta,H_Reco_LeadingLepton_Phi,H_Reco_LeadingLepton_Mass,H_Reco_SubleadingLepton_Pt,H_Reco_SubleadingLepton_Eta,H_Reco_SubleadingLepton_Phi,H_Reco_SubleadingLepton_Mass,H_Reco_DeltaR_ll,H_Reco_Mass_ll,H_Reco_TransMass,H_Reco_nLeptons,
        H_Reco_LeadingBJet_Pt,H_Reco_LeadingBJet_Eta,H_Reco_LeadingBJet_Phi,H_Reco_LeadingBJet_Mass,H_Reco_SubleadingBJet_Pt,H_Reco_SubleadingBJet_Eta,H_Reco_SubleadingBJet_Phi,H_Reco_SubleadingBJet_Mass,H_Reco_DeltaR_bb,H_Reco_Mass_bb,H_Reco_nBJets,H_Reco_BJets_DeltaPhi
    };
};


#endif