for i in $(seq 1 20)
do
  ./load-simulator --network load.prototxt --trial 200 --gpu 1 --layer_csv 20-concurrent-timing/load_timing_${i} &
done
