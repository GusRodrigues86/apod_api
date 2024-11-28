#include <chrono>
#include <thread>
#include <iostream>
#include <sstream>

#include "app.h"
#include <server_components.hpp>

App::App(char* argv[]) {
	this->run(argv);
}

void App::run(char* argv[]) {
	configureLogger(argv);
	configThread();
	start();
	idle();
}

void App::end() {
	oatpp::base::Environment::destroy();
}

void App::configureLogger(char* argv[]) {
	Logger::configureLogger(argv);
	Logger::startMessage();
	logger = Logger::get();
}

void App::configThread() {
	std::string start = "configuring thread";
	std::string end = "configuring thread finished";
	logger->info(start);
	std::thread t = std::thread([this] {
		startThread();
		});
	logger->info(end);

	t.detach();
}

void App::startThread() {
	while (true) {
		try {
			std::this_thread::sleep_for(std::chrono::seconds(10));
		}
		catch (...) {
		}
	}
}

void App::start() {
	std::thread([] {
	ServerComponents components;
	Logger* log = Logger::get();

	oatpp::network::Server server(
		components.serverConnectionProvider.getObject(),
		components.serverConnectionHandler.getObject() //
	);

	/* Print info about server port */
	auto serverProvider = components.serverConnectionProvider.getObject();
	auto host = static_cast<const char*>(serverProvider->getProperty("host").getData());
	auto port = static_cast<const char*>(serverProvider->getProperty("port").getData());

	std::ostringstream sWelcome;
	sWelcome << "APOD API Server running on " << host << ":" << port << std::endl;
	log->info(sWelcome.str());

	/* Run server */
		server.run();
		
		}).detach();
}

void App::idle() {
	while (true) {
		// holds the app awake, but only keeps "heart beat i.e. BEEP"
		std::this_thread::sleep_for(std::chrono::seconds(5));
		Logger::get()->heartBeat();
	}
}

int main(int argc, char* argv[]) {
	bool crash = false;
	App* app{ nullptr };


	oatpp::base::Environment::init();

	while (true) {
		try {
			app = new App(argv);
		}
		catch (const std::exception& ex) {
			Logger::get()->fatal(std::string(ex.what()));
			crash = true;
		}
	}

	App::end();

	return crash;
}