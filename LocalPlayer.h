#pragma once
#include <windows.h>

#include "Vector.h"

namespace LocalPlayer {
	extern DWORD GetLocalPlayer( );												
	extern int GetLocalFlags( );												
	extern int GetLocalHealth( );												
	extern int GetLocalCrossID( );		
	extern int GetLocalActiveWeapon( );
	extern DWORD GetLocalWeaponHandle( );
	extern DWORD GetLocalCurrentWeapon( );
	extern int GetLocalTeam( );																																											//Void functions 
	extern void ForceJump( int Wait = 35 );
	extern void SetLocalPlayer( );												
	extern void SetLocalViewAngles( Vector3 Angles );
	extern Vector3 GetLocalPos( );
	extern Vector3 GetLocalViewMatrix( );
	extern Vector3 GetLocalViewAngles( );
	extern Vector3 GetLocalPunchAngles( );

	extern DWORD LocalBaseaddress;											
}