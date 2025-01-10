#ifndef remote_controller_hpp
#define remote_controller_hpp

#include "../client/remote_client.hpp"
#include "../dto/dtos.hpp"
#include "oatpp/core/macro/codegen.hpp"
#include "oatpp/core/macro/component.hpp"
#include "oatpp/web/server/api/ApiController.hpp"

#include OATPP_CODEGEN_BEGIN(ApiController)  //<-- Begin Codegen

/**
 * Sample Api Controller.
 */
class RemoteController : public oatpp::web::server::api::ApiController {
 private:
  std::shared_ptr<RemoteApiClient> m_client;

 public:
  /**
   * Constructor with object mapper.
   * @param objectMapper - default object mapper used to serialize/deserialize
   * DTOs.
   */
  RemoteController(OATPP_COMPONENT(std::shared_ptr<ObjectMapper>, objectMapper),
                   OATPP_COMPONENT(std::shared_ptr<RemoteApiClient>, apiClient))
      : oatpp::web::server::api::ApiController(objectMapper, "/"),
        m_client(apiClient) {}

 public:
  ENDPOINT("GET", "apod", root) {
    auto res = m_client->doGetApod();

    auto str = res->readBodyToString();
    OATPP_LOGI("[getApod] data='%s'", str->c_str());
    auto dto = ApodResponseDto::createShared();
    // m_client->doGetApod();
    dto->statusCode = 200;
    // dto->message = "Hello World!";

    return createDtoResponse(Status::CODE_200, dto);
  }

  // TODO Insert Your endpoints here !!!
};

#include OATPP_CODEGEN_END(ApiController)  //<-- End Codegen

#endif  // ! remote_controller_hpp
