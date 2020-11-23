#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

int myClock = 1;

using namespace std;
string carPropertyValues[7];


vector<string> split(string str){

	vector<string> array;
	stringstream ss(str);
	string temp;

	  while(getline(ss, temp, ',')) {
	    array.push_back(temp);
	  }
	  return array;
}


string GetExcelData(int row, int column){
	ifstream csvFile("/root/DrivingData.csv");
	string lineText;
	string cellData = "NOT GOOD";
	if(csvFile){

		while(getline(csvFile,lineText) && (row > 0)){
			row--;
		}

		if(row == 0){
			vector<string> array = split(lineText);
			cellData = array[column];
		}
	}

	return cellData;
}

void*  FuelConsumptionThread( void*  arg )
{
	int excelColumn = 0;
	string fieldValue;

	while(true){
		fieldValue = GetExcelData(myClock,excelColumn);
		carPropertyValues[0] = fieldValue;
//		cout << "CURRENT TIME:" << myClock << "...... Fuel Consumption: "<< carPropertyValues[0] << endl;
		usleep(10000);
	}

   return( 0 );
}

void*  RPMThread( void*  arg )
{
	int excelColumn = 12;
	string fieldValue;
	while(true){
		fieldValue = GetExcelData(myClock,excelColumn);
		carPropertyValues[1] = fieldValue;
		//cout << "CURRENT TIME:" << myClock << "...... RPM: "<< carPropertyValues[1] << endl;
		usleep(500000);
	}

   return( 0 );
}

void*  CoolantTempThread( void*  arg )
{
	int excelColumn = 17;
	string fieldValue;
	while(true){
		fieldValue = GetExcelData(myClock,excelColumn);
		carPropertyValues[2] = fieldValue;
		//cout << "CURRENT TIME:" << myClock << "...... Coolant Temp: "<< carPropertyValues[2] << endl;
		   usleep(2000000);
	}

   return( 0 );
}

void*  GearThread( void*  arg )
{
	int excelColumn = 33;
	string fieldValue;
	while(true){
		fieldValue = GetExcelData(myClock,excelColumn);
		carPropertyValues[3] = fieldValue;
		//cout << "CURRENT TIME:" << myClock << "...... Current Gear: "<< carPropertyValues[3]  << endl;
		   usleep(100000);
	}

   return( 0 );
}

void*  TransmissionOilTempThread( void*  arg )
{
	int excelColumn = 34;
	string fieldValue;
	while(true){
		fieldValue = GetExcelData(myClock,excelColumn);
		carPropertyValues[4] = fieldValue;
		//cout << "CURRENT TIME:" << myClock << "...... Transmission Oil Temp: "<< carPropertyValues[4] << endl;
		   usleep(5000000);
	}

   return( 0 );
}

void*  SpeedThread( void*  arg )
{
	int excelColumn = 43;
	string fieldValue;
	while(true){
		fieldValue = GetExcelData(myClock,excelColumn);
		carPropertyValues[5] = fieldValue;
		//cout << "CURRENT TIME:" << myClock << "...... Current Speed: "<< carPropertyValues[5] << endl;
		   usleep(100000);
	}

   return( 0 );
}

void*  AccelerationThread( void*  arg )
{
	int excelColumn = 44;
	string fieldValue;
	while(true){
		fieldValue = GetExcelData(myClock,excelColumn);
		carPropertyValues[6] = fieldValue;
		//cout << "CURRENT TIME:" << myClock << "...... Acceleration: "<< carPropertyValues[6] << endl;
		   usleep(150000);
	}

   return( 0 );
}

void*  BreakSwitchThread( void*  arg )
{
	int excelColumn = 45;
	string fieldValue;
	while(true){
		fieldValue = GetExcelData(myClock,excelColumn);
		carPropertyValues[7] = fieldValue;
		//cout << "CURRENT TIME:" << myClock << "...... Break Switch: "<< carPropertyValues[7] << endl;
		   usleep(100000);
	}

   return( 0 );
}


void* DisplayThread(void* arg){

	string carProperties[8] = {"Fuel Consumption: ", "RPM: ", "Coolant Temp: ", "Gear: ",
			"Transmission Oil Temp: ", "Speed: ", "Acceleration: ", "Break Switch: "};

	while(true){

		cout <<"Reading out values" << endl;
		for(int i = 0 ; i < 8 ; i++){
			cout<<"CURRENT TIME: " << myClock << "......" << carProperties[i]<<
			carPropertyValues[i] << endl;
		}
		cout <<endl;
		usleep(3000000);
	}




}


int main( void )
{


   pthread_attr_t attr;

   pthread_attr_init( &attr );
   pthread_attr_setdetachstate(
      &attr, PTHREAD_CREATE_DETACHED );

   pthread_t joinThread;
   pthread_create( NULL, &attr, &FuelConsumptionThread, NULL );
   pthread_create( NULL, &attr, &RPMThread, NULL );
   pthread_create( NULL, &attr, &CoolantTempThread, NULL );
   pthread_create( NULL, &attr, &GearThread, NULL );
   pthread_create( NULL, &attr, &TransmissionOilTempThread, NULL );
   pthread_create( NULL, &attr, &SpeedThread, NULL );
   pthread_create( NULL, &attr, &AccelerationThread, NULL );
   pthread_create( NULL, &attr, &BreakSwitchThread, NULL );
   pthread_create( NULL, &attr, &DisplayThread, NULL );

   printf( "Clock Starting \n");
   /* Allow threads to run. */
   while(true){
//	   printf( "Clock time: %d \n", myClock );
	   usleep(1000000);
	   myClock++;
   }
   pthread_join(joinThread, NULL);


   return EXIT_SUCCESS;
}

