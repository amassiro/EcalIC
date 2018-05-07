
// https://root-forum.cern.ch/t/th2-col-above-lego/16180
int GetColorFromPalette ( int iter, int max, int min=0) {
  /// http://root.cern.ch/phpBB3/viewtopic.php?f=12&t=4101&p=16258 -> See THistPainter::PaintColorLevels()
  //  https://root-forum.cern.ch/t/th2-col-above-lego/16180
  Int_t ncolors  = gStyle->GetNumberOfColors() ;
  Int_t ndiv = max - min;
  if (ndiv == 0 ) { ndiv = gStyle->GetNumberContours() ; }
  Int_t ndivz = TMath::Abs(ndiv) ;
  Double_t zmin = min, zmax = max ;
  Double_t dz = zmax - zmin ;
  Double_t scale = ndivz/dz ;
  Int_t color = Int_t(0.01+(iter-zmin)*scale) ;
  Int_t theColor = Int_t((color+0.99)*Float_t(ncolors)/Float_t(ndivz)) ;
  if (theColor > ncolors-1) theColor = ncolors-1 ;  
  return (gStyle->GetColorPalette(theColor)) ;
}




void drawHistoryAll() {
  
  std::vector<float> *value = 0;
  std::vector<int> *ix = 0;
  std::vector<int> *iy = 0;
  std::vector<int> *iz = 0;
  std::vector<int> *ieta = 0;
  std::vector<int> *iphi = 0;
  std::vector<int> *iring = 0;
  int iov_min;
  
  tree->SetBranchAddress("value", &value);
  tree->SetBranchAddress("ix",    &ix);
  tree->SetBranchAddress("iy",    &iy);
  tree->SetBranchAddress("iz",    &iz);
  tree->SetBranchAddress("ieta",  &ieta);
  tree->SetBranchAddress("iphi",  &iphi);
  tree->SetBranchAddress("iring", &iring);
 
  tree->SetBranchAddress("iov_min", &iov_min);
  
  TMultiGraph* mg = new TMultiGraph();
  TGraphErrors* gr_mean[85];

  float mean[85];
  float rms[85];
  int num[85];
  float reference[85];

  int MINETA = 0;
  int MAXETA = 85;
  
  int nentries = tree->GetEntries();
  for (int jeta=MINETA; jeta<MAXETA; jeta++) {
    gr_mean[jeta] = new TGraphErrors ();
    reference[jeta] = 1.;
  }
  
  for (int i=0; i<nentries; i++) {
    if (! (i%20) ) std::cout << " i = " << i << " :: " << nentries << std::endl;
    
    //     for (int i=1; i<nentries; i++) {
    tree->GetEntry(i);
    
    for (int jeta=MINETA; jeta<MAXETA; jeta++) {
//       std::cout << " jeta = " << jeta << std::endl;
      
      int ieta_to_draw = jeta+1;
      
      //     for (int i=0; i<nentries; i++) {
      mean[jeta] = 0;
      num[jeta] = 0;
      rms[jeta] = 0;
      for (int ixtal=0; ixtal<value->size(); ixtal++) {
        if (ieta->at(ixtal) == ieta_to_draw) {
          mean[jeta] += value->at(ixtal);
          rms[jeta] += (value->at(ixtal)*value->at(ixtal));
          num[jeta]++;
        } 
      }
      
//       if (i == 0) reference[jeta]  = float(mean[jeta]/num[jeta]);
      if (i == 1) reference[jeta] = float(mean[jeta]/num[jeta]);
      
//       gr_mean[jeta]->SetPoint      (i-1, float(iov_min), float(mean[jeta]/num[jeta]) - reference[jeta]);
      gr_mean[jeta]->SetPoint      (i, float(iov_min), float(mean[jeta]/num[jeta]) / reference[jeta] );
      //       gr_mean[jeta]->SetPointError (i, 0, sqrt(rms[jeta]/num[jeta] - mean[jeta]/num[jeta]*mean[jeta]/num[jeta]) / reference[jeta] );
      
    }
    
  }
  
  
  TLegend* lg = new TLegend(0.90,0.10,0.99,0.90);
  
  
  for (int jeta=MINETA; jeta<MAXETA; jeta++) {
    
    //---- for some reason the first point is ==1
    gr_mean[jeta]->RemovePoint(0);
    
    gr_mean[jeta]->SetMarkerColor(GetColorFromPalette ( jeta, 0, 85));
    gr_mean[jeta]->SetMarkerSize(1.0);
    gr_mean[jeta]->SetMarkerStyle(20);
    gr_mean[jeta]->SetLineColor(GetColorFromPalette ( jeta, 0, 85));
    gr_mean[jeta]->SetLineWidth(1.0);
    
    mg->Add(gr_mean[jeta]);
  
    TString name = Form ("%d", jeta);
    lg->AddEntry(gr_mean[jeta],name.Data(),"p");
    
    
  }
 
 
 
 mg->Draw("APL");
  
 lg->Draw();
 
  
}
