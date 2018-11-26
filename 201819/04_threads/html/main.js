function Persona(name){
	return function suma(op1,op2){
		alert("<"+name+">:_"+(op1+op2))
	}
}

contable1 = Persona("Nacho")
contable2 = Persona("Eric")
contable1(2,3)
contable(5,4)
