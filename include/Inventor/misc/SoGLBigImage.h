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

#ifndef COIN_SOGLBIGIMAGE_H
#define COIN_SOGLBIGIMAGE_H

#include <Inventor/SbBasic.h>
#include <Inventor/SbVec2s.h>
#include <Inventor/SbVec2f.h>
#include <Inventor/misc/SoGLImage.h>

class COIN_DLL_API SoGLBigImage : public SoGLImage {
  typedef SoGLImage inherited;

public:

  SoGLBigImage();
  virtual void unref(SoState * state = NULL);

  static SoType getClassTypeId(void);
  virtual SoType getTypeId(void) const ;

  virtual void setData(const SbImage * image,
                       const Wrap wraps,
                       const Wrap wrapt,
                       const float quality = 0.5f,
                       const int border = 0,
                       SoState * createinstate = NULL);

  int initSubImages(SoState * state, const SbVec2s & subimagesize) const;
  void handleSubImage(const int idx, SbVec2f & start, SbVec2f & end,
                      SbVec2f & tcmul);
  void applySubImage(SoState * state, const int idx, const float quality,
                     const SbVec2s & projsize);

  // will return NULL to avoid that SoGLTextureImageElement will
  // update the texture state.
  virtual SoGLDisplayList * getGLDisplayList(SoState * state);

protected:
  virtual void unrefOldDL(SoState * state, const uint32_t maxage);

private:
  virtual ~SoGLBigImage();

  class SoGLBigImageP * pimpl;
  friend class SoGLBigImageP;
};

#endif // !COIN_SOGLBIGIMAGE_H
