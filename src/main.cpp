#include <chrono>
#include <thread>
#include <iostream>
#include "Logger/logger.h"

int main(int argc, char *argv[]) {
	 bool crash = false;
   Logger::configureLogger(argv);
	 Logger::startMessage();

   while (true) {
		 try {
			 // holds the app awake, but only keeps "heart beat"
			 std::this_thread::sleep_for(std::chrono::seconds(10));
			 Logger::get()->heartBeat();
		 }
		 catch (const std::exception& ex) {
			 Logger::get()->fatal(std::string(ex.what()));
			 crash = true;
		 }
   }
   
   return crash;
}
