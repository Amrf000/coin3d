/**************************************************************************\
 *
 *  This file is part of the Coin 3D visualization library.
 *  Copyright (C) 1998-2001 by Systems in Motion.  All rights reserved.
 *  
 *  This library is free software; you can redistribute it and/or
 *  modify it under the terms of the GNU General Public License
 *  version 2 as published by the Free Software Foundation.  See the
 *  file LICENSE.GPL at the root directory of this source distribution
 *  for more details.
 *
 *  If you desire to use Coin with software that is incompatible
 *  licensewise with the GPL, and / or you would like to take
 *  advantage of the additional benefits with regard to our support
 *  services, please contact Systems in Motion about acquiring a Coin
 *  Professional Edition License.  See <URL:http://www.coin3d.org> for
 *  more information.
 *
 *  Systems in Motion, Prof Brochs gate 6, 7030 Trondheim, NORWAY
 *  <URL:http://www.sim.no>, <mailto:support@sim.no>
 *
\**************************************************************************/

#ifndef COIN_SOIMAGE_H
#define COIN_SOIMAGE_H

#include <Inventor/nodes/SoSubNode.h>
#include <Inventor/nodes/SoShape.h>
#include <Inventor/fields/SoSFInt32.h>
#include <Inventor/fields/SoSFEnum.h>
#include <Inventor/fields/SoSFImage.h>
#include <Inventor/fields/SoSFString.h>

class SoSensor;
class SoFieldSensor;
class SbImage;

class COIN_DLL_API SoImage : public SoShape {
  typedef SoShape inherited;

  SO_NODE_HEADER(SoImage);

public:
  static void initClass(void);
  SoImage(void);

  enum VertAlignment {
    BOTTOM,
    HALF,
    TOP
  };

  enum HorAlignment {
    LEFT,
    CENTER,
    RIGHT
  };

  SoSFInt32 width;
  SoSFInt32 height;
  SoSFEnum vertAlignment;
  SoSFEnum horAlignment;
  SoSFImage image;
  SoSFString filename;

  virtual void GLRender(SoGLRenderAction * action);
  virtual void rayPick(SoRayPickAction * action);
  virtual void getPrimitiveCount(SoGetPrimitiveCountAction * action);

protected:
  virtual ~SoImage();

  virtual void generatePrimitives(SoAction * action);
  virtual void computeBBox(SoAction * action, SbBox3f & box, SbVec3f & center);

  virtual SbBool readInstance(SoInput * in, unsigned short flags);
  virtual void notify(SoNotList * list);
  int getReadStatus(void);
  void setReadStatus(SbBool flag);

private:
  SbVec2s getSize(void) const;
  static SbVec3f getNilpoint(SoState *state);
  void getQuad(SoState *state, SbVec3f &v0, SbVec3f &v1,
               SbVec3f &v2, SbVec3f &v3);

  const unsigned char * getImage(SbVec2s & size, int & nc);
  SbBool loadFilename(void);
  SbBool readstatus;
  SbImage * resizedimage;
  SbBool resizedimagevalid;
  class SoFieldSensor * filenamesensor;
  SbBool transparency;
  SbBool testtransparency;
  void testTransparency(void);
  static void filenameSensorCB(void *, SoSensor *);
};

#endif // !COIN_SOIMAGE_H
