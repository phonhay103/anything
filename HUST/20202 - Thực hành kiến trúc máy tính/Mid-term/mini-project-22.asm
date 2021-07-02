.data
	string: .space 100
	true: .asciiz "True"
	false: .asciiz "False"
	invalid: .asciiz "Invalid string"
.text
Input:
	li $v0, 8
    	li $a1, 100
    	la $a0, string
    	li $t8, 0	# i = 0
    	syscall
Main:
	# Input: 	$a0 = string[0]
	jal 	check
Get_word:
	# Input: 	$a0 = Address(word)
	# 		$a1 = length of word
	# Output:	$v0 the base address of the word
	#		$v1 length of the word
	jal 	load_word
	beq 	$v1, 0, Exit

	# Input:	$a0 = Address(word)
	# 		$a1 = length of word
	# Output:	$v0 = 1 or 0 (True or False)
	move $s0, $a0
	move $a0, $v0
	move $a1, $v1
	jal is_cyclone_phrase
	move $a0, $s0

	# Print True / False
	beq $v0, $zero, False
True:
	move $s0, $a0
	li $v0, 4
	la $a0, true
	syscall
	li $v0, 11
	li $a0, 32
	syscall
	move $a0, $s0
	j Get_word
False:
	move $s0, $a0
	li $v0, 4
	la $a0, false
	syscall
	li $v0, 11
	li $a0, 32
	syscall
	move $a0, $s0
	j Get_word
Invalid:
	li $v0, 4
	la $a0, invalid
	syscall
Exit:
	li $v0, 10
    	syscall

#------------------------------------------------------------------------------------
#Procedure 	check
# @brief 	Check if a string is valid, convert to lowercase
# @param[in] 	a0 the base address of the word need to be checked
#------------------------------------------------------------------------------------
#Procedure 	check
#function: 	Check if a string is valid, convert to lower case
check:
	li 	$t0, 0			# i = 0
loop:
	add 	$t1, $a0, $t0		# Address(string[i])
    	lb 	$t2, 0($t1)		# string[i]

    	beq 	$t2, '\n', end_of_check 	# Is newline char?
    	beq 	$t2, $zero, end_of_check 	# Is null char?
    	# If not
    	beq	$t2, 32, continue		# Is space char?
    	blt 	$t2, 'A', Invalid
    	bgt 	$t2, 'Z', check_valid
    	# If 'A' <= string[i] <= 'Z'
    	# Convert to lowercase
    	add 	$t2, $t2, 32	# 'A' + 32 = 'a'
    	sb 	$t2, 0($t1)
    	j 	continue
check_valid:
	# Check if 'a' <= string[i] <= 'z'
	blt 	$t2, 'a', Invalid
	bgt 	$t2, 'z', Invalid
continue:
    	addi 	$t0, $t0, 1	# i = i + 1
    	j 	loop
end_of_check:
	sb 	$zero, 0($t1) 	# Remove '\n' at end of string if exist
	jr 	$ra

#------------------------------------------------------------------------------------
#Procedure 	is_cyclone_phrase
# @brief 	check if a word is cyclone word
# @param[in] 	a0 the base address of the word need to be checked
# @param[in] 	a1 the length of this word
# @param[out] 	v0 the result check if this word is a cyclone word or not (1 or 0)
#------------------------------------------------------------------------------------
#Procedure 	is_cyclone_phrase
#function: 	Check if a word is cyclone word, the base address of this word in $a0
is_cyclone_phrase:
	li 	$t0, 0		# left = 0
	sub 	$t1, $a1, 1	# right = length - 1
	li 	$v0, 1		# Set defautl: v0 = 1
cp_loop:
	ble 	$t1, $t0, end_of_check_cyclone_phrase	# If right <= left, end
	# Check string[left] <= string[right]
	add 	$t2, $a0, $t0		# Address(string[0]+left) = Address(string[left])
	lb 	$t2, 0($t2)		# string[left]
	add 	$t3, $a0, $t1		# Address(string[0]+right) = Address(string[right])
	lb 	$t3, 0($t3)		# string[right]
	bgt 	$t2, $t3, return_false	# If string[left] > string[right] => The word is not cyclone word
	add 	$t0, $t0, 1		# left = left + 1
	
	# Check string[right] <= string[left]
	add 	$t2, $a0, $t0		# Address(string[0]+left) = Address(string[left])
	lb 	$t2, 0($t2)		# string[left]
	bgt 	$t3, $t2, return_false	# If string[right] > string[left] => The word is not cyclone word
	sub 	$t1, $t1, 1		# right = right - 1
	j 	cp_loop
return_false:
	li 	$v0, 0
end_of_check_cyclone_phrase:
	jr 	$ra

#------------------------------------------------------------------------------------
#Procedure 	load_word
# @brief 	load a word
# @param[in] 	a0 the base address of the string
# @param[out] 	v0 the base address of the word
# @param[out] 	v0 length of the word
#------------------------------------------------------------------------------------
#Procedure 	load_word
#function: 	Load a word, the base address of the string in $a0
load_word:
	add 	$v0, $a0, $t8		# Save Address(word)
	li	$v1, 0			# Length of word
get_char:
	add 	$t1, $a0, $t8		# Address(string[i])
    	lb 	$t1, 0($t1)		# string[i]
    	addi 	$t8, $t8, 1		# i = i + 1
    	beq 	$t1, 32, end_of_load_word	# Is space?
    	beq 	$t1, 0, end_of_load_word 	# Is null?
    	add	$v1, $v1, 1		# length = length + 1
    	j 	get_char
end_of_load_word:
	jr 	$ra
