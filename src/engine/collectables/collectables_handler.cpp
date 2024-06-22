
#include "collectables_handler.h"
#include <cstdint>
#include <iostream>

CollectablesHandler::CollectablesHandler(
    std::vector<std::unique_ptr<BaseCollectable>> &collectables,
    Snapshot &snapshot)
    : collectables(collectables), snapshot(snapshot) {}

void CollectablesHandler::initialize() {
  this->initialize_carrots();
  this->initializeGems();
}

void CollectablesHandler::initialize_carrots() {

  Rectangle carrot1(Coordinates(482, 1168 - HitboxSizes::CollectableHeight),
                    Coordinates(482 + HitboxSizes::CollectableWidth, 1168));
  collectables.push_back(std::make_unique<Carrot>(
      carrot1, snapshot, (uint32_t)snapshot.sizeCollectables));
  CollectableDto carrot1_dto;
  carrot1_dto.type = CollectableIds::Carrot;
  carrot1_dto.entity_id = snapshot.sizeCollectables;
  carrot1_dto.position_x = carrot1.getTopLeftCorner().getX();
  carrot1_dto.position_y = carrot1.getTopLeftCorner().getY();
  carrot1_dto.was_collected = NumericBool::False;
  snapshot.collectables[snapshot.sizeCollectables] = carrot1_dto;
  snapshot.sizeCollectables++;

  Rectangle carrot2(Coordinates(1382, 1168 - HitboxSizes::CollectableHeight),
                    Coordinates(1382 + HitboxSizes::CollectableWidth, 1168));
  collectables.push_back(std::make_unique<Carrot>(
      carrot2, snapshot, (uint32_t)snapshot.sizeCollectables));
  CollectableDto carrot2_dto;
  carrot2_dto.type = CollectableIds::Carrot;
  carrot2_dto.entity_id = snapshot.sizeCollectables;
  carrot2_dto.position_x = carrot2.getTopLeftCorner().getX();
  carrot2_dto.position_y = carrot2.getTopLeftCorner().getY();
  carrot2_dto.was_collected = NumericBool::False;
  snapshot.collectables[snapshot.sizeCollectables] = carrot2_dto;
  snapshot.sizeCollectables++;

  Rectangle carrot3(Coordinates(900, 292 - HitboxSizes::CollectableHeight),
                    Coordinates(900 + HitboxSizes::CollectableWidth, 292));
  collectables.push_back(std::make_unique<Carrot>(
      carrot3, snapshot, (uint32_t)snapshot.sizeCollectables));
  CollectableDto carrot3_dto;
  carrot3_dto.type = CollectableIds::Carrot;
  carrot3_dto.entity_id = snapshot.sizeCollectables;
  carrot3_dto.position_x = carrot3.getTopLeftCorner().getX();
  carrot3_dto.position_y = carrot3.getTopLeftCorner().getY();
  carrot3_dto.was_collected = NumericBool::False;
  snapshot.collectables[snapshot.sizeCollectables] = carrot3_dto;
  snapshot.sizeCollectables++;
}

void CollectablesHandler::initializeGems() {

  Rectangle gem1(Coordinates(900, 1168 - HitboxSizes::CollectableHeight),
                 Coordinates(900 + HitboxSizes::CollectableWidth, 1168));
  collectables.push_back(std::make_unique<Gem>(
      gem1, snapshot, (uint32_t)snapshot.sizeCollectables));
  CollectableDto gem1_dto;
  gem1_dto.type = CollectableIds::Diamond;
  gem1_dto.entity_id = snapshot.sizeCollectables;
  gem1_dto.position_x = gem1.getTopLeftCorner().getX();
  gem1_dto.position_y = gem1.getTopLeftCorner().getY();
  gem1_dto.was_collected = NumericBool::False;
  snapshot.collectables[snapshot.sizeCollectables] = gem1_dto;
  snapshot.sizeCollectables++;

  Rectangle gem2(Coordinates(1700, 1168 - HitboxSizes::CollectableHeight),
                 Coordinates(1700 + HitboxSizes::CollectableWidth, 1168));
  collectables.push_back(std::make_unique<Gem>(
      gem2, snapshot, (uint32_t)snapshot.sizeCollectables));
  CollectableDto gem2_dto;
  gem2_dto.type = CollectableIds::Diamond;
  gem2_dto.entity_id = snapshot.sizeCollectables;
  gem2_dto.position_x = gem2.getTopLeftCorner().getX();
  gem2_dto.position_y = gem2.getTopLeftCorner().getY();
  gem2_dto.was_collected = NumericBool::False;
  snapshot.collectables[snapshot.sizeCollectables] = gem2_dto;
  snapshot.sizeCollectables++;
}
