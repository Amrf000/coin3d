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

#ifndef COIN_SOERROR_H
#define COIN_SOERROR_H

#include <Inventor/SbBasic.h>
#include <Inventor/SbString.h>

class SoType;
class SoBase;
class SoNode;
class SoPath;
class SoEngine;

typedef void SoErrorCB(const class SoError * error, void * data);


class COIN_DLL_EXPORT SoError {
public:
  static void setHandlerCallback(SoErrorCB * const func, void * const data);
  static SoErrorCB * getHandlerCallback(void);
  static void * getHandlerData(void);

  const SbString & getDebugString(void) const;

  static SoType getClassTypeId(void);
  virtual SoType getTypeId(void) const;
  SbBool isOfType(const SoType type) const;

  static void post(const char * const format, ...);

  static SbString getString(const SoNode * const node);
  static SbString getString(const SoPath * const path);
  static SbString getString(const SoEngine * const engine);

  static void initClass(void);
  static void initClasses(void);

  virtual ~SoError() { } // Kill g++ compiler warnings.

protected:
  static void defaultHandlerCB(const SoError * error, void * userdata);
  virtual SoErrorCB * getHandler(void * & data) const;
  void setDebugString(const char * const str);
  void appendToDebugString(const char * const str);

  void handleError(void);

private:
  static void generateBaseString(SbString & str, const SoBase * const base,
                                 const char * const what);

  static SoType classTypeId;
  static SoErrorCB * callback;
  static void * callbackData;
  SbString debugstring;
};

#endif // !COIN_SOERROR_H
