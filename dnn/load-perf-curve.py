
import csv
import os
import re

import matplotlib.pyplot as plt
import matplotlib.cm as cmx
import matplotlib.colors as cl
from matplotlib import rcParams
from matplotlib.font_manager import FontProperties

import numpy as np

def color_maker(count, map='gnuplot2', min=0.100, max=0.900):
    assert(min >= 0.000 and max <= 1.000 and max > min)
    gran = 100000.0
    maker = cmx.ScalarMappable(norm=cl.Normalize(vmin=0, vmax=int(gran)),
                               cmap=plt.get_cmap(map))
    r = [min * gran]
    if count > 1:
        r = [min * gran + gran * x * (max - min) / float(count - 1) for x in range(0, count)]
        return [maker.to_rgba(t) for t in r]


apps=["imc", "dig", "face", "vgg", "asr", "pos", "ner", "chk"]
batch=512
procs=range(1,16)
dirname="server-load-timing"

for app in apps:
  layers = {}
  for p in procs:
    csvfile = "%s/%s-%d-%d-layer-timing-avg.csv" % (dirname, app, batch, p)
    with open(csvfile, 'rb') as f:
     data = csv.DictReader(f, delimiter=",", fieldnames=['layer', 'lat'])
     for row in data:
       if row['layer'] not in layers:
         layers[row['layer']] = [float(row['lat'])]
       else:
         layers[row['layer']].append(float(row['lat']))

  # plot for this app
  print app
    
  # plot for this app
  import matplotlib
  from matplotlib import pyplot as plt

  plt.rc('font', family='serif')
  plt.rc('font', size=15)
  plt.rc('legend', fontsize=15)

  fig,ax1 = plt.subplots()
  fig.set_size_inches(10,5)
  width = 0.8

  x_values = procs 

  colors = color_maker(len(layers), map="afmhot")
  idx=0
  for key,value in layers.iteritems():
    ax1.plot(x_values, value, linewidth=width, color=colors[idx], label=key)
    idx += 1

  ax1.set_ylabel("Latency(ms)")
  ax1.set_xticklabels(procs)
  ax1.legend(loc="upper left")

  import os
  figname = "-".join((app, 'server', 'load'))
  plt.savefig(figname+'.eps', bbox_inches="tight")
  os.popen('convert '+figname+'.eps ' +figname+'.png')

