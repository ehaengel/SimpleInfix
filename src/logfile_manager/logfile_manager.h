#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <time.h>

#include <vector>
#include <string>
using namespace std;

#ifndef LOGFILE_MANAGER_H
#define LOGFILE_MANAGER_H

class LogFileManager
{
public:
	LogFileManager();
	~LogFileManager();

	////////////////////////
	// Log file functions //
	////////////////////////

	int SaveLogFile();
	int SaveLogFile(string filename);

	int SetFilename(string filename);

	int VerboseModeOn();
	int VerboseModeOff();

	//Log message types
	enum
	{
		NORMAL_MESSAGE = 0,
		ERROR_MESSAGE = 1
	};

	int WriteNormalMessage(string message_source, string message);
	int WriteErrorMessage(string message_source, string message);

	int WriteMessage(int message_type, string message_source, string message);

	/////////////////////////
	// Debugging functions //
	/////////////////////////

	int Print();

private:
	/////////////////////////
	// LogFileManager data //
	/////////////////////////

	string filename;
	int verbose_mode;

	vector<int> log_type_list;
	vector<string> log_time_list;
	vector<string> log_message_source_list;
	vector<string> log_message_list;

};

#endif
