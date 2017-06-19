// PersistentWaitCursor.cpp: implementation of the CPersistentWaitCursor class.
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
#include "PersistentWaitCursor.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////////////
//                                                                          //
// CPersistentWaitCursorMonitor                                             //
//                                                                          //
//////////////////////////////////////////////////////////////////////////////

class CPersistentWaitCursorMonitor
{
public:
    CPersistentWaitCursorMonitor() { m_nCursorsShown = 0; };

    void AddWaitCursor();
    void RemoveWaitCursor();
    bool WaitCursorShown();

private:
    int                 m_nCursorsShown;
    CCriticalSection    m_CriticalSection;
};

//////////////////////////////////////////////////////////////////////////////
//                                                                          //
//  Function : AddWaitCursor                                                //
//  Purpose  : Registers a request to show the wait cursor                  //
//  Params   : None                                                         //
//  Returns  : None                                                         //
//  Throws   : None                                                         //
//                                                                          //
//////////////////////////////////////////////////////////////////////////////

void CPersistentWaitCursorMonitor::AddWaitCursor()
{
    // Increment the cursor counter, protecting access to the counter using a critical section
    CSingleLock lock(&m_CriticalSection);
    lock.Lock();  

    m_nCursorsShown++;

    lock.Unlock();
}

//////////////////////////////////////////////////////////////////////////////
//                                                                          //
//  Function : RemoveWaitCursor                                             //
//  Purpose  : Registers a request to hide the wait cursor                  //
//  Params   : None                                                         //
//  Returns  : None                                                         //
//  Throws   : None                                                         //
//                                                                          //
//////////////////////////////////////////////////////////////////////////////

void CPersistentWaitCursorMonitor::RemoveWaitCursor()
{
    // Decrement the cursor counter, protecting access to the counter using a critical section
    CSingleLock lock(&m_CriticalSection);
    lock.Lock();  

    m_nCursorsShown--;

    lock.Unlock();
}

//////////////////////////////////////////////////////////////////////////////
//                                                                          //
//  Function : WaitCursorShown                                              //
//  Purpose  : Indicates if the wait cursor is currently shown (i.e. the    //
//             number of requests to show the cursor is greater than the    //
//             number of requests to hide the cursor.                       //
//  Params   : None                                                         //
//  Returns  :                                                              //
//  Throws   : None                                                         //
//                                                                          //
//////////////////////////////////////////////////////////////////////////////

bool CPersistentWaitCursorMonitor::WaitCursorShown()
{
    // See if we have one or more show requests, protecting access to the counter using a critical section
    CSingleLock lock(&m_CriticalSection);
    lock.Lock();  

    bool bShown = m_nCursorsShown > 0;

    lock.Unlock();

    return bShown;
}

CPersistentWaitCursorMonitor    waitMonitor;    // We have one instance of the monitor, used by all instances of CPersistentWaitCursor


//////////////////////////////////////////////////////////////////////////////
//                                                                          //
// CPersistentWaitCursor                                                    //
//                                                                          //
//////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////
//                                                                          //
//  Function : CPersistentWaitCursor                                        //
//  Purpose  : Constructor - registers wait cursor show request             //
//  Params   : None                                                         //
//  Returns  : N/A                                                          //
//  Throws   : None                                                         //
//                                                                          //
//////////////////////////////////////////////////////////////////////////////

CPersistentWaitCursor::CPersistentWaitCursor()
{
    // Register ourselves with the monitor
    waitMonitor.AddWaitCursor();
}

//////////////////////////////////////////////////////////////////////////////
//                                                                          //
//  Function : ~CPersistentWaitCursor                                       //
//  Purpose  : Destructor - registers wait cursor hide request              //
//  Params   : None                                                         //
//  Returns  : N/A                                                          //
//  Throws   : None                                                         //
//                                                                          //
//////////////////////////////////////////////////////////////////////////////

CPersistentWaitCursor::~CPersistentWaitCursor()
{
    // Unregister ourselves with the monitor
    waitMonitor.RemoveWaitCursor();
}

//////////////////////////////////////////////////////////////////////////////
//                                                                          //
//  Function : WaitCursorShown                                              //
//  Purpose  : Static function which determines if wait cursor is shown     //
//  Params   : None                                                         //
//  Returns  : true if the wait cursor is shown, false otherwise            //
//  Throws   : None                                                         //
//                                                                          //
//////////////////////////////////////////////////////////////////////////////

bool CPersistentWaitCursor::WaitCursorShown()
{
    // Determine if we are to show, i.e. the number of show requests exceeds the number of hide requests
    return waitMonitor.WaitCursorShown();
}
