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

/*!
  \class SoCubeDetail SoCubeDetail.h Inventor/details/SoCubeDetail.h
  \brief The SoCubeDetail class is yet to be documented.
  \ingroup details

  FIXME: write doc.
*/

#include <Inventor/details/SoCubeDetail.h>
#include <Inventor/SbName.h>

SO_DETAIL_SOURCE(SoCubeDetail);


SoCubeDetail::SoCubeDetail(void)
  : part(0)
{
}

SoCubeDetail::~SoCubeDetail()
{
}


void
SoCubeDetail::initClass(void)
{
  SO_DETAIL_INIT_CLASS(SoCubeDetail, SoDetail);
}

SoDetail *
SoCubeDetail::copy(void) const
{
  SoCubeDetail * copy = new SoCubeDetail;
  copy->part = this->part;
  return copy;
}

void
SoCubeDetail::setPart(const int part)
{
  this->part = part;
}

int
SoCubeDetail::getPart(void) const
{
  return this->part;
}
