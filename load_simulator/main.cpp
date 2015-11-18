/* Johann Hauswald, Yiping Kang
 * {jahausw, ypkang}@umich.edu
 * 2014
 */

#include <vector>
#include <string>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <iostream>
#include <fstream>
#include <unistd.h>  
#include <errno.h>
#include <map>
#include <glog/logging.h>
#include <sys/stat.h>

#include "boost/program_options.hpp" 

#include "caffe/caffe.hpp"
#include "caffe/net.hpp"

using caffe::Blob;
using caffe::Caffe;
using caffe::Net;
using caffe::Layer;
using caffe::shared_ptr;
using caffe::Timer;
using caffe::vector;
using caffe::Net;

using namespace std;
namespace po = boost::program_options;

namespace caffe {
template <typename Dtype>
class LoadSim : public Net<Dtype> {
  public:
  Dtype LoopLayer(int idx, int loop){
    struct timeval start,end,diff;
    if(loop == 0){
      std::cerr<<"Infinte looping layer "<<this->layers_[idx]->name()<<" to keep the GPU at a certain utilization."<<std::endl;
      while(true){
        this->layers_[idx]->Forward(this->bottom_vecs_[idx], this->top_vecs_[idx]);
      }
    }else{
      for(int i=0; i < loop; i++)
        gettimeofday(&start, NULL);
        this->layers_[idx]->Forward(this->bottom_vecs_[idx], this->top_vecs_[idx]);
        cudaDeviceSynchronize();
        gettimeofday(&end, NULL);
        timersub(&end, &start, &diff);
        float lat = (double)diff.tv_sec*(double)1000 + (double)diff.tv_usec/(double)1000;
        std::cerr<<lat<<std::endl;
    }
  }
};

}

po::variables_map parse_opts( int ac, char** av )
{
    // Declare the supported options.
    po::options_description desc("Allowed options");
    desc.add_options()
        ("help,h", "Produce help message")
        ("gpu,u", po::value<bool>()->default_value(true), "Use GPU?")
        ("debug,v", po::value<bool>()->default_value(false), "Turn on all debug")

        // Options for local setup
        ("network,n", po::value<string>()->default_value("dummy.prototxt"), "DNN network to use in this experiment")
        ("input,i", po::value<string>()->default_value("undefined"), "Input to the DNN")
        ("trial,r", po::value<int>()->default_value(1), "number of trials")
        ("threads,t", po::value<int>()->default_value(1), "CPU threads used (default: 0)")
        ("layer_csv,l", po::value<string>()->default_value("NO_LAYER"), "CSV file to put layer latencies in.")
        ("app_csv,a", po::value<string>()->default_value("NO_APP"), "CSV file to put app latencies in.")
        ;

    po::variables_map vm;
    po::store(po::parse_command_line(ac, av, desc), vm);
    po::notify(vm);    

    if (vm.count("help")) {
        cout << desc << "\n";
        return vm;
    }
    return vm;
}

int main(int argc , char *argv[])
{
    po::variables_map vm = parse_opts(argc, argv);
    caffe::Phase phase = 1; // Set phase to TEST
    int openblas_threads = 1;

    if(vm["gpu"].as<bool>()){
        Caffe::set_mode(Caffe::GPU);
    }
    else{
        Caffe::set_mode(Caffe::CPU);
        openblas_threads = vm["threads"].as<int>();
    }

    vector<Blob<float>*> bottom;
    caffe::LoadSim<float>* net = new Net<float>(vm["network"].as<string>().c_str(), phase);
    float loss;

    net->ForwardPrefilled(&loss);
    net->LoopLayer(1,vm["trial"].as<int>());
    
    /*
    struct timeval start,end,diff;
    gettimeofday(&start, NULL);
    for(int i = 0; i < vm["trial"].as<int>(); i++)
      //net->ForwardPrefilled(&loss, vm["layer_csv"].as<string>());
      net->ForwardPrefilled(&loss, "NO_LAYER");

    gettimeofday(&end, NULL);
    timersub(&end, &start, &diff);
    float runtime = (double)diff.tv_sec*(double)1000 + (double)diff.tv_usec/(double)1000;

    std::ofstream csv;
    csv.open(vm["layer_csv"].as<string>().c_str(), ios::out | ios::app);

    if(!csv.is_open()){
      std::cerr<<"CSV file cant be opened"<<std::endl;
      exit(1);
    }
    
    char out_str[100];
    sprintf(out_str, "%.4f\n", runtime);
    csv<<out_str;
    csv.close();
    */
    return 0;
}
