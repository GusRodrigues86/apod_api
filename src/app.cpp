#include <chrono>
#include <thread>
#include <iostream>
#include <sstream>
#include "oatpp/core/macro/component.hpp"
#include "oatpp/core/base/Environment.hpp"
#include "oatpp/network/Server.hpp"
#include "oatpp/network/tcp/server/ConnectionProvider.hpp"
#include "oatpp/web/server/HttpConnectionHandler.hpp"

#include "Logger/logger.h"

void run() {
	/* Create Router for HTTP requests routing */
	auto router = oatpp::web::server::HttpRouter::createShared();

	/* Create HTTP connection handler with router */
	auto connectionHandler = oatpp::web::server::HttpConnectionHandler::createShared(router);

	/* Create TCP connection provider */
	auto connectionProvider = oatpp::network::tcp::server::ConnectionProvider::createShared({ "localhost", 8000, oatpp::network::Address::IP_4 });

	/* Create server which takes provided TCP connections and passes them to HTTP connection handler */
	oatpp::network::Server server(connectionProvider, connectionHandler);

	/* Print info about server port */
	auto host = static_cast<const char*>(connectionProvider->getProperty("host").getData());
	auto port = static_cast<const char*>(connectionProvider->getProperty("port").getData());
	
	std::ostringstream sWelcome;
	sWelcome << "APOD API Server running on " << host << ":" << port << std::endl;
	Logger::get()->info(sWelcome.str());

	/* Run server */
	server.run();
}

int main(int argc, char *argv[]) {
	 bool crash = false;
   Logger::configureLogger(argv);
	 Logger::startMessage();

   oatpp::base::Environment::init();

   while (true) {
		 try {
			 // holds the app awake, but only keeps "heart beat"
       run();
			 std::this_thread::sleep_for(std::chrono::seconds(10));
			 Logger::get()->heartBeat();
		 }
		 catch (const std::exception& ex) {
			 Logger::get()->fatal(std::string(ex.what()));
			 crash = true;
		 }
   }

	 oatpp::base::Environment::destroy();
   
   return crash;
}
