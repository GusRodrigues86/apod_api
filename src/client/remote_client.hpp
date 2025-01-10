#ifndef remote_api_client_hpp
#define remote_api_client_hpp

#include "oatpp/core/macro/codegen.hpp"
#include "oatpp/web/client/ApiClient.hpp"

/**
 * Remote Api Client
 */
class RemoteApiClient : public oatpp::web::client::ApiClient {
#include OATPP_CODEGEN_BEGIN(ApiClient)  //<-- Begin Codegen
 private:
  constexpr static const char* HTTP_GET = "GET";

 public:
  API_CLIENT_INIT(RemoteApiClient)

  API_CALL(HTTP_GET, "users", doGetApod)
  // API_CALL(HTTP_GET, "/planetary/apod", doGetApod)
  //?api_key=DEMO_KEY", getApod)

#include OATPP_CODEGEN_END(ApiClient)  //<-- End Codegen

  // TODO Insert Your endpoints here !!!
};

#endif  // ! remote_client_hpp
