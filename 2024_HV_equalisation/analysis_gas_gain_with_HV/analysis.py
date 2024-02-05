import ROOT
import pandas as pd
import matplotlib.pyplot as plt
import math
import numpy as np
import matplotlib.patches as patches
# This is the shell which print things
class Gas_gain_HV:
    
    def __init__(self, chamber, input_file, output_path):
        # Initialise this to use later
        self.str_rhid=""
        self.input_file = input_file
        self.chamber = chamber
        self.test = None
        self.data = None
        self.hist = None
        self.bin_edges =  None 
        self.output_path = output_path
    def decode_rhid(self,rhid):
        endcap = rhid // 1000000
        if(endcap==1) : 
            endcap_string='plus'
        if(endcap==2) : 
            endcap_string='minus'
            
        rhid %= 1000000

        station = rhid // 100000
        rhid %= 100000

        ring = rhid // 10000
        rhid %= 10000

        chamber_number = rhid // 100
        rhid %= 100

        layer = rhid // 10
        rhid %= 10
  
        hv_channel = rhid
        
        if(self.chamber=="ME11a" or self.chamber=="ME11b"):
            str_rhid = "ME"+ endcap_string + str(station) +  str(ring) + "_chamber_"+str(chamber_number)+"_layer"+str(layer)
        else:
            str_rhid = "ME"+ endcap_string + str(station) +  str(ring) + "_chamber_"+str(chamber_number)+"_layer"+str(layer)+"_HV_"+str(hv_channel)

        return str_rhid
   

    def remove_two_days_oct(self):
        # 26 Oct 2022
        t1 = 1666742400
        # 28 Oct 2022
        t2 = 1666915200
        filtered_df = self.data[~((self.data['_timesecond'] >= t1) & (self.data['_timesecond'] < t2))]
        self.data = filtered_df

        print("initial row ", self.data.iloc[1])
#        file_output_tmp = open("tmp_ME11b.csv","w")
#        self.data.to_csv(file_output_tmp, sep="\t", index=False)

    def read_dataframe(self, test):
        self.test = test
        if(test==True) : 
            self.data = pd.read_csv("ME11b_full_data_old.txt",sep='\t', nrows=100000)
        else :
            self.data = pd.read_csv(self.input_file,sep='\t')
        print(self.data)

    def HV_gas_gain(self):
        # go over rows of same rhid and make a histogram for similar rhid, to just go over 1 or 2 ids
        i=0
        #self.test=True
        for rhid, group in self.data.groupby('_rhid'):
            HV_list = []
            charge_list = []
            rhid_list = []
            for idx, row in group.iterrows():
                if(int(row['_HV'])==0.0 or row['_rhsumQ_RAW']>4100.0 or row['_rhsumQ_RAW']<50.0):
                    #print("yes")
                    continue
                rhid_string = self.decode_rhid(int(row['_rhid']))
                rhid_list.append(int(row['_rhid']))
                #print(rhid_string, "\t", int(row['_rhid']), " HV ",row['_HV'], " charge ", row['_rhsumQ_RAW'])
                HV_list.append(int(row['_HV']))
                charge_list.append(row['_rhsumQ_RAW'])
            
            if(self.test==True) : 
                if(i<=3):
                    self.plot_charge_HV(HV_list,charge_list, rhid_string)
                    self.find_mean_HV(HV_list,charge_list, rhid_string)
                    i=i+1
                if(i>3):
                    break
            else:
                self.plot_charge_HV(HV_list,charge_list, rhid_string)
                self.find_mean_HV(HV_list,charge_list, rhid_string)


    def plot_charge_HV(self, HV_list, charge_list, rhid_string):
        plt.figure()
        plt.scatter(HV_list, charge_list, color='blue', s=7)
        plt.title(f"{rhid_string}")
        plt.xlabel("HV")
        plt.ylabel("charge")
        plt.savefig(f"{self.output_path}charge_plots/charge_distribution_{rhid_string}.pdf")

        up_number = math.ceil(np.array(HV_list).max()) 
        low_number =  math.floor(np.array(HV_list).min())
        range_diff= math.ceil(np.array(HV_list).max()) -math.floor(np.array(HV_list).min())
        print("high" ,math.ceil(np.array(HV_list).max()))
        print("low ",math.floor(np.array(HV_list).min()))

        print(" number of bins = ", range_diff)
        #num_bins = range_diff/10+ range_diff%10
        bins = np.linspace(low_number, up_number,num=range_diff+1)

        hist, bin_edges = np.histogram(HV_list, bins= bins)
        plt.figure(figsize=(10, 6))
        plt.bar(bin_edges[:-1], hist, width=np.diff(bin_edges), edgecolor="black", bottom=True)
        plt.xlabel("HV")
        plt.ylabel("Number of Entries")
        plt.title(f"Number of Entries in each HV bin : {rhid_string}")
        #plt.xticks(bins)
        plt.savefig(f"{self.output_path}charge_entry_plots/charge_entries_{rhid_string}.pdf")
        plt.figure()
        # Assign each HV value to a bin
        #bin_indices = np.digitize(np.array(HV_list), bins)
        #print(bin_indices)
        #plt.figure(figsize=(10, 6))
        #HV_list_array=np.array(HV_list)
        #charge_list_array=np.array(charge_list)
        #for i in range(1, len(bins)):
        #    filtered_indices = bin_indices == i
        #    plt.scatter(HV_list_array[filtered_indices], charge_list_array[filtered_indices], label=f'Bin {i}')
        #    
        #plt.title(f"Scatter plot charge vs HV : {rhid_string}")
        #plt.xlabel("HV")
        #plt.ylabel("Charge")
        #plt.savefig(f"{self.output_path}charge_entry_plots/scattered_{rhid_string}.pdf")
        
        max_bin_index = np.argmax(hist)
        # Get the bin range (edges) for the bin with the maximum entries
        max_bin_range = (bin_edges[max_bin_index], bin_edges[max_bin_index + 1])
        max_bin_value = hist[max_bin_index]

        print(" max bin and value for ", rhid_string, " HV ", max_bin_value, " range ", max_bin_range)

        self.max_bin_low_edge = bin_edges[max_bin_index]
        self.max_bin_up_edge = bin_edges[max_bin_index+1]
        
        #colors = plt.cm.jet(np.linspace(0, 1, len(bins)))
        #for i in range(len(bins)-1):
        #    bin_df = df[(df['HV'] >= bins[i]) & (df['HV'] < bins[i+1])]
        #    plt.scatter(bin_df['HV'], bin_df['Charge'], color=colors[i], label=f'Bin {i+1}')
        #    plt.xlabel('HV')
        #    plt.ylabel('Charge')
        #    plt.title('charge vs HV with Binned Colors')
        #    plt.legend()
        #    plt.show()

    def find_mean_HV(self, HV_list, charge_list, rhid_string):
        mean_list= []
        mean_error_list = []
        HV_new_list = []
        hv_values_list_float = [self.max_bin_low_edge + i for i in range(-5, 2)]
        hv_values_list = [int(x) for x in hv_values_list_float]
        print(hv_values_list)

        #print(" HV list", HV_list)
        #if(self.chamber == "ME11a" or self.chamber =="ME11b"):
        #    #hv_values_list = [2880,2885,2886, 2887, 2889, 2900, 2905]  
        #    hv_values_list_float = [self.max_bin_low_edge + i for i in range(-5, 2)]

        #else:
        #    hv_values_list = [self.max_bin_low_edge + i for i in range(-5, 2)]
        #    #hv_values_list = [3580, 3585, 3590, 3592, 3594, 3596, 3598, 3600, 3605]  
        for i, HV_value in enumerate(hv_values_list):
            if i<len(hv_values_list)-1: 
                hv_low = HV_value
                hv_high =hv_values_list[i+1]
            else : 
                hv_low = HV_value
                hv_high = hv_values_list[i]+1
            filtered_charge = [charge for hv, charge in zip(HV_list, charge_list) if hv_low <= hv < hv_high]
            #print(f"Charge values for HV in the range ({hv_low}, {hv_high}): {filtered_charge}")

            hist_counts, _ = np.histogram(filtered_charge, bins=50)
            plt.figure()
            plt.hist(filtered_charge, bins=50, alpha=0.6, color='b')
            plt.title(f"{rhid_string} : {hv_low} <= HV < {hv_high}")
#            plt.xtitle(' charge ')
#            plt.ytitle(' n events')
            #plt.savefig(f"{self.output_path}HV_bins_plots/histogram_{hv_low}_HV_{hv_high}_{rhid_string}.pdf")
            plt.close()
            mean, mean_error = self.trimmed_mean(filtered_charge,hv_low, hv_high, rhid_string)
            hv_middle = (hv_low+hv_high)/2
            mean_list.append(mean)
            mean_error_list.append(mean_error)
            HV_new_list.append(hv_middle)

        # Plot mean and HV
        
        filtered_HV = [HV_value1 for HV_value1, mean_value1 in zip(HV_new_list, mean_list) if mean_value1 != 0]
        filtered_mean = [mean_value1 for mean_value1 in mean_list if mean_value1 != 0]
        filtered_mean_error = [mean_value1_error for mean_value1, mean_value1_error in zip(mean_list,mean_error_list) if mean_value1 != 0]
        

        print(" MEan list ", mean_list)
        print(" MEan error list ", mean_error_list)
        print(" HV list ", HV_new_list)
        plt.figure()
        #plt.plot(HV_new_list,mean_list,color='b')
        plt.axvline(x=self.max_bin_low_edge+0.5, color='r', linestyle='--')
        plt.plot(filtered_HV, filtered_mean,'o-',  color='b', markersize=5)
        plt.ylim(200,500)
        plt.errorbar(filtered_HV, filtered_mean, yerr=filtered_mean_error, fmt='o', color='b', markersize=5)
        plt.title(f" Gas gain with HV : {rhid_string}")
        plt.xlabel(" HV ")
        plt.ylabel(" Gas gain ")
        plt.savefig(f"{self.output_path}mean_plots/Mean_{rhid_string}.pdf")
    
    def trimmed_mean(self,charge_list,hv_low, hv_high, rhid_string):
        # Only evaluated trimmed mean for those histograms in which there are 50 entries
        if(len(charge_list) <=40): 
            return 0,0
        bin_edges = np.arange(start=1, stop=4100, step=2)
        hist, _ = np.histogram(charge_list, bins=bin_edges)
	
	# Calculate the cumulative distribution
        cumulative = np.cumsum(hist)
        print(cumulative)
        # Find the total number of entries
        total_entries = cumulative[-1]
        
        # Find the bin where the cumulative distribution reaches 70% of the total
        cutoff_index = np.where(cumulative >= total_entries * 0.7)[0][0]
        cutoff_value = bin_edges[cutoff_index + 1]

        bin_width = 1  # Set your bin width
        # Calculate bin centers
        bin_centers = (bin_edges[:-1] + bin_edges[1:]) / 2
        
        # Your specified cutoff value
        x_cutoff = cutoff_value  # Replace with your cutoff value
        
        # Calculate weighted sum and total count up to the cutoff
        weighted_sum = 0
        total_count = 0

        for center, count in zip(bin_centers, hist):
            if center <= x_cutoff:
                weighted_sum += center * count
                total_count += count
            else:
                break

        weighted_sum_square = 0
        

        # Calculate the mean up to the cutoff
        mean_up_to_cutoff = weighted_sum / total_count if total_count > 0 else None
 
        if(total_count >0) : 
            for center, count in zip(bin_centers, hist):
                if center <= x_cutoff:
                    weighted_sum_square += count * ((center - mean_up_to_cutoff) **2)
                else:
                    break
            variance = weighted_sum_square/total_count if total_count >0 else None
            mean_error = np.sqrt(variance)/np.sqrt(total_count) if total_count>0  else None

    
        #variance = np.sum(filtered_hist * (filtered_centers - weighted_mean)**2) / np.sum(filtered_hist)
        # Calculate the standard error of the mean
        #std_error_mean = np.sqrt(variance / np.sum(filtered_hist))
        #weighted_mean = np.sum(filtered_centers * filtered_hist) / np.sum(filtered_hist)

        #mean_error = weighted_sum / total_count if total_count > 0 else None
        plt.figure() 
        # Plot the histogram
        plt.hist(charge_list, bins=bin_edges, alpha=0.6, color='g')
        
        # Highlight the area of the histogram where 70% of the entries lie
        plt.hist(charge_list, bins=bin_edges, alpha=0.6, color='b', range=(np.min(charge_list), cutoff_value))
        
        # Optionally, add a line and text annotation for the cutoff
        plt.axvline(cutoff_value, color='r', linestyle='dashed', linewidth=2)
        plt.text(cutoff_value, plt.ylim()[1]*0.9, f'70% cutoff: {cutoff_value:.2f}', color='r')
        # Add titles and labels
        plt.title(f"{rhid_string} : {hv_low} <= HV < {hv_high}")
        plt.xlabel('HV')
        plt.ylabel('Raw charge')
        plt.text(0.95, 0.95, f'Mean: {mean_up_to_cutoff:.2f} \n Variance : {variance:.2f} \nMean error : {mean_error:.2f} \nentries_trimmed_mean : {total_count} \nTotal_entries:{total_entries}', transform=plt.gca().transAxes,
                horizontalalignment='right', verticalalignment='top',
                bbox=dict(facecolor='white', alpha=0.5))
        #rect = patches.Rectangle((1, 20), 2, 5, linewidth=2, edgecolor='r', facecolor='none')
        #plt.gca().add_patch(rect)
        #plt.text(1.5, 22, f'Value: {mean_up_to_cutoff:.2f}', horizontalalignment='center', verticalalignment='center')

        # Show the plot
        plt.savefig(f"{self.output_path}trimmed_plots/trimmed_dist_{hv_low}_HV_{hv_high}_{rhid_string}.pdf")
        plt.close() 

        return mean_up_to_cutoff, mean_error
        #return (mean_up_to_cutoff, mean_error)
#print(f"Mean up to {x_cutoff}: {mean_up_to_cutoff}")
if __name__=='__main__':
    chamber = "ME21HV1" 
    #input_file = "ME11b_full_data_old.txt"
    input_path = "input_HV_files/"
    input_file = f"{input_path}{chamber}_full_data.csv"
    output_path = "./output_plots_ME21HV1/"
    obj = Gas_gain_HV(chamber, input_file, output_path)
    obj.read_dataframe(test=True)
    obj.remove_two_days_oct()
    obj.HV_gas_gain()
