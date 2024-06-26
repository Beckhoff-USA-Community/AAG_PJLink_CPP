///////////////////////////////////////////////////////////////////////////////
// PJ_Link_Client.cpp
#include "TcPch.h"
#pragma hdrstop

#include "PJ_Link_Client.h"
#include "PJ_LinkVersion.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif
DEFINE_THIS_FILE()

///////////////////////////////////////////////////////////////////////////////
// CPJ_Link_Client
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// Collection of interfaces implemented by module CPJ_Link_Client
BEGIN_INTERFACE_MAP(CPJ_Link_Client)
	INTERFACE_ENTRY_ITCOMOBJECT()
	INTERFACE_ENTRY(IID_ITcADI, ITcADI)
	INTERFACE_ENTRY(IID_ITcWatchSource, ITcWatchSource)
///<AutoGeneratedContent id="InterfaceMap">
	INTERFACE_ENTRY(IID_ITcCyclic, ITcCyclic)
	INTERFACE_ENTRY(IID_ITcIoTcpProtocolRecv, ITcIoTcpProtocolRecv)
///</AutoGeneratedContent>
END_INTERFACE_MAP()

IMPLEMENT_IPERSIST_LIB(CPJ_Link_Client, VID_PJ_Link, CID_PJ_LinkCPJ_Link_Client)
IMPLEMENT_ITCOMOBJECT(CPJ_Link_Client)
IMPLEMENT_ITCOMOBJECT_SETSTATE_LOCKOP2(CPJ_Link_Client)
IMPLEMENT_ITCADI(CPJ_Link_Client)
IMPLEMENT_ITCWATCHSOURCE(CPJ_Link_Client)


///////////////////////////////////////////////////////////////////////////////
// Set parameters of CPJ_Link_Client 
BEGIN_SETOBJPARA_MAP(CPJ_Link_Client)
	SETOBJPARA_DATAAREA_MAP()
///<AutoGeneratedContent id="SetObjectParameterMap">
	SETOBJPARA_VALUE(PID_TcTraceLevel, m_TraceLevelMax)
	SETOBJPARA_VALUE(PID_PJ_Link_ClientTcpServerIpAddress, m_TcpServerIpAddress)
	SETOBJPARA_VALUE(PID_PJ_Link_ClientTcpServerPort, m_TcpServerPort)
	SETOBJPARA_VALUE(PID_PJ_Link_ClientClass2, m_Class2)
	SETOBJPARA_VALUE(PID_PJ_Link_ClientAuthentication, m_Authentication)
	SETOBJPARA_VALUE(PID_PJ_Link_ClientPollingRate, m_PollingRate)
	SETOBJPARA_ITFPTR(PID_Ctx_TaskOid, m_spCyclicCaller)
	SETOBJPARA_ITFPTR(PID_PJ_Link_ClientRT_Ethernet_Adapter, m_spRT_Ethernet_Adapter)
///</AutoGeneratedContent>
END_SETOBJPARA_MAP()

///////////////////////////////////////////////////////////////////////////////
// Get parameters of CPJ_Link_Client 
BEGIN_GETOBJPARA_MAP(CPJ_Link_Client)
	GETOBJPARA_DATAAREA_MAP()
///<AutoGeneratedContent id="GetObjectParameterMap">
	GETOBJPARA_VALUE(PID_TcTraceLevel, m_TraceLevelMax)
	GETOBJPARA_VALUE(PID_PJ_Link_ClientTcpServerIpAddress, m_TcpServerIpAddress)
	GETOBJPARA_VALUE(PID_PJ_Link_ClientTcpServerPort, m_TcpServerPort)
	GETOBJPARA_VALUE(PID_PJ_Link_ClientClass2, m_Class2)
	GETOBJPARA_VALUE(PID_PJ_Link_ClientAuthentication, m_Authentication)
	GETOBJPARA_VALUE(PID_PJ_Link_ClientPollingRate, m_PollingRate)
	GETOBJPARA_ITFPTR(PID_Ctx_TaskOid, m_spCyclicCaller)
	GETOBJPARA_ITFPTR(PID_PJ_Link_ClientRT_Ethernet_Adapter, m_spRT_Ethernet_Adapter)
///</AutoGeneratedContent>
END_GETOBJPARA_MAP()

///////////////////////////////////////////////////////////////////////////////
// Get watch entries of CPJ_Link_Client
BEGIN_OBJPARAWATCH_MAP(CPJ_Link_Client)
	OBJPARAWATCH_DATAAREA_MAP()
///<AutoGeneratedContent id="ObjectParameterWatchMap">
///</AutoGeneratedContent>
END_OBJPARAWATCH_MAP()

///////////////////////////////////////////////////////////////////////////////
// Get data area members of CPJ_Link_Client
BEGIN_OBJDATAAREA_MAP(CPJ_Link_Client)
///<AutoGeneratedContent id="ObjectDataAreaMap">
	OBJDATAAREA_VALUE(ADI_PJ_Link_ClientInputs, m_Inputs)
	OBJDATAAREA_VALUE(ADI_PJ_Link_ClientOutputs, m_Outputs)
///</AutoGeneratedContent>
END_OBJDATAAREA_MAP()


///////////////////////////////////////////////////////////////////////////////
CPJ_Link_Client::CPJ_Link_Client()
	: m_Trace(m_TraceLevelMax, m_spSrv)
{
///<AutoGeneratedContent id="MemberInitialization">
	m_TraceLevelMax = tlAlways;
	memset(&m_TcpServerIpAddress, 0, sizeof(m_TcpServerIpAddress));
	m_TcpServerPort = 0;
	m_Class2 = FALSE;
	memset(&m_Authentication, 0, sizeof(m_Authentication));
	m_PollingRate = 0;
	memset(&m_Inputs, 0, sizeof(m_Inputs));
	memset(&m_Outputs, 0, sizeof(m_Outputs));
///</AutoGeneratedContent>
	m_SockId = 0;
	m_spRT_Ethernet_Adapter = NULL;
	m_ConnectionCount = 0;
	m_StatusRequestID = 0;
	m_Connected = 0;
	m_sResponse.clear();
}

///////////////////////////////////////////////////////////////////////////////
CPJ_Link_Client::~CPJ_Link_Client() 
{
}


///////////////////////////////////////////////////////////////////////////////
// State Transitions 
///////////////////////////////////////////////////////////////////////////////
IMPLEMENT_ITCOMOBJECT_SETOBJSTATE_IP_PI(CPJ_Link_Client)
///////////////////////////////////////////////////////////////////////////////
// State transition from PREOP to SAFEOP
//
// Initialize input parameters 
// Allocate memory
HRESULT CPJ_Link_Client::SetObjStatePS(PTComInitDataHdr pInitData)
{
	m_Trace.Log(tlVerbose, FENTERA);

	HRESULT hr = S_OK;
	IMPLEMENT_ITCOMOBJECT_EVALUATE_INITDATA(pInitData);

	m_Trace.Log(tlVerbose, FLEAVEA "hr=0x%08x", hr);
	return hr;
}

///////////////////////////////////////////////////////////////////////////////
// State transition from SAFEOP to OP
//
// Register with other TwinCAT objects
HRESULT CPJ_Link_Client::SetObjStateSO()
{
	m_Trace.Log(tlVerbose, FENTERA);
	HRESULT hr = S_OK;

	if (SUCCEEDED(hr) && m_spRT_Ethernet_Adapter.HasOID())
	{
		hr = m_spSrv->TcQuerySmartObjectInterface(m_spRT_Ethernet_Adapter);
	}

	// If following call is successful the CycleUpdate method will be called, 
	// eventually even before method has been left.
	hr = FAILED(hr) ? hr : AddModuleToCaller();

	// Cleanup if transition failed at some stage
	if (FAILED(hr))
	{
		RemoveModuleFromCaller();
	}
	m_Trace.Log(tlVerbose, FLEAVEA "hr=0x%08x", hr);
	return hr;
}

///////////////////////////////////////////////////////////////////////////////
// State transition from OP to SAFEOP
HRESULT CPJ_Link_Client::SetObjStateOS()
{
	m_Trace.Log(tlVerbose, FENTERA);
	HRESULT hr = S_OK;

	RemoveModuleFromCaller();

	if (m_SockId != 0)
	{
		if (m_spRT_Ethernet_Adapter->IsConnected(m_SockId) == S_OK)
		{
			m_spRT_Ethernet_Adapter->Close(m_SockId);
			m_spRT_Ethernet_Adapter->CheckReceived();
		}

		m_spRT_Ethernet_Adapter->FreeSocket(m_SockId);
		m_SockId = 0;
	}


	m_Trace.Log(tlVerbose, FLEAVEA "hr=0x%08x", hr);
	return hr;
}

///////////////////////////////////////////////////////////////////////////////
// State transition from SAFEOP to PREOP
HRESULT CPJ_Link_Client::SetObjStateSP()
{
	m_Trace.Log(tlVerbose, FENTERA);
	HRESULT hr = S_OK;

	m_Trace.Log(tlVerbose, FLEAVEA "hr=0x%08x", hr);
	return hr;
}

///<AutoGeneratedContent id="ImplementationOf_ITcCyclic">
HRESULT CPJ_Link_Client::CycleUpdate(ITcTask* ipTask, ITcUnknown* ipCaller, ULONG_PTR context)
{
	HRESULT hr = S_OK;

	// Set Polling Rate
	m_PT = m_PollingRate; //in ms

	// Check if new data received
	m_spRT_Ethernet_Adapter->CheckReceived();

	// Check if socket is allocated
	if (m_SockId == 0)
	{
		if (SUCCEEDED_DBG(hr = m_spRT_Ethernet_Adapter->AllocSocket(THIS_CAST(ITcIoTcpProtocolRecv), m_SockId)))
		{
			if (FAILED(hr = m_spRT_Ethernet_Adapter->Connect(m_SockId, ((PULONG)&m_TcpServerIpAddress)[0], m_TcpServerPort)))
			{
				m_spRT_Ethernet_Adapter->FreeSocket(m_SockId);
				m_SockId = 0;
			}
			else {
				m_ConnectionCount++; //count number of connections
			}

		}
	}

	// Check if the system is connected to the projector
	m_Connected = (m_spRT_Ethernet_Adapter->IsConnected(m_SockId) == S_OK);
	m_Outputs.Connected = m_Connected;
	m_Outputs.AuthStatus = m_Receiving_Auth_Responses;

	if(m_Connected)
	{ 
		// Polling timer loop
		if (!m_q) {
			//rising edge for start (after start / restart) 
			m_cton.Update(ipTask, TRUE, m_PT, m_q, m_ET);
		}
		else if (!CheckSendCommand() && m_q)
		{
			//if q==true -> time elapsed -> do something! 
			SendStatusRequest();

			//falling edge for reset
			m_q = FALSE;
			m_cton.Update(ipTask, FALSE, m_PT, m_q, m_ET);
		}
	}
	return hr;
}
///</AutoGeneratedContent>

///////////////////////////////////////////////////////////////////////////////
HRESULT CPJ_Link_Client::AddModuleToCaller()
{
	m_Trace.Log(tlVerbose, FENTERA);

	HRESULT hr = S_OK;
	if ( m_spCyclicCaller.HasOID() )
	{
		if ( SUCCEEDED_DBG(hr = m_spSrv->TcQuerySmartObjectInterface(m_spCyclicCaller)) )
		{
			if ( FAILED(hr = m_spCyclicCaller->AddModule(m_spCyclicCaller, THIS_CAST(ITcCyclic))) )
			{
				m_spCyclicCaller = NULL;
			}
		}
	}
	else
	{
		hr = ADS_E_INVALIDOBJID; 
		SUCCEEDED_DBGT(hr, "Invalid OID specified for caller task");
	}

	m_Trace.Log(tlVerbose, FLEAVEA "hr=0x%08x", hr);
	return hr;
}

///////////////////////////////////////////////////////////////////////////////
VOID CPJ_Link_Client::RemoveModuleFromCaller()
{
	m_Trace.Log(tlVerbose, FENTERA);

	if ( m_spCyclicCaller )
	{
		m_spCyclicCaller->RemoveModule(m_spCyclicCaller);
	}
	m_spCyclicCaller	= NULL;

	m_Trace.Log(tlVerbose, FLEAVEA);
}


///<AutoGeneratedContent id="ImplementationOf_ITcIoTcpProtocolRecv">
HRESULT CPJ_Link_Client::ReceiveData(ULONG socketId, ULONG nData, PVOID pData)
{
	HRESULT hr = S_OK;

	// Copy out the data that was received
	PCHAR pResponse = new char[100];
	memcpy(pResponse, pData, 100);

	// Copy data to string
	m_sResponse.clear();
	m_sResponse.resize(strlen(pResponse));
	memcpy(&m_sResponse[0], pData, nData);

	// Log the received message
	m_Trace.Log(tlVerbose, FLEAVEA "Receive response: '%s'", m_sResponse.c_str());

	/********
	Authentication Section
	*********/
	// Check if response is Auth Token
	if (m_sResponse.find("ERRA") != std::string::npos) {
		m_Trace.Log(tlVerbose, FLEAVEA "Authentication Required for Projector!!!");
		m_AuthHashGenerated = false;
		m_Receiving_Auth_Responses = false;
		m_HashPrevSent = false;
	}
	else if (m_sResponse.find("PJLINK 0") != std::string::npos){
		m_Outputs.AuthRequired = false;
		m_AuthHashGenerated = false;
		m_Authentication_Response = true;
	}
	else if (m_sResponse.find("PJLINK 1") != std::string::npos) {
		m_Outputs.AuthRequired = true;
		m_Authentication_Response = true;

		// Set the token received from the projector
		m_sServerRandomKey.clear();
		m_sServerRandomKey = m_sResponse.substr(strlen("PJLINK 1 "), 8);
		m_Trace.Log(tlVerbose, FLEAVEA "Random Token Message Received: %s", m_sServerRandomKey.c_str());

		// Set the full password string
		m_sFullPassKey.clear();
		m_sFullPassKey.append(m_sServerRandomKey);
		m_sFullPassKey.append(m_Authentication.Password);
		m_Trace.Log(tlVerbose, FLEAVEA "Password Generated String: %s", m_sFullPassKey.c_str());

		// Generate hash
		md5::md5_t md5;
		md5.process(m_sFullPassKey.c_str(), m_sFullPassKey.length());
		md5.finish();
		
		md5.get_string(m_MD5AuthHash);
		m_Trace.Log(tlInfo, FLEAVEA "Hash Generated: %s", m_MD5AuthHash);

		m_AuthHashGenerated = true;
	}
	else
		ParseResponse(m_sResponse);
	
	delete[] pResponse;
	return hr;
}

HRESULT CPJ_Link_Client::ReceiveEvent(ULONG socketId, TCPIP_EVENT tcpEvent)
{
	//m_Trace.Log(tlInfo, FLEAVEA "Receive TCP Event: SocketId: %d Event: %d", socketId, tcpEvent);

	switch (tcpEvent)
	{
	case TCPIP_EVENT_RESET:
	case TCPIP_EVENT_TIMEOUT:
		if (socketId == m_SockId)
		{
			m_Trace.Log(tlInfo, FLEAVEA "Connection to remote server failed!");
			m_spRT_Ethernet_Adapter->FreeSocket(socketId);
			m_SockId = 0;
		}
		break;
	case TCPIP_EVENT_CONN_CLOSED:
		m_Trace.Log(tlInfo, FLEAVEA "Close connection: SocketId: %d", socketId);
		m_spRT_Ethernet_Adapter->FreeSocket(socketId);
		m_SockId = 0;
		break;
	case TCPIP_EVENT_CONN_INCOMING:
		break;
	case TCPIP_EVENT_KEEP_ALIVE:
		break;
	case TCPIP_EVENT_CONN_IDLE:
		break;
	case TCPIP_EVENT_DATA_SENT:
	case TCPIP_EVENT_DATA_RECEIVED:
		break;
	case TCPIP_EVENT_LINKCONNECT:
		m_AuthHashGenerated = false;
		m_HashPrevSent = false;
		break;
	case TCPIP_EVENT_LINKDISCONNECT:
		m_Trace.Log(tlInfo, FLEAVEA "link disconnect connection: SocketId: %d", socketId);
		m_spRT_Ethernet_Adapter->FreeSocket(socketId);
		m_SockId = 0;
		break;
	case TCPIP_EVENT_ERROR:
	default:
		break;
	}

	return S_OK;
}
///</AutoGeneratedContent>


VOID CPJ_Link_Client::SendRequest(std::string sRequest) {

	if (m_Authentication_Response && ((m_AuthHashGenerated && m_Authentication.Enable) || (!m_Outputs.AuthRequired))) {

		// Check for auth key here before sending
		if (m_AuthHashGenerated && !m_HashPrevSent) {
			if (isxdigit(m_MD5AuthHash[0]) && strlen(m_MD5AuthHash) == 32) {
				sRequest.insert(0, m_MD5AuthHash);
				m_HashPrevSent = true;
			}	
			else
				return;
		}

		// declaring character array (+1 for null terminator) 
		const int length = sRequest.length() + 1;

		// Allocate byte array
		char* char_array = new char[length];

		// Assign the data
		char_array = &sRequest[0];

		// Add the null terminator
		char_array[sRequest.length()] = '\x0d';

		// Log the request being sent
		m_Trace.Log(tlVerbose, FLEAVEA "Sending Status Request: %s", char_array);

		// Return variable for bytes send
		ULONG nSendData = 0;

		// Send Message
		m_spRT_Ethernet_Adapter->SendData(m_SockId, strlen(char_array), char_array, nSendData);

		// delete the pointer
		delete[] char_array;
	}
	else
		m_Trace.Log(tlVerbose, FLEAVEA "PJ Link reports that the projector requires authenticaion, please enable and set password");
}




VOID CPJ_Link_Client::SendStatusRequest() {

	// Send specific status message
	switch (m_StatusRequestID)
	{
	case 0:
		// Power Status
		SendRequest("%1POWR ?");
		break;
	case 1:
		// Lamp Status
		SendRequest("%1LAMP ?");
		break;
	case 2:
		// Input Query List
		if (m_Outputs.Vendor.Class == 2 && m_Class2)
			SendRequest("%2INST ?");
		else
			SendRequest("%1INST ?");
		break;
	case 3:
		// Name
		SendRequest("%1NAME ?");
		break;
	case 4:
		// Info Data 1
		SendRequest("%1INFO ?");
		break;
	case 5:
		// Info Data 2
		SendRequest("%1INF1 ?");
		break;
	case 6:
		// Info Data 3
		SendRequest("%1INF2 ?");
		break;
	case 7:
		// Class Support
		SendRequest("%1CLSS ?");
		break;
	case 8:
		// Input Status
		if (m_Outputs.Vendor.Class == 2 && m_Class2)
			SendRequest("%2INPT ?");
		else
			SendRequest("%1INPT ?");
		break;
	case 9:
		// Mute Status
		SendRequest("%1AVMT ?");
		break;
	case 10:
		// Error Status
		SendRequest("%1ERST ?");
		break;
	case 11:
		// Serial Number
		SendRequest("%2SNUM ?");
		break;
	case 12: 
		// Software Version
		SendRequest("%2SVER ?");
		break;
	case 13:
		// Input Terminal
		SendRequest("%2INNM ?");
		break;
	case 14: 
		// Input Resolution
		SendRequest("%2IRES ?");
		break;
	case 15:
		// Recommend Resolution
		SendRequest("%2RRES ?");
		break;
	case 16:
		// Replacement Lamp Part Number
		SendRequest("%2RLMP ?");
		break;
	case 17:
		// Replacement Filter Part Number
		SendRequest("%2RFIL ?");
		break;
	case 18:
		// Freeze Status
		SendRequest("%2FREZ ?");
		break;
	case 19:
		// Filter Status
		SendRequest("%2FILT ?");
		break;
	}

	// Check if class 2 messages are supported, or if an increment is needed
	if(((m_Outputs.Vendor.Class == 2 && m_Class2 && m_StatusRequestID >= 10) || (m_StatusRequestID < 10)) && m_StatusRequestID <=18)
		m_StatusRequestID++;
	else
		m_StatusRequestID = 0;
}

// Parse the response from the projector
VOID CPJ_Link_Client::ParseResponse(std::string sResponse) {

	// Received responses while Authenticated
	if (m_Outputs.AuthRequired)
		m_Receiving_Auth_Responses = true;

	// Check if the response is error type
	if (sResponse.find("ERR1") != std::string::npos ||
		sResponse.find("ERR2") != std::string::npos || 
		sResponse.find("ERR3") != std::string::npos ||
		sResponse.find("ERR4") != std::string::npos) {
		m_Trace.Log(tlWarning, FLEAVEA "Warning: Feature might not be supported on projector");
		return;
	}

	// Check if the response is response to command trigger
	if (sResponse.find("=OK") != std::string::npos) {
		m_Trace.Log(tlVerbose, FLEAVEA "Response Type: Command response received! \n");
		return;
	}

	// search variable
	std::size_t search_key;

	// POWER Command
	search_key = sResponse.find("%1POWR=");
	if (search_key != std::string::npos) {
		m_Trace.Log(tlVerbose, FLEAVEA "Response Type: Power Status");
		m_Outputs.Power = (sResponse[search_key + 7] == '1');
		return;
	}


	// LAMP Command
	search_key = sResponse.find("%1LAMP=");
	if (search_key != std::string::npos) {
		m_Trace.Log(tlVerbose, FLEAVEA "Response Type: Lamp Status");

		// Check the amount of spaces
		int lamp_idx_spchar = 0;
		int lamp_idx = 0;

		STRING255 lampStringValues = "";
		STRING255 lampHours = "";
		STRING255 lampStatus = "";

		strcat(lampStringValues, &sResponse[7]);

		// Find the delimiters
		for (int i = 0; i < strlen(lampStringValues); i++) {
			if (lampStringValues[i] == ' ')
			{
				// Clear old values
				memset(lampHours, 0, sizeof(lampHours));
				memset(lampStatus, 0, sizeof(lampStatus));
				memset(&m_Outputs.Lamps[lamp_idx].Time, 0, sizeof(m_Outputs.Lamps[lamp_idx].Time));
				memset(&m_Outputs.Lamps[lamp_idx].On, 0, sizeof(m_Outputs.Lamps[lamp_idx].On));

				// Copy new values
				memcpy(lampHours, lampStringValues + lamp_idx_spchar, i - lamp_idx_spchar);
				memcpy(lampStatus, lampStringValues + i + 1, 1);
				//Convert
				sscanf(lampHours, "%d", &m_Outputs.Lamps[lamp_idx].Time);
				m_Outputs.Lamps[lamp_idx].On = (lampStatus[0] == '1');

				lamp_idx++;
				lamp_idx_spchar = i + 2;
				i = lamp_idx_spchar;
			}
		}
		return;
	}

	// INST Command
	search_key = sResponse.find("%1INST=");
	//if (CommandIdentifier(pResponse, "%1INST=") || CommandIdentifier(pResponse, "%2INST")) {
	if (search_key != std::string::npos) {
		m_Trace.Log(tlVerbose, FLEAVEA "Response Type: Input Status");
		int x = 0;
		for (int i = 6; i < sResponse.length(); i++)
			if (sResponse[i] == ' ' || sResponse[i] == '=')
			{
				memcpy(m_Outputs.Inputs.Available[x], &sResponse[i+1], 2);
				x++;
			}
		return;
	}

	// NAME Command
	search_key = sResponse.find("%1NAME=");
	if (search_key != std::string::npos) {
		m_Trace.Log(tlVerbose, FLEAVEA "Response Type: Name Status");
		memset(m_Outputs.Vendor.Name, 0, sizeof(m_Outputs.Vendor.Name));
		memcpy(m_Outputs.Vendor.Name, &m_sResponse[7], m_sResponse.length() - 7);
		return;
	}
	
	// INFO1 Command
	search_key = sResponse.find("%1INFO=");
	if (search_key != std::string::npos) {
		m_Trace.Log(tlVerbose, FLEAVEA "Response Type: Info1 Status");
		memset(m_Outputs.Vendor.InfoData1, 0, sizeof(m_Outputs.Vendor.Name));
		memcpy(m_Outputs.Vendor.InfoData1, &m_sResponse[7], m_sResponse.length() - 7);
		return;
	}

	// INFO2 Command
	search_key = sResponse.find("%1INF1=");
	if (search_key != std::string::npos) {
		m_Trace.Log(tlVerbose, FLEAVEA "Response Type: Info2 Status");
		memset(m_Outputs.Vendor.InfoData2, 0, sizeof(m_Outputs.Vendor.Name));
		memcpy(m_Outputs.Vendor.InfoData2, &m_sResponse[7], m_sResponse.length() - 7);
		return;
	}

	// INFO3 Command
	search_key = sResponse.find("%1INF2=");
	if (search_key != std::string::npos) {
		m_Trace.Log(tlVerbose, FLEAVEA "Response Type: Info3 Status");
		memset(m_Outputs.Vendor.InfoData3, 0, sizeof(m_Outputs.Vendor.Name));
		memcpy(m_Outputs.Vendor.InfoData3, &m_sResponse[7], m_sResponse.length() - 7);
		return;
	}

	// CLASS Command
	search_key = sResponse.find("%1CLSS=");
	if (search_key != std::string::npos) {
		m_Trace.Log(tlVerbose, FLEAVEA "Response Type: Class Status");
		m_Outputs.Vendor.Class = USHORT(sResponse[search_key + 7]) - 48;
		return;
	}

	// INPUT Command
	search_key = sResponse.find("%1INPT=");
	if (search_key != std::string::npos) {
		m_Trace.Log(tlVerbose, FLEAVEA "Response Type: Input Status");
		memset(m_Outputs.Inputs.Selected, 0, sizeof(m_Outputs.Class2.SerialNumber));
		memcpy(m_Outputs.Inputs.Selected, &m_sResponse[7], m_sResponse.length() - 7);
		return;
	}

	// AV Mute Command
	search_key = sResponse.find("%1AVMT=");
	if (search_key != std::string::npos) {
		m_Trace.Log(tlVerbose, FLEAVEA "Response Type: Mute Status");
		if (sResponse.find("%1AVMT=11") != std::string::npos)
			m_Outputs.Mute = 1;
		else if (sResponse.find("%1AVMT=21") != std::string::npos)
			m_Outputs.Mute = 3;
		else if (sResponse.find("%1AVMT=31") != std::string::npos)
			m_Outputs.Mute = 5;
		else if (sResponse.find("%1AVMT=30") != std::string::npos)
			m_Outputs.Mute = 6;
		return;
	}

	// Error Status Command
	search_key = sResponse.find("%1ERST=");
	if (search_key != std::string::npos) {
		m_Trace.Log(tlVerbose, FLEAVEA "Response Type: Error Status");

		search_key +=7;
		m_Outputs.Errors.Fan.NoError = (sResponse[search_key] == '0');
		m_Outputs.Errors.Fan.Warning = (sResponse[search_key] == '1');
		m_Outputs.Errors.Fan.Error = (sResponse[search_key] == '2');

		search_key++;
		m_Outputs.Errors.Lamp.NoError = (sResponse[search_key] == '0');
		m_Outputs.Errors.Lamp.Warning = (sResponse[search_key] == '1');
		m_Outputs.Errors.Lamp.Error = (sResponse[search_key] == '2');

		search_key++;
		m_Outputs.Errors.Temp.NoError = (sResponse[search_key] == '0');
		m_Outputs.Errors.Temp.Warning = (sResponse[search_key] == '1');
		m_Outputs.Errors.Temp.Error = (sResponse[search_key] == '2');

		search_key++;
		m_Outputs.Errors.CoverOpen.NoError = (sResponse[search_key] == '0');
		m_Outputs.Errors.CoverOpen.Warning = (sResponse[search_key] == '1');
		m_Outputs.Errors.CoverOpen.Error = (sResponse[search_key] == '2');

		search_key++;
		m_Outputs.Errors.Filter.NoError = (sResponse[search_key] == '0');
		m_Outputs.Errors.Filter.Warning = (sResponse[search_key] == '1');
		m_Outputs.Errors.Filter.Error = (sResponse[search_key] == '2');

		search_key++;
		m_Outputs.Errors.Other.NoError = (sResponse[search_key] == '0');
		m_Outputs.Errors.Other.Warning = (sResponse[search_key] == '1');
		m_Outputs.Errors.Other.Error = (sResponse[search_key] == '2');
		return;
	}
	


	/***************
	Class 2 Commands
	****************/

	// INPUT Command Class 2
	search_key = sResponse.find("%2INPT=");
	if (search_key != std::string::npos) {
		m_Trace.Log(tlVerbose, FLEAVEA "Response Type: Input Status");
		memset(m_Outputs.Inputs.Selected, 0, sizeof(m_Outputs.Class2.SerialNumber));
		memcpy(m_Outputs.Inputs.Selected, &m_sResponse[7], m_sResponse.length() - 7);
		return;
	}

	// INST Command
	search_key = sResponse.find("%2INST=");
	//if (CommandIdentifier(pResponse, "%1INST=") || CommandIdentifier(pResponse, "%2INST")) {
	if (search_key != std::string::npos) {
		m_Trace.Log(tlVerbose, FLEAVEA "Response Type: Input Status");
		int x = 0;
		for (int i = 6; i < sResponse.length(); i++)
			if (sResponse[i] == ' ' || sResponse[i] == '=')
			{
				memcpy(m_Outputs.Inputs.Available[x], &sResponse[i + 1], 2);
				x++;
			}
		return;
	}

	// SNUM Command
	search_key = sResponse.find("%2SNUM=");
	if (search_key != std::string::npos) {
		m_Trace.Log(tlVerbose, FLEAVEA "Response Type: Serial Number Status");
		memset(m_Outputs.Class2.SerialNumber, 0, sizeof(m_Outputs.Class2.SerialNumber));
		memcpy(m_Outputs.Class2.SerialNumber, &m_sResponse[7], m_sResponse.length() - 7);
		return;
	}

	// SVER Command
	search_key = sResponse.find("%2SVER=");
	if (search_key != std::string::npos) {
		m_Trace.Log(tlVerbose, FLEAVEA "Response Type: Software Version Status");
		memset(m_Outputs.Class2.SoftwareVersion, 0, sizeof(m_Outputs.Class2.SoftwareVersion));
		memcpy(m_Outputs.Class2.SoftwareVersion, &m_sResponse[7], m_sResponse.length() - 7);
		return;
	}

	// INNM Command
	search_key = sResponse.find("%2INNM=");
	if (search_key != std::string::npos) {
		m_Trace.Log(tlVerbose, FLEAVEA "Response Type: Input Terminal Status");
		memset(m_Outputs.Class2.InputTerminal, 0, sizeof(m_Outputs.Class2.InputTerminal));
		memcpy(m_Outputs.Class2.InputTerminal, &m_sResponse[7], m_sResponse.length() - 7);
		return;
	}

	// IRES Command
	search_key = sResponse.find("%2IRES=");
	if (search_key != std::string::npos) {
		m_Trace.Log(tlVerbose, FLEAVEA "Response Type: Input Resolution Status");
		memset(m_Outputs.Class2.InputResolution, 0, sizeof(m_Outputs.Class2.InputResolution));
		memcpy(m_Outputs.Class2.InputResolution, &m_sResponse[7], m_sResponse.length() - 7);
		return;
	}

	// RRES Command
	search_key = sResponse.find("%2RRES=");
	if (search_key != std::string::npos) {
		m_Trace.Log(tlVerbose, FLEAVEA "Response Type: Recommended Resolution Status");
		memset(m_Outputs.Class2.RecommendResolution, 0, sizeof(m_Outputs.Class2.RecommendResolution));
		memcpy(m_Outputs.Class2.RecommendResolution, &m_sResponse[7], m_sResponse.length() - 7);
		return;
	}

	// RLMP Command
	search_key = sResponse.find("%2RLMP=");
	if (search_key != std::string::npos) {
		m_Trace.Log(tlVerbose, FLEAVEA "Response Type: Replacement Lamp Status");
		memset(m_Outputs.Class2.ReplacementLamp, 0, sizeof(m_Outputs.Class2.ReplacementLamp));
		memcpy(m_Outputs.Class2.ReplacementLamp, &m_sResponse[7], m_sResponse.length() - 7);
		return;
	}

	// RFIL Command
	search_key = sResponse.find("%2RFIL=");
	if (search_key != std::string::npos) {
		m_Trace.Log(tlVerbose, FLEAVEA "Response Type: Replacement Filter Status");
		memset(m_Outputs.Class2.ReplacementFilter, 0, sizeof(m_Outputs.Class2.ReplacementFilter));
		memcpy(m_Outputs.Class2.ReplacementFilter, &m_sResponse[7], m_sResponse.length() - 7);
		return;
	}

	// Freeze Command
	search_key = sResponse.find("%2FREZ=");
	if (search_key != std::string::npos) {
		m_Trace.Log(tlVerbose, FLEAVEA "Response Type: Freeze Status");
		m_Outputs.Class2.Freeze = (sResponse[search_key + 7] == '1');
		return;
	}

	// Filter Time Command
	search_key = sResponse.find("%2FILT=");
	if (search_key != std::string::npos) {
		m_Trace.Log(tlVerbose, FLEAVEA "Response Type: Filter Time Status");
		m_Outputs.Class2.FilterTime = (sResponse[search_key + 7] == '1');
		return;
	}

	// Display if no action taken
	m_Trace.Log(tlAlways, FLEAVEA "Message Received Was Not Found As Valid Function...");
}

BOOL CPJ_Link_Client::CheckSendCommand() {

	// Power On
	if (m_Inputs.Power.On && !m_trig_Power_On)
	{
		SendRequest("%1POWR 1");
		m_trig_Power_On = true;
		return true;
	}
	else if(!m_Inputs.Power.On)
		m_trig_Power_On = false;


	// Power Off
	if (m_Inputs.Power.Off && !m_trig_Power_Off)
	{
		SendRequest("%1POWR 0");
		m_trig_Power_Off = true;
		return true;
	}
	else if (!m_Inputs.Power.Off)
		m_trig_Power_Off = false;

	// Freeze On
	if (m_Inputs.Freeze.On && !m_trig_Freeze_On && m_Outputs.Vendor.Class == 2 && m_Class2)
	{
		SendRequest("%2FREZ 1");
		m_trig_Freeze_On = true;
		return true;
	}
	else if (!m_Inputs.Freeze.On)
		m_trig_Freeze_On = false;

	// Freeze Off
	if (m_Inputs.Freeze.Off && !m_trig_Freeze_Off && m_Outputs.Vendor.Class == 2 && m_Class2)
	{
		SendRequest("%2FREZ 0");
		m_trig_Freeze_Off = true;
		return true;
	}
	else if (!m_Inputs.Freeze.Off)
		m_trig_Freeze_Off = false;

	// Speaker Vol Up
	if (m_Inputs.SpeakerVolume.Up && !m_trig_SVolUp && m_Outputs.Vendor.Class == 2 && m_Class2)
	{
		SendRequest("%2SVOL 1");
		m_trig_SVolUp = true;
		return true;
	}
	else if (!m_Inputs.SpeakerVolume.Up)
		m_trig_SVolUp = false;

	// Speaker Vol Down
	if (m_Inputs.SpeakerVolume.Down && !m_trig_SVolDown && m_Outputs.Vendor.Class == 2 && m_Class2)
	{
		SendRequest("%2SVOL 0");
		m_trig_SVolDown = true;
		return true;
	}
	else if (!m_Inputs.SpeakerVolume.Down)
		m_trig_SVolDown = false;

	// Mic Vol Up
	if (m_Inputs.MicrophoneVolume.Up && !m_trig_MVolUp && m_Outputs.Vendor.Class == 2 && m_Class2)
	{
		SendRequest("%2MVOL 1");
		m_trig_MVolUp = true;
		return true;
	}
	else if (!m_Inputs.MicrophoneVolume.Up)
		m_trig_MVolUp = false;

	// Mic Vol Down
	if (m_Inputs.MicrophoneVolume.Down && !m_trig_MVolDown && m_Outputs.Vendor.Class == 2 && m_Class2)
	{
		SendRequest("%2MVOL 0");
		m_trig_MVolDown = true;
		return true;
	}
	else if (!m_Inputs.MicrophoneVolume.Down)
		m_trig_MVolDown = false;


	// Mute
	if (m_Inputs.Mute.Request && !m_trig_Mute_Request && m_Inputs.Mute.Selection > 0 && m_Inputs.Mute.Selection <=6)
	{
		switch (m_Inputs.Mute.Selection)
		{
		case 1:
			SendRequest("%1AVMT 11");
			break;
		case 2:
			SendRequest("%1AVMT 10");
			break;
		case 3:
			SendRequest("%1AVMT 21");
			break;
		case 4:
			SendRequest("%1AVMT 20");
			break;
		case 5:
			SendRequest("%1AVMT 31");
			break;
		case 6:
			SendRequest("%1AVMT 30");
			break;
		}
		m_trig_Mute_Request = true;
		return true;
	}
	else if (!m_Inputs.Mute.Request)
		m_trig_Mute_Request = false;


	// Input
	if (m_Inputs.Input.Request && !m_trig_Input_Request )
	{
		PCHAR pRequest = new char[9];
		

		if (m_Outputs.Vendor.Class == 2 && m_Class2)
			memcpy(pRequest, "%2INPT ", 7);
		else
			memcpy(pRequest, "%1INPT ", 7);

		memcpy(pRequest + 7, &m_Inputs.Input.Channel[0], 1);
		memcpy(pRequest + 8, &m_Inputs.Input.Channel[1], 1);

		std::string sRequest(pRequest);

		if (m_Outputs.Vendor.Class == 2 && m_Class2)
			SendRequest(sRequest);
		else
			SendRequest(sRequest);

		m_trig_Input_Request = true;
		delete[] pRequest;
		return true;
	}
	else if (!m_Inputs.Input.Request)
		m_trig_Input_Request = false;

	return false;
}
