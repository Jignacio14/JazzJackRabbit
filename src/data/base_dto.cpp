#include "base_dto.h"
#include <cstdint>

BaseDTO::BaseDTO(uint8_t operation_id, uint8_t player_id)
    : operation_id(operation_id), player_id(player_id) {}

uint8_t BaseDTO::getOperationId() const { return this->operation_id; }

uint8_t BaseDTO::getPlayerId() const { return this->player_id; }