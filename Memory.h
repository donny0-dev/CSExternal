#pragma  once
#include <windows.h>
#include <tlhelp32.h>
#include <iostream>
#include <string>

namespace Memory {
	inline DWORD BaseAddress;
	inline DWORD EngineAddress;
	inline DWORD ClientState;
	inline HANDLE ProcessSnapShot;
	inline PROCESSENTRY32 ProcessEntry32;
	inline HANDLE ModuleSnapShot;
	inline MODULEENTRY32 ModEntry32;
	inline DWORD PID;
	inline HANDLE Process;

	template <class DataType>
	inline void Write( DataType ValueToWrite, DWORD AddressToWrite ) {
		WriteProcessMemory( Process, ( PVOID ) AddressToWrite, &ValueToWrite, sizeof( DataType ), 0 );
	}

	template <class DataType>
	inline DataType Read( DWORD AddressToRead ) {
		DataType Buffer;
		ReadProcessMemory( Process, ( PVOID ) AddressToRead, &Buffer, sizeof( DataType ), 0 );
		return Buffer;
	}

	void InitMemory( );
	bool GetProcess( char* ProcessName );
	DWORD GetModule( char* ModuleName );
	std::uint32_t Find( const char* Process );
};