#!/bin/bash
#SBATCH --output=array_ME21HV1.out    # Standard output log
#SBATCH --error=array_ME21HV1.err    # Standard error log
#SBATCH --job-name=iteration_job             # Job name.
#SBATCH --mem=500mb             # RAM request on a node. Default is 2gb. per cpu request
#SBATCH --ntasks=1            # Number of requested cpus.
#SBATCH --cpus-per-task=1            # Number of requested cpus.
#SBATCH --time=00:10:00               # Time limit (hh:mm:ss).
#SBATCH --qos=avery-b 
#SBATCH --partition=hpg2-compute
#SBATCH --mail-user=neha.rawal@ufl.edu  # Get emailed the job status.
#SBATCH --mail-type=ALL              # Job status options: BEGIN, END, ALL, FAIL, NONE
# Define the range of iterations

# Put the code you want to run below:
pwd; hostname; date
python3 analysis.py
