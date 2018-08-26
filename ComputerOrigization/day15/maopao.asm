DATA SEGMENT
	BUFFER DB 20 DUP(0FFH)
	;定义数据段,放入20个FFH字节,DPU()相当于malloc(x)，用于写入数据
DATA ENDS

;使用默认堆栈段

CODE SEGMENT
	ASSUME CS:CODE,DS:DATA
	;代码段
	;设置代码段和数据段的段基地址

;各寄存器存的东西：
;AX 用于DOS调用，然后还用于*10之后存放结果
;BX 用于记录存了多少个数（每个数2字节16位）
;CX 用于存放得到每个数之前的临时值
;DX 在EXIT中用作移入结束符号和换行等等，在NEXT中DL用于存放*10放到AX里

START:
	MOV AX,DATA 	
	MOV DS,AX
	MOV BX,OFFSET BUFFER
	MOV DX,0
	MOV AX,0
	JMP NEXT



;下面是写入过程，各寄存器存的东西：
;AX 用于DOS调用，然后还用于*10，/10之后存放结果
;BX 用于记录存了多少个数（每个数2字节16位）
;CX 存放SHL、SHR的移动次数（超过1要放在CL里）
;DX 用于存放得到每个数之前的临时值
NNUM:;先把当前数字放入内存，然后使BX+2，然后下一个数字的开始（到NEXT）
	; MOV CL,4
	; SHR DX,CL		
	MOV [BX],DX
	ADD BX,2
	MOV DX,0
	;这里要让AL=0，DX=0，防止NEXT的第一句将数字*10对输入的第一个字符起作用
NEXT:
	;输入下一个数字
	MOV AH,1
	INT 21H
	;对输入的数进行判定，看是否是空格或者回车
	CMP AL,'.'		;如果是回车符号，则证明输入完了
	JZ SORTSTART	;结尾的话跳到SORT部分排序
	CMP AL,' '
	JZ NNUM		;如果是空格，则证明当前输入完了，将CX里的数字放到存储器中去
	;对之前的数字的高位数字调整,压缩BCD
	MOV CL,4
	SHL DX,CL
	;加入这次的个位数
	SUB AL,30H		;-30H得到对应的数字
	ADD DL,AL	
	JMP NEXT		;如果不是空格，证明当前元素没输入完，则再次检测输入当前数字的下一位




;上面完成了存入数据的操作，下面是排序的操作，各寄存器的内容：
;AX 存放交换的第一个数字
;BX 没用到，依旧保留原来的数值，即入读数的数量*2
;CX 内、外循环的次数，内循环完了出栈
;DX 没用到
SORTSTART:
	MOV AX,DATA 	
	MOV DS,AX
	MOV AX,BX
	SHR AX,1		;内容/2,得到数字个数
    MOV CX,AX        ;外层循环AX趟

;这里是外层循环
FORI:  
	PUSH CX          ;保存外层循环次数
    ;注意到外层第1次循环，内循环执行CX-1次，外层第2次循环，内循环执行CX-2次，...控制外循环的cx值恰就是内层循环次数
    MOV SI, 0        ;相当于内层循环时取数组内容的指针
;这里是内层循环
FORJ:
	MOV AX, [SI]     ;(ax)即a[j]
    CMP AX, [SI+2]   ;a[j]与a[j+1]比较
    JBE NEXTNUM      ;a[j]<=a[j+1]时	，跳到下一步NEXTNUM不交换
    XCHG AX, [SI+2]  ;交换
    MOV [SI], AX     ;最终效果是a[j]与a[j+1]交换了
;循环控制和转跳部分
NEXTNUM: 
	ADD SI, 2        ;下一个数,j++
    lOOP FORJ	     ;内层循环,使得CX--，然后再次执行，直到CX=0
    POP CX           ;恢复外层循环的CX，相当于当前的内层for（j）结束了，执行外层的fori
    lOOP FORI        ;外层循环





;这里是最后的显示
OUT_ALL:
	MOV DL,13	;回车 结尾
	MOV AH,2
	INT 21H
	MOV DL,10	;换行
	MOV AH,2
	INT 21H		;AH=2 单独显示DL的内容
	MOV BYTE PTR [BX],'$';结尾加上结尾符号标志

	MOV CX,BX
	MOV SI,0
SHOW:
	MOV DL,32	;空格 用于显示下一个数字
	MOV AH,2
	INT 21H
	MOV BX,[SI]
	ADD SI,2		;指向下一个字节的内容
	CMP BL,'$'
	JZ EXIT 		;设置出口
	MOV CL,4 		;CL是用在下面的SHL部分
	MOV CH,4 		;用于内层循环
;单独处理每两个字节的四位数字显示
BYTE1:
	MOV DX,BX
	AND DX,0F000H 	;仅保留最高四位
	SHR DH,CL   	;挪到DH的低四位
	MOV DL,DH
	ADD DL,30H 		;DL存放的恰好是所需要的ASC码
	MOV AH,2
	INT 21H
	SHL BX,CL		;将BX左移4位，把最高位让给下个字符
	DEC CH
	CMP CH,0
	JNZ BYTE1		;内层循环
	JMP SHOW



EXIT:
	MOV AH,4CH
	INT 21H  		
CODE ENDS			
	END START