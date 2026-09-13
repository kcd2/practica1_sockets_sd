PROGRAMAS = cliente servidor 

CFLAGS = -Wall

todo: $(PROGRAMAS)

cliente: WM_WS_M.c
	gcc $(CFLAGS) WM_WS_M.c -o cliente

servidor: WM_Central.c
	gcc $(CFLAGS) WM_Central.c -o servidor

borrar:
	rm -f *.o $(PROGRAMAS) *~

