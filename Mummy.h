//
// Mummy.h
//

#ifndef MUMMY_H
#define MUMMY_H

// Engine includes
#include "Event.h"
#include "Object.h"
#include "Vector.h"

// Game includes
#include "game.h"
#include "Hero.h"

class Mummy : public df::Object {

 private:
  Hero *m_p_hero;
  int m_move_countdown;
  int m_think_countdown;

 public:
  Mummy(Hero *p_hero);
  int eventHandler(const df::Event *e);
  Hero *getHero();
  void stopAnimation(bool stop);
  df::Vector seeHero();
  bool senseHero();
  int getMoveCountdown();
  void setMoveCountdown(int new_move_countdown);
  int getThinkCountdown();
  void setThinkCountdown(int new_think_countdown);
};

#endif
