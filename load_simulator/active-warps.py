#!/usr/bin/env python

import sys
import os # OS stuff
import glob # pathname stuff
import csv # CSV
import re # Regex
from pprint import pprint # Pretty Print

import pandas as pd
import numpy as np

MAXREGS = 65536
MAXBLOCKS = 16
WARPSIZE = 32
NUMWARPS = 64

def get_num(x):
    return float(''.join(ele for ele in x if ele.isdigit() or ele == '.'))

def calc_th(x):
    # x = max(16, x - x%16)
    return float(min(1, float( float(MAXREGS/(x*WARPSIZE))/NUMWARPS )))

def get_reg(filename, name):
    with open(filename, 'rb') as f:
        data = csv.DictReader(f)
        for row in data:
            if name in row['Name']:
                return row['Registers Per Thread']
    
    print "Not found"

def active ( profl, rcsvs, apps, batch, in_dim, out_dim ):
    outname = 'active.csv'
    writer = csv.writer(open(outname, 'a'))
    if os.stat(outname).st_size == 0:
      writer.writerow(['app', 'batch', 'in_dim', 'out_dim','achieved','theoretical', 'ratio'])

    # get average for metric
    for app in apps:
        agg = []
        for idx, filename in enumerate(profl):
            if not re.search(app, filename): 
                continue

            # batch = get_num(re.findall(r'\d+', filename))
            #batch = 1
            dur = 0
            occ = []
            ach_occ = []
            th_occs = []
            with open(filename, 'rb') as f:
                data = csv.DictReader(f)
                for row in data:
                    if row["Metric Name"] == 'achieved_occupancy':
                        regs = get_reg(rcsvs[idx], row['Name'])
                        th_occ = calc_th(int(regs))
                        avg = get_num(row["Avg_x"])
                        if re.search("%", row["Avg_x"]): # if value is 0-100
                            avg = get_num(row["Avg_x"])/100
                        ach_occ.append(float(avg)*float(row["Time(%)"]))
                        th_occs.append(float(th_occ)*float(row["Time(%)"]))
                        occ.append(float(avg/th_occ)*float(row["Time(%)"]))
                        dur += float(row["Time(%)"])
            agg.append((int(batch), int(in_dim),int(out_dim), sum(ach_occ)/float(dur), sum(th_occs)/float(dur), sum(occ)/float(dur)))
        agg.sort()
        for rat in agg:
            writer.writerow([app, rat[0], rat[1], rat[2], rat[3], rat[4], rat[5]])
                
# arg 1 = list of csvs
# arg 2 = load simulator input dimension
# arg 3 = load simulator output dimension
def main( args ):
    # apps = ['imc', 'asr']
    batch = args[2]
    in_dim = args[3]
    out_dim = args[4]

    apps = ['load']

    # collect csvs
    csvs = [ line.strip() for line in open(args[1]) ] # rm /n
    prof = "metrics_"
    dur = "summary_"
    regs = "trace_"
    profl = []
    durl = []
    regl = []
    for i in csvs:
        p = re.search(prof, i)
        d = re.search(dur, i)
        r = re.search(regs, i)
        if p:
            profl.append(i)
        elif d:
            durl.append(i)
        elif r:
            regl.append(i)
    
    profl.sort()
    durl.sort()
    regl.sort()
    NUM_FIELDS = 8
    # merge profiling and timing csvs
    for p,d in zip(profl,durl):
        p_csv = pd.read_csv(p)
        if len(p_csv.columns) > NUM_FIELDS:
            continue
        d_csv = pd.read_csv(d)
        p_csv = p_csv.merge(d_csv, left_on='Kernel', right_on='Name', how='outer')
        p_csv.to_csv(p, sep=",")

    active(profl, regl, apps, batch, in_dim, out_dim)

    return 0

if __name__=='__main__':
    sys.exit(main(sys.argv))
