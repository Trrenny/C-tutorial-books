#!/usr/bin/env bash

## source ##
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

source ../install/setup.bash

# kill existed ps
for ps_id in $( ps -ef | grep "./install/mpc_drv_ct*" | grep -v "grep" | awk '{print $2}' )
do 
    if [ $ps_id -ge 0 ]
    then
        kill -9 ${ps_id}
    fi
done


# get path of lib
lib_path=$(find ../ -name "install")
echo ${lib_path}
sleep 0.5s


./${lib_path}/mpc_drv_ctap_rm/mpc_drv_ctap_rm/script/run.sh &
echo "###  mpc_drv_ctap_rm has started  ###"
sleep 0.5s

./${lib_path}/mpc_drv_ctap_ba/mpc_drv_ctap_ba/script/run.sh &
echo "###  mpc_drv_ctap_ba has started  ###"
sleep 0.5s

./${lib_path}/mpc_drv_ctap_sm/mpc_drv_ctap_sm/script/run.sh &
echo "###  mpc_drv_ctap_sm has started  ###"
sleep 0.5s

./${lib_path}/mpc_drv_ctap_trplat/mpc_drv_ctap_trplat/script/run.sh &
echo "###  mpc_drv_ctap_trplat has started  ###"
sleep 0.5s

./${lib_path}/mpc_drv_ctap_trplon/mpc_drv_ctap_trplon/script/run.sh &
echo "###  mpc_drv_ctap_trplon has started  ###"
sleep 0.5s

./${lib_path}/mpc_drv_ctap_vse/mpc_drv_ctap_vse/script/run.sh &
echo "###  mpc_drv_ctap_vse has started  ###"
sleep 0.5s

./${lib_path}/mpc_drv_ctap_mpctrl/mpc_drv_ctap_mpctrl/script/run.sh &
echo "###  mpc_drv_ctap_mpctrl has started  ###"
sleep 0.5s

./${lib_path}/mpc_drv_ctap_mpplan/mpc_drv_ctap_mpplan/script/run.sh &
echo "###  mpc_drv_ctap_mpplan has started  ###"
sleep 0.5s


# echo "###  starting rqt  ###"
# source ./${lib_path}/../setup.bash
# rqt & 

# gnome-terminal --tab
