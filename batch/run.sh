#!/bin/bash

n_files=$1
file_list=$2
output_dir=$3

partition=debug
time=0:20:00
build_dir=/lustre/hades/user/mmamaev/hades_quality_assurance/build/

lists_dir=${output_dir}/lists/
log_dir=${output_dir}/log

mkdir -p $output_dir
mkdir -p $log_dir
mkdir -p $lists_dir

split -l $n_files -d -a 3 --additional-suffix=.list "$file_list" $lists_dir

n_runs=$(ls $lists_dir/*.list | wc -l)

job_range=1-$n_runs

echo file list: $file_list
echo output_dir: $output_dir
echo log_dir: $log_dir
echo lists_dir: $lists_dir
echo n_runs: $n_runs
echo job_range: $job_range

sbatch --wait \
      -J HADES-QA \
      -p $partition \
      -t $time \
      -a $job_range \
      -e ${log_dir}/%A_%a.e \
      -o ${log_dir}/%A_%a.o \
      --export=output_dir=$output_dir,file_list=$file_list,lists_dir=$lists_dir,build_dir=$build_dir \
      -- /lustre/hades/user/mmamaev/hades_quality_assurance/batch/batch_run.sh

source /lustre/nyx/hades/user/mmamaev/install/root-6.20.04-centos7-cxx17/bin/thisroot.sh

hadd -j -f $output_dir/qa_all.root $output_dir/*/output.root >& $log_dir/log_merge.txt

out_file_name=QA_`basename $output_dir`.root

cp $output_dir/correlation_all.root ~/Correlations/$out_file_name

echo Merging finished. Merging log is availible in
echo $log_dir/log_merge.txt
echo
echo output file name: $output_dir
