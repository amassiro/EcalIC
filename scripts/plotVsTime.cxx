//
//---- plot evolution vs time
//

void plotVsTime(std::string nameInputFile = "toplot_10.txt", std::string variableHR = "LC") {
  
  TCanvas* cc = new TCanvas ("cc","",800,600);
  
  TGraph *gr = new TGraph(nameInputFile.c_str());
  gr->Draw("APL");
  gr->SetMarkerSize  (1);
  gr->SetMarkerStyle (24);
  gr->SetMarkerColor (kRed);
  gr->SetLineWidth (1);
  gr->SetLineColor (kRed);
  
  
//   gr->GetXaxis()->SetTimeDisplay(1);
//   gr->GetXaxis()->SetNdivisions(-503);
//   gr->GetXaxis()->SetTimeFormat("%Y-%m-%d %H:%M");
//   gr->GetXaxis()->SetTimeOffset(0,"gmt");
  
  
//   gr->GetXaxis()->SetTitle("time");
  gr->GetXaxis()->SetTitle("run");
  gr->GetYaxis()->SetTitle(variableHR.c_str());
  
  cc->SetGrid();
  
  
}


