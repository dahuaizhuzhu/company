
	.text
	.export	__start
	.align 4
	.global __start
	.type __start,@function
__start:
	// set the stack
	lrw	r1, STACK_LOCATION
	mov	r0,r1

skip_set_vbr:	

  lrw	r1, VECTOR_LOCATION
	mtcr r1,vbr
	mfcr r2,vbr
	//Close Watch dog 0/1
  	lrw		r7,0x40130002
  	ldh     r6,(r7)
  	bclri   r6,0
  	sth     r6,(r7)
  	lrw		r7,0x40140002
  	ldh     r6,(r7)
  	bclri   r6,0
  	sth     r6,(r7)


//.ifdef CACHE_ENABLE
	// rcache initialization
	lrw	r7,0xfff81000    // 15728384
        lrw     r6,0x400
        lrw     r5,0x0
        lrw     r4,0x0

cache_tag_init:
	stw	r4,(r7)
	addi    r5,16
	addi    r7,16
	cmpne   r6,r5
	bt      cache_tag_init
 	movi    r6, 1
  	lrw     r7, 0xFFF80000
  	stw     r6, (r7, 0)
//.endif

	// zero the other regs
	movi	r1,0
	movi	r2,0		// argc
	movi	r3,0		// argv
	movi	r4,0
	movi	r5,0
	movi	r6,0
	movi	r7,0
	movi	r8,0
	movi	r9,0
	movi	r10,0
	movi	r11,0
	movi	r12,0
	movi	r13,0
	movi	r14,0
	movi	r15,0

	// call main (of the C code)
	jsri  __main
	jsri	main
	
	.export	exit
exit:	
	
	br 	exit
		  
