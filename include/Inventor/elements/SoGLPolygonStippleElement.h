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

#ifndef _SO_GL_POLYGON_STIPPLE_ELEMENT_H_
#define _SO_GL_POLYGON_STIPPLE_ELEMENT_H_

#include <Inventor/confdep.h>
#if defined(COIN_EXCLUDE_SOGLPOLYGONSTIPPLEELEMENT)
#error "Configuration settings disrespected -- do not include this file!"
#endif // COIN_EXCLUDE_SOGLPOLYGONSTIPPLEELEMENT

#include <Inventor/elements/SoElement.h>

class SoGLPolygonStippleElement : public SoElement {
  typedef SoElement inherited;
  
//$ BEGIN TEMPLATE ElementHeader( SoGLPolygonStippleElement )
public:
  static SoType classTypeId;
  static SoType getClassTypeId(void);
  static void * createInstance(void);
public:
  static int getClassStackIndex(void);
  virtual ~SoGLPolygonStippleElement(void);

  static void initClass(void);
  static void cleanClass(void);

protected:
  SoGLPolygonStippleElement(void);
  static int classStackIndex;
//$ END TEMPLATE ElementHeader

public:
  virtual void init(SoState *state);
  
  static void set(SoState * const state, const SbBool onoff);
  
  static void setTransparency(SoState * const state,
			      const float transparency);

  static SbBool get(SoState * const state);
  
  virtual void push(SoState *state);
  virtual void pop(SoState *state, const SoElement *prevTopElement);

  virtual SbBool matches(const SoElement *elt) const;
  virtual SoElement *copyMatchInfo() const;

  virtual void print(FILE *fp) const;

  void evaluate() const;

private:
  static u_char patterns[64 + 1][32 * 4];

  void updategl();
  SbBool isEnabled;
  int pattern;

  SbBool currentEnabled;
  int currentPattern;

}; // class SoGLPolygonStippleElement

#endif // ! _SO_GL_POLYGON_STIPPLE_ELEMENT_H_ 
