#!/usr/bin/env python

import math
import subprocess, re, os, sys, csv

def shcmd(cmd):
    subprocess.call(cmd, shell=True)

def shcom(cmd):
    p = subprocess.Popen(cmd, shell=True, stdout=subprocess.PIPE)
    out = p.communicate()[0]
    return out

def main( args ):
    batch = args[1]
    in_dim = args[2]
    out_dim = args[3]
    NETCONF='load'
    NET=NETCONF + '.prototxt'
    
    # change input dimension
    cmd = './change-dim.sh %s %s %s' % (NET, 2, in_dim)
    shcom(cmd)
    
    # change batch size
    cmd = './change-dim.sh %s %s %s' % (NET, 1, batch)
    shcom(cmd)

    # change output dimension
    cmd = './change-entry.sh %s %s %s' % (NET, 'num_output', out_dim)
    shcom(cmd)
    
if __name__=='__main__':
  sys.exit(main(sys.argv))
