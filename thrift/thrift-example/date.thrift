namespace cpp bookstore

enum Month {
    JAN = 1,
    FEB,
    MAR,
    APR,
    MAY,
    JUNE,
    JULY,
    AUG,
    SEP,
    OCT,
    NOV,
    DEC
}

struct Date {
    1: required i32 year = 2021,
    2: required Month month = Month.MAY,
    3: required i8 day = 16
}
