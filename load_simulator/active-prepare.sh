rm -rf *.txt
#mkdir -p graphs
#for d in asr chk face googlenet imc 
for d in load
do
    echo $d
    ./prepare-nvprof.sh $d
    ls $d/*.csv >> active.txt
    # ./metrics-parser.py $d.txt $d
done
