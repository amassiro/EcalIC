
void plotADC(int numadc, float transparency) {

 TGraph* graph_value = new TGraph ();
 
 int NMAX = 100;
 
 for (int ieta=0; ieta<NMAX; ieta++) {
   float eta = 1.5 + ieta*(3.0-1.5)/NMAX;  
   //                                              65 MeV per ADC count
   float amplitude_after_transparency_loss = numadc *  65. / 1000. * transparency;
   
   //
   // https://en.wikipedia.org/wiki/Pseudorapidity
   // p = pt * cosh(eta)
   // pt = p / cosh(eta)
   //
   float amplitude_transverse = amplitude_after_transparency_loss / cosh(eta);
   
   graph_value->SetPoint (ieta, eta, amplitude_transverse);
 }
 
 
 graph_value->SetMarkerStyle (20);
 graph_value->SetMarkerSize  (2);
 graph_value->SetMarkerColor (kRed);
 graph_value->SetLineColor   (kRed);
 
 graph_value->Draw("APL");
 graph_value->GetXaxis()->SetTitle("#eta");
 graph_value->GetYaxis()->SetTitle("Laser pulse equivalent Transverse Energy [GeV]");
 
}


