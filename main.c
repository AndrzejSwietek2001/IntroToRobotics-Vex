#pragma config(Sensor, dgtl1,  encoderARM,     sensorQuadEncoder)
#pragma config(Motor,  port1,           motorLEFT,     tmotorVex393_HBridge, openLoop)
#pragma config(Motor,  port2,           motorCLAW,     tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port3,           motorARM,      tmotorVex269_MC29, openLoop)
#pragma config(Motor,  port4,           motorFOOT,     tmotorVex269_MC29, openLoop)
#pragma config(Motor,  port5,           motorEXTENTION, tmotorVex269_MC29, openLoop)
#pragma config(Motor,  port6,           motorLEFT_SHOOTER, tmotorVex269_MC29, openLoop)
#pragma config(Motor,  port7,           motorRIGHT_SHOOTER, tmotorVex269_MC29, openLoop)
#pragma config(Motor,  port8,           motoreMOVE_SHOOTER, tmotorVex269_MC29, openLoop)
#pragma config(Motor,  port9,           motorROTATE,   tmotorVex269_MC29, openLoop)
#pragma config(Motor,  port10,          motorRIGHT,    tmotorVex393_HBridge, openLoop)


/*------------------------------ AUTHOR ANDRZEJ SWIETEK -----------------------------*/
#define MAXacc 2
#define MINacc 0.5

enum constants{
	STANDART_SPEED = 90,
	EXTENTION_ARM_ENCODER_TICKS = 360,
	TIME_GRIPPER = 1000,
	REV_TIME_SHOOTER = 1000,
	CATCH_BACK_TIME = 1000,
	ARM_HEIGHT_TIME = 1000


};
//ENCODER 360 TICKS = 1 rotation
bool stopkaKlikniety = false;
bool extentionArmKlikniety = false;
float moznikPrzyspieszenia=1;

void extend()
{
	while(SensorValue[dgtl1]< EXTENTION_ARM_ENCODER_TICKS)
	{
		motor[motorEXTENTION]=STANDART_SPEED;
	}
}

void retract()
{
	while(SensorValue[dgtl1] < -EXTENTION_ARM_ENCODER_TICKS)
	{
		motor[motorEXTENTION] = -STANDART_SPEED;
	}
}
void footDown()
{
					while(vexRT[Btn5U]==1) //wykonaj komende positive direction
					{
							motor[motorFOOT]=STANDART_SPEED;
							if (vexRT[Btn5U]==0){break;}
					}
					while(vexRT[Btn5U]==0) 
					{
							motor[motorFOOT]=0;
							if (vexRT[Btn5U]==1){break;}
					}
}



void footUp()
{
					while(vexRT[Btn5D]==1) //wykonaj komende negative direction
					{
							motor[motorFOOT]=-STANDART_SPEED;
							if (vexRT[Btn5D]==0){break;}
					}
					while(vexRT[Btn5D]==0) //nie wykonuj nic
					{
							motor[motorFOOT]=0;
							if (vexRT[Btn5D]==0){break;}
					}
}

void moveARM()
{
		
				if(vexRT[Btn7U]==1)
				{
					motor[port3]=STANDART_SPEED;
		 		}

		  		else if(vexRT[Btn7D]==1)//blad
				{
					motor[port3]=-STANDART_SPEED;
		  		}
		  		else
		  		{
		  			motor[port3]=0;
		  		}
}

void speedUp()
{
				if(vexRT[Btn6U]==1)
				{
					moznikPrzyspieszenia=MAXacc;
				}

				  else if(vexRT[Btn6D]==1)
				{
					moznikPrzyspieszenia=MINacc;
				}
				else
				  {
				  	moznikPrzyspieszenia=1;
				  }
}

task main()
{
	
  			motor[motorLEFT]=vexRT[Ch2];//tylko lewy ale do innego programu
  			motor[motorRIGHT]=vexRT[Ch3];//tylko prawya ale do innego prigramu tu nie przeszkadza
	while(true)
	{
//Przyspieszenie
	if(vexRT[Btn6U]==1 || vexRT[Btn6D]==1)
	{
		speedUp();
	}
			int lewy=(getJoystickValue(Ch2) + getJoystickValue(Ch3))/2;
			int prawy = (getJoystickValue(Ch2) - getJoystickValue(Ch3))/2;
			motor[motorLEFT]=lewy*moznikPrzyspieszenia;
			motor[motorRIGHT]=prawy*moznikPrzyspieszenia;


//ARM
	if(vexRT[Btn7U]==1 || vexRT[Btn7D]==1)
	{
		moveARM();
		wait1Msec(ARM_HEIGHT_TIME);
	}	
				

//CLAW
	if(vexRT[Btn7L]==1)
	{
		motor[motorCLAW]=STANDART_SPEED;
	}

		else if(vexRT[Btn7R]==1)
		{
			motor[motorCLAW]=-STANDART_SPEED;
		}
		else
		{
			motor[motorCLAW]=0;
		}
//stopka do gory
	if(vexRT[Btn5D]==1)
	{
		footUp();
	}
//stopka w dol		
	if(vexRT[Btn5U]==1)
	{	
		footDown();
	}		
//wydluz ramie			
	if(vexRT[Btn8R]==1)
	{
		extend();	
	}
//skroc ramie		
	else if(vexRT[Btn8D]==1)
	{
		retract();	
	}
// 	else
// 	{
// 		continue;
// 	}
			

			



}//loop










}//The end of the program
