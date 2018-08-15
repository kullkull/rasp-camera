IDIR=./include
CC=gcc
CFLAGS=-I$(IDIR) -lncurses -lpthread -lmenu -g
SDIR=./src
ODIR=./obj
LDI=./lib
LIBS=
VERSION=rasp-3.0v

_DEPS=window.h
DEPS=$(patsubst %,$(IDIR)/%,$(_DEPS))

_OBJ=create_window.o destroy_window.o loader.o read_settings.o default_settings.o
OBJ=$(patsubst %,$(ODIR)/%,$(_OBJ))

_DEPSE=network.h service.h
DEPSE=$(patsubst %,$(IDIR)/%,$(_DEPSE))

_OBJE=core.o network_service.o start_service.o camera_service.o detect_service.o
OBJE=$(patsubst %,$(ODIR)/%,$(_OBJE))

all :  pre-pos $(VERSION) core

pre-pos:
	@echo "$(VERSION) is now Building..."


$(ODIR)/%.o: $(SDIR)/windows/%.c
	@echo "Building $@..."
	@sleep 0.2
	@$(CC) -c -o $@ $< $(CFLAGS)

$(ODIR)/%.o: $(SDIR)/settings/%.c
	@echo "Building $@..."
	@sleep 0.2
	@$(CC) -c -o $@ $< $(CFLAGS)

$(ODIR)/%.o: $(SDIR)/%.c
	@echo "Building $@..."
	@sleep 0.2
	@$(CC) -c -o $@ $< $(CFLAGS)

$(ODIR)/%.o: $(SDIR)/exec/%.c
	@echo "Building $@..."
	@sleep 0.2
	@$(CC) -c -o $@ $< $(CFLAGS)

$(ODIR)/%.o: $(SDIR)/services/%.c
	@echo "Building $@..."
	@sleep 0.2
	@$(CC) -c -o $@ $< $(CFLAGS)






$(VERSION): $(OBJ)
	@$(CC) -o bin/$@ $^ $(CFLAGS) $(LIBS)
	@echo "Installation Successfull! $(VERSION)"
	@echo "Creating Symbolic link..."	
	@ln -s bin/$(VERSION) .

core: $(OBJE)
	@$(CC) -o bin/$@ $^ $(CFLAGS) $(LIBS)
	@echo "Installation Successfull! core"

.PHONY: clean

clean:
	@rm -f $(ODIR)/*.o
	@rm -f $(VERSION)
	@rm -f bin/$(VERSION)
	@rm -f bin/core



