Plotting tools
====

Draw the IC for EB and EE


    drawIC.cxx
    
    r99t drawIC.cxx\(\"combined.txt\"\)
    r99t drawIC.cxx\(\"EtaScale_Cal_Oct2017_cand_v5_RunF.relativeToRunB.txt\"\)
    r99t drawIC.cxx\(\"ICsHarness_Cal_Oct2017_cand_v5_RunF.txt\"\)
    r99t drawIC.cxx\(\"Cal_Oct2017_IC_v5_FtoBCDE_template_SF.txt\"\)
    r99t drawIC.cxx\(\"Cal_Oct2017_IC_v5_FtoBCDE_template_SF.txt\",-1\)
 
 
    /afs/cern.ch/user/v/vciriolo/work/public/Cal_Oct2017_IC_v5_FtoBCDE_template_SF.txt

 



Multiply the IC


    multiplyIC.cxx
    
    r99t multiplyIC.cxx\(\"EtaScale_Cal_Oct2017_cand_v5_RunF.relativeToRunB.txt\",\"ICsHarness_Cal_Oct2017_cand_v5_RunF.txt\",\"combined.txt\"\)
 
    /afs/cern.ch/work/f/fcouderc/public/ecal/etaScales/2017/EtaScale_Cal_Oct2017_cand_v5_RunF.relativeToRunB.txt
    /afs/cern.ch/work/f/fcouderc/public/ecal/etaScales/2017/ICsHarness_Cal_Oct2017_cand_v5_RunF.txt
    



Difference the IC

    differenceIC.cxx
    
    r99t differenceIC.cxx\(\"EtaScale_Cal_Oct2017_cand_v5_RunF.relativeToRunB.txt\",\"ICsHarness_Cal_Oct2017_cand_v5_RunF.txt\",\"combined-difference.txt\"\)

    r99t drawIC.cxx\(\"combined-difference.txt\"\)

    
    
    conddb_dumper -O EcalIntercalibConstants -t EcalIntercalibConstants_eopPNEB_etaScalePNEE_v5_RunFonly    -c frontier://FrontierPrep/CMS_CONDITIONS
    conddb_dumper -O EcalIntercalibConstants -t EcalIntercalibConstants_eopPNEB_etaScalePNEE_v5_RunFonly    -d frontier://FrontierPrep/CMS_CONDITIONS
    conddb_dumper -O EcalIntercalibConstants -t EcalIntercalibConstants_eopPNEB_etaScalePNEE_v6       

    conddb_dumper -O EcalIntercalibConstants -t EcalIntercalibConstants_Run1_Run2_V05_offline       

    
    
    -EB: EcalIntercalibConstants_eopPNEB_etaScalePNEE_v5_RunFonly
    -EE: EcalIntercalibConstants_eopPNEB_etaScalePNEE_v6
    

    
    
    data_EcalIntercalibConstants_eopPNEB_etaScalePNEE_v5_RunFonly/dump_EcalIntercalibConstants__since_00306705_till_00306708.dat
    data_EcalIntercalibConstants_eopPNEB_etaScalePNEE_v5_RunFonly/dump_EcalIntercalibConstants__since_00306705_till_00306708.dat
    
    r99t differenceIC.cxx\(\"data_EcalIntercalibConstants_eopPNEB_etaScalePNEE_v5_RunFonly/dump_EcalIntercalibConstants__since_00306705_till_00306708.dat\",\"data_EcalIntercalibConstants_eopPNEB_etaScalePNEE_v5_RunFonly/dump_EcalIntercalibConstants__since_00306705_till_00306708.dat\",\"combined-difference-00306705_till_00306708.txt\"\)

    r99t drawIC.cxx\(\"combined-difference-00306705_till_00306708.txt\",1,-0.2,0.2\)
    
    
    
    
    