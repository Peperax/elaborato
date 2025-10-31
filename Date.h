#ifndef DATE_H
#define DATE_H

#include <string>

class Date {
private:
    int day;
    int month;
    int year;

public:
    Date(int d, int m, int y);

    [[nodiscard]] bool isValid() const;

    [[nodiscard]] int getDay() const {
        return day;
    }

    [[nodiscard]] int getMonth() const {
        return month;
    }

    [[nodiscard]] int getYear() const {
        return year;
    }

    void setDay(int d);
    void setMonth(int m);
    void setYear(int y);
};



#endif //DATE_H
