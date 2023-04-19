import time
import os
import subprocess
#chambers=["ME11b","ME12HV1", "ME12HV2","ME12HV3", "ME13HV1","ME13HV2","ME13HV3","ME21HV1","ME31HV2","ME31HV3","ME41HV1"]

chambers=["ME21HV2","ME21HV3", "ME31HV1","ME22HV1", "ME22HV2","ME22HV3","ME22HV4", "ME22HV5","ME32HV1", "ME32HV2","ME32HV3","ME32HV4", "ME32HV5","ME42HV1", "ME42HV2","ME42HV3","ME42HV4", "ME42HV5"]
#chambers=["ME11a", "ME11b", "ME12HV1","ME21HV1", "ME13HV3"]
for chamber_name in chambers:
	print("chamber name ",chamber_name)
	subprocess.call("sbatch job_{}.batch".format(chamber_name),shell=True)
	time.sleep(30)
