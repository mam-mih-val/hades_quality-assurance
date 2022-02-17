#!/bin/bash

format='+%Y/%m/%d-%H:%M:%S'

date $format

job_num=$(($SLURM_ARRAY_TASK_ID))

filelist=$lists_dir/$(ls $lists_dir | sed "${job_num}q;d")

cd $output_dir
mkdir -p $job_num
cd $job_num

build_dir=/lustre/hades/user/mmamaev/hades_quality_assurance/build-deb10/

echo "loading /lustre/hades/user/mmamaev/install/root-6.18.04-debian10-cxx17/bin/thisroot.sh"
. /lustre/hades/user/mmamaev/install/root-6.18.04-debian10-cxx17/bin/thisroot.sh

echo "executing $build_dir/run_qa -N 1000 -i $filelist -o output.root --tree-name hades_analysis_tree -m"
$build_dir/run_qa -N 1000 \
                -i $filelist \
                -o output.root \
                --tree-name hades_analysis_tree \
                -m

echo JOB FINISHED!