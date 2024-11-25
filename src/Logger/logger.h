#ifndef logger_class
#define logger_class

#include <string>

class Logger {
public:
	static Logger* get();
	static void startMessage();
	static void configureLogger(char* argv[]);
	void info(std::string& message);
	void warning(std::string& message);
	void error(std::string& message);
	void fatal(std::string& message);
	void heartBeat();
};
#endif // !logger_class
