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

/*
  The purpose of this file is to make a small wrapper "tool" around
  the TextureFilenameElement extension element, just for showing
  example code on how to make use of a user-defined custom element.

  The code goes like this:

  We initialize the element, enable it for the SoCallbackAction, read
  a scene graph file, set callbacks on SoTexture2 and all shape nodes
  and applies the SoCallbackAction. The callbacks will then print out
  the texture filename information from the TextureFilenameElement
  each time an interesting node is hit.


  Check the code in texturefilenameelement.cpp for further information
  on how to construct your own elements.


  Code by Peder Blekken <pederb@sim.no>. Cleaned up, integrated in
  Coin distribution and commented by Morten Eriksen <mortene@sim.no>.
  1999-12-09.
*/

#include <Inventor/SoDB.h>
#include <Inventor/SoInput.h>
#include <Inventor/actions/SoCallbackAction.h>
#include <Inventor/nodes/SoSeparator.h>
#include <Inventor/nodes/SoTexture2.h>
#include <Inventor/nodes/SoShape.h>
#include <Inventor/misc/SoState.h>
#include <stdio.h>

#include "texturefilenameelement.h"


SoCallbackAction::Response
pre_tex2_cb(void * /*data*/, SoCallbackAction * action, const SoNode * node)
{
  const SbString & filename = ((SoTexture2 *)node)->filename.getValue();
  TextureFilenameElement::set(action->getState(), (SoNode *)node, filename);

  fprintf(stdout, "=> New texture: %s\n",
          filename.getLength() == 0 ? "<inlined>" : filename.getString());

  return SoCallbackAction::CONTINUE;
}

SoCallbackAction::Response
pre_shape_cb(void * /*data*/, SoCallbackAction * action, const SoNode * node)
{
  const SbString & filename =
    TextureFilenameElement::get(action->getState());

  fprintf(stdout, "Texturemap on %s: %s\n",
          node->getTypeId().getName().getString(),
          filename.getLength() == 0 ? "<inlined>" : filename.getString());

  return SoCallbackAction::CONTINUE;
}

void
usage(const char * appname)
{
  fprintf(stderr, "\n\tUsage: %s <modelfile.iv>\n\n", appname);
  fprintf(stderr,
          "\tLists all texture filenames in the model file,\n"
          "\tand on which shape nodes they are used.\n\n"
          "\tThe purpose of this example utility is simply to\n"
          "\tshow how to create and use an extension element for\n"
          "\tscene graph traversal.\n\n");
}

int
main(int argc, char ** argv)
{
  if (argc != 2) {
    usage(argv[0]);
    exit(1);
  }

  SoDB::init();

  TextureFilenameElement::initClass();
  SO_ENABLE(SoCallbackAction, TextureFilenameElement);

  SoInput input;
  if (!input.openFile(argv[1])) {
    fprintf(stderr, "ERROR: couldn't open file ``%s''.\n", argv[1]);
    exit(1);
  }

  SoSeparator * root = SoDB::readAll(&input);
  if (root) {
    SoCallbackAction cbaction;
    cbaction.addPreCallback(SoTexture2::getClassTypeId(), pre_tex2_cb, NULL);
    cbaction.addPreCallback(SoShape::getClassTypeId(), pre_shape_cb, NULL);
    cbaction.apply(root);
    return 0;
  }
  return 1;
}
