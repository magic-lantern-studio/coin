#ifndef COIN_VBO_H
#define COIN_VBO_H

/**************************************************************************\
 *
 *  This file is part of the Coin 3D visualization library.
 *  Copyright (C) 1998-2005 by Systems in Motion.  All rights reserved.
 *
 *  This library is free software; you can redistribute it and/or
 *  modify it under the terms of the GNU General Public License
 *  ("GPL") version 2 as published by the Free Software Foundation.
 *  See the file LICENSE.GPL at the root directory of this source
 *  distribution for additional information about the GNU GPL.
 *
 *  For using Coin with software that can not be combined with the GNU
 *  GPL, and for taking advantage of the additional benefits of our
 *  support services, please contact Systems in Motion about acquiring
 *  a Coin Professional Edition License.
 *
 *  See <URL:http://www.coin3d.org/> for more information.
 *
 *  Systems in Motion, Postboks 1283, Pirsenteret, 7462 Trondheim, NORWAY.
 *  <URL:http://www.sim.no/>.
 *
\**************************************************************************/

#ifndef COIN_INTERNAL
#error this is a private header file
#endif /* !COIN_INTERNAL */

#include <Inventor/system/gl.h>
#include <Inventor/misc/SbHash.h>
#include <Inventor/C/glue/gl.h>

class SoVBO {
 public:
  SoVBO(const GLenum target = GL_ARRAY_BUFFER,
        const GLenum usage = GL_STATIC_DRAW);
  ~SoVBO();
  
  void setData(const GLvoid * data, intptr_t size);  
  void bindBuffer(uint32_t contextid);
  
 private:
  static void context_destruction_cb(uint32_t context, void * userdata);
  static void vbo_schedule(const uint32_t & key,
                           const GLuint & value,
                           void * closure);
  static void vbo_delete(void * closure, uint32_t contextid);
  
  GLenum target;
  GLenum usage;
  const GLvoid * data;
  intptr_t datasize;

  SbHash <GLuint, uint32_t> vbohash;
};

#endif // COIN_VERTEXARRAYINDEXER_H