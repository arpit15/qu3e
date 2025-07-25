#include <iostream>
#include <chrono>
#include "../src/q3.h"

int simloop( )
{
    // scene
    q3Scene scene( 1.0 / 60.0 );
    // Create the floor
    q3BodyDef bodyDef;
    //bodyDef.axis.Set( q3RandomFloat( -1.0f, 1.0f ), q3RandomFloat( -1.0f, 1.0f ), q3RandomFloat( -1.0f, 1.0f ) );
    //bodyDef.angle = q3PI * q3RandomFloat( -1.0f, 1.0f );
    q3Body* body = scene.CreateBody( bodyDef );
    
    q3BoxDef boxDef;
    q3Transform localSpace; // Contains position and orientation, see q3Transform.h for details
    q3Identity( localSpace ); // Specify the origin, and identity orientation
    boxDef.Set( localSpace, q3Vec3( 50.0f, 1.0f, 50.0f ) );
    body->AddBox( boxDef );
    
    // box body
    int num_boxes = 1000;
    float x_size = 2.0;
    float y_size = 3.0;
    float z_size = 1.0;
    // bodyDef.bodyType = eDynamicBody;
    boxDef.Set( localSpace, q3Vec3( x_size, y_size, z_size ) );
    for ( int i = 0; i < num_boxes; i++ )
    {
        bodyDef.position.Set(0, (y_size + 0.1) * i, 0);
        body = scene.CreateBody(bodyDef);
        body->AddBox(boxDef);
    }

    // add a dynamic box
    bodyDef.bodyType = eDynamicBody;
    bodyDef.position.Set(0, 0.0, 2 * z_size);
    body = scene.CreateBody(bodyDef);
    body->AddBox(boxDef);

    // main loop
    for ( int i = 0; i < 10; i++ )
    {
        scene.Step();
        // std::cout << "Step: " << i << std::endl;
    }

    return 0;

}

int main( int argc, char** argv )
{
    // calculate the time
    auto start = std::chrono::high_resolution_clock::now();
    for ( int i = 0; i < 10; i++ )
    {
        simloop( );
    }
    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
    std::cout << "Time taken: " << duration.count() << " milliseconds" << std::endl;
    return 0;
}