#pragma config(Motor,  port1,           R1,            tmotorVex393_HBridge, openLoop, reversed, encoderPort, None)
#pragma config(Motor,  port2,           R2,            tmotorVex393_HBridge, openLoop, reversed)
#pragma config(Motor,  port3,           L1,            tmotorVex393_HBridge, openLoop, encoderPort, None)
#pragma config(Motor,  port4,           L2,            tmotorVex393_HBridge, openLoop)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

#define vexCompetitionState (nVexRCReceiveState & (vrDisabled | vrAutonomousMode))
#pragma competitionControl(Competition)
#pragma autonomousDuration(15)
#pragma userControlDuration(150)
#include "VEX_Competition_Includes.c"

void pre_auton ()
{
}
task autonomous ()
{
}
task usercontrol()
{
	while (1==1){
		//Right joystick controls right wheels
		motor[R1] = vexRT[Ch2]*0.8;
		motor[R2] = vexRT[Ch2]*0.8;
		//Left joystick controls left wheels
		motor[L1] = vexRT[Ch3]*0.8;
    motor[L2] = vexRT[Ch3]*0.8;

    //Sending 80% power to prevent overheating in the motors

		if(vexRT[Btn8D]){
			startTask(autonomous);
			wait1Msec(15000);
			stopTask(autonomous);
		}
		/* press the bottom button of the right buttons to
		start the autonomous*/
	}
}
