#ifndef serverComponents_class
#define serverComponents_class

#include "oatpp/web/server/AsyncHttpConnectionHandler.hpp"
#include "oatpp/web/server/HttpRouter.hpp"
#include "oatpp/network/tcp/server/ConnectionProvider.hpp"
#include "oatpp/parser/json/mapping/ObjectMapper.hpp"
#include "oatpp/core/macro/component.hpp"

class ServerComponents {
public:

	/**
	 * Create Async Executor
	 */
	OATPP_CREATE_COMPONENT(std::shared_ptr<oatpp::async::Executor>, executor)([] {
		return std::make_shared<oatpp::async::Executor>(
			4 /* Data-Processing threads */,
			1 /* I/O threads */,
			1 /* Timer threads */
		);
		}());

	/**
	 *  Create ConnectionProvider component which listens on the port
	 */
	OATPP_CREATE_COMPONENT(std::shared_ptr<oatpp::network::ServerConnectionProvider>, serverConnectionProvider)([] {
		return oatpp::network::tcp::server::ConnectionProvider::createShared(oatpp::network::Address("localhost", 8000, oatpp::network::Address::Family::IP_4));
		}());

	/**
	 *  Create Router component
	 */
	OATPP_CREATE_COMPONENT(std::shared_ptr<oatpp::web::server::HttpRouter>, httpRouter)([] {
		return oatpp::web::server::HttpRouter::createShared();
		}());

	/**
	 *  Create ConnectionHandler component which uses Router component to route requests
	 */
	OATPP_CREATE_COMPONENT(std::shared_ptr<oatpp::network::ConnectionHandler>, serverConnectionHandler)([] {
		OATPP_COMPONENT(std::shared_ptr<oatpp::web::server::HttpRouter>, router); // get Router component
		OATPP_COMPONENT(std::shared_ptr<oatpp::async::Executor>, executor); // get Async executor component
		return oatpp::web::server::AsyncHttpConnectionHandler::createShared(router, executor);
		}());

	/**
	 *  Create ObjectMapper component to serialize/deserialize DTOs in Contoller's API
	 */
	OATPP_CREATE_COMPONENT(std::shared_ptr<oatpp::data::mapping::ObjectMapper>, apiObjectMapper)([] {
		auto serializerConfig = oatpp::parser::json::mapping::Serializer::Config::createShared();
		auto deserializerConfig = oatpp::parser::json::mapping::Deserializer::Config::createShared();
		deserializerConfig->allowUnknownFields = false;
		auto objectMapper = oatpp::parser::json::mapping::ObjectMapper::createShared(serializerConfig, deserializerConfig);
		return objectMapper;
		}());


};
#endif // !serverComponents_class

