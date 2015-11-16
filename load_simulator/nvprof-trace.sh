network=$1
trial=$2
gpu=$3

fname=${network##*/}
export TASK=${fname%%.*}
stats=${fname%%.*}
mkdir -p $stats
rm -rf $stats/trace*

nvprof \
    --aggregate-mode on \
    --print-gpu-trace \
    --csv \
    --log-file $stats/trace_%q{TASK}_%p.csv \
    ./load-simulator --network $network \
                 --trial $trial \
                 --gpu $gpu
