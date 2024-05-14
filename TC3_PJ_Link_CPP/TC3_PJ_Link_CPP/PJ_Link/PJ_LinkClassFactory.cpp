///////////////////////////////////////////////////////////////////////////////
// PJ_LinkClassFactory.cpp
#include "TcPch.h"
#pragma hdrstop

#include "PJ_LinkClassFactory.h"
#include "PJ_LinkServices.h"
#include "PJ_LinkVersion.h"
#include "PJ_Link_Client.h"

BEGIN_CLASS_MAP(CPJ_LinkClassFactory)
///<AutoGeneratedContent id="ClassMap">
	CLASS_ENTRY_LIB(VID_PJ_Link, CID_PJ_LinkCPJ_Link_Client, SRVNAME_PJ_LINK "!CPJ_Link_Client", CPJ_Link_Client)
///</AutoGeneratedContent>
END_CLASS_MAP()

CPJ_LinkClassFactory::CPJ_LinkClassFactory() : CObjClassFactory()
{
	TcDbgUnitSetImageName(TCDBG_UNIT_IMAGE_NAME_TMX(SRVNAME_PJ_LINK));
#if defined(TCDBG_UNIT_VERSION)
	TcDbgUnitSetVersion(TCDBG_UNIT_VERSION(PJ_Link));
#endif //defined(TCDBG_UNIT_VERSION)
}

