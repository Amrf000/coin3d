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

#ifndef _SO_TEXTURE_IMAGE_ELEMENT_H_
#define _SO_TEXTURE_IMAGE_ELEMENT_H_

#include <Inventor/confdep.h>
#if defined(COIN_EXCLUDE_SOTEXTUREIMAGEELEMENT)
#error "Configuration settings disable this class!"
#endif // COIN_EXCLUDE_SOTEXTUREIMAGEELEMENT

#include <Inventor/elements/SoReplacedElement.h>

#include <Inventor/SbVec2s.h>
#include <Inventor/SbColor.h>

class SoState;

class SoTextureImageElement : public SoReplacedElement {
  typedef SoReplacedElement inherited;

//$ BEGIN TEMPLATE ElementHeader( SoTextureImageElement )
public:
  static SoType classTypeId;
  static SoType getClassTypeId(void);
  static void * createInstance(void);
public:
  static int getClassStackIndex(void);
  virtual ~SoTextureImageElement(void);

  static void initClass(void);
  static void cleanClass(void);

protected:
  SoTextureImageElement(void);
  static int classStackIndex;
//$ END TEMPLATE ElementHeader

public:
  enum Model {
    MODULATE,
    DECAL,
    BLEND
  };

  enum Wrap {
    REPEAT,
    CLAMP
  };
  
  virtual void init(SoState * state);

  static  void set(SoState * const state, SoNode * const node,
		   const SbVec2s & size, const int numComponents,
		   const unsigned char * bytes, 
		   const int wrapS, const int wrapT,
		   const int model, const SbColor & blendColor);

  static  void set(SoState * const state, SoNode * const node,
		   const SbVec2s & size, const int numComponents,
		   const unsigned char * bytes, 
		   const Wrap wrapS, const Wrap wrapT,
		   const Model model, const SbColor & blendColor);

  static const unsigned char *get(SoState * const state,
				  SbVec2s & size, 
				  int & numComponents, 
				  Wrap & wrapS, 
				  Wrap & wrapT,
				  Model & model, 
				  SbColor & blendColor);

  static const unsigned char *get(SoState * const state,
				  SbVec2s & size, 
				  int & numComponents, 
				  int & wrapS, 
				  int & wrapT,
				  int & model, 
				  SbColor & blendColor);

  static SbBool containsTransparency(SoState * const state);

  static const unsigned char *getDefault(SbVec2s & size, int & numComponents);

protected:
  virtual void setElt(const SbVec2s & size, const int numComponents,
		      const unsigned char * bytes, 
		      const Wrap wrapS, const Wrap wrapT,
		      const Model model, const SbColor & blendColor);

  SbVec2s size;
  int numComponents;
  const unsigned char *bytes;
  Wrap wrapS, wrapT;
  Model model;
  SbColor blendColor;

}; // class SoTextureImageElement

#endif // ! _SO_TEXTURE_IMAGE_ELEMENT_H_
