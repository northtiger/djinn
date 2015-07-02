#!/usr/bin/env python

import os,sys
import string 

#common='./data_set/' 
common='./'
fullset= common + 'extracted'
trainset= common + 'selected'

full_spk = []
train_spk = []

for spk in os.listdir(fullset):
    full_spk.append(spk)

for spk in os.listdir(trainset):
    train_spk.append(spk)

full_spk.sort()
train_spk.sort()

#diff_spk=list(set(full_spk) - set(train_spk))

diff_spk=[]
same_spk=[]
for i in full_spk:
    if i not in train_spk:
        diff_spk.append(i)
    else:
        same_spk.append(i)


# deal with anonymous speakers here
for s in train_spk:
    if 'anonymous' in s:
        # split 
        arr=s.split('-')
        # reconstruct 
        new_s= 'anonymous-' + arr[1] + '-' + arr[2]

        # see if it is in diff, if so, get rid of it
        if new_s in diff_spk:
            diff_spk.remove(new_s)
            same_spk.append(new_s)

diff_spk.sort()
same_spk.sort()

print len(full_spk)
print len(train_spk)
print len(diff_spk)
print len(same_spk)

full_file = file("full.list", 'w')
full_file.write('\n'.join(full_spk))

train_file = file("train.list", 'w')
train_file.write('\n'.join(train_spk))

diff_file = file("diff.list", 'w')
diff_file.write('\n'.join(diff_spk))

same_file = file("same.list", 'w')
same_file.write('\n'.join(same_spk))

