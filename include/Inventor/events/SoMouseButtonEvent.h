/**************************************************************************\
 *
 *  Copyright (C) 1998-2000 by Systems in Motion.  All rights reserved.
 *
 *  This file is part of the Coin library.
 *
 *  This file may be distributed under the terms of the Q Public License
 *  as defined by Troll Tech AS of Norway and appearing in the file
 *  LICENSE.QPL included in the packaging of this file.
 *
 *  If you want to use Coin in applications not covered by licenses
 *  compatible with the QPL, you can contact SIM to aquire a
 *  Professional Edition license for Coin.
 *
 *  Systems in Motion AS, Prof. Brochs gate 6, N-7030 Trondheim, NORWAY
 *  http://www.sim.no/ sales@sim.no Voice: +47 22114160 Fax: +47 67172912
 *
\**************************************************************************/

#ifndef COIN_SOMOUSEBUTTONEVENT_H
#define COIN_SOMOUSEBUTTONEVENT_H

#include <Inventor/events/SoButtonEvent.h>

#define SO_MOUSE_PRESS_EVENT(EVENT, BUTTON) \
 (SoMouseButtonEvent::isButtonPressEvent(EVENT, SoMouseButtonEvent::BUTTON))

#define SO_MOUSE_RELEASE_EVENT(EVENT, BUTTON) \
 (SoMouseButtonEvent::isButtonReleaseEvent(EVENT, SoMouseButtonEvent::BUTTON))


class SoMouseButtonEvent : public SoButtonEvent {
  typedef SoButtonEvent inherited;

  SO_EVENT_HEADER();

public:
  enum Button {
    ANY, BUTTON1, BUTTON2, BUTTON3, BUTTON4, BUTTON5
  };


  SoMouseButtonEvent(void);
  virtual ~SoMouseButtonEvent();

  void setButton(SoMouseButtonEvent::Button button);
  SoMouseButtonEvent::Button getButton(void) const;

  static SbBool isButtonPressEvent(const SoEvent * e,
                                   SoMouseButtonEvent::Button whichButton);
  static SbBool isButtonReleaseEvent(const SoEvent * e,
                                     SoMouseButtonEvent::Button whichButton);

  static void initClass(void);

private:
  Button button;
};

#endif // !COIN_SOMOUSEBUTTONEVENT_H
