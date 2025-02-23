#include <nodepp/nodepp.h>
#include <nodepp/serial.h>
#include <nodepp/encoder.h>
#include <nodepp/fs.h>

using namespace nodepp;

void onMain() {

    if( !fs::exists_file( path::join( "/dev", process::env::get("DEVICE") ) ) )
      { process::error( process::env::get("DEVICE"), "device not found" ); return; }

    serial_t str ( process::env::get("DEVICE"), 115200 );

    cin::onData([=]( string_t data ){
        str.write( encoder::buffer::hex2buff( data.slice( 0, -1 ) ) );
    });

    str::onData([=]( string_t data ){
        console::log( "->", encoder::buffer::buff2hex( data ) );
    });

    str::onClose([=](){
        console::log(" Device Disconnected ");
    }); console::log(" Device Connected ");

    stream::pipe( cin );
    stream::pipe( str );

}