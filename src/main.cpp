#include "calendarApp.h"

int main(){
	CalendarApp calendar;
	bool need_to_stop;
	while (true){
		need_to_stop = calendar.process_request();
		if (need_to_stop){
			break;
		}
	}
	return 0;
}

