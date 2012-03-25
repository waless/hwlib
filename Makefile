project_dir:=/home/seel/project/hwlib

src_dir:=$(project_dir)/hwu

obj_dir:=$(project_dir)/obj
obj_target_dir:=$(obj_dir)/debug

lib_dir:=$(project_dir)/lib
lib_target_dir:=$(lib_dir)/debug

bin_dir:=$(project_dir)/bin
bin_target_dir:=$(bin_dir)/debug

tag_dir:=$(project_dir)
tag_file:=$(tag_dir)/tags

source_files:=$(shell find $(src_dir)/ -name "*.c")
obj_files:=$(patsubst $(src_dir)/%.c,$(obj_target_dir)/%.o,$(source_files))
lib_files:=$(lib_target_dir)/libhw.a
bin_files:=$(bin_target_dir)/hw.exe

CC:=gcc-4
AR:=ar
CFLAGS:=-Wall -g -I $(project_dir) -ansi

target : make-dir lib bin

clean :
	@rm -rf $(obj_target_dir)
	@rm -rf $(lib_target_dir)
	@rm -rf $(bin_target_dir)

all : clean target

bin : $(bin_files)

lib : $(lib_files)

run :
	$(bin_files)

tags : $(tag_file)
	@ctags -f $@ -R $(src_dir)

test :
	@echo $(source_files)

.PHONY : target clean all test

make-dir :
	@mkdir -p $(obj_target_dir)
	@mkdir -p $(lib_target_dir)
	@mkdir -p $(bin_target_dir)

$(obj_files) : $(obj_target_dir)/%.o : $(src_dir)/%.c Makefile
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

$(bin_files) : $(obj_files)
	$(CC) $(CFLAGS) $+ -o $@

$(lib_files) : $(obj_files)
	ar rsv $@ $+

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
	@echo $(lib_target_dir)
	@echo $(bin_target_dir)
	@echo
	@echo $(source_files)
	@echo $(obj_files)
	@echo $(lib_files)
	@echo $(bin_files)

