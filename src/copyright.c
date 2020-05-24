#include "global.h"
#include "copyright.h"


const char program_name[] = PROGRAM_NAME; 
enum { program_name__cstrlen = ARRAY_SIZE(program_name) - 1 }; 
const int program_name__len = program_name__cstrlen; 


const char program_copyright[] = 
//"ISC License" "\n"
//"http://...." "\n"
//"" "\n"
  //"_Software_ : calc2" "\n"
  //"_Authors_ : Father Christmas" "\n"
  //"_Description_ : ...XXX..." "\n"
  //"" "\n"
PROGRAM_NAME "\n" 
  //"Copyright (c) " PROGRAM_COPYRIGHT_YEAR1 " - " PROGRAM_COPYRIGHT_YEAR2 " _Authors_ (as defined above)" "\n"
"Copyright (c) " PROGRAM_COPYRIGHT_YEAR1 " - " PROGRAM_COPYRIGHT_YEAR2 " " "\n"
"All rights reserved." "\n"
"" "\n"
  //"e-mail to contact the _Authors_ : someone@provider.com" "\n"
  //"" "\n"
  //"" "\n"
"Redistribution and use in source and binary forms, with or without" "\n"
"modification, are permitted provided that the following conditions" "\n"
"are met:" "\n"
"1. Redistributions of source code must retain the above copyright" "\n"
"   notice, this list of conditions and the following disclaimer." "\n"
"2. Redistributions in binary form must reproduce the above copyright" "\n"
"   notice, this list of conditions and the following disclaimer in the" "\n"
"   documentation and/or other materials provided with the distribution." "\n"
"" "\n"
"THIS SOFTWARE IS PROVIDED BY THE _AUTHORS_ ``AS IS'' AND ANY EXPRESS" "\n"
"OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED" "\n"
"WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE" "\n"
"DISCLAIMED. IN NO EVENT SHALL THE _AUTHORS_ BE LIABLE FOR ANY DIRECT," "\n"
"INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES" "\n"
"(INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR" "\n"
"SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)" "\n"
"HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT," "\n"
"STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING" "\n"
"IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE" "\n"
"POSSIBILITY OF SUCH DAMAGE." "\n" 
"" "\n"
"NB: We mostly do not care of what you do with this code as long as " "\n" 
"    you do not prevent us nor others from using it." "\n"
;
enum { program_copyright__strlen = ARRAY_SIZE(program_copyright) - 1 }; 

const int program_copyright__len = program_copyright__strlen; 
