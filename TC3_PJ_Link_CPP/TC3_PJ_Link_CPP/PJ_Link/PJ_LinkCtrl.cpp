// PJ_LinkCtrl.cpp : Implementation of CTcPJ_LinkCtrl
#include "TcPch.h"
#pragma hdrstop

#include "PJ_LinkW32.h"
#include "PJ_LinkCtrl.h"

/////////////////////////////////////////////////////////////////////////////
// CPJ_LinkCtrl

CPJ_LinkCtrl::CPJ_LinkCtrl() 
	: ITcOCFCtrlImpl<CPJ_LinkCtrl, CPJ_LinkClassFactory>() 
{
}

CPJ_LinkCtrl::~CPJ_LinkCtrl()
{
}

