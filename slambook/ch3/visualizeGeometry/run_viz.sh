#!/bin/bash

# 启动虚拟显示服务
Xvfb :1 -screen 0 1024x768x16 &
export DISPLAY=:1

# 启动 VNC 服务
x11vnc -forever -create -display :1 &

# 启动 noVNC（网页访问服务）
/usr/share/novnc/utils/launch.sh --vnc localhost:5900 --listen 8080 &

# 等待服务启动
sleep 2

# 运行可视化程序
./build/visualizeGeometry