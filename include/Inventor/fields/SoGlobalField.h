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

#ifndef COIN_SOGLOBALFIELD_H
#define COIN_SOGLOBALFIELD_H

#include <Inventor/fields/SoFieldContainer.h>


class COIN_DLL_EXPORT SoGlobalField : public SoFieldContainer {
  typedef SoFieldContainer inherited;

public:
  SoGlobalField(const SbName & name, SoField * field);

  static void initClass(void);
  static SoType getClassTypeId(void);
  virtual SoType getTypeId(void) const;

  SoField * getGlobalField(void) const;
  virtual const SoFieldData * getFieldData(void) const;

  virtual void setName(const SbName & newname);

  virtual void addWriteReference(SoOutput * out, SbBool isfromfield = FALSE);
  virtual void writeInstance(SoOutput * out);

  static SoGlobalField * getGlobalFieldContainer(const SbName & name);
  static void removeGlobalFieldContainer(SoGlobalField * fieldcontainer);
  static SoBaseList * getGlobalFieldContainers(void);

protected:
  ~SoGlobalField();

  virtual SbBool readInstance(SoInput * in, unsigned short flags);

private:
  static void * createInstance(void);
  static void clean(void);
  static int getGlobalFieldIndex(const SbName & name);

  static SoType classTypeId;
  SoFieldData * classfielddata;
  static SoBaseList * allcontainers;
};

#endif // !COIN_SOGLOBALFIELD_H
