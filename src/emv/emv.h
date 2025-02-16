/*
 * Copyright 2023 The Nodepp Project Authors. All Rights Reserved.
 *
 * Licensed under the MIT (the "License").  You may not use
 * this file except in compliance with the License.  You can obtain a copy
 * in the file LICENSE in the source distribution or at
 * https://github.com/NodeppOficial/nodepp/blob/main/LICENSE
 */

/*────────────────────────────────────────────────────────────────────────────*/

#ifndef EMV_READER
#define EMV_READER

/*────────────────────────────────────────────────────────────────────────────*/

#include "utility/SoftwareSerial.h"
#include <nodepp/encoder.h>
using CARD = SoftwareSerial;

/*────────────────────────────────────────────────────────────────────────────*/

namespace nodepp { enum emv_protocol {
    PROTOCOL_T0 = 0,
    PROTOCOL_T1 = 1
};}

/*────────────────────────────────────────────────────────────────────────────*/

namespace nodepp { class emv_t {
protected:

    struct NODE {
        ptr_t<CARD> ctx;
        bool state   =0;
        ptr_t<uchar> IO;
    };  ptr_t<NODE> obj;
    
    /*─······································································─*/

    static clock() { 
    if( OCR1A == 1 ){ return; }
        TCCR1B = 0B00001001;
        TCCR1A = 0B01000000;
        OCR1A  = 1; TCNT1=0;
        pinMode( 9, OUTPUT );
    }
    
    /*─······································································─*/

    void begin( uchar rx, uchar tx, uint baudrate ) const noexcept {
        obj->ctx = new CARD( rx, tx );
        obj->ctx->begin( baudrate ); 
        obj->ctx->listen();
    }

public:

    emv_t( uchar vcc, uchar rst, uchar rx, uchar tx ) noexcept : obj( new NODE ) {
        obj->IO = ptr_t<uchar>({ vcc, rst, rx, tx }); obj->state=1;
        pinMode( vcc,OUTPUT ); pinMode( rst,OUTPUT );
        pinMode(  tx,OUTPUT ); pinMode(  rx,INPUT  );
        clock(); reset(); begin( rx, tx, 10753 );
    }

   ~emv_t() noexcept { if( obj.count()>1 ){ return; } free(); }

    emv_t() noexcept : obj( new NODE ) {}

    /*─······································································─*/

    bool is_closed()    const noexcept { return obj->state==0 || obj->ctx==nullptr; }
    bool is_available() const noexcept { return !is_closed(); }
    void close()        const noexcept { free(); }
    
    /*─······································································─*/

    void off() const noexcept {
        digitalWrite( obj->IO[0], 0 );
        digitalWrite( obj->IO[1], 0 );
    }

    void reset() const noexcept { off(); delay(5);
        digitalWrite( obj->IO[0], 1 );   delay(5);
        digitalWrite( obj->IO[1], 1 );
    }

    void flush() const noexcept {
        digitalWrite( obj->IO[1], 0 );   delay(5);
        digitalWrite( obj->IO[1], 1 );
        obj->ctx->flush();
    }

    /*─······································································─*/

    string_t read( ulong timeout=30 ) const noexcept { 
        int c=0; ptr_t<char> buffer ( CHUNK_SIZE, '\0' );
        while( (c=_read( buffer.get(), buffer.size(), timeout ))==-2 )
             { process::next(); }if( c<=0 ){ return nullptr; }
        return string_t( buffer.get(), c );
    }

    int write( string_t data ) const noexcept { int c=0;
        while( (c=_write( data.get(), data.size() ))==-2 )
             { process::next(); } return c;
    }

    /*─······································································─*/

    int _read( char *buffer, ulong size, ulong timeout=30 ) const noexcept { 
    if( is_closed() )               { return -1; } int len=0;
    if( buffer==nullptr || size==0 ){ return  0; } int   c=0;
        pinMode( obj->IO[3], INPUT_PULLUP );  
        ulong stamp = process::now();

        while( (process::now()-stamp)<timeout && len<size ){
           if( !obj->ctx->available() ){ continue; }
           buffer[len]=obj->ctx->read(); 
           stamp=process::now(); len++;
        }
        
        pinMode( obj->IO[3], OUTPUT ); return len;
    }

    int _write( char *buffer, ulong size ) const noexcept {
    if( is_closed() )               { return -1; } int len=0;
    if( buffer==nullptr || size==0 ){ return  0; } int   c=0;
        obj->ctx->stopListening();

        for( len=0; len<size; len++ )
           { obj->ctx->write_8E2(buffer[len]); }
        
        obj->ctx->listen(); return len;
    }

    /*─······································································─*/

    void free() const noexcept { if( obj->state==0 ) { return; } obj->state=0; }

};}

/*────────────────────────────────────────────────────────────────────────────*/

#endif