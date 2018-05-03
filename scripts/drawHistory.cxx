

void drawHistory() {
  
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
  
  
  int ieta_to_draw = 1;
  
  
  TGraphErrors* gr_mean = new TGraphErrors ();
  int nentries = tree->GetEntries();
  float mean = 0;
  float rms = 0;
  int num = 0;
  for (int i=0; i<nentries; i++) {
    tree->GetEntry(i);
    mean = 0;
    num = 0;
    rms = 0;
    for (int ixtal=0; ixtal<value->size(); ixtal++) {
      if (iphi->at(ixtal) == ieta_to_draw) {
        mean += value->at(ixtal);
        rms += (value->at(ixtal)*value->at(ixtal));
        num++;
      } 
    }
    
    gr_mean->SetPoint      (i, float(iov_min), float(mean/num) );
    gr_mean->SetPointError (i, 0, sqrt(rms/num - mean/num*mean/num) );
    
    
    
  }
  
  gr_mean->SetMarkerColor(kRed);
  gr_mean->SetMarkerSize(1.0);
  gr_mean->SetMarkerStyle(20);
  gr_mean->SetLineColor(kRed);
  gr_mean->SetLineWidth(1.0);
  
  gr_mean->Draw("APL");
  
  
}
