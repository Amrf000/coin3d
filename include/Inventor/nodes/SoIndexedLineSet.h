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

#ifndef __SOINDEXEDLINESET_H__
#define __SOINDEXEDLINESET_H__

#include <Inventor/nodes/SoIndexedShape.h>

#if defined(COIN_EXCLUDE_SOINDEXEDLINESET)
#error Configuration settings disrespected -- do not include this file!
#endif // COIN_EXCLUDE_SOINDEXEDLINESET

#define SO_END_LINE_INDEX (-1)

// *************************************************************************

class SoIndexedLineSet : public SoIndexedShape {
  typedef SoIndexedShape inherited;

//$ BEGIN TEMPLATE NodeHeader( SoIndexedLineSet )
private:
  static SoType classTypeId;

public:
  static SoType getClassTypeId(void);
  virtual SoType getTypeId(void) const;
  static void * createInstance(void);
public:
  static void initClass(void);
  static void cleanClass(void);

  SoIndexedLineSet(void);
protected:
  virtual ~SoIndexedLineSet();
//$ END TEMPLATE NodeHeader

public:
  enum Binding {
    OVERALL = 0,
    PER_SEGMENT,
    PER_SEGMENT_INDEXED,
    PER_LINE,
    PER_LINE_INDEXED,
    PER_VERTEX,
    PER_VERTEX_INDEXED
  };


#if !defined(COIN_EXCLUDE_SOGLRENDERACTION)
  virtual void GLRender(SoGLRenderAction * action);
  virtual SbBool willSetShapeHints() const;
#endif // !COIN_EXCLUDE_SOGLRENDERACTION
#if !defined(COIN_EXCLUDE_SOGETBOUNDINGBOXACTION)
  virtual void getBoundingBox(SoGetBoundingBoxAction * action);
#endif // !COIN_EXCLUDE_SOGETBOUNDINGBOXACTION
#if !defined(COIN_EXCLUDE_SOGETPRIMITIVECOUNTACTION)
  virtual void getPrimitiveCount(SoGetPrimitiveCountAction * action);
#endif // !COIN_EXCLUDE_SOGETPRIMITIVECOUNTACTION


private:
#if !defined(COIN_EXCLUDE_SOACTION)
  virtual void generatePrimitives(SoAction * action);
#endif // !COIN_EXCLUDE_SOACTION
#if !defined(COIN_EXCLUDE_SORAYPICKACTION)
  virtual SoDetail * createLineSegmentDetail(SoRayPickAction * action,
					     const SoPrimitiveVertex *v1,
					     const SoPrimitiveVertex *v2,
					     SoPickedPoint *pp);
#endif // !COIN_EXCLUDE_SORAYPICKACTION

  SbBool generateDefaultNormals(SoState *, SoNormalCache *nc);

  Binding findNormalBinding(SoState *state);
  Binding findMaterialBinding(SoState *state);

  int numLines() const;
  int numLineSegments() const;

};

#endif // !__SOINDEXEDLINESET_H__
