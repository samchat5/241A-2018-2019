#pragma config(Sensor, in1,    powerex,        sensorAnalog)
#pragma config(Sensor, in2,    Poten,          sensorPotentiometer)
#pragma config(Sensor, in3,    gyro,           sensorGyro)
#pragma config(Sensor, in4,    ClawPoten,      sensorPotentiometer)
#pragma config(Sensor, dgtl1,  REncoder,       sensorQuadEncoder)
#pragma config(Sensor, dgtl3,  LEncoder,       sensorQuadEncoder)
#pragma config(Motor,  port2,           R1,            tmotorVex393_MC29, openLoop, reversed, encoderPort, None)
#pragma config(Motor,  port3,           R2,            tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port4,           L1,            tmotorVex393_MC29, openLoop, encoderPort, None)
#pragma config(Motor,  port5,           L2,            tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port6,           Tower1,        tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port7,           Tower2,        tmotorVex393_MC29, openLoop, reversed)
#pragma config(Motor,  port8,           Claw,          tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port9,           launcher,      tmotorVex393_MC29, openLoop)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

#define vexCompetitionState (nVexRCReceiveState & (vrDisabled | vrAutonomousMode))
#pragma competitionControl(Competition)
#pragma autonomousDuration(15)
#pragma userControlDuration(150)
#include "VEX_Competition_Includes.c"

float in = 360/(3.14159265358979*4);

void moveBack(int ticks){
	SensorValue[REncoder] = 0;
	SensorValue[LEncoder] = 0;
	while(SensorValue[LEncoder] <= ticks && SensorValue[REncoder] <= ticks){
		if(SensorValue[LEncoder] <= ticks){
			motor[L1] = -127;
			motor[L2] = -127;
		}
		if(SensorValue[REncoder] <= ticks){
			motor[R1] = -127;
			motor[R2] = -127;
		}
	}
	motor[L1] = 0;
	motor[L2] = 0;
	motor[R1] = 0;
	motor[R2] = 0;
}
void move(int ticks){
	SensorValue[REncoder] = 0;
	SensorValue[LEncoder] = 0;
	while(SensorValue[LEncoder] >= -1*ticks && SensorValue[REncoder] >= -1*ticks){
		if(SensorValue[LEncoder] >= -1*ticks){
			motor[L1] = 127;
			motor[L2] = 127;
		}
		if(SensorValue[REncoder] >= -1*ticks){
			motor[R1] = 127;
			motor[R2] = 127;
		}
	}
	motor[L1] = 0;
	motor[L2] = 0;
	motor[R1] = 0;
	motor[R2] = 0;
}
void spinRight(int deg10){
	SensorValue[gyro] = 0;
	while(abs(SensorValue[gyro]) < deg10){
		motor[L1] = 100;
		motor[L2] = 100;
	}
	motor[L1] = 0;
	motor[L2] = 0;
}
void shoot(){
	motor[launcher] = 127;
	wait1Msec(4000);
	motor[launcher] = 0;
}
void pre_auton(){
}
task autonomous ()
{
	wait1Msec(1200);
	moveBack(37*in);
	shoot();

}
task usercontrol()
{
	//This whole block is dedicated to displaying the Battery Voltage on the LCD Display
	bLCDBacklight = true;									// Turn on LCD Backlight
	string mainBattery;
	string secondaryBattery;
	clearLCDLine(0);											// Clear line 1 (0) of the LCD
	clearLCDLine(1);											// Clear line 2 (1) of the LCD

	//Display the Primary Robot battery voltage
	displayLCDString(0, 0, "Primary: ");
	sprintf(mainBattery, "%1.2f%c", nImmediateBatteryLevel/1000.0,'V'); //Build the value to be displayed
	displayNextLCDString(mainBattery);

	//Display the Secondary Robot battery voltage
	displayLCDString(1, 0, "Secondary: ");
	sprintf(secondaryBattery, "%1.2f%c", SensorValue(powerex)/275, 'V');
	displayNextLCDString(secondaryBattery);

	//Short delay for the LCD refresh rate
	wait1Msec(100);

	while (1==1){
		//Right joystick controls right wheels
		motor[R1] = vexRT[Ch2]*0.5;
		motor[R2] = vexRT[Ch2]*0.5;
		//Left joystick controls left wheels
		motor[L1] = vexRT[Ch3]*0.5;
    motor[L2] = vexRT[Ch3]*0.5;

		//Sending 50% power to prevent overheating in the motors

    if(vexRT[Btn5U] && SensorValue[Poten] < 2000){
    		motor[Tower1] = 100;
  			motor[Tower2] = 100;
  	}
   	else if(vexRT[Btn6U] && SensorValue[Poten] > 250){
   		motor[Tower1] = -100;
    	motor[Tower2] = -100;
  	}
    else{
    	motor[Tower1] = 0;
    	motor[Tower2] = 0;
    }
  	if(vexRT[Btn7U]){
  		motor[Claw] = 127;
  	}
  	else{
  		motor[Claw] = 0;
  	}
		if(vexRT[Btn8U] && SensorValue[ClawPoten] < 1350){
				motor[Claw] = -127;
		}
		else if(vexRT[Btn7D]){
  		motor[Claw] = 127;
  	}
		else{
			motor[Claw] = 0;
		}
		if(vexRT[Btn8D]){
			startTask(autonomous);
			wait1Msec(6000);
			stopTask(autonomous);
		}
		/* press the bottom button of the right buttons to
		start the autonomous*/
	}
}
