In order to compile, set machine up with a QNX machine.

For our testing purposes, a virtual machine was used 

Place DrivingData.csv inside the QNX virtual machine. 
The directory "/root/DrivingData.csv" was used in our case.
If another directory is used be sure to specify at line 34: ifstream csvFile("/root/DrivingData.csv");

The int "consumerPeriod" at line 238 can be changed in order to change the period of the consumer thread.
This will change the frequency at which the data is being displayed to the user.

Build the project, and then compile in order to have the program execute.
