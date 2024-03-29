
class chisquare 
{

public:
  chisquare(TH1F* data1, TH1F* constMC1, TH1F* diphotonMC1, TH1F* datadrivenQCD1,
	    TH1F* data2, TH1F* constMC2, TH1F* diphotonMC2, TH1F* datadrivenQCD2)
  {
    data1_ = data1; 
    constMC1_ = constMC1; 
    diphotonMC1_ = diphotonMC1; 
    datadrivenQCD1_ = datadrivenQCD1;
    data2_ = data2; 
    constMC2_ = constMC2; 
    diphotonMC2_ = diphotonMC2; 
    datadrivenQCD2_ = datadrivenQCD2;
    SFdiphoton_ = 1.;
    SFdatadrivenQCD_ = 1.;
  }
  double operator()( double* SFs, double *p)
  {
    SFdiphoton_ = SFs[0];
    SFdatadrivenQCD_ = SFs[1];
    double chisquarevalue = 0.;
    for(int ibin=1; ibin<=data1_->GetXaxis()->GetNbins(); ++ibin) {
      double Nev_data1 = data1_->GetBinContent(ibin);
      double Nev_constMC1 = constMC1_->GetBinContent(ibin);
      double Nev_diphotonMC1 = SFdiphoton_ * diphotonMC1_->GetBinContent(ibin);
      double Nev_datadrivenQCDMC1 = SFdatadrivenQCD_ * datadrivenQCD1_->GetBinContent(ibin);
      double Nev_exp1 = Nev_constMC1+Nev_diphotonMC1+Nev_datadrivenQCDMC1; 
      // cout<<"Nev_data1:"<<Nev_data1<<endl;
      if (Nev_data1 == 0) {
        Nev_data1 = 1e-6; // 或者其他很小的值
      }
      chisquarevalue += (Nev_data1-Nev_exp1)*(Nev_data1-Nev_exp1) / Nev_data1;
    }
    for(int ibin=1; ibin<=data2_->GetXaxis()->GetNbins(); ++ibin) {
      double Nev_data2 = data2_->GetBinContent(ibin);
      double Nev_constMC2 = constMC2_->GetBinContent(ibin);
      double Nev_diphotonMC2 = SFdiphoton_ * diphotonMC2_->GetBinContent(ibin);
      double Nev_datadrivenQCDMC2 = SFdatadrivenQCD_ * datadrivenQCD2_->GetBinContent(ibin);
      double Nev_exp2 = Nev_constMC2+Nev_diphotonMC2+Nev_datadrivenQCDMC2; 
      // cout<<"Nev_data2:"<<Nev_data2<<endl;
      if (Nev_data2 == 0) {
        Nev_data2 = 1e-6; // 或者其他很小的值
      }
      else {  
        chisquarevalue += (Nev_data2-Nev_exp2)*(Nev_data2-Nev_exp2) / Nev_data2;

      }
    }

    return chisquarevalue;
  }
  
private:
  TH1F *data1_, *constMC1_, *diphotonMC1_, *datadrivenQCD1_;
  TH1F *data2_, *constMC2_, *diphotonMC2_, *datadrivenQCD2_;
  double SFdiphoton_, SFdatadrivenQCD_;
};

void deriveSFs()
{

  // Inputs//(LeadPhoton_pt/Diphoton_mass>0.35)*(SubleadPhoton_pt/Diphoton_mass>0.25)*
  // string common_selection = "(Diphoton_mass<115 || Diphoton_mass>135)*(Diphoton_minID>-0.7)*(Diphoton_maxID>-0.7)*weight_central!=-999";
  string common_selection = "(Diphoton_mass<115 || Diphoton_mass>135)*(Diphoton_minID>-0.7)*(Diphoton_maxID>-0.7)";//*weight_central>0";
  
  map<string, vector<string> > filenames_map;
  map<string, vector<string> > treenames_map;
  map<string, vector<float> > lumis_map;

  // filenames_map["diphoton"] = { vector<string>{
  //     "/eos/user/s/shsong/combined_WWgg/parquet/bkg/cat2/rename/Diphoton.root"
  //   }};
  filenames_map["data"] = { vector<string>{
      // "/eos/user/s/shsong/HHWWgg/root/cat2_electron/Data_2017.root"

      // "/eos/user/s/shsong/HHWWgg/root/cat3/Data_2017.root"
      "/eos/user/s/shsong/HHWWgg/root/cat4/Data_2017.root"
      // "/eos/user/s/shsong/HHWWgg/root/cat7/Data_2017.root"
    }};
  filenames_map["qcd"] = { vector<string>{
      // "/eos/user/s/shsong/HHWWgg/root/cat2_electron/DatadrivenQCD.root"

      // "/eos/user/s/shsong/HHWWgg/root/cat3/DatadrivenQCD.root"
      "/eos/user/s/shsong/HHWWgg/root/cat4/DatadrivenQCD.root"
      // "/eos/user/s/shsong/HHWWgg/root/cat7/DatadrivenQCD.root"
      // "/eos/user/s/shsong/HHWWgg/root/cat2_electron/DatadrivenQCD_usingcat7Gjet.root"
    }};
  filenames_map["diphoton"] = { vector<string>{
      // "/eos/user/s/shsong/HHWWgg/root/cat2_electron/DiPhotonJetsBox.root"
      // "/eos/user/s/shsong/HHWWgg/root/cat7/DiPhotonJetsBox.root"
      // "/eos/user/s/shsong/HHWWgg/root/cat3/DiPhotonJetsBox.root"
      "/eos/user/s/shsong/HHWWgg/root/cat4/DiPhotonJetsBox.root"
    }};

  // treenames_map["diphoton"] = { vector<string>{
  //     "DiphotonJetsBox"
  //   }};
  treenames_map["data"] = { vector<string>{
      // "cat7"
      // "cat2"
      "cat4"
      // "cat3"
    }};
  treenames_map["qcd"] = { vector<string>{
      // "cat7"
      // "cat2"
      "cat4"
      // "cat3"
    }};
  treenames_map["diphoton"] = { vector<string>{
      // "cat7"
      // "cat2"
      "cat4"
      // "cat3"
    }};
  // lumis_map["diphoton"] = {vector<float>{
  //   1
  // }};
  lumis_map["data"] = {vector<float>{
    1
  }};
  lumis_map["qcd"] = {vector<float>{
    1
  }};
  lumis_map["diphoton"] = {vector<float>{
    1}};
  cout<<"reading all root files"<<endl;

  //Get min and max photon ID distribution
  map<string,TH1F*> h_minphotonID;
  map<string,TH1F*> h_maxphotonID;
  for( auto filenameitr : filenames_map) {
    auto samplename = filenameitr.first;
    // cout << samplename << endl;
    auto filenames = filenameitr.second;
    // cout << filenames << endl;
    auto treenames = treenames_map[samplename];
    // cout << treenames << endl;    
    auto lumis = lumis_map[samplename];
    // cout << lumis << endl;    

    h_minphotonID[samplename] = new TH1F(Form("h_minphotonID_%s",samplename.c_str()),
					 Form("h_minphotonID_%s",samplename.c_str()),
					 17,-0.7,1);
    h_maxphotonID[samplename] = new TH1F(Form("h_maxphotonID_%s",samplename.c_str()),
					 Form("h_maxphotonID_%s",samplename.c_str()),
					 17,-0.7,1);

    for( unsigned ifile=0; ifile<filenames.size(); ++ifile) {
      TChain* ch = new TChain();
      ch->Add( Form("%s/%s",filenames[ifile].c_str(),treenames[ifile].c_str()) );
      ch->Draw( Form("Diphoton_minID >>+ h_minphotonID_%s",samplename.c_str()),
		Form("(weight_central)*(%f)*(%s)",lumis[ifile],common_selection.c_str()),
		"goff");
      ch->Draw( Form("Diphoton_maxID >>+ h_maxphotonID_%s",samplename.c_str()),
		Form("(weight_central)*(%f)*(%s)",lumis[ifile],common_selection.c_str()),
		"goff");
    }
  }

// set other mc as TTJets
  // h_minphotonID["otherMC"] = new TH1F(Form("h_minphotonID_TT"),
	// 				 Form("h_minphotonID_TT"),
	// 				 34,-0.7,1);
  // h_maxphotonID["otherMC"] = new TH1F(Form("h_maxphotonID_TT"),
	// 				 Form("h_maxphotonID_TT"),
	// 				 34,-0.7,1);
  // const TString TTFile = "/eos/user/s/shsong/combined_WWgg/parquet/bkg/cat7/rename/TTJets_2017.root";
  // const TString TreeNameTTJets = "TTG";
  // TChain *MCTTJets_Tree=new TChain(TreeNameTTJets);
  // MCTTJets_Tree->Add(TTFile);
  // MCTTJets_Tree->Draw( Form("minID >>+ h_minphotonID_TT"),
	// 	Form("(weight_central)*(%s)",common_selection.c_str()),
	// 	"goff");
  // MCTTJets_Tree->Draw( Form("Diphoton_maxID >>+ h_maxphotonID_TT"),
	// 	Form("(weight_central)*(%s)",common_selection.c_str()),
	// 	"goff");

  // For now assume no other MC --> h_minphotonID["otherMC"] and h_maxphotonID["otherMC"] are left empty
  // this can be updated to further improve the data/MC agreement of few percent
  h_minphotonID["otherMC"] = new TH1F("constMC1","constMC1",17,-0.7,1);  
  h_minphotonID["MCtot"] = new TH1F("MCtot1","MCtot1",17,-0.7,1);
  h_minphotonID["scaledMCtot"] = new TH1F("MCtot1_scaled","MCtot1_scaled",17,-0.7,1);
  h_maxphotonID["otherMC"] = new TH1F("constMC2","constMC2",17,-0.7,1); 
  h_maxphotonID["MCtot"] = new TH1F("MCtot2","MCtot2",17,-0.7,1);
  h_maxphotonID["scaledMCtot"] = new TH1F("MCtot2_scaled","MCtot2_scaled",17,-0.7,1);

  TCanvas* c1 = new TCanvas();
  h_minphotonID["MCtot"]->Add(h_minphotonID["otherMC"]);
  h_minphotonID["MCtot"]->Add(h_minphotonID["diphoton"]);
  h_minphotonID["MCtot"]->Add(h_minphotonID["qcd"]);
  h_minphotonID["MCtot"]->Draw("hist");
  h_minphotonID["data"]->SetMarkerStyle(20);
  h_minphotonID["data"]->Draw("E1 same");
  h_minphotonID["MCtot"]->GetYaxis()->SetRangeUser(0., 1.3*TMath::Max(h_minphotonID["MCtot"]->GetMaximum(),h_minphotonID["data"]->GetMaximum()) );

  // c1->SaveAs("Diphoton_minID_cat7.png");
  // c1->SaveAs("Diphoton_minID_cat3.png");
  c1->SaveAs("Diphoton_minID_cat4.png");
  // c1->SaveAs("Diphoton_minID_cat2.png");

  TCanvas* c12 = new TCanvas();
  h_maxphotonID["MCtot"]->Add(h_maxphotonID["otherMC"]);
  h_maxphotonID["MCtot"]->Add(h_maxphotonID["diphoton"]);
  h_maxphotonID["MCtot"]->Add(h_maxphotonID["qcd"]);
  h_maxphotonID["MCtot"]->Draw("hist");
  h_maxphotonID["data"]->SetMarkerStyle(20);
  h_maxphotonID["data"]->Draw("E1 same");
  h_maxphotonID["MCtot"]->GetYaxis()->SetRangeUser(0., 1.3*TMath::Max(h_maxphotonID["MCtot"]->GetMaximum(),h_maxphotonID["data"]->GetMaximum()) );

  chisquare chisquareobj(h_minphotonID["data"], h_minphotonID["otherMC"], h_minphotonID["diphoton"], h_minphotonID["qcd"], 
			 h_maxphotonID["data"], h_maxphotonID["otherMC"], h_maxphotonID["diphoton"], h_maxphotonID["qcd"]);
  TF2 *f = new TF2("chi2",chisquareobj,0.001,10.,0.001,10.,0);
  
  double SFdiphoton,SFdatadrivenQCD;
  double chi2 = f->GetMinimumXY(SFdiphoton,SFdatadrivenQCD);
  cout<<"observed: "<<SFdiphoton<<" "<<SFdatadrivenQCD<<" chi2="<<chi2<<endl;

  // c12->SaveAs("Diphoton_maxID_cat7.png");
  // c12->SaveAs("Diphoton_maxID_cat3.png");
  c12->SaveAs("Diphoton_maxID_cat4.png");
  // c12->SaveAs("Diphoton_maxID_cat2.png");
  TCanvas* c2 = new TCanvas();
  h_minphotonID["diphoton"]->Scale(SFdiphoton);
  h_minphotonID["qcd"]->Scale(SFdatadrivenQCD);
  h_minphotonID["scaledMCtot"]->Add(h_minphotonID["otherMC"]);
  h_minphotonID["scaledMCtot"]->Add(h_minphotonID["diphoton"]);
  h_minphotonID["scaledMCtot"]->Add(h_minphotonID["qcd"]);
  h_minphotonID["scaledMCtot"]->Draw("hist");
  h_minphotonID["data"]->Draw("E1 same");
  h_minphotonID["scaledMCtot"]->GetYaxis()->SetRangeUser(0., 1.3*TMath::Max(h_minphotonID["scaledMCtot"]->GetMaximum(),h_minphotonID["data"]->GetMaximum()) );

  // c2->SaveAs("minID_scale_cat7.png");
  // c2->SaveAs("minID_scale_cat3.png");
  c2->SaveAs("minID_scale_cat4.png");
  // c2->SaveAs("minID_scale_cat2.png");
  TCanvas* c22 = new TCanvas();
  h_maxphotonID["diphoton"]->Scale(SFdiphoton);
  h_maxphotonID["qcd"]->Scale(SFdatadrivenQCD);
  h_maxphotonID["scaledMCtot"]->Add(h_maxphotonID["otherMC"]);
  h_maxphotonID["scaledMCtot"]->Add(h_maxphotonID["diphoton"]);
  h_maxphotonID["scaledMCtot"]->Add(h_maxphotonID["qcd"]);
  h_maxphotonID["scaledMCtot"]->Draw("hist");
  h_maxphotonID["data"]->Draw("E1 same");
  cout<<"QCD:"<<h_maxphotonID["qcd"]->Integral()<<endl;
  cout<<"DiPhoton:"<<h_maxphotonID["diphoton"]->Integral()<<endl;
  h_maxphotonID["scaledMCtot"]->GetYaxis()->SetRangeUser(0., 1.3*TMath::Max(h_maxphotonID["scaledMCtot"]->GetMaximum(),h_maxphotonID["data"]->GetMaximum()) );

  // c22->SaveAs("maxID_scale_cat7.png");
  // c22->SaveAs("maxID_scale_cat3.png");
  c22->SaveAs("maxID_scale_cat4.png");
  // c22->SaveAs("maxID_scale_cat2.png");
}


void deriveSF_toyvalidation()
{
  TH1F* data1 = new TH1F("data1","data1",20,-1,1);
  TH1F* constMC1 = new TH1F("constMC1","constMC1",20,-1,1);
  TH1F* diphotonMC1 = new TH1F("diphotonMC1","diphotonMC1",20,-1,1);
  TH1F* datadrivenQCD1 = new TH1F("datadrivenQCD1","datadrivenQCD1",20,-1,1);
  TH1F* MCtot1 = new TH1F("MCtot1","MCtot1",20,-1,1);
  TH1F* MCtot1_scaled = new TH1F("MCtot1_scaled","MCtot1_scaled",20,-1,1);

  TH1F* data2 = new TH1F("data2","data2",20,-1,1);
  TH1F* constMC2 = new TH1F("constMC2","constMC2",20,-1,1);
  TH1F* diphotonMC2 = new TH1F("diphotonMC2","diphotonMC2",20,-1,1);
  TH1F* datadrivenQCD2 = new TH1F("datadrivenQCD2","datadrivenQCD2",20,-1,1);
  TH1F* MCtot2 = new TH1F("MCtot2","MCtot2",20,-1,1);
  TH1F* MCtot2_scaled = new TH1F("MCtot2_scaled","MCtot2_scaled",20,-1,1);

  TF1 *fexpo = new TF1("fexpo","exp(-x)",-1.,1.); 
  TF1 *fexpoinv = new TF1("fexpoinv","exp(x)",-1.,1.); 
  TF1 *fconst = new TF1("fconst","1.+x-x",-1.,1.); 

  double exp_SFdiphoton = 1.3;
  double exp_SFdatadrivenQCD = 0.9;

  data1->FillRandom("fexpo",10000);
  datadrivenQCD1->FillRandom("fexpo",(int)10000./exp_SFdatadrivenQCD);
  data1->FillRandom("fexpoinv",50000);
  diphotonMC1->FillRandom("fexpoinv",(int)50000./exp_SFdiphoton);
  data1->FillRandom("fconst",5000);
  constMC1->FillRandom("fconst",5000);

  data2->FillRandom("fexpo",50000);
  datadrivenQCD2->FillRandom("fexpo",(int)50000./exp_SFdatadrivenQCD);
  data2->FillRandom("fexpoinv",10000);
  diphotonMC2->FillRandom("fexpoinv",(int)10000./exp_SFdiphoton);
  data2->FillRandom("fconst",5000);
  constMC2->FillRandom("fconst",5000);

  TCanvas* c1 = new TCanvas();
  MCtot1->Add(constMC1);
  MCtot1->Add(diphotonMC1);
  MCtot1->Add(datadrivenQCD1);
  MCtot1->Draw("hist");
  data1->SetMarkerStyle(20);
  data1->Draw("E1 same");
  MCtot1->GetYaxis()->SetRangeUser(0., 1.3*TMath::Max(MCtot1->GetMaximum(),data1->GetMaximum()) );

  TCanvas* c12 = new TCanvas();
  MCtot2->Add(constMC2);
  MCtot2->Add(diphotonMC2);
  MCtot2->Add(datadrivenQCD2);
  MCtot2->Draw("hist");
  data2->SetMarkerStyle(20);
  data2->Draw("E1 same");
  MCtot2->GetYaxis()->SetRangeUser(0., 1.3*TMath::Max(MCtot2->GetMaximum(),data2->GetMaximum()) );

  chisquare chisquareobj(data1, constMC1, diphotonMC1, datadrivenQCD1, data2, constMC2, diphotonMC2, datadrivenQCD2);
  TF2 *f = new TF2("chi2",chisquareobj,0.001,10.,0.001,10.,0);
  
  double SFdiphoton,SFdatadrivenQCD;
  double chi2 = f->GetMinimumXY(SFdiphoton,SFdatadrivenQCD);
  cout<<"observed: "<<SFdiphoton<<" "<<SFdatadrivenQCD<<" chi2="<<chi2<<endl;
  cout<<"expected: "<<exp_SFdiphoton<<" "<<exp_SFdatadrivenQCD<<endl;
  
  TCanvas* c2 = new TCanvas();
  diphotonMC1->Scale(SFdiphoton);
  datadrivenQCD1->Scale(SFdatadrivenQCD);
  MCtot1_scaled->Add(constMC1);
  MCtot1_scaled->Add(diphotonMC1);
  MCtot1_scaled->Add(datadrivenQCD1);
  MCtot1_scaled->Draw("hist");
  data1->Draw("E1 same");
  MCtot1_scaled->GetYaxis()->SetRangeUser(0., 1.3*TMath::Max(MCtot1_scaled->GetMaximum(),data1->GetMaximum()) );

  TCanvas* c22 = new TCanvas();
  diphotonMC2->Scale(SFdiphoton);
  datadrivenQCD2->Scale(SFdatadrivenQCD);
  MCtot2_scaled->Add(constMC2);
  MCtot2_scaled->Add(diphotonMC2);
  MCtot2_scaled->Add(datadrivenQCD2);
  MCtot2_scaled->Draw("hist");
  data2->Draw("E1 same");
  MCtot2_scaled->GetYaxis()->SetRangeUser(0., 1.3*TMath::Max(MCtot2_scaled->GetMaximum(),data2->GetMaximum()) );

}
