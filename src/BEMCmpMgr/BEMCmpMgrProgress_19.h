// bemcm_I.H - externs used within 'BEMCmpMgr*.DLL'
//
/**********************************************************************
 *  Copyright (c) 2012-2017, California Energy Commission
 *  Copyright (c) 2022, SAC Software Solutions, LLC
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


#ifndef __BEMCMPMGRPROGRESS_19_H__
#define __BEMCMPMGRPROGRESS_19_H__


// -- Non-residential analysis progress stuff --
//		2,147,483,647 - max long int
//		  ABB,CCC,CDD - compliance analysis
//		  AEE,EEF,FFF - batch processing

#define  BCM_NRP_AMult  100000000
#define  BCM_NRP_BMult    1000000
#define  BCM_NRP_CMult        100
#define  BCM_NRP_EMult      10000
#define  BCM_NRP_ComplianceProgressID(  lAnalType, lAnalStep, lModels, lSimProg )	(long) ( (lAnalType * BCM_NRP_AMult) + (lAnalStep * BCM_NRP_BMult) + (lModels * BCM_NRP_CMult) + lSimProg )

// A: analysis type
	#define	BCM_NRP_Type_Comp			0	//	0-compliance
	#define	BCM_NRP_Type_Batch		1	//	1-batch processing
	#define	BCM_NRP_Type( lNRP )			(long) (lNRP / BCM_NRP_AMult)
	#define	BCM_NRP_TypeIsComp(  lNRP )	(long) (BCM_NRP_Type( lNRP ) == BCM_NRP_Type_Comp  ? 1 : 0)
	#define	BCM_NRP_TypeIsBatch( lNRP )	(long) (BCM_NRP_Type( lNRP ) == BCM_NRP_Type_Batch ? 1 : 0)

// B: analysis step - valid range 0-99
	#define	BCM_NRP_Step_None			0	//	0-blank
	#define	BCM_NRP_Step_Init			1	//	1-Initialization
	#define	BCM_NRP_Step_Read			2	//	2-Read/Parse Input
	#define	BCM_NRP_Step_MPrep		3	//	3-Preparing Model(s)
	#define	BCM_NRP_Step_MTrans		4	//	4-Translating Model(s)
	#define	BCM_NRP_Step_MSim			5	//	5-Simulating Model(s)
	#define	BCM_NRP_Step_MSimRes		6	//	6-Simulation Results
	#define	BCM_NRP_Step_Store		7	//	7-Store Model & Result
	#define	BCM_NRP_Step_Report		8	//	8-Report Generation
	#define	BCM_NRP_Step_Done			9	//	9-Completed
	#define	BCM_NRP_Step( lNRP )			(long) ((lNRP - ((lNRP / BCM_NRP_AMult) * BCM_NRP_AMult)) / BCM_NRP_BMult)

// C:	bitwise flags for up to 13 individual models
		//	          0 - none
		//	0 0000 0000 0001 - u  / user input model		(not included in normal compliance analysis)
		//	0 0000 0000 0010 - zp / sizing proposed model
		//	0 0000 0000 0100 - zb / sizing baseline model
		//	0 0000 0000 1000 - ap / annual proposed model
		//	0 0000 0001 0000 - ab / annual baseline model
	#define	BCM_NRP_Model( lNRP )				(long) ((lNRP - ((lNRP / BCM_NRP_BMult) * BCM_NRP_BMult)) / BCM_NRP_CMult)
	  // int BCM_NRP_NumModels( int iModels )			- defined in .cpp
	  // int BCM_NRP_NumProgressModels( long lNRP )	- defined in .cpp
	#define	BCM_NRP_Model_None		  0	//	0-none
						// generic models 1-13
	#define	BCM_NRP_Model_1			  1
	#define	BCM_NRP_Model_2			  2
	#define	BCM_NRP_Model_3			  4
	#define	BCM_NRP_Model_4			  8
	#define	BCM_NRP_Model_5			 16
	#define	BCM_NRP_Model_6			 32
	#define	BCM_NRP_Model_7			 64
	#define	BCM_NRP_Model_8			128
	#define	BCM_NRP_Model_9			256
	#define	BCM_NRP_Model_10			512
	#define	BCM_NRP_Model_11		  1024
	#define	BCM_NRP_Model_12		  2048
	#define	BCM_NRP_Model_13		  4096
						// model names from CA non-res rules
	#define	BCM_NRP_Model_u			  1	// user model
	#define	BCM_NRP_Model_zp			  2	// proposed sizing
	#define	BCM_NRP_Model_zb			  4	// baseline sizing
	#define	BCM_NRP_Model_ap			  8	// proposed annual
	#define	BCM_NRP_Model_ab			 16	// baseline annual
	#define	BCM_NRAP_Model_zp			  2 	// ASHRAE proposed sizing
	#define	BCM_NRAP_Model_zb1		  4 	// ASHRAE baseline sizing - orientation 1
	#define	BCM_NRAP_Model_zb2		  8 	// ASHRAE baseline sizing - orientation 2
	#define	BCM_NRAP_Model_zb3		 16 	// ASHRAE baseline sizing - orientation 3
	#define	BCM_NRAP_Model_zb4		 32 	// ASHRAE baseline sizing - orientation 4
	#define	BCM_NRAP_Model_ap			 64 	// ASHRAE proposed annual
	#define	BCM_NRAP_Model_ab1		128 	// ASHRAE baseline annual - orientation 1
	#define	BCM_NRAP_Model_ab2		256 	// ASHRAE baseline annual - orientation 2
	#define	BCM_NRAP_Model_ab3		512 	// ASHRAE baseline annual - orientation 3
	#define	BCM_NRAP_Model_ab4	  1024	// bASHRAE aseline annual - orientation 4

// D:	simulation progress - valid range 0-99
	#define	BCM_NRP_Prog( lNRP )			(long) (lNRP % BCM_NRP_CMult)
	#define	BCM_NRP_Prog_None				 0		// blank
	#define	BCM_NRP_Prog_Init				 1		// Initialization
	#define	BCM_NRP_Prog_Warmup			 2		// Warmup
	#define	BCM_NRP_Prog_Jan   			 3		// Jan
	#define	BCM_NRP_Prog_Feb   			 4		// Feb
	#define	BCM_NRP_Prog_Mar   			 5		// Mar
	#define	BCM_NRP_Prog_Apr   			 6		// Apr
	#define	BCM_NRP_Prog_May   			 7		// May
	#define	BCM_NRP_Prog_Jun   			 8		// Jun
	#define	BCM_NRP_Prog_Jul   			 9		// Jul
	#define	BCM_NRP_Prog_Aug  			10		// Aug
	#define	BCM_NRP_Prog_Sep  			11		// Sep
	#define	BCM_NRP_Prog_Oct  			12		// Oct
	#define	BCM_NRP_Prog_Nov  			13		// Nov
	#define	BCM_NRP_Prog_Dec  			14		// Dec
	#define	BCM_NRP_Prog_Rpt				15		// Reporting

//	E:	1-based index of run being performed
//	F:	Total number of batch runs to be performed

extern int /*CALLBACK*/ CECNRes_ProgressIncrement( long lProgressID );
extern int /*CALLBACK*/ S901G_ProgressIncrement( long lProgressID );


#endif // __BEMCMPMGRPROGRESS_19_H__
