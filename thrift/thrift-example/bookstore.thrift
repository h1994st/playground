include "date.thrift"

namespace cpp bookstore

struct Book {
    1: required string name,
    2: required string publisher,
    3: required string author,
    4: required date.Date date
}

typedef list<Book> BookList

struct BookSearchResult {
    1: BookList books
}

exception InvalidOperation {
    1: i32 whatOp,
    2: string why
}

service Bookstore {
    bool addBook(1: Book book) throws (1: InvalidOperation e),
    BookSearchResult searchBooks(1: string query)
}
