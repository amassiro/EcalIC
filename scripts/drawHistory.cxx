

void drawHistory() {
  
  std::vector<float> *value;
  std::vector<int> *ix;
  std::vector<int> *iy;
  std::vector<int> *iz;
  std::vector<int> *ieta;
  std::vector<int> *iphi;
  std::vector<int> *iring;
  int *iov_min;
  
  tree->SetBranchAddress("value", value);
  tree->SetBranchAddress("ix",    ix);
  tree->SetBranchAddress("iy",    iy);
  tree->SetBranchAddress("iz",    iz);
  tree->SetBranchAddress("ieta",  ieta);
  tree->SetBranchAddress("iphi",  iphi);
  tree->SetBranchAddress("iring", iring);
 
  tree->SetBranchAddress("iov_min", iov_min);
  
  
  int ieta_to_draw = 1;
  
  
  TGraph* gr_mean = new TGraph ();
  int nentries = tree->GetEntries();
  float mean = 0;
  for (int i=0; i<nentries; i++) {
    tree->GetEntry(i);
    int num = 0;
    for (int ixtal=0; ixtal<value.size(); ixtal++) {
      if (iphi[ixtal] == ieta_to_draw) {
        mean += value[ixtal];
        num++;
      } 
    }
    
    gr_mean->SetPoint (i, iov_min, mean/num);
  }
  
  gr_mean->Draw("APL");
  
}
