#ifndef app_component_hpp
#define app_component_hpp

#include "client/remote_client.hpp"
#include "error_handler.hpp"
#include "oatpp/core/macro/component.hpp"
#include "oatpp/network/tcp/client/ConnectionProvider.hpp"
#include "oatpp/network/tcp/server/ConnectionProvider.hpp"
#include "oatpp/parser/json/mapping/ObjectMapper.hpp"
#include "oatpp/web/client/ApiClient.hpp"
#include "oatpp/web/client/HttpRequestExecutor.hpp"
#include "oatpp/web/server/HttpConnectionHandler.hpp"
#include "swagger_component.hpp"

/**
 *  Class which creates and holds Application components and registers
 * components in oatpp::base::Environment Order of components initialization is
 * from top to bottom
 */
class AppComponent {
 public:
  SwaggerComponent swagger;

  /**
   *  Create ConnectionProvider component which listens on the port
   */
  OATPP_CREATE_COMPONENT(
      std::shared_ptr<oatpp::network::ServerConnectionProvider>,
      serverConnectionProvider)
  ([] {
    return oatpp::network::tcp::server::ConnectionProvider::createShared(
        {"0.0.0.0", 8000, oatpp::network::Address::IP_4});
  }());

  /**
   *  Create Router component
   */
  OATPP_CREATE_COMPONENT(std::shared_ptr<oatpp::web::server::HttpRouter>,
                         httpRouter)
  ([] { return oatpp::web::server::HttpRouter::createShared(); }());

  /**
   *  Create ObjectMapper component to serialize/deserialize DTOs in Contoller's
   * API
   */
  OATPP_CREATE_COMPONENT(std::shared_ptr<oatpp::data::mapping::ObjectMapper>,
                         objectMapper)
  ([] {
    auto mapper = oatpp::parser::json::mapping::ObjectMapper::createShared();
    mapper->getDeserializer()->getConfig()->allowUnknownFields = true;

    return mapper;
  }());

  /**
   *  Create ConnectionHandler component which uses Router component to route
   * requests
   */
  OATPP_CREATE_COMPONENT(std::shared_ptr<oatpp::network::ConnectionHandler>,
                         serverConnectionHandler)
  ([] {
    OATPP_COMPONENT(std::shared_ptr<oatpp::web::server::HttpRouter>,
                    router);  // get Router component
    OATPP_COMPONENT(std::shared_ptr<oatpp::data::mapping::ObjectMapper>,
                    objectMapper);

    auto handler =
        oatpp::web::server::HttpConnectionHandler::createShared(router);
    handler->setErrorHandler(std::make_shared<ErrorHandler>(objectMapper));

    return handler;
  }());

  /**
   * Creates Request Executor for external API Consumption
   */
  OATPP_CREATE_COMPONENT(std::shared_ptr<oatpp::web::client::RequestExecutor>,
                         requestExecutor)
  ([] {
    auto connectionProvider =
        oatpp::network::tcp::client::ConnectionProvider::createShared(
            {"jsonplaceholder.typicode.com", 80});
    // planetary/apod?api_key=DEMO_KEY

    return oatpp::web::client::HttpRequestExecutor::createShared(
        connectionProvider);
  }());

  /**
   * remote api client
   */
  OATPP_CREATE_COMPONENT(std::shared_ptr<RemoteApiClient>, apiClient)
  ([] {
    OATPP_COMPONENT(std::shared_ptr<oatpp::data::mapping::ObjectMapper>,
                    objectMapper);
    OATPP_COMPONENT(std::shared_ptr<oatpp::web::client::RequestExecutor>,
                    requestExecutor);

    auto client = RemoteApiClient::createShared(requestExecutor, objectMapper);

    return client;
  }());
};

#endif  // ! app_component_hpp
