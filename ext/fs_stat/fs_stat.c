#include <sys/statvfs.h>
#include "ruby.h"
#pragma GCC optimize ("O3")
#pragma clang optimize on

static VALUE statfs(VALUE obj, VALUE dir) {
	struct statvfs buf ;
	char *d = StringValuePtr(dir) ;
	VALUE hash = rb_hash_new() ;

	if(statvfs(d, &buf) < 0) return hash ;

	rb_hash_aset(hash, ID2SYM(rb_intern("block_size")), INT2FIX(buf.f_bsize)) ;
	rb_hash_aset(hash, ID2SYM(rb_intern("fragment_size")), INT2FIX(buf.f_frsize)) ;
	rb_hash_aset(hash, ID2SYM(rb_intern("blocks")), INT2FIX(buf.f_blocks)) ;
	rb_hash_aset(hash, ID2SYM(rb_intern("block_free")), INT2FIX(buf.f_bfree)) ;
	rb_hash_aset(hash, ID2SYM(rb_intern("block_avail_unpriv")), INT2FIX(buf.f_bavail)) ;
	rb_hash_aset(hash, ID2SYM(rb_intern("inodes")), INT2FIX(buf.f_files)) ;
	rb_hash_aset(hash, ID2SYM(rb_intern("free_inodes")), INT2FIX(buf.f_ffree)) ;
	rb_hash_aset(hash, ID2SYM(rb_intern("filesystem_id")), INT2FIX(buf.f_fsid)) ;
	rb_hash_aset(hash, ID2SYM(rb_intern("mount_flags")), INT2FIX(buf.f_flag)) ;
	rb_hash_aset(hash, ID2SYM(rb_intern("max_filename_length")), INT2FIX(buf.f_namemax)) ;

	return hash ;
}

void Init_fs_stat() {
	VALUE _linux_stat = rb_define_module("LinuxStat") ;
	VALUE fs = rb_define_module_under(_linux_stat, "FS") ;
	rb_define_module_function(fs, "stat", statfs, 1) ;
}
