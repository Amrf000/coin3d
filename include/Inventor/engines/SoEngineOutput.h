/**************************************************************************\
 * 
 *  Copyright (C) 1998-1999 by Systems in Motion.  All rights reserved.
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
 *  http://www.sim.no/ sales@sim.no Voice: +47 73540378 Fax: +47 73943861
 *
\**************************************************************************/

#ifndef __SOENGINEOUTPUT_H__
#define __SOENGINEOUTPUT_H__

#include <Inventor/SoType.h>
#include <Inventor/lists/SoFieldList.h>

#if defined(COIN_EXCLUDE_SOENGINE)
#error "Configuration settings disrespected -- do not include this file!"
#endif // COIN_EXCLUDE_SOENGINE


class SoEngineOutput {
public:
  SoType getConnectionType(void) const;
  int getForwardConnections(SoFieldList & list) const;
  void enable(const SbBool flag);
  SbBool isEnabled(void) const;
  class SoEngine * getContainer(void) const;

  SoEngineOutput(void);
  virtual ~SoEngineOutput();
  void setType(SoType type);
  void setContainer(SoEngine * engine);
  void addConnection(SoField * f);
  void removeConnection(SoField * f);
  int getNumConnections(void) const;
  SoField * operator[](int i) const;

  void prepareToWrite(void) const;
  void doneWriting(void) const;

private:
  SoType type;
  SbBool enabled;
  SoEngine * container;
  SoFieldList connections;
};

#endif // !__SOENGINEOUTPUT_H__
