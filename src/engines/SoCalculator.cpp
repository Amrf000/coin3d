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


#include <Inventor/engines/SoCalculator.h>
#include <Inventor/lists/SoEngineOutputList.h>
#include "evaluator.h"
#include <assert.h>
#include <Inventor/engines/SoSubEngineP.h>

#if COIN_DEBUG
#include <Inventor/errors/SoDebugError.h>
#endif // COIN_DEBUG

/*!
  \class SoCalculator Inventor/engines/SoCalculator.h
  \brief General purpose calculator for floats and 3D float vectors.
  \ingroup engines

  FIXME: doc
*/

SO_ENGINE_SOURCE(SoCalculator);

/*!
  Constructor.
*/
SoCalculator::SoCalculator(void)
{
  SO_ENGINE_INTERNAL_CONSTRUCTOR(SoCalculator);

  SO_ENGINE_ADD_INPUT(a, (0.0f));
  SO_ENGINE_ADD_INPUT(b, (0.0f));
  SO_ENGINE_ADD_INPUT(c, (0.0f));
  SO_ENGINE_ADD_INPUT(d, (0.0f));
  SO_ENGINE_ADD_INPUT(e, (0.0f));
  SO_ENGINE_ADD_INPUT(f, (0.0f));
  SO_ENGINE_ADD_INPUT(g, (0.0f));
  SO_ENGINE_ADD_INPUT(h, (0.0f));
  SO_ENGINE_ADD_INPUT(A, (SbVec3f(0.0f, 0.0f, 0.0f)));
  SO_ENGINE_ADD_INPUT(B, (SbVec3f(0.0f, 0.0f, 0.0f)));
  SO_ENGINE_ADD_INPUT(C, (SbVec3f(0.0f, 0.0f, 0.0f)));
  SO_ENGINE_ADD_INPUT(D, (SbVec3f(0.0f, 0.0f, 0.0f)));
  SO_ENGINE_ADD_INPUT(E, (SbVec3f(0.0f, 0.0f, 0.0f)));
  SO_ENGINE_ADD_INPUT(F, (SbVec3f(0.0f, 0.0f, 0.0f)));
  SO_ENGINE_ADD_INPUT(G, (SbVec3f(0.0f, 0.0f, 0.0f)));
  SO_ENGINE_ADD_INPUT(H, (SbVec3f(0.0f, 0.0f, 0.0f)));
  SO_ENGINE_ADD_INPUT(expression, (""));

  SO_ENGINE_ADD_OUTPUT(oa, SoMFFloat);
  SO_ENGINE_ADD_OUTPUT(ob, SoMFFloat);
  SO_ENGINE_ADD_OUTPUT(oc, SoMFFloat);
  SO_ENGINE_ADD_OUTPUT(od, SoMFFloat);
  SO_ENGINE_ADD_OUTPUT(oA, SoMFVec3f);
  SO_ENGINE_ADD_OUTPUT(oB, SoMFVec3f);
  SO_ENGINE_ADD_OUTPUT(oC, SoMFVec3f);
  SO_ENGINE_ADD_OUTPUT(oD, SoMFVec3f);

  // initialize temporary registers (ta-th, tA-tH)
  int i;
  for (i = 0; i < 8; i++) {
    ta_th[i] = 0.0f;
    tA_tH[i].setValue(0.0f, 0.0f, 0.0f);
  }
}

/*!
  Destructor.
*/
SoCalculator::~SoCalculator(void)
{
  for (int i = 0; i < this->evaluatorList.getLength(); i++) {
    so_eval_delete(this->evaluatorList[i]);
  }
}

// overloaded from parent
void
SoCalculator::initClass(void)
{
  SO_ENGINE_INTERNAL_INIT_CLASS(SoCalculator);
}

// overloaded from parent
void
SoCalculator::evaluate(void)
{
  int i, j;

  if (this->expression.getNum() == 0 ||
      this->expression[0].getLength() == 0) return;

  if (this->evaluatorList.getLength() == 0) {
    for (i = 0; i < this->expression.getNum(); i++) {
      const SbString &s = this->expression[i];
      if (s.getLength()) {
        this->evaluatorList.append(so_eval_parse(s.getString()));
#if COIN_DEBUG && 1 // debug
        if (so_eval_error()) {
          SoDebugError::postWarning("SoCalculator::evaluateExpression",
                                    "%s", so_eval_error());
        }
#endif // debug
      }
      else this->evaluatorList.append(NULL);
    }
  }


  // find all fields used in all expressions
  int maxnum = 0;
  char inused[16]; /* a-h and A-H */
  char outused[8]; /* a-d and A-D */
  for (i = 0; i < 16; i++) inused[i] = 0;
  for (i = 0; i < 8; i++) outused[i] = 0;

  for (i = 0; i < this->evaluatorList.getLength(); i++) {
    this->findUsed(this->evaluatorList[i], inused, outused);
  }

  // find max number of values in used input fields
  char fieldname[2];
  fieldname[1] = 0;
  for (i = 0; i < 16; i++) {
    if (inused[i]) {
      if (i < 8) {
        fieldname[0] = 'a' + i;
      }
      else {
        fieldname[0] = 'A' + (i-8);
      }
      SoMField *field = (SoMField*)this->getField(fieldname);
      maxnum = SbMax(maxnum, field->getNum());
    }
  }
  if (maxnum == 0) maxnum = 1; // in case only temporary registers were used

  if (outused[0]) { SO_ENGINE_OUTPUT(oa, SoMFFloat, setNum(maxnum)); }
  if (outused[1]) { SO_ENGINE_OUTPUT(ob, SoMFFloat, setNum(maxnum)); }
  if (outused[2]) { SO_ENGINE_OUTPUT(oc, SoMFFloat, setNum(maxnum)); }
  if (outused[3]) { SO_ENGINE_OUTPUT(od, SoMFFloat, setNum(maxnum)); }

  if (outused[4]) { SO_ENGINE_OUTPUT(oA, SoMFVec3f, setNum(maxnum)); }
  if (outused[5]) { SO_ENGINE_OUTPUT(oB, SoMFVec3f, setNum(maxnum)); }
  if (outused[6]) { SO_ENGINE_OUTPUT(oC, SoMFVec3f, setNum(maxnum)); }
  if (outused[7]) { SO_ENGINE_OUTPUT(oD, SoMFVec3f, setNum(maxnum)); }

  // loop through all fieldindices and evaluate
  for (i = 0; i < maxnum; i++) {
    // just initialize output registers to default values
    // (in case an expression reads from an output before setting its value)
    oA_oD[0] = SbVec3f(0.0f, 0.0f, 0.0f);
    oA_oD[1] = SbVec3f(0.0f, 0.0f, 0.0f);
    oA_oD[2] = SbVec3f(0.0f, 0.0f, 0.0f);
    oA_oD[3] = SbVec3f(0.0f, 0.0f, 0.0f);
    oa_od[0] = 0.0f;
    oa_od[1] = 0.0f;
    oa_od[2] = 0.0f;
    oa_od[3] = 0.0f;

    // evaluate all expressions for this fieldidx
    for (j = 0; j < this->evaluatorList.getLength(); j++) {
      if (this->evaluatorList[j]) {
        this->evaluateExpression(this->evaluatorList[j], i);
      }
    }
  }
}

// evaluates a single expression from/into fieldidx
void
SoCalculator::evaluateExpression(struct so_eval_node *node, const int fieldidx)
{
  int i;

  char fieldname[2];
  fieldname[1] = 0;
  char inused[16]; /* a-h and A-H */
  char outused[8]; /* oa-od and oA-oD */

  so_eval_cbdata cbdata;
  cbdata.readfieldcb = SoCalculator::readfieldcb;
  cbdata.writefieldcb = SoCalculator::writefieldcb;
  cbdata.userdata = this;

  for (i = 0; i < 16; i++) inused[i] = 0;
  for (i = 0; i < 8; i++) outused[i] = 0;

  this->findUsed(node, inused, outused);

  // copy values from fields to temporary "registers" while evaluating
  for (i = 0; i < 8; i++) {
    if (inused[i]) {
      fieldname[0] = 'a' + i;
      SoMFFloat *field = (SoMFFloat*) this->getField(fieldname);
      int num = field->getNum();
      if (num) a_h[i] = field->getValues(0)[SbMin(fieldidx, num-1)];
      else a_h[i] = 0.0f;
    }
  }
  for (i = 0; i < 8; i++) {
    if (inused[i+8]) {
      fieldname[0] = 'A' + i;
      SoMFVec3f *field = (SoMFVec3f*) this->getField(fieldname);
      int num = field->getNum();
      if (num) A_H[i] = field->getValues(0)[SbMin(fieldidx, num-1)];
      else A_H[i] = SbVec3f(0.0f, 0.0f, 0.0f);
    }
  }
  so_eval_evaluate(node, &cbdata);

  // copy the output values from "registers" to engine output
  if (outused[0]) { SO_ENGINE_OUTPUT(oa, SoMFFloat, set1Value(fieldidx, oa_od[0])); }
  if (outused[1]) { SO_ENGINE_OUTPUT(ob, SoMFFloat, set1Value(fieldidx, oa_od[1])); }
  if (outused[2]) { SO_ENGINE_OUTPUT(oc, SoMFFloat, set1Value(fieldidx, oa_od[2])); }
  if (outused[3]) { SO_ENGINE_OUTPUT(od, SoMFFloat, set1Value(fieldidx, oa_od[3])); }

  if (outused[4]) { SO_ENGINE_OUTPUT(oA, SoMFVec3f, set1Value(fieldidx, oA_oD[0])); }
  if (outused[5]) { SO_ENGINE_OUTPUT(oB, SoMFVec3f, set1Value(fieldidx, oA_oD[1])); }
  if (outused[6]) { SO_ENGINE_OUTPUT(oC, SoMFVec3f, set1Value(fieldidx, oA_oD[2])); }
  if (outused[7]) { SO_ENGINE_OUTPUT(oD, SoMFVec3f, set1Value(fieldidx, oA_oD[3])); }
}



//
// find all input and output fields that are used in the expression(s)
// inused 0-7   => a-h
// inused 8-15  => A-H
// outused 0-3  => oa-od
// outused 4-7  => oA-oD
//
// inused and outused must be cleared before calling this method
//
void
SoCalculator::findUsed(struct so_eval_node *node, char *inused, char *outused)
{
  if (node == NULL) return;

  if (node->id == ID_ASSIGN_FLT || node->id == ID_ASSIGN_VEC) {
    this->findUsed(node->child2, inused, outused); // traverse rhs
    // inspect lhs
    node = node->child1;
    if (node->regname[0] == 'o') { // only consider engine outputs
      if ((node->regname[1] >= 'A') && (node->regname[1] <= 'D')) {
        outused[node->regname[1]-'A'+4] = 1;
      }
      else {
        assert((node->regname[1] >= 'a') && (node->regname[1] <= 'd'));
        outused[node->regname[1]-'a'] = 1;
      }
    }
  }
  else {
    if (node->child1) this->findUsed(node->child1, inused, outused);
    if (node->child2) this->findUsed(node->child2, inused, outused);
    if (node->child3) this->findUsed(node->child3, inused, outused);
  }
  if (node->id == ID_FLT_REG) {
    if ((node->regname[0] >= 'a') && (node->regname[0] <= 'h')) {
      inused[node->regname[0]-'a'] = 1;
    }
  }
  else if (node->id == ID_VEC_REG || node->id == ID_VEC_REG_COMP) {
    if ((node->regname[0] >= 'A') && (node->regname[0] <= 'H')) {
      inused[node->regname[0]-'A'+8] = 1;
    }
  }
}

// overloaded from parent
void
SoCalculator::inputChanged(SoField *which)
{
  // if expression changes we have to rebuild the eval tree structure
  if (which == &this->expression) {
    for (int i = 0; i < this->evaluatorList.getLength(); i++) {
      so_eval_delete(this->evaluatorList[i]);
    }
    this->evaluatorList.truncate(0);
  }
}

// callback from evaluator. Reads values from temporay registers
void
SoCalculator::readfieldcb(const char *fieldname, float *data, void *userdata)
{
  SoCalculator *thisp = (SoCalculator*) userdata;
  if (fieldname[0] == 'o') {
    //
    // FIXME: I'm not quite sure if it should be legal to read from an
    // output field. Investigate. pederb, 20000307
    //

    // this will work if output was set in an earlier expression
    if ((fieldname[1] >= 'A') && (fieldname[1] <= 'D')) {
      int idx = fieldname[1] - 'A';
      data[0] = thisp->oA_oD[idx][0];
      data[1] = thisp->oA_oD[idx][1];
      data[2] = thisp->oA_oD[idx][2];
    }
    else {
      assert((fieldname[1] >= 'a') && (fieldname[1] <= 'd'));
      int idx = fieldname[1] - 'a';
      data[0] = thisp->oa_od[idx];
    }
  }
  else if (fieldname[0] == 't') {
    if ((fieldname[1] >= 'A') && (fieldname[1] <= 'H')) {
      int idx = fieldname[1] - 'A';
      data[0] = thisp->tA_tH[idx][0];
      data[1] = thisp->tA_tH[idx][1];
      data[2] = thisp->tA_tH[idx][2];
    }
    else {
      assert((fieldname[1] >= 'a') && (fieldname[1] <= 'h'));
      int idx = fieldname[1] - 'a';
      data[0] = thisp->ta_th[idx];
    }
  }
  else if ((fieldname[0] >= 'A') && (fieldname[0] <= 'H')) {
    int idx = fieldname[0] - 'A';
    data[0] = thisp->A_H[idx][0];
    data[1] = thisp->A_H[idx][1];
    data[2] = thisp->A_H[idx][2];
  }
  else {
    assert((fieldname[0] >= 'a') && (fieldname[0] <= 'h'));
    int idx = fieldname[0] - 'a';
    data[0] = thisp->a_h[idx];
  }
}

// callback from evaluator. Writes values into temporary registers
void
SoCalculator::writefieldcb(const char *fieldname, float *data,
                           int comp, void *userdata)
{
  SoCalculator *thisp = (SoCalculator*) userdata;
  if (fieldname[0] == 'o') {
    if ((fieldname[1] >= 'A') && (fieldname[1] <= 'D')) {
      int idx = fieldname[1] - 'A';
      if (comp >= 0) {
        thisp->oA_oD[idx][comp] = data[0];
      }
      else {
        thisp->oA_oD[idx][0] = data[0];
        thisp->oA_oD[idx][1] = data[1];
        thisp->oA_oD[idx][2] = data[2];
      }
    }
    else {
      assert((fieldname[1] >= 'a') && (fieldname[1] <= 'd'));
      int idx = fieldname[1] - 'a';
      thisp->oa_od[idx] = data[0];
    }
  }
  else if (fieldname[0] == 't') {
    if ((fieldname[1] >= 'A') && (fieldname[1] <= 'H')) {
      int idx = fieldname[1] - 'A';
      if (comp >= 0) {
        thisp->tA_tH[idx][comp] = data[0];
      }
      else {
        thisp->tA_tH[idx][0] = data[0];
        thisp->tA_tH[idx][1] = data[1];
        thisp->tA_tH[idx][2] = data[2];
      }
    }
    else {
      assert((fieldname[1] >= 'a') && (fieldname[1] <= 'h'));
      int idx = fieldname[1] - 'a';
      thisp->ta_th[idx] = data[0];
    }
  }
  else {
    assert(0 && "should not happen");
  }
}
