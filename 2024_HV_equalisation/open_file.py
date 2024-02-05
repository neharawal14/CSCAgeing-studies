import time
import ROOT
#import RDataFrame
#from RDataFrame import Snapshot
import pandas as pd
import matplotlib.dates as mdates
import numpy as np
import matplotlib.pyplot as plt
from datetime import datetime
import calendar
from array import array
st_time = time.time()


class HV_equalisation:
    #Initialising the chamber name and number of events you want to test program
    def __init__(self, chamber,HV_chamber, output_path, test_events, test):
        print(" Initializing the class")
        self.chamber = chamber
        self.HV_chamber = HV_chamber
        self.test_events = test_events
        self.data_HV = None    
        self.test = test
        self.output_path = output_path
        self.output_file = open(output_path+"error_"+chamber+".txt","w")
        self.output_file.write("here")

    # Program to read the root file and store it in a dataframe
    def read_root_file(self, input_string):
        file = ROOT.TFile(input_string, "READ") 
        ##
        ### Access the tree. Replace 'your_tree_name' with the name of your tree
        tree = file.Get("tree")
        i=0
        ## Prepare a dictionary to hold your data
        data = {}
        ## Initialize dictionary with lists for branches that I need
        list_branch = ['_rhid', '_timesecond','_HV', '_rhsumQ_RAW']
        #All the branches
        #list_branch =['_passZmumusel', '_eventNb', '_runNb', '_lumiBlock', '_rhid', '_stationring', '_rhsumQ', '_rhsumQ_RAW', '_HV', '_pressure', '_temperature', '_instlumi', '_integratelumi', '_timesecond', '_n_PV', '_bunchcrossing', '_etamuon', '_phimuon', '_ptmuon', 'z_pt', 'z_eta', 'z_phi', 'z_mass']
        for branche in list_branch:
            #branch_name = branch.GetName()
            branch_name = branche
            data[branch_name] = []
        for event in tree:
        ##    print("entry inside")
            if(i==self.test_events and self.test=='true') :
                break
    
        # I tried this, since the values getting stored in my root file are of the same type float
        #    data['_passZmumusel'].append(tree._passZmumusel)
        #    data['_eventNb'].append(tree._eventNb)
        #    data['_runNb'].append(tree._runNb)
        #    data['_lumiBlock'].append(tree._lumiBlock)
        #    data['_rhid'].append(tree._rhid)
        #    data['_stationring'].append(tree._stationring)
        #    data['_rhsumQ'].append(tree._rhsumQ)
        #    data['_rhsumQ_RAW'].append(tree._rhsumQ_RAW)
        #    data['_HV'].append(tree._HV)
        #    data['_pressure'].append(tree._pressure)
        #    data['_temperature'].append(tree._temperature)
        #    data['_instlumi'].append(tree._instlumi)
        #    data['_integratelumi'].append(tree._integratelumi)
        #    data['_timesecond'].append(tree._timesecond)
        #    data['_n_PV'].append(tree._n_PV)
        #    data['_bunchcrossing'].append(tree._bunchcrossing)
        #    data['_etamuon'].append(tree._etamuon)
        #    data['_phimuon'].append(tree._phimuon)
        #    data['_ptmuon'].append(tree._ptmuon)
        #    data['z_pt'].append(tree.z_pt)
        #    data['z_eta'].append(tree.z_eta)
        #    data['z_phi'].append(tree.z_phi)
        #    data['z_mass'].append(tree.z_mass)
        #    i=i+1
            for branch in list_branch: 
                #print("event in tree ", event) 
                branch_name = branch
                data[branch_name].append(getattr(event, branch_name))
            i=i+1

        self.df=pd.DataFrame(data)
        print(self.df)
        file.Close()
 
    def splitting_plus_minus(self):
        self.df['_rhid'] = self.df['_rhid'].astype(str)
        # Split the DataFrame into two based on the first character of 'rhid'
        self.mask_plus = self.df['_rhid'].str.startswith('1')
        self.mask_minus = self.df['_rhid'].str.startswith('2')
        self.df['_rhid'] = self.df['_rhid'].astype(int)
        self.df['_HV'] = self.df['_HV'].round().astype(int)

     
    def writing_output(self):
        output_root_filename = self.chamber + '_output.root'
        f_output = ROOT.TFile(output_root_filename , 'RECREATE')
        tree = ROOT.TTree('tree', 'Example Tree')
#        self.df.Snapshot(tree, output_root_filename, {"_HV", "_rhid", "_timesecond","_rhsumQ_RAW"});

       #_passZmumusel = array('f',[0])
        #tree.Branch('_passZmumusel', _passZmumusel, '_passZmumusel/F')
        #_eventNb = array('f',[0])
        #tree.Branch('_eventNb', _eventNb, '_eventNb/F')
        #_runNb = array('f',[0])
        #tree.Branch('_runNb', _runNb, '_runNb/F')
        #_lumiBlock = array('f',[0])
        #tree.Branch('_lumiBlock', _lumiBlock, '_lumiBlock/F')
        ##_rhid = array('i',[0])
        ##tree.Branch('_rhid', _rhid, '_rhid/L')
        ###_stationring = array('f',[0])
        ###tree.Branch('_stationring', _stationring, '_stationring/F')
        ###_rhsumQ = array('f',[0])
        ###tree.Branch('_rhsumQ', _rhsumQ, '_rhsumQ/F')
        ###_rhsumQ_RAW = array('f',[0])
        ##tree.Branch('_rhsumQ_RAW', _rhsumQ_RAW, '_rhsumQ_RAW/F')
        ##_HV = array('f',[0])
        ##tree.Branch('_HV', _HV, '_HV/F')
        ##_pressure = array('f',[0])
        ###tree.Branch('_pressure', _pressure, '_pressure/F')
        ###_temperature = array('f',[0])
        ###tree.Branch('_temperature', _temperature, '_temperature/F')
        ###_instlumi = array('f',[0])
        ###tree.Branch('_instlumi', _instlumi, '_instlumi/F')
        ###_integratelumi = array('f',[0])
        ###tree.Branch('_integratelumi', _integratelumi, '_integratelumi/F')
        ##_timesecond = array('f',[0])
        ##tree.Branch('_timesecond', _timesecond, '_timesecond/F')
        #_n_PV = array('f',[0])
        #tree.Branch('_n_PV', _n_PV, '_n_PV/F')
        #_bunchcrossing = array('f',[0])
        #tree.Branch('_bunchcrossing', _bunchcrossing, '_bunchcrossing/F')
        #_etamuon = array('f',[0])
        #tree.Branch('_etamuon', _etamuon, '_etamuon/F')
        #_phimuon = array('f',[0])
        #tree.Branch('_phimuon', _phimuon, '_phimuon/F')
        #_ptmuon = array('f',[0])
        #tree.Branch('_ptmuon', _ptmuon, '_ptmuon/F')
        #z_pt = array('f',[0])
        #tree.Branch('z_pt', z_pt, 'z_pt/F')
        #z_eta = array('f',[0])
        #tree.Branch('z_eta', z_eta, 'z_eta/F')
        #z_phi = array('f',[0])
        #tree.Branch('z_phi', z_phi, 'z_phi/F')
        #z_mass = array('f',[0])
        #tree.Branch('z_mass', z_mass, 'z_mass/F')

#    for index, row in df.iterrows():
#        print(row['_rhsumQ'])
#        #'', '_eventNb', '_runNb', '_lumiBlock', '_rhid', '_stationring', '_rhsumQ', '_rhsumQ_RAW', '_HV', '_pressure', '_temperature', '_instlumi', '_integratelumi', '_timesecond', '_n_PV', '_bunchcrossing', '_etamuon', '_phimuon', '_ptmuon', 'z_pt', 'z_eta', 'z_phi', 'z_mass']
#    for index, row in df.iterrows():
#           _passZmumusel[0] = row['_passZmumusel']
#           _eventNb[0] = row['_eventNb']
#           _runNb[0] = row['_runNb']
#           _lumiBlock[0] = row['_lumiBlock']
#           _rhid[0] = row['_rhid']
#           _stationring[0] = row['_stationring']
#           _rhsumQ[0] = row['_rhsumQ']
#           _rhsumQ_RAW[0] = row['_rhsumQ_RAW']
#           _HV[0] = row['_HV']
#           _pressure[0] = row['_pressure']
#           _temperature[0] = row['_temperature']
#           _instlumi[0] = row['_instlumi']
#           _integratelumi[0] = row['_integratelumi']
#           _timesecond[0] = row['_timesecond']
#           _n_PV[0] = row['_n_PV']
#           _bunchcrossing[0] = row['_bunchcrossing']
#           _etamuon[0] = row['_etamuon']
#           _phimuon[0] = row['_phimuon']
#           _ptmuon[0] = row['_ptmuon']
#           z_pt[0] = row['z_pt']
#           z_eta[0] = row['z_eta']
#           z_phi[0] = row['z_phi']
#           z_mass[0] = row['z_mass']
#           tree.Fill()


        # to store the branches as dictionary
        # I could not write a better program to automate things, since the data types of all branches in root file is different
        values = {}
        for col in self.df.columns:
            values[col] = array('f', [0])  # Float
            tree.Branch(col, values[col], f'{col}/F')
        for index, row in self.df.iterrows():
            for col in self.df.columns: 
                values[col][0] = row[col]
                
            tree.Fill()
        tree.Show(1)
        f_output.Write()
        f_output.Close()

    def reading_HV_values(self):
        # My HV values file name is 'ME11_plus_new.txt'
        HV_file_path = "input_HV_information_files/"
        HV_file_name = HV_file_path+self.input_HV_file 
        print("HV file name ", HV_file_name)
        self.data_HV= pd.read_csv(HV_file_name,sep="\t")
   
        # Convert start time and end time in datetime
        self.data_HV['Start time'] = pd.to_datetime(self.data_HV['Start time'])
        self.data_HV['End time'] = pd.to_datetime(self.data_HV['End time'])
        self.data_HV['Start time'] = pd.to_datetime(self.data_HV['Start time'], utc=True)
        self.data_HV['End time'] = pd.to_datetime(self.data_HV['End time'], utc=True)
        
        self.data_HV['start_time_epoch'] = self.data_HV['Start time'].apply(lambda x: calendar.timegm(x.timetuple()))
        self.data_HV['end_time_epoch'] = self.data_HV['End time'].apply(lambda x: calendar.timegm(x.timetuple()))

# Finding the correct HV value for a entry and update our dataframe
    def finding_matched_HV(self):
        # Create a output text file to store the error values while the evaluation
        list_HV =[]
        for index, row in self.df[self.mask].iterrows():
            #print(" row here ", row['rhid'])
            match = self.data_HV[(self.data_HV['rhid'] == row['_rhid']) & (self.data_HV['start_time_epoch'] <= row['_timesecond']) & (self.data_HV['end_time_epoch'] >= row['_timesecond'])]

            if match.empty: 
                # Since on e lumisection is like 40, 50 s . So sometimes though in my list run has ended, but it will actually end after a minute
                match = self.data_HV[(self.data_HV['rhid'] == row['_rhid']) & (self.data_HV['start_time_epoch'] -80 <= row['_timesecond']) & (self.data_HV['end_time_epoch']+60 >= row['_timesecond'])]
                if match.empty: 
                    if index in self.df.index and self.mask[index]:
                        self.df.at[index, '_HV'] =  0
                        list_HV.append(0)
                        match.to_csv(self.output_file, sep="\t", index=False)
                        output_str = " row "+str(row['_rhid'])+ " time "+ str(row['_timesecond'])+"\n"
                        self.output_file.write(output_str)

            else :
                #print(match['HV value'])
                hv_value = match['HV value'].iloc[0]
                #print("data HV rhid ",hv_value)
                if index in self.df.index and self.mask[index]:
                    #df.at[index, '_HV'] =  int(match['HV value'].item(0))
                    self.df.at[index, '_HV'] =  hv_value
                    #list_HV.append(int(match['HV value'].item(0)))
                    #list_HV.append(hv_value)

        print("list :  ",list_HV)
    
    def setting_charge_chamber(self, filename, charge):
        self.charge =  charge
        if(self.charge=="plus"):
            self.mask = self.mask_plus
        if(self.charge=="minus"):
            self.mask = self.mask_minus
        self.input_HV_file = HV_chamber+filename
        print("input file here", self.input_HV_file)

    def write_output(self):
        #print("new modified full", df)

        #self.df['_HV'] = self.df['_HV'].astype(int)
        #self.df['_rhid'] = self.df['_rhid'].astype(int)
        #self.df['_rhsumQ_RAW'] = self.df['_rhsumQ_RAW'].astype(float) 
        #self.df['_timesecond'] = self.df['_timesecond'].astype('uint64') 
        output_file_name = output_path+self.chamber+"_full_data.csv"
        file_output = open(output_file_name,"w")
        self.df.to_csv(file_output, sep="\t", index=False) 


        #_passZmumusel = array('f',[0])
        #tree.Branch('_passZmumusel', _passZmumusel, '_passZmumusel/F')
        #_eventNb = array('f',[0])
        #tree.Branch('_eventNb', _eventNb, '_eventNb/F')
        #_runNb = array('f',[0])
        #tree.Branch('_runNb', _runNb, '_runNb/F')
        #_lumiBlock = array('f',[0])
        #tree.Branch('_lumiBlock', _lumiBlock, '_lumiBlock/F')
        #_rhid = array('f',[0])
        #tree.Branch('_rhid', _rhid, '_rhid/F')
        #_stationring = array('f',[0])
        #tree.Branch('_stationring', _stationring, '_stationring/F')
        #_rhsumQ = array('f',[0])
        #tree.Branch('_rhsumQ', _rhsumQ, '_rhsumQ/F')
        #_rhsumQ_RAW = array('f',[0])
        #tree.Branch('_rhsumQ_RAW', _rhsumQ_RAW, '_rhsumQ_RAW/F')
        #_HV = array('f',[0])
        #tree.Branch('_HV', _HV, '_HV/F')
        #_pressure = array('f',[0])
        #tree.Branch('_pressure', _pressure, '_pressure/F')
        #_temperature = array('f',[0])
        #tree.Branch('_temperature', _temperature, '_temperature/F')
        #_instlumi = array('f',[0])
        #tree.Branch('_instlumi', _instlumi, '_instlumi/F')
        #_integratelumi = array('f',[0])
        #tree.Branch('_integratelumi', _integratelumi, '_integratelumi/F')
        #_timesecond = array('f',[0])
        #tree.Branch('_timesecond', _timesecond, '_timesecond/F')
        #_n_PV = array('f',[0])
        #tree.Branch('_n_PV', _n_PV, '_n_PV/F')
        #_bunchcrossing = array('f',[0])
        #tree.Branch('_bunchcrossing', _bunchcrossing, '_bunchcrossing/F')
        #_etamuon = array('f',[0])
        #tree.Branch('_etamuon', _etamuon, '_etamuon/F')
        #_phimuon = array('f',[0])
        #tree.Branch('_phimuon', _phimuon, '_phimuon/F')
        #_ptmuon = array('f',[0])
        #tree.Branch('_ptmuon', _ptmuon, '_ptmuon/F')
        #z_pt = array('f',[0])
        #tree.Branch('z_pt', z_pt, 'z_pt/F')
        #z_eta = array('f',[0])
        #tree.Branch('z_eta', z_eta, 'z_eta/F')
        #z_phi = array('f',[0])
        #tree.Branch('z_phi', z_phi, 'z_phi/F')
        #z_mass = array('f',[0])
        #tree.Branch('z_mass', z_mass, 'z_mass/F')

#    for index, row in df.iterrows():
#        print(row['_rhsumQ'])
#        #'', '_eventNb', '_runNb', '_lumiBlock', '_rhid', '_stationring', '_rhsumQ', '_rhsumQ_RAW', '_HV', '_pressure', '_temperature', '_instlumi', '_integratelumi', '_timesecond', '_n_PV', '_bunchcrossing', '_etamuon', '_phimuon', '_ptmuon', 'z_pt', 'z_eta', 'z_phi', 'z_mass']
#    for index, row in df.iterrows():
#           _passZmumusel[0] = row['_passZmumusel']
#           _eventNb[0] = row['_eventNb']
#           _runNb[0] = row['_runNb']
#           _lumiBlock[0] = row['_lumiBlock']
#           _rhid[0] = row['_rhid']
#           _stationring[0] = row['_stationring']
#           _rhsumQ[0] = row['_rhsumQ']
#           _rhsumQ_RAW[0] = row['_rhsumQ_RAW']
#           _HV[0] = row['_HV']
#           _pressure[0] = row['_pressure']
#           _temperature[0] = row['_temperature']
#           _instlumi[0] = row['_instlumi']
#           _integratelumi[0] = row['_integratelumi']
#           _timesecond[0] = row['_timesecond']
#           _n_PV[0] = row['_n_PV']
#           _bunchcrossing[0] = row['_bunchcrossing']
#           _etamuon[0] = row['_etamuon']
#           _phimuon[0] = row['_phimuon']
#           _ptmuon[0] = row['_ptmuon']
#           z_pt[0] = row['z_pt']
#           z_eta[0] = row['z_eta']
#           z_phi[0] = row['z_phi']
#           z_mass[0] = row['z_mass']
#           tree.Fill()

#df['_timesecond'] = pd.to_datetime(df['_timesecond'], utc=True)
#df['_timesecond_epoch'] = df['_timesecond'].apply(lambda x: calendar.timegm(x.timetuple()))
# Separate dataframe into plus and minus endcaps

if __name__ == "__main__":
# Read the input root file
    st_time = time.time()
    
    chamber = "ME11b"
    HV_chamber = "ME11b"
    input_path = "/cmsuf/data/store/user/t2/users/neha.rawal/CSCAgeing_2022/final_files_2022_new/2022_all/"
    output_path = "/cmsuf/data/store/user/t2/users/neha.rawal/CSCAgeing_2022/2024_HV_equalisation/generated_files/"
    input_file = f"{input_path}csc_output_2022_{chamber}_tree.root"

    obj = HV_equalisation(chamber, HV_chamber,output_path, 5000, test='false')
    # Read root file and initialise a data frame for it 
    obj.read_root_file(input_file)
    # Initialise the plus and minus mask for the data frame, since the root file contains event for both plus and minus endcap 
    obj.splitting_plus_minus()
    # For charge plus
    obj.setting_charge_chamber("_plus.txt", charge="plus")
    # Reading the corresponding HV information file for plus endcap, and store it in a dataframe
    obj.reading_HV_values()
    obj.finding_matched_HV()
    # For charge minus
    obj.setting_charge_chamber("_minus.txt", charge = "minus")
    obj.reading_HV_values()
    obj.finding_matched_HV()
   
    # To write the final dataframe in a text file
    obj.write_output()

    # To write the final dataframe in a root file for further analysis
    obj.writing_output()
    
    
    en_time = time.time()
    print(" start time ", st_time)
    print(" end time ", en_time)
    print(" diff time ", en_time-st_time)
#    data_HV_plus = pd.read_csv('./ME11_plus_new.txt',sep="\t")
#    data_HV_minus = pd.read_csv('./ME11_minus_new.txt',sep="\t")
#    
#    data_HV['Start time'] = pd.to_datetime(data_HV['Start time'])
#    data_HV['End time'] = pd.to_datetime(data_HV['End time'])
#    #table1 = pd.DataFrame({
#    #    '_rhid': [1110111,1110112, 1110111],
#    #    '_timesecond': ['2022-07-05 15:48:58', '2022-07-05 16:50:43', '2022-07-05 17:20:22']
#    #})
#    #table1['_timesecond'] = pd.to_datetime(table1['_timesecond'], utc=True)
#    #table1['_timesecond_epoch'] = table1['_timesecond'].apply(lambda x: calendar.timegm(x.timetuple()))
#    data_HV['Start time'] = pd.to_datetime(data_HV['Start time'], utc=True)
#    data_HV['End time'] = pd.to_datetime(data_HV['End time'], utc=True)
#    
#    data_HV['start_time_epoch'] = data_HV['Start time'].apply(lambda x: calendar.timegm(x.timetuple()))
#    data_HV['end_time_epoch'] = data_HV['End time'].apply(lambda x: calendar.timegm(x.timetuple()))
#    
#    data_HV_minus['Start time'] = pd.to_datetime(data_HV_minus['Start time'])
#    data_HV_minus['End time'] = pd.to_datetime(data_HV_minus['End time'])
#    #table1 = pd.DataFrame({
#    #    '_rhid': [1110111,1110112, 1110111],
#    #    '_timesecond': ['2022-07-05 15:48:58', '2022-07-05 16:50:43', '2022-07-05 17:20:22']
#    #})
#    #table1['_timesecond'] = pd.to_datetime(table1['_timesecond'], utc=True)
#    #table1['_timesecond_epoch'] = table1['_timesecond'].apply(lambda x: calendar.timegm(x.timetuple()))
#    data_HV_minus['Start time'] = pd.to_datetime(data_HV_minus['Start time'], utc=True)
#    data_HV_minus['End time'] = pd.to_datetime(data_HV_minus['End time'], utc=True)
#    
#    data_HV_minus['start_time_epoch'] = data_HV_minus['Start time'].apply(lambda x: calendar.timegm(x.timetuple()))
#    data_HV_minus['end_time_epoch'] = data_HV_minus['End time'].apply(lambda x: calendar.timegm(x.timetuple()))
#

# program to include the dataframe in a root file 
    #iterate over all columns of dataframe and store the output in branches
        #tree.Branch('_passZmumusel', _passZmumusel, '_passZmumusel/F'
        #' _eventNb ', ' _runNb ', ' _lumiBlock ', ' _rhid ', ' _stationring ', ' _rhsumQ ', ' _rhsumQ_RAW ', ' _HV ', ' _pressure ', ' _temperature ', ' _instlumi ', ' _integratelumi ', ' _timesecond ', ' _n_PV ', ' _bunchcrossing ', ' _etamuon ', ' _phimuon ', ' _ptmuon ', ' z_pt ', ' z_eta ', ' z_phi ',

#table1 = table1.assign(HV_value=list_HV['HV value'])
#print("new table1 ")
#print(table1)
##
##
##
##
###or column in 
