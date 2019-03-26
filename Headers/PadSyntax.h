#ifndef _padsyntax_
#define _padsyntax_


#include <iostream>
#include <string>
#include <fstream>
#include "TROOT.h"
#include "TFile.h"
#include "TTree.h"
#include "TH2.h"
#include "TRandom.h"


void CreatePadSyntax (int canvas, int pad, int nhistograms){
	std::string Canvas = to_string(canvas);
	std::string Pad = to_string(pad);
	//std::string Row = to_string(row);
	//std::string Column = to_string(column);
	std::string Nhistograms = to_string(nhistograms);

	std::ofstream syntax ("/afs/cern.ch/work/p/pmeiring/private/ATLAS/My_FlatTuple_Analysis_01/PadSyntax/Pad"+Canvas+Pad+".txt");

	syntax <<"\n\nc"<<Canvas<<"->cd("<<Pad<<");"<<std::endl;

	// First histogram
	syntax <<"\tMasterHistogram[i"<<Canvas<<Pad<<"1]->SetLineColor(color1);"<<std::endl;
	syntax <<"\tMasterHistogram[i"<<Canvas<<Pad<<"1]->Draw();"<<std::endl;

	// X axis
	syntax <<"\tMasterHistogram[i"<<Canvas<<Pad<<"1]->GetXaxis()->SetTitle(\"Inv. Mass [GeV]\");"<<std::endl;
	//syntax <<"\tMasterHistogram[i"<<Canvas<<Pad<<"1]->GetXaxis()->SetRangeUser(0,500);"<<std::endl;

	// Y axis
	syntax <<"\tMasterHistogram[i"<<Canvas<<Pad<<"1]->GetYaxis()->SetTitle(\"\");"<<std::endl;
	syntax <<"\tgPad-> SetLogy();"<<std::endl;
	syntax <<"\tTLatex t"<<Canvas<<Pad<<"(0,0.95,\"Events\");   t"<<Canvas<<Pad<<".SetNDC(kTRUE);   t"<<Canvas<<Pad<<".SetTextSize(0.030); t"<<Canvas<<Pad<<".Draw(\"same\");\n"<<std::endl;


	// Draw other histograms
	for (int h=2; h<nhistograms+1; h++){
		std::string H = to_string(h);
		syntax <<"\tMasterHistogram[i"<<Canvas<<Pad<<H<<"]->SetLineColor(color"<<H<<");"<<std::endl;
		syntax <<"\tMasterHistogram[i"<<Canvas<<Pad<<H<<"]->Draw(\"same\");"<<std::endl;
	}

	// Legend
	syntax <<"\n\tauto legend"<<Canvas<<Pad<<" = new TLegend(.6,.75,.9,.9);"<<std::endl;
	for (int h=1; h<nhistograms+1; h++){
		std::string H = to_string(h);
		syntax <<"\tlegend"<<Canvas<<Pad<<"->AddEntry(MasterHistogram[i"<<Canvas<<Pad<<H<<"],\"\");"<<std::endl;
	}
	syntax <<"\tlegend"<<Canvas<<Pad<<"->Draw(\"same\");\n"<<std::endl;

	// Statistics
	for (int h=1; h<nhistograms+1; h++){
		std::string H = to_string(h);
		syntax <<"\tstd::ostringstream oss"<<Canvas<<Pad<<H<<";"<<std::endl;
		// syntax <<"\toss"<<Canvas<<Pad<<H<<" << \"#color["<<H<<"]{#splitline{Nr. Events = \"<<MasterHistogram[i"<<Canvas<<Pad<<H<<"]->GetEntries()"<<std::endl;
		// syntax << "\t\t<<\"}{#splitline{Mean = \"<<				MasterHistogram[i"<<Canvas<<Pad<<H<<"]->GetMean()"<<std::endl;
		// syntax << "\t\t<<\"}{Std Dev = \"<<						MasterHistogram[i"<<Canvas<<Pad<<H<<"]->GetStdDev()<<\"}}}"<<std::endl;;
		syntax <<"\toss"<<Canvas<<Pad<<H<<" << \"#color["<<H<<"]{#splitline{Nr. Events = \"<<MasterHistogram[i"<<Canvas<<Pad<<H<<"]->GetEntries()<<\"}{#splitline{Mean = \"<<	MasterHistogram[i"<<Canvas<<Pad<<H<<"]->GetMean()<<\"}{Std Dev = \"<<		MasterHistogram[i"<<Canvas<<Pad<<H<<"]->GetStdDev()<<\"}}}\";"<<std::endl;

		syntax <<"\tstd::string var"<<Canvas<<Pad<<H<<" = oss"<<Canvas<<Pad<<H<<".str();"<<std::endl;
		syntax <<"\tTLatex t"<<Canvas<<Pad<<H<<"(.65,.6,var"<<Canvas<<Pad<<H<<".c_str());    t"<<Canvas<<Pad<<H<<".SetTextSize(0.025);"<<std::endl;
		syntax <<"\tt"<<Canvas<<Pad<<H<<".SetNDC(kTRUE);"<<std::endl;
	    if (h==1){
	    	syntax << "\tt"<<Canvas<<Pad<<H<<".Draw();"<<std::endl;
	    }
	    else{
	    	syntax << "\tt"<<Canvas<<Pad<<H<<".Draw(\"same\");"<<std::endl;
	    }
	}

	//syntax<<"gApplication->Terminate();"<<std::endl;
	//syntax <<"}"<<std::endl;
}


void CreatePadSyntaxStack (int canvas, int pad, int nhistograms){
	std::string Canvas = to_string(canvas);
	std::string Pad = to_string(pad);
	//std::string Row = to_string(row);
	//std::string Column = to_string(column);
	std::string Nhistograms = to_string(nhistograms);

	std::ofstream syntax ("/afs/cern.ch/work/p/pmeiring/private/ATLAS/My_FlatTuple_Analysis_01/PadSyntax/Pad"+Canvas+Pad+"_stack.txt");

	syntax <<"\n\nc"<<Canvas<<"->cd("<<Pad<<");\n"<<std::endl;
	syntax <<"gStyle->SetLineWidth(1);"<<std::endl;

	syntax <<"\t THStack *hs"<<Canvas<<Pad<<" = new THStack(\"hs"<<Canvas<<Pad<<"\",\"\");"<<std::endl;
	syntax <<"\tauto legend"<<Canvas<<Pad<<" = new TLegend(.6,.75,.9,.9);\n"<<std::endl;
	syntax <<"\tlegend"<<Canvas<<Pad<<"->SetNColumns(2);"<<std::endl;

	syntax <<"\tfor (int iH = 0; iH < "<<Nhistograms<<"; iH++){"<<std::endl;
	syntax <<"\t\tMasterHistogram[iH][i"<<Canvas<<Pad<<"1]->SetFillColor(color[iH]);"<<std::endl;
	syntax <<"\t\tMasterHistogram[iH][i"<<Canvas<<Pad<<"1]->SetLineColor(kBlack);"<<std::endl;	
	//syntax <<"\t\tMasterHistogram[iH][i"<<Canvas<<Pad<<"1]->Scale(Scale[iH]);"<<std::endl;	
	syntax <<"\t\ths"<<Canvas<<Pad<<"->Add(MasterHistogram[iH][i"<<Canvas<<Pad<<"1]);"<<std::endl;
	syntax <<"\t\tif (iH==0){"<<std::endl;
	syntax <<"\t\t\tMasterHistogram[iH][i"<<Canvas<<Pad<<"1]->GetXaxis()->SetTitle(\"Inv. Mass [GeV]\");"<<std::endl;
	syntax <<"\t\t\tMasterHistogram[iH][i"<<Canvas<<Pad<<"1]->GetYaxis()->SetTitle(\"\");"<<std::endl;
	syntax <<"\t\t}"<<std::endl;	
	syntax <<"\t}\n"<<std::endl;
	
	syntax <<"\ths"<<Canvas<<Pad<<"->Draw(\"HIST\");"<<std::endl;
	syntax <<"\ths"<<Canvas<<Pad<<"->GetXaxis()->SetTitle(MasterHistogram[0][i"<<Canvas<<Pad<<"1]->GetTitle());"<<std::endl;

	syntax <<"\tgPad->Modified();"<<std::endl;
	syntax <<"\tgPad->SetLogy();"<<std::endl;
	syntax <<"\tTLatex t"<<Canvas<<Pad<<"(0,0.95,\"Events\");   t"<<Canvas<<Pad<<".SetNDC(kTRUE);   t"<<Canvas<<Pad<<".SetTextSize(0.030); t"<<Canvas<<Pad<<".Draw(\"same\");\n"<<std::endl;

	// Legend
	for (int h=1; h<nhistograms+1; h++){
		std::string H = to_string(h);
		syntax <<"\tlegend"<<Canvas<<Pad<<"->AddEntry(MasterHistogram["<<h-1<<"][i"<<Canvas<<Pad<<H<<"],(label["<<h-1<<"]).c_str(),\"f\");"<<std::endl;
	}
	syntax <<"\tlegend"<<Canvas<<Pad<<"->Draw(\"same\");\n"<<std::endl;


/*

	// Statistics
	for (int h=1; h<nhistograms+1; h++){
		std::string H = to_string(h);
		syntax <<"\tstd::ostringstream oss"<<Canvas<<Pad<<H<<";"<<std::endl;
		// syntax <<"\toss"<<Canvas<<Pad<<H<<" << \"#color["<<H<<"]{#splitline{Nr. Events = \"<<MasterHistogram[i"<<Canvas<<Pad<<H<<"]->GetEntries()"<<std::endl;
		// syntax << "\t\t<<\"}{#splitline{Mean = \"<<				MasterHistogram[i"<<Canvas<<Pad<<H<<"]->GetMean()"<<std::endl;
		// syntax << "\t\t<<\"}{Std Dev = \"<<						MasterHistogram[i"<<Canvas<<Pad<<H<<"]->GetStdDev()<<\"}}}"<<std::endl;;
		syntax <<"\toss"<<Canvas<<Pad<<H<<" << \"#color["<<H<<"]{#splitline{Nr. Events = \"<<MasterHistogram[i"<<Canvas<<Pad<<H<<"]->GetEntries()<<\"}{#splitline{Mean = \"<<	MasterHistogram[i"<<Canvas<<Pad<<H<<"]->GetMean()<<\"}{Std Dev = \"<<		MasterHistogram[i"<<Canvas<<Pad<<H<<"]->GetStdDev()<<\"}}}\";"<<std::endl;

		syntax <<"\tstd::string var"<<Canvas<<Pad<<H<<" = oss"<<Canvas<<Pad<<H<<".str();"<<std::endl;
		syntax <<"\tTLatex t"<<Canvas<<Pad<<H<<"(.65,.6,var"<<Canvas<<Pad<<H<<".c_str());    t"<<Canvas<<Pad<<H<<".SetTextSize(0.025);"<<std::endl;
		syntax <<"\tt"<<Canvas<<Pad<<H<<".SetNDC(kTRUE);"<<std::endl;
	    if (h==1){
	    	syntax << "\tt"<<Canvas<<Pad<<H<<".Draw();"<<std::endl;
	    }
	    else{
	    	syntax << "\tt"<<Canvas<<Pad<<H<<".Draw(\"same\");"<<std::endl;
	    }
	}
*/
	//syntax<<"gApplication->Terminate();"<<std::endl;
	//syntax <<"}"<<std::endl;

}



void CreatePadSyntaxStack_hh (int canvas, int pad, int nhistograms){
	std::string Canvas = to_string(canvas);
	std::string Pad = to_string(pad);
	//std::string Row = to_string(row);
	//std::string Column = to_string(column);
	std::string Nhistograms = to_string(nhistograms);

	std::ofstream syntax ("/afs/cern.ch/work/p/pmeiring/private/ATLAS/My_FlatTuple_Analysis_01/PadSyntax/Pad"+Canvas+Pad+"_stack.txt");

	syntax <<"\n\nc"<<Canvas<<"->cd("<<Pad<<");\n"<<std::endl;
	syntax <<"\tgStyle->SetLineWidth(1);"<<std::endl;

	syntax <<"\t THStack *hs"<<Canvas<<Pad<<" = new THStack(\"hs"<<Canvas<<Pad<<"\",\"\");\n"<<std::endl;

	syntax <<"\tfor (int iH = 0; iH < "<<Nhistograms<<"; iH++){"<<std::endl;
	syntax <<"\t\tif (iH == hh) {"<<std::endl;
	syntax <<"\t\t\tMasterHistogram[iH][i"<<Canvas<<Pad<<"1]->SetLineColor(color[iH]);"<<std::endl;
	syntax <<"\t\t\tMasterHistogram[iH][i"<<Canvas<<Pad<<"1]->SetLineStyle(9);"<<std::endl;
	syntax <<"\t\t}"<<std::endl;
	syntax <<"\t\telse {"<<std::endl;
	syntax <<"\t\t\tMasterHistogram[iH][i"<<Canvas<<Pad<<"1]->SetFillColor(color[iH]);"<<std::endl;
	syntax <<"\t\t\tMasterHistogram[iH][i"<<Canvas<<Pad<<"1]->SetLineColor(kBlack);"<<std::endl;	
	syntax <<"\t\t}"<<std::endl;
	syntax <<"\t}\n"<<std::endl;

	//syntax <<"\t\tMasterHistogram[iH][i"<<Canvas<<Pad<<"1]->Scale(Scale[iH]);"<<std::endl;	
	syntax <<"\ths"<<Canvas<<Pad<<"->Add(MasterHistogram[vv][i"<<Canvas<<Pad<<"1]);"<<std::endl;
	syntax <<"\ths"<<Canvas<<Pad<<"->Add(MasterHistogram[singleh][i"<<Canvas<<Pad<<"1]);"<<std::endl;
	syntax <<"\ths"<<Canvas<<Pad<<"->Add(MasterHistogram[ttw][i"<<Canvas<<Pad<<"1]);"<<std::endl;
	syntax <<"\ths"<<Canvas<<Pad<<"->Add(MasterHistogram[dy][i"<<Canvas<<Pad<<"1]);"<<std::endl;
	syntax <<"\ths"<<Canvas<<Pad<<"->Add(MasterHistogram[wt][i"<<Canvas<<Pad<<"1]);"<<std::endl;
	syntax <<"\ths"<<Canvas<<Pad<<"->Add(MasterHistogram[zjets][i"<<Canvas<<Pad<<"1]);"<<std::endl;
	syntax <<"\ths"<<Canvas<<Pad<<"->Add(MasterHistogram[tt][i"<<Canvas<<Pad<<"1]);\n"<<std::endl;

	// Some axis options
	syntax <<"\ths"<<Canvas<<Pad<<"->SetMinimum(1e-2);\n"<<std::endl;
	syntax <<"\ths"<<Canvas<<Pad<<"->SetMaximum(2e8);\n"<<std::endl;

	syntax <<"\ths"<<Canvas<<Pad<<"->Draw(\"HIST\");"<<std::endl;
	syntax <<"\ths"<<Canvas<<Pad<<"->GetXaxis()->SetTitle(MasterHistogram[0][i"<<Canvas<<Pad<<"1]->GetTitle());"<<std::endl;
	syntax <<"\t//hs"<<Canvas<<Pad<<"->GetXaxis()->SetNdivisions(9);\n"<<std::endl;
	syntax <<"\ths"<<Canvas<<Pad<<"->GetYaxis()->SetNdivisions(6);\n"<<std::endl;

	syntax <<"\tMasterHistogram[hh][i"<<Canvas<<Pad<<"1]->Draw(\"same\");\n"<<std::endl;

	// Label for y axis
	syntax <<"\tgPad->Modified();"<<std::endl;
	syntax <<"\tgPad->SetLogy();\n"<<std::endl;
	syntax <<"\tTLatex t"<<Canvas<<Pad<<"1(0,0.95,\"Events\");   t"<<Canvas<<Pad<<"1.SetNDC(kTRUE);   t"<<Canvas<<Pad<<"1.SetTextSize(0.030); t"<<Canvas<<Pad<<"1.Draw(\"same\");\n"<<std::endl;

	// General information in pad
	syntax <<"\tstd::ostringstream oss"<<Canvas<<Pad<<"2;"<<std::endl;
	syntax <<"\toss"<<Canvas<<Pad<<"2 << \"#splitline{#sqrt{s} = 13 TeV, 140 fb^{-1} }{m_{bb} #in [100,140]}\";";
	syntax <<"\tstd::string var"<<Canvas<<Pad<<"2 = oss"<<Canvas<<Pad<<"2.str();"<<std::endl;
	syntax <<"\tTLatex t"<<Canvas<<Pad<<"2(.2,.8,var"<<Canvas<<Pad<<"2.c_str());    t"<<Canvas<<Pad<<"2.SetTextSize(0.03);"<<std::endl;
	syntax <<"\tt"<<Canvas<<Pad<<"2.SetNDC(kTRUE);"<<std::endl;
	syntax <<"\tt"<<Canvas<<Pad<<"2.Draw();"<<std::endl;


	// Legend
	syntax <<"\tauto legend"<<Canvas<<Pad<<" = new TLegend(.6,.75,.9,.9);\n"<<std::endl;
	syntax <<"\tlegend"<<Canvas<<Pad<<"->SetNColumns(2);"<<std::endl;
	syntax <<"\tlegend"<<Canvas<<Pad<<"->AddEntry(MasterHistogram[vv][i"<<Canvas<<Pad<<"1],(label[vv]).c_str(),\"f\");"<<std::endl;
	syntax <<"\tlegend"<<Canvas<<Pad<<"->AddEntry(MasterHistogram[hh][i"<<Canvas<<Pad<<"2],(label[hh]).c_str(),\"l\");"<<std::endl;
	syntax <<"\tlegend"<<Canvas<<Pad<<"->AddEntry(MasterHistogram[singleh][i"<<Canvas<<Pad<<"3],(label[singleh]).c_str(),\"f\");"<<std::endl;
	syntax <<"\tlegend"<<Canvas<<Pad<<"->AddEntry(MasterHistogram[ttw][i"<<Canvas<<Pad<<"4],(label[ttw]).c_str(),\"f\");"<<std::endl;
	syntax <<"\tlegend"<<Canvas<<Pad<<"->AddEntry(MasterHistogram[dy][i"<<Canvas<<Pad<<"5],(label[dy]).c_str(),\"f\");"<<std::endl;
	syntax <<"\tlegend"<<Canvas<<Pad<<"->AddEntry(MasterHistogram[wt][i"<<Canvas<<Pad<<"6],(label[wt]).c_str(),\"f\");"<<std::endl;
	syntax <<"\tlegend"<<Canvas<<Pad<<"->AddEntry(MasterHistogram[zjets][i"<<Canvas<<Pad<<"7],(label[zjets]).c_str(),\"f\");"<<std::endl;
	syntax <<"\tlegend"<<Canvas<<Pad<<"->AddEntry(MasterHistogram[tt][i"<<Canvas<<Pad<<"8],(label[tt]).c_str(),\"f\");"<<std::endl;
	syntax <<"\tlegend"<<Canvas<<Pad<<"->Draw(\"same\");\n"<<std::endl;


/*

	// Statistics
	for (int h=1; h<nhistograms+1; h++){
		std::string H = to_string(h);
		syntax <<"\tstd::ostringstream oss"<<Canvas<<Pad<<H<<";"<<std::endl;
		// syntax <<"\toss"<<Canvas<<Pad<<H<<" << \"#color["<<H<<"]{#splitline{Nr. Events = \"<<MasterHistogram[i"<<Canvas<<Pad<<H<<"]->GetEntries()"<<std::endl;
		// syntax << "\t\t<<\"}{#splitline{Mean = \"<<				MasterHistogram[i"<<Canvas<<Pad<<H<<"]->GetMean()"<<std::endl;
		// syntax << "\t\t<<\"}{Std Dev = \"<<						MasterHistogram[i"<<Canvas<<Pad<<H<<"]->GetStdDev()<<\"}}}"<<std::endl;;
		syntax <<"\toss"<<Canvas<<Pad<<H<<" << \"#color["<<H<<"]{#splitline{Nr. Events = \"<<MasterHistogram[i"<<Canvas<<Pad<<H<<"]->GetEntries()<<\"}{#splitline{Mean = \"<<	MasterHistogram[i"<<Canvas<<Pad<<H<<"]->GetMean()<<\"}{Std Dev = \"<<		MasterHistogram[i"<<Canvas<<Pad<<H<<"]->GetStdDev()<<\"}}}\";"<<std::endl;

		syntax <<"\tstd::string var"<<Canvas<<Pad<<H<<" = oss"<<Canvas<<Pad<<H<<".str();"<<std::endl;
		syntax <<"\tTLatex t"<<Canvas<<Pad<<H<<"(.65,.6,var"<<Canvas<<Pad<<H<<".c_str());    t"<<Canvas<<Pad<<H<<".SetTextSize(0.025);"<<std::endl;
		syntax <<"\tt"<<Canvas<<Pad<<H<<".SetNDC(kTRUE);"<<std::endl;
	    if (h==1){
	    	syntax << "\tt"<<Canvas<<Pad<<H<<".Draw();"<<std::endl;
	    }
	    else{
	    	syntax << "\tt"<<Canvas<<Pad<<H<<".Draw(\"same\");"<<std::endl;
	    }
	}
*/
	//syntax<<"gApplication->Terminate();"<<std::endl;
	//syntax <<"}"<<std::endl;

}


#endif
