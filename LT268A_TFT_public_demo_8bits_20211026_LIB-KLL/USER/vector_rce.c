
#define _POSIX_SOURCE 	1

void DummyHandler(void)
{
  LTPrintf("WARNING: Default dummy interrupt handler entered \n");
}

void Misaligned_Access( void )
{
  LTPrintf("WARNING: Unexpected Misaligned Access exception taken \n");
}

void Access_Error( void )
{
  LTPrintf("WARNING: Unexpected Access Error exception taken \n");
}

void Illegal_Instrn( void )
{
  LTPrintf("WARNING: Unexpected Illegal_Instrn exception taken \n");
}


void Breakpoint_Exception( void )
{
  LTPrintf("WARNING: Unexpected Breakpoint exception taken \n");
}

void Unrecoverable_Error( void )
{
   LTPrintf("WARNING: Unexpected Unrecoverable_Error exception taken \n");
}

extern char _end_text[];
extern char _start_data[];
extern char _end_data[];

extern char _bss_start[];
extern char _bss_end[];

void __main(void)
{
	char *dst = _start_data;
	char *src = _end_text;
	int i;

	/* if the start of data (dst)
	 is not equal to end of text (src) then
	 copy it, else it's already in the right place
	 */
	if (_start_data != _end_text) {
		for(i=0;i<(_end_data - _start_data);i++)
			dst[i]=src[i];
	}

	/* zero the bss
	 */
	dst=_bss_start;
	if (_bss_end - _bss_start) {
		for(i=0;i<(_bss_end - _bss_start);i++)
			dst[i]=0;
	}
}


