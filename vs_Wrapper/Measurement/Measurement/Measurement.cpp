#include <iostream>
#include <stdio.h>
#include "C:\Program Files\IVI Foundation\VISA\Win64\Include\visa.h"
#include <vector>
#include <sstream>
#include <chrono>



using namespace std;

//Sends commands to the instrument
void sendCommand(ViSession vi, const std::string& cmd) {
	ViUInt32 retCount;
	viWrite(vi, (ViBuf)cmd.c_str(), cmd.size(), &retCount);
}

//sends commands to the instrument
// Reads response in a loop if response > 1kB
// Stops when reading termination character \n
std::string queryCommand(ViSession vi, const std::string& cmd) {
	ViChar buffer[1024]{}; //Read 1kB every cycle
	ViUInt32 retCount;
	sendCommand(vi, cmd);
	viRead(vi, (ViBuf)buffer, sizeof(buffer), &retCount);
	string currentChars = std::string(buffer, retCount);
	string response = currentChars;
	while (currentChars.find('\n') == string::npos) {
		viRead(vi, (ViBuf)buffer, sizeof(buffer), &retCount);
		currentChars = std::string(buffer, retCount);
		response += currentChars;
	}
	return response;
}

//checks for Errors on the SCPI Server and prints the error queue
void checkError(ViSession vi, string when) {
	string error = queryCommand(vi, ":SYST:ERR?\n");
	cout << when << endl << error << endl;
}

//Transform measurement data to float arrays
std::vector<float> parseResults(const std::string& data) {
	std::vector<float> results;
	std::istringstream ss(data);
	std::string token;
	while (getline(ss, token, ',')) {
		results.push_back(std::stof(token));
	}
	return results;
}

int main() {

	auto start = chrono::high_resolution_clock::now();

	// Edit this to your address
	ViConstRsrc resource_name = "TCPIP0::172.22.44.19::5025::SOCKET";

	//Adjust these values
	int numOfPoints = 201;
	string startfreq = "10kHz";
	string stopfreq = "10MAHz";
	string bandwidth = "300Hz";

	cout << "Trying to connect to Visa resource " << resource_name << "\n";

	//open a visa session and
	//enable termination character and set it to '\n'
	//set desired timeout
	ViSession rm, vi;
	ViStatus status = viOpenDefaultRM(&rm);
	status = viOpen(rm, resource_name, VI_NULL, VI_NULL, &vi);
	viSetAttribute(vi, VI_ATTR_TERMCHAR_EN, VI_TRUE);
	viSetAttribute(vi, VI_ATTR_TERMCHAR, '\n');
	viSetAttribute(vi, VI_ATTR_TMO_VALUE, 4000);

	//get id of the SCPI Server
	char command[] = "*IDN?";
	string id = queryCommand(vi, command);
	cout << "SCPI client connected to SCPI Server: " << id << endl;

	//Trying to lock the Bode device
	string lockOK = queryCommand(vi, ":SYST:LOCK:REQ?\n");
	cout << "lock status: " << lockOK << endl;

	//Reset the device
	sendCommand(vi, "*CLS\n");
	sendCommand(vi, "*RST\n");
	queryCommand(vi, "*OPC?\n");
	sendCommand(vi, "*ESE 255\n"); //enable errorchecking
	checkError(vi, "After reset:"); //check for errors after resets

	//configure the sweep
	sendCommand(vi, ":CALC:PAR:DEF Z\n"); //one port impedance measurement
	queryCommand(vi, "*OPC?\n");
	sendCommand(vi, ":SENS:FREQ:STAR" + startfreq + "\n"); //start frequency 10kHz
	sendCommand(vi, ":SENS:FREQ:STOP" + stopfreq + "\n"); //stop frequency 10MHz
	sendCommand(vi, ":SENS:SWE:POIN " + to_string(numOfPoints) + "\n"); //201 points
	sendCommand(vi, ":SENS:SWE:TYPE LOG\n"); //logarithmic sweep
	sendCommand(vi, ":SENS:BAND" + bandwidth + "\n");
	checkError(vi, "After freq definition:"); //check for errors after sweep config

	//Estimate measurement duration
	string time = queryCommand(vi, ":SENS:SWE:TIME?");
	cout << "Time needed for the Measurement: " << time << "seconds" << endl;

	//Trigger config
	sendCommand(vi, ":CALC:FORM SLIN\n"); //linear magnitude and phase
	sendCommand(vi, ":TRIG:SOUR BUS\n"); //Bus as trigger source
	sendCommand(vi, ":INIT\n"); //initialize the trigger
	sendCommand(vi, ":TRIG:SING\n"); //trigger a single measurement
	checkError(vi, "after trig config: "); //check for errors after trigger congfig

	//Wait for all operations to finish
	string opc = queryCommand(vi, "*OPC?\n");
	cout << "opc status: " << opc << endl;

	//Read the frequency values
	string frequencies = queryCommand(vi, ":SENS:FREQ:DATA?\n");
	checkError(vi, "after freq data: ");

	//Read the measurement data
	string allResults = queryCommand(vi, ":CALC:DATA:SDAT?\n");
	checkError(vi, "after meas data: ");

	cout << "results: " << endl << allResults << endl;
	cout << "frequencies :" << endl << frequencies << endl;

	//Transform values to readable arrays
	std::vector<float> magnitude_phase = parseResults(allResults);
	std::vector<float> freqValues = parseResults(frequencies);

	//Example print of the first measurement point
	cout << "Frequency: " << freqValues[0] << "Hz\t"
		<< "Magnitude: " << magnitude_phase[0] << "Ohms\t"
		<< "Phase: " << magnitude_phase[201] << "deg" << endl;

	//Trying to release the Bode device
	string relok = queryCommand(vi, ":SYST:LOCK:REL?\n");
	cout << "release status: " << relok << endl;

	//Close visa session
	viClose(vi);
	viClose(rm);

	auto end = chrono::high_resolution_clock::now();

	auto duration = chrono::duration_cast<chrono::milliseconds>(end - start);

	cout << "Measurement complete. Took " << duration.count() << " milliseconds"
		<< endl;

	return 0;
}