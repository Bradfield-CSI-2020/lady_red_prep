full_lis : lis test_lis

lis : lis.c
	gcc -o lis lis.c

test_lis : 
	./lis
	./lis /var
	./lis `pwd`/..
	./lis ..

minitail: minitail.c
	gcc -o minitail minitail.c

