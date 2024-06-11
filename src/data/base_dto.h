#ifndef BASE_DTO
#define BASE_DTO

#include <cstdint>

class BaseDTO {
private:
  // cppcheck-suppress unusedStructMember
  uint8_t operation_id;
  // cppcheck-suppress unusedStructMember
  uint8_t player_id;

public:
  BaseDTO(uint8_t operation_id, uint8_t player_id);

  uint8_t getOperationId() const;
  uint8_t getPlayerId() const;

  virtual ~BaseDTO();
};

#endif // BASE_DTO
