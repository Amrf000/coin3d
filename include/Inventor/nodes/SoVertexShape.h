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

#ifndef __SOVERTEXSHAPE_H__
#define __SOVERTEXSHAPE_H__

#include <Inventor/nodes/SoShape.h>
#include <Inventor/fields/SoSFNode.h>

#if defined(COIN_EXCLUDE_SOVERTEXSHAPE)
#error Configuration settings disrespected -- do not include this file!
#endif // COIN_EXCLUDE_SOVERTEXSHAPE

class SoNormalCache;
class SoNormalBundle;
class SbVec3f;
class SoTextureCoordinateElement;
class SoCoordinateElement;


class SoVertexShape : public SoShape 
{
  typedef SoShape inherited;

//$ BEGIN TEMPLATE NodeAbstractHeader( SoVertexShape )
private:
  static SoType classTypeId;

public:
  static SoType getClassTypeId(void);
  virtual SoType getTypeId(void) const;
public:
  static void initClass(void);
  static void cleanClass(void);

protected:
  SoVertexShape(void);
  virtual ~SoVertexShape();
//$ END TEMPLATE NodeAbstractHeader

public:
  SoSFNode vertexProperty;

  virtual void notify(SoNotList * list);
  virtual SbBool generateDefaultNormals(SoState * state,
	        			SoNormalBundle * bundle);
#if !defined(COIN_EXCLUDE_SOWRITEACTION)
  virtual void write(SoWriteAction * writeAction);
#endif // !COIN_EXCLUDE_SOWRITEACTION

protected:
#if !defined(COIN_EXCLUDE_SOGLRENDERACTION)
  virtual SbBool willSendUnitLengthNormals(SoState *state) const;
  virtual SbBool shouldGLRender(SoGLRenderAction * action);
#endif // !COIN_EXCLUDE_SOGLRENDERACTION

  void setNormalCache(SoState * const state,
		      const int num, const SbVec3f * normals);
  SoNormalCache * getNormalCache(void) const;

  void getGLData(SoState * state,
		 const SoCoordinateElement *& coords,
		 const SbVec3f *& normals,
		 SbBool & needNormals);

private:
  virtual SbBool generateDefaultNormals(SoState * state,
					SoNormalCache * cache);
  void generateNormals(SoState * const state);
  SoNormalCache * normalCache;
};



#endif // !__SOVERTEXSHAPE_H__
