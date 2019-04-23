#include"head.h"

/* run this program using the console pauser or add your own getch, system("pause") or input loop */

int main(int argc, char** argv) {
	Graphmtx<City,int>  cityTimetable,cityPrice ;
	initializeCity(cityTimetable);
	initializeCity(cityPrice);
	initializeTime(cityTimetable);
	initializePrice(cityPrice);
	cout<<"价格表："<<endl<<cityPrice
	<<"========================================================="<<endl
	<<"时间表："<<endl<<cityTimetable;
	City_user(cityTimetable,cityPrice);
	return 0;
}
