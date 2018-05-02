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
    
    r99t differenceIC.cxx\(\"data_EcalIntercalibConstants_eopPNEB_etaScalePNEE_v5_RunFonly/dump_EcalIntercalibConstants__since_00306705_till_00306708.dat\",\"data_EcalIntercalibConstants_Run1_Run2_V05_offline/dump_EcalIntercalibConstants__since_00306705_till_00306708.dat\",\"combined-difference-00306705_till_00306708.txt\"\)

    r99t drawIC.cxx\(\"combined-difference-00306705_till_00306708.txt\",1,-0.002,0.002\)
    
    
    
    data_EcalIntercalibConstants_Run1_Run2_V05_offline/dump_EcalIntercalibConstants__since_00306705_till_00306708.dat
    data_EcalIntercalibConstants_eopPNEB_etaScalePNEE_v6/dump_EcalIntercalibConstants__since_00306705_till_00306708.dat
    
    r99t differenceIC.cxx\(\"data_EcalIntercalibConstants_Run1_Run2_V05_offline/dump_EcalIntercalibConstants__since_00306705_till_00306708.dat\",\"data_EcalIntercalibConstants_eopPNEB_etaScalePNEE_v6/dump_EcalIntercalibConstants__since_00306705_till_00306708.dat\",\"combined-difference-00306705_till_00306708_EE.txt\"\)

    r99t drawIC.cxx\(\"combined-difference-00306705_till_00306708_EE.txt\",1,-0.002,0.002\)

    

Compare MC tags for IC

    digi2raw
    EcalIntercalibConstantsMCRcd --> EcalIntercalibConstantsMC_digi_2011_V3_Bon_mc
    
    raw2reco
    EcalIntercalibConstantsRcd --> EcalIntercalibConstants_2011_V3_Bon_design_mc
    
    
    conddb_dumper -O EcalIntercalibConstants -t EcalIntercalibConstantsMC_digi_2011_V3_Bon_mc    -d frontier://FrontierPrep/CMS_CONDITIONS
    mv dump_EcalIntercalibConstants__since_00000001_till_18446744073709551615.dat     digi2raw.txt
    
    conddb_dumper -O EcalIntercalibConstants -t EcalIntercalibConstants_2011_V3_Bon_design_mc    -d frontier://FrontierPrep/CMS_CONDITIONS
    mv dump_EcalIntercalibConstants__since_00000001_till_18446744073709551615.dat     raw2reco.txt
    
    
    r99t scripts/differenceIC.cxx\(\"digi2raw.txt\",\"raw2reco.txt\",\"difference-MC.txt\"\)

    r99t scripts/drawIC.cxx\(\"difference-MC.txt\",1,-0.01,0.01\)


    


Dump IC vs time


    EcalIntercalibConstants_Run2017BCDEF_eopPNEB_etaScalePNEE_finalComb_EffLCcorr_HighEtaICs_EtaScale_v1
    
    
    conddb_dumper -O EcalIntercalibConstants -t EcalIntercalibConstants_Run2017BCDEF_eopPNEB_etaScalePNEE_finalComb_EffLCcorr_HighEtaICs_EtaScale_v1    -d frontier://FrontierPrep/CMS_CONDITIONS

    
    # 10th crystal
    ls /tmp/amassiro/data_flat/ | tr "_" " " | tr "." " " | awk '{print "echo -n \" "$4"     \" >> temp_10.txt ; head -n 10 /tmp/amassiro/data_flat/"$1"_"$2"__"$3"_"$4"_"$5"_"$6"."$7" | tail -n 1  >> temp_10.txt"}'
    
    cat temp_10.txt  | awk '{print $1 "  " $5}' > toplot_10.txt
    
    r99t plotVsTime.cxx\(\"\toplot_10.txt\"\)
    
    
    
Transform IC vs time into trees
    
    r99t DumpTree.cxx
    
    r99t dumpIC.root
    
    tree->Draw("value:iov_min","iphi==197 && ieta==-9", "")
    tree->Draw("value:iov_min","ieta==-9", "")
    
    tree->Draw("value:iov_min","ieta==-9", "colz")
        
    (iov_min==297046)
    
    r99t drawHistory.cxx
    
    
    
    
    
    
    
    

    
    
    