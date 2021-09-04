#pragma once

#define STATUS_DOOR_OPEN 2
#define STATUS_DOOR_CLOSE 3
#define STATUS_DOOR_OPENING 0
#define STATUS_DOOR_CLOSING 1
#define STATUS_DOOR_STOP 4



	#define STATUS_GEAR_EXTEND 2
	#define STATUS_GEAR_EXTENDING 0
	#define STATUS_GEAR_RETRACTED 3
	#define STATUS_GEAR_RETRACTING 1	
	#define STATUS_GEAR_STOP 4


extern int door_status;
extern int gear_status;