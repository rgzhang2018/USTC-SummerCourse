DATAS SEGMENT
	STRING DB 13,10,'Hello World!',13,10,'$'
	;定义一个字符串，13表示回车，10表示换行，$表示结尾
DATAS ENDS

CODES SEGMENT
	ASSUME CS:CODES,DS:DATAS
	;代码段
	;设置代码段和数据段的段基地址

START:
	MOV AX,DATAS	;把字符串的地址放入指针DS（需经过AX转存）
	MOV DS,AX
	LEA DX,STRING	;即MOV DX,OFFSET STRING，将偏移地址移入DX
	MOV AH,9 		;AH=09H，DOS调用里作用是显示字符串，DS:DX位置的字符串
	INT 21H

	MOV AH,4CH
	INT 21H  		;调用结束返回
CODES ENDS			;代码段结束
	END START		;程序结束