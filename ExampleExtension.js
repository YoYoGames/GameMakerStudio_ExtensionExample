function MyExtension_Init()
{
}

function MyExtension_Quit()
{
}

function MyExtension_Function( _argument0 )
{
	return _argument0 * 100;
}

function MyExtension_StringReturn( _heading, _value )
{
	return _heading + _value;
}

function MyExtension_BufferPointer( buffer_pointer, size )
{
	var view = new Uint8Array( buffer_pointer, 0, size );
	var total = 0;
	for( var i=0; i<size; ++i) {
		total += view[i];
		view[i] = i;
	}

	return "Total = " + total;
}