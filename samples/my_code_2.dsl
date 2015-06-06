/*Prints out the first 10 Fibonacci numbers*/
main() {
	Int previous;
	previous = 0 ;
	Int current;
	current = 1 ;
	Int next;
	next = current + previous;
	Int count;
	count = 0 ;
	while(count<10){
		print(next) ;
		print("\n") ;
		next = current + previous ;
		previous = current ;
		current = next ;
		count = count + 1;		
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
