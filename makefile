pull-all.out: src/pull-all.c
	$(CC) -Wall -Ofast -o pull-all.out src/pull-all.c

pull-all.1.gz: pull-all.1
	gzip -k pull-all.1

no-color: src/pull-all.c
	# Disabling color output
	$(CC) -Wall -Ofast -o pull-all.out -D NO_COLOR src/pull-all.c

clean:
	rm pull-all.out
	rm pull-all.1.gz

install: pull-all.out pull-all.1.gz
	sudo cp pull-all.out /usr/bin/pull-all
	sudo cp pull-all.1.gz /usr/share/man/man1/

uninstall:
	sudo rm /usr/bin/pull-all
	sudo rm /usr/share/man/man1/pull-all.1.gz

