#pragma config(I2C_Usage, I2C1, i2cSensors)
#pragma config(Sensor, dgtl1,  Button1,        sensorTouch)
#pragma config(Sensor, dgtl2,  Button2,        sensorTouch)
#pragma config(Sensor, dgtl12, ArmPotent,      sensorNone)
#pragma config(Sensor, I2C_1,  ,               sensorQuadEncoderOnI2CPort,    , AutoAssign )
#pragma config(Motor,  port1,           LeftMotor,     tmotorVex393_HBridge, openLoop, reversed, encoderPort, I2C_1)
#pragma config(Motor,  port6,           Arm,           tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port10,          RightMotor,    tmotorVex393_HBridge, openLoop, driveRight)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

bool button1_pushed;
bool button2_pushed;

//check for buttons////////////////////////
void monitorInput()
{
	if(SensorValue(Button1))
	{
		button1_pushed = true;
	}

	if(SensorValue(Button2))
	{
		button2_pushed = true;
	}
}
//end of check for buttons/////////////////////

task main()
{
nMotorEncoder[LeftMotor] = 0;

//robot moves 1 m straight
//button 2 pushed
//robot moves 90 degrees
//button 3 pushed
//rotate the arm

//states
enum T_StopOrRun_state {
		BOTH_STOP = 0,
		BOTH_RUNNING,
		TURN_RIGHT,
		TURN_LEFT

	};

	T_StopOrRun_state StopOrRun_state = BOTH_STOP;

	while(true)
	{
		/// IS button 1 pushed
		monitorInput(); // This function updates the button1_pushed and button2_pushed flags.
		// Switch the states.
		switch(StopOrRun_state) {

			// Code for BOTH_STOP state:
		case BOTH_STOP:
			// Turn motor off.

		  motor[RightMotor] = 0;
			motor[LeftMotor] = 0;


			if ( button1_pushed ) {
				// If button1 pushed, change to the MOTOR_RUNNING state.
				StopOrRun_state = BOTH_RUNNING;
				// Clear flag to indicate button 1 processed.
				button1_pushed = false;
			}//enf of if

			if (button2_pushed) {
				// If button 2 pushed, transition to MOTOR_STOP state.
				StopOrRun_state = TURN_RIGHT;
				// Clear flag to indicate that button 2 processed.
				button2_pushed = false;
			}//end of if

			break;

		case BOTH_RUNNING:
			// Turn motor on.

			while (nMotorEncoder[LeftMotor] < 2000 && nMotorEncoder[RightMotor] > -2000){
			motor[LeftMotor] = 40;
			motor[RightMotor] = 50;
			}//end of while

			motor[LeftMotor] = 0;
			motor[RightMotor] = 0;


			if (button2_pushed) {
				// If button 2 pushed, transition to MOTOR_STOP state.
				StopOrRun_state = TURN_RIGHT;
				// Clear flag to indicate that button 2 processed.
				button2_pushed = false;
			}//end of if

			break;


		case TURN_RIGHT:
			motor[RightMotor] = 0;
			motor[RightMotor] = 0;

			while (nMotorEncoder[LeftMotor] < 470 && nMotorEncoder[LeftMotor]>-470){
			motor[LeftMotor] = 50;
			motor[RightMotor] = -50;
			}//end of while

			motor[LeftMotor] = 0;

			break;

		default:
		}

	}//end while

}
