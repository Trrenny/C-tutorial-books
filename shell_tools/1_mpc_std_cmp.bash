#!/usr/bin/env bash
cd ..

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


rm -rf install
rm -rf build
rm -rf log
colcon build
