//for c0 fp

	
.section .text

	.export	 __addsf3
	.export	 __subsf3
	.export	 __mulsf3
	.export	 __divsf3
	.export sfpFloatNormalize

	.export	 _f_ftod
	.export	 _f_itof

	.align 4
ff1_r14:
	btsti r14,31
	movi r6,0
	bt bk_rt

	btsti r14,30
	movi r6,1
	bt bk_rt

	btsti r14,29
	movi r6,2
	bt bk_rt

	btsti r14,28
	movi r6,3
	bt bk_rt

	btsti r14,27
	movi r6,4
	bt bk_rt

	btsti r14,26
	movi r6,5
	bt bk_rt

	btsti r14,25
	movi r6,6
	bt bk_rt

	btsti r14,24
	movi r6,7
	bt bk_rt

	btsti r14,23
	movi r6,8
	bt bk_rt

	btsti r14,22
	movi r6,9
	bt bk_rt

	btsti r14,21
	movi r6,10
	bt bk_rt

	btsti r14,20
	movi r6,11
	bt bk_rt

	btsti r14,19
	movi r6,12
	bt bk_rt

	btsti r14,18
	movi r6,13
	bt bk_rt

	btsti r14,17
	movi r6,14
	bt bk_rt

	btsti r14,16
	movi r6,15
	bt bk_rt

	btsti r14,15
	movi r6,16
	bt bk_rt

	btsti r14,14
	movi r6,17
	bt bk_rt

	btsti r14,13
	movi r6,18
	bt bk_rt

	btsti r14,12
	movi r6,19
	bt bk_rt

	btsti r14,11
	movi r6,20
	bt bk_rt

	btsti r14,10
	movi r6,21
	bt bk_rt

	btsti r14,9
	movi r6,22
	bt bk_rt

	btsti r14,8
	movi r6,23
	bt bk_rt

	btsti r14,7
	movi r6,24
	bt bk_rt

	btsti r14,6
	movi r6,25
	bt bk_rt

	btsti r14,5
	movi r6,26
	bt bk_rt

	btsti r14,4
	movi r6,27
	bt bk_rt

	btsti r14,3
	movi r6,28
	bt bk_rt

	btsti r14,2
	movi r6,29
	bt bk_rt

	btsti r14,1
	movi r6,30
	bt bk_rt

	btsti r14,0
	movi r6,31
	bt bk_rt

	movi r6,32
bk_rt:
	mov r14,r6
	jmp r15
sfpFloatNormalize:
		subi	r0, 16
		stm	r13-r15, (r0)
		mov	r14, r4
		ff1	r14
		//jsri ff1_r14
     	subi	r14, 8
     	movi	r6, 127
     	subu	r6, r14
     	addu	r3, r6
     	cmplti	r3, 1
     	mov	r13, r5
		.short 0xe809  //      	bf	0x80050c
     	addu	r14, r3
     	subi	r14, 1
     	movi	r7, 34
     	rsubi	r7, 0
     	cmplt	r14, r7
   	   .short 0xe802  //    	bf	0x80050a
     	lsli	r2, 31
		.short 0xf051    //  	br	0x8005ac
     	movi	r3, 0
     	cmplti	r14, 1
		.short 0xe00f //     	bt	0x80052e
     	cmplti	r14, 32
		.short 0xe005 //     	bt	0x80051e
     	mov	r4, r13
     	subi	r14, 32
     	lsl	r4, r14
     	movi	r13, 0
		.short 0xf01b //     	br	0x800554
     	movi	r5, 32
     	mov	r6, r13
     	subu	r5, r14
     	lsl	r4, r14
     	lsr	r6, r5
     	or	r4, r6
     	lsl	r13, r14
		.short 0xf013   //   	br	0x800554
     	btsti	r14, 31
		.short 0xe811  //     	bf	0x800554
     	cmpnei	r5, 0
     	movi	r1, 32
     	mvc	r13
     	rsubi	r1, 0
     	cmplt	r1, r14
     	mov	r6, r4
		.short 0xe004   //   	bt	0x800548
     	subu	r1, r14
     	lsr	r6, r1
     	movi	r4, 0
		.short 0xf005   //   	br	0x800552
     	mov	r5, r14
     	addi	r5, 32
     	lsl	r6, r5
     	rsubi	r14, 0
     	lsr	r4, r14
     	or	r13, r6
     	lrw	r7, __sfpRoundMode
				//movi r7,0
     	bclri	r4, 23
     	ld	r7, (r7, 0)
     	//movi r7,0
     	cmpnei	r7, 0
		.short 0xe805  //    	bf	0x800568
     	cmpnei	r7, 2
		.short 0xe80c  //    	bf	0x80057a
     	cmpnei	r7, 3
		.short 0xe810   //   	bf	0x800586
		.short 0xf015    //  	br	0x800592
     	btsti	r13, 31
		.short 0xe813    //  	bf	0x800592
     	bmaski	r7, 31
     	tst	r13, r7
    	.short 0xe002    //  	bt	0x800576
     	btsti	r4, 0
		.short 0xe80e    //  	bf	0x800592
     	addi	r4, 1
		.short 0xf00c    //  	br	0x800592
     	cmpnei	r2, 0
		.short 0xe00a    //  	bt	0x800592
     	btsti	r13, 31
		.short 0xe808    //  	bf	0x800592
     	addi	r4, 1
		.short 0xf006    //  	br	0x800592
     	cmpnei	r2, 0
		.short 0xe804   //   	bf	0x800592
     	bgeni	r7, 31
     	and	r7, r13
     	cmpnei	r7, 0
     	inct	r4
     	btsti	r4, 23
     	inct	r3
     	clrt	r4
     	bmaski	r7, 8
     	cmplt	r3, r7
     	lsli	r2, 31
		.short 0xe003     // 	bt	0x8005a6
     	lrw	r6, 0x7F800000
     	or	r2, r6
		.short 0xf003     // 	br	0x8005ac
     	lsli	r3, 23
     	or	r2, r3
     	or	r2, r4
     	ldm	r13-r15, (r0)
     	addi	r0, 16
     	jmp	r15

__addsf3:
    	subi	r0, 16
    	stm	r12-r15, (r0)
    	mov	r13, r2
    	lsri	r13, 23
    	bmaski	r4, 23
    	mov	r5, r2
    	zextb	r13
    	and	r4, r2
    	bmaski	r7, 8
    	lsri	r2, 31
    	cmpne	r13, r7
    	andi	r2, 1
		.short 0xe014     // 	bt	0x8002be
    	cmpnei	r4, 0
		.short 0xe010      //	bt	0x8002ba
    	mov	r14, r3
    	lsri	r14, 23
    	zextb	r14
    	mov	r13, r3
    	bmaski	r4, 23
    	lsri	r13, 31
    	cmpne	r14, r7
    	and	r4, r3
    	andi	r13, 1
		.short 0xe006     // 	bt	0x8002ba
    	cmpnei	r4, 0
    	movt	r2, r3
		.short 0xe06b      //	bt	0x80038a
    	cmpne	r2, r13
    	lrw	r2, 0x7F800001
		.short 0xe068      //	bt	0x80038a
    	mov	r2, r5
		.short 0xf066     // 	br	0x80038a
    	cmpnei	r13, 0
		.short 0xe00f      //	bt	0x8002e0
    	cmpnei	r4, 0
		.short 0xe00a     // 	bt	0x8002da
    	bmaski	r7, 31
    	tst	r3, r7
		.short 0xe005     // 	bt	0x8002d6
    	lsri	r3, 31
    	and	r2, r3
    	andi	r2, 1
    	lsli	r2, 31
		.short 0xf05a      //	br	0x80038a
    	mov	r2, r3
		.short 0xf058     // 	br	0x80038a
    	movi	r13, 126
    	rsubi	r13, 0
		.short 0xf004      //	br	0x8002e8
    	bseti	r4, 23
    	mov	r7, r13
    	movi	r13, 127
    	rsub	r13, r7
    	mov	r12, r3
    	lsri	r12, 23
    	zextb	r12
    	bmaski	r6, 8
    	cmpne	r12, r6
    	movf	r2, r3
		.short 0xe84a      //	bf	0x80038a
    	bmaski	r14, 23
    	and	r14, r3
    	cmpnei	r12, 0
		.short 0xe006      //	bt	0x80030a
    	cmpnei	r14, 0
    	movf	r2, r5
		.short 0xe843      //	bf	0x80038a
    	movi	r12, 126
    	rsubi	r12, 0
		.short 0xf004     /// 	br	0x800312
    	bseti	r14, 23
    	mov	r7, r12
    	movi	r12, 127
    	rsub	r12, r7
    	lsri	r3, 31
    	andi	r3, 1
    	mov	r1, r13
    	subu	r1, r12
    	cmplti	r1, 1
		.short 0xe00c     // 	bt	0x800336
    	cmplti	r1, 32
    	mov	r5, r14
		.short 0xe004      //	bt	0x80032c
    	subi	r1, 32
    	lsr	r5, r1
    	movi	r14, 0
		.short 0xf01e      //	br	0x800368
    	movi	r6, 32
    	subu	r6, r1
    	lsl	r5, r6
    	lsr	r14, r1
		.short 0xf019     // 	br	0x800368
    	btsti	r1, 31
		.short 0xe811     // 	bf	0x80035c
    	mov	r7, r1
    	rsubi	r7, 0
    	cmplti	r7, 32
    	mov	r5, r4
    	mov	r6, r1
		.short 0xe005     // 	bt	0x800350
    	rsubi	r6, 0
    	subi	r6, 32
    	lsr	r5, r6
    	movi	r4, 0
		.short 0xf004     // 	br	0x800358
    	addi	r6, 32
    	lsl	r5, r6
    	rsubi	r1, 0
    	lsr	r4, r1
    	mov	r13, r12
		.short 0xf006     // 	br	0x800368
    	cmpne	r2, r3
		.short 0xe803     // 	bf	0x800366
    	cmpne	r4, r14
    	clrf	r2
		.short 0xe812    //  	bf	0x80038a
    	movi	r5, 0
    	cmpne	r2, r3
	.short 0xe002     // 	bt	0x800370
    	addu	r4, r14
		.short 0xf00b     // 	br	0x800386
    	cmphs	r14, r4
		.short 0xe002     // 	bt	0x800378
    	subu	r4, r14
		.short 0xf003     // 	br	0x80037e
    	rsub	r4, r14
    	movi	r6, 1
    	xor	r2, r6
    	cmpnei	r5, 0
.short 0xe802      //	bf	0x800386
    	rsubi	r5, 0
    	subi	r4, 1
    	mov	r3, r13
    	jsri	sfpFloatNormalize	// 8003a0 <sfpFloatNormalize>
    	ldm	r12-r15, (r0)
    	addi	r0, 16
    	jmp	r15

__subsf3:
       	mov	r1, r3
       	bgeni	r3, 31
       	xor	r3, r1
		.short 0xf772      //	br	0x80028c


__mul6432:
  	mov	r6, r2
  	lsri	r6, 16
  	zexth	r2
  	mov	r7, r3
  	lsri	r7, 16
  	zexth	r3
  	mov	r1, r7
  	mult	r1, r2
  	mult	r7, r6
  	mult	r6, r3
  	mult	r2, r3
  	cmpne	r0, r0
  	addc	r1, r6
  	mvc	r3
  	lsli	r3, 16
  	addu	r3, r7
  	mov	r7, r1
  	lsli	r1, 16
  	lsri	r7, 16
  	cmpne	r0, r0
  	addc	r2, r1
  	addc	r3, r7
   	jmp	r15


ff1r1:
		subi r0, 4
		stw  r11,(r0)
		movi r6, 31
	.YW31:
		mov  r11, r1
		lsr  r11, r6
		cmpnei r11, 0
		bf    .YW11
	.YW21:
	    rsubi r6, 31
		mov   r1, r6
		br .YW41
	.YW11:
		subi r6, 1
		mov  r11, r1
		lsr  r11, r6
		cmpnei r11, 0
		bt .YW21
		cmpnei r6, 0
		bt .YW31
		movi r1, 32
	.YW41:
		//restore r11
		ldw r11, (r0)
		addi r0, 4
		jmp  r15

ff1r3:
		subi r0, 4
		stw  r11,(r0)
		movi r6, 31
	.YW33:
		mov  r11, r3
		lsr  r11, r6
		cmpnei r11, 0
		bf    .YW13
	.YW23:
	    rsubi r6, 31
		mov   r3, r6
		br .YW43
	.YW13:
		subi r6, 1
		mov  r11, r3
		lsr  r11, r6
		cmpnei r11, 0
		bt .YW23
		cmpnei r6, 0
		bt .YW33
		movi r3, 32
	.YW43:
		ldw r11, (r0)
		addi r0, 4
		jmp  r15

__mulsf3:
			subi	r0, 16
			stm	r13-r15, (r0)
			subi	r0, 8
			mov	r14, r2
			mov	r13, r2
			bmaski	r2, 23
			mov	r4, r3
			lsri	r13, 23
			and	r2, r14
			zextb	r13
			lsri	r14, 31
			lsri	r3, 31
			bmaski	r7, 8
			andi	r14, 1
			andi	r3, 1
			cmpne	r13, r7
			xor	r14, r3
			.short 0xe018
			cmpnei	r2, 0
			.short 0xe014
			mov	r2, r4
			lsri	r2, 23
			zextb	r2
			bmaski	r6, 23
			cmpne	r2, r7
			and	r4, r6
			.short 0xe004
			cmpnei	r4, 0
			.short 0xe806
			cmpne	r2, r7
			.short 0xe809
			cmpnei	r4, 0
			.short 0xe002
			cmpnei	r2, 0
			.short 0xe805
			lrw	r6, 0x7F800000
			mov	r2, r14
			lsli	r2, 31
			or	r2, r6
			.short 0xf047
			lrw	r2, 0x7F800001
			.short 0xf045
			cmpnei	r13, 0
			.short 0xe00a
			cmpnei	r2, 0
			.short 0xe80c
			mov	r1, r2
			ff1 r1
			//jsri ff1r1
			movi	r13, 126
			subi	r1, 8
			rsubi	r13, 0
			subu	r13, r1
			lsl	r2, r1
			.short 0xf004
			bseti	r2, 23
			mov	r7, r13
			movi	r13, 127
			rsub	r13, r7
			mov	r1, r4
			lsri	r1, 23
			zextb	r1
			bmaski	r7, 8
			bmaski	r6, 23
			cmpne	r1, r7
			and	r4, r6
			.short 0xe00a
			cmpnei	r4, 0
			.short 0xe006
			lrw	r6, 0x7F800000
			cmpnei	r2, 0
			mov	r2, r14
			lsli	r2, 31
			or	r2, r6
			.short 0xe025
			lrw	r2, 0x7F800001
 			.short 0xf047
			cmpnei	r1, 0
			.short 0xe00d
			cmpnei	r4, 0
			.short 0xe003
			mov	r2, r14
			lsli	r2, 31
			.short 0xf01c
			mov	r3, r4
			//jsri ff1r3
			ff1 r3
			//movi r3,2
			movi	r1, 126
			subi	r3, 8
			rsubi	r1, 0
			subu	r1, r3
			lsl	r4, r3
			.short 0xf004
			bseti	r4, 23
			mov	r7, r1
			movi	r1, 127
			rsub	r1, r7
			cmpnei	r2, 0
			.short 0xe003
			mov	r2, r14
			lsli	r2, 31
			.short 0xf00b
			addu	r13, r1
			addi	r13, 9
			mov	r3, r4
			jsri	__mul6432	// 800474 <__mul6432>
			st	r2, (r0, 0)
			st	r3, (r0, 4)
			mov	r4, r3
			mov	r5, r2
			mov	r2, r14
			mov	r3, r13
			jsri	sfpFloatNormalize	// 800374 <sfpFloatNormalize>
			addi	r0, 8
			ldm	r13-r15, (r0)
			addi	r0, 16
			jmp	r15

ff1r2:
		subi r0, 4
		stw  r11,(r0)
		movi r6, 31
	.YW32:
		mov  r11, r2
		lsr  r11, r6
		cmpnei r11, 0
		bf    .YW12
	.YW22:
	    rsubi r6, 31
		mov   r2, r6
		br .YW42
	.YW12:
		subi r6, 1
		mov  r11, r2
		lsr  r11, r6
		cmpnei r11, 0
		bt .YW22
		cmpnei r6, 0
		bt .YW32
		movi r2, 32
	.YW42:
		ldw r11, (r0)
		addi r0, 4
		jmp  r15

ff1r4:
		subi r0, 4
		stw  r11,(r0)
		movi r6, 31
	.YW34:
		mov  r11, r4
		lsr  r11, r6
		cmpnei r11, 0
		bf    .YW14
	.YW24:
	    rsubi r6, 31
		mov   r4, r6
		br .YW44
	.YW14:
		subi r6, 1
		mov  r11, r4
		lsr  r11, r6
		cmpnei r11, 0
		bt .YW24
		cmpnei r6, 0
		bt .YW34
		movi r4, 32
	.YW44:
		ldw r11, (r0)
		addi r0, 4
		jmp  r15

__divsf3:
      	subi	r0, 8
      	mov	r4, r3
      	mov	r3, r2
      	lsri	r3, 23
      	mov	r5, r2
      	mov	r1, r4
      	zextb	r3
      	lsri	r5, 31
      	lsri	r1, 31
      	bmaski	r7, 8
      	bmaski	r6, 23
      	andi	r5, 1
      	andi	r1, 1
      	cmpne	r3, r7
      	st	r15, (r0, 0)
      	and	r6, r2
      	xor	r5, r1
		.short 0xe010      //	bt	0x8002c0
      	mov	r3, r4
      	lsri	r3, 23
      	zextb	r3
      	cmpnei	r6, 0
		.short 0xe007      //	bt	0x8002b8
      	cmpne	r3, r7
		.short 0xe807      //	bf	0x8002bc
      	lrw	r6, 0x7F800000
      	mov	r2, r5
      	lsli	r2, 31
      	or	r2, r6
		.short 0xf058      //	br	0x800368
      	cmpne	r3, r7
		.short 0xe056      //	bt	0x800368
      	lrw	r2, 0x7F800001
		.short 0xf054     // 	br	0x800368
      	cmpnei	r3, 0
		.short 0xe00a      //	bt	0x8002d8
      	cmpnei	r6, 0
		.short 0xe80c      //	bf	0x8002e0
      	mov	r2, r6
      	ff1	r2
		//jsri ff1r2
      	movi	r3, 126
      	subi	r2, 8
      	rsubi	r3, 0
      	subu	r3, r2
      	lsl	r6, r2
		.short 0xf004      	//br	0x8002e0
      	bseti	r6, 23
      	mov	r7, r3
      	movi	r3, 127
      	rsub	r3, r7
      	mov	r1, r4
      	lsri	r1, 23
      	zextb	r1
      	bmaski	r7, 8
      	bmaski	r2, 23
      	cmpne	r1, r7
      	and	r2, r4
		.short 0xe006      	///bt	0x8002fc
      	cmpnei	r2, 0
      	mov	r2, r5
      	lsli	r2, 31
		.short 0xe838      //	bf	0x800368
      	mov	r2, r4
		.short 0xf036      //	br	0x800368
      	cmpnei	r1, 0
		.short 0xe012      //	bt	0x800324
      	cmpnei	r2, 0
		.short 0xe008      	//bt	0x800314
      	cmpnei	r6, 0
      	lrw	r2, 0x7F800001
		.short 0xe82f      	//bf	0x800368
      	lrw	r6, 0x7F800000
      	mov	r2, r5
      	lsli	r2, 31
      	or	r2, r6
		.short 0xf02a      //	br	0x800368
      	mov	r4, r2
      	ff1	r4
      	//jsri ff1r4
      	movi	r1, 126
      	subi	r4, 8
      	rsubi	r1, 0
      	subu	r1, r4
      	lsl	r2, r4
		.short 0xf004      	//br	0x80032c
      	bseti	r2, 23
      	mov	r7, r1
      	movi	r1, 127
      	rsub	r1, r7
      	cmpnei	r6, 0
		.short 0xe003      //	bt	0x800336
      	mov	r2, r5
      	lsli	r2, 31
		.short 0xf019      //	br	0x800368
      	subu	r3, r1
      	mov	r7, r2
      	subi	r7, 1
      	tst	r2, r7
      	mov	r4, r6
		.short 0xe810      	//bf	0x800362
      	addi	r3, 24
      	movi	r4, 0
      	subi	r3, 1
      	lsli	r4, 1
      	cmphs	r6, r2
		.short 0xe802      //	bf	0x800352
      	subu	r6, r2
      	bseti	r4, 0
      	lsli	r6, 1
      	cmpnei	r6, 0
		.short 0xe802      	//bf	0x80035c
      	btsti	r4, 26
		.short 0xeff5      //	bf	0x800346
      	cmpnei	r6, 0
		.short 0xe801      	//bf	0x800362
      	bseti	r4, 0
      	mov	r2, r5
      	movi	r5, 0
      	jsri	sfpFloatNormalize	  // 80037c <sfpFloatNormalize>
      	ld	r15, (r0, 0)
      	addi	r0, 8
      	jmp	r15


_f_ftod:
 	subi	r0, 8
 	st	r14, (r0, 0)
 	mov	r14, r2
 	lsri	r14, 23
 	mov	r3, r2
 	zextb	r14
 	mov	r7, r2
 	lsri	r3, 31
 	bmaski	r6, 23
 	cmpnei	r14, 0
 	andi	r3, 1
 	and	r7, r6
	.short 0xe00d      	//bt	0x20000c2c
 	cmpnei	r7, 0
	.short 0xe004      	//bt	0x20000c1e
 	lsli	r3, 11
 	lsli	r3, 20
 	mov	r2, r7
	.short 0xf019      	//br	0x20000c50
 	mov	r1, r7
 	//jsri ff1r1  
	ff1	r1
 	subi	r1, 8
 	mov	r14, r1
 	lsl	r7, r1
 	rsubi	r14, 1
 	bclri	r7, 23
 	mov	r5, r7
 	mov	r4, r7
 	bmaski	r7, 8
 	cmpne	r14, r7
 	lsri	r5, 3
 	lsli	r4, 29
	.short 0xe002       //bt	0x20000c3e
 	movi	r14, 127
 	bseti	r14, 10
 	movi	r6, 7
 	lsli	r6, 7
 	addu	r14, r6
 	lsli	r3, 11
 	or	r3, r14
 	lsli	r3, 20
 	movi	r2, 0
 	or	r2, r4
 	or	r3, r5
 	ld	r14, (r0, 0)
 	addi	r0, 8
 	jmp	r15

__ftod:
 	subi	r0, 16
 	st	r15, (r0, 8)
 	st	r2, (r0, 0)
 	bsr	_f_ftod	// 20000bf8 <_f_ftod>
 	ld	r15, (r0, 8)
 	addi	r0, 16
 	jmp	r15

_f_itof:
	subi	r0, 8
	st	r15, (r0, 0)
	cmpnei	r2, 0
	.short 0xe80b      //	bf	0x20000c82
	btsti	r2, 31
	.short 0xe803      	//bf	0x20000c76
	movi	r1, 1
	rsubi	r2, 0
	.short 0xf001      //	br	0x20000c78
	movi	r1, 0
	mov	r4, r2
	mov	r2, r1
	movi	r3, 23
	movi	r5, 0
	jsri	sfpFloatNormalize	// 20000ca0 <sfpFloatNormalize>
	ld	r15, (r0, 0)
	addi	r0, 8
	jmp	r15

__itof:
 	subi	r0, 8
 	stm	r14-r15, (r0)
 	subi	r0, 8
 	bsr	_f_itof	// 20000c64 <_f_itof>
 	st	r2, (r0, 0)
 	addi	r0, 8
 	ldm	r14-r15, (r0)
 	addi	r0, 8
 	jmp	r15


.section .data
.align 4
errno:
.short 0x0000
.short 0x0000

.section .bss
.align 4
__sfpRoundMode:
.short 0x00
.short 0x00
.short 0x00
.short 0x00
