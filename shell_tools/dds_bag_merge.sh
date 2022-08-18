#!/bin/bash

set -e
# set -x

DDS_TOOL_PATH="/home/igs/Desktop/1.git/dds_tools/"

LOG_PATH="/data/saic_server/logDDS/动态测试数据/20220727/"

MERGE_MODULES=("fs_bag_*" "other_*" "control_bag_*")

merge() {
    if [[ ! -d ${DDS_TOOL_PATH} || ! -d ${LOG_PATH} || -z ${MERGE_MODULES} ]]; then
        echo "ERROR: please check input!"
    fi

    if [[ -n $(ls ${DDS_TOOL_PATH}"/dds_bag/merged/") ]]; then
        echo "ERROR: there are some remaning merged output in ${DDS_TOOL_PATH}"/dds_bag/merged/"!"
        exit -1
    fi

    source ${DDS_TOOL_PATH}"dds_tools_setup.bash"

    cd $LOG_PATH

    for dir in $(ls); do
        if [[ -d ${dir} ]]; then
            cd ${dir}
            flag_all_modules=1
            for m in ${MERGE_MODULES[@]}; do
                if [[ ! -d $m ]]; then
                    flag_all_modules=$((flag_all_modules * 0))
                fi
            done
            if [[ 0 -eq ${flag_all_modules} ]]; then
                echo ${flag_all_modules}
                echo "WARNING: there is some modules missing in folder ${dir}!"
                cd ..
                continue
            fi
            dds_bag_convert -m -i ${MERGE_MODULES[@]}
            mv ${DDS_TOOL_PATH}"dds_bag/merged/"* .
            cd ..
        else
            echo ${dir} " is not a folder. Pass....."
        fi
    done
}

merge 2>&1 | tee -a ${LOG_PATH}/bag_merge_log.txt

