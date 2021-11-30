
## OpenCV安装

#### 依赖项安装&编译

```
# download OpenCV 3.4.14
https://opencv.org/releases/
unzip opencv-3.4.14.zip
wget -O opencv_contrib.zip https://github.com/Itseez/opencv_contrib/archive/3.4.14.zip  # OpenCV3之后,SIFT/ SUFR功能就移到contrib
unzip opencv_contrib-3.4.14.zip

# 安装依赖
sudo apt-get install build-essential
sudo apt-get install cmake git libgtk2.0-dev pkg-config libavcodec-dev libavformat-dev libswscale-dev
sudo apt-get install python-dev python-numpy libtbb2 libtbb-dev libjpeg-dev libpng-dev libtiff5-dev libdc1394-22-dev # 处理图像所需的包
sudo apt-get install libavcodec-dev libavformat-dev libswscale-dev libv4l-dev liblapacke-dev
sudo apt-get install libxvidcore-dev libx264-dev         # 处理视频所需的包
sudo apt-get install libatlas-base-dev gfortran          # 优化opencv功能
sudo apt-get install ffmpeg
sudo apt-get install libgtk-3-dev						 # 用来操控OpenCV GUI的模块是highgui. highgui模块依赖GTK库

# 编译安装opencv
cd opencv-3.4.14
mkdir build
cd build
cmake -D CMAKE_BUILD_TYPE=Release -D CMAKE_INSTALL_PREFIX=/usr/local ..
make -j8
sudo make install
```



#### 配置环境

```
# 1) 
sudo /bin/bash -c 'echo "/usr/local/lib" > /etc/ld.so.conf.d/opencv.conf'
sudo ldconfig		# 默认搜寻/lilb和/usr/lib，以及配置文件/etc/ld.so.conf内所列的目录下的库文件; 创建出动态装入程序(ld.so)所需的连接和缓存文件。缓存文件默认为/etc/ld.so.cache



ps.
`pkg-config opencv --libs --cflags opencv`		# 编译的时候可以add the命令
$ pkg-config opencv --libs --cflags opencv
-I/usr/local/include/opencv -I/usr/local/include -L/usr/local/lib -lopencv_dnn -lopencv_highgui -lopencv_ml -lopencv_objdetect -lopencv_shape -lopencv_stitching -lopencv_superres -lopencv_videostab -lopencv_calib3d -lopencv_videoio -lopencv_imgcodecs -lopencv_features2d -lopencv_video -lopencv_photo -lopencv_imgproc -lopencv_flann -lopencv_core
```



#### OpenCV测试

1. 查看Opencv安装的版本号

```
pkg-config --modversion opencv
```

2. 在终端打开到opencv-3.4.14/sample/cpp/example_cmake目录，执行下面的代码

```shell
cmake .
make
./opencv_example
```

如果摄像头打开，左上角出现 Hello OpenCV 则证明安装成功