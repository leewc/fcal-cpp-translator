/*Prints out the first 10 Fibonacci numbers*/
main() {
	Int previous;
	previous = 0 ;
	Int current;
	current = 1 ;
	Int next;
	Int count;
	count = 0 ;
	while(count<10){
		next = current + previous ;
		print(next) ;
		print("\n") ;
		previous = current ;
		current = next ;		
	}
}


/*
1
1
2
3
5
8
13
21
34
55
*/