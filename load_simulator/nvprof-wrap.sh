network=$1
trial=$2
gpu=1

k=$network

rm -rf $k/*
./nvprof-metrics.sh $k \
                    $trial \
                    $gpu

./nvprof-timing.sh $k \
                   $trial \
                   $gpu

./nvprof-trace.sh $k \
                  $trial \
                  $gpu
