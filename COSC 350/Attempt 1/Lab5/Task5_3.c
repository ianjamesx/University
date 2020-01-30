#include <time.h>
#include <stdio.h>
#include <string.h>

/*

char *asctime, library function taking time pointer struct as parameter
definition of tm pointer as structure:

struct tm {
   int tm_sec;
   int tm_min;
   int tm_hour;
   int tm_mday;
   int tm_mon;
   int tm_year;
   int tm_wday;
   int tm_yday;
   int tm_isdst;
};


*/

static char weekday[7][3] = {"Sun","Mon","Tue","Wed","Thu","Fri","Sat"};
static char month[12][3] = {"Jan","Feb","Mar","Apr","May","Jun","Jul","Aug","Sep","Oct","Nov","Dec"};

char *myasctime(const struct tm *timeptr){

  static char result[26];

  sprintf(result, "%.3s", weekday[(*timeptr).tm_wday]);
  sprintf(result, "%s %.3s", result, month[(*timeptr).tm_mon]);
  sprintf(result, "%s  %d %.2d:%.2d:%.2d %d\n", result, (*timeptr).tm_mday, (*timeptr).tm_hour, (*timeptr).tm_min, (*timeptr).tm_sec, (*timeptr).tm_year+1900);

  return result;
  
}

int main(){

  struct tm t;

  //lets just put in some arbitrary values here
  //to get some time

  //this date will actually be july 4, 2000
  t.tm_sec=10;
  t.tm_min=10;
  t.tm_hour=6;
  t.tm_mday=4;
  t.tm_mon=6;
  t.tm_year=100;
  t.tm_wday=5;
  t.tm_yday=200;

  printf("myasctime generated time: %s\n", myasctime(&t));

  return 0;

}
