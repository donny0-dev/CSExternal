#pragma  once
#include <windows.h>
#include <tlhelp32.h>
#include <iostream>
#include <string>

#include "LocalPlayer.h"
#include "Memory.h"
#include "Offsets.h"

DWORD LocalPlayer::LocalBaseaddress = 0;

DWORD LocalPlayer::GetLocalPlayer( ) {
	return LocalPlayer::LocalBaseaddress;
}

void LocalPlayer::SetLocalPlayer( ) {
	LocalPlayer::LocalBaseaddress = Memory::Read<DWORD>( Memory::BaseAddress + Offsets::dwLocalPlayer );
}

int LocalPlayer::GetLocalFlags( ) {
	return Memory::Read<int>( LocalPlayer::GetLocalPlayer( ) + Offsets::m_fFlags );
}

int LocalPlayer::GetLocalHealth( ) {
	return Memory::Read<int>( LocalPlayer::GetLocalPlayer( ) + Offsets::m_iHealth );
}

int LocalPlayer::GetLocalTeam( ) {
	return Memory::Read<int>( LocalPlayer::GetLocalPlayer( ) + Offsets::m_iTeamNum );
}

void LocalPlayer::ForceJump( int Wait ) {
	Memory::Write<int>( 1, Memory::BaseAddress + Offsets::dwForceJump );
	Sleep( Wait );
	Memory::Write<int>( 0, Memory::BaseAddress + Offsets::dwForceJump );
}

int LocalPlayer::GetLocalCrossID( ) {
	auto Temp = Memory::Read<int>( LocalPlayer::GetLocalPlayer( ) + Offsets::m_iCrosshairId );

	if ( Temp <= 0 || Temp > 32 )
		return -1;

	return Temp;
}

DWORD LocalPlayer::GetLocalWeaponHandle( ) {
	return Memory::Read<DWORD>( LocalPlayer::GetLocalPlayer( ) + Offsets::m_hActiveWeapon );
}

DWORD LocalPlayer::GetLocalCurrentWeapon( ) {
	int GetWeaponHandle = LocalPlayer::GetLocalWeaponHandle( ) & 0xFFF;
	return Memory::Read<DWORD>( Memory::BaseAddress + Offsets::dwEntityList + ( GetWeaponHandle - 1 ) * 0x10 );
}

int LocalPlayer::GetLocalActiveWeapon( ) {
	return Memory::Read<int>( LocalPlayer::GetLocalCurrentWeapon( ) + Offsets::m_iItemDefinitionIndex );
}

Vector3 LocalPlayer::GetLocalPos( ) {
	return Memory::Read<Vector3>( LocalPlayer::GetLocalPlayer( ) + Offsets::m_vecOrigin );
}

Vector3	LocalPlayer::GetLocalViewMatrix( ) {
	return Memory::Read<Vector3>( Memory::BaseAddress + Offsets::dwViewMatrix );
}

Vector3 LocalPlayer::GetLocalViewAngles( ) {
	return Memory::Read<Vector3>( Memory::ClientState + Offsets::dwClientState_ViewAngles );
}

void LocalPlayer::SetLocalViewAngles( Vector3 Angles ) {
	Memory::Write<Vector3>( Angles, Memory::ClientState + Offsets::dwClientState_ViewAngles );
}

Vector3 LocalPlayer::GetLocalPunchAngles( ) {
	return Memory::Read<Vector3>( LocalPlayer::GetLocalPlayer( ) + Offsets::m_aimPunchAngle );
}