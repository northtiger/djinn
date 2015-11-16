
import csv
apps=["imc", "dig", "face", "vgg", "asr", "pos", "ner", "chk"]
batch=512
procs=range(1,16)
trial=10.0
dirname="server-load-timing"

for app in apps:
  for p in procs:
    layers={}
    csvfile = "%s/%s-%d-%d-layer-timing.csv" % (dirname, app, batch, p)
    with open(csvfile, 'rb') as f:
      data = csv.DictReader(f, delimiter=',', fieldnames=['layer','lat'])
      for row in data:
        if row['layer'] not in layers:
          layers[row['layer']] = float(row['lat'])
        else:
          layers[row['layer']] += float(row['lat'])
    
      # take average
      for key,value in layers.iteritems():
        layers[key] = value/trial
    
      # write to csv
      OutCsv = "%s/%s-%d-%d-layer-timing-avg.csv" % (dirname,app,batch,p)
      writer = csv.writer(open(OutCsv, 'wb'))
      for key,value in layers.iteritems():
        writer.writerow([key,value])


