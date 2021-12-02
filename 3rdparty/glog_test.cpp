
#define GLOG_NO_ABBREVIATED_SEVERITIES

#include <glog/logging.h>
#include <assert.h>

int main(int argc, char* argv[]) {
    // 在InitGoogleLogging前设置，或者在程序运行时作为参数选项传入
    // FLAGS_logtostderr = 1;
    // LOG(INFO) << "logtostderr = 1";
    // FLAGS_logtostderr = 1;
    FLAGS_stderrthreshold = 0;
    FLAGS_minloglevel = 0;
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