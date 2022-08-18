cem-dds_tools:  
    http://10.94.38.105/cem/dds_framework/dds_tools  

  
# es33上车

## 1 准备工作
规控mpd相关信息：
> 账号密码均为：nvidia  
ros-noetic路径：/opt/ros/noetic/setup.bash  
ros2-galactic路径：/home/nvidia/ros2_galactic/ros2-linux/setup.bash  

### 1.1 dds功能包编译
1. 通过ssh工具（推荐MobaXterm）连接规控mpd（ip可联系任玉庆确认）,账号密码均为：nvidia
2. 到`/ufs`路径下新建自己的工作空间，如以`ba`为例：
```bash
cd /ufs
mkdir mpc_ba
cd mpc_ba
```
3. 在自己工作空间内新建ros2工作空间（建议命名：`时间-更新模块与目的`，如：`20220328-ba-test`），然后拷贝并编译功能包
4. 将模块软件拷贝出：
    1. 拷贝整个install：（建议先压缩，如：`tar -cvf 20220328-ba-test.tar ./install`）
    2. **或**仅拷贝自己需要更新的模块：（建议先压缩，如：`tar -cvf 20220328-ba-rm-test.tar ./install/mpc_drv_ctap_ba ./install/mpc_drv_ctap_rm`）



## 2 上车
> 既可以直接通过车上工控机操作（需要将软件拷贝至移动硬盘），也可以通过自己开发本操作（直接将软件放在开发本本地即可）（先连接车上WiFi，密码：12345678，然后通过ssh工具连接工控机）
### 2.1 登录mpd
* 硬件环境
    * <mark>EP⻋的操作包括MPD与⼯控机。⻋上显⽰器接⼯控机，**在⼯控机**上通过ssh远程连接MPD进⾏操作</mark>。
    * 启动CEM程序、**录制数据 在MPD**上完成。
    * 监控数据状态 在⼯控机上完成。

* ⼯控机
    * ⽹卡/ip地址 enp8s0/**192.168.2.200**
    * ⽤户名 saic
    * 密码 PASS

* MPD
    * ⽹卡/ip地址 mgbe3_0/**192.168.1.102**
    * <mark>⽤户名: nvidia</mark>
    * <mark> 密码: nvidia</mark>


* 常⽤命令
    * 在⼯控机上登录mpd: `ssh $mpd`


### 2.2 模块软件拷贝
以`ba`为例：新建文件夹`/app/package/temp/mpc_test/ba_test`
将模块软件拷贝至mpd：`/app/package/temp/mpc_test/ba_test`
解压：
```bash
cd /app/package/temp/mpc_test/ba_test
tar -xvf 20220328-ba-test.tar
```

### 2.3 节点状态查看
现在457和490上均已设置：mpd开机，pp-cem（包含cem和mpc）所有节点自启动

节点状态查看：
```bash
source /app/dds/setup.bash
ros2 node list
```

### 2.4 模块更新
说明：
> 目前车上各模块均通过daemon（service/服务）进行自启，其对各模块软件的调用均通过`/app/package/running`路径下的软链接进行定位的，
<mark>因此更新模块只需要更新软链接的指向即可</mark>。
`/app/package/running`下目录为：
> * ap：存放指向中间件的软链接
> * cem：存放指向各模块软件的软链接
> * msg：存放指向所有msg头文件的软链接

#### 2.4.1 链接状态查看
```bash
cd /app/package
tree ./ -L 3
```
即可查看各链接指向。

#### 2.4.2 链接替换
> 注意要连接到模块软件下的包含lib、script的文件夹，即为：`install/mpc_drv_ctap_ba/mpc_drv_ctap_ba`

以`ba`为例：
**方式1：**
使用`change_package`脚本（替换模块较多时使用）
新建`.log`文件，如：`change_ba.log`，
```bash
cd /app/package/temp/mpc_test/ba_test
vi change_ba.log
```
编辑内容，每一行为：<新模块软件相对`.log`文件的路径> <软链接(相对`/app/package/running`的路径)>，如：
```bash
./install/mpc_drv_ctap_ba/mpc_drv_ctap_ba ./cem/mpc_drv_ctap_ba
```

```bash
./install/mpc_drv_ctap_ba/mpc_drv_ctap_ba ./cem/mpc_drv_ctap_ba
./install/mpc_drv_ctap_rm/mpc_drv_ctap_rm ./cem/mpc_drv_ctap_rm
```
更改软链接：
```bash
cd /app/package
./change_package some ./temp/mpc_test/ba_testchange_ba.log
```

**方式2：**
删除需要替换的软链接，然后新建软链接（以`ba`为例）
```bash
cd /app/package/running/cem
rm mpc_drv_ctap_ba
# ln -s target link ，如：
ln -s /app/package/temp/mpc_test/ba_test/install/mpc_drv_ctap_ba/mpc_drv_ctap_ba mpc_drv_ctap_ba
```

#### 2.4.3 服务重启（链接生效）
```bash
# 重启
sudo systemctl restart cem_*

# 状态查看
sudo systemctl status cem_mpc_*
```


### 2.5 测试
source ros2环境
```bash
source /app/dds/setup.bash
```

录log数据
```bash
cd /fota/mpc_record
./mpc_record.bash
```
拷贝log数据