in_dim=1024
out_dim=1024
#BATCHLIST=($(seq 0 16 512))
#BATCHLIST[0]=1
BATCHLIST=(1024)
PROCESSES=($(seq 1 1 16))

TRIAL=200
LOADSIMDIR=../load_simulator
pwd=$PWD
apps=("imc" "dig" "dig-10" "face" "vgg" "asr" "pos" "chk" "ner")
#apps=("imc")
#export CUDA_MPS_PIPE_DIRECTORY="/tmp/mps_7"
OUTPUTDIR=server-load-timing
for batch in ${BATCHLIST[@]}; do
  for proc in ${PROCESSES[@]}; do
    cd ${LOADSIMDIR}
    ./change-load.py $batch $in_dim $out_dim
    LOADGEN_PID_LIST=($())
    for p in $(seq 1 1 ${proc}); do
      # Start FC layer processes to infinite looping to generate load
      taskset -c 23 ./load-simulator --network load.prototxt --trial 0 --gpu 1 & 
      # save the PIDs so that we can kill them later
      PREV_PID=$!
      LOADGEN_PID_LIST[$p]=$PREV_PID
    done
    cd $pwd
    sleep 5
    # run the actual process
    for app in ${apps[@]}; do
      layer_timing=${OUTPUTDIR}/${app}-${batch}-${proc}-layer-timing.csv
      timing=${OUTPUTDIR}/${app}-${batch}-${proc}-timing.csv
      taskset -c 23 ./layer_run.sh ${app} 1 1 ${timing} ${TRIAL} ${layer_timing}
      sleep 1
    done # for app
    
    # kill all the load gen processes
    for pid in ${LOADGEN_PID_LIST[@]}; do
      kill -9 $pid
    done # for pid
  done # for proc 
done # for batch 
