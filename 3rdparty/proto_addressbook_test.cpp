/**
 * @file proto_test.cpp
 * @brief 官方使用文档：https://developers.google.com/protocol-buffers/docs/overview
 *        生成*pb.h和*pb.cc文件的命令：protoc -I=./ --cpp_out=./ proto_person.proto
 *        就可以实现，转成*pb.h和*pb.cc后，提供如下API：
 *        1. required/optional类型的字段，提供访问接口：has_, set_, clear_, mutable_(numeric没有，string类型才有)
 *        2. repeated类型的字段，提供访问接口：        _size, add_, clear_, mutable_
 *        3. message类型的消息，提供标准消息方法：IsInitialized(), DebugString(), CopyFrom(...), Clear()
 *        4. 解析接口：  ParseFromString(const string& data), ParseFromIstream(istream* input)
 *        5. 序列化接口：SerializeToString(string* output), SerializeToOstream(ostream* output)
 *        
 * @author sj.su (sj.su@tungthih.com.cn)
 * @version 1.0
 * @date 2021-11-15
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
 *     <th>2021-11-15
 *     <th>v0.0.1
 *     <th>sj.su
 *     <th>原型开发
 * </tr>
 * </table>
 */
#include <iostream>
#include <fstream>
#include <string>
#include "proto_addressbook.pb.h"

using namespace std;


void proto_default_value_test(tutorial::AddressBook &address_book)
{
    if(!address_book.IsInitialized()) {
        cout << "address_book has not been initialized" << endl;
    }

    cout << "address_book size: " << address_book.people_size() << endl;
    cout << "has book_name?: " << address_book.has_book_name() << endl;
    cout << "set book_name" << endl;
    address_book.set_book_name("test");
    cout << "has book_name?: " << address_book.has_book_name() << endl;
    address_book.clear_book_name();
    cout << "has book_name?: " << address_book.has_book_name() << endl;

    tutorial::Person *people = address_book.add_people();  // 针对repeated字段，需要先添加一个对象才能访问
    cout << "people name: " << address_book.people(0).name() << endl;
    cout << "people id: " << address_book.people(0).id() << endl;
    cout << "people email: " << address_book.people(0).email() << endl;
    // address_book.people(0).add_phones();     // 不能通过这种方式添加
    people->add_phones();
    cout << "people phone number: " << address_book.people(0).phones(0).number() << endl;
    cout << "people phone type: " << address_book.people(0).phones(0).type() << endl;

    cout << "DebugString: " << address_book.DebugString() << endl;
    address_book.Clear();       // clears all the elements back to the empty state.
}

// 命令：./3rdparty/proto_addressbook_test addr_book.bin
int main(int argc, char* argv[]) {
  // Verify that the version of the library that we linked against is
  // compatible with the version of the headers we compiled against.
  GOOGLE_PROTOBUF_VERIFY_VERSION;

  if (argc != 2) {
    cerr << "Usage:  " << argv[0] << " ADDRESS_BOOK_FILE" << endl;
    return -1;
  }

  tutorial::AddressBook address_book;
  // protocol buffer默认值测试
  proto_default_value_test(address_book);

  {
    // Read the existing address book.
    fstream input(argv[1], ios::in | ios::binary);
    if (!input) {
      cout << argv[1] << ": File not found.  Creating a new file." << endl;
    } else if (!address_book.ParseFromIstream(&input)) {
      cerr << "Failed to parse address book." << endl;
      return -1;
    }
  }
  
  tutorial::AddressBook address_book2;
  address_book2.CopyFrom(address_book);

  cout << "DebugString: " << address_book.DebugString() << endl;
  cout << "DebugString: " << address_book2.DebugString() << endl;

  // Optional:  Delete all global objects allocated by libprotobuf.
  google::protobuf::ShutdownProtobufLibrary();

  return 0;
}