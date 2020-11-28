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

bool data_ready = true;
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t  condvar = PTHREAD_COND_INITIALIZER;

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
	string cellData;
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
	int arrayIndex = 0;

	while(true){
		pthread_mutex_lock(&mutex); //Lock mutex
		while(!data_ready){ //Waits for CPU to be available
			pthread_cond_wait (&condvar, &mutex);
		}
		data_ready = false; //Blocks threads
		fieldValue = GetExcelData(myClock,excelColumn); //Gets the data from excel file
		carPropertyValues[arrayIndex] = fieldValue; //Updates the array value for consumer thread
		pthread_cond_signal (&condvar); //Allow threads waiting on the condition to start
		pthread_mutex_unlock (&mutex); //unlock mutex
		data_ready = true; //Open threads
		usleep(10000); //wait for next period
	}

   return( 0 );
}

void*  RPMThread( void*  arg )
{
	int excelColumn = 12;
	string fieldValue;
	int arrayIndex = 1;
	while(true){
		pthread_mutex_lock(&mutex);
		while(!data_ready){
			pthread_cond_wait (&condvar, &mutex);
		}
		data_ready = false;
		fieldValue = GetExcelData(myClock,excelColumn);
		carPropertyValues[arrayIndex] = fieldValue;
		pthread_cond_signal (&condvar);
		pthread_mutex_unlock (&mutex);
		data_ready = true;
		usleep(500000);
	}

   return( 0 );
}

void*  CoolantTempThread( void*  arg )
{
	int excelColumn = 17;
	string fieldValue;
	int arrayIndex = 2;
	while(true){
		pthread_mutex_lock(&mutex);
		while(!data_ready){
			pthread_cond_wait (&condvar, &mutex);
		}
		data_ready = false;
		fieldValue = GetExcelData(myClock,excelColumn);
		carPropertyValues[arrayIndex] = fieldValue;
		pthread_cond_signal (&condvar);
		pthread_mutex_unlock (&mutex);
		data_ready = true;
		usleep(2000000);
	}

   return( 0 );
}

void*  GearThread( void*  arg )
{
	int excelColumn = 33;
	string fieldValue;
	int arrayIndex = 3;
	while(true){
		pthread_mutex_lock(&mutex);
		while(!data_ready){
			pthread_cond_wait (&condvar, &mutex);
		}
		data_ready = false;
		fieldValue = GetExcelData(myClock,excelColumn);
		carPropertyValues[arrayIndex] = fieldValue;
		pthread_cond_signal (&condvar);
		pthread_mutex_unlock (&mutex);
		data_ready = true;
		usleep(100000);
	}

   return( 0 );
}

void*  TransmissionOilTempThread( void*  arg )
{
	int excelColumn = 34;
	string fieldValue;
	int arrayIndex = 4;
	while(true){
		pthread_mutex_lock(&mutex);
		while(!data_ready){
			pthread_cond_wait (&condvar, &mutex);
		}
		data_ready = false;
		fieldValue = GetExcelData(myClock,excelColumn);
		carPropertyValues[arrayIndex] = fieldValue;
		pthread_cond_signal (&condvar);
		pthread_mutex_unlock (&mutex);
		data_ready = true;
		usleep(5000000);
	}

   return( 0 );
}

void*  SpeedThread( void*  arg )
{
	int excelColumn = 43;
	string fieldValue;
	int arrayIndex = 5;
	while(true){
		pthread_mutex_lock(&mutex);
		while(!data_ready){
			pthread_cond_wait (&condvar, &mutex);
		}
		data_ready = false;
		fieldValue = GetExcelData(myClock,excelColumn);
		carPropertyValues[arrayIndex] = fieldValue;
		pthread_cond_signal (&condvar);
		pthread_mutex_unlock (&mutex);
		data_ready = true;
		usleep(100000);
	}

   return( 0 );
}

void*  AccelerationThread( void*  arg )
{
	int excelColumn = 44;
	string fieldValue;
	int arrayIndex = 6;
	while(true){
		pthread_mutex_lock(&mutex);
		while(!data_ready){
			pthread_cond_wait (&condvar, &mutex);
		}
		data_ready = false;
		fieldValue = GetExcelData(myClock,excelColumn);
		carPropertyValues[arrayIndex] = fieldValue;
		pthread_cond_signal (&condvar);
		pthread_mutex_unlock (&mutex);
		data_ready = true;
		usleep(150000);
	}

   return( 0 );
}

void*  BreakSwitchThread( void*  arg )
{
	int excelColumn = 45;
	string fieldValue;
	int arrayIndex = 7;
	while(true){
		pthread_mutex_lock(&mutex);
		while(!data_ready){
			pthread_cond_wait (&condvar, &mutex);
		}
		data_ready = false;
		fieldValue = GetExcelData(myClock,excelColumn);
		carPropertyValues[arrayIndex] = fieldValue;
		pthread_cond_signal (&condvar);
		pthread_mutex_unlock (&mutex);
		data_ready = true;
		usleep(100000);
	}

   return( 0 );
}


void* ConsumerThread(void* arg){

	string carProperties[8] = {"Fuel Consumption: ", "RPM: ", "Coolant Temp: ", "Gear: ",
			"Transmission Oil Temp: ", "Speed: ", "Acceleration: ", "Break Switch: "};

	int consumerPeriod = 5 * 1000000; // set the period in seconds
	while(true){
		pthread_mutex_lock (&mutex); //Lock mutex
		while(!data_ready){ //Waits for CPU to be available
			pthread_cond_wait (&condvar, &mutex);
		}
		data_ready = false;//Block threads
		//Print function
		cout <<"Reading out values" << endl;
		for(int i = 0 ; i < 8 ; i++){
			cout<<"CURRENT TIME: " << myClock << "......" << carProperties[i]<<
			carPropertyValues[i] << endl;
		}
		cout <<endl;
        pthread_cond_signal (&condvar);//Allow threads waiting on the condition to start
        pthread_mutex_unlock (&mutex);//unlock mutex
        data_ready = true;//unblock threads
		usleep(consumerPeriod); //Period for consumer thread
	}

}


int main( void )
{


	//Initializers
   pthread_attr_t attr;
   pthread_attr_init( &attr );
   pthread_attr_setdetachstate(
      &attr, PTHREAD_CREATE_DETACHED );

   //Producer Threads
   pthread_t joinThread;
   pthread_create( NULL, &attr, &FuelConsumptionThread, NULL );
   pthread_create( NULL, &attr, &RPMThread, NULL );
   pthread_create( NULL, &attr, &CoolantTempThread, NULL );
   pthread_create( NULL, &attr, &GearThread, NULL );
   pthread_create( NULL, &attr, &TransmissionOilTempThread, NULL );
   pthread_create( NULL, &attr, &SpeedThread, NULL );
   pthread_create( NULL, &attr, &AccelerationThread, NULL );
   pthread_create( NULL, &attr, &BreakSwitchThread, NULL );

   //Consumer Thread
   pthread_create( NULL, &attr, &ConsumerThread, NULL );

   printf( "Clock Starting \n");

   //Increase system time by 1 second
   while(true){
	   usleep(1000000);
	   myClock++;
   }
   pthread_join(joinThread, NULL);


   return EXIT_SUCCESS;
}
