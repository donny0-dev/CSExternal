#pragma once
#include <string>
#include <time.h>
#include <thread>
#include <iostream>

namespace Utils {
    inline std::string RandomString( const int Length ) {

        std::string TempString;

        static const char Characters[ ] =
            "0123456789"
            "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
            "abcdefghijklmnopqrstuvwxyz";

        srand( ( unsigned ) time( NULL ) * rand( ) % INT_MAX );

        TempString.reserve( Length );

        for ( int i = 0; i < Length; ++i )
            TempString += Characters[ rand( ) % ( sizeof( Characters ) - 1 ) ];


        return TempString;
    }

    inline float RandomFloat( float Min, float Max ) {
        float Random = ( float ) rand( ) / ( float ) RAND_MAX;
        return Min + Random * ( Max - Min );
    }

    inline void RenderString( std::string String ) {
        std::cout << String;
    }

    inline bool IsRunning( const char* Name ) {
        HWND HWND;
        HWND = FindWindowA( NULL, Name );

        if ( HWND != 0 )
            return true;
        else
            return false;
    }
};