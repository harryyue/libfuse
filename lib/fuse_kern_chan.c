/*
  FUSE: Filesystem in Userspace
  Copyright (C) 2001-2007  Miklos Szeredi <miklos@szeredi.hu>

  This program can be distributed under the terms of the GNU LGPLv2.
  See the file COPYING.LIB
*/

#include "fuse_lowlevel.h"
#include "fuse_kernel.h"
#include "fuse_i.h"

#include <stdio.h>
#include <errno.h>
#include <unistd.h>
#include <assert.h>

static void fuse_kern_chan_destroy(struct fuse_chan *ch)
{
	close(fuse_chan_fd(ch));
}

#define MIN_BUFSIZE 0x21000

struct fuse_chan *fuse_kern_chan_new(int fd)
{
	struct fuse_chan_ops op = {
		.destroy = fuse_kern_chan_destroy,
	};
	size_t bufsize = getpagesize() + 0x1000;
	bufsize = bufsize < MIN_BUFSIZE ? MIN_BUFSIZE : bufsize;
	return fuse_chan_new(&op, fd, bufsize);
}
