
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




void drawHistoryAllEE() {
  
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
  TGraphErrors* gr_mean[39];

  float mean[39];
  float rms[39];
  int num[39];
  float reference[39];

  int MINRING = 0;
  int MAXRING = 39;
  
  int nentries = tree->GetEntries();
  for (int jring=MINRING; jring<MAXRING; jring++) {
    gr_mean[jring] = new TGraphErrors ();
    reference[jring] = 1.;
  }
  
  for (int i=0; i<nentries; i++) {
    if (! (i%20) ) std::cout << " i = " << i << " :: " << nentries << std::endl;
    
    //     for (int i=1; i<nentries; i++) {
    tree->GetEntry(i);
    
    for (int jring=MINRING; jring<MAXRING; jring++) {
//       std::cout << " jring = " << jring << std::endl;
      
      int iring_to_draw = jring+1;
      
      //     for (int i=0; i<nentries; i++) {
      mean[jring] = 0;
      num[jring] = 0;
      rms[jring] = 0;
      for (int ixtal=0; ixtal<value->size(); ixtal++) {
        if ( (ieta->at(ixtal) == -999) && (iring->at(ixtal) == iring_to_draw) ) {
          mean[jring] += value->at(ixtal);
          rms[jring] += (value->at(ixtal)*value->at(ixtal));
          num[jring]++;
        } 
      }
      
//       if (i == 0) reference[jring]  = float(mean[jring]/num[jring]);
      if (i == 1) reference[jring] = float(mean[jring]/num[jring]);
      
//       gr_mean[jring]->SetPoint      (i-1, float(iov_min), float(mean[jring]/num[jring]) - reference[jring]);
      gr_mean[jring]->SetPoint      (i, float(iov_min), float(mean[jring]/num[jring]) / reference[jring] );
      //       gr_mean[jring]->SetPointError (i, 0, sqrt(rms[jring]/num[jring] - mean[jring]/num[jring]*mean[jring]/num[jring]) / reference[jring] );
      
    }
    
  }
  
  TLegend* lg = new TLegend(0.90,0.10,0.99,0.90);
  
  for (int jring=MINRING; jring<MAXRING; jring++) {
    
    //---- for some reason the first point is ==1
    gr_mean[jring]->RemovePoint(0);
    
    gr_mean[jring]->SetMarkerColor(GetColorFromPalette ( jring, 0, 39));
    gr_mean[jring]->SetMarkerSize(1.0);
    gr_mean[jring]->SetMarkerStyle(20);
    gr_mean[jring]->SetLineColor(GetColorFromPalette ( jring, 0, 39));
    gr_mean[jring]->SetLineWidth(1.0);
    
    mg->Add(gr_mean[jring]);
    
    TString name = Form ("%d", jring);
    lg->AddEntry(gr_mean[jring],name.Data(),"p");
    
    
  }
    
  mg->Draw("APL");
  
  lg->Draw();
  
}


