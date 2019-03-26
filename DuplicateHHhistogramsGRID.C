#include "TROOT.h"
#include "TFile.h"
#include "TTree.h"
#include "TBrowser.h"
#include "TH2.h"
#include "TRandom.h"
#include "/afs/cern.ch/work/p/pmeiring/private/ATLAS/My_FlatTuple_Analysis_01/Headers/PadSyntax.h"
#include "/afs/cern.ch/work/p/pmeiring/private/ATLAS/My_FlatTuple_Analysis_01/Headers/ProcessHandler.h"
#include "/afs/cern.ch/work/p/pmeiring/private/ATLAS/My_FlatTuple_Analysis_01/Headers/Hists.h"
#include "/afs/cern.ch/work/p/pmeiring/private/ATLAS/My_FlatTuple_Analysis_01/Headers/ScaleFactors.h"


void DuplicateHHhistogramsGRID(){
 	// Multi-threading
    ROOT::EnableImplicitMT();

    int i11 = 78;
	int i111 = i11;
	int i112 = i11;
	int i113 = i11;
	int i114 = i11;
	int i115 = i11;
	int i116 = i11;
	int i117 = i11;
	int i118 = i11;

	int i12 = 82;
	int i121 = i12;
	int i122 = i12;
	int i123 = i12;
	int i124 = i12;
	int i125 = i12;
	int i126 = i12;
	int i127 = i12;
	int i128 = i12;

	int i13 = 86;
	int i131 = i13;
	int i132 = i13;
	int i133 = i13;
	int i134 = i13;
	int i135 = i13;
	int i136 = i13;
	int i137 = i13;
	int i138 = i13;

	int i14 = 87;
	int i141 = i14;
	int i142 = i14;
	int i143 = i14;
	int i144 = i14;
	int i145 = i14;
	int i146 = i14;
	int i147 = i14;
	int i148 = i14;

    int i21 = 90;
	int i211 = i21;
	int i212 = i21;
	int i213 = i21;
	int i214 = i21;
	int i215 = i21;
	int i216 = i21;
	int i217 = i21;
	int i218 = i21;

	int i22 = 94;
	int i221 = i22;
	int i222 = i22;
	int i223 = i22;
	int i224 = i22;
	int i225 = i22;
	int i226 = i22;
	int i227 = i22;
	int i228 = i22;

	int i23 = 101;
	int i231 = i23;
	int i232 = i23;
	int i233 = i23;
	int i234 = i23;
	int i235 = i23;
	int i236 = i23;
	int i237 = i23;
	int i238 = i23;

	int i24 = 99;
	int i241 = i24;
	int i242 = i24;
	int i243 = i24;
	int i244 = i24;
	int i245 = i24;
	int i246 = i24;
	int i247 = i24;
	int i248 = i24;

	//std::vector<std::vector<TH1F*>> MasterHistogram;
	std::vector<TH1F*> MasterHistogram[8];
	//std::vector<std::string> label;
	std::string label[8];
	//std::vector<float> CrossSection;
	//std::vector<float> Scale;

	// Declare paths and open file
    const char *dirname = "/afs/cern.ch/work/p/pmeiring/private/ATLAS/My_FlatTuple_Analysis_01/HistogramFiles/0324_llbb/";
	const char *ext=".root";
	TSystemDirectory dir(dirname, dirname);
	TList *files = dir.GetListOfFiles();
	if (!files) abort();
	TSystemFile *file;
	TString fname; std::vector<std::string> fnames; 
	TIter nextf(files); int CurrentProcess=-1; 
	int hh=0; int tt=1; int zjets=2; int dy=3; int ttv=4; int singleh=5; int vv=6; int wt=7;
	while ((file=(TSystemFile*)nextf())){
		fname = file->GetName();

		// If it is a directory or not a root file, continue
		bool GoodFile = (!file->IsDirectory() && fname.EndsWith(ext));
		if (!GoodFile) {continue;}

		std::cout<<"\nReading histograms from: "<<file->GetName()<<std::endl;	

		// Construct filename (complete path) and open file
		fnames.push_back((std::string)fname.Data());
		std::string filename = (std::string)dirname + (std::string)fname.Data();
		const char *fileName = filename.c_str();
	    TFile *File= TFile::Open(fileName);

	    // Check if there is a process known to correspond to the data file
		Process process;
		float ScaleFactor;
		bool ProcessKnown = ReadGridProcess(process,(std::string)fname.Data());
		if (!ProcessKnown) {std::cout<<"Process not known, please check which files you are handling..."<<std::endl; abort();}
		else {
			std::cout<<process.ProcessAbrev<<std::endl;
			if (process.ProcessAbrev=="tt") 		{CurrentProcess=tt;}
			if (process.ProcessAbrev=="hh") 		{CurrentProcess=hh;}
			if (process.ProcessAbrev=="Z+jets") 	{CurrentProcess=zjets;}
			if (process.ProcessAbrev=="Wt") 		{CurrentProcess=wt;}
			if (process.ProcessAbrev=="DY") 		{CurrentProcess=dy;}
			if (process.ProcessAbrev=="tt+V") 		{CurrentProcess=ttv;}
			if (process.ProcessAbrev=="singleH")	{CurrentProcess=singleh;}
			if (process.ProcessAbrev=="VV") 		{CurrentProcess=vv;}

			ScaleFactor = DetermineScaleFactor(process.DSID);	
		}

		
		bool FirstOfItsKind = (MasterHistogram[CurrentProcess].size()==0); // 1 if file is first of it's kind; 0 if Masterhistogram already contains hists
		if (FirstOfItsKind) {
			label[CurrentProcess] = process.ProcessAbrev.c_str();
		}	

		// Get a list of keys for each file; if it corresponds to a TH1F, push_back MasterHistogram
		TKey *key1;	TObject* obj1; int i=0;
		TIter next(File->GetListOfKeys());
		while ((key1=(TKey*)next())){

			obj1 = key1->ReadObj();
			if (obj1->InheritsFrom(TH1F::Class())){
				TH1F *h = (TH1F*)obj1;
				h->Scale(ScaleFactor);

				if (FirstOfItsKind) {MasterHistogram[CurrentProcess].push_back(h);}
				else 				{MasterHistogram[CurrentProcess][i]->Add(h);}
				
				if (FirstOfItsKind) {cout<<i<<"\t"<<h->GetName()<<"\t"<<h->GetTitle()<<endl;}
				i++;
			}
		}
	}
	
	cout<<"\n\nInitialized MasterHistogram"<<endl;
	Color_t color[8] = {};
	color[tt] 	   = kCyan-1;
	color[hh] 	   = kRed;
	color[zjets]   = kOrange+2;
	color[dy] 	   = kOrange+1;
	color[singleh] = kRed-4;
	color[vv] 	   = kYellow-10;
	color[wt] 	   = kSpring+3;
	color[ttv] 	   = kYellow+4;

	gStyle->SetOptStat(0);
    TCanvas *c1 = new TCanvas("c1","Canvas",900,900);
	c1->SetFillStyle(4000); //will be transparent
	c1->Divide(2,2);

	

	c1->cd(1);

		gStyle->SetLineWidth(1);
		 THStack *hs11 = new THStack("hs11","");

		for (int iH = 0; iH < 8; iH++){
			if (iH == hh) {
				MasterHistogram[iH][i111]->SetLineColor(color[iH]);
				MasterHistogram[iH][i111]->SetLineStyle(9);
			}
			else {
				MasterHistogram[iH][i111]->SetFillColor(color[iH]);
				MasterHistogram[iH][i111]->SetLineColor(kBlack);
			}
		}

		hs11->Add(MasterHistogram[vv][i111]);
		hs11->Add(MasterHistogram[singleh][i111]);
		hs11->Add(MasterHistogram[ttv][i111]);
		hs11->Add(MasterHistogram[dy][i111]);
		hs11->Add(MasterHistogram[wt][i111]);
		hs11->Add(MasterHistogram[zjets][i111]);
		hs11->Add(MasterHistogram[tt][i111]);

		hs11->SetMinimum(1e-2);

		hs11->SetMaximum(2e8);

		hs11->Draw("HIST");
		hs11->GetXaxis()->SetTitle(MasterHistogram[0][i111]->GetTitle());
		//hs11->GetXaxis()->SetNdivisions(9);

		hs11->GetYaxis()->SetNdivisions(6);

		MasterHistogram[hh][i111]->Draw("same");

		gPad->Modified();
		gPad->SetLogy();

		TLatex t111(0,0.95,"Events #upoint #frac{140 fb^{-1}}{Total events/#sigma} ");   t111.SetNDC(kTRUE);   t111.SetTextSize(0.030); t111.Draw("same");

		std::ostringstream oss112;
		oss112 << "#splitline{#sqrt{s} = 13 TeV, 140 fb^{-1} }{m_{bb} #in [100,140]}";	std::string var112 = oss112.str();
		TLatex t112(.2,.8,var112.c_str());    t112.SetTextSize(0.03);
		t112.SetNDC(kTRUE);
		t112.Draw();
		auto legend11 = new TLegend(.6,.75,.9,.9);

		legend11->SetNColumns(2);
		legend11->AddEntry(MasterHistogram[vv][i111],(label[vv]).c_str(),"f");
		legend11->AddEntry(MasterHistogram[hh][i112],(label[hh]).c_str(),"l");
		legend11->AddEntry(MasterHistogram[singleh][i113],(label[singleh]).c_str(),"f");
		legend11->AddEntry(MasterHistogram[ttv][i114],(label[ttv]).c_str(),"f");
		legend11->AddEntry(MasterHistogram[dy][i115],(label[dy]).c_str(),"f");
		legend11->AddEntry(MasterHistogram[wt][i116],(label[wt]).c_str(),"f");
		legend11->AddEntry(MasterHistogram[zjets][i117],(label[zjets]).c_str(),"f");
		legend11->AddEntry(MasterHistogram[tt][i118],(label[tt]).c_str(),"f");
		legend11->Draw("same");


	c1->cd(2);

		gStyle->SetLineWidth(1);
		 THStack *hs12 = new THStack("hs12","");

		for (int iH = 0; iH < 8; iH++){
			if (iH == hh) {
				MasterHistogram[iH][i121]->SetLineColor(color[iH]);
				MasterHistogram[iH][i121]->SetLineStyle(9);
			}
			else {
				MasterHistogram[iH][i121]->SetFillColor(color[iH]);
				MasterHistogram[iH][i121]->SetLineColor(kBlack);
			}
		}

		hs12->Add(MasterHistogram[vv][i121]);
		hs12->Add(MasterHistogram[singleh][i121]);
		hs12->Add(MasterHistogram[ttv][i121]);
		hs12->Add(MasterHistogram[dy][i121]);
		hs12->Add(MasterHistogram[wt][i121]);
		hs12->Add(MasterHistogram[zjets][i121]);
		hs12->Add(MasterHistogram[tt][i121]);

		hs12->SetMinimum(1e-2);

		hs12->SetMaximum(2e8);

		hs12->Draw("HIST");
		hs12->GetXaxis()->SetTitle(MasterHistogram[0][i121]->GetTitle());
		//hs12->GetXaxis()->SetNdivisions(9);

		hs12->GetYaxis()->SetNdivisions(6);

		MasterHistogram[hh][i121]->Draw("same");

		gPad->Modified();
		gPad->SetLogy();

		TLatex t121(0,0.95,"Events #upoint #frac{140 fb^{-1}}{Total events/#sigma} ");   t121.SetNDC(kTRUE);   t121.SetTextSize(0.030); t121.Draw("same");

		std::ostringstream oss122;
		oss122 << "#splitline{#sqrt{s} = 13 TeV, 140 fb^{-1} }{m_{bb} #in [100,140]}";	std::string var122 = oss122.str();
		TLatex t122(.2,.8,var122.c_str());    t122.SetTextSize(0.03);
		t122.SetNDC(kTRUE);
		t122.Draw();
		auto legend12 = new TLegend(.6,.75,.9,.9);

		legend12->SetNColumns(2);
		legend12->AddEntry(MasterHistogram[vv][i121],(label[vv]).c_str(),"f");
		legend12->AddEntry(MasterHistogram[hh][i122],(label[hh]).c_str(),"l");
		legend12->AddEntry(MasterHistogram[singleh][i123],(label[singleh]).c_str(),"f");
		legend12->AddEntry(MasterHistogram[ttv][i124],(label[ttv]).c_str(),"f");
		legend12->AddEntry(MasterHistogram[dy][i125],(label[dy]).c_str(),"f");
		legend12->AddEntry(MasterHistogram[wt][i126],(label[wt]).c_str(),"f");
		legend12->AddEntry(MasterHistogram[zjets][i127],(label[zjets]).c_str(),"f");
		legend12->AddEntry(MasterHistogram[tt][i128],(label[tt]).c_str(),"f");
		legend12->Draw("same");



	c1->cd(3);

		gStyle->SetLineWidth(1);
		 THStack *hs13 = new THStack("hs13","");

		for (int iH = 0; iH < 8; iH++){
			if (iH == hh) {
				MasterHistogram[iH][i131]->SetLineColor(color[iH]);
				MasterHistogram[iH][i131]->SetLineStyle(9);
			}
			else {
				MasterHistogram[iH][i131]->SetFillColor(color[iH]);
				MasterHistogram[iH][i131]->SetLineColor(kBlack);
			}
		}

		hs13->Add(MasterHistogram[vv][i131]);
		hs13->Add(MasterHistogram[singleh][i131]);
		hs13->Add(MasterHistogram[ttv][i131]);
		hs13->Add(MasterHistogram[dy][i131]);
		hs13->Add(MasterHistogram[wt][i131]);
		hs13->Add(MasterHistogram[zjets][i131]);
		hs13->Add(MasterHistogram[tt][i131]);

		hs13->SetMinimum(1e-2);

		hs13->SetMaximum(2e8);

		hs13->Draw("HIST");
		hs13->GetXaxis()->SetTitle(MasterHistogram[0][i131]->GetTitle());
		//hs13->GetXaxis()->SetNdivisions(9);

		hs13->GetYaxis()->SetNdivisions(6);

		MasterHistogram[hh][i131]->Draw("same");

		gPad->Modified();
		gPad->SetLogy();

		TLatex t131(0,0.95,"Events #upoint #frac{140 fb^{-1}}{Total events/#sigma} ");   t131.SetNDC(kTRUE);   t131.SetTextSize(0.030); t131.Draw("same");

		std::ostringstream oss132;
		oss132 << "#splitline{#sqrt{s} = 13 TeV, 140 fb^{-1} }{m_{bb} #in [100,140]}";	std::string var132 = oss132.str();
		TLatex t132(.2,.8,var132.c_str());    t132.SetTextSize(0.03);
		t132.SetNDC(kTRUE);
		t132.Draw();
		auto legend13 = new TLegend(.6,.75,.9,.9);

		legend13->SetNColumns(2);
		legend13->AddEntry(MasterHistogram[vv][i131],(label[vv]).c_str(),"f");
		legend13->AddEntry(MasterHistogram[hh][i132],(label[hh]).c_str(),"l");
		legend13->AddEntry(MasterHistogram[singleh][i133],(label[singleh]).c_str(),"f");
		legend13->AddEntry(MasterHistogram[ttv][i134],(label[ttv]).c_str(),"f");
		legend13->AddEntry(MasterHistogram[dy][i135],(label[dy]).c_str(),"f");
		legend13->AddEntry(MasterHistogram[wt][i136],(label[wt]).c_str(),"f");
		legend13->AddEntry(MasterHistogram[zjets][i137],(label[zjets]).c_str(),"f");
		legend13->AddEntry(MasterHistogram[tt][i138],(label[tt]).c_str(),"f");
		legend13->Draw("same");


	c1->cd(4);

		gStyle->SetLineWidth(1);
		 THStack *hs14 = new THStack("hs14","");

		for (int iH = 0; iH < 8; iH++){
			if (iH == hh) {
				MasterHistogram[iH][i141]->SetLineColor(color[iH]);
				MasterHistogram[iH][i141]->SetLineStyle(9);
			}
			else {
				MasterHistogram[iH][i141]->SetFillColor(color[iH]);
				MasterHistogram[iH][i141]->SetLineColor(kBlack);
			}
		}

		hs14->Add(MasterHistogram[vv][i141]);
		hs14->Add(MasterHistogram[singleh][i141]);
		hs14->Add(MasterHistogram[ttv][i141]);
		hs14->Add(MasterHistogram[dy][i141]);
		hs14->Add(MasterHistogram[wt][i141]);
		hs14->Add(MasterHistogram[zjets][i141]);
		hs14->Add(MasterHistogram[tt][i141]);

		hs14->SetMinimum(1e-2);

		hs14->SetMaximum(2e8);

		hs14->Draw("HIST");
		hs14->GetXaxis()->SetTitle(MasterHistogram[0][i141]->GetTitle());
		//hs14->GetXaxis()->SetNdivisions(9);

		hs14->GetYaxis()->SetNdivisions(6);

		MasterHistogram[hh][i141]->Draw("same");

		gPad->Modified();
		gPad->SetLogy();

		TLatex t141(0,0.95,"Events #upoint #frac{140 fb^{-1}}{Total events/#sigma} ");   t141.SetNDC(kTRUE);   t141.SetTextSize(0.030); t141.Draw("same");

		std::ostringstream oss142;
		oss142 << "#splitline{#sqrt{s} = 13 TeV, 140 fb^{-1} }{m_{bb} #in [100,140]}";	std::string var142 = oss142.str();
		TLatex t142(.2,.8,var142.c_str());    t142.SetTextSize(0.03);
		t142.SetNDC(kTRUE);
		t142.Draw();
		auto legend14 = new TLegend(.6,.75,.9,.9);

		legend14->SetNColumns(2);
		legend14->AddEntry(MasterHistogram[vv][i141],(label[vv]).c_str(),"f");
		legend14->AddEntry(MasterHistogram[hh][i142],(label[hh]).c_str(),"l");
		legend14->AddEntry(MasterHistogram[singleh][i143],(label[singleh]).c_str(),"f");
		legend14->AddEntry(MasterHistogram[ttv][i144],(label[ttv]).c_str(),"f");
		legend14->AddEntry(MasterHistogram[dy][i145],(label[dy]).c_str(),"f");
		legend14->AddEntry(MasterHistogram[wt][i146],(label[wt]).c_str(),"f");
		legend14->AddEntry(MasterHistogram[zjets][i147],(label[zjets]).c_str(),"f");
		legend14->AddEntry(MasterHistogram[tt][i148],(label[tt]).c_str(),"f");
		legend14->Draw("same");


    TCanvas *c2 = new TCanvas("c2","Canvas",900,900);
	c2->SetFillStyle(4000); //will be transparent
	c2->Divide(2,2);

	c2->cd(1);

		gStyle->SetLineWidth(1);
		 THStack *hs21 = new THStack("hs21","");

		for (int iH = 0; iH < 8; iH++){
			if (iH == hh) {
				MasterHistogram[iH][i211]->SetLineColor(color[iH]);
				MasterHistogram[iH][i211]->SetLineStyle(9);
			}
			else {
				MasterHistogram[iH][i211]->SetFillColor(color[iH]);
				MasterHistogram[iH][i211]->SetLineColor(kBlack);
			}
		}

		hs21->Add(MasterHistogram[vv][i211]);
		hs21->Add(MasterHistogram[singleh][i211]);
		hs21->Add(MasterHistogram[ttv][i211]);
		hs21->Add(MasterHistogram[dy][i211]);
		hs21->Add(MasterHistogram[wt][i211]);
		hs21->Add(MasterHistogram[zjets][i211]);
		hs21->Add(MasterHistogram[tt][i211]);

		hs21->SetMinimum(1e-2);

		hs21->SetMaximum(2e8);

		hs21->Draw("HIST");
		hs21->GetXaxis()->SetTitle(MasterHistogram[0][i211]->GetTitle());
		//hs21->GetXaxis()->SetNdivisions(9);

		hs21->GetYaxis()->SetNdivisions(6);

		MasterHistogram[hh][i211]->Draw("same");

		gPad->Modified();
		gPad->SetLogy();

		TLatex t211(0,0.95,"Events #upoint #frac{140 fb^{-1}}{Total events/#sigma} ");   t211.SetNDC(kTRUE);   t211.SetTextSize(0.030); t211.Draw("same");

		std::ostringstream oss212;
		oss212 << "#splitline{#sqrt{s} = 13 TeV, 140 fb^{-1} }{m_{bb} #in [100,140]}";	std::string var212 = oss212.str();
		TLatex t212(.2,.8,var212.c_str());    t212.SetTextSize(0.03);
		t212.SetNDC(kTRUE);
		t212.Draw();
		auto legend21 = new TLegend(.6,.75,.9,.9);

		legend21->SetNColumns(2);
		legend21->AddEntry(MasterHistogram[vv][i211],(label[vv]).c_str(),"f");
		legend21->AddEntry(MasterHistogram[hh][i212],(label[hh]).c_str(),"l");
		legend21->AddEntry(MasterHistogram[singleh][i213],(label[singleh]).c_str(),"f");
		legend21->AddEntry(MasterHistogram[ttv][i214],(label[ttv]).c_str(),"f");
		legend21->AddEntry(MasterHistogram[dy][i215],(label[dy]).c_str(),"f");
		legend21->AddEntry(MasterHistogram[wt][i216],(label[wt]).c_str(),"f");
		legend21->AddEntry(MasterHistogram[zjets][i217],(label[zjets]).c_str(),"f");
		legend21->AddEntry(MasterHistogram[tt][i218],(label[tt]).c_str(),"f");
		legend21->Draw("same");




	c2->cd(2);

		gStyle->SetLineWidth(1);
		 THStack *hs22 = new THStack("hs22","");

		for (int iH = 0; iH < 8; iH++){
			if (iH == hh) {
				MasterHistogram[iH][i221]->SetLineColor(color[iH]);
				MasterHistogram[iH][i221]->SetLineStyle(9);
			}
			else {
				MasterHistogram[iH][i221]->SetFillColor(color[iH]);
				MasterHistogram[iH][i221]->SetLineColor(kBlack);
			}
		}

		hs22->Add(MasterHistogram[vv][i221]);
		hs22->Add(MasterHistogram[singleh][i221]);
		hs22->Add(MasterHistogram[ttv][i221]);
		hs22->Add(MasterHistogram[dy][i221]);
		hs22->Add(MasterHistogram[wt][i221]);
		hs22->Add(MasterHistogram[zjets][i221]);
		hs22->Add(MasterHistogram[tt][i221]);

		hs22->SetMinimum(1e-2);

		hs22->SetMaximum(2e8);

		hs22->Draw("HIST");
		hs22->GetXaxis()->SetTitle(MasterHistogram[0][i221]->GetTitle());
		//hs22->GetXaxis()->SetNdivisions(9);

		hs22->GetYaxis()->SetNdivisions(6);

		MasterHistogram[hh][i221]->Draw("same");

		gPad->Modified();
		gPad->SetLogy();

		TLatex t221(0,0.95,"Events #upoint #frac{140 fb^{-1}}{Total events/#sigma} ");   t221.SetNDC(kTRUE);   t221.SetTextSize(0.030); t221.Draw("same");

		std::ostringstream oss222;
		oss222 << "#splitline{#sqrt{s} = 13 TeV, 140 fb^{-1} }{m_{bb} #in [100,140]}";	std::string var222 = oss222.str();
		TLatex t222(.2,.8,var222.c_str());    t222.SetTextSize(0.03);
		t222.SetNDC(kTRUE);
		t222.Draw();
		auto legend22 = new TLegend(.6,.75,.9,.9);

		legend22->SetNColumns(2);
		legend22->AddEntry(MasterHistogram[vv][i221],(label[vv]).c_str(),"f");
		legend22->AddEntry(MasterHistogram[hh][i222],(label[hh]).c_str(),"l");
		legend22->AddEntry(MasterHistogram[singleh][i223],(label[singleh]).c_str(),"f");
		legend22->AddEntry(MasterHistogram[ttv][i224],(label[ttv]).c_str(),"f");
		legend22->AddEntry(MasterHistogram[dy][i225],(label[dy]).c_str(),"f");
		legend22->AddEntry(MasterHistogram[wt][i226],(label[wt]).c_str(),"f");
		legend22->AddEntry(MasterHistogram[zjets][i227],(label[zjets]).c_str(),"f");
		legend22->AddEntry(MasterHistogram[tt][i228],(label[tt]).c_str(),"f");
		legend22->Draw("same");

	c2->cd(3);

		gStyle->SetLineWidth(1);
		 THStack *hs23 = new THStack("hs23","");

		for (int iH = 0; iH < 8; iH++){
			if (iH == hh) {
				MasterHistogram[iH][i231]->SetLineColor(color[iH]);
				MasterHistogram[iH][i231]->SetLineStyle(9);
			}
			else {
				MasterHistogram[iH][i231]->SetFillColor(color[iH]);
				MasterHistogram[iH][i231]->SetLineColor(kBlack);
			}
		}

		hs23->Add(MasterHistogram[vv][i231]);
		hs23->Add(MasterHistogram[singleh][i231]);
		hs23->Add(MasterHistogram[ttv][i231]);
		hs23->Add(MasterHistogram[dy][i231]);
		hs23->Add(MasterHistogram[wt][i231]);
		hs23->Add(MasterHistogram[zjets][i231]);
		hs23->Add(MasterHistogram[tt][i231]);

		hs23->SetMinimum(1e-2);

		hs23->SetMaximum(2e8);

		hs23->Draw("HIST");
		hs23->GetXaxis()->SetTitle(MasterHistogram[0][i231]->GetTitle());
		//hs23->GetXaxis()->SetNdivisions(9);

		hs23->GetYaxis()->SetNdivisions(6);

		MasterHistogram[hh][i231]->Draw("same");

		gPad->Modified();
		gPad->SetLogy();

		TLatex t231(0,0.95,"Events #upoint #frac{140 fb^{-1}}{Total events/#sigma} ");   t231.SetNDC(kTRUE);   t231.SetTextSize(0.030); t231.Draw("same");

		std::ostringstream oss232;
		oss232 << "#splitline{#sqrt{s} = 13 TeV, 140 fb^{-1} }{m_{bb} #in [100,140]}";	std::string var232 = oss232.str();
		TLatex t232(.2,.8,var232.c_str());    t232.SetTextSize(0.03);
		t232.SetNDC(kTRUE);
		t232.Draw();
		auto legend23 = new TLegend(.6,.75,.9,.9);

		legend23->SetNColumns(2);
		legend23->AddEntry(MasterHistogram[vv][i231],(label[vv]).c_str(),"f");
		legend23->AddEntry(MasterHistogram[hh][i232],(label[hh]).c_str(),"l");
		legend23->AddEntry(MasterHistogram[singleh][i233],(label[singleh]).c_str(),"f");
		legend23->AddEntry(MasterHistogram[ttv][i234],(label[ttv]).c_str(),"f");
		legend23->AddEntry(MasterHistogram[dy][i235],(label[dy]).c_str(),"f");
		legend23->AddEntry(MasterHistogram[wt][i236],(label[wt]).c_str(),"f");
		legend23->AddEntry(MasterHistogram[zjets][i237],(label[zjets]).c_str(),"f");
		legend23->AddEntry(MasterHistogram[tt][i238],(label[tt]).c_str(),"f");
		legend23->Draw("same");




	c2->cd(4);

		gStyle->SetLineWidth(1);
		 THStack *hs24 = new THStack("hs24","");

		for (int iH = 0; iH < 8; iH++){
			if (iH == hh) {
				MasterHistogram[iH][i241]->SetLineColor(color[iH]);
				MasterHistogram[iH][i241]->SetLineStyle(9);
			}
			else {
				MasterHistogram[iH][i241]->SetFillColor(color[iH]);
				MasterHistogram[iH][i241]->SetLineColor(kBlack);
			}
		}

		hs24->Add(MasterHistogram[vv][i241]);
		hs24->Add(MasterHistogram[singleh][i241]);
		hs24->Add(MasterHistogram[ttv][i241]);
		hs24->Add(MasterHistogram[dy][i241]);
		hs24->Add(MasterHistogram[wt][i241]);
		hs24->Add(MasterHistogram[zjets][i241]);
		hs24->Add(MasterHistogram[tt][i241]);

		hs24->SetMinimum(1e-2);

		hs24->SetMaximum(2e8);

		hs24->Draw("HIST");
		hs24->GetXaxis()->SetTitle(MasterHistogram[0][i241]->GetTitle());
		//hs24->GetXaxis()->SetNdivisions(9);

		hs24->GetYaxis()->SetNdivisions(6);

		MasterHistogram[hh][i241]->Draw("same");

		gPad->Modified();
		gPad->SetLogy();

		TLatex t241(0,0.95,"Events #upoint #frac{140 fb^{-1}}{Total events/#sigma} ");   t241.SetNDC(kTRUE);   t241.SetTextSize(0.030); t241.Draw("same");

		std::ostringstream oss242;
		oss242 << "#splitline{#sqrt{s} = 13 TeV, 140 fb^{-1} }{m_{bb} #in [100,140]}";	std::string var242 = oss242.str();
		TLatex t242(.2,.8,var242.c_str());    t242.SetTextSize(0.03);
		t242.SetNDC(kTRUE);
		t242.Draw();
		auto legend24 = new TLegend(.6,.75,.9,.9);

		legend24->SetNColumns(2);
		legend24->AddEntry(MasterHistogram[vv][i241],(label[vv]).c_str(),"f");
		legend24->AddEntry(MasterHistogram[hh][i242],(label[hh]).c_str(),"l");
		legend24->AddEntry(MasterHistogram[singleh][i243],(label[singleh]).c_str(),"f");
		legend24->AddEntry(MasterHistogram[ttv][i244],(label[ttv]).c_str(),"f");
		legend24->AddEntry(MasterHistogram[dy][i245],(label[dy]).c_str(),"f");
		legend24->AddEntry(MasterHistogram[wt][i246],(label[wt]).c_str(),"f");
		legend24->AddEntry(MasterHistogram[zjets][i247],(label[zjets]).c_str(),"f");
		legend24->AddEntry(MasterHistogram[tt][i248],(label[tt]).c_str(),"f");
		legend24->Draw("same");





















    c1->Update();   
    c2->Update();   

    gPad->WaitPrimitive();
	c1->Print("/eos/user/p/pmeiring/ATLAS_MasterThesis/Plots/Leptons.pdf","PDF");
	c2->Print("/eos/user/p/pmeiring/ATLAS_MasterThesis/Plots/BJets.pdf","PDF");

    //c1->SaveAs("/eos/user/p/pmeiring/ATLAS_MaseterThesis/Plots/plots.jpg");
    c1->Close();
    c2->Close();

	gApplication->Terminate();

}




