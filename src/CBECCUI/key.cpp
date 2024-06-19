// key.cpp : Defines the program's analysis/reporting security key
//
/**********************************************************************
 *  Copyright (c) 2012-2017, California Energy Commission
 *  Copyright (c) 2012-2017, Wrightsoft Corporation
 *  All rights reserved.
 *  Redistribution and use in source and binary forms, with or without
 *  modification, are permitted provided that the following conditions are met:
 *  - Redistributions of source code must retain the above copyright notice, this
 *    list of conditions and the following disclaimer.
 *  - Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions, the following disclaimer in the documentation
 *    and/or other materials provided with the distribution.
 *  - Neither the name of the California Energy Commission nor the names of its
 *    contributors may be used to endorse or promote products derived from this
 *    software without specific prior written permission.
 *  DISCLAIMER: THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 *  "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
 *  THE IMPLIED WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 *  NON-INFRINGEMENT ARE DISCLAIMED. IN NO EVENT SHALL CALIFORNIA ENERGY COMMISSION,
 *  WRIGHTSOFT CORPORATION, ITRON, INC. OR ANY OTHER AUTHOR OR COPYRIGHT HOLDER OF
 *  THIS SOFTWARE (COLLECTIVELY, THE "AUTHORS") BE LIABLE FOR ANY DIRECT, INDIRECT,
 *  INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 *  LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA,
 *  OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
 *  LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE
 *  OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF
 *  ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.  EACH LICENSEE AND SUBLICENSEE OF THE
 *  SOFTWARE AGREES NOT TO ASSERT ANY CLAIM AGAINST ANY OF THE AUTHORS RELATING TO
 *  THIS SOFTWARE, WHETHER DUE TO PERFORMANCE ISSUES, TITLE OR INFRINGEMENT ISSUES,
 *  STRICT LIABILITY OR OTHERWISE.
 **********************************************************************/

#include "stdafx.h"
#include "CUIGlobl.h"


#ifdef UI_CANRES
 #ifdef  UI_PROGYEAR2025
  CString esSecurityKey = "599@3d9@AA8@A7(2;5IeRqJJy)NJ=Ovq87Pb6;wA94>aesl))?4rNqK9pyLL2f;.";	// reusing 2019/22 for now...
 #elif  UI_PROGYEAR2022
  CString esSecurityKey = "599@3d9@AA8@A7(2;5IeRqJJy)NJ=Ovq87Pb6;wA94>aesl))?4rNqK9pyLL2f;.";	// reusing 2019 for now...
 #elif  UI_PROGYEAR2019
  CString esSecurityKey = "599@3d9@AA8@A7(2;5IeRqJJy)NJ=Ovq87Pb6;wA94>aesl))?4rNqK9pyLL2f;.";	// 2019.1.0
 #elif  UI_PROGYEAR2016
  CString esSecurityKey = "599@319@AA8@A7ay:jg0Ii2R@;ay+<Q86Ntvuu/1Snp,b0zs9f).Ka0fg/m.,L;J";
 #else
  CString esSecurityKey = "599@319@AA8@A6vfow>Nq0jd,hQtx7@nP0::n?g3Wu2jdK9wpOjg=q<<8suO/I)S";
 #endif
#elif  UI_CARES
 #ifdef  UI_PROGYEAR2025
  CString esSecurityKey = "599@3d9@AA8@A8m89Q96=o*7z//ibKp:I3<-il+qdNjIpJf.q>03svMw@8(-1n;+";	// reusing 2019/22 for now...
 #elif  UI_PROGYEAR2022
  CString esSecurityKey = "599@3d9@AA8@A8m89Q96=o*7z//ibKp:I3<-il+qdNjIpJf.q>03svMw@8(-1n;+";	// reusing 2019 for now...
 #elif  UI_PROGYEAR2019
  CString esSecurityKey = "599@3d9@AA8@A8m89Q96=o*7z//ibKp:I3<-il+qdNjIpJf.q>03svMw@8(-1n;+";	// 2019.1.0
 #elif  UI_PROGYEAR2016
  //CString esSecurityKey = "599@3d9@AA8@A6S?gvztikhLub8q7qkm(M+rr/0xQwRxO9rfz;djO/)LmS/P/@s7";	// 2016.3.0
  CString esSecurityKey = "599@3d9@AA8@A6/br69,brb65evk,dq-(f7O0g8c,@Jx:y@+x9n3y9ySk4n7ckOe";	// 2016.3.1
 #else
  CString esSecurityKey = "599@319@AA8@A6vfow>Nq0jd,hQtx7@nP0::n?g3Wu2jdK9wpOjg=q<<8suO/I)S";
 #endif
#else
CString esSecurityKey = "599@3d9@AA8@A6Mo<n(aQ9P(y><9wQM06Owb:mmPA97+M65bL(sS1jN1dzW?@s:(";
#endif


// ASCII codes:
//   39- 47 : '-/  ->   91- 84
//   48- 57 : 0-9  ->   83- 72
//   58- 64 : :-@  ->   73- 66
//   65- 91 : A-[  ->   65- 39
//       92 : \    -> never translate from or to    
//   93- 96 : ]-`  ->  126-121
//   97-122 : a-z  ->  120- 95
//  123-126 : {-~  ->   94- 91
void TweakString( char* lpBuf, int length )  // consistent w/ BEMCmpMgr: CM_CharSwap()
{  for (int i = 0; i < length; i++)
	{	if      (lpBuf[i]>=39 && lpBuf[i]<=91)
			      lpBuf[i] = 130 -lpBuf[i];
		else if (lpBuf[i]>=93 && lpBuf[i]<=126)
			      lpBuf[i] = 219 -lpBuf[i];
		else     lpBuf[i] =      lpBuf[i];
	}
}

