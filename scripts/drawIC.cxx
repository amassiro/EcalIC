

//
//---- plot IC
//

void drawIC(std::string nameInputFile = "dump_Data_EcalIntercalibConstants__since_00298613_till_18446744073709551615.dat") {
  
  gStyle->SetOptStat(0);
  
  TCanvas* ccEB = new TCanvas ("ccEB","",1600,600);
  
  TCanvas* ccEE = new TCanvas ("ccEE","",1600,600);
  
  
  //   
  // input file format:
  //
  // ix/ieta iy/iphi   iz/0       IC        rawId
  //
  // -85    2    0        0.983292 838904322
  // 
  
  
  
  std::vector<int> ix_ieta;
  std::vector<int> iy_iphi;
  std::vector<int> iz;
  
  std::vector<float> IC;
  
  std::ifstream file (nameInputFile.c_str()); 
  
  std::string buffer;
  
  if(!file.is_open()) {
    std::cerr << "** ERROR: Can't open '" << nameInputFile.c_str() << "' for input" << std::endl;
    exit(0);
  }
  
  int num;
  float value;
  while(!file.eof()) {
    getline(file,buffer);
    //     std::cout << "buffer = " << buffer << std::endl;
    if (buffer != "" && buffer.at(0) != '#'){ ///---> save from empty line at the end and from comments starting from "#"
      std::stringstream line( buffer );      
      line >> num; 
      ix_ieta.push_back(num);
      line >> num; 
      iy_iphi.push_back(num);
      line >> num; 
      iz.push_back(num);
      
      
      line >> value; 
      IC.push_back(value);
      
    } 
  }
  
  
  std::cout << " ix_ieta.size() = " << ix_ieta.size() << std::endl;
  
  if (ix_ieta.size() > 75848) {
    std::cout << " Attention: you appended the tag twice!" << std::endl;
  }    
  
  
  //---- EB ----
  
  TH2F* histoEB_IC = new TH2F ("histoEB_IC", "IC" ,  360, 0.5, 360.5,  171, -85.5, 85.5);
  histoEB_IC->GetXaxis()->SetTitle("i#phi");
  histoEB_IC->GetYaxis()->SetTitle("i#eta");
  
  
  for (int iter = 0; iter < ix_ieta.size(); iter++) {
    if (iz.at(iter) == 0) {
      
      histoEB_IC->Fill(iy_iphi.at(iter), ix_ieta.at(iter), IC.at(iter) );
      
    }
  }
  
  ccEB->cd();
  histoEB_IC->Draw("colz");
  ccEB->SaveAs("IC_EB.png");
  ccEB->SaveAs("IC_EB.root");
  
  
  
  
  
  
  //---- EE ----
  
  TH2F* histoEE_IC = new TH2F ("histoEE_IC", "IC" ,  200, 0.5, 200.5,  100, 0.5, 100.5);
  
  
  histoEE_IC->GetXaxis()->SetTitle("x");
  histoEE_IC->GetYaxis()->SetTitle("y");
  
  for (int iter = 0; iter < ix_ieta.size(); iter++) {
    if (iz.at(iter) != 0) {
      
      histoEE_IC->Fill(ix_ieta.at(iter) + 100*(iz.at(iter)>0), iy_iphi.at(iter), IC.at(iter) );
      
    }
  }
  
  ccEE->cd();
  histoEE_IC->Draw("colz");
  ccEE->SaveAs("IC_EE.png");
  ccEE->SaveAs("IC_EE.root");  
  
  //   
  //   iring = sqrt ((ix-100)^2 + (iy-100)^2)
  //   
  
  std::vector<float> ringPlus_IC;          std::vector<float> ringMinus_IC;
  std::vector<int> ringPlus_ICcount;       std::vector<int> ringMinus_ICcount;  
  
  for (int iter = 0; iter < (50-11+3); iter++) {
    ringPlus_IC.push_back(0);            ringMinus_IC.push_back(0);
    ringPlus_ICcount.push_back(0);       ringMinus_ICcount.push_back(0);
  }
  
  for (int iter = 0; iter < ix_ieta.size(); iter++) {
    if (iz.at(iter) != 0) {
      
      float dx = ix_ieta.at(iter) - 50;
      float dy = iy_iphi.at(iter) - 50;
      
      float ring = sqrt( dx*dx + dy*dy );
      
      int iring = round(ring) - 11;  //---- 12 [ = (62 - 50 - 1) from the 2D plot] is the first ring
      
      
      if (iring > (50-11+2) || iring < 0) std::cout << " what ?!?   iring = " << iring << " dx = " << dx << " dy = " << dy << " :::: ix = " << ix_ieta.at(iter) << "  iy = " << iy_iphi.at(iter) << std::endl;
      
      if (iz.at(iter) > 0) {
        
        ringPlus_IC.at(iring) = ringPlus_IC.at(iring) + IC.at(iter);
        ringPlus_ICcount.at(iring) =  ringPlus_ICcount.at(iring) + 1 ;      
        
      } 
      else {
        
        ringMinus_IC.at(iring) = ringMinus_IC.at(iring) + IC.at(iter);
        ringMinus_ICcount.at(iring) =  ringMinus_ICcount.at(iring) + 1 ;      
        
        
      }
      
    } 
  }
  
  
  TGraph *gr_EEPlus_IC = new TGraph();     TGraph *gr_EEMinus_IC = new TGraph();
  
  
  for (int iter = 0; iter < (50-11+3); iter++) {
    
    gr_EEPlus_IC-> SetPoint (iter,  42 -  iter,   ringPlus_ICcount.at(iter)  ?  ringPlus_IC.at(iter)  / ringPlus_ICcount.at(iter)  : 0 ) ;           
    gr_EEMinus_IC-> SetPoint (iter, 42 -   iter,  ringMinus_ICcount.at(iter) ?  ringMinus_IC.at(iter) / ringMinus_ICcount.at(iter) : 0 ) ;  
    
  }
  
  
  //---- style ----
  
  gr_EEPlus_IC->SetMarkerSize  (1);                           gr_EEMinus_IC->SetMarkerSize  (1);
  gr_EEPlus_IC->SetMarkerStyle (24);                          gr_EEMinus_IC->SetMarkerStyle (22);
  gr_EEPlus_IC->SetMarkerColor (kRed);                        gr_EEMinus_IC->SetMarkerColor (kRed);
  gr_EEPlus_IC->SetLineWidth (1);                             gr_EEMinus_IC->SetLineWidth (1);
  gr_EEPlus_IC->SetLineColor (kRed);                          gr_EEMinus_IC->SetLineColor (kRed);
  
  
  //---- style (end) ----
  
  
  TCanvas* ccRing = new TCanvas ("ccRing","",800,600);
  
  gr_EEPlus_IC->Draw("APL");
  gr_EEMinus_IC->Draw("PL");
  
  gr_EEPlus_IC->GetYaxis()->SetTitle("<IC>");
  gr_EEPlus_IC->GetXaxis()->SetTitle("iRing");
  
  ccRing->SaveAs("IC_EE_perRing.png");
  ccRing->SaveAs("IC_EE_perRing.root");  
  
  
  
  //   
  //   iring = ieta in EB
  //   
  
  std::vector<float> EBringPlus_IC;          std::vector<float> EBringMinus_IC;
  std::vector<int> EBringPlus_ICcount;       std::vector<int> EBringMinus_ICcount;  
  
  for (int iter = 0; iter < 85; iter++) {
    EBringPlus_IC.push_back(0);            EBringMinus_IC.push_back(0);
    EBringPlus_ICcount.push_back(0);       EBringMinus_ICcount.push_back(0);
  }
  
  for (int iter = 0; iter < ix_ieta.size(); iter++) {
    if (iz.at(iter) == 0) {
      
      int iEBring = abs(ix_ieta.at(iter)) - 1 ;
      
      
      if (iEBring > 84 || iEBring < 0) std::cout << " what ?!?   iEBring = " << iEBring << std::endl;
      
      if (ix_ieta.at(iter) > 0) {
        
        EBringPlus_IC.at(iEBring) = EBringPlus_IC.at(iEBring) + IC.at(iter);
        EBringPlus_ICcount.at(iEBring) =  EBringPlus_ICcount.at(iEBring) + 1 ;      
        
      } 
      else {
        
        EBringMinus_IC.at(iEBring) = EBringMinus_IC.at(iEBring) + IC.at(iter);
        EBringMinus_ICcount.at(iEBring) =  EBringMinus_ICcount.at(iEBring) + 1 ;      
        
      }
      
    } 
  }
  
  
  TGraph *gr_EBPlus_IC = new TGraph();     TGraph *gr_EBMinus_IC = new TGraph();
  
  for (int iter = 0; iter < 85; iter++) {
    
    gr_EBPlus_IC-> SetPoint (iter,    iter+1,   EBringPlus_ICcount.at(iter) ? EBringPlus_IC.at(iter) / EBringPlus_ICcount.at(iter) : 0 ) ;           
    gr_EBMinus_IC-> SetPoint (iter,    iter+1,   EBringMinus_ICcount.at(iter) ?  EBringMinus_IC.at(iter) / EBringMinus_ICcount.at(iter) : 0 ) ;  
    
  }
  
  
  //---- style ----
  
  gr_EBPlus_IC->SetMarkerSize  (1);                           gr_EBMinus_IC->SetMarkerSize  (1);
  gr_EBPlus_IC->SetMarkerStyle (24);                          gr_EBMinus_IC->SetMarkerStyle (22);
  gr_EBPlus_IC->SetMarkerColor (kRed);                        gr_EBMinus_IC->SetMarkerColor (kRed);
  gr_EBPlus_IC->SetLineWidth (1);                             gr_EBMinus_IC->SetLineWidth (1);
  gr_EBPlus_IC->SetLineColor (kRed);                          gr_EBMinus_IC->SetLineColor (kRed);
  
  
  //---- style (end) ----
  
  
  TCanvas* ccRingEB = new TCanvas ("ccRingEB","",800,600);
  
  gr_EBPlus_IC->Draw("APL");
  gr_EBMinus_IC->Draw("PL");
  
  gr_EBPlus_IC->GetYaxis()->SetTitle("<IC>");
  gr_EBPlus_IC->GetXaxis()->SetTitle("i#eta");
  
  ccRingEB->SaveAs("IC_EB_perRing.png");
  ccRingEB->SaveAs("IC_EB_perRing.root");    
  
  
  TFile fileout("fileOut.root","RECREATE");
  fileout.cd();
  histoEB_IC->Write();
  histoEE_IC->Write();
}
