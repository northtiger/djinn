#/usr/bin/bash
#for batch in $(seq 1 4 512) 
#for batch in "1" "2" "4" "8" "16" "32" "64" "128" "256" "512"
#do
#  for in_dim in "1" "2" "4" "8" "16" "32" "64" "128" "256" "512"
#  do
#    for out_dim in "1" "2" "4" "8" "16" "32" "64" "128" "256" "512"
#    do
#      ./change-load.py $batch $in_dim $out_dim
#      ./nvprof-wrap.sh load.prototxt 10
#      ./active-prepare.sh
#      ./active-warps.py active.txt $batch $in_dim $out_dim
#    done
#  done
#done


# profile the per SM occupancy of each load level
#in_dim=512
#out_dim=512
#BATCHLIST=($(seq 0 16 512))
#BATCHLIST[0]=1
#
#for batch in ${BATCHLIST[@]}; do
#  ./change-load.py $batch $in_dim $out_dim
#  ./nvprof-wrap.sh load.prototxt 10
#  ./active-prepare.sh
#  ./active-warps.py active.txt $batch $in_dim $out_dim
#done

in_dim=512
out_dim=512
BATCHLIST=($(seq 0 16 512))
BATCHLIST[0]=1
PROCESSES=($(seq 1 15 1))

for batch in ${BATCHLIST[@]}; do
  ./change-load.py $batch $in_dim $out_dim
  for proc in ${PROCESSES[@]}; do
     # Start FC layer processes to infinite looping to generate load
    ./load-simulator --network load.prototxt --trial 0 --gpu 1 & 
  done
   
done
