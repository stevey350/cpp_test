/**
 * @file gflags_test.cpp
 * @brief 除了官方文档：
 *        还可以参考：https://blog.csdn.net/mj641893086/article/details/74943136
 * @author sj.su (sj.su@tungthih.com.cn)
 * @version 1.0
 * @date 2021-11-11
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
 *     <th>2021-11-11
 *     <th>v0.0.1
 *     <th>sj.su
 *     <th>原型开发
 * </tr>
 * </table>
 */
#include <iostream>
#include <gflags/gflags.h>

using namespace std;

static bool ValidatePort(const char* flagname, int value) {
   if (value > 0 && value < 32768)   // value is ok
     return true;
   printf("Invalid value for --%s: %d\n", flagname, (int)value);
   return false;
}

// 定义Flags, 一般会单独定义，如在foo.h和foo.cc中
DEFINE_bool(big_menu, true, "Include 'advanced' options in the menu listing");
DEFINE_string(languages, "english,french,german",
                "comma-separated list of languages to offer in the 'lang' menu");
DEFINE_int32(port, 1, "What port to listen on");    // 可尝试置为0试一下
DEFINE_validator(port, &ValidatePort);


// 终端输入：./3rdparty/gflags_test --nobig_menu --languages="chinese,japanese,korean" --port=2
// 备注：bool型值变更通过--variable/--novariable, 非bool型值变更通过--variable=value
int main(int argc, char **argv)
{
    // 注意：SetVersionString() 和 SetUsageMessage() 一定要在 ParseCommandLineFlags() 之前设定
    gflags::SetVersionString("V1.0.0");         // 通过该命令./xxx --version显示版本信息
    string usage_str = "Usage: ";
    usage_str+=argv[0];
    gflags::SetUsageMessage(usage_str);
    if(argc<2){
        gflags::ShowUsageWithFlagsRestrict(argv[0], "gflags_test");
        return 0;
    }
    gflags::ParseCommandLineFlags(&argc, &argv, true);  // true表示不保留定义的flags ?
    cout << "big_menu: " << FLAGS_big_menu << endl;
    cout << "languages: " << FLAGS_languages << endl;
    cout << "port: " << FLAGS_port << endl;

    // 直接访问Flags，只需加上前缀FLAGS_
    if (FLAGS_big_menu)
        FLAGS_languages += ",klingon";
    cout << "languages: " << FLAGS_languages << endl;

    return 0;
}