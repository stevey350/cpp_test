
## Eigen安装
在Ubuntu下使用如下命令
```
sudo apt-get install libeigen3-dev
```

## gflags
gflags是一种命令行解析工具，主要用于解析用命令行执行可执行文件时传入的参数。与getops()不同的是，在gflags中flag可以分散的定义在各个文件之中，而不用定义在一起，这就意味着在我们可以在一个单独的文件中只定义这个文件所需要用到的一些flag，链接了该文件应用都可以使用该文件中的flag，这样就能非常方便的实现代码的复用，如果不同的文件定义了相同的flag，则会产生错误，所以需要明确规范gflags的使用规范。

官方文档
[gflags github](https://github.com/gflags/gflags)
[How To Use gflags (formerly Google Commandline Flags)](https://gflags.github.io/gflags/)


### 安装
```
sudo apt-get install libgflags-dev
```

## protocol buffers
在ubuntu18.04上直接使用下面命令
```
sudo apt-get install libprotobuf-dev			# 安装
sudo apt-get remove libprotobuf-dev				# 御载
protoc --version	# 查看安装的版本
```
