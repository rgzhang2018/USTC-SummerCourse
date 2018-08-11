DATAS SEGMENT
	
	;定义数据段
DATAS ENDS

;使用默认堆栈段

CODES SEGMENT
	ASSUME CS:CODES,DS:DATAS
	;代码段
	;设置代码段和数据段的段基地址

START:

	MOV AH,1 		;AH=01H，DOS调用里作用是输入一个字符，放入AL，有回显
	INT 21H
	MOV DL,AX		;把需要显示的内容放入DL
	MOV AH,02H		;AH=02H，DOS调用的功能是显示DL的内容
	INT 21H

	MOV AH,4CH
	INT 21H  		;调用结束返回
CODES ENDS			;代码段结束
	END START		;程序结束