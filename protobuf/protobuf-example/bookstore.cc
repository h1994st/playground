#include <iostream>

#include <google/protobuf/text_format.h>

#include "bookstore.pb.h"

int main(int argc, char* argv[]) {
    GOOGLE_PROTOBUF_VERIFY_VERSION;

    bookstore::Bookstore bookstore;

    auto book = bookstore.add_book();

    book->set_name("Test");
    book->set_publisher("Publisher Cat");
    book->set_author("Author Dog");

    auto date = book->mutable_date();
    date->set_year(2021);
    date->set_month(5);
    date->set_day(15);

    std::string s;
    google::protobuf::TextFormat::PrintToString(bookstore, &s);
    std::cout << s << std::endl;

    google::protobuf::ShutdownProtobufLibrary();

    return 0;
}
