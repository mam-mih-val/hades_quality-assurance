#!/bin/bash

format='+%Y/%m/%d-%H:%M:%S'

date $format

job_num=$(($SLURM_ARRAY_TASK_ID))

filelist=$lists_dir/$(ls $lists_dir | sed "${job_num}q;d")

cd $output_dir
mkdir -p $job_num
cd $job_num

echo "loading /lustre/nyx/hades/user/mmamaev/install/root-6.20.04-centos7-cxx17/bin/thisroot.sh"
. /lustre/nyx/hades/user/mmamaev/install/root-6.20.04-centos7-cxx17/bin/thisroot.sh

echo "executing $build_dir/run_qa -i list.txt -o output.root --tree-name hades_analysis_tree"
$build_dir/run_qa -N 1000 -i $filelist -o output.root --tree-name hades_analysis_tree -m

echo JOB FINISHED!