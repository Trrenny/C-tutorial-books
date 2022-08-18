#!/usr/bin/env bash

# kill existed ps
for ps_id in $( ps -ef | grep "./install/mpc_drv_ct*" | grep -v "grep" | awk '{print $2}' )
do 
    if [ $ps_id -ge 0 ]
    then
        kill -9 ${ps_id}
    fi
done

