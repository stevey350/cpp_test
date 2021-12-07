/**
 * @file glog_test.cpp
 * @brief  glog日志级别有INFO, WARNING, ERROR, and FATAL，对应数字为0, 1, 2, 和3
 * @author sj.su (sj.su@tungthih.com.cn)
 * @version 1.0
 * @date 2021-12-07
 * 
 * @copyright Copyright (c) 2021 Xiamen Tung Thih Electron CO.,LTD
 * 
 * @par History:
 * <table>
 * <tr>
 *     <th>Date
 *     <th>Version
 *     <th>Author
 *     <th>Description
 * </tr>
 * <tr>
 *     <th>2021-12-07
 *     <th>v0.0.1
 *     <th>sj.su
 *     <th>原型开发
 * </tr>
 * </table>
 */
#define GLOG_NO_ABBREVIATED_SEVERITIES

#include <glog/logging.h>
#include <assert.h>

int main(int argc, char* argv[]) {
    // 在InitGoogleLogging前设置，或者在程序运行时作为参数选项传入
    FLAGS_log_dir = "./";       // 输出日志目录，默认输出到默认目录下，即
    FLAGS_logtostderr = false;   // 默认为false, 输出到日志文件中；设为true后，输出到终端中
    // FLAGS_stderrthreshold = 0;  // 默认为2,输出到日志文件中的消息中，有高于该级别的，会拷贝一份输出到终端中
    // FLAGS_minloglevel = 0;      // 默认为0，最低输出级别（日志文件和终端都会受该标志影响）
    FLAGS_v = 1;

    // 初始化Google logging库
    google::InitGoogleLogging(argv[0]);
    // google::EnableLogCleaner(1);

    LOG(INFO) << "stderrthreshold = 0";

    int flag = 0;
    LOG_IF(INFO, flag==1) << "flag is 1";

    for (int i=0; i<100; i++) {
        LOG_FIRST_N(WARNING, 20) << "Got the " << google::COUNTER << "th cookie";
        LOG_IF_EVERY_N(WARNING, i>=50, 15) << "LOG_IF_EVERY_N " << google::COUNTER;
    }

    LOG(INFO) << "----------------------------------------";
    for (int i=0; i<100; i++) {
        LOG_EVERY_N(WARNING, 20) << "Got the " << google::COUNTER << "th cookie";
    }

    DLOG(INFO) << "DLOG";

    // ...
    LOG(ERROR) << "Found " << 10 << " cookies";

    VLOG(1) << "I’m printed when you run the program with --v=1 or higher";

    // -------------------------------
    // CHECK(flag != 0) << "check message";
    // assert(flag != 0);

    return 0;
}