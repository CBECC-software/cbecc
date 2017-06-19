// pathname.cpp - implementation of the CPathName class
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

/*********************************************************************/
/*                                                                   */
/*  (c) Copyright 1997, Regional Economic Research, Inc.             */
/*  All Rights Reserved.                                             */
/*                                                                   */
/*  Use, reproduction, or disclosure is subject to the restrictions  */
/*  set forth in FAR Part 52.227-19 and Contract No. 268134-A-A6     */
/*  awarded by Battelle Memorial Institute, Pacific Northwest        */
/*  Division, for the U.S. Department of Energy.                     */
/*                                                                   */
/*********************************************************************/

#include "stdafx.h"
#include "pathname.h"


/////////////////////////////////////////////////////////////////////////////
//
// CPathName Class Function:  GetDrive()
//
// Purpose ------------------------------------------------------------------
//   Fill the CString argument with the drive component of the pathname.
//   
// Arguments ----------------------------------------------------------------
//   CString& drive : CString to populate with drive
//   
// Return Value -------------------------------------------------------------
//   None
//   
// Notes --------------------------------------------------------------------
//   None
//   
/////////////////////////////////////////////////////////////////////////////
void CPathName::GetDrive( CString& drive ) const
{
   _splitpath( GetString(), drive.GetBuffer( _MAX_DRIVE ), NULL, NULL, NULL );
   drive.ReleaseBuffer();
}


/////////////////////////////////////////////////////////////////////////////
//
// CPathName Class Function:  GetDir()
//
// Purpose ------------------------------------------------------------------
//   Fill the CString argument with the directory component of the pathname.
//   
// Arguments ----------------------------------------------------------------
//   CString& dir : CString to populate with directory
//   
// Return Value -------------------------------------------------------------
//   None
//   
// Notes --------------------------------------------------------------------
//   None
//   
/////////////////////////////////////////////////////////////////////////////
void CPathName::GetDir( CString& dir ) const
{
   _splitpath( GetString(), NULL, dir.GetBuffer( _MAX_DIR ), NULL, NULL );
   dir.ReleaseBuffer();
}


/////////////////////////////////////////////////////////////////////////////
//
// CPathName Class Function:  GetNode()
//
// Purpose ------------------------------------------------------------------
//   Fill the CString argument with the node (filename) component of the pathname.
//   
// Arguments ----------------------------------------------------------------
//   CString& node : CString to populate with node (filename)
//   
// Return Value -------------------------------------------------------------
//   None
//   
// Notes --------------------------------------------------------------------
//   None
//   
/////////////////////////////////////////////////////////////////////////////
void CPathName::GetNode( CString& node ) const
{
   _splitpath( GetString(), NULL, NULL, node.GetBuffer( _MAX_FNAME ), NULL );
   node.ReleaseBuffer();
}


/////////////////////////////////////////////////////////////////////////////
//
// CPathName Class Function:  GetExt()
//
// Purpose ------------------------------------------------------------------
//   Fill the CString argument with the file extension component of the pathname.
//   
// Arguments ----------------------------------------------------------------
//   CString& ext : CString to populate with file extension
//   
// Return Value -------------------------------------------------------------
//   None
//   
// Notes --------------------------------------------------------------------
//   None
//   
/////////////////////////////////////////////////////////////////////////////
void CPathName::GetExt( CString& ext ) const
{
   _splitpath( GetString(), NULL, NULL, NULL, ext.GetBuffer( _MAX_EXT ) );
   ext.ReleaseBuffer();
}


/////////////////////////////////////////////////////////////////////////////
//
// CPathName Class Function:  SetComponents()
//
// Purpose ------------------------------------------------------------------
//   Sets each individual component of the pathname based on the functions arguments.
//   
// Arguments ----------------------------------------------------------------
//   const char* drive : the string to set this pathname's drive component to
//   const char* dir   : the string to set this pathname's directory component to
//   const char* node  : the string to set this pathname's node (filename) component to
//   const char* ext   : the string to set this pathname's file extension component to
//   
// Return Value -------------------------------------------------------------
//   None
//   
// Notes --------------------------------------------------------------------
//   None
//   
/////////////////////////////////////////////////////////////////////////////
void CPathName::SetComponents( const char* drive, const char* dir,
                               const char* node,  const char* ext )
{
   CPathName newDrive = drive;
   CPathName newDir   = dir;
   CPathName newNode  = node;
   CPathName newExt   = ext;

   // If any of the formal parameters are NULL, then we shouldn't
   // change the respective pathname components.
   if( drive == NULL )
      GetDrive( newDrive );
   if( dir == NULL )
      GetDir( newDir );
   if( node == NULL )
      GetNode( newNode );
   if( ext == NULL )
      GetExt( newExt );

   // set final path components
   _makepath( GetBuffer( _MAX_PATH ), newDrive, newDir, newNode, newExt );
   ReleaseBuffer();
}

