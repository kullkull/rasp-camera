IDIR=./include
CC=gcc
CFLAGS=-I$(IDIR) -lncurses -lpthread -lmenu
SDIR=./src
ODIR=./obj
LDI=./lib
LIBS=
VERSION=rasp1.1v

_DEPS=Color_Setting.h Init_Program.h System_Command.h create_newslectwin.h create_newwin.h locate_shared_data.h destroy_win.h network_process.h picam_process.h picampic_process.h
DEPS=$(patsubst %,$(IDIR)/%,$(_DEPS))

_OBJ=Color_Setting.o Init_Program.o System_Command.o create_newslectwin.o create_newwin.o locate_shared_data.o destroy_win.o network_process.o picam_process.o picampic_process.o main.o
OBJ=$(patsubst %,$(ODIR)/%,$(_OBJ))


all :  pre-pos $(VERSION)

pre-pos:
	@echo "$(VERSION) is now Building..."

$(ODIR)/%.o: $(SDIR)/%.c $(DEPS)
	@echo "Building $@..."
	@sleep 0.2
	@$(CC) -c -o $@ $< $(CFLAGS)

$(VERSION): $(OBJ)
	@$(CC) -o bin/$@ $^ $(CFLAGS) $(LIBS)
	@echo "Installation Successfull! $(VERSION)"
	@echo "Creating Symbolic link..."	
	@ln -s bin/$(VERSION) .


.PHONY: clean

clean:
	@rm -f $(ODIR)/*.o
	@rm -f $(VERSION)
	@rm -f bin/$(VERSION)



