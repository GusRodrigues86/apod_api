
#ifndef swagger_component_hpp
#define swagger_component_hpp

#include <memory>

#include "oatpp-swagger/Model.hpp"
#include "oatpp-swagger/Resources.hpp"
#include "oatpp/core/macro/component.hpp"

/**
 *  Swagger ui is served at
 *  http://host:port/swagger/ui
 */
class SwaggerComponent {
 public:
  /**
   *  Swagger-Ui Resources (<oatpp-examples>/lib/oatpp-swagger/res)
   *  OATPP_SWAGGER_RES_PATH variable declared on CMakeList
   */
  OATPP_CREATE_COMPONENT(std::shared_ptr<oatpp::swagger::Resources>,
                         swaggerResources)
  ([] {
    // Make sure to specify correct full path to oatpp-swagger/res folder
    // !!!
    return oatpp::swagger::Resources::loadResources(OATPP_SWAGGER_RES_PATH);
  }());

  /**
   *  General API docs info
   */
  OATPP_CREATE_COMPONENT(std::shared_ptr<oatpp::swagger::DocumentInfo>,
                         swaggerDocumentInfo)
  ([] {
    oatpp::swagger::DocumentInfo::Builder builder;

    builder.setTitle("APOD entity service")
        .setDescription("REST API Example project with swagger docs")
        .setVersion("1.0")
        .setContactName("Gustavo Bonifacio Rodrigues")
        .setContactUrl("https://github.com/GusRodrigues86")

        .setLicenseName("BSD-3 Clause")
        .setLicenseUrl("https://opensource.org/license/BSD-3-Clause")

        .addServer("http://localhost:8000", "server on localhost");

    return builder.build();
  }());
};

#endif  // !swagger_component_hpp
