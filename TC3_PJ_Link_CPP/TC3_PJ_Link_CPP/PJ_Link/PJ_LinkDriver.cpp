///////////////////////////////////////////////////////////////////////////////
// PJ_LinkDriver.cpp
#include "TcPch.h"
#pragma hdrstop

#include "PJ_LinkDriver.h"
#include "PJ_LinkClassFactory.h"

DECLARE_GENERIC_DEVICE(PJ_LINKDRV)

IOSTATUS CPJ_LinkDriver::OnLoad( )
{
	TRACE(_T("CObjClassFactory::OnLoad()\n") );
	m_pObjClassFactory = new CPJ_LinkClassFactory();

	return IOSTATUS_SUCCESS;
}

VOID CPJ_LinkDriver::OnUnLoad( )
{
	delete m_pObjClassFactory;
}

unsigned long _cdecl CPJ_LinkDriver::PJ_LINKDRV_GetVersion( )
{
	return( (PJ_LINKDRV_Major << 8) | PJ_LINKDRV_Minor );
}

