// 
// x1, x2, x3, x_true (x_t)
// 
// All randomly distributed around 1.
// 

void simulate(){
  
  TH1F* h_x_1 = new TH1F ("h_x_1", "x1", 2000, 0, 2);
  TH1F* h_x_2 = new TH1F ("h_x_2", "x2", 2000, 0, 2);
  TH1F* h_x_3 = new TH1F ("h_x_3", "x3", 2000, 0, 2);
  TH1F* h_x_t = new TH1F ("h_x_t", "xt", 2000, 0, 2);

  TH1F* h_x_12 = new TH1F ("h_x_12", "x1-x2", 2000, -1, 1);
  TH1F* h_x_13 = new TH1F ("h_x_13", "x1-x3", 2000, -1, 1);
  TH1F* h_x_23 = new TH1F ("h_x_23", "x2-x3", 2000, -1, 1);
  TH1F* h_x_1t = new TH1F ("h_x_1t", "x1-xt", 2000, -1, 1);
  TH1F* h_x_2t = new TH1F ("h_x_2t", "x2-xt", 2000, -1, 1);
  TH1F* h_x_3t = new TH1F ("h_x_3t", "x3-xt", 2000, -1, 1);
  
  float res1 = 0.020;
  float res2 = 0.020;
  float res3 = 0.020;
  float rest = 0.005;
  
  
  TString name;
  
  name = Form ("exp( -(x-1)*(x-1)/(2*%f*%f) )", res1, res1);
  TF1 *f1 = new TF1("f1",name.Data(),0,2);

  name = Form ("exp( -(x-1)*(x-1)/(2*%f*%f) )", res2, res2);
  TF1 *f2 = new TF1("f2",name.Data(),0,2);

  name = Form ("exp( -(x-1)*(x-1)/(2*%f*%f) )", res3, res3);
  TF1 *f3 = new TF1("f3",name.Data(),0,2);

  name = Form ("exp( -(x-1)*(x-1)/(2*%f*%f) )", rest, rest);
  TF1 *ft = new TF1("ft",name.Data(),0,2);
  
  
  int num_events = 100000;
  for (int i=0; i<num_events; i++) {
    float x_1 = f1->GetRandom();
    float x_2 = f2->GetRandom();
    float x_3 = f3->GetRandom();
    float x_t = ft->GetRandom();
    
    h_x_1->Fill(x_1);
    h_x_2->Fill(x_2);
    h_x_3->Fill(x_3);
    h_x_t->Fill(x_t);
    
    h_x_12->Fill(x_1-x_2);
    h_x_13->Fill(x_1-x_3);
    h_x_23->Fill(x_2-x_3);
    h_x_1t->Fill(x_1-x_t);
    h_x_2t->Fill(x_2-x_t);
    h_x_3t->Fill(x_3-x_t);
    
  }
  
  TCanvas* cc = new TCanvas ("cc", "", 800, 600);
  cc->Divide (3,3);
  
  cc->cd(1); h_x_1->Draw();
  cc->cd(2); h_x_2->Draw();
  cc->cd(3); h_x_3->Draw();
  
  cc->cd(4); h_x_12->Draw();
  cc->cd(5); h_x_13->Draw();
  cc->cd(6); h_x_23->Draw();
  
  cc->cd(7); h_x_1t->Draw();
  cc->cd(8); h_x_2t->Draw();
  cc->cd(9); h_x_3t->Draw();
  
  TCanvas* cct = new TCanvas ("cct", "", 800, 600);
  h_x_t->Draw();
  

  std::cout << " ----- " << std::endl;
  std::cout << " ----- " << std::endl;
  std::cout << " ----- " << std::endl;
  
  std::cout << " RMS t = " << h_x_t->GetRMS() << std::endl;
  std::cout << " RMS 1 = " << h_x_1->GetRMS() << std::endl;
  std::cout << " RMS 2 = " << h_x_2->GetRMS() << std::endl;
  std::cout << " RMS 3 = " << h_x_3->GetRMS() << std::endl;
  std::cout << " ----- " << std::endl;
  
  std::cout << " RMS 12 = " << h_x_12->GetRMS() << std::endl;
  std::cout << " RMS 13 = " << h_x_13->GetRMS() << std::endl;
  std::cout << " RMS 23 = " << h_x_23->GetRMS() << std::endl;
  std::cout << " ----- " << std::endl;
  
  std::cout << " RMS 1t = " << h_x_1t->GetRMS() << std::endl;
  std::cout << " RMS 2t = " << h_x_2t->GetRMS() << std::endl;
  std::cout << " RMS 3t = " << h_x_3t->GetRMS() << std::endl;
  std::cout << " ----- " << std::endl;
  

  std::cout << " RMS 2 (+) RMS 3 = " << sqrt(h_x_2->GetRMS()*h_x_2->GetRMS() + h_x_3->GetRMS()*h_x_3->GetRMS()) << " = " << h_x_23->GetRMS() << " = RMS (2-3) " << std::endl;
  

//   
//   P1 + P2 = RMS (1-2)
//   P1 + P3 = RMS (1-3)
//   P2 + P3 = RMS (2-3)
//
//   RMS(1-T) (+) RMS(2-T) != RMS ( (1-T) - (2-T) )
//   RMS(1-T) (+) RMS(3-T) != RMS ( (1-T) - (3-T) )
//   RMS(2-T) (+) RMS(3-T) != RMS ( (2-T) - (3-T) )
//   
//   it can be "==" instead of "!="
//   
//   
//   
//   Algebra:
//   
//   P1 = (   RMS (1-2)^2 + RMS (1-3)^2 - RMS (2-3)^2 ) / 2.
//   P3 = (   RMS (1-2)^2 - RMS (1-3)^2 + RMS (2-3)^2 ) / 2.
//   P3 = ( - RMS (1-2)^2 + RMS (1-3)^2 + RMS (2-3)^2 ) / 2.
//   
  
  
  std::cout << " ----- " << std::endl;
  std::cout << " ----- " << std::endl;
  
  
  std::cout << " P1 = " << sqrt( (   h_x_12->GetRMS()*h_x_12->GetRMS() + h_x_13->GetRMS()*h_x_13->GetRMS() - h_x_23->GetRMS()*h_x_23->GetRMS() ) / 2. ) << " --> P1 = " << sqrt( h_x_1t->GetRMS() * h_x_1t->GetRMS() )<< std::endl;
  std::cout << " P2 = " << sqrt( (   h_x_12->GetRMS()*h_x_12->GetRMS() - h_x_13->GetRMS()*h_x_13->GetRMS() + h_x_23->GetRMS()*h_x_23->GetRMS() ) / 2. ) << " --> P2 = " << sqrt( h_x_2t->GetRMS() * h_x_2t->GetRMS() )<< std::endl;
  std::cout << " P3 = " << sqrt( ( - h_x_12->GetRMS()*h_x_12->GetRMS() + h_x_13->GetRMS()*h_x_13->GetRMS() + h_x_23->GetRMS()*h_x_23->GetRMS() ) / 2. ) << " --> P3 = " << sqrt( h_x_3t->GetRMS() * h_x_3t->GetRMS() )<< std::endl;
  
  std::cout << " ----- " << std::endl;
  std::cout << " ----- " << std::endl;
  
  
}


