// Generated from FusePiece.cs by tools/gen/gen.js - do not edit. Method bodies: src/game/cpp/FusePiece.cpp
#pragma once
#include "../game_types.h"
#include "ObjectActionController.h"

class FusePiece : public ObjectActionController {
public:
  // ---- fields
  static bool broken;
  bool N{};
  bool E{};
  bool S_{};
  bool W{};
  bool n_now{};
  bool e_now{};
  bool w_now{};
  bool s_now{};
  String coords_X{};
  String coords_Y{};
  Array<Vector2> breakers{};
  Array<P<ParticleGenerator>> breakersParts{};
  Array<P<Sprite>> sprites{};
  P<SpriteRenderer> sr{};
  bool energized{};
  bool energized_before{};
  bool checkedNow{};
  P<FusePiece> first{};
  P<FusePiece> doorish{};
  P<FusePiece> last{};
  P<FusePiece> neighbour_n{};
  P<FusePiece> neighbour_e{};
  P<FusePiece> neighbour_s{};
  P<FusePiece> neighbour_w{};
  List<P<FusePiece>> allPieces{};
  P<ParticleGenerator> pg{};
  static int updateIndex;
  float delay{};
  // ---- constructors
  FusePiece() {}
  // ---- methods
  void Start();
  void Update();
  void updateNESW();
  void updateView(bool slow);
  void pykSound();
  void updateView();
  void updateEnergy(bool slow = false);
  void energizeThis();
  void door();
  void win();
  void breakBoom(int whichone);
  void stopZapBreak();
  void zap(float delay);
  void zapzap();
  void stopBreak();
  void endZap();
  void updateState() override;
  void clickAction0() override;
  void rotate();
  void clickAction() override;
  void clickAction2() override;
  // ---- generated
  void _load(FieldReader& r) override;
  void _clearRefs() override;
  const ClassInfo* _getClassInfo() const override;
  void _saveSerialized(JsonWriter& w) override;
};
