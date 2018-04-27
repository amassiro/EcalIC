//
// dump IC in different run ranges into a TTree
//

int DumpTree(){

  std::string folder = "/tmp/amassiro/data_flat/";
  
  system( (std::string("ls " + folder + " | grep \".dat\" > test.txt")).c_str() );
  
  int numFiles = system( (std::string("wc test.txt")).c_str() );
  
  std::cout << " num files = " << numFiles << std::endl;
  
  
  
  // ---- read iring definition from file
  //        (ix, iy, iz) -> ring
  //
  
  
  std::map < std::pair<int, int> , int > iring_map_plus;
  std::map < std::pair<int, int> , int > iring_map_minus;
  
  std::ifstream fileEEring ("eerings.dat"); 
  
  std::string buffer;
  int num;
  if (!fileEEring.is_open()) {
    std::cerr << "** ERROR: Can't open EE ring for input" << std::endl;
    return false;
  }
  
  while(!fileEEring.eof()) {
    getline(fileEEring,buffer);
    if (buffer != ""){ ///---> save from empty line at the end!
      int temp_ix;
      int temp_iy;
      int temp_iz;
      int temp_iring;
      
      //       std::cout << " buffer = " << buffer << std::endl;
      
      std::stringstream line( buffer );      
      line >> temp_ix; 
      line >> temp_iy; 
      line >> temp_iz; 
      line >> temp_iring; 
      
      std::pair<int, int> ixiy (temp_ix, temp_iy);
      //       if (iz>0) iring_map_plus  [ixiy] = 38 - iring;
      //       else      iring_map_minus [ixiy] = 38 - iring;
      
      if (temp_iz>0) iring_map_plus  [ixiy] = temp_iring;
      else           iring_map_minus [ixiy] = temp_iring;
      
    } 
  }
  
  std::cout << " ee rings loaded ..." << std::endl;
  
  
  
  
  //---- output file
  
  
  TFile* outFile = new TFile ("dumpIC.root", "RECREATE");
  
  TTree* tree = new TTree ();
  
  std::vector<float> value;
  std::vector<int> ix;
  std::vector<int> iy;
  std::vector<int> iz;
  std::vector<int> ieta;
  std::vector<int> iphi;
  std::vector<int> iring;
 
  tree->Branch("value", &value);
  tree->Branch("ix",    &ix);
  tree->Branch("iy",    &iy);
  tree->Branch("iz",    &iz);
  tree->Branch("ieta",  &ieta);
  tree->Branch("iphi",  &iphi);
  tree->Branch("iring", &iring);
  


  std::ifstream fileList ("test.txt"); 
  if(!fileList.is_open()) {
    std::cerr << "** ERROR: Can't open fileList for input" << std::endl;
    return false;
  }
  
  while(!fileList.eof()) {
    getline(fileList,buffer);
    if (buffer != ""){ ///---> save from empty line at the end!
      
      std::string name_file = buffer;
      
      std::cout << " name_file = " << (folder + name_file) << std::endl;
      
      std::ifstream file ( (folder + name_file).c_str()); 
      
      int num1, num2, num3;
      float val;
      
      
      value.clear();
      ix.clear();
      iy.clear();
      iz.clear();
      ieta.clear();
      iphi.clear();
      iring.clear();
      
      
      if(!file.is_open()) {
        std::cerr << "** ERROR: Can't open file for input" << std::endl;
        return false;
      }
      
      while(!file.eof()) {
        getline(file,buffer);
        if (buffer != ""){ ///---> save from empty line at the end!
          
          //       
          //      EB
          //       -85 33 0 0.862160 838904353
          //      EE 
          //       53 100 1 0.472275 872438500
          //      
          
          std::stringstream line( buffer );      
          line >> num1; 
          line >> num2; 
          line >> num3;
          
          iz.push_back(num3);
          
          //---- EB
          if (num3 == 0) {
            ix.push_back(-999);
            iy.push_back(-999);
            
            ieta.push_back(num1);
            iphi.push_back(num2);
            iring.push_back(fabs(num1));
          }
          //---- EE
          else {
            ix.push_back(num1);
            iy.push_back(num2);
            
            std::pair<int, int> ixiy (num1%100, num2%100);      
            int temp_iring = iring_map_plus [ixiy];       
            iring.push_back( temp_iring );
            
            ieta.push_back(-999);
            iphi.push_back(-999);
          }
          
          line >> val; 
          
          value.push_back(val);
          
        } 
        
      }
      tree->Fill();
    }
  }
  
  
  tree->Write();
  
  
  
  return 0;
  
}




