all: gcs
build_dir = .build

CC = gcc
CFLAGS = -g -Wall
INC_FLAGS = -lsqlite3 -lwiringPi

SOURCES = \
	main.c\
	byte_manipulation.c\
	sensor_payload.c\
	release_payload.c\
	data_packet.c\
	database.c\
	# udp.c\

OBJECTS = $(addprefix $(build_dir)/,$(SOURCES:.c=.o)) 

TARGET = gcs

$(TARGET) : $(OBJECTS)
	$(CC) $(CFLAGS) $(OBJECTS) $(INC_FLAGS) -o $@


$(build_dir)/%.o: %.c | $(build_dir)
	$(CC) $(CFLAGS) -c $< -o $@

.PHONY: $(build_dir) clean 

$(build_dir): 
	@mkdir -p $@

clean:
	rm -f $(TARGET) $(OBJECTS)

VPATH = src Data_Packet Database

