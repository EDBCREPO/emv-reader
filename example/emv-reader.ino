#include <nodepp.h>
#include "src/emv/emv.h"

using namespace nodepp;

void onMain() {

    char buff[UNBFF_SIZE]; memset( buff, 0, UNBFF_SIZE );
    Serial.begin( 115200 ); emv_t card( 2, 3, 4, 5 );

    process::add([=](){
        if( !card.is_available() ){ return 1; }
        static int c=0;
    coStart

        while( (c=card._read( buff, UNBFF_SIZE, 100 ))==-2 )
             { coNext; } if ( c<=0 ) { coGoto(0); }
        Serial.write( buff, c ); coGoto(0);

    coStop
    });

    process::add([=](){ int c=0;
        if( !Serial.available() ){ return 1; }
        
        auto data = Serial.readString();
        auto raw  = string_t( data.c_str(), data.length() );

        if( raw.empty() )               {               return 1; }
        if( raw.size()==1 && raw[0]==0 ){ card.reset(); return 1; }

        card.write( raw ); return 1;
    });

}
