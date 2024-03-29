class chisquare 
{

public:
  chisquare(TH1F* data1, TH1F* constMC1, TH1F* diphotonMC1, TH1F* datadrivenQCDEE1,TH1F* datadrivenQCDEB1,
	    TH1F* data2, TH1F* constMC2, TH1F* diphotonMC2, TH1F* datadrivenQCDEE2,TH1F* datadrivenQCDEB2)
  {
    data1_ = data1; 
    constMC1_ = constMC1; 
    diphotonMC1_ = diphotonMC1; 
    datadrivenQCDEE1_ = datadrivenQCDEE1;
    datadrivenQCDEB1_ = datadrivenQCDEB1;
    data2_ = data2; 
    constMC2_ = constMC2; 
    diphotonMC2_ = diphotonMC2; 
    datadrivenQCDEE2_ = datadrivenQCDEE2;
    datadrivenQCDEB2_ = datadrivenQCDEB2;
    SFdiphoton_ = 1.;
    SFdatadrivenQCDEE_ = 1.;
    SFdatadrivenQCDEB_ = 1.;
  }
  double operator()( double* SFs, double *p)
  //  double operator()(double SFdiphoton, double SFdatadrivenQCDEE, double SFdatadrivenQCDEB)
  {
    SFdiphoton_ = SFs[0];
    SFdatadrivenQCDEE_ = SFs[1];
    SFdatadrivenQCDEB_ = SFs[2];
    // cout<<"SFdiphoton_:"<<SFdiphoton_<<endl;
    // cout<<"SFdatadrivenQCDEE_:"<<SFdatadrivenQCDEE_<<endl;
    // cout<<"SFdatadrivenQCDEB_:"<<SFdatadrivenQCDEB_<<endl;
    double chisquarevalue = 0.;
    for(int ibin=1; ibin<=data1_->GetXaxis()->GetNbins(); ++ibin) {
      double Nev_data1 = data1_->GetBinContent(ibin);
      double Nev_constMC1 = constMC1_->GetBinContent(ibin);
      double Nev_diphotonMC1 = SFdiphoton_ * diphotonMC1_->GetBinContent(ibin);
      double Nev_datadrivenQCDEEMC1 = SFdatadrivenQCDEE_ * datadrivenQCDEE1_->GetBinContent(ibin);
      double Nev_datadrivenQCDEBMC1 = SFdatadrivenQCDEB_ * datadrivenQCDEB1_->GetBinContent(ibin);
      double Nev_exp1 = Nev_constMC1+Nev_diphotonMC1+Nev_datadrivenQCDEEMC1+Nev_datadrivenQCDEBMC1;
  
      if (Nev_data1 == 0) {
        Nev_data1 = 1e-6; // 或者其他很小的值
      }
      else{
        chisquarevalue += (Nev_data1-Nev_exp1)*(Nev_data1-Nev_exp1) / Nev_data1;}
    }
    for(int ibin=1; ibin<=data2_->GetXaxis()->GetNbins(); ++ibin) {
      double Nev_data2 = data2_->GetBinContent(ibin);
      double Nev_constMC2 = constMC2_->GetBinContent(ibin);
      double Nev_diphotonMC2 = SFdiphoton_ * diphotonMC2_->GetBinContent(ibin);
      double Nev_datadrivenQCDEEMC2 = SFdatadrivenQCDEE_ * datadrivenQCDEE2_->GetBinContent(ibin);
      double Nev_datadrivenQCDEBMC2 = SFdatadrivenQCDEB_ * datadrivenQCDEB2_->GetBinContent(ibin);
      double Nev_exp2 = Nev_constMC2+Nev_diphotonMC2+Nev_datadrivenQCDEEMC2+Nev_datadrivenQCDEBMC2; 
      if (Nev_data2 == 0) {
        Nev_data2 = 1e-6; // 或者其他很小的值
      }
      else {  
        chisquarevalue += (Nev_data2-Nev_exp2)*(Nev_data2-Nev_exp2) / Nev_data2;
      }
    }
      // cout<<"chisquarevalue:"<<chisquarevalue<<endl;
      return chisquarevalue;
  }
  
private:
  TH1F *data1_, *constMC1_, *diphotonMC1_, *datadrivenQCDEE1_, *datadrivenQCDEB1_;
  TH1F *data2_, *constMC2_, *diphotonMC2_, *datadrivenQCDEE2_, *datadrivenQCDEB2_;
  double SFdiphoton_, SFdatadrivenQCDEE_, SFdatadrivenQCDEB_;
};
void deriveSFscat8()
{

  string common_selection = "(Diphoton_mass<115 || Diphoton_mass>135)*(is_passPhotonMVA90)*(category==8)*(weight_central>0)";
  map<string, vector<string> > filenames_map;
  map<string, vector<string> > treenames_map;
  map<string, vector<float> > lumis_map;
  filenames_map["data"] = { vector<string>{
      "/eos/user/s/shsong/HiggsDNA/root/cat8/Data_2017.root"
    }};
  filenames_map["qcdEB"] = { vector<string>{
      "/eos/user/s/shsong/HiggsDNA/root/cat8/DatadrivenQCDEB.root"
    }};
  filenames_map["qcdEE"] = { vector<string>{
      "/eos/user/s/shsong/HiggsDNA/root/cat8/DatadrivenQCDEE.root"
    }};
  filenames_map["diphoton"] = { vector<string>{
      "/eos/user/s/shsong/HiggsDNA/root/cat8/DiPhotonJetsBox.root"
    }};
  treenames_map["data"] = { vector<string>{
      "cat8"
    }};
  treenames_map["qcdEE"] = { vector<string>{
      "cat8"
    }};
  treenames_map["qcdEB"] = { vector<string>{
      "cat8"
    }};
  treenames_map["diphoton"] = { vector<string>{
      "cat8"
    }};
  lumis_map["data"] = {vector<float>{
    1
  }};
  lumis_map["qcdEE"] = {vector<float>{
    1
  }};
  lumis_map["qcdEB"] = {vector<float>{
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
    auto filenames = filenameitr.second;
    auto treenames = treenames_map[samplename];
    auto lumis = lumis_map[samplename];
    h_minphotonID[samplename] = new TH1F(Form("h_minphotonID_%s",samplename.c_str()),
					 Form("h_minphotonID_%s",samplename.c_str()),
					 39,-0.3,1);
    h_maxphotonID[samplename] = new TH1F(Form("h_maxphotonID_%s",samplename.c_str()),
					 Form("h_maxphotonID_%s",samplename.c_str()),
					 39,-0.3,1);
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

  h_minphotonID["otherMC"] = new TH1F("constMC1","constMC1",39,-0.3,1);  
  h_minphotonID["MCtot"] = new TH1F("MCtot1","MCtot1",39,-0.3,1);
  h_minphotonID["scaledMCtot"] = new TH1F("MCtot1_scaled","MCtot1_scaled",39,-0.3,1);
  h_maxphotonID["otherMC"] = new TH1F("constMC2","constMC2",39,-0.3,1); 
  h_maxphotonID["MCtot"] = new TH1F("MCtot2","MCtot2",39,-0.3,1);
  h_maxphotonID["scaledMCtot"] = new TH1F("MCtot2_scaled","MCtot2_scaled",39,-0.3,1);

  TCanvas* c1 = new TCanvas();
  h_minphotonID["MCtot"]->Add(h_minphotonID["otherMC"]);
  h_minphotonID["MCtot"]->Add(h_minphotonID["diphoton"]);
  h_minphotonID["MCtot"]->Add(h_minphotonID["qcdEE"]);
  h_minphotonID["MCtot"]->Add(h_minphotonID["qcdEB"]);
  h_minphotonID["MCtot"]->Draw("hist");
  h_minphotonID["data"]->SetMarkerStyle(20);
  h_minphotonID["data"]->Draw("E1 same");
  h_minphotonID["MCtot"]->GetYaxis()->SetRangeUser(0., 1.3*TMath::Max(h_minphotonID["MCtot"]->GetMaximum(),h_minphotonID["data"]->GetMaximum()) );
  cout<<"Data minID:"<<h_minphotonID["data"]->Integral()<<endl;
  cout<<"QCDEE minID:"<<h_minphotonID["qcdEE"]->Integral()<<endl;
  cout<<"QCDEB minID:"<<h_minphotonID["qcdEB"]->Integral()<<endl;
  cout<<"DiPhoton minID:"<<h_minphotonID["diphoton"]->Integral()<<endl;

  c1->SaveAs("Diphoton_minID_cat8.png");

  TCanvas* c12 = new TCanvas();
  h_maxphotonID["MCtot"]->Add(h_maxphotonID["otherMC"]);
  h_maxphotonID["MCtot"]->Add(h_maxphotonID["diphoton"]);
  h_maxphotonID["MCtot"]->Add(h_maxphotonID["qcdEE"]);
  h_maxphotonID["MCtot"]->Add(h_maxphotonID["qcdEB"]);
  h_maxphotonID["MCtot"]->Draw("hist");
  h_maxphotonID["data"]->SetMarkerStyle(20);
  h_maxphotonID["data"]->Draw("E1 same");
  h_maxphotonID["MCtot"]->GetYaxis()->SetRangeUser(0., 1.3*TMath::Max(h_maxphotonID["MCtot"]->GetMaximum(),h_maxphotonID["data"]->GetMaximum()) );
  cout<<"Data maxID:"<<h_maxphotonID["data"]->Integral()<<endl;
  cout<<"QCDEE maxID:"<<h_maxphotonID["qcdEE"]->Integral()<<endl;
  cout<<"QCDEB maxID:"<<h_maxphotonID["qcdEB"]->Integral()<<endl;
  cout<<"DiPhoton maxID:"<<h_maxphotonID["diphoton"]->Integral()<<endl;
  c12->SaveAs("Diphoton_maxID_cat8.png");

  chisquare chisquareobj(h_minphotonID["data"], h_minphotonID["otherMC"], h_minphotonID["diphoton"], h_minphotonID["qcdEE"], h_minphotonID["qcdEB"],h_maxphotonID["data"], h_maxphotonID["otherMC"], h_maxphotonID["diphoton"], h_maxphotonID["qcdEE"], h_maxphotonID["qcdEB"]);
  cout<<"getting all chisquareobj"<<endl;
  TF3 *f = new TF3("chi2",chisquareobj,0.000001,10.,0.000001,10.,0.000001,10.,0);
  double SFdiphoton, SFdatadrivenQCDEE, SFdatadrivenQCDEB;
  double chi2 = f->GetMinimumXYZ(SFdiphoton, SFdatadrivenQCDEE, SFdatadrivenQCDEB);
 
  cout << "observed: " << SFdiphoton << " " << SFdatadrivenQCDEE << " " << SFdatadrivenQCDEB << " chi2=" << chi2 << endl;

  TCanvas* c21 = new TCanvas();

  h_minphotonID["diphoton"]->Scale(SFdiphoton);
  h_minphotonID["qcdEE"]->Scale(0.7*SFdatadrivenQCDEE);
  h_minphotonID["qcdEB"]->Scale(1.3*SFdatadrivenQCDEB);
  h_minphotonID["scaledMCtot"]->Add(h_minphotonID["otherMC"]);
  h_minphotonID["scaledMCtot"]->Add(h_minphotonID["diphoton"]);
  h_minphotonID["scaledMCtot"]->Add(h_minphotonID["qcdEE"]);
  h_minphotonID["scaledMCtot"]->Add(h_minphotonID["qcdEB"]);
  h_minphotonID["scaledMCtot"]->Draw("hist");
  h_minphotonID["data"]->Draw("E1 same");
  cout<<"Data:"<<h_minphotonID["data"]->Integral()<<endl;
  cout<<"QCDEE:"<<h_minphotonID["qcdEE"]->Integral()<<endl;
  cout<<"QCDEB:"<<h_minphotonID["qcdEB"]->Integral()<<endl;
  cout<<"DiPhoton:"<<h_minphotonID["diphoton"]->Integral()<<endl;
  h_minphotonID["scaledMCtot"]->GetYaxis()->SetRangeUser(0., 1.3*TMath::Max(h_minphotonID["scaledMCtot"]->GetMaximum(),h_minphotonID["data"]->GetMaximum()) );
  c21->SaveAs("minID_scale_cat8.png");

  TCanvas* c22 = new TCanvas();

  h_maxphotonID["diphoton"]->Scale(SFdiphoton);
  h_maxphotonID["qcdEE"]->Scale(0.7*SFdatadrivenQCDEE);
  h_maxphotonID["qcdEB"]->Scale(1.3*SFdatadrivenQCDEB);
  h_maxphotonID["scaledMCtot"]->Add(h_maxphotonID["otherMC"]);
  h_maxphotonID["scaledMCtot"]->Add(h_maxphotonID["diphoton"]);
  h_maxphotonID["scaledMCtot"]->Add(h_maxphotonID["qcdEE"]);
  h_maxphotonID["scaledMCtot"]->Add(h_maxphotonID["qcdEB"]);
  h_maxphotonID["scaledMCtot"]->Draw("hist");
  h_maxphotonID["data"]->Draw("E1 same");
  cout<<"Data:"<<h_maxphotonID["data"]->Integral()<<endl;
  cout<<"QCDEE:"<<h_maxphotonID["qcdEE"]->Integral()<<endl;
  cout<<"QCDEB:"<<h_maxphotonID["qcdEB"]->Integral()<<endl;
  cout<<"DiPhoton:"<<h_maxphotonID["diphoton"]->Integral()<<endl;
  h_maxphotonID["scaledMCtot"]->GetYaxis()->SetRangeUser(0., 1.3*TMath::Max(h_maxphotonID["scaledMCtot"]->GetMaximum(),h_maxphotonID["data"]->GetMaximum()) );


  c22->SaveAs("maxID_scale_cat8.png");
}

