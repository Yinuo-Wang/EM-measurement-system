
// EM measurement system V2.h : main header file for the PROJECT_NAME application
//

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"		// main symbols


// CEMmeasurementsystemV2App:
// See EM measurement system V2.cpp for the implementation of this class
//

class CEMmeasurementsystemV2App : public CWinApp
{
public:
	CEMmeasurementsystemV2App();

// Overrides
public:
	virtual BOOL InitInstance();

// Implementation

	DECLARE_MESSAGE_MAP()
};

extern CEMmeasurementsystemV2App theApp;
