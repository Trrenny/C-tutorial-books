#!/usr/bin/env bash

source /app/dds/setup.bash
ros2 bag record -e "/(mpc|sensor|tracking|structured|roadedge|traffic|odom|gloc|fusion_msg|freespace|aguamenti_sep/map|aguamenti_sep/static).*"


# # # source env
# # base_dir=$(cd ; pwd)
# # echo $base_dir

# # ros2_folder="ros2_galactic"
# # if [ -d "$base_dir/$ros2_folder" ]
# # then
#     # # echo "$base_dir/$ros2_folder"
#     # source "$base_dir/ros2_galactic/ros2-linux/setup.bash"
# # else
#     # echo "!!!!!"
#     # source /opt/ros/ros2_galactic/ros2-linux/setup.bash
# # fi

# # source /ufs/ap_dds/dds_msg_lib/setup.bash
# # source ../install/setup.bash

# # 457
# source /ufs/dds/setup.bash
# source /ufs/install/local_setup.bash


# # # set param
# # read -ep "请输入截断时长（单位：s）：" Dur_num
# # split_duration=${Dur_num}
# # ((sleep_num=${Dur_num}/2))
# # sleep_duration=${sleep_num}

# # add topic to log
# all_topic=""

# # export mpc_debug_topic="/mpc_interface_Lat_debug  \
#                 # /fromROSgotoCAN_509_FVCM_HSC2_FrP03 \
# # "
# # all_topic=${all_topic}" "${mpc_debug_topic}

# # mpc topic
# for mpc_topic in $(ros2 topic list | grep "/mpc_*")
# do
#     all_topic=${all_topic}" "${mpc_topic}
# done

# # cem topic
# # for mpc_topic in $(ros2 topic list | grep "/(camera|sensor|tracking|structured|roadedge|traffic|odom|gloc|fusion_msg|freespace|aguamenti_sep/map|aguamenti_sep/static).*")
# for cem_topic in $(ros2 topic list | grep -E "/sensor|/tracking|/structured|/roadedge|/traffic|/odom|/gloc|/fusion_msg|/freespace|/aguamenti_sep/map|/aguamenti_sep/static")
# do
#     all_topic=${all_topic}" "${cem_topic}
# done


# echo "Subscribed topics list:"
# echo ${all_topic}
	

# echo -e "\n###### start log######\n"
# ros2 bag record ${all_topic}