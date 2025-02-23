#include <nodepp/nodepp.h>
#include <nodepp/serial.h>
#include <nodepp/encoder.h>
#include <nodepp/fs.h>

using namespace nodepp;

void onMain() {

    auto dir = "/dev/" + process::env::get("DEVICE");

    if( process::env::get("DEVICE").empty() ){ goto ERROR; }
    if( !fs::exists_file( dir ) )            { goto ERROR; }

    do {

        auto str = serial_t( dir, 115200 );
        auto cin = fs::std_input();

        cin.onData([=]( string_t data ){
            auto hex = regex::match_all( data, "\\w+" );
            str.write( encoder::buffer::hex2buff( hex.join("") ) );
        });

        str.onData([=]( string_t data ){
            console::log( "->", encoder::buffer::buff2hex( data ) );
        });

        str.onClose([=](){
            console::log(" Device Disconnected ");
        }); console::log(" Device Connected ");

        stream::pipe( cin ); stream::pipe( str );

    } while(0); return; ERROR:;

    process::error( process::env::get("DEVICE"), "device not found" );

}