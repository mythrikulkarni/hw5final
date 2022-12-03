
# Makefile for f2022, ecs36b
# https://macappstore.org/libjson-rpc-cpp/
# https://github.com/cinemast/libjson-rpc-cpp

CC = g++ -std=c++14
CFLAGS = -g -I/usr/include/jsoncpp

# LDFLAGS = 	-L/Users/sfwu/vcpkg/installed/arm64-osx/lib -ljsoncpp -L/opt/homebrew/lib/ -lmicrohttpd -ljsonrpccpp-common -ljsonrpccpp-server -ljsonrpccpp-client -lcurl

LDFLAGS = -L/usr/include/jsoncpp -ljsoncpp -lmicrohttpd -ljsonrpccpp-common -ljsonrpccpp-server -ljsonrpccpp-client -lcurl

INC	=	ecs36b_Common.h
INC_CL	=	GPS.h Network.h JvTime.h Person.h Thing.h IOT_Thing.h Core.h
OBJ	=	GPS.o Network.o JvTime.o Person.o Thing.o IOT_Thing.o Core.o

# rules.
all: 	hw5Forest hw5Home hw5GrandmaHome

#
#
# <target> : [... tab...] <dependency>
# [... tab ....] <action>

hw5Home.h:		ecs36b_hw5.json
	jsonrpcstub ecs36b_hw5.json --cpp-server=hw5Forest --cpp-client=hw5Home

hw5Forest.h:		ecs36b_hw5.json
	jsonrpcstub ecs36b_hw5.json --cpp-server=hw5Forest --cpp-client=hw5Home

hw5Home.o:		hw5Home.cpp hw5Home.h $(INC_CL) $(INC)
	$(CC) -c $(CFLAGS) hw5Home.cpp

hw5Forest.o:		hw5Forest.cpp hw5Forest.h $(INC_CL) $(INC)
	$(CC) -c $(CFLAGS) hw5Forest.cpp

hw5GrandmaHome.o:		hw5GrandmaHome.cpp hw5Forest.h $(INC_CL) $(INC)
	$(CC) -c $(CFLAGS) hw5GrandmaHome.cpp

ecs36b_JSON.o:		ecs36b_JSON.cpp $(INC)
	$(CC) -c $(CFLAGS) ecs36b_JSON.cpp

GPS.o:		GPS.cpp GPS.h $(INC)
	$(CC) -c $(CFLAGS) GPS.cpp

Core.o:		Core.cpp Core.h $(INC)
	$(CC) -c $(CFLAGS) Core.cpp

Network.o:	Network.cpp Network.h $(INC)
	$(CC) -c $(CFLAGS) Network.cpp

JvTime.o:	JvTime.cpp JvTime.h $(INC)
	$(CC) -c $(CFLAGS) JvTime.cpp

Person.o:	Person.cpp Person.h $(INC)
	$(CC) -c $(CFLAGS) Person.cpp

Thing.o:	Thing.cpp Thing.h $(INC)
	$(CC) -c $(CFLAGS) Thing.cpp

IOT_Thing.o:	IOT_Thing.cpp IOT_Thing.h Network.h $(INC)
	$(CC) -c $(CFLAGS) IOT_Thing.cpp

hw5GrandmaHome:	 hw5GrandmaHome.o ecs36b_JSON.o $(OBJ)
	$(CC) -o hw5GrandmaHome hw5GrandmaHome.o ecs36b_JSON.o $(OBJ) $(LDFLAGS)

hw5Forest:	 hw5Forest.o ecs36b_JSON.o $(OBJ)
	$(CC) -o hw5Forest hw5Forest.o ecs36b_JSON.o $(OBJ) $(LDFLAGS)

hw5Home:	 hw5Home.o ecs36b_JSON.o $(OBJ)
	$(CC) -o hw5Home hw5Home.o ecs36b_JSON.o $(OBJ) $(LDFLAGS)

clean:
	rm -f *.o *~ core hw5Home.h hw5Forest.h hw5Home hw5Forest


