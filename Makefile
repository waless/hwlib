project_dir:=/home/seel/project/hwlib

src_dir:=$(project_dir)/hwu

obj_dir:=$(project_dir)/obj
obj_target_dir:=$(obj_dir)/debug

bin_dir:=$(project_dir)/bin
bin_target_dir:=$(bin_dir)/debug

tag_dir:=$(project_dir)
tag_file:=$(tag_dir)/tags

source_files:=$(shell find $(src_dir)/ -name "*.c")
obj_files:=$(patsubst $(src_dir)/%.c,$(obj_target_dir)/%.o,$(source_files))
bin_files:=$(bin_target_dir)/hwu.exe

CC:=gcc-4
CFLAGS:=-Wall -g -I $(project_dir) -ansi

target : make-dir $(bin_files) $(tag_file)

clean :
	@rm -rf $(obj_target_dir)
	@rm -rf $(bin_target_dir)

all : clean target

run :
	$(bin_files)

test :
	@echo $(source_files)

.PHONY : target clean all test

make-dir :
	@mkdir -p $(obj_target_dir)
	@mkdir -p $(bin_target_dir)

$(obj_files) : $(obj_target_dir)/%.o : $(src_dir)/%.c Makefile
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

$(bin_files) : $(obj_files)
	$(CC) $(CFLAGS) $+ -o $@

$(tag_file) : $(source_files)
	ctags $+

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

