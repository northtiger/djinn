#!/usr/bin/env python

import csv 
import operator
import pandas as pd

df = pd.read_csv("active.csv")
df = df.sort('ratio')

df.to_csv("active-sorted.csv", index=False)
