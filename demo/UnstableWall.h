struct UnstableWall : public Demo
{
    virtual void Init()
    {
        // Create the floor
		q3BodyDef bodyDef;
		//bodyDef.axis.Set( q3RandomFloat( -1.0f, 1.0f ), q3RandomFloat( -1.0f, 1.0f ), q3RandomFloat( -1.0f, 1.0f ) );
		//bodyDef.angle = q3PI * q3RandomFloat( -1.0f, 1.0f );
		q3Body* body = scene.CreateBody( bodyDef );

		q3BoxDef boxDef;
		boxDef.SetRestitution( 0 );
		q3Transform tx;
		q3Identity( tx );
		boxDef.Set( tx, q3Vec3( 50.0f, 1.0f, 50.0f ) );
		body->AddBox( boxDef );

        // size
        boxDef.Set( tx, q3Vec3( 3.0f, 2.0f, 1.0f ) );
        // Create the wall
        bodyDef.position.Set( 0.0f, 2.0f, 0.0f );
        // Create a new body
        body = scene.CreateBody( bodyDef );
        body->AddBox( boxDef );
        
        bodyDef.bodyType = eDynamicBody;
        bodyDef.position.Set( 2.5f, 5.0f, 0.0f );
        body = scene.CreateBody( bodyDef );
        body->AddBox( boxDef );
    }

    virtual void Shutdown( )
	{
		scene.RemoveAllBodies( );
	}
};