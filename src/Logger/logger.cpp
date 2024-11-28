#include "logger.h"
#include <glog/logging.h>
#include <iostream>

Logger* Logger::get() {
	static Logger logger;

	return &logger;
}

void Logger::startMessage() {
	std::cout << "Starting APOD API server" << std::endl;
}

void Logger::configureLogger(char* argv[]) {
	google::InitGoogleLogging(argv[0]);
	google::InstallFailureSignalHandler();
	google::SetLogDestination(google::GLOG_INFO, "Log_");
	google::SetLogFilenameExtension(".log");

	FLAGS_alsologtostderr = true;
	FLAGS_colorlogtostderr = true;
	FLAGS_timestamp_in_logfile_name = true;
	FLAGS_logfile_mode = 0644;
}

void Logger::info(std::string& message) {
	LOG(INFO) << message;
}

void Logger::warning(std::string& message) {
	LOG(WARNING) << message;
}

void Logger::error(std::string& message) {
	LOG(ERROR) << message;
}

void Logger::fatal(std::string& message) {
	LOG(FATAL) << message << " \n";
	google::ShutdownGoogleLogging();
}

void Logger::heartBeat() {
	std::cout << "Beep..." << std::endl;
}


