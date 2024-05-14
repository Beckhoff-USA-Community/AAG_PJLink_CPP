///////////////////////////////////////////////////////////////////////////////
// PJ_LinkDriver.h

#ifndef __PJ_LINKDRIVER_H__
#define __PJ_LINKDRIVER_H__

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "TcBase.h"

#define PJ_LINKDRV_NAME        "PJ_LINK"
#define PJ_LINKDRV_Major       1
#define PJ_LINKDRV_Minor       0

#define DEVICE_CLASS CPJ_LinkDriver

#include "ObjDriver.h"

class CPJ_LinkDriver : public CObjDriver
{
public:
	virtual IOSTATUS	OnLoad();
	virtual VOID		OnUnLoad();

	//////////////////////////////////////////////////////
	// VxD-Services exported by this driver
	static unsigned long	_cdecl PJ_LINKDRV_GetVersion();
	//////////////////////////////////////////////////////
	
};

Begin_VxD_Service_Table(PJ_LINKDRV)
	VxD_Service( PJ_LINKDRV_GetVersion )
End_VxD_Service_Table


#endif // ifndef __PJ_LINKDRIVER_H__