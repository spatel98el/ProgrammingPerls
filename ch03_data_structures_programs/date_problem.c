// prob 3: date related
// 1. Given two dates -> compute numbed of days between them
// 2. given date -> return its day of week
// 3. given a month and year -> produce calendar for month
#include <stdio.h>

#define DAYS_OF_YEAR 365 // add offset later

typedef struct {
    int day, month, year;
}Date;
static const int DaysOfMonth[12] = {
    31,28,31,30,31,30,31,31,30,31, 30, 31
};
int isLeapYear(int y) {
    // check for leap year
    if((y % 400 == 0) || (y % 4 == 0 && y % 100 != 0)) {
        return 1;
    } else {
        return 0;
    }
}


int computeDays(Date startDate, Date endDate) {
    int days = 0, months = 0, years = 0;

    // delta of years - if > 1, = 1, = 0
    years += endDate.year - startDate.year;
    if(years > 1) {
        months += (years - 1) * 12;
        days += (years - 1)*365;
        
        // add leap year offsets
        for(int y = startDate.year + 1; y < endDate.year; y++) {
            days += isLeapYear(y);
        }
        
        years = 1;
    } 

    if(years == 1) {
        months += 12 - startDate.month + endDate.month;
        years = 0;

        for(int m = startDate.month + 1; m <= 12; m++) {
            days += DaysOfMonth[m-1];
            if(m == 2) {
                days += isLeapYear(startDate.year);
            }
        }
        for(int m = 1; m < endDate.month ; m++) {
            days += DaysOfMonth[m-1];
            if(m == 2) {
                days += isLeapYear(endDate.year);
            }
        }
    } else {
        months += endDate.month - startDate.month;
        for(int m = startDate.month + 1; m < endDate.month; m++) {
            days += DaysOfMonth[m-1];
            if(m == 2) {
                days += isLeapYear(startDate.year);
            }
        }

    }

    if(months == 0) {
        days += endDate.day - startDate.day;
    } else {
        days += DaysOfMonth[startDate.month] - startDate.day;
        days += endDate.day;
    }

    return days;
}


int main() {
   
    Date startDate = {6,11,2025};
    Date endDate = {10,11,2025};

    int days = computeDays(startDate, endDate);

    printf("days : %d\n", days);

    return 0;
}
