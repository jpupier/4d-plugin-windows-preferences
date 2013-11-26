/* --------------------------------------------------------------------------------
 #
 #	4DPlugin.c
 #	source generated by 4D Plugin Wizard
 #	Project : Windows Preferences
 #	author : miyako
 #	11/26/13
 #
 # --------------------------------------------------------------------------------*/

#include "4DPlugin.h"

void PluginMain(int32_t selector, PA_PluginParameters params)
{
	try
	{
		int32_t pProcNum = selector;
		sLONG_PTR *pResult = (sLONG_PTR *)params->fResult;
		PackagePtr pParams = (PackagePtr)params->fParameters;

		CommandDispatcher(pProcNum, pResult, pParams); 
	}
	catch(...)
	{

	}
}

void CommandDispatcher (int32_t pProcNum, sLONG_PTR *pResult, PackagePtr pParams)
{
	switch(pProcNum)
	{
// --- Power

		case 1 :
			SYSTEM_Get_power_status(pResult, pParams);
			break;

		case 2 :
			SYSTEM_Set_execution_state(pResult, pParams);
			break;

// --- Beep

		case 3 :
			SYSTEM_Set_beep_enabled(pResult, pParams);
			break;

		case 4 :
			SYSTEM_Get_beep_enabled(pResult, pParams);
			break;

// --- Screensaver

		case 5 :
			SYSTEM_Set_screensaver_timeout(pResult, pParams);
			break;

		case 6 :
			SYSTEM_Get_screensaver_timeout(pResult, pParams);
			break;

		case 7 :
			SYSTEM_Set_screensaver_active(pResult, pParams);
			break;

		case 8 :
			SYSTEM_Get_screensaver_active(pResult, pParams);
			break;

	}
}

// ------------------------------------- Power ------------------------------------

void SYSTEM_Get_power_status(sLONG_PTR *pResult, PackagePtr pParams)
{
	ARRAY_TEXT Param1;
	ARRAY_TEXT Param2;
	C_LONGINT returnValue;
	
	SYSTEM_POWER_STATUS status;
	
	if(GetSystemPowerStatus(&status))
	{
		Param1.setSize(1);
		Param2.setSize(1);
		
		returnValue.setIntValue(1);
		
		Param1.appendUTF16String((const PA_Unichar *)L"ACLineStatus");
		
		switch (status.ACLineStatus) {
			case 0:
				Param2.appendUTF16String((const PA_Unichar *)L"Offline");
				break;
			case 1:
				Param2.appendUTF16String((const PA_Unichar *)L"Online");
				break;
			default:
				Param2.appendUTF16String((const PA_Unichar *)L"Unknown status");
				break;	
		}
		
		Param1.appendUTF16String((const PA_Unichar *)L"BatteryFlag");
		
		switch (status.BatteryFlag) {
			case 1:
				Param2.appendUTF16String((const PA_Unichar *)L"High: the battery capacity is at more than 66 percent");
				break;
			case 2:
				Param2.appendUTF16String((const PA_Unichar *)L"Low: the battery capacity is at less than 33 percent");
				break;
			case 4:
				Param2.appendUTF16String((const PA_Unichar *)L"Critical: the battery capacity is at less than five percent");
				break;
			case 8:
				Param2.appendUTF16String((const PA_Unichar *)L"Charging");
				break;
			case 128:
				Param2.appendUTF16String((const PA_Unichar *)L"No system battery");
				break;				
			default:
				Param2.appendUTF16String((const PA_Unichar *)L"Unknown status: unable to read the battery flag information");
				break;	
		}
		
		Param1.appendUTF16String((const PA_Unichar *)L"BatteryLifePercent");
		
		switch (status.BatteryLifePercent) {
			case 255:
				Param2.appendUTF16String((const PA_Unichar *)L"Unknown status: unable to read the battery flag information");
				break;				
			default:
			{
				char percent[256];
				sprintf((char *)percent, "%i", (int)status.BatteryLifePercent);
				Param2.appendUTF8String((const uint8_t *)percent, strlen(percent));
			}
				break;	
		}
		
		Param1.appendUTF16String((const PA_Unichar *)L"BatteryLifeTime");
		
		switch (status.BatteryLifeTime) {
			case -1:
				Param2.appendUTF16String((const PA_Unichar *)L"Unknown status");
				break;				
			default:
			{
				char seconds[256];
				sprintf((char *)seconds, "%i", (int)status.BatteryLifeTime);
				Param2.appendUTF8String((const uint8_t *)seconds, strlen(seconds));
			}
				break;	
		}
		
		Param1.appendUTF16String((const PA_Unichar *)L"BatteryFullLifeTime");
		
		switch (status.BatteryFullLifeTime) {
			case -1:
				Param2.appendUTF16String((const PA_Unichar *)L"Unknown status");
				break;				
			default:
			{
				char seconds[256];
				sprintf((char *)seconds, "%i", (int)status.BatteryFullLifeTime);
				Param2.appendUTF8String((const uint8_t *)seconds, strlen(seconds));
			}
				break;	
		}
		
	}
	
	Param1.toParamAtIndex(pParams, 1);
	Param2.toParamAtIndex(pParams, 2);
	returnValue.setReturn(pResult);
}

#define __ES_AWAYMODE_REQUIRED (1)
#define __ES_CONTINUOUS (2)
#define __ES_DISPLAY_REQUIRED (4)
#define __ES_SYSTEM_REQUIRED (8)

void SYSTEM_Set_execution_state(sLONG_PTR *pResult, PackagePtr pParams)
{
	C_LONGINT Param1;
	C_LONGINT returnValue;

	Param1.fromParamAtIndex(pParams, 1);
	
	EXECUTION_STATE state = 0;
	
	if(Param1.getIntValue() & __ES_AWAYMODE_REQUIRED)
		state = state|ES_AWAYMODE_REQUIRED;
	if(Param1.getIntValue() & __ES_CONTINUOUS)
		state = state|ES_CONTINUOUS;
	if(Param1.getIntValue() & __ES_DISPLAY_REQUIRED)
		state = state|ES_DISPLAY_REQUIRED;
	if(Param1.getIntValue() & __ES_SYSTEM_REQUIRED)
		state = state|ES_SYSTEM_REQUIRED;
	
	if(SetThreadExecutionState(state))
		returnValue.setIntValue(1);

	returnValue.setReturn(pResult);
}

// ------------------------------------- Beep -------------------------------------


void SYSTEM_Set_beep_enabled(sLONG_PTR *pResult, PackagePtr pParams)
{
	C_LONGINT Param1;
	C_LONGINT returnValue;

	Param1.fromParamAtIndex(pParams, 1);

	ULONG enabled;
	
	enabled = Param1.getIntValue();
	
	returnValue.setIntValue(SystemParametersInfo(SPI_SETBEEP, enabled, NULL, 0));

	returnValue.setReturn(pResult);
}

void SYSTEM_Get_beep_enabled(sLONG_PTR *pResult, PackagePtr pParams)
{
	C_LONGINT Param1;
	C_LONGINT returnValue;

	BOOL enabled;

	if(SystemParametersInfo(SPI_GETBEEP, 0, &enabled, 0))
	{
		returnValue.setIntValue(1);
		Param1.setIntValue(enabled);	
	}
	
	Param1.toParamAtIndex(pParams, 1);
	returnValue.setReturn(pResult);
}

// ---------------------------------- Screensaver ---------------------------------


void SYSTEM_Set_screensaver_timeout(sLONG_PTR *pResult, PackagePtr pParams)
{
	C_LONGINT Param1;
	C_LONGINT returnValue;

	Param1.fromParamAtIndex(pParams, 1);

	ULONG duration;
	
	duration = Param1.getIntValue();
	
	returnValue.setIntValue(SystemParametersInfo(SPI_SETSCREENSAVETIMEOUT, duration, NULL, 0));	

	returnValue.setReturn(pResult);
}

void SYSTEM_Get_screensaver_timeout(sLONG_PTR *pResult, PackagePtr pParams)
{
	C_LONGINT Param1;
	C_LONGINT returnValue;

	ULONG duration;

	if(SystemParametersInfo(SPI_GETSCREENSAVETIMEOUT, 0, &duration, 0))
	{
		returnValue.setIntValue(1);
		Param1.setIntValue(duration);	
	}
	
	Param1.toParamAtIndex(pParams, 1);
	returnValue.setReturn(pResult);
}

void SYSTEM_Set_screensaver_active(sLONG_PTR *pResult, PackagePtr pParams)
{
	C_LONGINT Param1;
	C_LONGINT returnValue;

	Param1.fromParamAtIndex(pParams, 1);

	BOOL active;
	
	active = Param1.getIntValue();
	
	returnValue.setIntValue(SystemParametersInfo(SPI_SETSCREENSAVEACTIVE, active, NULL, 0));	
	
	returnValue.setReturn(pResult);
}

void SYSTEM_Get_screensaver_active(sLONG_PTR *pResult, PackagePtr pParams)
{
	C_LONGINT Param1;
	C_LONGINT returnValue;

	BOOL active;

	if(SystemParametersInfo(SPI_GETSCREENSAVEACTIVE, 0, &active, 0))
	{
		returnValue.setIntValue(1);
		Param1.setIntValue(active);
	}
	
	Param1.toParamAtIndex(pParams, 1);
	returnValue.setReturn(pResult);
}
