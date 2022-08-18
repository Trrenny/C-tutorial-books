#!/usr/bin/env bash

# source env
base_dir=$(cd ; pwd)
echo $base_dir

ros2_folder="ros2_galactic"
if [ -d "$base_dir/$ros2_folder" ]
then
    # echo "$base_dir/$ros2_folder"
    source "$base_dir/ros2_galactic/ros2-linux/setup.bash"
else
    echo "!!!!!"
    source /opt/ros/ros2_galactic/ros2-linux/setup.bash
fi

source /ufs/ap_dds/dds_msg_lib/setup.bash
source ../install/setup.bash

# set param
read -ep "请输入截断时长（单位：s）：" Dur_num
split_duration=${Dur_num}

# add topic to log
all_topic=""

# export mpc_debug_topic="/mpc_interface_Lat_debug  \
#                 /fromROSgotoCAN_509_FVCM_HSC2_FrP03 \
# "
# all_topic=${all_topic}" "${mpc_debug_topic}


for mpc_topic in $(ros2 topic list | grep "/mpc_interface_*")
do
    all_topic=${all_topic}" "${mpc_topic}
done


# start logging
folder="$(date "+%Y-%m-%d")""-rosbag"
if [ -d "./"${folder} ]
then
    echo "${folder}already exists!"
else
    mkdir ${folder}
fi
echo "folder_name: ${folder}"

cd ${folder}

echo -e "\n###### start log######\n"
ros2 bag record ${all_topic} -d ${split_duration}