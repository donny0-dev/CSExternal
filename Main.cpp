#include <Windows.h>
#include <iostream>
#include <thread>

#include "Utils.h"
#include "LazyImporter.h"
#include "XorStr.h"
#include "Memory.h"
#include "Offsets.h"
#include "LocalPlayer.h"
#include "Defs.h"

void Menu( ) {
	Utils::RenderString( XorStr( "Happy hacking! \n" ) );
}

void Hack( ) {
	Memory::InitMemory( );

	while ( true ) {
		if ( GetAsyncKeyState( VK_SPACE ) && LocalPlayer::GetLocalFlags( ) == FL_ON_GROUND ) {
			LocalPlayer::ForceJump( );
		}

		Sleep( 1 );
	}

	LI_FN( CloseHandle )( Memory::Process );
}

int main( ) {
	LI_FN( SetConsoleTitleA )( Utils::RandomString( 25 ).c_str( ) );

	std::thread One( Hack );
	std::thread Two( Hack );

	One.join( );
	Two.join( );

	std::cin.ignore( );
	return NULL;
}