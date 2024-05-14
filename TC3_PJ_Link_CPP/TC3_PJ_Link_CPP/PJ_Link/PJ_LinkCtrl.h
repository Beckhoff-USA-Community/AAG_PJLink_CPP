///////////////////////////////////////////////////////////////////////////////
// PJ_LinkCtrl.h

#ifndef __PJ_LINKCTRL_H__
#define __PJ_LINKCTRL_H__

#include <atlbase.h>
#include <atlcom.h>


#include "resource.h"       // main symbols
#include "PJ_LinkW32.h"
#include "TcBase.h"
#include "PJ_LinkClassFactory.h"
#include "TcOCFCtrlImpl.h"

class CPJ_LinkCtrl 
	: public CComObjectRootEx<CComMultiThreadModel>
	, public CComCoClass<CPJ_LinkCtrl, &CLSID_PJ_LinkCtrl>
	, public IPJ_LinkCtrl
	, public ITcOCFCtrlImpl<CPJ_LinkCtrl, CPJ_LinkClassFactory>
{
public:
	CPJ_LinkCtrl();
	virtual ~CPJ_LinkCtrl();

DECLARE_REGISTRY_RESOURCEID(IDR_PJ_LINKCTRL)
DECLARE_NOT_AGGREGATABLE(CPJ_LinkCtrl)

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CPJ_LinkCtrl)
	COM_INTERFACE_ENTRY(IPJ_LinkCtrl)
	COM_INTERFACE_ENTRY(ITcCtrl)
	COM_INTERFACE_ENTRY(ITcCtrl2)
END_COM_MAP()

};

#endif // #ifndef __PJ_LINKCTRL_H__
