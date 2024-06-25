
#include "collectables_handler.h"
#include "../../common/global_configs.h"
#include "../../common/random_string_generator.h"
#include "../global_counter.h"
#include <cstdint>
#include <iostream>
#include <sys/types.h>

static GlobalConfigs &globalConfigs = GlobalConfigs::getInstance();
static int IS_CARROT_POSIONED_CHANCE = globalConfigs.getCarrotPoisonedChance();

static GlobalCounter &counter = GlobalCounter::getInstance();

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

  uint32_t id1 = counter.getNextID();
  Rectangle carrot1(Coordinates(500, 1168 - HitboxSizes::CollectableHeight),
                    Coordinates(500 + HitboxSizes::CollectableWidth, 1168));

  if (IS_CARROT_POSIONED_CHANCE > 0 &&
      RandomStringGenerator::get_random_number(1, 100) <=
          IS_CARROT_POSIONED_CHANCE) {
    collectables.push_back(std::make_unique<Poisoned>(carrot1, snapshot, id1));
  } else {
    collectables.push_back(std::make_unique<Carrot>(carrot1, snapshot, id1));
  }

  CollectableDto carrot1_dto;
  carrot1_dto.type = CollectableIds::Carrot;
  carrot1_dto.entity_id = id1;
  carrot1_dto.position_x = carrot1.getTopLeftCorner().getX();
  carrot1_dto.position_y = carrot1.getTopLeftCorner().getY();
  carrot1_dto.was_collected = NumericBool::False;
  snapshot.collectables[snapshot.sizeCollectables] = carrot1_dto;
  snapshot.sizeCollectables++;

  uint32_t id2 = counter.getNextID();
  Rectangle carrot2(Coordinates(1310, 1168 - HitboxSizes::CollectableHeight),
                    Coordinates(1310 + HitboxSizes::CollectableWidth, 1168));

  if (IS_CARROT_POSIONED_CHANCE > 0 &&
      RandomStringGenerator::get_random_number(0, 99) <=
          IS_CARROT_POSIONED_CHANCE) {
    collectables.push_back(std::make_unique<Poisoned>(carrot2, snapshot, id2));
  } else {
    collectables.push_back(std::make_unique<Carrot>(carrot2, snapshot, id2));
  }

  CollectableDto carrot2_dto;
  carrot2_dto.type = CollectableIds::Carrot;
  carrot2_dto.entity_id = id2;
  carrot2_dto.position_x = carrot2.getTopLeftCorner().getX();
  carrot2_dto.position_y = carrot2.getTopLeftCorner().getY();
  carrot2_dto.was_collected = NumericBool::False;
  snapshot.collectables[snapshot.sizeCollectables] = carrot2_dto;
  snapshot.sizeCollectables++;

  uint32_t id3 = counter.getNextID();
  Rectangle carrot3(Coordinates(781, 292 - HitboxSizes::CollectableHeight),
                    Coordinates(781 + HitboxSizes::CollectableWidth, 292));

  if (IS_CARROT_POSIONED_CHANCE > 0 &&
      RandomStringGenerator::get_random_number(0, 99) <=
          IS_CARROT_POSIONED_CHANCE) {
    collectables.push_back(std::make_unique<Poisoned>(carrot3, snapshot, id3));
  } else {
    collectables.push_back(std::make_unique<Carrot>(carrot3, snapshot, id3));
  }

  CollectableDto carrot3_dto;
  carrot3_dto.type = CollectableIds::Carrot;
  carrot3_dto.entity_id = id3;
  carrot3_dto.position_x = carrot3.getTopLeftCorner().getX();
  carrot3_dto.position_y = carrot3.getTopLeftCorner().getY();
  carrot3_dto.was_collected = NumericBool::False;
  snapshot.collectables[snapshot.sizeCollectables] = carrot3_dto;
  snapshot.sizeCollectables++;

  uint32_t id4 = counter.getNextID();
  Rectangle carrot4(Coordinates(947, 292 - HitboxSizes::CollectableHeight),
                    Coordinates(947 + HitboxSizes::CollectableWidth, 292));

  if (IS_CARROT_POSIONED_CHANCE > 0 &&
      RandomStringGenerator::get_random_number(0, 99) <=
          IS_CARROT_POSIONED_CHANCE) {
    collectables.push_back(std::make_unique<Poisoned>(carrot4, snapshot, id4));
  } else {
    collectables.push_back(std::make_unique<Carrot>(carrot4, snapshot, id4));
  }

  CollectableDto carrot4_dto;
  carrot4_dto.type = CollectableIds::Carrot;
  carrot4_dto.entity_id = id4;
  carrot4_dto.position_x = carrot4.getTopLeftCorner().getX();
  carrot4_dto.position_y = carrot4.getTopLeftCorner().getY();
  carrot4_dto.was_collected = NumericBool::False;
  snapshot.collectables[snapshot.sizeCollectables] = carrot4_dto;
  snapshot.sizeCollectables++;
}

void CollectablesHandler::initialize_gems() {

  uint32_t id1 = counter.getNextID();
  Rectangle gem1(Coordinates(623, 583 - HitboxSizes::CollectableHeight),
                 Coordinates(623 + HitboxSizes::CollectableWidth, 583));
  collectables.push_back(std::make_unique<Gem>(gem1, snapshot, id1));
  CollectableDto gem1_dto;
  gem1_dto.type = CollectableIds::Diamond;
  gem1_dto.entity_id = id1;
  gem1_dto.position_x = gem1.getTopLeftCorner().getX();
  gem1_dto.position_y = gem1.getTopLeftCorner().getY();
  gem1_dto.was_collected = NumericBool::False;
  snapshot.collectables[snapshot.sizeCollectables] = gem1_dto;
  snapshot.sizeCollectables++;

  uint32_t id2 = counter.getNextID();
  Rectangle gem2(Coordinates(1103, 583 - HitboxSizes::CollectableHeight),
                 Coordinates(1103 + HitboxSizes::CollectableWidth, 583));
  collectables.push_back(std::make_unique<Gem>(gem2, snapshot, id2));
  CollectableDto gem2_dto;
  gem2_dto.type = CollectableIds::Diamond;
  gem2_dto.entity_id = id2;
  gem2_dto.position_x = gem2.getTopLeftCorner().getX();
  gem2_dto.position_y = gem2.getTopLeftCorner().getY();
  gem2_dto.was_collected = NumericBool::False;
  snapshot.collectables[snapshot.sizeCollectables] = gem2_dto;
  snapshot.sizeCollectables++;

  uint32_t id3 = counter.getNextID();
  Rectangle gem3(Coordinates(862, 292 - HitboxSizes::CollectableHeight),
                 Coordinates(862 + HitboxSizes::CollectableWidth, 292));
  collectables.push_back(std::make_unique<Gem>(gem3, snapshot, id3));
  CollectableDto gem3_dto;
  gem3_dto.type = CollectableIds::Diamond;
  gem3_dto.entity_id = id3;
  gem3_dto.position_x = gem3.getTopLeftCorner().getX();
  gem3_dto.position_y = gem3.getTopLeftCorner().getY();
  gem3_dto.was_collected = NumericBool::False;
  snapshot.collectables[snapshot.sizeCollectables] = gem3_dto;
  snapshot.sizeCollectables++;
}

void CollectablesHandler::initialize_coins() {

  uint32_t id1 = counter.getNextID();
  Rectangle coin1(Coordinates(440, 1168 - HitboxSizes::CollectableHeight),
                  Coordinates(440 + HitboxSizes::CollectableWidth, 1168));
  collectables.push_back(std::make_unique<Coin>(coin1, snapshot, id1));
  CollectableDto coin1_dto;
  coin1_dto.type = CollectableIds::Coin;
  coin1_dto.entity_id = id1;
  coin1_dto.position_x = coin1.getTopLeftCorner().getX();
  coin1_dto.position_y = coin1.getTopLeftCorner().getY();
  coin1_dto.was_collected = NumericBool::False;
  snapshot.collectables[snapshot.sizeCollectables] = coin1_dto;
  snapshot.sizeCollectables++;

  uint32_t id2 = counter.getNextID();
  Rectangle coin2(Coordinates(470, 1168 - HitboxSizes::CollectableHeight),
                  Coordinates(470 + HitboxSizes::CollectableWidth, 1168));
  collectables.push_back(std::make_unique<Coin>(coin2, snapshot, id2));
  CollectableDto coin2_dto;
  coin2_dto.type = CollectableIds::Coin;
  coin2_dto.entity_id = id2;
  coin2_dto.position_x = coin2.getTopLeftCorner().getX();
  coin2_dto.position_y = coin2.getTopLeftCorner().getY();
  coin2_dto.was_collected = NumericBool::False;
  snapshot.collectables[snapshot.sizeCollectables] = coin2_dto;
  snapshot.sizeCollectables++;

  uint32_t id3 = counter.getNextID();
  Rectangle coin3(Coordinates(530, 1168 - HitboxSizes::CollectableHeight),
                  Coordinates(530 + HitboxSizes::CollectableWidth, 1168));
  collectables.push_back(std::make_unique<Coin>(coin3, snapshot, id3));
  CollectableDto coin3_dto;
  coin3_dto.type = CollectableIds::Coin;
  coin3_dto.entity_id = id3;
  coin3_dto.position_x = coin3.getTopLeftCorner().getX();
  coin3_dto.position_y = coin3.getTopLeftCorner().getY();
  coin3_dto.was_collected = NumericBool::False;
  snapshot.collectables[snapshot.sizeCollectables] = coin3_dto;
  snapshot.sizeCollectables++;

  uint32_t id4 = counter.getNextID();
  Rectangle coin4(Coordinates(560, 1168 - HitboxSizes::CollectableHeight),
                  Coordinates(560 + HitboxSizes::CollectableWidth, 1168));
  collectables.push_back(std::make_unique<Coin>(coin4, snapshot, id4));
  CollectableDto coin4_dto;
  coin4_dto.type = CollectableIds::Coin;
  coin4_dto.entity_id = id4;
  coin4_dto.position_x = coin4.getTopLeftCorner().getX();
  coin4_dto.position_y = coin4.getTopLeftCorner().getY();
  coin4_dto.was_collected = NumericBool::False;
  snapshot.collectables[snapshot.sizeCollectables] = coin4_dto;
  snapshot.sizeCollectables++;

  uint32_t id5 = counter.getNextID();
  Rectangle coin5(Coordinates(1250, 1168 - HitboxSizes::CollectableHeight),
                  Coordinates(1250 + HitboxSizes::CollectableWidth, 1168));
  collectables.push_back(std::make_unique<Coin>(coin5, snapshot, id5));
  CollectableDto coin5_dto;
  coin5_dto.type = CollectableIds::Coin;
  coin5_dto.entity_id = id5;
  coin5_dto.position_x = coin5.getTopLeftCorner().getX();
  coin5_dto.position_y = coin5.getTopLeftCorner().getY();
  coin5_dto.was_collected = NumericBool::False;
  snapshot.collectables[snapshot.sizeCollectables] = coin5_dto;
  snapshot.sizeCollectables++;

  uint32_t id6 = counter.getNextID();
  Rectangle coin6(Coordinates(1280, 1168 - HitboxSizes::CollectableHeight),
                  Coordinates(1280 + HitboxSizes::CollectableWidth, 1168));
  collectables.push_back(std::make_unique<Coin>(coin6, snapshot, id6));
  CollectableDto coin6_dto;
  coin6_dto.type = CollectableIds::Coin;
  coin6_dto.entity_id = id6;
  coin6_dto.position_x = coin6.getTopLeftCorner().getX();
  coin6_dto.position_y = coin6.getTopLeftCorner().getY();
  coin6_dto.was_collected = NumericBool::False;
  snapshot.collectables[snapshot.sizeCollectables] = coin6_dto;
  snapshot.sizeCollectables++;

  uint32_t id7 = counter.getNextID();
  Rectangle coin7(Coordinates(1340, 1168 - HitboxSizes::CollectableHeight),
                  Coordinates(1340 + HitboxSizes::CollectableWidth, 1168));
  collectables.push_back(std::make_unique<Coin>(coin7, snapshot, id7));
  CollectableDto coin7_dto;
  coin7_dto.type = CollectableIds::Coin;
  coin7_dto.entity_id = id7;
  coin7_dto.position_x = coin7.getTopLeftCorner().getX();
  coin7_dto.position_y = coin7.getTopLeftCorner().getY();
  coin7_dto.was_collected = NumericBool::False;
  snapshot.collectables[snapshot.sizeCollectables] = coin7_dto;
  snapshot.sizeCollectables++;

  uint32_t id8 = counter.getNextID();
  Rectangle coin8(Coordinates(1370, 1168 - HitboxSizes::CollectableHeight),
                  Coordinates(1370 + HitboxSizes::CollectableWidth, 1168));
  collectables.push_back(std::make_unique<Coin>(coin8, snapshot, id8));
  CollectableDto coin8_dto;
  coin8_dto.type = CollectableIds::Coin;
  coin8_dto.entity_id = id8;
  coin8_dto.position_x = coin8.getTopLeftCorner().getX();
  coin8_dto.position_y = coin8.getTopLeftCorner().getY();
  coin8_dto.was_collected = NumericBool::False;
  snapshot.collectables[snapshot.sizeCollectables] = coin8_dto;
  snapshot.sizeCollectables++;

  uint32_t id9 = counter.getNextID();
  Rectangle coin9(Coordinates(306, 926 - HitboxSizes::CollectableHeight),
                  Coordinates(306 + HitboxSizes::CollectableWidth, 926));
  collectables.push_back(std::make_unique<Coin>(coin9, snapshot, id9));
  CollectableDto coin9_dto;
  coin9_dto.type = CollectableIds::Coin;
  coin9_dto.entity_id = id9;
  coin9_dto.position_x = coin9.getTopLeftCorner().getX();
  coin9_dto.position_y = coin9.getTopLeftCorner().getY();
  coin9_dto.was_collected = NumericBool::False;
  snapshot.collectables[snapshot.sizeCollectables] = coin9_dto;
  snapshot.sizeCollectables++;

  uint32_t id10 = counter.getNextID();
  Rectangle coin10(Coordinates(336, 926 - HitboxSizes::CollectableHeight),
                   Coordinates(336 + HitboxSizes::CollectableWidth, 926));
  collectables.push_back(std::make_unique<Coin>(coin10, snapshot, id10));
  CollectableDto coin10_dto;
  coin10_dto.type = CollectableIds::Coin;
  coin10_dto.entity_id = id10;
  coin10_dto.position_x = coin10.getTopLeftCorner().getX();
  coin10_dto.position_y = coin10.getTopLeftCorner().getY();
  coin10_dto.was_collected = NumericBool::False;
  snapshot.collectables[snapshot.sizeCollectables] = coin10_dto;
  snapshot.sizeCollectables++;

  uint32_t id11 = counter.getNextID();
  Rectangle coin11(Coordinates(694, 926 - HitboxSizes::CollectableHeight),
                   Coordinates(694 + HitboxSizes::CollectableWidth, 926));
  collectables.push_back(std::make_unique<Coin>(coin11, snapshot, id11));
  CollectableDto coin11_dto;
  coin11_dto.type = CollectableIds::Coin;
  coin11_dto.entity_id = id11;
  coin11_dto.position_x = coin11.getTopLeftCorner().getX();
  coin11_dto.position_y = coin11.getTopLeftCorner().getY();
  coin11_dto.was_collected = NumericBool::False;
  snapshot.collectables[snapshot.sizeCollectables] = coin11_dto;
  snapshot.sizeCollectables++;

  uint32_t id12 = counter.getNextID();
  Rectangle coin12(Coordinates(724, 926 - HitboxSizes::CollectableHeight),
                   Coordinates(724 + HitboxSizes::CollectableWidth, 926));
  collectables.push_back(std::make_unique<Coin>(coin12, snapshot, id12));
  CollectableDto coin12_dto;
  coin12_dto.type = CollectableIds::Coin;
  coin12_dto.entity_id = id12;
  coin12_dto.position_x = coin12.getTopLeftCorner().getX();
  coin12_dto.position_y = coin12.getTopLeftCorner().getY();
  coin12_dto.was_collected = NumericBool::False;
  snapshot.collectables[snapshot.sizeCollectables] = coin12_dto;
  snapshot.sizeCollectables++;

  uint32_t id13 = counter.getNextID();
  Rectangle coin13(Coordinates(1106, 926 - HitboxSizes::CollectableHeight),
                   Coordinates(1106 + HitboxSizes::CollectableWidth, 926));
  collectables.push_back(std::make_unique<Coin>(coin13, snapshot, id13));
  CollectableDto coin13_dto;
  coin13_dto.type = CollectableIds::Coin;
  coin13_dto.entity_id = id13;
  coin13_dto.position_x = coin13.getTopLeftCorner().getX();
  coin13_dto.position_y = coin13.getTopLeftCorner().getY();
  coin13_dto.was_collected = NumericBool::False;
  snapshot.collectables[snapshot.sizeCollectables] = coin13_dto;
  snapshot.sizeCollectables++;

  uint32_t id14 = counter.getNextID();
  Rectangle coin14(Coordinates(1136, 926 - HitboxSizes::CollectableHeight),
                   Coordinates(1136 + HitboxSizes::CollectableWidth, 926));
  collectables.push_back(std::make_unique<Coin>(coin14, snapshot, id14));
  CollectableDto coin14_dto;
  coin14_dto.type = CollectableIds::Coin;
  coin14_dto.entity_id = id14;
  coin14_dto.position_x = coin14.getTopLeftCorner().getX();
  coin14_dto.position_y = coin14.getTopLeftCorner().getY();
  coin14_dto.was_collected = NumericBool::False;
  snapshot.collectables[snapshot.sizeCollectables] = coin14_dto;
  snapshot.sizeCollectables++;

  uint32_t id15 = counter.getNextID();
  Rectangle coin15(Coordinates(1494, 926 - HitboxSizes::CollectableHeight),
                   Coordinates(1494 + HitboxSizes::CollectableWidth, 926));
  collectables.push_back(std::make_unique<Coin>(coin15, snapshot, id15));
  CollectableDto coin15_dto;
  coin15_dto.type = CollectableIds::Coin;
  coin15_dto.entity_id = id15;
  coin15_dto.position_x = coin15.getTopLeftCorner().getX();
  coin15_dto.position_y = coin15.getTopLeftCorner().getY();
  coin15_dto.was_collected = NumericBool::False;
  snapshot.collectables[snapshot.sizeCollectables] = coin15_dto;
  snapshot.sizeCollectables++;

  uint32_t id16 = counter.getNextID();
  Rectangle coin16(Coordinates(1524, 926 - HitboxSizes::CollectableHeight),
                   Coordinates(1524 + HitboxSizes::CollectableWidth, 926));
  collectables.push_back(std::make_unique<Coin>(coin16, snapshot, id16));
  CollectableDto coin16_dto;
  coin16_dto.type = CollectableIds::Coin;
  coin16_dto.entity_id = id16;
  coin16_dto.position_x = coin16.getTopLeftCorner().getX();
  coin16_dto.position_y = coin16.getTopLeftCorner().getY();
  coin16_dto.was_collected = NumericBool::False;
  snapshot.collectables[snapshot.sizeCollectables] = coin16_dto;
  snapshot.sizeCollectables++;

  uint32_t id17 = counter.getNextID();
  Rectangle coin17(Coordinates(379, 894 - HitboxSizes::CollectableHeight),
                   Coordinates(379 + HitboxSizes::CollectableWidth, 894));
  collectables.push_back(std::make_unique<Coin>(coin17, snapshot, id17));
  CollectableDto coin17_dto;
  coin17_dto.type = CollectableIds::Coin;
  coin17_dto.entity_id = id17;
  coin17_dto.position_x = coin17.getTopLeftCorner().getX();
  coin17_dto.position_y = coin17.getTopLeftCorner().getY();
  coin17_dto.was_collected = NumericBool::False;
  snapshot.collectables[snapshot.sizeCollectables] = coin17_dto;
  snapshot.sizeCollectables++;

  uint32_t id18 = counter.getNextID();
  Rectangle coin18(Coordinates(651, 894 - HitboxSizes::CollectableHeight),
                   Coordinates(651 + HitboxSizes::CollectableWidth, 894));
  collectables.push_back(std::make_unique<Coin>(coin18, snapshot, id18));
  CollectableDto coin18_dto;
  coin18_dto.type = CollectableIds::Coin;
  coin18_dto.entity_id = id18;
  coin18_dto.position_x = coin18.getTopLeftCorner().getX();
  coin18_dto.position_y = coin18.getTopLeftCorner().getY();
  coin18_dto.was_collected = NumericBool::False;
  snapshot.collectables[snapshot.sizeCollectables] = coin18_dto;
  snapshot.sizeCollectables++;

  uint32_t id19 = counter.getNextID();
  Rectangle coin19(Coordinates(1175, 894 - HitboxSizes::CollectableHeight),
                   Coordinates(1175 + HitboxSizes::CollectableWidth, 894));
  collectables.push_back(std::make_unique<Coin>(coin19, snapshot, id19));
  CollectableDto coin19_dto;
  coin19_dto.type = CollectableIds::Coin;
  coin19_dto.entity_id = id19;
  coin19_dto.position_x = coin19.getTopLeftCorner().getX();
  coin19_dto.position_y = coin19.getTopLeftCorner().getY();
  coin19_dto.was_collected = NumericBool::False;
  snapshot.collectables[snapshot.sizeCollectables] = coin19_dto;
  snapshot.sizeCollectables++;

  uint32_t id20 = counter.getNextID();
  Rectangle coin20(Coordinates(1452, 894 - HitboxSizes::CollectableHeight),
                   Coordinates(1452 + HitboxSizes::CollectableWidth, 894));
  collectables.push_back(std::make_unique<Coin>(coin20, snapshot, id20));
  CollectableDto coin20_dto;
  coin20_dto.type = CollectableIds::Coin;
  coin20_dto.entity_id = id20;
  coin20_dto.position_x = coin20.getTopLeftCorner().getX();
  coin20_dto.position_y = coin20.getTopLeftCorner().getY();
  coin20_dto.was_collected = NumericBool::False;
  snapshot.collectables[snapshot.sizeCollectables] = coin20_dto;
  snapshot.sizeCollectables++;
}

void CollectablesHandler::reset_collectables() {
  collectables.clear();
  snapshot.sizeCollectables = 0;
  initialize();
}

void CollectablesHandler::add_ammo(Rectangle rectangle) {
  uint32_t id_ammo = counter.getNextID();
  collectables.push_back(std::make_unique<Ammo>(rectangle, snapshot, id_ammo));
  CollectableDto ammo_dto;
  ammo_dto.type = CollectableIds::AmmoGun2;
  ammo_dto.entity_id = id_ammo;
  ammo_dto.position_x = rectangle.getTopLeftCorner().getX();
  ammo_dto.position_y = rectangle.getTopLeftCorner().getY();
  ammo_dto.was_collected = NumericBool::False;
  snapshot.collectables[snapshot.sizeCollectables] = ammo_dto;
  snapshot.sizeCollectables++;
}

void CollectablesHandler::add_carrot(Rectangle rectangle) {
  uint32_t id_carrot = counter.getNextID();
  collectables.push_back(
      std::make_unique<Carrot>(rectangle, snapshot, id_carrot));
  CollectableDto carrot_dto;
  carrot_dto.type = CollectableIds::Carrot;
  carrot_dto.entity_id = id_carrot;
  carrot_dto.position_x = rectangle.getTopLeftCorner().getX();
  carrot_dto.position_y = rectangle.getTopLeftCorner().getY();
  carrot_dto.was_collected = NumericBool::False;
  snapshot.collectables[snapshot.sizeCollectables] = carrot_dto;
  snapshot.sizeCollectables++;
}
