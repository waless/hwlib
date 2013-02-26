project_dir:=$(HOME)/projects/hwlib

src_dir:=$(project_dir)/src
include_dir:=$(project_dir)/include
test_dir:=$(project_dir)/test

obj_dir:=$(project_dir)/obj
obj_target_dir:=$(obj_dir)/debug

lib_dir:=$(project_dir)/lib
lib_target_dir:=$(lib_dir)/debug

bin_dir:=$(project_dir)/bin
bin_target_dir:=$(bin_dir)/debug

tag_dir:=$(project_dir)
tag_file:=$(tag_dir)/tags

source_files:=$(shell find $(src_dir)/ -name "*.c")
test_files:=$(shell  find $(test_dir)/ -name "*.c")
obj_files:=$(patsubst $(src_dir)/%.c,$(obj_target_dir)/%.o,$(source_files))
lib_files:=$(lib_target_dir)/libhw.a
bin_files:=$(bin_target_dir)/hw.exe

CC:=gcc-4
AR:=ar
CFLAGS:=-Wall -g -I $(include_dir) -ansi

target : bin

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
	@$(CC) $(CFLAGS) -c $< -o $@

$(bin_files) : $(test_files) $(lib_files)
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $< -L$(lib_target_dir) -lhw -o $@

$(lib_files) : $(obj_files)
	@mkdir -p $(dir $@)
	@$(AR) rsv $@ $+

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

