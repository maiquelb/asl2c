/*
This file is part of AgentSpeakTranslator.

Copyright (c) 2015, Samuel Bucheli, Department of Computer Science, University
of Oxford. All rights reserved.

Redistribution and use in source and binary forms, with or without 
modification, are permitted provided that the following conditions are met:

1. Redistributions of source code must retain the above copyright notice, this
   list of conditions and the following disclaimer.

2. Redistributions in binary form must reproduce the above copyright notice,
   this list of conditions and the following disclaimer in the documentation
   and/or other materials provided with the distribution.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE 
DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/

/**
 * @file trigger.cpp
 *
 * @author Samuel Bucheli
 */

#include <ostream>

#include "formula.h"
#include "term.h"
#include "trigger.h"
#include "util.h"

std::ostream& operator<<(std::ostream &strm, const triggert &t) 
{
  switch (t.get_op())
  {
    case triggeropt::add:
      strm << "+"; 
      break;
    case triggeropt::del:
      strm << "-";
      break;
    default:
      ASSERT(false, "trigger " << t.get_literal() << " has unknown operation");
      break;
  }
  switch (t.get_type())
  {
    case triggertypet::achieve: 
      strm << "!"; 
      break;
    case triggertypet::percept:
      // nothing to do
      break;
    case triggertypet::test:    
      strm << "?"; 
      break;
    default: 
      ASSERT(false, "trigger " << t.get_literal() << " has unknown type");
      break;
  }
  strm << t.get_literal();
  return strm;
}
