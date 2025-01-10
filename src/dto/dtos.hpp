#ifndef dtos_hpp
#define dtos_hpp

#include "oatpp/core/Types.hpp"
#include "oatpp/core/macro/codegen.hpp"

#include OATPP_CODEGEN_BEGIN(DTO)

ENUM(MediaType, v_int32, VALUE(IMAGE, 1, "image"), VALUE(VIDEO, 2, "video"))

class APodPayload : public oatpp::DTO {
  DTO_INIT(APodPayload, DTO)

  DTO_FIELD(String, date);
  DTO_FIELD(oatpp::Enum<MediaType>, mediaType);
  DTO_FIELD(String, title);
  DTO_FIELD(String, explanation);
  DTO_FIELD(String, url);
  DTO_FIELD(String, author, "copyright");
};

/**
 *  Data Transfer Object. Object containing fields only.
 *  Used in API for serialization/deserialization and validation
 */
class ApodResponseDto : public oatpp::DTO {
  DTO_INIT(ApodResponseDto, DTO)

  DTO_FIELD(Int32, statusCode);
  DTO_FIELD(Object<APodPayload>, message);
};

class ErrorDTO : public oatpp::DTO {
  DTO_INIT(ErrorDTO, DTO)

  DTO_FIELD(Int32, code);
  DTO_FIELD(String, message);
};

#include OATPP_CODEGEN_END(DTO)

#endif  // ! dtos_hpp
