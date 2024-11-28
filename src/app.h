#ifndef app_class
#define app_class

#include "Logger/logger.h"
#include "oatpp/core/macro/component.hpp"
#include "oatpp/core/base/Environment.hpp"
#include "oatpp/network/Server.hpp"
#include "oatpp/network/tcp/server/ConnectionProvider.hpp"
#include "oatpp/web/server/AsyncHttpConnectionHandler.hpp"


class App {
private:
	// Logging
	void configureLogger(char* argv[]);
	
	// --- threading ---

	void configThread();
	void startThread();

	// --- Executing ---
	void start();
	static void idle();

protected:
	Logger* logger{ nullptr };

public:
	explicit App(char* argv[] = (char) 0);
	~App() = default;
	virtual void run(char* argv[]);
	static void end();
};
#endif // !app_class
