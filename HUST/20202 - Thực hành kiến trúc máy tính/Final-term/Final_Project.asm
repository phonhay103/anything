.data
	String1: .asciiz  "                                           *************  \n"
	String2: .asciiz  "**************                            *3333333333333* \n"
	String3: .asciiz  "*222222222222222*                         *33333********  \n"
	String4: .asciiz  "*22222******222222*                       *33333*         \n"
	String5: .asciiz  "*22222*      *22222*                      *33333********  \n"
	String6: .asciiz  "*22222*       *22222*      *************  *3333333333333* \n"
	String7: .asciiz  "*22222*       *22222*    **11111*****111* *33333********  \n"
	String8: .asciiz  "*22222*       *22222*  **1111**       **  *33333*         \n"
	String9: .asciiz  "*22222*      *222222*  *1111*             *33333********  \n"
	String10: .asciiz "*22222*******222222*  *11111*             *3333333333333* \n"
	String11: .asciiz "*2222222222222222*    *11111*              *************  \n"
	String12: .asciiz "***************       *11111*                             \n"
	String13: .asciiz "      ---              *1111**                            \n"
	String14: .asciiz "    / o o \\             *1111****   *****                 \n"
	String15: .asciiz "    \\   > /              **111111***111*                  \n"
	String16: .asciiz "     -----                 ***********    dce.hust.edu.vn \n"
	strEmpty: .asciiz "                 "

	StrMenu0: .asciiz "\n------------ MENU ---------"
	StrMenu1: .asciiz "\n1. In chu DCE		 "
	StrMenu2: .asciiz "\n2. In khong mau		 "
	StrMenu3: .asciiz "\n3. In chu ECD		 "
	StrMenu4: .asciiz "\n4. Doi mau			 "
	StrMenu5: .asciiz "\n5. Thoat			 "
	StrInput: .asciiz "\nNhap gia tri: "
	D:	  .asciiz"\nNhap màu cho chu D(0->9): "
	C:	  .asciiz"\nNhap màu cho chu C(0->9): "
	E:	  .asciiz"\nNhap màu cho chu E(0->9): "

.text
main:
	li	$s1, 60 	# Do dai string
	li	$s2, 16		# So dong string
	li	$s6, 48		# '0'
	li	$s7, 57		# '9'
#-------------------------------------------------------------------------#
Menu:
	li	$v0, 4
	la	$a0, StrMenu0
	syscall
	li	$v0, 4
	la	$a0, StrMenu1
	syscall
	li	$v0, 4
	la	$a0, StrMenu2
	syscall
	li	$v0, 4
	la	$a0, StrMenu3
	syscall
	li	$v0, 4
	la	$a0, StrMenu4
	syscall
	li	$v0, 4
	la	$a0, StrMenu5
	syscall
	li	$v0, 4
	la	$a0, StrInput
	syscall
	li	$v0, 12
	syscall
	blt	$v0, '1', Menu
	bgt	$v0, '5', Menu
	
	beq	$v0, '1', Case1
	beq	$v0, '2', Case2
	beq	$v0, '3', Case3
	beq	$v0, '4', Case4
	beq	$v0, '5', Exit
#-------------------------------------------------------------------------#
Case1:	# In chu
	jal 	Writeln
	li 	$t0, 0		# row = 0
	la 	$a0, String1	
Loop1:
	beq 	$t0, $s2, Menu
	li 	$v0, 4		# Print $a0
	syscall

	add 	$a0, $a0, $s1	# String i -> String i+1
	addi 	$t0, $t0, 1	# row = row + 1
	j 	Loop1
#-------------------------------------------------------------------------#
Case2:	# Xoa mau
	jal 	Writeln
	li 	$t0, 0		# row = 0
	la 	$a0, String1
Loop2:
	beq 	$t0, $s2, Menu
	li 	$t1, 0		# j = 0, dung de duyet chuoi
	Loop2_print:
		beq 	$t1, $s1, Loop2_continue
		add 	$t2, $a0, $t1	# Address(String[j])
		lb	$t2, 0($t2)	# String[j]
		# ---------------------------------------- #
		move 	$s0, $a0
		blt	$t2, $s6, L2_print_char	# < 0
		bgt	$t2, $s7, L2_print_char	# > 9
		li 	$t2, ' ' 	# Convert to space
		L2_print_char:
			move	$a0, $t2
			li 	$v0, 11
			syscall
		move	$a0, $s0
		# ---------------------------------------- #
		addi	$t1, $t1, 1	# j = j + 1
		j 	Loop2_print
Loop2_continue:
	add 	$a0, $a0, $s1	# String i -> String i+1
	addi 	$t0, $t0, 1	# row = row + 1
	j 	Loop2
#-------------------------------------------------------------------------#
Case3: # Doi vi tri
	jal 	Writeln
	li 	$t0, 0		# row = 0
	la 	$a0, String1
	li	$t1, 32		# Space
Loop3:	
	beq 	$t0, $s2, Menu

	# Tach chuoi con - Thay ky tu khoang cach bang ky tu \0 o cuoi chu
	sb	$zero, 21($a0) # D
	sb	$zero, 41($a0) # C
	sb	$zero, 57($a0) # E
	move 	$s0, $a0

	# *** In chuoi con theo thu tu: ECD ***
	#1
	li 	$v0, 4
	la	$a0, 42($s0) # E - 42
	syscall
	li	$v0, 11
	add	$a0, $zero, $t1 # Space
	syscall
	#2
	li 	$v0, 4
	la	$a0, 22($s0) # C - 22
	#la	$a0, strEmpty
	syscall
	li	$v0, 11
	add	$a0, $zero, $t1 # Space
	syscall
	#3
	li 	$v0, 4
	la	$a0, 0($s0) # D - 0
	syscall
	#--New Line--#
	li	$v0, 4
	la	$a0, 58($s0)
	syscall
	#jal 	Writeln !ERROR!
	# ************************************** #

	# Tra lai nhu ban dau
	move	$a0, $s0
	sb	$t1, 21($a0)
	sb	$t1, 41($a0)
	sb	$t1, 57($a0)

	# Next string
	add 	$a0, $a0, $s1	# String i -> String i+1
	addi 	$t0, $t0, 1	# row = row + 1
	j 	Loop3
#-------------------------------------------------------------------------#
Case4:
	li 	$t0, 0		# row = 0
	la 	$a0, String1
InputColor:
	move	$s0, $a0
	# ------------------------- #
	ColorD:
		li	$v0, 4
		la	$a0, D
		syscall
		li	$v0, 12
		syscall
		blt	$v0, $s6, ColorD # < 0
		bgt	$v0, $s7, ColorD # > 9
		add	$s3, $zero, $v0
	ColorC:
		li	$v0, 4
		la	$a0, C
		syscall
		li	$v0, 12
		syscall
		blt	$v0, $s6, ColorC # < 0
		bgt	$v0, $s7, ColorC # > 9
		add	$s4, $zero, $v0
	ColorE:
		li	$v0, 4
		la	$a0, E
		syscall
		li	$v0, 12
		syscall
		blt	$v0, $s6, ColorE # < 0
		bgt	$v0, $s7, ColorE # > 9
		add	$s5, $zero, $v0
	# ------------------------- #
	move 	$a0, $s0
	jal 	Writeln
Loop4:
	beq 	$t0, $s2, Menu
	li 	$t1, 0		# j = 0, dung de duyet chuoi
	Loop4_print:
		beq 	$t1, $s1, Loop4_continue
		add 	$t2, $a0, $t1	# Address(String[j])
		lb	$t2, 0($t2)	# String[j]
		# ---------------------------------------- #
		move 	$s0, $a0
		blt	$t2, $s6, L4_print_char	 # < 0
		bgt	$t2, $s7, L4_print_char	 # > 9
		# Hien thi mau
		CheckD:
		bgt	$t1, 21, CheckC
		add	$t2, $zero, $s3
		j	L4_print_char
		CheckC:
		bgt	$t1, 41, CheckE
		add	$t2, $zero, $s4
		j	L4_print_char
		CheckE:
		add	$t2, $zero, $s5
		L4_print_char:
			move	$a0, $t2
			li 	$v0, 11
			syscall
		move	$a0, $s0
		# ---------------------------------------- #
		addi	$t1, $t1, 1	# j = j + 1
		j 	Loop4_print
Loop4_continue:
	add 	$a0, $a0, $s1	# String i -> String i+1
	addi 	$t0, $t0, 1	# row = row + 1
	j 	Loop4	
#-------------------------------------------------------------------------#
Writeln:
	move	$s0, $a0
	li	$v0, 11
	la	$a0, '\n'
	syscall
	move	$a0, $s0
	jr	$ra
#-------------------------------------------------------------------------#
Exit:
	li	$v0, 10
	syscall
