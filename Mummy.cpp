//
// Mummy.cpp
//

// Engine includes.
#include "EventStep.h"
#include "LogManager.h"
#include "WorldManager.h"
#include "utility.h"

// Game includes.
#include "Mummy.h"

Mummy::Mummy(Hero *p_hero) {

  // Basic Mummy attributes.
  m_move_countdown = 0;
  m_think_countdown = 0;
  setType("Mummy");
  setAltitude(3);
  setSpeed(0);

  // Default sprite, standing.
  setSprite("mummy-white");
  stopAnimation(true);
  
  // Mummy keeps track of Hero.
  m_p_hero = p_hero;

  // Get step events.
  registerInterest(df::STEP_EVENT);
}

// Start or stop animation.
void Mummy::stopAnimation(bool stop) {
  df::Animation animation = getAnimation();
  if (stop) {
    if (animation.getSlowdownCount() != -1) {
      animation.setSlowdownCount(-1);
      animation.setIndex(0);
    }
  } else {
    if (animation.getSlowdownCount() == -1) {
      animation.setSlowdownCount(0);
      animation.setIndex(0);
    }
  }
  setAnimation(animation);
}  

// Handle event.
// Return 0 if ignored, else 1
int Mummy::eventHandler(const df::Event *e) {

  // If we get here, we have ignored this event.
  return 0;
}

// Return true if Hero is within sensing distance.
bool Mummy::senseHero() {

  df::Vector diff = getPosition() - m_p_hero -> getPosition();
  float dist = diff.getMagnitude();
  if (dist < SENSE_RANGE)
    return true;
  else
    return false;
}

// If can see Hero and can sense Hero, return direction
// else return (0,0).
df::Vector Mummy::seeHero() {

  // See if can cast line to Hero without hitting a Wall.
  df::Vector hero_pos = m_p_hero -> getPosition();
  df::Vector mummy_pos = getPosition();
  df::Line sight_line(mummy_pos, hero_pos);
  df::ObjectList ol = WM.objectsOnLine(sight_line);
  df::ObjectListIterator i(&ol);
  bool no_wall = true;
  for (i.first(); !i.isDone(); i.next()) {
    if (i.currentObject() -> getType() == "Wall")
      no_wall = false;
  }

  // If no wall on line and in sense range, return normalized vector.
  if (no_wall && senseHero()) {
    df::Vector dir = getPosition() - m_p_hero->getPosition();
    dir.normalize();
    return dir;
  } else
    return df::Vector(0,0);  // Can't see.
}

void Mummy::setMoveCountdown(int new_move_countdown) {
  m_move_countdown = new_move_countdown;
}

int Mummy::getMoveCountdown() {
  return m_move_countdown;
}

void Mummy::setThinkCountdown(int new_think_countdown) {
  m_think_countdown = new_think_countdown;
}

int Mummy::getThinkCountdown() {
  return m_think_countdown;
}

Hero *Mummy::getHero() {
  return m_p_hero;
}
