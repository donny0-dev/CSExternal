#include "Memory.h"
#include "XorStr.h"
#include "Utils.h"
#include "Offsets.h"
#include "LocalPlayer.h"
#include "LazyImporter.h"

bool Memory::GetProcess( char* ProcessName ) {
	ProcessEntry32.dwSize = sizeof( PROCESSENTRY32 );
	ProcessSnapShot = LI_FN( CreateToolhelp32Snapshot )( TH32CS_SNAPPROCESS, 0 );

	if ( ProcessSnapShot == INVALID_HANDLE_VALUE )
		return false;

	while ( LI_FN( Process32Next )( ProcessSnapShot, &ProcessEntry32 ) ) {
		if ( !LI_FN( strcmp )( ProcessName, ProcessEntry32.szExeFile ) ) {
			Process = LI_FN( OpenProcess )( PROCESS_ALL_ACCESS, FALSE, ProcessEntry32.th32ProcessID );
			PID = ProcessEntry32.th32ProcessID;

			if ( Process == NULL )
				return false;

			LI_FN( CloseHandle )( ProcessSnapShot );
			return true;
		}
	}

	LI_FN( CloseHandle )( ProcessSnapShot );
	return false;
}

DWORD Memory::GetModule( LPSTR ModuleName ) {
	ModuleSnapShot = INVALID_HANDLE_VALUE;
	ModuleSnapShot = LI_FN( CreateToolhelp32Snapshot )( TH32CS_SNAPMODULE, PID );

	if ( ModuleSnapShot == INVALID_HANDLE_VALUE ) {
		LI_FN( CloseHandle )( ModuleSnapShot );
		return 0;
	}

	ModEntry32.dwSize = sizeof( MODULEENTRY32 );

	if ( LI_FN( Module32First )( ModuleSnapShot, &ModEntry32 ) ) {
		if ( !LI_FN( strcmp )( ModuleName, ModEntry32.szModule ) ) {
			LI_FN( CloseHandle )( ModuleSnapShot );
			return ( DWORD ) ModEntry32.modBaseAddr;
		}
	}

	while ( LI_FN( Module32Next )( ModuleSnapShot, &ModEntry32 ) ) {
		if ( !LI_FN( strcmp )( ModuleName, ModEntry32.szModule ) ) {
			LI_FN( CloseHandle )( ModuleSnapShot );
			return ( DWORD ) ModEntry32.modBaseAddr;
		}
	}

	LI_FN( CloseHandle )( ModuleSnapShot );
	return false;
}

std::uint32_t Memory::Find( const char* Process ) {
	auto Snapshot = LI_FN( CreateToolhelp32Snapshot )( TH32CS_SNAPPROCESS, 0 );
	PROCESSENTRY32 ProcessEntry;
	ProcessEntry.dwSize = sizeof( ProcessEntry );

	if ( LI_FN( Process32First )( Snapshot, &ProcessEntry ) ) {
		while ( LI_FN( Process32Next )( Snapshot, &ProcessEntry ) ) {
			if ( !LI_FN( strcmp )( Process, ProcessEntry.szExeFile ) ) {
				LI_FN( CloseHandle )( Snapshot );
				return ProcessEntry.th32ProcessID;
			}
		}
	}
	LI_FN( CloseHandle )( Snapshot );
	return 0;
}

void Memory::InitMemory( ) {
	if ( GetProcess( XorStr( "csgo.exe" ) ) ) {
		BaseAddress = GetModule( XorStr( "client.dll" ) );
		EngineAddress = GetModule( XorStr( "engine.dll" ) );

		ClientState = Read<DWORD>( EngineAddress + Offsets::dwClientState );
	}

	LocalPlayer::SetLocalPlayer( );
}