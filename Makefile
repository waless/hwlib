src_dir:=/home/waless/labo/hwlib/project/hwu

obj_dir:=/home/waless/labo/hwlib/project/obj
obj_target_dir:=$(obj_dir)/debug

bin_dir:=/home/waless/labo/hwlib/project/bin
bin_target_dir:=$(bin_dir)/debug

tag_dir:=.
tag_file:=$(tag_dir)/TAGS

source_files:=$(shell find $(src_dir)/ ! -name ".svn" -name "*.c")
obj_files:=$(patsubst $(src_dir)/%.c,$(obj_target_dir)/%.o,$(source_files))
bin_files:=$(bin_target_dir)/hwu.exe

CC:=gcc-4
CFLAGS:=-Wall -g -I /home/waless/labo/hwlib/project -ansi

target : make-dir $(bin_files) $(tag_file)

clean :
	@rm -rf $(obj_target_dir)
	@rm -rf $(bin_target_dir)

all : clean target

.PHONY : target clean all

make-dir :
	@mkdir -p $(obj_target_dir)
	@mkdir -p $(bin_target_dir)

$(obj_files) : $(obj_target_dir)/%.o : $(src_dir)/%.c Makefile
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

$(bin_files) : $(obj_files)
	$(CC) $(CFLAGS) $+ -o $@

$(tag_file) : $(source_files)
	etags $+

echo-variable :
	@echo $(source_files)
	@echo
	@echo $(obj_files)
	@echo
	@echo $(obj_dir)
	@echo $(bin_dir)
	@echo
	@echo $(obj_target_dir)
	@echo $(bin_target_dir)
	@echo
	@echo $(source_files)
	@echo $(obj_files)
	@echo $(bin_files)
