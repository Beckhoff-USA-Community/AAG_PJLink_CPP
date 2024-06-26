///////////////////////////////////////////////////////////////////////////////
// PJ_Link_Client.h
#pragma once

#include "PJ_LinkInterfaces.h"
#include "TON.h"
#include "md5.h"
#include "string"


class CPJ_Link_Client 
	: public ITComObject
	, public ITcADI
	, public ITcWatchSource
///<AutoGeneratedContent id="InheritanceList">
	, public ITcCyclic
	, public ITcIoTcpProtocolRecv
///</AutoGeneratedContent>
{
public:
	DECLARE_IUNKNOWN()
	DECLARE_IPERSIST_LIB()
	DECLARE_ITCOMOBJECT_LOCKOP()
	DECLARE_ITCADI()
	DECLARE_ITCWATCHSOURCE()
	DECLARE_OBJPARAWATCH_MAP()
	DECLARE_OBJDATAAREA_MAP()

	CPJ_Link_Client();
	virtual	~CPJ_Link_Client();


///<AutoGeneratedContent id="InterfaceMembers">
	// ITcCyclic
	virtual HRESULT TCOMAPI CycleUpdate(ITcTask* ipTask, ITcUnknown* ipCaller, ULONG_PTR context);

	// ITcIoTcpProtocolRecv
	virtual HRESULT TCOMAPI ReceiveData(ULONG socketId, ULONG nData, PVOID pData);
	virtual HRESULT TCOMAPI ReceiveEvent(ULONG socketId, TCPIP_EVENT tcpEvent);

///</AutoGeneratedContent>

protected:
	DECLARE_ITCOMOBJECT_SETSTATE();

	HRESULT AddModuleToCaller();
	VOID RemoveModuleFromCaller();

	// Tracing
	CTcTrace m_Trace;

	// Custom Methods
	VOID SendRequest(std::string sRequest);
	VOID SendStatusRequest();
	VOID ParseResponse(std::string sRequest);
	BOOL CheckSendCommand();


///<AutoGeneratedContent id="Members">
	TcTraceLevel m_TraceLevelMax;
	IPADDR m_TcpServerIpAddress;
	USHORT m_TcpServerPort;
	bool m_Class2;
	PJ_Link_ClientAuthentication m_Authentication;
	USHORT m_PollingRate;
	PJ_Link_ClientInputs m_Inputs;
	PJ_Link_ClientOutputs m_Outputs;
	ITcCyclicCallerInfoPtr m_spCyclicCaller;
	ITcIoTcpProtocolPtr m_spRT_Ethernet_Adapter;
///</AutoGeneratedContent>

	// Connection Variables
	ULONG m_SockId; // TCP Socket ID
	ULONG m_ConnectionCount; //count number of connection attempts
	BOOL m_Connected;

	// Command Triggers
	BOOL m_trig_Power_On;
	BOOL m_trig_Power_Off;
	BOOL m_trig_Input_Request;
	BOOL m_trig_Mute_Request;
	BOOL m_trig_Freeze_On;
	BOOL m_trig_Freeze_Off;
	BOOL m_trig_SVolUp;
	BOOL m_trig_SVolDown;
	BOOL m_trig_MVolUp;
	BOOL m_trig_MVolDown;
	
	// Process Timer
	CTON m_cton;
	BOOL m_q;
	LONGLONG m_PT; //time to wait
	LONGLONG m_ET; //time since started TON

	// Incrementer for status request type
	INT m_StatusRequestID;
	
	// Response
	std::string m_sResponse;

	// Auth Vars
	//char m_authkey_random[9];
	

	std::string m_sServerRandomKey;
	std::string m_sFullPassKey;
	char m_MD5AuthHash[MD5_STRING_SIZE];

	BOOL m_AuthHashGenerated, m_HashPrevSent, m_Authentication_Response, m_Receiving_Auth_Responses;
};
