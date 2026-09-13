PROGRAMAS = cliente servidor

CFLAGS = -Wall

todo: $(PROGRAMAS)

cliente: cliente.c
	gcc $(CFLAGS) cliente.c -o cliente

servidor: servidor.c
	gcc $(CFLAGS) servidor.c -o servidor

borrar:
	rm -f *.o $(PROGRAMAS) *~


