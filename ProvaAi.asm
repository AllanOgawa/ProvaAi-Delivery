.data
	espacos:   .asciiz "\n"
	menu:      .asciiz "MENU"
	addcli:    .asciiz "ADICIONAR CLIENTE"
	addmot:    .asciiz "ADICIONAR ENTREGADOR"
	addloj:    .asciiz "ADICIONAR LOJA"
	opcli:     .asciiz "1 - Adicionar Cliente "
	opmoto:    .asciiz "2 - Adicionar Entregador "
	oploja:    .asciiz "3 - Adicionar Loja "
	opcao:     .asciiz "Opcao: "
	cpfs:      .asciiz "CPF: "
	telefones: .asciiz "TELEFONE: "
	titular:   .asciiz "TITULAR DA LOJA: "
	nomes:     .asciiz "NOME: "
	cnpjs:     .asciiz "CNPJ: "
	lojas:     .asciiz "NOME DA LOJA: "
	ceps:      .asciiz "CEP: "
	cidades:   .asciiz "CIDADE: "
	estados:   .asciiz "ESTADO: "
	ruas:      .asciiz "ENDEREÇO: "
	cnhs:      .asciiz "CNH: "
	veiculos:  .asciiz "VEICULO: "
	anos:      .asciiz "ANO: "
	placas:    .asciiz "PLACA: "
	renavams:  .asciiz "RENAVAM DO VEICULO: "
	
	cpf:      .space 50
	telefone: .space 50
	nome:     .space 50
	cnpj:     .space 50
	loja:     .space 50
	cep:      .space 50
	cidade:   .space 50
	estado:   .space 50
	rua:      .space 50
	cnh:      .space 50
	veiculo:  .space 50
	ano:      .space 50
	placa:    .space 50
	renavam:  .space 50
	
.text
	#printa o menu
	li $v0,4
	la $a0,menu
	syscall
	jal espaco
	#printa opcao 1
	li $v0,4
	la $a0,opcli
	syscall 
	jal espaco
	#printa opcao 2
	li $v0,4
	la $a0,opmoto
	syscall
	jal espaco
	#printa opcao 3
	li $v0,4
	la $a0,oploja
	syscall
	jal espaco
	#printa opcao a ser escolhida
	li $v0,4
	la $a0,opcao
	syscall
	#leitura da entrada
	li $v0,5
	syscall
	move $t0,$v0 
	
	beq $t0,1,addCliente
	beq $t0,2,addMotorista
	beq $t0,3,addLoja

addCliente:
	jal espaco
	#printa ADICIONAR CLIENTE
	li $v0,4
	la $a0,addcli
	syscall
	jal espaco

	jal NomeCpfTelefone
	#CEP
	li $v0,4
	la $a0,ceps
	syscall
	li $v0,8
	la $a0,cep
	la $a1,50
	syscall
	#ESTADO
	li $v0,4
	la $a0,estados
	syscall
	li $v0,8
	la $a0,estado
	la $a1,50
	syscall
	#CIDADE
	li $v0,4
	la $a0,cidades
	syscall
	li $v0,8
	la $a0,cidade
	la $a1,50
	syscall
	#RUA
	li $v0,4
	la $a0,ruas
	syscall
	li $v0,8
	la $a0,rua
	la $a1,50
	syscall
	
	#printa os dados
	jal espaco
	li $v0,4
	la $a0,nome
	syscall
	li $v0,4
	la $a0,cpf
	syscall
	li $v0,4
	la $a0,telefone
	syscall
	li $v0,4
	la $a0,cep
	syscall
	li $v0,4
	la $a0,estado
	syscall
	li $v0,4
	la $a0,cidade
	syscall
	li $v0,4
	la $a0,rua
	syscall
	
	j fimprograma
	
addMotorista:
	jal espaco
	#printa ADICIONAR CLIENTE
	li $v0,4
	la $a0,addmot
	syscall
	jal espaco
	
	jal NomeCpfTelefone
	#CNH
	li $v0,4
	la $a0,cnhs
	syscall
	li $v0,8
	la $a0,cnh
	la $a1,50
	syscall
	#VEICULO
	li $v0,4
	la $a0,veiculos
	syscall
	li $v0,8
	la $a0,veiculo
	la $a1,50
	syscall
	#ANO
	li $v0,4
	la $a0,anos
	syscall
	li $v0,8
	la $a0,ano
	la $a1,50
	syscall
	#PLACA
	li $v0,4
	la $a0,placas
	syscall
	li $v0,8
	la $a0,placa
	la $a1,50
	syscall
	#RENAVAM
	li $v0,4
	la $a0,renavams
	syscall
	li $v0,8
	la $a0,renavam
	la $a1,50
	syscall
	
	#printa os dados
	jal espaco
	li $v0,4
	la $a0,nome
	syscall
	li $v0,4
	la $a0,cpf
	syscall
	li $v0,4
	la $a0,telefone
	syscall
	li $v0,4
	la $a0,cnh
	syscall
	li $v0,4
	la $a0,veiculo
	syscall
	li $v0,4
	la $a0,ano
	syscall
	li $v0,4
	la $a0,placa
	syscall
	li $v0,4
	la $a0,renavam
	syscall
	
	j fimprograma
	
addLoja:
	jal espaco
	#printa ADICIONAR CLIENTE
	li $v0,4
	la $a0,addloj
	syscall
	jal espaco

	#EMPRESA
	li $v0,4
	la $a0,lojas
	syscall
	li $v0,8
	la $a0,loja
	la $a1,50
	syscall
	#TITULAR
	li $v0,4
	la $a0,titular
	syscall
	li $v0,8
	la $a0,nome
	la $a1,50
	syscall
	#CNPJ
	li $v0,4
	la $a0,cnpjs
	syscall
	li $v0,8
	la $a0,cnpj
	la $a1,50
	syscall
	
	#printa os dados
	jal espaco
	li $v0,4
	la $a0,loja
	syscall
	li $v0,4
	la $a0,nome
	syscall
	li $v0,4
	la $a0,cnpj
	syscall
	
	j fimprograma
	
espaco:
	#printa o espaco
	li $v0,4
	la $a0,espacos
	syscall
	jr $ra
	
NomeCpfTelefone:	
	#NOME
	li $v0,4
	la $a0,nomes
	syscall
	li $v0,8
	la $a0,nome
	la $a1,50
	syscall
	#CPF
	li $v0,4
	la $a0,cpfs
	syscall
	li $v0,8
	la $a0,cpf
	la $a1,50
	syscall
	#TELEFONE
	li $v0,4
	la $a0,telefones
	syscall
	li $v0,8
	la $a0,telefone
	la $a1,50
	syscall
	
	jr $ra	
	
	
fimprograma:
	li $v0,10
	syscall

	
