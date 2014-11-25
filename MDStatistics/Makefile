# Project: Console App (Linux)
# .mD. Statistics For Firearms Mod v2.6
# (c) 2002-2003 Michael Griffin

CC   = g++
OBJ  = config.o LogFunc.o WeaponFunc.o Mapfunc.o PlayerFunc.o FA26.o Stats.o Html1.o Html2.o log.o $(RES)
BIN  = md_stats
CFLAGS = $(INCS)  -s -O3 -fPIC

SYSTEM:= $(shell uname -s)
ifeq "$(SYSTEM)" "Linux"
DEFINE=_LINUX
endif

.PHONY: all all-before all-after clean clean-custom

all: all-before md_stats all-after


clean: clean-custom
	rm -f $(OBJ) $(BIN)

$(BIN): $(OBJ)
	$(CC) $(OBJ) -o "md_stats" $(LIBS) $(CFLAGS)

config.o: config.cpp
	$(CC) -c config.cpp -o config.o $(CFLAGS) -D$(DEFINE)

LogFunc.o: LogFunc.cpp
	$(CC) -c LogFunc.cpp -o LogFunc.o $(CFLAGS) -D$(DEFINE)

WeaponFunc.o: WeaponFunc.cpp
	$(CC) -c WeaponFunc.cpp -o WeaponFunc.o $(CFLAGS) -D$(DEFINE)

Mapfunc.o: Mapfunc.cpp
	$(CC) -c Mapfunc.cpp -o Mapfunc.o $(CFLAGS) -D$(DEFINE)

PlayerFunc.o: PlayerFunc.cpp
	$(CC) -c PlayerFunc.cpp -o PlayerFunc.o $(CFLAGS) -D$(DEFINE)

FA26.o: FA26.cpp
	$(CC) -c FA26.cpp -o FA26.o $(CFLAGS) -D$(DEFINE)

Stats.o: Stats.cpp
	$(CC) -c Stats.cpp -o Stats.o $(CFLAGS) -D$(DEFINE)

log.o: log.cpp
	$(CC) -c log.cpp -o log.o $(CFLAGS) -D$(DEFINE)

Html1.o: Html1.cpp
	$(CC) -c Html1.cpp -o Html1.o $(CFLAGS) -D$(DEFINE)

Html2.o: Html2.cpp
	$(CC) -c Html2.cpp -o Html2.o $(CFLAGS) -D$(DEFINE)

