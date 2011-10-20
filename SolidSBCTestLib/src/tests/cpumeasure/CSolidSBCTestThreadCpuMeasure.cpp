/*
 * CSolidSBCTestThreadCpuMeasure.cpp
 *
 *  Created on: 20.10.2011
 *      Author: Moritz Wagner
 */

#include "CSolidSBCTestThreadCpuMeasure.h"
#include "CSolidSBCTestConfigCpuMeasure.h"
#include "CSolidSBCTestResultCpuMeasure.h"

#include "../../../../SolidSBCSDK/src/thread/CSolidSBCThread.h"
#include "../../../../SolidSBCSDK/src/debug/CSolidSBCPerformanceCounter.h"

#include "../../interface/CSolidSBCTestManagerImpl.h"

#include <cmath>

//TODO: disable optimizations
//#pragma optimize( "", off )

CSolidSBCTestThreadCpuMeasure::CSolidSBCTestThreadCpuMeasure()
{
}

CSolidSBCTestThreadCpuMeasure::~CSolidSBCTestThreadCpuMeasure()
{
}

void* CSolidSBCTestThreadCpuMeasure::ThreadFunc(void* pParam)
{
	CSolidSBCThread::PSSBC_THREAD_PARAM pThreadParam = reinterpret_cast<CSolidSBCThread::PSSBC_THREAD_PARAM>(pParam);
	CSolidSBCTestConfigCpuMeasure*      pTestConfig  = reinterpret_cast<CSolidSBCTestConfigCpuMeasure*>(pThreadParam->pParam);
	CSolidSBCThread*                    pThread      = reinterpret_cast<CSolidSBCThread*>(pThreadParam->pInstance);

	//cache config parameters to save overhead parsing xml each
	//time requested
	unsigned int nAdditionCnt = pTestConfig->GetAdditionCnt();
	unsigned int nDivisionCnt = pTestConfig->GetDivisionCnt();
	double dFixMultiplierTreshold   = pTestConfig->GetFixMultiplierTreshold();
	unsigned int nAutoFixMultiplier = pTestConfig->GetAutoFixMultiplier();
	bool bTransmitData              = pTestConfig->GetTransmitData();

	CSolidSBCPerformanceCounter cnt, cntOverAll;
	double              dAddCnt = 0, dDivCnt = 0, dOverallCnt, dAddLoop = 0, dDivLoop = 0;
	unsigned long long	ullAdditionMtlp = 1, ullDivisionMtlp = 1;
	unsigned long long	ullAddTotalSteps = 0,ullDivTotalSteps = 0;
	unsigned long long	lCounter = 0;

	while ( 1 ) {

		dAddCnt  = 0.0f;
		dDivCnt  = 0.0f;
		dAddLoop = 0.0f;
		dDivLoop = 0.0f;

		//start overall counter
		cntOverAll.Start();

		//calculate needed steps
		ullAddTotalSteps = ( ((unsigned long long)nAdditionCnt) * ullAdditionMtlp );
		ullDivTotalSteps = ( ((unsigned long long)nDivisionCnt) * ullDivisionMtlp );

		/*
		//measure empty add loop
		cnt.Start();
		for (ULONG i = 0; i < ulAddTotalSteps; i++){
		}
		dAddLoop = cnt.Stop();

		//measure empty division loop
		cnt.Start();
		for (ULONG i = 0; i < ulDivTotalSteps; i++){
		}
		dDivLoop = cnt.Stop();
		*/

		//measure add
		cnt.Start();
		if ( nAdditionCnt )
		{
			for (unsigned long long i = 0; i < ullAddTotalSteps; i++){
				lCounter++;}
		}
		dAddCnt = cnt.Stop();

		//measure division
		cnt.Start();
		if ( nDivisionCnt )
		{
			for (unsigned long long i = 0; i < ullDivTotalSteps; i++){
				lCounter = lCounter/2;}
		}
		dDivCnt = cnt.Stop();

		//hold current multipliers
		unsigned long long recentAddMultiplier = ullAdditionMtlp;
		unsigned long long recentDivMultiplier = ullDivisionMtlp;

		//fix multipliers
		if ( nAutoFixMultiplier )
		{
			FixMultipliers(dAddCnt, nAdditionCnt, &ullAdditionMtlp, dFixMultiplierTreshold, nAutoFixMultiplier );
			FixMultipliers(dDivCnt, nDivisionCnt, &ullDivisionMtlp, dFixMultiplierTreshold, nAutoFixMultiplier );
		}

		dOverallCnt = cntOverAll.Stop();

		//send result
		if ( bTransmitData )
		{
			CSolidSBCTestResultCpuMeasure* pResult = new CSolidSBCTestResultCpuMeasure();
			pResult->SetAddDuration(dAddCnt);
			pResult->SetAddMultiplier(recentAddMultiplier);
			pResult->SetDivDuration(dDivCnt);
			pResult->SetDivMultiplier(recentDivMultiplier);
			pResult->SetOverallDuration(dOverallCnt);
			CSolidSBCTestManagerImpl::GetInstance()->AddResult(pResult);
		}

		//exit thread?
		if ( pThread->ShallEnd() ) {
				break;}
	}

	return 0;
}

unsigned int CSolidSBCTestThreadCpuMeasure::FixMultipliers( double dCnt, unsigned int nStepCnt, unsigned long long* pullMtpl, double dFixMultiplierThreshold, unsigned int nMaxSecs )
{
	// Zeit (soll)	   Multi(soll)
	// ----------   =  -----------
	// Zeit (ist)      Multi(ist)

	double dMaxSecs  = (double)nMaxSecs;

	if (  ( nMaxSecs != 0 )										//may and should not be zero
			   && ( abs(dMaxSecs - dCnt) > dFixMultiplierThreshold )	//time out of threshold?
	   ){
		double dNewMtlp  = ( dMaxSecs / dCnt ) * ((double)*pullMtpl);
		*pullMtpl = (unsigned long long)dNewMtlp;
		if ( (*pullMtpl) == 0 )
			*pullMtpl = 1; //zero multiplier, no good, set at least to one
	   }
	   return 0;
}

//#pragma optimize( "", on )
