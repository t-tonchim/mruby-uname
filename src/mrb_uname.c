/*
** mrb_uname.c - Uname class
**
** Copyright (c) t-tonchim 2019
**
** See Copyright Notice in LICENSE
*/

#include "mruby.h"
#include "mruby/data.h"
#include "mrb_uname.h"
#include <mruby/error.h>
#include <sys/utsname.h>

#define DONE mrb_gc_arena_restore(mrb, 0);

typedef struct utsname mrb_utsname;

void mrb_uname_free(mrb_state *mrb, void *p) {
  mrb_free(mrb, (mrb_utsname *)p);
}

static const struct mrb_data_type mrb_uname_data_type = {
  "mrb_utsname", mrb_uname_free,
};

static mrb_value mrb_uname_sysname(mrb_state *mrb, mrb_value self)
{
  mrb_utsname *data = DATA_PTR(self);
  return mrb_str_new_cstr(mrb, data->sysname);
}

static mrb_value mrb_uname_init(mrb_state *mrb, mrb_value self)
{
  mrb_utsname *data;
  data = (mrb_utsname *)DATA_PTR(self);
  if (data) {
    mrb_free(mrb, data);
  }
  DATA_TYPE(self) = &mrb_uname_data_type;
  DATA_PTR(self) = NULL;

  data = (mrb_utsname *)mrb_malloc(mrb, sizeof(mrb_utsname));

  if(uname(data) < 0) {
    mrb_sys_fail(mrb, "uname");
  }

  DATA_PTR(self) = data;

  return self;
}

void mrb_mruby_uname_gem_init(mrb_state *mrb)
{
  struct RClass *uname;
  uname = mrb_define_class(mrb, "Uname", mrb->object_class);
  mrb_define_method(mrb, uname, "initialize", mrb_uname_init, MRB_ARGS_REQ(1));
  mrb_define_method(mrb, uname, "sysname", mrb_uname_sysname, MRB_ARGS_NONE());
  DONE;
}

void mrb_mruby_uname_gem_final(mrb_state *mrb)
{
}

