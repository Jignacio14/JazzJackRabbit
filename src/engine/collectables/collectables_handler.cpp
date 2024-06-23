
#include "collectables_handler.h"
#include <cstdint>
#include <iostream>

CollectablesHandler::CollectablesHandler(
    std::vector<std::unique_ptr<BaseCollectable>> &collectables,
    Snapshot &snapshot)
    : collectables(collectables), snapshot(snapshot) {}

void CollectablesHandler::initialize() {
  this->initialize_carrots();
  this->initialize_gems();
  this->initialize_coins();
  this->initialize_poisoned();
}

void CollectablesHandler::initialize_carrots() {

  Rectangle carrot1(Coordinates(500, 1168 - HitboxSizes::CollectableHeight),
                    Coordinates(500 + HitboxSizes::CollectableWidth, 1168));
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
  /*std::cout << "Carrot 1 id:" << snapshot.sizeCollectables - 1 << std::endl;
  std::cout << "Position: TopLeft: (" << carrot1.getTopLeftCorner().getX() << ",
  "
            << carrot1.getTopLeftCorner().getY() << ")" << "BottonRight: (" <<
  carrot1.getBottomRightCorner().getX() << ", "
            << carrot1.getBottomRightCorner().getY() << ")" << std::endl;
  std::cout << "Snapshot TopLeft: (" <<
  snapshot.collectables[snapshot.sizeCollectables - 1].position_x << ", "
            << snapshot.collectables[snapshot.sizeCollectables - 1].position_y
  << ")" << std::endl;
*/
  Rectangle carrot2(Coordinates(1310, 1168 - HitboxSizes::CollectableHeight),
                    Coordinates(1310 + HitboxSizes::CollectableWidth, 1168));
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
  /*std::cout << "Carrot 2 id:" << snapshot.sizeCollectables - 1 << std::endl;
  std::cout << "Position: TopLeft: (" << carrot2.getTopLeftCorner().getX() << ",
  "
            << carrot2.getTopLeftCorner().getY() << ")" << "BottonRight: (" <<
  carrot2.getBottomRightCorner().getX() << ", "
            << carrot2.getBottomRightCorner().getY() << ")" << std::endl;
  std::cout << "Snapshot TopLeft: (" <<
  snapshot.collectables[snapshot.sizeCollectables - 1].position_x << ", "
            << snapshot.collectables[snapshot.sizeCollectables - 1].position_y
  << ")" << std::endl;
*/
  Rectangle carrot3(Coordinates(781, 292 - HitboxSizes::CollectableHeight),
                    Coordinates(781 + HitboxSizes::CollectableWidth, 292));
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
  /*std::cout << "Carrot 3 id:" << snapshot.sizeCollectables - 1 << std::endl;
  std::cout << "Position: TopLeft: (" << carrot3.getTopLeftCorner().getX() << ",
  "
            << carrot3.getTopLeftCorner().getY() << ")" << "BottonRight: (" <<
  carrot3.getBottomRightCorner().getX() << ", "
            << carrot3.getBottomRightCorner().getY() << ")" << std::endl;
  std::cout << "Snapshot TopLeft: (" <<
  snapshot.collectables[snapshot.sizeCollectables - 1].position_x << ", "
            << snapshot.collectables[snapshot.sizeCollectables - 1].position_y
  << ")" << std::endl;
  */
}

void CollectablesHandler::initialize_gems() {

  Rectangle gem1(Coordinates(623, 583 - HitboxSizes::CollectableHeight),
                 Coordinates(623 + HitboxSizes::CollectableWidth, 583));
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

  Rectangle gem2(Coordinates(1103, 583 - HitboxSizes::CollectableHeight),
                 Coordinates(1103 + HitboxSizes::CollectableWidth, 583));
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

  Rectangle gem3(Coordinates(862, 292 - HitboxSizes::CollectableHeight),
                 Coordinates(862 + HitboxSizes::CollectableWidth, 292));
  collectables.push_back(std::make_unique<Gem>(
      gem3, snapshot, (uint32_t)snapshot.sizeCollectables));
  CollectableDto gem3_dto;
  gem3_dto.type = CollectableIds::Diamond;
  gem3_dto.entity_id = snapshot.sizeCollectables;
  gem3_dto.position_x = gem3.getTopLeftCorner().getX();
  gem3_dto.position_y = gem3.getTopLeftCorner().getY();
  gem3_dto.was_collected = NumericBool::False;
  snapshot.collectables[snapshot.sizeCollectables] = gem3_dto;
  snapshot.sizeCollectables++;
}

void CollectablesHandler::initialize_coins() {

  Rectangle coin1(Coordinates(440, 1168 - HitboxSizes::CollectableHeight),
                  Coordinates(440 + HitboxSizes::CollectableWidth, 1168));
  collectables.push_back(std::make_unique<Coin>(
      coin1, snapshot, (uint32_t)snapshot.sizeCollectables));
  CollectableDto coin1_dto;
  coin1_dto.type = CollectableIds::Coin;
  coin1_dto.entity_id = snapshot.sizeCollectables;
  coin1_dto.position_x = coin1.getTopLeftCorner().getX();
  coin1_dto.position_y = coin1.getTopLeftCorner().getY();
  coin1_dto.was_collected = NumericBool::False;
  snapshot.collectables[snapshot.sizeCollectables] = coin1_dto;
  snapshot.sizeCollectables++;

  Rectangle coin2(Coordinates(470, 1168 - HitboxSizes::CollectableHeight),
                  Coordinates(470 + HitboxSizes::CollectableWidth, 1168));
  collectables.push_back(std::make_unique<Coin>(
      coin2, snapshot, (uint32_t)snapshot.sizeCollectables));
  CollectableDto coin2_dto;
  coin2_dto.type = CollectableIds::Coin;
  coin2_dto.entity_id = snapshot.sizeCollectables;
  coin2_dto.position_x = coin2.getTopLeftCorner().getX();
  coin2_dto.position_y = coin2.getTopLeftCorner().getY();
  coin2_dto.was_collected = NumericBool::False;
  snapshot.collectables[snapshot.sizeCollectables] = coin2_dto;
  snapshot.sizeCollectables++;

  Rectangle coin3(Coordinates(530, 1168 - HitboxSizes::CollectableHeight),
                  Coordinates(530 + HitboxSizes::CollectableWidth, 1168));
  collectables.push_back(std::make_unique<Coin>(
      coin3, snapshot, (uint32_t)snapshot.sizeCollectables));
  CollectableDto coin3_dto;
  coin3_dto.type = CollectableIds::Coin;
  coin3_dto.entity_id = snapshot.sizeCollectables;
  coin3_dto.position_x = coin3.getTopLeftCorner().getX();
  coin3_dto.position_y = coin3.getTopLeftCorner().getY();
  coin3_dto.was_collected = NumericBool::False;
  snapshot.collectables[snapshot.sizeCollectables] = coin3_dto;
  snapshot.sizeCollectables++;

  Rectangle coin4(Coordinates(560, 1168 - HitboxSizes::CollectableHeight),
                  Coordinates(560 + HitboxSizes::CollectableWidth, 1168));
  collectables.push_back(std::make_unique<Coin>(
      coin4, snapshot, (uint32_t)snapshot.sizeCollectables));
  CollectableDto coin4_dto;
  coin4_dto.type = CollectableIds::Coin;
  coin4_dto.entity_id = snapshot.sizeCollectables;
  coin4_dto.position_x = coin4.getTopLeftCorner().getX();
  coin4_dto.position_y = coin4.getTopLeftCorner().getY();
  coin4_dto.was_collected = NumericBool::False;
  snapshot.collectables[snapshot.sizeCollectables] = coin4_dto;
  snapshot.sizeCollectables++;

  Rectangle coin5(Coordinates(1250, 1168 - HitboxSizes::CollectableHeight),
                  Coordinates(1250 + HitboxSizes::CollectableWidth, 1168));
  collectables.push_back(std::make_unique<Coin>(
      coin5, snapshot, (uint32_t)snapshot.sizeCollectables));
  CollectableDto coin5_dto;
  coin5_dto.type = CollectableIds::Coin;
  coin5_dto.entity_id = snapshot.sizeCollectables;
  coin5_dto.position_x = coin5.getTopLeftCorner().getX();
  coin5_dto.position_y = coin5.getTopLeftCorner().getY();
  coin5_dto.was_collected = NumericBool::False;
  snapshot.collectables[snapshot.sizeCollectables] = coin5_dto;
  snapshot.sizeCollectables++;

  Rectangle coin6(Coordinates(1280, 1168 - HitboxSizes::CollectableHeight),
                  Coordinates(1280 + HitboxSizes::CollectableWidth, 1168));
  collectables.push_back(std::make_unique<Coin>(
      coin6, snapshot, (uint32_t)snapshot.sizeCollectables));
  CollectableDto coin6_dto;
  coin6_dto.type = CollectableIds::Coin;
  coin6_dto.entity_id = snapshot.sizeCollectables;
  coin6_dto.position_x = coin6.getTopLeftCorner().getX();
  coin6_dto.position_y = coin6.getTopLeftCorner().getY();
  coin6_dto.was_collected = NumericBool::False;
  snapshot.collectables[snapshot.sizeCollectables] = coin6_dto;
  snapshot.sizeCollectables++;

  Rectangle coin7(Coordinates(1340, 1168 - HitboxSizes::CollectableHeight),
                  Coordinates(1340 + HitboxSizes::CollectableWidth, 1168));
  collectables.push_back(std::make_unique<Coin>(
      coin7, snapshot, (uint32_t)snapshot.sizeCollectables));
  CollectableDto coin7_dto;
  coin7_dto.type = CollectableIds::Coin;
  coin7_dto.entity_id = snapshot.sizeCollectables;
  coin7_dto.position_x = coin7.getTopLeftCorner().getX();
  coin7_dto.position_y = coin7.getTopLeftCorner().getY();
  coin7_dto.was_collected = NumericBool::False;
  snapshot.collectables[snapshot.sizeCollectables] = coin7_dto;
  snapshot.sizeCollectables++;

  Rectangle coin8(Coordinates(1370, 1168 - HitboxSizes::CollectableHeight),
                  Coordinates(1370 + HitboxSizes::CollectableWidth, 1168));
  collectables.push_back(std::make_unique<Coin>(
      coin8, snapshot, (uint32_t)snapshot.sizeCollectables));
  CollectableDto coin8_dto;
  coin8_dto.type = CollectableIds::Coin;
  coin8_dto.entity_id = snapshot.sizeCollectables;
  coin8_dto.position_x = coin8.getTopLeftCorner().getX();
  coin8_dto.position_y = coin8.getTopLeftCorner().getY();
  coin8_dto.was_collected = NumericBool::False;
  snapshot.collectables[snapshot.sizeCollectables] = coin8_dto;
  snapshot.sizeCollectables++;

  Rectangle coin9(Coordinates(320, 926 - HitboxSizes::CollectableHeight),
                  Coordinates(320 + HitboxSizes::CollectableWidth, 926));
  collectables.push_back(std::make_unique<Coin>(
      coin9, snapshot, (uint32_t)snapshot.sizeCollectables));
  CollectableDto coin9_dto;
  coin9_dto.type = CollectableIds::Coin;
  coin9_dto.entity_id = snapshot.sizeCollectables;
  coin9_dto.position_x = coin9.getTopLeftCorner().getX();
  coin9_dto.position_y = coin9.getTopLeftCorner().getY();
  coin9_dto.was_collected = NumericBool::False;
  snapshot.collectables[snapshot.sizeCollectables] = coin9_dto;
  snapshot.sizeCollectables++;

  Rectangle coin10(Coordinates(350, 926 - HitboxSizes::CollectableHeight),
                   Coordinates(350 + HitboxSizes::CollectableWidth, 926));
  collectables.push_back(std::make_unique<Coin>(
      coin10, snapshot, (uint32_t)snapshot.sizeCollectables));
  CollectableDto coin10_dto;
  coin10_dto.type = CollectableIds::Coin;
  coin10_dto.entity_id = snapshot.sizeCollectables;
  coin10_dto.position_x = coin10.getTopLeftCorner().getX();
  coin10_dto.position_y = coin10.getTopLeftCorner().getY();
  coin10_dto.was_collected = NumericBool::False;
  snapshot.collectables[snapshot.sizeCollectables] = coin10_dto;
  snapshot.sizeCollectables++;

  Rectangle coin11(Coordinates(670, 926 - HitboxSizes::CollectableHeight),
                   Coordinates(670 + HitboxSizes::CollectableWidth, 926));
  collectables.push_back(std::make_unique<Coin>(
      coin11, snapshot, (uint32_t)snapshot.sizeCollectables));
  CollectableDto coin11_dto;
  coin11_dto.type = CollectableIds::Coin;
  coin11_dto.entity_id = snapshot.sizeCollectables;
  coin11_dto.position_x = coin11.getTopLeftCorner().getX();
  coin11_dto.position_y = coin11.getTopLeftCorner().getY();
  coin11_dto.was_collected = NumericBool::False;
  snapshot.collectables[snapshot.sizeCollectables] = coin11_dto;
  snapshot.sizeCollectables++;

  Rectangle coin12(Coordinates(710, 926 - HitboxSizes::CollectableHeight),
                   Coordinates(710 + HitboxSizes::CollectableWidth, 926));
  collectables.push_back(std::make_unique<Coin>(
      coin12, snapshot, (uint32_t)snapshot.sizeCollectables));
  CollectableDto coin12_dto;
  coin12_dto.type = CollectableIds::Coin;
  coin12_dto.entity_id = snapshot.sizeCollectables;
  coin12_dto.position_x = coin12.getTopLeftCorner().getX();
  coin12_dto.position_y = coin12.getTopLeftCorner().getY();
  coin12_dto.was_collected = NumericBool::False;
  snapshot.collectables[snapshot.sizeCollectables] = coin12_dto;
  snapshot.sizeCollectables++;

  Rectangle coin13(Coordinates(1120, 926 - HitboxSizes::CollectableHeight),
                   Coordinates(1120 + HitboxSizes::CollectableWidth, 926));
  collectables.push_back(std::make_unique<Coin>(
      coin13, snapshot, (uint32_t)snapshot.sizeCollectables));
  CollectableDto coin13_dto;
  coin13_dto.type = CollectableIds::Coin;
  coin13_dto.entity_id = snapshot.sizeCollectables;
  coin13_dto.position_x = coin13.getTopLeftCorner().getX();
  coin13_dto.position_y = coin13.getTopLeftCorner().getY();
  coin13_dto.was_collected = NumericBool::False;
  snapshot.collectables[snapshot.sizeCollectables] = coin13_dto;
  snapshot.sizeCollectables++;

  Rectangle coin14(Coordinates(1155, 926 - HitboxSizes::CollectableHeight),
                   Coordinates(1155 + HitboxSizes::CollectableWidth, 926));
  collectables.push_back(std::make_unique<Coin>(
      coin14, snapshot, (uint32_t)snapshot.sizeCollectables));
  CollectableDto coin14_dto;
  coin14_dto.type = CollectableIds::Coin;
  coin14_dto.entity_id = snapshot.sizeCollectables;
  coin14_dto.position_x = coin14.getTopLeftCorner().getX();
  coin14_dto.position_y = coin14.getTopLeftCorner().getY();
  coin14_dto.was_collected = NumericBool::False;
  snapshot.collectables[snapshot.sizeCollectables] = coin14_dto;
  snapshot.sizeCollectables++;

  Rectangle coin15(Coordinates(1470, 926 - HitboxSizes::CollectableHeight),
                   Coordinates(1470 + HitboxSizes::CollectableWidth, 926));
  collectables.push_back(std::make_unique<Coin>(
      coin15, snapshot, (uint32_t)snapshot.sizeCollectables));
  CollectableDto coin15_dto;
  coin15_dto.type = CollectableIds::Coin;
  coin15_dto.entity_id = snapshot.sizeCollectables;
  coin15_dto.position_x = coin15.getTopLeftCorner().getX();
  coin15_dto.position_y = coin15.getTopLeftCorner().getY();
  coin15_dto.was_collected = NumericBool::False;
  snapshot.collectables[snapshot.sizeCollectables] = coin15_dto;
  snapshot.sizeCollectables++;

  Rectangle coin16(Coordinates(1500, 926 - HitboxSizes::CollectableHeight),
                   Coordinates(1500 + HitboxSizes::CollectableWidth, 926));
  collectables.push_back(std::make_unique<Coin>(
      coin16, snapshot, (uint32_t)snapshot.sizeCollectables));
  CollectableDto coin16_dto;
  coin16_dto.type = CollectableIds::Coin;
  coin16_dto.entity_id = snapshot.sizeCollectables;
  coin16_dto.position_x = coin16.getTopLeftCorner().getX();
  coin16_dto.position_y = coin16.getTopLeftCorner().getY();
  coin16_dto.was_collected = NumericBool::False;
  snapshot.collectables[snapshot.sizeCollectables] = coin16_dto;
  snapshot.sizeCollectables++;

  Rectangle coin17(Coordinates(399, 894 - HitboxSizes::CollectableHeight),
                   Coordinates(399 + HitboxSizes::CollectableWidth, 894));
  collectables.push_back(std::make_unique<Coin>(
      coin17, snapshot, (uint32_t)snapshot.sizeCollectables));
  CollectableDto coin17_dto;
  coin17_dto.type = CollectableIds::Coin;
  coin17_dto.entity_id = snapshot.sizeCollectables;
  coin17_dto.position_x = coin17.getTopLeftCorner().getX();
  coin17_dto.position_y = coin17.getTopLeftCorner().getY();
  coin17_dto.was_collected = NumericBool::False;
  snapshot.collectables[snapshot.sizeCollectables] = coin17_dto;
  snapshot.sizeCollectables++;

  Rectangle coin18(Coordinates(624, 894 - HitboxSizes::CollectableHeight),
                   Coordinates(624 + HitboxSizes::CollectableWidth, 894));
  collectables.push_back(std::make_unique<Coin>(
      coin18, snapshot, (uint32_t)snapshot.sizeCollectables));
  CollectableDto coin18_dto;
  coin18_dto.type = CollectableIds::Coin;
  coin18_dto.entity_id = snapshot.sizeCollectables;
  coin18_dto.position_x = coin18.getTopLeftCorner().getX();
  coin18_dto.position_y = coin18.getTopLeftCorner().getY();
  coin18_dto.was_collected = NumericBool::False;
  snapshot.collectables[snapshot.sizeCollectables] = coin18_dto;
  snapshot.sizeCollectables++;

  Rectangle coin19(Coordinates(1200, 894 - HitboxSizes::CollectableHeight),
                   Coordinates(1200 + HitboxSizes::CollectableWidth, 894));
  collectables.push_back(std::make_unique<Coin>(
      coin19, snapshot, (uint32_t)snapshot.sizeCollectables));
  CollectableDto coin19_dto;
  coin19_dto.type = CollectableIds::Coin;
  coin19_dto.entity_id = snapshot.sizeCollectables;
  coin19_dto.position_x = coin19.getTopLeftCorner().getX();
  coin19_dto.position_y = coin19.getTopLeftCorner().getY();
  coin19_dto.was_collected = NumericBool::False;
  snapshot.collectables[snapshot.sizeCollectables] = coin19_dto;
  snapshot.sizeCollectables++;

  Rectangle coin20(Coordinates(1423, 894 - HitboxSizes::CollectableHeight),
                   Coordinates(1423 + HitboxSizes::CollectableWidth, 894));
  collectables.push_back(std::make_unique<Coin>(
      coin20, snapshot, (uint32_t)snapshot.sizeCollectables));
  CollectableDto coin20_dto;
  coin20_dto.type = CollectableIds::Coin;
  coin20_dto.entity_id = snapshot.sizeCollectables;
  coin20_dto.position_x = coin20.getTopLeftCorner().getX();
  coin20_dto.position_y = coin20.getTopLeftCorner().getY();
  coin20_dto.was_collected = NumericBool::False;
  snapshot.collectables[snapshot.sizeCollectables] = coin20_dto;
  snapshot.sizeCollectables++;
}

void CollectablesHandler::initialize_poisoned() {

  Rectangle poisoned1(Coordinates(947, 292 - HitboxSizes::CollectableHeight),
                      Coordinates(947 + HitboxSizes::CollectableWidth, 292));
  collectables.push_back(std::make_unique<Poisoned>(
      poisoned1, snapshot, (uint32_t)snapshot.sizeCollectables));
  CollectableDto poisoned1_dto;
  poisoned1_dto.type = CollectableIds::Carrot;
  poisoned1_dto.entity_id = snapshot.sizeCollectables;
  poisoned1_dto.position_x = poisoned1.getTopLeftCorner().getX();
  poisoned1_dto.position_y = poisoned1.getTopLeftCorner().getY();
  poisoned1_dto.was_collected = NumericBool::False;
  snapshot.collectables[snapshot.sizeCollectables] = poisoned1_dto;
  snapshot.sizeCollectables++;
}

void CollectablesHandler::reset_collectables() {
  collectables.clear();
  snapshot.sizeCollectables = 0;
  initialize();
}
