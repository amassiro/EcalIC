

//
//---- multiply IC
//

void differenceIC( std::string nameInputFileOne = "dump_Data_EcalIntercalibConstants__since_00298613_till_18446744073709551615.dat",
                 std::string nameInputFileTwo = "dump_Data_EcalIntercalibConstants__since_00298613_till_18446744073709551615.dat",
                 std::string nameOutputFile   = "out.dat"
) {
  
  gStyle->SetOptStat(0);
  
  //   
  // input file_One format:
  //
  // ix/ieta iy/iphi   iz_One/0       IC_One        rawId
  //
  // -85    2    0        0.983292 838904322
  // 
  
  
  
  std::vector<int> ix_ieta_One;
  std::vector<int> iy_iphi_One;
  std::vector<int> iz_One;
  
  std::vector<float> IC_One;
  std::vector<unsigned int> RawId_One;
  
  std::ifstream file_One (nameInputFileOne.c_str()); 
  
  std::string buffer;
  
  if(!file_One.is_open()) {
    std::cerr << "** ERROR: Can't open '" << nameInputFileOne.c_str() << "' for input" << std::endl;
    exit(0);
  }
  
  int num;
  float value;
  unsigned int value_ui;
  while(!file_One.eof()) {
    getline(file_One,buffer);
    //     std::cout << "buffer = " << buffer << std::endl;
    if (buffer != "" && buffer.at(0) != '#'){ ///---> save from empty line at the end and from comments starting from "#"
      std::stringstream line( buffer );      
      line >> num; 
      ix_ieta_One.push_back(num);
      line >> num; 
      iy_iphi_One.push_back(num);
      line >> num; 
      iz_One.push_back(num);
      
      
      line >> value; 
      IC_One.push_back(value);

      line >> value_ui; 
      RawId_One.push_back(value_ui);
      
    } 
  }
  
  
  std::cout << " ix_ieta_One.size() = " << ix_ieta_One.size() << std::endl;
  
  if (ix_ieta_One.size() > 75848) {
    std::cout << " Attention: you appended the tag twice!" << std::endl;
  }    
  
  
  
  
  
  
  
  
  std::vector<int> ix_ieta_Two;
  std::vector<int> iy_iphi_Two;
  std::vector<int> iz_Two;
  
  std::vector<float> IC_Two;
  std::vector<unsigned int> RawId_Two;
  
  std::ifstream file_Two (nameInputFileTwo.c_str()); 
  
  
  if(!file_Two.is_open()) {
    std::cerr << "** ERROR: Can't open '" << nameInputFileTwo.c_str() << "' for input" << std::endl;
    exit(0);
  }
  
  while(!file_Two.eof()) {
    getline(file_Two,buffer);
    //     std::cout << "buffer = " << buffer << std::endl;
    if (buffer != "" && buffer.at(0) != '#'){ ///---> save from empty line at the end and from comments starting from "#"
      std::stringstream line( buffer );      
      line >> num; 
      ix_ieta_Two.push_back(num);
      line >> num; 
      iy_iphi_Two.push_back(num);
      line >> num; 
      iz_Two.push_back(num);
      
      
      line >> value; 
      IC_Two.push_back(value);
 
      line >> value_ui; 
      RawId_Two.push_back(value_ui);
      
    } 
  }
  
  
  std::cout << " ix_ieta_Two.size() = " << ix_ieta_Two.size() << std::endl;
  
  if (ix_ieta_Two.size() > 75848) {
    std::cout << " Attention: you appended the tag twice!" << std::endl;
  }    
  
  
  
  
  
  
  //   
  // output file format:
  //
  // ix/ieta iy/iphi   iz_One/0       IC_One        rawId
  //
  // -85    2    0        0.983292 838904322
  // 
  
  
  
  ofstream myfile;
  myfile.open (nameOutputFile.c_str());
  
  for (int iter = 0; iter < ix_ieta_One.size(); iter++) { 
    if (!(iter % 1000)) std::cout << " iter = " << iter << " [ " << ix_ieta_Two.size() << "]" << std::endl;
    
    float multiplicative = IC_One.at(iter) ;
    //---- very inefficient but it works
    for (int iter_Two = 0; iter_Two < ix_ieta_Two.size(); iter_Two++) { 
      if (iy_iphi_One.at(iter) == iy_iphi_Two.at(iter_Two)  && 
          ix_ieta_One.at(iter) == ix_ieta_Two.at(iter_Two)  && 
          iz_One.at(iter) == iz_Two.at(iter_Two) ) {
           
        multiplicative *= -1; 
        multiplicative += IC_Two.at(iter_Two);
      
      //
      // ---- to speed up ...
      ix_ieta_Two.erase (ix_ieta_Two.begin() + iter_Two ,ix_ieta_Two.begin() + iter_Two+1);
      //
      
      //
      //    one - two 
      //
      
      continue;
      
      }
    }
    
    myfile << ix_ieta_One.at(iter) << "   "  << iy_iphi_One.at(iter) << "   " << iz_One.at(iter) << "   " <<  multiplicative << "   " << RawId_One.at(iter) << std::endl;
  }
  
  myfile.close(); 
  
  
  
}
